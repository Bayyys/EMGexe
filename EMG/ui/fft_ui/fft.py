import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
from scipy.signal import sosfilt, detrend
from PyQt5.QtWidgets import QApplication
# utils
import pyqtgraph as pg

class FFTCanvas(pg.PlotWidget):
    """FFT 绘图 canvas"""
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initData()

    def initData(self):
        self.curve1 = self.plot(pen='r', name='CH 1')
        self.curve2 = self.plot(pen='b', name='CH 2')
        self.setRange(xRange=[0, 100], yRange=[0, 100])

    def updateFFT(self, xdata, ydata):
        self.curve1.setData(xdata[0], ydata[0])
        self.curve2.setData(xdata[1], ydata[1])

if __name__ == '__main__':    
    pg.setConfigOption('background', 'w')
    pg.setConfigOption('foreground', 'k') 
    pg.setConfigOption('leftButtonPan', False)
    # 程序界面
    app = QApplication(sys.argv)
    ex = FFTCanvas()
    ex.show()
    sys.exit(app.exec_())
    ...