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
        self.resizeEvent(None)

    def initUI(self):
        super().initUI()
        self.btn_tab.setVisible(False)  # 隐藏Tab按钮
        self.btn_identify.setVisible(False)  # 隐藏测试按钮
        self.canvasTabFrame.setVisible(False)  # 隐藏标记数据段窗口
        self.lb_max.setVisible(False)  # 隐藏最大值标签
        self.lb_maxInfo.setVisible(False)  # 隐藏最大值信息标签
        self.lb_max_unit.setVisible(False)  # 隐藏最大值单位标签
        self.lb_min.setVisible(False)  # 隐藏最小值标签
        self.lb_minInfo.setVisible(False)  # 隐藏最小值信息标签
        self.lb_min_unit.setVisible(False)  # 隐藏最小值单位标签
        self.lb_rms.setVisible(False)  # 隐藏均方根标签
        self.lb_rmsInfo.setVisible(False)  # 隐藏均方根信息标签
        self.lb_rms_unit.setVisible(False)  # 隐藏均方根单位标签

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
