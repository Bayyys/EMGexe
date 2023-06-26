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
from classTestWidget import testWidget
import numpy as np


class MyMain(QMainWindow):

    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi('ui/testMain.ui', self)
        self.initUI()

    def initUI(self):
        self.wtest = QWidget(self)
        self.wtest.ui = uic.loadUi('ui/filter.ui', self.wtest)
        self.Menu = QMenu(self)
        act = QWidgetAction(self)
        act.setDefaultWidget(self.wtest)
        self.Menu.addAction(act)
        self.tb.setMenu(self.Menu)
        self.btn_1.clicked.connect(self.btn_1_clicked)
        self.sb.editingFinished.connect(self.sb_changed)
    
    def sb_changed(self):
        # self.cb.setCurrentIndex(self.cb.findText(str(self.sb.value())))
        self.findIndex(self.cb)
        self.findIndex(self.ck)
    
    def findIndex(self, event):
        # 判断控件类型
        if event.metaObject().className() == 'QComboBox':
            event.setCurrentIndex(event.findText(str(self.sb.value())))
        elif event.metaObject().className() == 'QCheckBox':
            event.setChecked(self.sb.value() > 3)
        
    
    def btn_1_clicked(self):
        if self.tb.isChecked():
            print('btn_1 clicked')
            self.et_test.append('btn_1 clicked')
            self.et_test.moveCursor(self.et_test.textCursor().End)
        else:
            print('btn_1 not clicked')
            self.et_test.clear()



if __name__ == '__main__':
    app = QApplication(sys.argv)
    myMain = MyMain()
    myMain.show()
    sys.exit(app.exec_())