import sys
import os
import typing
import time
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QWidgetAction
from PyQt6.QtCore import QObject, QThread, pyqtSignal, QMutex
from queue import Queue
import numpy as np
import scipy.signal as signal

class dataProcess(QThread):
    """数据处理线程"""
    data_process_signal = pyqtSignal(list)

    def __init__(self, parent: QObject | None = ..., channel: str|int=32, rate: str|int=1000, isFilter: bool=True, filter_dict: dict={}) -> None:
        super().__init__(parent)
        self.channel = int(channel)  # 存放当前线程处理的通道数
        self.rate = int(rate)   # 采样率
        self.isFilter = isFilter    # 滤波器开启标志
        self.filter_dict = filter_dict  # 滤波器参数
        self.initValues()
        self.initList()
        self.initFilter()
    
    def initValues(self):
        self.is_running = True  # 线程运行标志
        self.put_lock = QMutex()    # 数据存取线程锁
        self.process_lock = QMutex()    # 数据处理线程锁
        self.filter_key_list = ["bandstop", "bandpass", "highpass", "lowpass"]  # 滤波器类型列表

    
    def initList(self):
        self.data_queue: Queue[list] = Queue()  # 存放待处理数据的队列
        self.process_list: list=[np.array([]) for i in range(self.channel)]    # 存放原始数据的列表
        self.history_list: list=[np.array([]) for i in range(self.channel)]    # 存放历史数据的列表
        self.data_processd_lsit: list=[np.array([]) for i in range(self.channel)] # 存放处理后数据的列表
    
    def initFilter(self):
        self.isFilter_dict = {}
        self.sosFilter_dict = {}
        for key in self.filter_dict.keys():
            if key.startswith("is"):
                self.isFilter_dict[key] = self.filter_dict[key]
            else:
                self.updateFilter(key, self.filter_dict[key])

    def updateFilter(self, key, param, N=8, ripple=1):
        if len(param) == 1:
            self.sosFilter_dict[key] = signal.butter(N=N, Wn=param[0], btype=key, output='sos', fs=self.rate)
        else:
            self.sosFilter_dict[key] = signal.butter(N=N, Wn=[param[0], param[1]], btype=key, output='sos', fs=self.rate)
    
    def updateFilterParam(self, update_dict):
        [key, param] = update_dict
        if key.startswith("is"):
            self.isFilter_dict[key] = param
            print(self.isFilter_dict)
        else:
            self.updateFilter(key, param)
            print(self.sosFilter_dict.keys())
    
    def put_data(self, data: list=[[1,2,3] for i in range(32)]) -> None:
        self.put_lock.tryLock()
        self.data_queue.put(data)
        self.put_lock.unlock()

    def get_data(self) -> list:
        self.put_lock.tryLock()
        self.process_list: list=[np.array([]) for i in range(self.channel)]    # 存放处理后数据的字典
        while not self.data_queue.empty():
            data = self.data_queue.get()
            for i in range(self.channel):
                self.process_list[i] = np.append(self.process_list[i], data[i])
        self.put_lock.unlock()
        return self.process_list

    def process(self) -> bool:
        data_list = self.get_data()
        if data_list[0].size == 0:
            return False
        self.process_lock.tryLock()
        for i in range(self.channel):
            data = data_list[i].copy()
            data_length = data.shape[0]
            self.history_list[i] = np.append(self.history_list[i], data)[-self.rate:].copy()
            data = self.history_list[i].copy()
            if self.isFilter_dict["isbaseline"]:
                data = signal.detrend(data, type='constant')
            if self.isFilter:
                for key in self.filter_key_list:
                    if self.isFilter_dict["is"+key]:
                        data = signal.sosfilt(self.sosFilter_dict[key], data)
                    if key == "bandpass" and self.isFilter_dict["is"+key]:
                        break
            self.data_processd_lsit[i] = np.append(self.data_processd_lsit[i], data[-data_length:])[-self.rate*5:]
        self.process_lock.unlock()
        return True
    
    def del_thread(self) -> None:
        self.is_running = False

    def run(self) -> None:
        while self.is_running:
            if self.process():
                self.data_process_signal.emit(self.data_processd_lsit)
            QThread.msleep(10)
            
if __name__ == '__main__':
    d = dataProcess(None, 32)
    time_start = time.time()
    for i in range(10000):
        d.put_data()
    d.process()
    print("Time used:"+str(time.time()-time_start)+"s")



