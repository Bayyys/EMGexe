import sys
import os
from PyQt6 import QtGui
sys.path.append(os.getcwd()+"\\EMG")
import numpy as np
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QWidget
# ui
from widget.canvas_frame.myCanvas.MyCanvas import MyPlotCanvas
import pyqtgraph as pg

class fftWidget(pg.PlotWidget):
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initValues()
        self.initChart()

    def initValues(self):
        self.ydata = np.zeros(1000)     # y轴数据
        self.curve_list = []    # 曲线列表

    def initChart(self, channel:int=32):
        # 设置坐标轴标签
        self.setLabel('left', 'Amplitute / a.u.')
        self.setLabel('bottom', 'Frequence / Hz')
        self.getPlotItem().getAxis('left').setStyle(autoReduceTextSpace=True)
        self.getPlotItem().getAxis('bottom').setStyle(autoReduceTextSpace=True)
        # self.curve = self.plot(self.xdata, self.ydata, pen='k')     # 曲线
        # 绘制曲线channel条, 颜色不同
        for i in range(channel):
            # curve = self.plot(self.xdata, self.ydata, pen=pg.mkPen(color=(i, channel*1.3)))     # 曲线
            curve = self.plot(self.ydata, pen='k', width=1)     # 曲线
            self.curve_list.append(curve)
    
    def updateChart(self, para_list:list=[]):
        amp_list, fre_list = para_list
        for i in range(len(amp_list)):
            self.curve_list[i].setData(fre_list[i], amp_list[i])

    def zoomReset(self):    # 重置缩放
        self.enableAutoRange()

if __name__ == '__main__':
    pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
    pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
    pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式
    app = QApplication(sys.argv)
    win = fftWidget(app)
    win.show()
    sys.exit(app.exec())
