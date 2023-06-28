import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import time
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter, lfilter, freqz, filtfilt, detrend, sosfilt
from PyQt6.QtCore import Qt, QTimer, QThread, QMutex, pyqtSignal
from PyQt6.QtWidgets import QApplication, QSizePolicy, QFrame, QPushButton
import pyqtgraph as pg
# ui
from ui.canvas_ui.canvasTab_ui.canvasTab import Ui_canvasTab
from widget.canvas_frame.myCanvas.MyCanvas import MyCanvas

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
        self.initUI()
        self.initValues()
        self.initCanvasTab()

    def initUI(self):
        self.setupUi(self)
        # 横向滚动条关闭
        self.btn_head.clicked.connect(self.btn_head_clicked)    # 头部节点
        self.btn_tail.clicked.connect(self.btn_tail_clicked)    # 尾部节点
        self.btn_pre.clicked.connect(self.btn_pre_clicked)  # 上一页
        self.btn_next.clicked.connect(self.btn_next_clicked)    # 下一页
        # self.et_page.returnPressed.connect(self.et_page_returnPressed)  # 跳转到指定页_键入
        self.btn_to.clicked.connect(self.btn_to_clicked)    # 跳转到指定页_点击
        self.sb_page.editingFinished.connect(self.sb_page_editingFinished)  # 显示当前页码范围 

    def initValues(self):
        self.tabCanvasList = [] # 用于存储tabCanvas的列表(三维)
        self.findNum = 0    # 记录标记数据段的个数
        self.fromNum = 1    # 记录标记数据段的绘图起始位置
        self.toNum = 3    # 记录标记数据段的绘图结束位置
        self.fresh_state = True # 记录是否刷新tabCanvas的状态
        self.arrayLen = 50  # 用于存储tab数据的长度(实时)
        self.tabDataList = np.zeros((self.arrayLen, 4000))   # 用于存储tab数据的列表(二维 arrayLen * sample_rate)
        self.data_tab_point = np.array([])  # 存储标记数据段的坐标点(结束记录后存储)
    
    def initCanvasTab(self):   # 初始化画布Tab
        pg.setConfigOption('foreground', 'k')   # 设置前景色(绘图折线笔刷颜色) - 黑色

        # 设置tabCanvas(三维)
        for i in range(3):
            tabCanvas = MyCanvas()
            # tabCanvas.setWindowTitle('第'+str(i+1)+'个标记数据段')
            self.plotLayout2.addWidget(tabCanvas)
            self.tabCanvasList.append(tabCanvas)

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
            self.tabCanvasList[i].addItem(pg.PlotCurveItem(np.arange(self.data_tab_point[fromNum+i-1], 4000, 1), self.tabDataList[(fromNum+i-1)%20], pen=pg.mkPen('k', width=1.5)))  # 添加画布Tab数据
        
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
    
if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = drawTabFrame()
    win.show()
    sys.exit(app.exec())
