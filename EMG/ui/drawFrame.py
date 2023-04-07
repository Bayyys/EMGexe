import sys
sys.path.append("..")  # 将上级目录加入到搜索路径中
import time
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import sosfilt, detrend
from PyQt5.QtCore import Qt, QTimer, QThread, QMutex, pyqtSignal
from PyQt5.QtWidgets import QApplication, QSizePolicy, QFrame
from PyQt5 import uic
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from ui.draw import Ui_Form
import utils.globalParams as glo
from matplotlib.lines import Line2D
import pyqtgraph as pg

class FFTThread(QThread):
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
            # self.mutex.lock()
            # if len(self.data) > 0:
                # data = self.data
                # self.data = []
                # self.mutex.unlock()
                # data = np.array(data)
                # data = data[:, 1]
            # data = data.astype(np.float)
            if glo.history.shape[1] > glo.sample_rate:
                self.data1 = self.mainWin.chartFrameList[0].canvas.ydata[-4000:]
                self.data2 = self.mainWin.chartFrameList[1].canvas.ydata[-4000:]
                
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
                time_all = int(glo.history.shape[1] / glo.sample_rate)
                self.mainWin.lb_connect.setText('Time: ' + str(time_all) + 's')
            # else:
                # self.mutex.unlock()
            time.sleep(0.5)

# 绘制 频谱图
class FFTCanvas(FigureCanvas):
    def __init__(self, parent=None):
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlim(0, 100)
        self.ax.set_ylim(0, 100)
        self.line1 = Line2D([], [])
        self.line2 = Line2D([], [])
        self.line2.set_color('orange')
        self.ax.add_line(self.line1)
        self.ax.add_line(self.line2)
        self.fig.set_constrained_layout(True)   # 自动调整子图间距
        FigureCanvas.__init__(self, self.fig)
        self.setParent(parent)
        FigureCanvas.setSizePolicy(self, QSizePolicy.Expanding, QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)

    def updateFFT(self, xdata, ydata):
        self.line1.set_data(xdata[0], ydata[0])
        self.line2.set_data(xdata[1], ydata[1])
        self.draw()

class MyPlotCanvasFile(pg.PlotWidget):
    XMAX = 16000
    xdata = np.array([])
    ydata = np.array([])
    Ydis = 0

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initData()

    def initData(self):
        self.xdata = np.arange(0, self.XMAX/glo.sample_rate, 1/glo.sample_rate)
        self.ydata = np.zeros(self.XMAX)
        self.curve = self.plot(self.xdata, self.ydata, pen='k')
        self.curve.setPos(0, 0)
        self.setLabel('left', 'Amplitude', units='μV')
        self.setLabel('bottom', 'Time', units='s')
        # self.setLabels(bottom=('Time', 's'), left=('Amplitude', 'μV'))

    def zoomReset(self):
        self.autoRange()

    def close_event(self, event) -> None:
        try:
            self.timer.stop()
            # self.mythread.stop()
            self.mythread.terminate()
        except:
            ...

class drawFrameFile(QFrame):    #, Ui_Form):
    history = np.array([])  # 历史数据

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        # self.setupUi(self)
        try:
            self.ui = uic.loadUi('ui/draw.ui', self)
        except:
            self.ui = uic.loadUi('draw.ui', self)
        self.initUI()

    def initUI(self):
        self.btn_reset.clicked.connect(lambda: self.canvas.zoomReset())
        self.btn_close.clicked.connect(lambda: self.setVisible(False))

        self.canvas = MyPlotCanvasFile(self.mainWin)
        self.canvasLayout.addWidget(self.canvas)
        ...

    def drawFile(self):
        self.canvas.ydata = self.history.copy()
        if glo.isBaseline:
            self.canvas.ydata = detrend(self.canvas.ydata, type='linear')
            ...
        self.canvas.xdata = np.arange(0, self.history.size, 1) / glo.sample_rate
        print(self.canvas.xdata.shape)
        self.lb_max.setText(str(np.round(max(self.canvas.ydata), 2)))
        self.lb_min.setText(str(np.round(min(self.canvas.ydata), 2)))
        self.lb_rms.setText(str(np.round(np.sqrt(np.mean(self.canvas.ydata ** 2)), 2)))
        self.canvas.curve.setData(self.canvas.xdata, self.canvas.ydata)
    
    def drawFileAgain(self):
        data_process = self.history.copy()
        if glo.isBaseline:
            try:
                data_process = detrend(data_process, type='linear')
            except:
                ...
            data_process = detrend(data_process, type='constant')
        if glo.isLowPassFilter:
            data_process = sosfilt(glo.sos_low, data_process)
        if glo.isHighPassFilter:
            data_process = sosfilt(glo.sos_high, data_process)
        if glo.isNotchFilter:
            data_process = sosfilt(glo.sos_notch, data_process)
        if glo.isBandPassFilter:
            data_process = sosfilt(glo.sos_band, data_process)
        self.lb_max.setText(str(np.round(max(data_process), 2)))
        self.lb_min.setText(str(np.round(min(data_process), 2)))
        self.lb_rms.setText(str(np.round(np.sqrt(np.mean(data_process ** 2)), 2)))
        self.canvas.curve.setData(self.canvas.xdata, data_process)
    
    def updateYlim(self):   # 更新Y轴范围
        self.canvas.setYRange(-glo.YDIS, glo.YDIS)

    def updateXlim(self):  # 更新X轴范围
        ...

    def updateSampleRate(self):
        self.canvas.xdata = np.arange(0, self.history.size, 1) / glo.sample_rate
        print(self.canvas.xdata.shape)
        self.canvas.curve.setData(self.canvas.xdata, self.canvas.ydata)


    def keyPressEvent(self, e) -> None:  # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.chart.zoomReset()

    def closeEvent(self, event=None) -> None:   # 关闭事件
        # self.canvas.close_event()
        # self.canvas.mythread.terminate()
        ...

class MyPlotCanvas(pg.PlotWidget):
    XMAX = 16000
    Xdis = 1000
    xdata = np.array([])
    ydata = np.array([])

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initData()

    def initData(self):
        self.setLabel('left', 'Amplitude', units='V')
        self.setLabel('bottom', 'Time', units='s')
        self.xdata = np.arange(0, self.XMAX / glo.sample_rate, 1 / glo.sample_rate)
        self.ydata = np.zeros(self.XMAX)
        self.curve = self.plot(self.xdata, self.ydata, pen='k')
        self.curve.setPos(0, 0)
    
    def zoomReset(self):
        self.autoRange()

class drawFrame(QFrame, Ui_Form):
    history = np.array([])  # 待处理数据部分的原始数据, 保持长度为当前采样率
    data_add = np.array([])  # 待处理数据部分长度，防止处理过程中数据堆积
    data_add_mutex = QMutex()   # 待处理数据互斥锁
    pos = 0 # 当前数据原点偏移位置
    
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        # self.setupUi(self)
        try:
            self.ui = uic.loadUi('ui/draw.ui', self)
        except:
            self.ui = uic.loadUi('draw.ui', self)
        self.initUI()

    def initUI(self):
        self.btn_reset.clicked.connect(lambda: self.canvas.zoomReset()) # 重置按钮
        self.btn_close.clicked.connect(lambda: self.setVisible(False))  # 关闭按钮

        pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
        pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
        pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式

        self.canvas = MyPlotCanvas(self.mainWin)    # 画布
        self.plotWidget.addWidget(self.canvas)  # 添加画布到布局中

        self.processTimer = QTimer(self)
        self.processTimer.timeout.connect(self.processData) # 定时处理数据
        self.processTimer.start(50) # 50ms处理一次数据
        ...
    
    def processData(self):  # 处理数据 --> 定时器50ms调用一次
        # 待处理数据获取(互斥锁)
        self.data_add_mutex.lock()
        data = self.data_add
        if data.size == 0:
            self.data_add_mutex.unlock()
            return
        self.data_add = np.array([])    # 清空待处理数据
        self.data_add_mutex.unlock()

        # 数据处理
        len_data = len(data)    # 待处理数据长度
        self.history = np.append(self.history, data)[-glo.sample_rate:] # 更新历史数据
        if glo.isBaseline:
            data_filter = detrend(self.history.copy(), type='constant') # 基线移除
        else:
            data_filter = self.history.copy()
        process = data_filter
        if glo.isLowPassFilter:
            process = sosfilt(glo.sos_low, process)     # 低通滤波
        if glo.isHighPassFilter:
            process = sosfilt(glo.sos_high, process)    # 高通滤波
        if glo.isNotchFilter:
            process = sosfilt(glo.sos_notch, process)   # 陷波滤波
        if glo.isBandPassFilter:
            process = sosfilt(glo.sos_band, process)    # 带通滤波

        data = process[-len_data:]  # 待显示数据(长度为len_data)

        # 数据原点移动
        self.pos += len_data
        self.canvas.curve.setPos(self.pos, 0)

        # 更新绘图数据
        self.canvas.ydata[:-len_data] = self.canvas.ydata[len_data:]
        self.canvas.ydata[-len_data:] = data
        self.canvas.curve.setData(self.canvas.xdata, self.canvas.ydata)


        self.lb_min.setText(str(np.round(min(self.canvas.ydata[-500:]), 3)))
        self.lb_max.setText(str(np.round(max(self.canvas.ydata[-500:]), 3)))
        self.lb_rms.setText(
            str(np.round(np.sqrt(np.mean(self.canvas.ydata[-500:]**2)), 3)))
        ...

    def addData(self, data):    # 向待处理数据中添加测取数据
        # 待处理数据添加(互斥锁)
        self.data_add_mutex.lock()
        self.data_add = np.append(self.data_add, data)
        self.data_add_mutex.unlock()

    def updateYlim(self):   # 更新Y轴范围
        self.canvas.setYRange = (-glo.YDIS, glo.YDIS)

    def updateXlim(self):  # 更新X轴范围    # TODO
        ...

    def keyPressEvent(self, e) -> None: # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.chart.zoomReset()
    
    def closeEvent(self, event=None) -> None:   # 关闭事件
        # self.canvas.close_event()
        # self.canvas.mythread.terminate()
        ...

if __name__ == '__main__':
    # glo.__init__()
    # glo.initFilterParams()
    data_o = np.loadtxt("txt.txt")
    data1 = data_o[::2]
    data2 = data_o[1::2]
    # data = np.vstack((data1, data2))
    # np.savetxt("data.txt", data)
    # print(data)
    # print(data_o.shape, data1.shape, data2.shape)
    # print(data_o)
    # print(data.shape)
    # np.savetxt("txt1.txt", data1)
    # np.savetxt("txt2.txt", data2)
    # for i in range(0, len(data1)):
        # data1[:i+1] = data1[:i+1] - np.mean(data2[:i+1])

    # data3 = detrend(data1)
    # plt.plot(np.arange(0, len(data3) / 8000, 1 / 8000), data3)
    # plt.show()

    app = QApplication(sys.argv)
    pg.setConfigOption('background', 'w')
    pg.setConfigOption('foreground', 'k') 
    pg.setConfigOption('leftButtonPan', False)
    ex = drawFrame()
    # data2 = sosfilt(glo.sos_high, data3)
    # plt.plot(np.arange(0, len(data2) / 8000, 1 / 8000), data2)
    # plt.show()
    # data4 = sosfilt(glo.sos_notch, data2)
    # plt.plot(np.arange(0, len(data4) / 8000, 1 / 8000), data4)
    # plt.show()
    # data = sosfilt(glo.sos_band, data4)
    # plt.plot(np.arange(0, len(data) / 8000, 1 / 8000), data)
    # plt.show()
    # data = data1[2000:]
    # ex.canvas.ydata = data
    # ymax = np.max(data)
    # ymin = np.min(data)
    # ex.canvas.xdata = np.arange(0, len(data) / 8000, 1 / 8000)
    # ex.canvas.line.set_data(ex.canvas.xdata, ex.canvas.ydata)
    # ex.canvas.ax.set_xlim(0, np.max(ex.canvas.xdata) + 1)
    # ex.canvas.ax.set_ylim(ymin, ymax)
    # ex.canvas.draw()
    # print(data[-100:])
    ex.show()
    sys.exit(app.exec_())
    ...