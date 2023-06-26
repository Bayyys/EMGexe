import sys
import os
import typing
from PyQt6 import QtCore
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QFileDialog, QWidgetAction
# ui
from ui.mainWindow import Ui_MainWindow
from widget.filter_frame.filterFrame import filterWidget

class MyWindow(QMainWindow, Ui_MainWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setupUi(self)  # 初始化UI
        # QComboBox
        self.cb_channel.clear() # 通道数
        self.cb_channel.addItems(["2", "32"])
        self.cb_channel.setCurrentText("32")
        self.cb_sample_rate.clear() # 采样率
        self.cb_sample_rate.addItems(["250", "500", "1000", "2000", "4000", "8000", "16000"])
        self.cb_sample_rate.setCurrentText("1000")
        self.cb_xdis.clear() # 时基s
        self.cb_xdis.addItems(["1", "2", "3", "4"])
        self.cb_xdis.setCurrentText("4")
        self.cb_ydis.clear() # 幅值uV
        self.cb_ydis.addItems(["20", "50", "100", "200", "500", "1000", "2000", "5000", "10000"])
        self.cb_ydis.setCurrentText("1000")
        # 文件路径初始化
        self.et_filePath.setText(os.getcwd()) # 文件路径
        # 滤波器设置控件
        self.filterWidget = filterWidget(self)
        act = QWidgetAction(self)
        act.setDefaultWidget(self.filterWidget)
        self.btn_filter.addAction(act)
        # 信号和槽
        self.btn_filePath.clicked.connect(self.btn_filePath_clicked) # 选择文件路径
    
    def btn_filePath_clicked(self):
        filePath = QFileDialog.getExistingDirectory(self, "选择文件路径", "./")
        if filePath:
            self.et_filePath.setText(filePath)

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = MyWindow()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
