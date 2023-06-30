import sys
import os
from PyQt6 import QtGui
sys.path.append(os.getcwd()+"\\EMG")
import numpy as np
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QWidget
# ui
from widget.canvas_frame.myCanvas.MyCanvas import MyCanvas

class drawSingleCanvas(MyCanvas):
    """实时绘图窗口"""

    def __init__(self, parent=None):
        super().__init__(parent)
        self.initValues()

    def initUI(self):
        super().initUI()
        self.btn_tab.setVisible(False)  # 隐藏Tab按钮
        self.btn_identify.setVisible(False)  # 隐藏测试按钮
        self.canvasTabFrame.setVisible(False)  # 隐藏标记数据段窗口

    def initValues(self):
        # 变量初始化
        ...

    def keyPressEvent(self, e) -> None: # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.canvas.zoomReset()
        
    def resizeEvent(self, a0: QWidget.resizeEvent) -> None:
        if self.canvas.getPlotItem().height() < 200:
            self.canvas.getPlotItem().showLabel('bottom', show=False)
            self.canvas.getPlotItem().showLabel('left', show=False)
        else:
            self.canvas.getPlotItem().showLabel('bottom', show=True)
            self.canvas.getPlotItem().showLabel('left', show=True)
        return super().resizeEvent(a0)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = drawSingleCanvas()
    win.show()
    sys.exit(app.exec())
