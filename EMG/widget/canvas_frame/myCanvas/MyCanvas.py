import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import random
import numpy as np
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QFrame, QApplication
# ui
from ui.canvas_ui.myCanvas_ui.my_canvas import Ui_myCanvas
# utils
import utils.globalParams as glo
import pyqtgraph as pg

class MyPlotCanvas(pg.PlotWidget):
    '''绘图 canvas
    
    Attributes:
    ----------------
        mainWin: 主窗口
        XMAX: x轴最大值
        xdata: x轴数据
        ydata: y轴数据
        XDIS: x轴显示范围
    '''
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initValues()
        self.initData()

    def initValues(self):
        self.XMAX = 4*4000   # x轴最大值
        self.xdata = np.array([])   # x轴数据
        self.ydata = np.array([])   # y轴数据
        self.XDIS = 4*4000   # x轴显示范围

    def initData(self):
        # 设置坐标轴标签
        self.setLabel('left', 'Amplitude(uV)')
        self.setLabel('bottom', 'Time(s)')
        # 设置坐标轴范围及刻度
        self.getPlotItem().getAxis('bottom').enableAutoSIPrefix(False)  # 不自动缩放单位(横轴：时间)
        self.getPlotItem().getAxis('bottom').setScale(1 / 4000)  # 单位放缩: 1s = 1 / 采样率
        self.getPlotItem().getAxis('bottom').setTickSpacing(1, 0.5) # 设置刻度间隔
        self.getPlotItem().getAxis('left').enableAutoSIPrefix(False)    # 不自动缩放单位(纵轴：幅值)
        self.getPlotItem().getAxis('left').setScale(1) # / 1_000_000)  # 单位放缩: 1μV
        self.getPlotItem().getAxis('left').setStyle(autoReduceTextSpace=True)
        # 添加初始数据及设定范围和原点
        self.xdata = np.arange(0, self.XMAX, 1) # x轴数据
        self.ydata = np.zeros(self.XMAX)    # y轴数据
        self.curve = self.plot(self.xdata, self.ydata, pen='k')     # 曲线
        self.curve.setPos(0, 0) # 设置曲线的起始位置(0, 0)
    
    def zoomReset(self):    # 重置缩放
        self.enableAutoRange()


class MyCanvas(QFrame, Ui_myCanvas):
    """实时绘图窗口 模板类"""

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.num = 0
        self.initMyUI()

    def initMyUI(self):
        # 初始化UI
        self.setupUi(self)
        # 按键绑定
        self.btn_reset.clicked.connect(lambda: self.canvas.zoomReset()) # 重置按钮
        self.btn_close.clicked.connect(lambda: self.setVisible(False))  # 关闭按钮
        # 设置plotWidget样式
        pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
        pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
        pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式
        # 添加画布
        self.canvas = MyPlotCanvas(self.mainWin)    # 画布
        self.canvasLayout.addWidget(self.canvas)  # 添加画布到布局中
        
    
    def updateYlim(self):   # 更新Y轴范围
        ''' 更新Y轴范围'''
        self.canvas.setRange(yRange=[-glo.YDIS, glo.YDIS])

    def updateXlim(self):  # 更新X轴范围
        ''' 更新X轴范围'''
        self.canvas.XDIS = glo.XDIS
        self.canvas.curve.setData(
            self.canvas.xdata[-self.canvas.XDIS:], self.canvas.ydata[-self.canvas.XDIS:])
    
    def updateData(self, data: list):
        self.canvas.curve.setData([random.random() for i in range(100)])

    def keyPressEvent(self, e) -> None: # 键盘事件
        if e.key() == Qt.Key.Key_R: # 重置缩放
            self.canvas.zoomReset()
    
    def closeEvent(self, event=None) -> None:   # 关闭事件
        ...

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MyCanvas()
    win.show()
    sys.exit(app.exec())