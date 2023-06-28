import sys
import os
import typing
sys.path.append(os.getcwd()+"\\EMG")
import serial
import serial.tools.list_ports
from PyQt6 import QtWidgets, QtCore, QtGui
from PyQt6 import uic
from PyQt6.QtWidgets import QMainWindow, QWidget

# ui
from widget.serial_dialog.serialDialog import serialDialog
# utils
import utils.globalParams as glo

class mainWin(QMainWindow):
    def __init__(self,) -> None:
        super().__init__()
        self.initUI()
    
    def initUI(self):
        # ui
        self.vl = QtWidgets.QVBoxLayout()
        self.btn_setting = QtWidgets.QPushButton('设置')
        self.et_setting = QtWidgets.QTextEdit(self)
        self.vl.addWidget(self.btn_setting)
        self.vl.addWidget(self.et_setting)
        self.widget = QWidget()
        self.widget.setLayout(self.vl)
        self.setCentralWidget(self.widget)
        # 信号和槽
        self.btn_setting.clicked.connect(self.btn_setting_clicked)
        self.serialDialog = serialDialog()
    
    def btn_setting_clicked(self):
        self.serialDialog.show()
        if self.serialDialog.exec() == QtWidgets.QDialog.DialogCode.Accepted:
            self.serialDialog_btn_ok_clicked()
    
    def serialDialog_btn_ok_clicked(self):
        self.et_setting.append(str(self.serialDialog.getSerParams()))
        self.serialDialog.close()

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = mainWin()
    win.show()
    sys.exit(app.exec())
