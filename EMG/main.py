import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow
from widget.main_mainWindow.mainWin import MyWindow

class mainWin(MyWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
    
    def initUI(self):
        ...

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = MyWindow()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
