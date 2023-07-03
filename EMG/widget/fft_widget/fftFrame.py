import sys
import os
from PyQt6 import QtGui
sys.path.append(os.getcwd()+"\\EMG")
import numpy as np
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QGridLayout
# ui
from widget.canvas_frame.myCanvas.MyCanvas import MyPlotCanvas
import pyqtgraph as pg
from widget.fft_widget.fftWidget import fftPlot


class fftFrame(QWidget):
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initValues()
        self.initChart()
        self.initUI()
    
    def initValues(self):
        self.chartNum = 32
        self.chart_list:fftPlot = []
        self.rate = 1000
        

    def initChart(self):
        for i in range(self.chartNum):
            chart = fftPlot(self)
            # fft曲线
            chart.curve.setPen(pg.mkPen(color=(i, self.chartNum*1.3)))
            chart.getPlotItem().setTitle("Channel"+str(i))
            self.chart_list.append(chart)
    
    def initUI(self):
        self.gl = QGridLayout(self)
        self.gl.setContentsMargins(0, 0, 0, 0)
        for i in range(self.chartNum):
            # self.gl.addWidget(self.chart_list[i], i%8, i//8)
            self.gl.addWidget(self.chart_list[i], i//8, i%8)
        self.setLayout(self.gl)
        self.setContentsMargins(0, 0, 0, 0)

    def updateRate(self, rate: str|int = 1000):
        self.rate = int(rate)
        for i in range(self.chartNum):
            self.chart_list[i].getPlotItem().getAxis('bottom').setScale(self.rate)
    
    def updateChart(self, para_list:list=[]):   # Wait
        amp_list, fre_list = para_list
        for i in range(len(amp_list)):
            self.chart_list[i].curve.setData(fre_list[i], amp_list[i])

    def update_chart(self, data_lsit:list=[]):
        for i in range(len(data_lsit)):
            self.chart_list[i].curve.setData(data_lsit[i][-self.rate*2:])

    def cb_fft_y_currentIndexChanged(self, x: int=200):
        for i in range(self.chartNum):
            self.chart_list[i].setRange(xRange=[0, x])

    def zoomReset(self):    # 重置缩放
        for i in range(self.chartNum):
            self.chart_list[i].zoomReset()

if __name__ == '__main__':
    pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
    pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
    pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式
    app = QApplication(sys.argv)
    win = fftFrame(app)
    win.show()
    sys.exit(app.exec())
