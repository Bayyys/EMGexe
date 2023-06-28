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
    """实时绘图窗口
    
    Attributes:
    ----------------
        history: 待处理数据部分的原始数据, 保持长度为当前采样率.
        data_add: 待处理数据部分长度，防止处理过程中数据堆积
        data_add_mutex: 待处理数据互斥锁
        pos: 当前数据原点偏移位置
        data_tab: 标记数据段数组
        data_tab_mutex: 标记数据段互斥锁
        tab_flag: 标记数据段标志
        test_flag: 标记数据段测试标志
    """

    def __init__(self, parent=None):
        super(drawSingleCanvas, self).__init__(parent)
        self.initUI()
        self.initValues()

    def initUI(self):
        self.btn_tab.setVisible(False)  # 隐藏Tab按钮
        self.btn_identify.setVisible(False)  # 隐藏测试按钮
        self.canvasTabFrame.setVisible(False)  # 隐藏标记数据段窗口
        # 页面高度变化槽函数
        

    def initValues(self):
        # 变量初始化
        ...
    def keyPressEvent(self, e) -> None: # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.canvas.zoomReset()
        
    def resizeEvent(cls, a0: QWidget.resizeEvent) -> None:
        if cls.canvas.getPlotItem().height() < 200:
            cls.canvas.getPlotItem().showLabel('bottom', show=False)
            cls.canvas.getPlotItem().showLabel('left', show=False)
        else:
            cls.canvas.getPlotItem().showLabel('bottom', show=True)
            cls.canvas.getPlotItem().showLabel('left', show=True)
        return super().resizeEvent(a0)

    def closeEvent(self, event=None) -> None:   # 关闭事件
        # self.canvas.close_event()
        # self.canvas.mythread.terminate()
        ...
    
if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = drawSingleCanvas()
    win.show()
    sys.exit(app.exec())
