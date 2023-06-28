import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import time
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter, lfilter, freqz, filtfilt, detrend, sosfilt
from PyQt6.QtCore import Qt, QTimer, QThread, QMutex, pyqtSignal
from PyQt6.QtWidgets import QApplication, QSizePolicy, QFrame, QPushButton
from PyQt6 import uic
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
# ui
from ui.canvas_ui.canvas import Ui_canvas
from ui.canvas_ui.canvasTab_ui.canvasTab import Ui_canvasTab
# utils
import utils.globalParams as glo
from matplotlib.lines import Line2D
import pyqtgraph as pg
from pyqtgraph import GraphicsWidget, AxisItem

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

class FFTCanvas(pg.PlotWidget):
    '''FFT 绘图 canvas'''
    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        self.initData()
        ...

    def initData(self):
        self.curve1 = self.plot(pen='r', name='CH 1')
        self.curve2 = self.plot(pen='b', name='CH 2')
        self.setRange(xRange=[0, 100], yRange=[0, 100])

    def updateFFT(self, xdata, ydata):
        self.curve1.setData(xdata[0], ydata[0])
        self.curve2.setData(xdata[1], ydata[1])

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
        self.XMAX = 4*glo.sample_rate   # x轴最大值
        self.xdata = np.array([])   # x轴数据
        self.ydata = np.array([])   # y轴数据
        self.XDIS = 4*glo.sample_rate   # x轴显示范围

    def initData(self):
        # 设置坐标轴标签
        self.setLabel('left', 'Amplitude(uV)')
        self.setLabel('bottom', 'Time(s)')
        # 设置坐标轴范围及刻度
        self.getPlotItem().getAxis('bottom').enableAutoSIPrefix(False)  # 不自动缩放单位(横轴：时间)
        self.getPlotItem().getAxis('bottom').setScale(1 / glo.sample_rate)  # 单位放缩: 1s = 1 / 采样率
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

class MyCanvas(QFrame, Ui_canvas):
    """实时绘图窗口 模板类"""

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
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

    def keyPressEvent(self, e) -> None: # 键盘事件
        if e.key() == Qt.Key.Key_R: # 重置缩放
            self.canvas.zoomReset()
    
    def closeEvent(self, event=None) -> None:   # 关闭事件
        ...

class drawTabFrame(QFrame, Ui_canvasTab):
    '''标记数据段绘图
    
    Attributes:
    ----------------
        tabCanvasList: 用于存储tabCanvas的列表(三维)
        findNum: 记录标记数据段的个数
        fromNum: 记录标记数据段的绘图起始位置
        toNum: 记录标记数据段的绘图结束位置
        fresh_state: 记录是否刷新tabCanvas的状态
        arrayLen: 用于存储tab数据的长度(实时)
        tabDataList: 用于存储tab数据的列表(二维 arrayLen * sample_rate)
        data_tab_point: # 存储标记数据段的坐标点(结束记录后存储)
    '''

    def __init__(self, parent=None):
        super().__init__()
        self.mainWin = parent
        if glo.ui_flag:
            try:
                self.ui = uic.loadUi('ui/canvasTab.ui', self)
            except:
                self.ui = uic.loadUi('canvasTab.ui', self)
        else:
            self.setupUi(self)
        self.tabCanvasList = [] # 用于存储tabCanvas的列表(三维)
        self.findNum = 0    # 记录标记数据段的个数
        self.fromNum = 1    # 记录标记数据段的绘图起始位置
        self.toNum = 3    # 记录标记数据段的绘图结束位置
        self.fresh_state = True # 记录是否刷新tabCanvas的状态
        self.arrayLen = 50  # 用于存储tab数据的长度(实时)
        self.tabDataList = np.zeros((self.arrayLen, glo.sample_rate))   # 用于存储tab数据的列表(二维 arrayLen * sample_rate)
        self.data_tab_point = np.array([])  # 存储标记数据段的坐标点(结束记录后存储)
        self.initUI()

    def initUI(self):
        pg.setConfigOption('foreground', 'k')   # 设置前景色(绘图折线笔刷颜色) - 黑色

        # 设置tabCanvas(三维)
        for i in range(3):
            tabCanvas = MyPlotCanvas()
            tabCanvas.getPlotItem().setTitle(' ')
            self.plotLayout2.addWidget(tabCanvas)
            self.tabCanvasList.append(tabCanvas)

        self.btn_head.clicked.connect(self.btn_head_clicked)    # 头部节点
        self.btn_tail.clicked.connect(self.btn_tail_clicked)    # 尾部节点
        self.btn_pre.clicked.connect(self.btn_pre_clicked)  # 上一页
        self.btn_next.clicked.connect(self.btn_next_clicked)    # 下一页
        # self.et_page.returnPressed.connect(self.et_page_returnPressed)  # 跳转到指定页_键入
        self.btn_to.clicked.connect(self.btn_to_clicked)    # 跳转到指定页_点击
        self.sb_page.editingFinished.connect(self.sb_page_editingFinished)  # 显示当前页码范围 

    def canvasTabDraw(self, fromNum:int, toNum:int):    # 画布Tab绘图
        '''画布Tab绘图

        Attributes:
        ----------------
            fromNum: 绘图起始位置
            toNum: 绘图结束位置
        '''
        size = toNum - fromNum + 1
        for i in range(size):
            self.tabCanvasList[i].getPlotItem().clearPlots()  # 清空画布Tab
            self.tabCanvasList[i].getPlotItem().setTitle('第'+str(fromNum+i)+'个标记数据段')
            self.tabCanvasList[i].addItem(pg.PlotCurveItem(np.arange(self.data_tab_point[fromNum+i-1], self.data_tab_point[fromNum+i-1] + glo.sample_rate, 1), self.tabDataList[(fromNum+i-1)%20], pen=pg.mkPen('k', width=1.5)))  # 添加画布Tab数据
        
        self.lb_page.setText(str(fromNum) + '-' + str(toNum))

    def btn_head_clicked(self): # 跳转到头部节点
        self.fresh_state = False
        if self.findNum > 3:
            self.fromNum = 1
            self.toNum = 3
        else:
            self.fromNum = 1
            self.toNum = self.findNum
        self.canvasTabDraw(1, self.findNum)
        ...

    def btn_tail_clicked(self): # 跳转到尾部节点
        self.fresh_state = True
        if self.findNum > 3:
            self.fromNum = self.findNum - 2
            self.toNum = self.findNum
        else:
            self.fromNum = 1
            self.toNum = self.findNum
        self.canvasTabDraw(self.fromNum, self.findNum)
        ...

    def btn_pre_clicked(self):  # 上一页
        self.fresh_state = False
        if self.fromNum > 3:
            self.fromNum -= 1
            self.toNum -= 1
        else:
            self.fromNum = 1
            self.toNum = 3
        self.canvasTabDraw(self.fromNum, self.toNum)
        ...

    def btn_next_clicked(self): # 下一页
        self.fresh_state = False
        if self.fromNum < self.findNum - 2:
            self.fromNum += 1
            self.toNum += 1
        else:
            self.fromNum = self.findNum - 2
            self.toNum = self.findNum
        self.canvasTabDraw(self.fromNum, self.toNum)
        ...

    def sb_page_editingFinished(self):  # 跳转页码_键入
        self.fresh_state = False
        self.fromNum = int(self.sb_page.text()) - 1
        self.toNum = self.fromNum + 2
        if self.fromNum < 1:
            self.fromNum = 1
            self.toNum = 3
        if self.toNum > self.findNum:
            self.toNum = self.findNum
        self.canvasTabDraw(self.fromNum, self.toNum)
        ...

    def btn_to_clicked(self):   # 跳转页码_点击 # WAIT
        ...

class drawFrameFile(MyCanvas):
    '''文件绘图窗口
    
    Attributes:
    ----------------
        history: 历史数据
    '''

    def __init__(self, parent=None):
        super(drawFrameFile, self).__init__(parent)
        self.initUI()

    def initUI(self):
        # 设置 drawTab 隐藏
        self.btn_tab.setVisible(False)  # 标签显示/隐藏按钮
        self.btn_identify.setVisible(False)    # 识别/停止识别按钮
        self.canvasTabFrame.setVisible(False)
    
    def initValues(self):
        self.history = np.array([]) # 历史数据

    def drawFile(self): # 绘制文件(首次)
        self.canvas.ydata = self.history.copy()
        if glo.isBaseline:
            self.canvas.ydata = detrend(self.canvas.ydata, type='linear')
            ...
        self.canvas.xdata = np.arange(0, self.history.size, 1)
        self.lb_max.setText(str(np.round(max(self.canvas.ydata), 2)))
        self.lb_min.setText(str(np.round(min(self.canvas.ydata), 2)))
        self.lb_rms.setText(str(np.round(np.sqrt(np.mean(self.canvas.ydata ** 2)), 2)))
        self.canvas.curve.setData(self.canvas.xdata, self.canvas.ydata)
        self.drawFileAgain()
    
    def drawFileAgain(self):    # 绘制文件(再次)
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
        '''更新Y轴范围'''
        self.canvas.setYRange(-glo.YDIS, glo.YDIS)

    def updateXlim(self):  # 更新X轴范围
        '''更新X轴范围'''
        ...

    def updateSampleRate(self): # 更新采样率
        '''更新采样率'''
        self.canvas.getPlotItem().getAxis('bottom').setScale(1 / glo.sample_rate)  # 单位放缩: 1s = 1 / 采样率

    def keyPressEvent(self, e) -> None:  # 键盘事件
        if e.key() == Qt.Key_Enter:
            self.chart.zoomReset()

    def closeEvent(self, event=None) -> None:   # 关闭事件
        # self.canvas.close_event()
        # self.canvas.mythread.terminate()
        ...

if __name__ == '__main__':    
    glo.__init__()
    pg.setConfigOption('background', 'w')
    pg.setConfigOption('foreground', 'k') 
    pg.setConfigOption('leftButtonPan', False)
    # 程序界面
    app = QApplication(sys.argv)
    ex = drawFrameFile()
    ex.show()
    sys.exit(app.exec_())
    ...