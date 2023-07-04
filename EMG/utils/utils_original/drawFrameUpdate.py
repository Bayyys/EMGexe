import sys
import os
import typing
import time
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtCore import QObject, QThread
from queue import Queue
import numpy as np
import scipy.signal as signal
from widget.canvas_frame.drawFrame import drawFrame
from widget.fft_widget.fftWidget import fftWidget

class dataFrameUpdate(QThread):
    """数据处理线程"""

    def __init__(self, parent: QObject | None = ..., drawFrame:drawFrame=None, fftWidget:fftWidget=None) -> None:
        super().__init__(parent)
        self.drawFrame = drawFrame
        self.fftWidget = fftWidget
        self.initValues()
        self.initList()
    
    def initValues(self):
        self.is_running = True  # 线程运行标志
    
    def initList(self):
        self.data_list = []
    
    def put_data(self, data: list=[[1,2,3] for i in range(32)]) -> None:
        self.data_list = data
    
    def process(self) -> None:
        data_list = self.data_list
        if data_list:
            self.drawFrame.updateData(data_list)
            self.fftWidget.update_chart(data_list)

    def del_thread(self) -> None:
        self.is_running = False

    def run(self) -> None:
        while self.is_running:
            self.process()
            QThread.msleep(10)
            
if __name__ == '__main__':
    d = dataFrameUpdate(None, 32)
    time_start = time.time()
    for i in range(10000):
        d.put_data()
    d.process()
    print("Time used:"+str(time.time()-time_start)+"s")



