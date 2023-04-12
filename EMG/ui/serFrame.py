import sys
sys.path.append('..')
import serial
import serial.tools.list_ports
from ui.ser import Ui_serDialog
from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5 import uic
import utils.globalParams as glo


class serDialog(QtWidgets.QDialog, Ui_serDialog):
    def __init__(self) -> None:
        super().__init__()
        if glo.ui_flag:
            try:
                self.ui = uic.loadUi('ser.ui', self)
            except:
                self.ui = uic.loadUi('ui/ser.ui', self)
        else:
            self.setupUi(self)
        self.moreFrame.setVisible(False)
        self.portListUpdate()
        self.btn_more.clicked.connect(self.btn_more_clicked)
        self.setAttribute(QtCore.Qt.WA_QuitOnClose, False)
    
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
    serDialog = serDialog()
    serDialog.show()
    sys.exit(app.exec_())