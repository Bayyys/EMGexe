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
import utils.serialUtils as serialUtils

class mainWin(MyWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI_mainWin()
        self.initValues_mainWin()
    
    def initUI_mainWin(self):
        self.drawFrame = drawFrame()
        self.chart_frame.layout().addWidget(self.drawFrame)
        self.cb_channel.currentTextChanged.connect(self.cb_channel_currentTextChanged)
        self.btn_connect.clicked.connect(self.btn_connect_clicked)
        self.btn_disconnect.clicked.connect(self.btn_disconnect_clicked)
        self.btn_start.clicked.connect(self.btn_start_clicked)
        self.btn_stop.clicked.connect(self.btn_stop_clicked)
    
    def initValues_mainWin(self):
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
        if serialUtils.serialClose(self.ser):
            print("串口关闭成功!")
        else:
            print("串口关闭失败!")
    
    def btn_start_clicked(self):
        if not serialUtils.serialIsOpen(self.ser):
            print("串口未打开!")
            return
        serialUtils.serialWrite(self.ser, state='start', connect='usb', sample_rate=self.cb_rate.currentText(), channel=self.cb_channel.currentText())
        self.serialReadThread = serialRead(self, self.ser, self.cb_channel.currentText())
        # self.serialReadThread.dataUpdate.connect(self.drawFrame.updateData)
        self.serialReadThread.dataDecodeUpdate.connect(self.drawFrame.updateDate)
        self.serialReadThread.start()
    
    def test(self, data):
        print(data)
    
    def btn_stop_clicked(self):
        self.serialReadThread.__del__()
        self.serialReadThread = None

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = mainWin()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
