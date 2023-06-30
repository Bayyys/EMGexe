import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication, QMainWindow, QFileDialog, QWidgetAction, QMessageBox
from PyQt6.QtCore import Qt
# ui
from ui.mainWindow import Ui_MainWindow
from widget.filter_frame.filterFrame import filterFrame

class MyWindow(QMainWindow, Ui_MainWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
        self.initValues()
    
    def initUI(self):
        self.setupUi(self)  # 初始化UI
        # QComboBox
        self.cb_channel.clear() # 通道数
        self.cb_channel.addItems(["2", "32"])
        self.cb_channel.setCurrentText("32")
        self.cb_rate.clear() # 采样率
        self.cb_rate.addItems(["250", "500", "1000", "2000", "4000", "8000", "16000"])
        self.cb_rate.setCurrentText("1000")
        self.cb_xdis.clear() # 时基s
        self.cb_xdis.addItems(["1", "2", "3", "4"])
        self.cb_xdis.setCurrentText("4")
        self.cb_ydis.clear() # 幅值uV
        self.cb_ydis.addItems(["20", "50", "100", "200", "500", "1000", "2000", "5000", "10000"])
        self.cb_ydis.setCurrentText("1000")
        # 文件路径初始化
        self.et_filePath.setText(os.getcwd()) # 文件路径
        # 滤波器设置控件
        self.filterWidget = filterFrame(self)
        act = QWidgetAction(self)
        act.setDefaultWidget(self.filterWidget)
        self.btn_filter.addAction(act)
        # 信号和槽
        self.btn_filePath.clicked.connect(self.btn_filePath_clicked) # 选择文件路径
        self.btn_filter.clicked.connect(self.btn_filter_clicked) # 滤波器设置
    
    def initValues(self):
        self.port = {}
        self.ser = None
        self.file_name = "" # 文件名
        self.serial_read_thread = None
        self.data_process_thread = None
        self.data_save_thread = None

    def btn_filePath_clicked(self):
        filePath = QFileDialog.getExistingDirectory(self, "选择文件路径", "./")
        if filePath:
            self.et_filePath.setText(filePath)
    
    def btn_filter_clicked(self):
        if self.btn_filter.text() == "滤波器-ON":
            self.btn_filter.setText("滤波器-OFF")
        else:
            self.btn_filter.setText("滤波器-ON")

    def file_save_dialog(self, file_name: str=""):
        box = QMessageBox(QMessageBox.Icon.Information, "提示", "数据保存成功!\n保存路径: {}".format(self.et_filePath.text()))
        open_btn = box.addButton("打开", QMessageBox.ButtonRole.NoRole)
        save_btn = box.addButton("另存为", QMessageBox.ButtonRole.NoRole)
        delete_btn = box.addButton("删除", QMessageBox.ButtonRole.NoRole)
        yes_btn = box.addButton("确定", QMessageBox.ButtonRole.NoRole)
        box.exec()

        if box.clickedButton() == open_btn:
            os.startfile(self.et_filePath.text())
        elif box.clickedButton() == save_btn:
            # 另存为 .txt
            fileName = QFileDialog.getSaveFileName(self, "另存为", "./", "文本文件(*.txt)")   # 返回元组: (文件名, 文件类型)
            filePath = os.path.dirname(fileName[0])
            if fileName[0] != "":
                if os.path.exists(fileName[0]):
                    os.remove(fileName[0])
                os.rename(file_name, fileName[0])
                self.et_filePath.setText(filePath)
            self.file_save_dialog(fileName[0])
        elif box.clickedButton() == delete_btn:
            try:
                os.remove(file_name)
                # 如果文件夹为空, 则删除文件夹
                path = os.path.dirname(file_name)
                if not os.listdir(path):
                    os.removedirs(path)
            except:
                print("删除失败")
        elif box.clickedButton() == yes_btn:
            ...

    def data_save_signal_slot(self, file_name: str=""):
        self.file_name = file_name

    def btn_connect_success(self):
        self.lb_connect.setStyleSheet("color: rgb(64, 192, 87); font-weight: bold" )
        self.lb_connect.setText(self.port['port'])
        self.lb_connect.setStatusTip(self.port['port'])
        self.lb_connect.setToolTip(self.port['port'])
        self.btn_connect.setText("断开")
    
    def btn_connect_failure(self):
        self.ser = None
        box = QMessageBox.critical(self, "错误", "串口打开失败!", QMessageBox.StandardButton.Ok | QMessageBox.StandardButton.Retry)
        if box == QMessageBox.StandardButton.Ok:
            ...
        elif box == QMessageBox.StandardButton.Retry:
            self.btn_connect_clicked()
    
    def btn_connect_init(self):
        self.ser = None
        self.lb_connect.setStyleSheet("color: rgb(0, 0, 0)" )
        self.lb_connect.setText("未连接")
        self.lb_connect.setStatusTip("未连接")
        self.lb_connect.setToolTip("未连接")
        self.lb_start.setText("未连接")
        self.lb_start.setStyleSheet("color: rgb(0, 0, 0)" )

    def btn_connect_repeat(self):
        box = QMessageBox(QMessageBox.Icon.Question, "提示", "串口已打开 ["+self.port['port']+"]\n是否重新打开?")
        box_ok = box.addButton("重新连接", QMessageBox.ButtonRole.NoRole)
        box_no = box.addButton("取消", QMessageBox.ButtonRole.NoRole)
        box.exec()
        if box.clickedButton() == box_ok:
            self.btn_connect_init()
            self.btn_connect_clicked()
        elif box.clickedButton() == box_no:
            ...

    def btn_start_success(self):
        self.btn_start.setText("暂停")
        self.lb_start.setText("采集中")
        self.lb_start.setStyleSheet("color: rgb(64, 192, 87); font-weight: bold" )
        ...

    def btn_start_failure(self):
        box = QMessageBox(QMessageBox.Icon.Information, "串口未打开", "请先打开串口!")
        box.setWindowFlags(Qt.WindowType.WindowCloseButtonHint)
        box_ok = box.addButton("连接", QMessageBox.ButtonRole.NoRole)
        box_no = box.addButton("取消", QMessageBox.ButtonRole.NoRole)
        box.exec()
        if box.clickedButton() == box_ok:
            self.btn_connect_clicked()
        elif box.clickedButton() == box_no:
            ...

    def btn_stop_success(self):
        self.btn_start.setText("开始")
        self.lb_start.setText("停止采集")
        self.lb_start.setStyleSheet("color: rgb(224, 49, 49); font-weight: bold")
        self.file_save_dialog(self.file_name)
        self.serial_read_thread = None
        self.data_process_thread = None
        self.data_save_thread = None

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = MyWindow()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
