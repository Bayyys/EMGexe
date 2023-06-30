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
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
        self.initValues()
        self.initChart()
    
    def initUI(self):
        self.setupUi(self)
        self.setWindowTitle("drawFrame")
    
    def initValues(self):
        self.chartList = []
        self.chartNum = 32
    
    def initChart(self, chartNum: int=32):
        for i in range(chartNum):
            chart = drawSingleCanvas()
            chart.lb_num.setText(f"CH {i+1}")
            self.chartList.append(chart)
            self.layout_chart.addWidget(chart)

    def updateChart(self, charNum: int=32):
        self.chartNum = charNum
        for i in range(self.chartNum):
            self.chartList[i].show()
        for i in range(self.chartNum, 32):
            self.chartList[i].hide()
        self.resizeEvent(None)
    
    def updateData(self, data: list):
        for i in range(self.chartNum):
            self.chartList[i].updateData(data[i])

    def updateRate(self, rate: str|int = 1000):
        for i in range(self.chartNum):
            self.chartList[i].updateRate(int(rate))

    def updateXdis(self, xdis: str|int = 4):
        for i in range(self.chartNum):
            self.chartList[i].updateXdis(int(xdis))
    
    def updateYdis(self, ydis: str|int = 1000):
        for i in range(self.chartNum):
            self.chartList[i].updateYdis(int(ydis))

    def resetChart(self):
        for i in range(self.chartNum):
            self.chartList[i].canvas.zoomReset()

    def resizeEvent(self, a0: QWidget.resizeEvent) -> None:
        self.scrollContent.setMinimumHeight(int(self.scrollArea.height()/4)*self.chartNum)
        return super().resizeEvent(a0)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = drawFrame()
    win.show()
    sys.exit(app.exec())
