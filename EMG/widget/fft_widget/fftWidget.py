import sys
import os
from PyQt6 import QtGui
sys.path.append(os.getcwd()+"\\EMG")
import numpy as np
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout
# ui
from widget.canvas_frame.myCanvas.MyCanvas import MyPlotCanvas
import pyqtgraph as pg


class fftPlot(pg.PlotWidget):
    """fft图像显示 Canvas"""
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initValues()
        self.initChart()
    
    def initValues(self):
        self.ydata = np.zeros(1000)     # y轴数据
        self.rate = 1000
        self.chartNum = 32
        self.curve = None
        self.curve_list = []    # 曲线列表

    def initChart(self):
        # 设置坐标轴标签
        self.setLabel('left', 'Amplitute/a.u.')
        self.setLabel('bottom', 'Frequence/Hz')
        self.getPlotItem().setDownsampling(mode='peak')
        self.getPlotItem().getAxis('left').setStyle(autoReduceTextSpace=True)
        self.getPlotItem().getAxis('bottom').setStyle(autoReduceTextSpace=True)
        self.getPlotItem().getAxis('bottom').setScale(self.rate)
        self.curve = self.plotItem.plot(self.ydata, pen=pg.mkPen(color=(0, self.chartNum*1.3)), width=1, name="Channel0")
        self.setMouseEnabled(x=True, y=False)   # 禁止y轴缩放

class fftWidget(QWidget):
    """fft图像显示界面"""
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initValues()
        self.initChart()
    
    def initValues(self):
        self.chartNum = 32
        self.rate = 1000
        self.chart = fftPlot(self)
        self.chart.getPlotItem().clearPlots()
        self.vl = QVBoxLayout(self)
        self.vl.setContentsMargins(0, 0, 0, 0)
        self.vl.addWidget(self.chart)
        self.setLayout(self.vl)
        self.setContentsMargins(0, 0, 0, 0)

    def initChart(self):
        """初始化fft图表"""
        for i in range(self.chartNum):
            curve = self.chart.plotItem.plot(self.chart.ydata, pen=pg.mkPen(color=(i, self.chartNum*1.3)), width=1, name="Channel"+str(i))
            curve.setFftMode(True)
            self.chart.curve_list.append(curve)

    def updateRate(self, rate: str|int = 1000):
        """
        更新采样率

        Attributes:
        -----------
            rate: str|int
        """
        self.rate = int(rate)
        self.chart.getPlotItem().getAxis('bottom').setScale(self.rate)
    
    def updateChart(self, chartNum: int=32):
        """
        更新图表
        
        根据通道数更新图表

        Attributes:
        -----------
            chartNum: 图表数量
        """
        self.chartNum = chartNum
        for i in range(self.chartNum):
            self.chart.curve_list[i].setData(self.chart.ydata)
            self.chart.curve_list[i].setPen(pg.mkPen(color=(i, self.chartNum*1.3)))
            self.chart.curve_list[i].setFftMode(True)
        for i in range(self.chartNum, len(self.chart.curve_list)):
            self.chart.getPlotItem().removeItem(self.chart.curve_list[i])


    def updateData(self, data_lsit:list=[]):
        for i in range(len(data_lsit)):
            self.chart.curve_list[i].setData(data_lsit[i][-self.rate*2:])

    def cb_fft_y_currentIndexChanged(self, x: int=200):
        self.chart.setRange(xRange=[0, x/self.rate])

    def zoomReset(self):    # 重置缩放
        self.chart.enableAutoRange()

if __name__ == '__main__':
    pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
    pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
    pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式
    app = QApplication(sys.argv)
    win = fftWidget(app)
    win.show()
    sys.exit(app.exec())
