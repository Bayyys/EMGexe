import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import time
import numpy as np
from scipy.signal import sosfilt, detrend    # type: ignore
from PyQt6.QtCore import QThread, QMutex, pyqtSignal
from PyQt6.QtWidgets import QApplication, QPushButton
import pyqtgraph as pg
# ui
from ui.fft_ui.fft import FFTCanvas
# utils
import utils.globalParams as glo

class FFTThread(QThread):
    '''FFT线程
    
    signal:
    ----------------
        fftSignal: 频谱图信号
    '''
    fftSignal = pyqtSignal(np.ndarray, np.ndarray)

    def __init__(self, mainWin):
        super().__init__()
        self.mainWin = mainWin
        self.mutex = QMutex()
        self.data1 = np.array([])
        self.data2 = np.array([])
        self.xdata1 = np.array([])
        self.xdata2 = np.array([])
        self.ydata1 = np.array([])
        self.ydata2 = np.array([])

    def run(self):
        while(glo.connected):
            if not glo.history.empty():
                # self.xdata = self.mainWin.chartFrameList[0].canvas.xdata[-4000:]
                # self.ydata1 = self.mainWin.chartFrameList[0].canvas.ydata[-4000:]
                # self.ydata2 = self.mainWin.chartFrameList[1].canvas.ydata[-4000:]
                self.data1 = self.mainWin.chartFrameList[0].canvas.ydata[-4000:]
                self.data2 = self.mainWin.chartFrameList[1].canvas.ydata[-4000:]
                if self.data1.shape[0] < 4000:
                    continue
                
                self.data1 = self.data1 - np.mean(self.data1)
                self.data1 = self.data1 * np.hamming(len(self.data1))
                self.data1 = np.abs(np.fft.fft(self.data1))
                self.data1 = self.data1[0:int(len(self.data1) / 2)]
                self.data1 = self.data1 / max(self.data1) if max(self.data1) != 0 else np.arange(len(self.data1))
                self.data1 = self.data1* 100
                self.xdata1 = np.linspace(0, glo.sample_rate / 2, len(self.data1))
                self.ydata1 = self.data1

                self.data2 = self.data2 - np.mean(self.data2)
                self.data2 = self.data2 * np.hamming(len(self.data2))
                self.data2 = np.abs(np.fft.fft(self.data2))
                self.data2 = self.data2[0:int(len(self.data2) / 2)]
                self.data2 = self.data2 / max(self.data2) if max(self.data2) != 0 else np.arange(len(self.data2))
                self.data2 = self.data2* 100
                self.xdata2 = np.linspace(0, glo.sample_rate / 2, len(self.data2))
                self.ydata2 = self.data2
                xdata = np.array([self.xdata1, self.xdata2])
                ydata = np.array([self.ydata1, self.ydata2])
                self.fftSignal.emit(xdata, ydata)
                # time_all = int(glo.history.shape[1] / glo.sample_rate)
                # self.mainWin.lb_connect.setText('Time: ' + str(time_all) + 's')
            # else:
                # self.mutex.unlock()
            time.sleep(0.05)

class FFTWidget(FFTCanvas):
    '''FFT 绘图 canvas'''
    def __init__(self, parent=None):
        super(FFTWidget, self).__init__(parent)

if __name__ == '__main__':    
    glo.__init__()
    pg.setConfigOption('background', 'w')
    pg.setConfigOption('foreground', 'k') 
    pg.setConfigOption('leftButtonPan', False)
    # 程序界面
    app = QApplication(sys.argv)
    ex = FFTWidget()
    ex.show()
    sys.exit(app.exec_())
    ...