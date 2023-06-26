import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial
import serial.tools.list_ports
from serial_util_test_ui import Ui_serialUtilTestWin
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow
from PyQt6 import QtWidgets
from utils.getCom import getCom
from utils.serialRead import serialRead
import utils.serialUtils as serialUtils

class serialUtilTestWidget(QMainWindow, Ui_serialUtilTestWin):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
        self.initValues()
    
    def initUI(self):
        self.setupUi(self)  # 初始化UI
        self.cb_bps.addItems(["9600", "115200", "4608000"]) # 波特率
        self.cb_bps.setCurrentIndex(2)
        self.cb_channel.addItems(["2", "32"])
        self.cb_rate.addItems(["1000", "8000"])
        self.serialUtil_getCom_Test()
        self.btn_filter.clicked.connect(self.portChanged) # 过滤串口号
        self.btn_connect.clicked.connect(self.serialUtil_serialOpen_Test) # 连接串口号
        self.btn_disconnect.clicked.connect(self.serialUtil_serialClose_Test) # 断开串口号
        self.btn_start.clicked.connect(self.btn_start_clicked) # 开始过滤
        self.btn_pause.clicked.connect(self.btn_pause_clicked) # 停止过滤
    
    def initValues(self):
        self.serial = None
    
    def serialUtil_getCom_Test(self):
        self.getComThread = getCom(self.cb_port)
        self.getComThread.getCom_portChanged.connect(self.portChanged)
        self.getComThread.start()
    
    def portChanged(self, exist: bool=True, port_list: list=[]):
        self.cb_port.clear()
        for port in port_list:
            self.cb_port.addItem(str(port))
        if not exist:
            msg_box = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Icon.Warning, "警告", "当前串口断开!")
            msg_box.exec()
    
    def serialUtil_serialOpen_Test(self):
        self.serial = serialUtils.serialOpen(self.cb_port.currentText(), self.cb_bps.currentText())
        if self.serial:
            QtWidgets.QMessageBox.information(self, "提示", "串口打开成功!")
        else:
            QtWidgets.QMessageBox.warning(self, "警告", "串口打开失败!")

    def serialUtil_serialClose_Test(self):
        if serialUtils.serialClose(self.serial):
            QtWidgets.QMessageBox.information(self, "提示", "串口关闭成功!")
        else:
            QtWidgets.QMessageBox.warning(self, "警告", "串口关闭失败!")

    def filterPort(self):   # 过滤规则： # TODO
        msg_box = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Icon.Information, "提示", "过滤成功!")
        msg_box.exec()
    
    def btn_start_clicked(self):
        print("开始打印")
        if self.serial is None:
            print("串口不存在！")
            return
        serialUtils.serialWrite(self.serial, "start", channel=self.cb_channel.currentText(), sample_rate=self.cb_rate.currentText())
        self.serialReadThread = serialRead(self, self.serial, self.cb_channel.currentText())
        self.serialReadThread.dataUpdate.connect(self.et_original_update)
        self.serialReadThread.dataDecodeUpdate.connect(self.et_decode_update)
        self.serialReadThread.start()
    
    def et_original_update(self, data: bytes=b''):
        self.et_original.append(str(data))
    
    def et_decode_update(self, data: dict={}):
        self.et_decode.append(str(data))

    def btn_pause_clicked(self):
        print("停止打印")
        self.serialReadThread.__del__()
        ...

    def close(self) -> bool:
        self.getComThread.__del__()
        return super().close()

if __name__ == '__main__':
    print(__file__)
    app = QApplication(sys.argv)
    win = serialUtilTestWidget()
    win.show()
    sys.exit(app.exec())