# 弃用
import sys
import os
import typing
import time
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QWidgetAction
from PyQt6.QtCore import QObject, QThread, pyqtSignal, QMutex
from queue import Queue
import numpy as np
from scipy.fft import fft
import scipy.signal as signal

class fftProcess(QThread):
    """数据处理线程"""
    fft_process_signal = pyqtSignal(list)

    def __init__(self, parent: QObject | None = ..., channel: str|int=32, rate: str|int=1000) -> None:
        super().__init__(parent)
        self.channel = int(channel)  # 存放当前线程处理的通道数
        self.rate = int(rate)   # 采样率
        self.initValues()
    
    def initValues(self):
        self.is_running = True  # 线程运行标志
        self.put_lock = QMutex()    # 数据存取线程锁
        self.data_list: list=[]    # 存放数据的字典
        self.process_list: list=[]  # 存放处理后数据的字典
        self.amp_lsit: list=[]    # 存放幅值的字典
        self.fre_list: list=[]    # 存放频率的字典

    def put_data(self, data: list=[[1,2,3] for i in range(32)]) -> None:
        self.put_lock.tryLock()
        self.data_list = data[:]
        self.put_lock.unlock()

    def get_data(self) -> list:
        return self.data_list
    
    def compute_fft(self, data):
        fft_x = fft(data)   #  fft计算
        amp_x = abs(fft_x)/len(data)*2  # 纵坐标变换
        label_x = np.linspace(0,int(len(data)/2)-1,int(len(data)/2))    # 生成频率坐标
        amp = amp_x[0:int(len(data)/2)] # 选取前半段计算结果即可
        # amp[0] = 0    # 可选择是否去除直流量信号
        fre = label_x/len(data)*self.rate   # 频率坐标变换
        # pha = np.unwrap(np.angle(fft_x))    # 计算相位角并去除2pi跃变
        # amp 幅值归一化
        if np.max(amp) != 0:
            amp = amp/np.max(amp)
        return amp, fre  # 返回幅度和频率

    def del_thread(self) -> None:
        self.is_running = False
    
    def process(self):
        data_list = self.get_data()
        self.amp_lsit: list=[np.array([]) for i in range(self.channel)]    # 存放幅值的字典
        self.fre_list: list=[np.array([]) for i in range(self.channel)]    # 存放频率的字典
        if data_list == []:
            return False
        i = 0
        for i in range(len(data_list)):
            amp, fre = self.compute_fft(data_list[i][-self.rate:])
            self.amp_lsit[i] = np.array(amp)
            self.fre_list[i] = np.array(fre)
        return True
    
    def run(self) -> None:
        while self.is_running:
            if self.process():
                self.fft_process_signal.emit([self.amp_lsit, self.fre_list])
            else:
                self.fft_process_signal.emit([self.amp_lsit, self.fre_list])
            QThread.msleep(10)

if __name__ == '__main__':
    d = fftProcess(None, 32)
    time_start = time.time()
    for i in range(10000):
        d.put_data()
    d.process()
    print("Time used:"+str(time.time()-time_start)+"s")



