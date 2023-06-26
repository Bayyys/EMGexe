import sys
sys.path.append('..')
import serial
import serial.tools.list_ports
from ui.ser import Ui_serDialog
from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5 import uic
import utils.globalParams as glo
from ui.filter import Ui_formtest

class filterWidget(QtWidgets.QWidget, Ui_formtest):
    def __init__(self) -> None:
        super().__init__()
        if glo.ui_flag:
            try:
                self.ui = uic.loadUi('filter.ui', self)
            except:
                self.ui = uic.loadUi('ui/filter.ui', self)
        else:
            self.setupUi(self)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    glo.__init__()
    filterWidget = filterWidget()
    filterWidget.show()
    sys.exit(app.exec_())