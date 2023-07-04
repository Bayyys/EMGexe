import sys
import os
from PyQt6 import QtGui
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication
from PyQt6.QtGui import QCloseEvent
from widget.main_mainWindow.mainWin import MyWindow
from widget.canvas_frame.drawFrame import drawFrame
from widget.serial_dialog.serialDialog import serialDialog
from widget.fft_widget.fftWidget import fftWidget
# utils
from utils.serialRead import serialRead
from utils.dataProcess import dataProcess
from utils.dataSave import dataSave
import utils.serialUtils as serialUtils

class mainWin(MyWindow):
    def __init__(self) -> None:
        super().__init__()
    
    def initUI(self) -> None:
        """初识化界面及槽函数"""
        super().initUI()
        self.drawFrame: drawFrame=drawFrame()   # 图像显示界面
        self.chart_frame.layout().addWidget(self.drawFrame) # 将图像显示界面添加到主界面
        self.drawFrame.fftChangeMode(False) # 默认模式为时域显示
        self.fftWidget: fftWidget=fftWidget()   # fft显示界面
        self.layout_fft.layout().addWidget(self.fftWidget)  # 将fft显示界面添加到主界面
        self.cb_channel.currentTextChanged.connect(self.cb_channel_currentTextChanged)  # 信道选择
        self.cb_rate.currentIndexChanged.connect(self.cb_rate_currentIndexChanged)  # 采样率选择
        self.cb_xdis.currentIndexChanged.connect(self.cb_xdis_currentIndexChanged)  # x轴显示范围选择
        self.cb_ydis.currentIndexChanged.connect(self.cb_ydis_currentIndexChanged)  # y轴显示范围选择
        self.btn_reset.clicked.connect(self.drawFrame.resetChart)   # 重置图像显示界面
        self.btn_connect.clicked.connect(self.btn_connect_choose)   # 连接/断开串口
        self.btn_start.clicked.connect(self.btn_start_choose)   # 开始/暂停采集
        self.btn_mode.clicked.connect(self.btn_mode_clicked)    # 切换显示模式
        self.sb_fft_x.valueChanged.connect(self.cb_fft_currentIndexChanged)   # fft x轴选择
    
    def cb_fft_currentIndexChanged(self) -> None:
        """fft x轴选择"""
        self.fftWidget.cb_fft_y_currentIndexChanged(int(self.sb_fft_x.value())) # 更新fft显示界面

    def initValues(self) -> None:
        """初始化变量"""
        super().initValues()

    def cb_channel_currentTextChanged(self) -> None:
        """
        通道数改变

        更新图像显示界面和fft显示界面
        """
        self.drawFrame.updateChart(int(self.cb_channel.currentText()))
        self.fftWidget.updateChart(int(self.cb_channel.currentText()))
    
    def cb_rate_currentIndexChanged(self) -> None:
        """
        采样率改变

        更新图像显示界面和fft显示界面
        """
        self.drawFrame.updateRate(int(self.cb_rate.currentText()))
        self.fftWidget.updateRate(int(self.cb_rate.currentText()))
    
    def cb_xdis_currentIndexChanged(self) -> None:
        """
        x轴显示范围改变

        更新图像显示界面
        """
        self.drawFrame.updateXdis(int(self.cb_xdis.currentText()))

    def cb_ydis_currentIndexChanged(self) -> None:
        """
        y轴显示范围改变

        更新图像显示界面
        """
        self.drawFrame.updateYdis(int(self.cb_ydis.currentText()))
    
    def btn_mode_clicked(self) -> None:
        """
        切换显示模式

        更新模式按钮文本, 更新图像显示(setFFTMode)
        """
        if self.btn_mode.text() == "模式: 时域信号":
            self.btn_mode.setText("模式: 频域分析")
            self.drawFrame.fftChangeMode(True)
            ...
        elif self.btn_mode.text() == "模式: 频域分析":
            self.btn_mode.setText("模式: 时域信号")
            self.drawFrame.fftChangeMode(False)
            ...
    
    def btn_connect_choose(self) -> None:
        """
        连接/断开串口

        根据按钮文本选择连接或断开
        """
        if self.btn_connect.text() == "连接":
            self.btn_connect_clicked()
        elif self.btn_connect.text() == "断开":
            self.btn_disconnect_clicked()

    def btn_connect_clicked(self) -> None:
        """
        连接串口

        打开串口设置对话框, 获取串口参数, 打开串口
        """
        if self.ser is not None:    # 判断是否重复连接
            self.btn_connect_repeat()
            return
        serial_dialog = serialDialog()  # 打开串口设置对话框
        serial_dialog.exec()
        if serial_dialog.result() == serialDialog.DialogCode.Accepted:  # 连接串口
            self.port = serial_dialog.getSerParams()
            self.ser = serialUtils.serialOpen(com=self.port['port'], bps=self.port['baudrate'])
            if serialUtils.serialIsOpen(self.ser):  # 判断是否连接成功
                self.btn_connect_success()
            else:
                self.btn_connect_failure()
        elif serial_dialog.result() == serialDialog.DialogCode.Rejected:    # 取消连接
            self.btn_connect_init()

    def btn_disconnect_clicked(self) -> None:
        """
        断开串口

        关闭串口, 更新按钮文本
        """
        if self.data_save_thread is not None:   # 判断是否暂停(关闭线程)
            try:
                self.btn_stop_clicked() # 停止测量、关闭线程、保存数据
            except:
                ...
        if serialUtils.serialClose(self.ser):   # 关闭串口, 并判断是否关闭成功
            self.btn_connect_init()
            self.btn_connect.setText("连接")
        else:
            print("串口关闭失败!")

    def btn_start_choose(self) -> None:
        """
        开始/暂停采集

        根据按钮文本选择开始或暂停
        """
        if self.btn_start.text() == "开始":
            self.btn_start_clicked()
        elif self.btn_start.text() == "暂停":
            self.btn_stop_clicked()

    def btn_start_clicked(self) -> None:
        """
        开始采集

        判断串口是否打开, 打开串口, 开启线程
        """
        if not serialUtils.serialIsOpen(self.ser):  # 判断串口是否打开
            self.btn_start_failure()    # 串口未打开, 打开提示框, 判断是否重新连接
            return

        # 串口已打开, 设置通道数、采样率, 开启线程
        serialUtils.serialWrite(self.ser, state='start', connect='usb', sample_rate=self.cb_rate.currentText(), channel=self.cb_channel.currentText())

        """-----开启线程-----"""
        # 串口读取线程
        self.serial_read_thread: serialRead=serialRead(self,    # 父窗口
                                                       self.ser,    # 串口
                                                       self.cb_channel.currentText()) # 通道数
        # 数据处理线程
        self.data_process_thread: dataProcess=dataProcess(self,    # 父窗口
                                               self.cb_channel.currentText(),   # 通道数
                                               self.cb_rate.currentText(),  # 采样率
                                               True if self.btn_filter.text() == "滤波器-ON" else False,    # 是否开启滤波器
                                               self.filterWidget.getParameters())   # 滤波器参数
        # # 数据更新线程  # WAIT: 暂未使用
        # self.data_update_thread: dataUpdate=dataUpdate(self,  # 父窗口
        #                                      self.drawFrame,    # 图像显示窗口
        #                                      self.fftWidget)    # 频谱显示窗口
        # fft处理线程   # WAIT: 暂未使用
        # self.fft_process_thread: fftProcess=fftProcess(self,  # 父窗口
        #                                      self.cb_channel.currentText(),  # 通道数
        #                                      self.cb_rate.currentText())    # 采样率
        # 数据保存线程
        self.data_save_thread: dataSave=dataSave(self,  # 父窗口
                                         self.et_filePath.text(),   # 文件路径
                                         self.cb_channel.currentText()) # 通道数
        
        """-----线程信号连接-----"""
        self.serial_read_thread.serial_read_data_decode_update_signal.connect(self.data_process_thread.put_data)    # 串口读取线程 -> 数据处理线程
        self.serial_read_thread.serial_read_data_decode_update_signal.connect(self.data_save_thread.put_data)   # 串口读取线程 -> 数据保存线程
        # self.data_process_thread.data_process_signal.connect(self.data_update_thread.put_data)    # 数据处理线程 -> 数据更新线程
        self.data_process_thread.data_process_signal.connect(self.fftWidget.update_chart)   # 数据处理线程 -> 频谱显示窗口
        self.data_process_thread.data_process_signal.connect(self.drawFrame.updateData)  # 数据处理线程 -> 图像显示窗口
        # self.fft_process_thread.fft_process_signal.connect(self.fftWidget.updateChart)    # fft处理线程 -> 频谱显示窗口
        self.data_save_thread.data_save_signal.connect(self.data_save_signal_slot)  # 数据保存线程 -> 主窗口(文件名称更新)
        self.filterWidget.filter_update_signal.connect(self.data_process_thread.updateFilterParam)  # 滤波器窗口 -> 数据处理线程(滤波器参数更新)

        """-----线程启动-----"""
        self.serial_read_thread.start()
        self.data_process_thread.start()
        # self.data_update_thread.start()
        # self.fft_process_thread.start()
        self.data_save_thread.start()
        self.btn_start_success()    # 更新按钮文本

    def btn_stop_clicked(self) -> None:
        """
        暂停采集

        停止测量, 关闭线程, 保存数据
        """
        serialUtils.serialWrite(self.ser, state='stop')   # 发送停止采集指令
        self.serial_read_thread.del_thread()    
        self.data_process_thread.del_thread()
        # self.data_update_thread.del_thread()
        # self.fft_process_thread.del_thread()
        self.data_save_thread.del_thread()
        self.btn_stop_success() # 暂停采集, 更新按钮文本

    def btn_filter_clicked(self):
        """
        滤波器开关

        更新数据处理线程滤波器开关标志
        """
        super(mainWin, self).btn_filter_clicked()
        try:
            self.data_process_thread.isFilter = True if self.btn_filter.text() == "滤波器-ON" else False
        except:
            ...

    def closeEvent(self, a0: QCloseEvent) -> None:  # 重写窗口关闭事件, 断开连接
        try:
            self.btn_disconnect_clicked()
        except:
            ...
        return super().closeEvent(a0)

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = mainWin()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
