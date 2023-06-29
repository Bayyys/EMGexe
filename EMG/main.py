import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QWidgetAction
from widget.main_mainWindow.mainWin import MyWindow
from widget.canvas_frame.drawFrame.drawFrame import drawFrame
from widget.serial_dialog.serialDialog import serialDialog
# utils
from utils.getCom import getCom
from utils.serialRead import serialRead
from utils.dataProcess import DataProcess
import utils.serialUtils as serialUtils

class mainWin(MyWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
        self.initValues()
    
    def initUI(self):
        super().initUI()
        self.drawFrame = drawFrame()
        self.chart_frame.layout().addWidget(self.drawFrame)
        self.cb_channel.currentTextChanged.connect(self.cb_channel_currentTextChanged)
        self.btn_connect.clicked.connect(self.btn_connect_clicked)
        self.btn_disconnect.clicked.connect(self.btn_disconnect_clicked)
        self.btn_start.clicked.connect(self.btn_start_clicked)
        self.btn_stop.clicked.connect(self.btn_stop_clicked)
    
    def initValues(self):
        self.serialDialog = serialDialog()
        self.port = {}
        self.ser = None

    def cb_channel_currentTextChanged(self):
        self.drawFrame.updateChart(int(self.cb_channel.currentText()))
    
    def btn_connect_clicked(self):
        self.serialDialog.show()
        if self.serialDialog.exec() == serialDialog.DialogCode.Accepted:
            self.port = self.serialDialog.getSerParams()
            self.ser = serialUtils.serialOpen(com=self.port['port'], bps=self.port['baudrate'])
            if serialUtils.serialIsOpen(self.ser):
                print("串口打开成功!")
            else:
                print("串口打开失败!")
    
    def btn_disconnect_clicked(self):
        try:
            self.btn_stop_clicked()
        except:
            ...
        if serialUtils.serialClose(self.ser):
            print("串口关闭成功!")
        else:
            print("串口关闭失败!")
    
    def btn_start_clicked(self):
        serialUtils.serialWrite(self.ser, state='start', connect='usb', sample_rate=self.cb_rate.currentText(), channel=self.cb_channel.currentText())
        self.serial_read_thread = serialRead(self, self.ser, self.cb_channel.currentText())
        self.data_process_thread = DataProcess(self, self.cb_channel.currentText(), self.cb_rate.currentText(), True if self.btn_filter.text() == "滤波器-ON" else False, self.filterWidget.getParameters())
        self.serial_read_thread.dataDecodeUpdate.connect(self.data_process_thread.put_data)
        self.data_process_thread.data_signal.connect(self.drawFrame.updateData)
        self.filterWidget.filter_update_signal.connect(self.data_process_thread.updateFilterParam)
        self.serial_read_thread.start()
        self.data_process_thread.start()

    def btn_stop_clicked(self):
        self.serial_read_thread.del_thread()
        self.data_process_thread.del_thread()

    def btn_filter_clicked(self):
        super(mainWin, self).btn_filter_clicked()
        try:
            self.data_process_thread.isFilter = True if self.btn_filter.text() == "滤波器-ON" else False
        except:
            ...

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = mainWin()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
