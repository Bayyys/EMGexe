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
    """
    数据处理线程

    Attribute:
    --------
        parent(QObject | None): 父对象
        channel(str|int): 通道数
        rate(str|int): 采样率
        isFilter(bool): 滤波器开启标志
        filter_dict(dict): 滤波器参数
    
    Signals:
    --------
        data_process_signal: list
            处理后数据信号 -> 数据显示线程, 数据保存线程
    """
    data_process_signal: pyqtSignal=pyqtSignal(list)

    def __init__(self, parent: QObject | None = ..., channel: str|int=32, rate: str|int=1000, isFilter: bool=True, filter_dict: dict={}) -> None:
        super().__init__(parent)
        self.channel: int=int(channel)  # 存放当前线程处理的通道数
        self.rate: int=int(rate)   # 采样率
        self.isFilter: bool=isFilter    # 滤波器开启标志
        self.filter_dict: dict=filter_dict  # 滤波器参数
        self.initValues()
        self.initList()
        self.initFilter()
    
    def initValues(self):
        """初始化变量"""
        self.is_running: bool=True  # 线程运行标志
        self.put_lock: QMutex=QMutex()    # 数据存取线程锁
        self.process_lock: QMutex=QMutex()    # 数据处理线程锁
        self.filter_key_list: list[str]=["bandstop", "bandpass", "highpass", "lowpass"]  # 滤波器类型列表

    
    def initList(self):
        """初始化列表"""
        self.data_queue: Queue[list] = Queue()  # 存放待处理数据的队列
        self.process_list: list=[np.array([]) for i in range(self.channel)]    # 存放原始数据的列表
        self.history_list: list=[np.array([]) for i in range(self.channel)]    # 存放历史数据的列表
        self.data_processd_lsit: list=[np.array([]) for i in range(self.channel)] # 存放处理后数据的列表
    
    def initFilter(self) -> None:
        """初始化滤波器"""
        self.isFilter_dict: dict={}   # 滤波器开启标志字典
        self.sosFilter_dict: dict={}    # 滤波器参数字典
        for key in self.filter_dict.keys(): # 初始化滤波器参数字典
            if key.startswith("is"):    # 初始化滤波器开启标志字典
                self.isFilter_dict[key] = self.filter_dict[key]
            else:   # 初始化滤波器参数字典
                self.updateFilter(key, self.filter_dict[key])

    def updateFilter(self, key: str="", param: list=[], N=8, ripple=1) -> None:
        """
        更新滤波器参数

        Attribute:
        ----------------
            key: 滤波器类型
            param: 滤波器参数
            N: 滤波器阶数 默认为8
            ripple: 滤波器衰减系数 默认为1

        """
        if len(param) == 1: # 低通或高通滤波器
            self.sosFilter_dict[key] = signal.butter(N=N, Wn=param[0], btype=key, output='sos', fs=self.rate)
        else:   # 带通或带阻滤波器
            self.sosFilter_dict[key] = signal.butter(N=N, Wn=[param[0], param[1]], btype=key, output='sos', fs=self.rate)
    
    def updateFilterParam(self, update_dict) -> None:
        """
        更新滤波器参数

        Attribute:
        ----------------
            update_dict(dict): 滤波器参数字典
        """
        [key, param] = update_dict  # 获取滤波器类型和参数
        if key.startswith("is"):    # 更新滤波器开启标志字典
            self.isFilter_dict[key] = param
            print(self.isFilter_dict)
        else:   # 更新滤波器参数字典
            self.updateFilter(key, param)
            print(self.sosFilter_dict.keys())
    
    def put_data(self, data: list=[[1,2,3] for i in range(32)]) -> None:
        """
        存放数据
        
        Attribute:
        ----------------
            data(list): 原始数据列表
        """
        self.put_lock.tryLock() # 加锁
        self.data_queue.put(data)   # 存放数据
        self.put_lock.unlock()  # 解锁

    def get_data(self) -> list:
        """
        获取数据
        
        Returns:
        ----------------
            process_list(list): 处理后数据列表
        """
        self.put_lock.tryLock() # 加锁
        self.process_list: list=[np.array([]) for i in range(self.channel)]    # 存放处理后数据的字典
        while not self.data_queue.empty():  # 队列不为空
            data = self.data_queue.get()
            for i in range(self.channel):
                self.process_list[i] = np.append(self.process_list[i], data[i])
        self.put_lock.unlock()  # 解锁
        return self.process_list    # 返回处理后数据列表

    def process(self) -> bool:
        """
        数据处理

        Returns:
        ----------------
            bool: 数据处理成功标志(无数据返回False)
        """
        data_list = self.get_data() # 获取数据
        if data_list[0].size == 0:  # 无数据, 返回False
            return False
        self.process_lock.tryLock() # 加锁
        for i in range(self.channel):   # 遍历通道
            data = data_list[i].copy()
            data_length = data.shape[0]
            self.history_list[i] = np.append(self.history_list[i], data)[-self.rate:].copy()
            data = self.history_list[i].copy()
            if self.isFilter_dict["isbaseline"]:    # 基线移除
                data = signal.detrend(data, type='constant')
            if self.isFilter:   # 开启滤波器
                for key in self.filter_key_list:    # 遍历滤波器类型
                    if self.isFilter_dict["is"+key]:    # 滤波
                        data = signal.sosfilt(self.sosFilter_dict[key], data)
                    if key == "bandpass" and self.isFilter_dict["is"+key]:
                        break
            self.data_processd_lsit[i] = np.append(self.data_processd_lsit[i], data[-data_length:])[-self.rate*5:]  # 存放处理后数据(最多存放5s数据)
        self.process_lock.unlock()  # 解锁
        return True
    
    def del_thread(self) -> None:
        """
        删除线程
        
        线程运行标志置为False
        """
        self.is_running = False

    def run(self) -> None:
        while self.is_running:  # 线程运行标志为True
            if self.process():
                self.data_process_signal.emit(self.data_processd_lsit)  # 发送处理后数据
            QThread.msleep(50)
            
if __name__ == '__main__':
    d = dataProcess(None, 32)
    time_start = time.time()
    for i in range(10000):
        d.put_data()
    d.process()
    print("Time used:"+str(time.time()-time_start)+"s")



