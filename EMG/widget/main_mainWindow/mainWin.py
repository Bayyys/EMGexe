import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial
from PyQt6.QtWidgets import QApplication, QMainWindow, QFileDialog, QWidgetAction, QMessageBox, QPushButton
from PyQt6.QtCore import Qt, QThread
# ui
from ui.mainWindow import Ui_MainWindow # 主界面
from widget.filter_frame.filterFrame import filterFrame # 滤波器设置控件
from utils.serialRead import serialRead # 串口读取线程
from utils.dataProcess import dataProcess # 数据处理线程
from utils.drawFrameUpdate import dataFrameUpdate # 图像显示界面更新线程
from utils.fftProcess import fftProcess # fft处理线程
from utils.dataSave import dataSave # 数据保存线程

class MyWindow(QMainWindow, Ui_MainWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
        self.initValues()
    
    def initUI(self):
        """初始化界面及槽函数"""
        self.setupUi(self)  # 初始化UI
        # QComboBox
        self.cb_channel.clear() # 通道数
        self.cb_channel.addItems(["2", "32"])   # 通道数列表初始化 
        self.cb_channel.setCurrentText("32")    # 通道数初始化设置: 32
        self.cb_rate.clear() # 采样率
        self.cb_rate.addItems(["250", "500", "1000", "2000", "4000", "8000", "16000"])  # 采样率列表初始化
        self.cb_rate.setCurrentText("1000") # 采样率初始化设置: 1000
        self.cb_xdis.clear() # 时基(x/s)
        self.cb_xdis.addItems(["1", "2", "3", "4", "5"])    # 时基列表初始化
        self.cb_xdis.setCurrentText("5")    # 时基初始化设置: 5
        self.cb_ydis.clear() # 幅值(y/uV)
        self.cb_ydis.addItems(["20", "50", "100", "200", "500", "1000", "2000", "5000", "10000"])   # 幅值列表初始化
        self.cb_ydis.setCurrentText("1000") # 幅值初始化设置: 1000
        # 文件路径初始化
        self.et_filePath.setText(os.getcwd()) # 文件路径初始化: 项目路径
        # 滤波器设置控件
        self.filterWidget: filterFrame=filterFrame(self)   
        act: QWidgetAction= QWidgetAction(self)
        act.setDefaultWidget(self.filterWidget)
        self.btn_filter.addAction(act)  # 滤波器触发按钮连接滤波器设置控件
        # 信号和槽
        self.btn_filePath.clicked.connect(self.btn_filePath_clicked) # 选择文件路径
        self.btn_filter.clicked.connect(self.btn_filter_clicked) # 滤波器设置
    
    def initValues(self):
        """初始化值"""
        self.port: dict[str, str]={}
        self.ser: serial.Serial= None
        self.file_name: str="" # 文件名
        self.serial_read_thread: serialRead=None   # 数据读取线程
        self.data_process_thread: dataProcess=None  # 数据处理线程
        # self.data_update_thread: dataUpdate=None   # 数据更新线程   # WAIT: 暂未使用
        # self.fft_process_thread: fftProcess=None   # fft处理线程   # WAIT: 暂未使用
        self.data_save_thread: dataSave=None     # 数据保存线程

    def btn_filePath_clicked(self) -> None:
        """btn_filePath: 选择文件路径"""
        filePath = QFileDialog.getExistingDirectory(self, "选择文件路径", "./")
        if filePath:
            self.et_filePath.setText(filePath)
    
    def btn_filter_clicked(self) -> None:
        """
        btn_filter: 滤波器按钮点击

        根据滤波器按钮文字, 修改滤波器文字设置(ON/OFF)
        """
        if self.btn_filter.text() == "滤波器-ON":
            self.btn_filter.setText("滤波器-OFF")
        else:
            self.btn_filter.setText("滤波器-ON")

    def data_save_signal_slot(self, file_name: str="") -> None:
        """
        文件名修改槽函数

        由data_save_thread data_save_signal信号触发, 线程创建时新建文件, 提供文件名(取决于创建时间)
        
        Attribute:
        ------
            file_name:
                文件名
        """
        self.file_name = file_name

    def btn_connect_success(self) -> None:
        """
        连接成功

        连接按钮触发成功, 修改按钮文字为'断开', 修改标签提示为'串口信息', 修改标签提示为绿色(rgb(64, 192, 87))
        """
        self.lb_connect.setStyleSheet("color: rgb(64, 192, 87); font-weight: bold" )
        self.lb_connect.setText(self.port['port'])
        self.lb_connect.setStatusTip(self.port['port'])
        self.lb_connect.setToolTip(self.port['port'])
        self.btn_connect.setText("断开")
    
    def btn_connect_failure(self) -> None:
        """
        连接失败

        连接按钮触发失败, 弹出提示信息框
        """
        self.ser: serial.Serial=None
        box = QMessageBox.critical(self, "错误", "串口打开失败!", QMessageBox.StandardButton.Ok | QMessageBox.StandardButton.Retry)
        if box == QMessageBox.StandardButton.Ok:
            ...
        elif box == QMessageBox.StandardButton.Retry:
            self.btn_connect_clicked()
    
    def btn_connect_init(self) -> None:
        """连接初始化"""
        self.ser = None
        self.lb_connect.setStyleSheet("color: rgb(0, 0, 0)" )
        self.lb_connect.setText("未连接")
        self.lb_connect.setStatusTip("未连接")
        self.lb_connect.setToolTip("未连接")
        self.lb_start.setText("未连接")
        self.lb_start.setStyleSheet("color: rgb(0, 0, 0)" )

    def btn_connect_repeat(self) -> None:
        """重复连接"""
        box = QMessageBox(QMessageBox.Icon.Question, "提示", "串口已打开 ["+self.port['port']+"]\n是否重新打开?")
        box_ok = box.addButton("重新连接", QMessageBox.ButtonRole.NoRole)
        box_no = box.addButton("取消", QMessageBox.ButtonRole.NoRole)
        box.exec()
        if box.clickedButton() == box_ok:
            self.btn_connect_init()
            self.btn_connect_clicked()
        elif box.clickedButton() == box_no:
            ...

    def btn_start_success(self) -> None:
        """
        开始测量成功, 更新界面文本

        开始按钮触发成功, 修改按钮文字为'暂停', 修改标签提示为'采集中', 修改标签样式为'绿色(rgb(64, 192, 87))-粗体'
        """
        self.btn_start.setText("暂停")
        self.lb_start.setText("采集中")
        self.lb_start.setStyleSheet("color: rgb(64, 192, 87); font-weight: bold" )
        ...

    def btn_start_failure(self) -> None:
        """
        开始测量失败

        开始按钮触发失败, 认为串口打开失败, 弹出提示对话框, 选择重连
        """
        box: QMessageBox=QMessageBox(QMessageBox.Icon.Information, "串口未打开", "请先打开串口!")
        box.setWindowFlags(Qt.WindowType.WindowCloseButtonHint)
        box_ok: QPushButton=box.addButton("连接", QMessageBox.ButtonRole.NoRole)    # 连接按钮
        box_no: QPushButton=box.addButton("取消", QMessageBox.ButtonRole.NoRole)    # 取消按钮
        box.exec()
        if box.clickedButton() == box_ok:   # 连接, 触发 btn_connect_clicked()
            self.btn_connect_clicked()
        elif box.clickedButton() == box_no:
            ...

    def btn_stop_success(self) -> None:
        """
        暂停测量成功

        暂停按钮触发成功, 同时触发文件保存对话框, 修改按钮文字为'开始', 修改你标签提示为'停止检测', 修改标签样式为'红色(rgb(224, 49, 49))-粗体'
        """
        self.btn_start.setText("开始")
        self.lb_start.setText("停止采集")
        self.lb_start.setStyleSheet("color: rgb(224, 49, 49); font-weight: bold")
        self.file_save_dialog(self.file_name)
        self.serial_read_thread: serialRead=None   # 数据读取线程
        self.data_process_thread: dataProcess=None  # 数据处理线程
        # self.data_update_thread: dataUpdate=None   # 数据更新线程   # WAIT: 暂未使用
        # self.fft_process_thread: fftProcess=None   # fft处理线程   # WAIT: 暂未使用
        self.data_save_thread: dataSave=None     # 数据保存线程

    
    
    def file_save_dialog(self, file_name: str="") -> None:
        """文件保存对话框"""
        box = QMessageBox(QMessageBox.Icon.Information, "提示", "数据保存成功!\n保存路径: {}".format(self.et_filePath.text()))
        open_btn: QPushButton=box.addButton("打开", QMessageBox.ButtonRole.NoRole)
        save_btn: QPushButton=box.addButton("另存为", QMessageBox.ButtonRole.NoRole)
        delete_btn: QPushButton=box.addButton("删除", QMessageBox.ButtonRole.NoRole)
        yes_btn: QPushButton=box.addButton("确定", QMessageBox.ButtonRole.NoRole)
        box.exec()

        if box.clickedButton() == open_btn: # 打开按钮
            os.startfile(self.et_filePath.text())
        elif box.clickedButton() == save_btn:   # 另存为按钮
            fileName = QFileDialog.getSaveFileName(self, "另存为", "./", "文本文件(*.txt)")   # 返回元组: (文件名, 文件类型)
            filePath = os.path.dirname(fileName[0])
            if fileName[0] != "":
                if os.path.exists(fileName[0]):
                    os.remove(fileName[0])
                os.rename(file_name, fileName[0])
                self.et_filePath.setText(filePath)
            self.file_save_dialog(fileName[0])
        elif box.clickedButton() == delete_btn: # 删除按钮
            try:
                os.remove(file_name)
                # 如果文件夹为空, 则删除文件夹
                path = os.path.dirname(file_name)
                if not os.listdir(path):
                    os.removedirs(path)
            except:
                print("删除失败")
        elif box.clickedButton() == yes_btn:    # 确定
            ...

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = MyWindow()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
