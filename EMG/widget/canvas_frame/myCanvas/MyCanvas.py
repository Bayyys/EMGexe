import sys
import os
import typing
sys.path.append(os.getcwd()+"\\EMG")
import random
import numpy as np
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QFrame, QApplication
# ui
from ui.canvas_ui.myCanvas_ui.my_canvas import Ui_myCanvas
# utils
import pyqtgraph as pg

class MyPlotCanvas(pg.PlotWidget):
    '''绘图 canvas'''
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initValues()
        self.initChart()

    def initValues(self):
        self.rate = 1000
        self.XMAX = 4*self.rate   # x轴最大值
        self.xdata = np.array([])   # x轴数据
        self.ydata = np.array([])   # y轴数据
        self.XDIS = 4*self.rate   # x轴显示范围

    def initChart(self):
        # 设置坐标轴标签
        self.setLabel('left', 'Amplitude(uV)')
        self.setLabel('bottom', 'Time(s)')
        # 设置坐标轴范围及刻度
        self.getPlotItem().getAxis('bottom').enableAutoSIPrefix(False)  # 不自动缩放单位(横轴：时间)
        # self.getPlotItem().getAxis('bottom').setScale(1 / self.rate)  # 单位放缩: 1s = 1 / 采样率
        # self.getPlotItem().getAxis('bottom').setTickSpacing(1, 0.5) # 设置刻度间隔
        self.getPlotItem().getAxis('left').enableAutoSIPrefix(False)    # 不自动缩放单位(纵轴：幅值)
        # self.getPlotItem().getAxis('left').setScale(1) # / 1_000_000)  # 单位放缩: 1μV
        self.getPlotItem().getAxis('left').setStyle(autoReduceTextSpace=True)
        # 添加初始数据及设定范围和原点
        self.xdata = np.arange(0, self.XMAX, 1) # x轴数据
        self.ydata = np.zeros(self.XMAX)    # y轴数据
        self.curve = self.plotItem.plot(self.xdata, self.ydata, pen=pg.mkPen(color='k', width=1))     # 曲线
        # self.curve.setFftMode(True) # 设置为频域模式
        self.curve.setPos(0, 0) # 设置曲线的起始位置(0, 0)
        # self.useOpenGL(True)    # 使用OpenGL加速绘图
        self.setAntialiasing(True)  # 抗锯齿
    
    def updateChart(self):
        self.getPlotItem().getAxis('bottom').setScale(1 / self.rate)  # 单位放缩: 1s = 1 / 采样率
        self.xdata = np.arange(0, self.XMAX, 1) / self.rate # x轴数据
        self.ydata = np.zeros(self.XMAX)    # y轴数据
        self.curve.setData(self.xdata, self.ydata)     # 曲线
    
    def zoomReset(self):    # 重置缩放
        self.setYRange(-1000, 1000)
        self.enableAutoRange()
    
class MyCanvas(QFrame, Ui_myCanvas):
    """实时绘图窗口 模板类"""

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.num = 0
        self.initUI()

    def initUI(self):
        # 初始化UI
        self.setupUi(self)
        # 按键绑定
        self.btn_reset.clicked.connect(lambda: self.canvas.zoomReset()) # 重置按钮
        self.btn_close.clicked.connect(lambda: self.setVisible(False))  # 关闭按钮
        # 设置plotWidget样式
        pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
        pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
        pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式
        pg.setConfigOptions(antialias=True)
        # 添加画布
        self.canvas = MyPlotCanvas(self.mainWin)    # 画布
        self.canvasLayout.addWidget(self.canvas)  # 添加画布到布局中
        
    def updateData(self, data: typing.Any):
        # ydata = np.array(data[-self.canvas.XDIS*self.canvas.rate:]) # 取最后一段数据
        # xdata = np.arange(0, len(ydata)) / self.canvas.rate  # x轴数据: 0~4s
        self.canvas.curve.setData(data[-self.canvas.XDIS*self.canvas.rate:])
    
    def updateRate(self, rate: int=1000):
        self.canvas.getPlotItem().getAxis('bottom').setScale(1 / self.canvas.rate)
        self.canvas.rate = rate
        self.canvas.XMAX = 4*self.canvas.rate
        self.canvas.XDIS = 4*self.canvas.rate
        self.canvas.updateChart()
    
    def updateXdis(self, xdis: int=4):
        self.canvas.XDIS = xdis
    
    def updateYdis(self, ydis: int=1000):
        self.canvas.setYRange(-ydis, ydis)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MyCanvas()
    win.show()
    sys.exit(app.exec())