import sys
import os
import typing
from PyQt6 import QtCore, QtGui
sys.path.append(os.getcwd()+"\\EMG")
import numpy as np
from PyQt6.QtWidgets import QApplication, QFrame, QWidget, QVBoxLayout, QScrollArea, QSizePolicy, QWidgetAction, QAbstractScrollArea
# ui
from ui.canvas_ui.draw_frame_ui import Ui_drawFrame
from widget.canvas_frame.drawSingleFrame.drawSingleFrame import drawSingleCanvas

class drawFrame(QFrame, Ui_drawFrame):
    """
    图像显示界面
    """
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
        self.initValues()
        self.initChart()
    
    def initUI(self):
        self.setupUi(self)
        self.setWindowTitle("drawFrame")
    
    def initValues(self):
        self.chartList: list[drawSingleCanvas] = [] # 图表列表
        self.chartNum = 32
    
    def initChart(self, chartNum: int=32):
        """
        初始化图表
        
        最初创建32通道图表数据
        """
        for i in range(chartNum):
            chart = drawSingleCanvas()
            chart.lb_num.setText(f"CH {i+1}")
            # chart.canvas.curve.setPen(color=(i, self.chartNum+1.3))
            self.chartList.append(chart)
            self.layout_chart.addWidget(chart)

    def updateChart(self, chartNum: int=32):
        """
        更新图表

        根据通道数更新图表显示数量

        Attribute:
        ----------
            charNum: 通道数
        """
        self.chartNum = chartNum
        for i in range(self.chartNum):
            self.chartList[i].show()
        for i in range(self.chartNum, 32):
            self.chartList[i].hide()
        self.resizeEvent(None)
    
    def updateData(self, data: list):
        """
        更新数据
        
        Attribute:
        ----------
            data: 数据
        """
        for i in range(self.chartNum):
            self.chartList[i].updateData(data[i])

    def updateRate(self, rate: str|int = 1000):
        """
        更新采样率

        Attribute:
        ----------
            rate: 采样率
        """
        for i in range(self.chartNum):
            self.chartList[i].updateRate(int(rate))

    def updateXdis(self, xdis: str|int = 4):
        """
        更新X轴显示范围

        Attribute:
        ----------
            xdis: X轴显示范围
        """
        for i in range(self.chartNum):
            self.chartList[i].updateXdis(int(xdis))
    
    def updateYdis(self, ydis: str|int = 1000):
        """
        更新Y轴显示范围

        Attribute:
        ----------
            ydis: Y轴显示范围
        """
        for i in range(self.chartNum):
            self.chartList[i].updateYdis(int(ydis))

    def resetChart(self):
        """
        重置图表

        设定自动更新坐标轴范围
        """
        for i in range(self.chartNum):
            self.chartList[i].canvas.zoomReset()
            self.chartList[i].resizeEvent(None)

    def fftChangeMode(self, fft: bool=True):
        if fft:
            for i in range(self.chartNum):
                self.chartList[i].canvas.curve.setFftMode(fft)
                self.chartList[i].canvas.getPlotItem().getAxis('bottom').setScale(self.chartList[i].canvas.rate)  # 单位放缩: 1s = 1 / 采样率
                self.chartList[i].canvas.setLabel('left', 'Amplitute/a.u.')
                self.chartList[i].canvas.setLabel('bottom', 'Frequence/Hz')
        else:
            for i in range(self.chartNum):
                self.chartList[i].canvas.curve.setFftMode(fft)
                self.chartList[i].canvas.getPlotItem().getAxis('bottom').setScale(1 / self.chartList[i].canvas.rate)  # 单位放缩: 1s = 1 / 采样率
                self.chartList[i].canvas.setLabel('left', 'Amplitude(uV)')
                self.chartList[i].canvas.setLabel('bottom', 'Time(s)')

    def resizeEvent(self, a0: QWidget.resizeEvent) -> None:
        self.scrollContent.setMinimumHeight(int(self.scrollArea.height()/4)*self.chartNum)
        return super().resizeEvent(a0)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = drawFrame()
    win.show()
    sys.exit(app.exec())
