import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial
import serial.tools.list_ports
from PyQt6 import QtWidgets, QtCore, QtGui
from PyQt6 import uic
# ui
from ui.serial_ui.serial import Ui_serialDialog
# utils
import utils.globalParams as glo


class serialDialog(QtWidgets.QDialog, Ui_serialDialog):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
    
    def initUI(self):
        # ui
        self.setupUi(self)
        self.moreFrame.setVisible(False)
        self.portListUpdate()
        # 信号和槽
        self.btn_more.clicked.connect(self.btn_more_clicked)
        # 设置窗口属性
        self.setAttribute(QtCore.Qt.WidgetAttribute.WA_QuitOnClose, False)  # 使得关闭窗口时不退出程序

    
    def portListUpdate(self):
        port_list = list(serial.tools.list_ports.comports())
        self.box_port.addItems([port_list[i][0] + ' ' + port_list[i][1]
                              for i in range(len(port_list))])

    def btn_more_clicked(self):
        if self.moreFrame.isVisible():
            self.moreFrame.setVisible(False)
            self.btn_more.setText('更多参数∨')
        else:
            self.moreFrame.setVisible(True)
            self.btn_more.setText('更多参数∧')
    
    def getSerParams(self):
        return (self.box_port.currentText(),    # 串口号
                self.box_baudrate.currentText(),  # 波特率
                self.box_bytesize.currentText(),   # 数据位
                self.box_parity.currentText(),    # 数据校验位
                self.box_stopbits.currentText(),   # 数据停止位
                self.box_timeout.currentText(),    # 写超时
                self.box_control.currentText(),    # 控制位
                self.box_write_timeout.currentText(),    # 写超时
                self.box_inter_byte_timeout.currentText(),    # 字节间隔超时
                self.box_exclusive.currentText())    # 独占模式)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    glo.__init__()
    win = serialDialog()
    win.show()
    sys.exit(app.exec())