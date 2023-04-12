import sys
import os
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog, QComboBox, QVBoxLayout, QAction, QToolButton, QFrame, QMenu, QWidget, QWidgetAction, QGroupBox, QCheckBox, QGridLayout, QTextEdit
from PyQt5.QtCore import Qt, QDateTime, pyqtSignal, QThread, QMutex, QTimer, QCoreApplication, QRect
from PyQt5 import uic
# 串口操作
import utils.serialUtil as serUtil
import utils.globalParams as glo
from ui.drawFrame import drawFrame, drawFrameFile, FFTCanvas, FFTThread
from ui.mainWindow import Ui_MainWindow
from ui.test import Ui_formtest as test_Form
import numpy as np

class testWidget(QWidget):
    def __init__(self) -> None:
        super().__init__()
        self.ui = uic.loadUi('ui/filter.ui', self)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    myMain = testWidget()
    myMain.show()
    sys.exit(app.exec_())
