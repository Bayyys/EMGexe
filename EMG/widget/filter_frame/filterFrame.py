import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial.tools.list_ports
from PyQt6 import QtWidgets
# ui
from ui.filterSetting_ui.filter import Ui_formtest
# utils

class filterWidget(QtWidgets.QWidget, Ui_formtest):
    def __init__(self, parent) -> None:
        super().__init__()
        self.parent = parent
        self.initUI()
    
    def initUI(self):
        self.setupUi(self)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    filter = filterWidget(app)
    filter.show()
    sys.exit(app.exec())