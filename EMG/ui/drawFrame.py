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
from ui.canvasTab import Ui_canvasTab
import utils.globalParams as glo
from matplotlib.lines import Line2D
import pyqtgraph as pg
from pyqtgraph import GraphicsWidget, AxisItem

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
            if not glo.history2.empty():
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

# 绘制 频谱图
class FFTCanvas(pg.PlotWidget):

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        # self.curve1 = self.plot(np.array([1, 2, 3]), np.array([1, 2, 3]), pen='r')
        # self.curve2maximum recursion depth exceeded = self.plot([0], [0], pen='b')
        self.initData()
        ...

    def initData(self):
        # self.getPlotItem().addLegend(offset=(0, 10))
        self.curve1 = self.plot(pen='r', name='CH 1')
        self.curve2 = self.plot(pen='b', name='CH 2')
        self.setRange(xRange=[0, 100], yRange=[0, 100])

    def updateFFT(self, xdata, ydata):
        self.curve1.setData(xdata[0], ydata[0])
        self.curve2.setData(xdata[1], ydata[1])

class MyPlotCanvas(pg.PlotWidget):
    XMAX = 32000
    xdata = np.array([])
    ydata = np.array([])
    XDIS = 16000

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initData()

    def initData(self):
        # 设置坐标轴Label
        self.setLabel('left', 'Amplitude(uV)')
        self.setLabel('bottom', 'Time(s)')
        self.getPlotItem().getAxis('bottom').enableAutoSIPrefix(False)
        self.getPlotItem().getAxis('bottom').setScale(1 / glo.sample_rate)  # 单位放缩: 1s = 1 / 采样率
        self.getPlotItem().getAxis('bottom').setTickSpacing(1, 0.5)
        self.getPlotItem().getAxis('left').enableAutoSIPrefix(False)
        self.getPlotItem().getAxis('left').setScale(1) # / 1_000_000)  # 单位放缩: 1μV
        self.getPlotItem().getAxis('left').setStyle(autoReduceTextSpace=True)
        self.xdata = np.arange(0, self.XMAX, 1)
        self.ydata = np.zeros(self.XMAX)
        self.curve = self.plot(self.xdata, self.ydata, pen='k')
        self.curve.setPos(0, 0)
    
    def zoomReset(self):
        self.enableAutoRange()

class drawTabFrame(QFrame, Ui_canvasTab):
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        # self.setupUi(self)
        try:
            self.ui = uic.loadUi('ui/canvasTab.ui', self)
        except:
            self.ui = uic.loadUi('canvasTab.ui', self)
        self.tabCanvasList = []
        self.findNum = 0
        self.initUI()
        # self.initTimer()

    def initUI(self):
        self.buttonFrame.setVisible(False)
        pg.setConfigOption('foreground', 'k')
        for i in range(3):
            tabCanvas = MyPlotCanvas()
            tabCanvas.getPlotItem().setTitle(' ')
            self.plotLayout.addWidget(tabCanvas)
            self.tabCanvasList.append(tabCanvas)

        self.btn_1.clicked.connect(self.btn_1_clicked)
        self.btn_2.clicked.connect(self.btn_2_clicked)
        self.btn_head.clicked.connect(self.btn_head_clicked)
        self.btn_tail.clicked.connect(self.btn_tail_clicked)
        self.btn_pre.clicked.connect(self.btn_pre_clicked)
        self.btn_next.clicked.connect(self.btn_next_clicked)
        self.et_page.returnPressed.connect(self.et_page_returnPressed)
        self.sb_page.valueChanged.connect(self.sb_page_valueChanged)
        self.btn_to.clicked.connect(self.btn_to_clicked)

    def initTimer(self):
        self.count = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.updateCanvas)
        self.timer.start(100)

    def updateCanvas(self):
        self.count += 1
        print("test:" + str(self.count))

    def btn_1_clicked(self):
        print('btn_1_clicked')
        ...

    def btn_2_clicked(self):
        print('btn_2_clicked')
        ...

    def btn_head_clicked(self):
        print('btn_head_clicked')
        ...

    def btn_tail_clicked(self):
        print('btn_tail_clicked')
        ...

    def btn_pre_clicked(self):
        print('btn_pre_clicked')
        ...

    def btn_next_clicked(self):
        print('btn_next_clicked')
        ...

    def et_page_returnPressed(self):
        print('et_page_returnPressed:', self.et_page.text())
        ...

    def sb_page_valueChanged(self):
        print('sb_page_valueChanged:', self.sb_page.value())
        ...

    def btn_to_clicked(self):
        print('btn_to_clicked: ', self.sb_page.text())
        ...
    
    def flush(self):
        ...

class drawFrameFile(QFrame, Ui_Form):    #, Ui_Form):
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

        self.canvas = MyPlotCanvas(self.mainWin)
        self.canvasLayout.addWidget(self.canvas)
        self.canvasTabFrame.setVisible(False)
        ...

    def drawFile(self):
        self.canvas.ydata = self.history.copy()
        if glo.isBaseline:
            self.canvas.ydata = detrend(self.canvas.ydata, type='linear')
            ...
        self.canvas.xdata = np.arange(0, self.history.size, 1)
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
        self.canvas.getPlotItem().getAxis('bottom').setScale(1 / glo.sample_rate)  # 单位放缩: 1s = 1 / 采样率


    def keyPressEvent(self, e) -> None:  # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.chart.zoomReset()

    def closeEvent(self, event=None) -> None:   # 关闭事件
        # self.canvas.close_event()
        # self.canvas.mythread.terminate()
        ...

class drawFrame(QFrame, Ui_Form):
    history = np.array([])  # 待处理数据部分的原始数据, 保持长度为当前采样率
    data_add = np.array([])  # 待处理数据部分长度，防止处理过程中数据堆积
    data_add_mutex = QMutex()   # 待处理数据互斥锁
    pos = 0 # 当前数据原点偏移位置
    data_tab = np.array([])  # 标记数据段数组
    data_tab_mutex = QMutex()   # 标记数据段互斥锁
    tab_flag = False    # 标记数据段标志
    test_flag = False    # 标记数据段测试标志
    Mo = 0

    
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
        self.btn_tab.clicked.connect(self.btn_tab_clicked)  # Tab按钮
        self.btn_test.clicked.connect(self.btn_test_clicked)    # 测试按钮

        pg.setConfigOption('background', 'w')   # 设置背景颜色：白色
        pg.setConfigOption('foreground', 'k')   # 设置前景颜色：黑色
        pg.setConfigOption('leftButtonPan', False)  # 更改鼠标左键为框选模式

        self.canvas = MyPlotCanvas(self.mainWin)    # 画布
        self.canvasLayout.addWidget(self.canvas)  # 添加画布到布局中
        
        self.canvasTab = drawTabFrame(self.mainWin) # 画布Tab
        self.canvasTabLayout.addWidget(self.canvasTab)  # 添加画布Tab到布局中
        self.canvasTabFrame.setVisible(False)    # 隐藏画布Tab

        self.processTimer = QTimer(self)
        self.processTimer.timeout.connect(self.processData) # 定时处理数据
        self.processTimer.start(50) # 50ms处理一次数据
        ...
    def btn_test_clicked(self): # 测试按钮点击事件
        if self.test_flag:  # 如果测试标志为True --> 关闭测试
            self.test_flag = False
            self.btn_test.setText('测试')
        else:
            self.test_flag = True
            self.btn_test.setText('停止')

    def btn_tab_clicked(self):  # 显示/隐藏Tab按钮点击事件
        if self.canvasTabFrame.isVisible():  # 如果画布Tab可见 --> 隐藏
            self.btn_tab.setText('∨显示')
            self.canvasTabFrame.setVisible(False)    # 隐藏画布Tab
            self.canvas.getPlotItem().getAxis('left').showLabel(True)  # 显示右侧坐标轴
            self.canvas.getPlotItem().getAxis('bottom').showLabel(True)  # 显示下方坐标轴
        else:   # 如果画布Tab不可见 --> 显示
            self.btn_tab.setText('∧隐藏')
            self.canvasTabFrame.setVisible(True)    # 隐藏画布Tab
            self.canvas.getPlotItem().getAxis('left').showLabel(False)  # 隐藏右侧坐标轴
            self.canvas.getPlotItem().getAxis('bottom').showLabel(False)  # 隐藏下方坐标轴

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
        self.canvas.curve.setPos(self.pos - self.canvas.XDIS, 0)
        print(self.canvas.curve.pos() / 8000)

        if max(abs(data)) > 6000 and not self.tab_flag and self.test_flag:
            print("标记数据段开始")
            self.tab_flag = True
            ...

        if self.tab_flag:   # 如果标记数据段 --> 添加标记数据段
            self.data_tab = np.append(self.data_tab, data)
            if self.data_tab.size > glo.sample_rate:
                self.tab_flag = False
                print("标记数据段结束")
                self.canvasTab.tabCanvasList[self.Mo].getPlotItem().clearPlots()  # 清空画布Tab
                self.canvasTab.tabCanvasList[self.Mo].addItem(pg.PlotCurveItem(np.arange(0, glo.sample_rate, 1), self.data_tab[-glo.sample_rate:], pen=pg.mkPen('k', width=1.5)))  # 添加画布Tab数据
                self.canvasTab.findNum += 1
                self.canvasTab.tabCanvasList[self.Mo].getPlotItem().setTitle('第'+str(self.canvasTab.findNum)+'个标记数据段')
                self.canvasTab.lb_all.setText('共 '+str(self.canvasTab.findNum))
                self.canvasTab.et_page.setText(str(self.pos))

                self.Mo = (self.Mo + 1) % 3
                self.data_tab = np.array([])    # 清空标记数据段

        # 更新绘图数据
        self.canvas.ydata[:-len_data] = self.canvas.ydata[len_data:]
        self.canvas.ydata[-len_data:] = data
        self.canvas.curve.setData(self.canvas.xdata[-self.canvas.XDIS:], self.canvas.ydata[-self.canvas.XDIS:])

        # 更新标签(最小值、最大值、均方根)
        self.lb_min.setText(str(np.round(min(self.canvas.ydata[-self.canvas.XDIS:]), 3)))
        self.lb_max.setText(str(np.round(max(self.canvas.ydata[-self.canvas.XDIS:]), 3)))
        self.lb_rms.setText(
            str(np.round(np.sqrt(np.mean(self.canvas.ydata[-self.canvas.XDIS:]**2)), 3)))
        ...

    def addData(self, data):    # 向待处理数据中添加测取数据
        # 待处理数据添加(互斥锁)
        self.data_add_mutex.lock()
        self.data_add = np.append(self.data_add, data)
        self.data_add_mutex.unlock()

    def updateYlim(self):   # 更新Y轴范围
        print("updateYlim")
        self.canvas.setRange(yRange=[-glo.YDIS, glo.YDIS])

    def updateXlim(self):  # 更新X轴范围    # TODO
        self.canvas.XDIS = glo.XDIS
        self.canvas.curve.setData(
            self.canvas.xdata[-self.canvas.XDIS:], self.canvas.ydata[-self.canvas.XDIS:])
        ...

    def keyPressEvent(self, e) -> None: # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.canvas.zoomReset()
    
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