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

class dataSave(QThread):
    """数据保存线程"""
    data_save_signal = pyqtSignal(str)  # 数据处理完成信号

    def __init__(self, parent: QObject | None = ..., file_path: str=os.getcwd(), channel: str|int=32) -> None:
        super().__init__(parent)
        self.file_path = file_path  # 存放数据的文件夹路径
        self.channel = int(channel)  # 存放当前线程处理的通道数
        self.initValues()
        self.initList()
    
    def initValues(self):
        self.is_running = True  # 线程运行标志
        self.file_name = ""
        self.put_lock = QMutex()    # 数据存取线程锁
    
    def initList(self):
        self.data_queue: Queue[list] = Queue()  # 存放待处理数据的队列
    
    def initFile(self, file_path: str):
        # 确定文件夹是否存在
        self.file_path = file_path+"\\MeasureData"
        if not os.path.exists(self.file_path):
            os.mkdir(self.file_path)
        # 创建文件
        file_name = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime()) + ".txt"
        self.file_name = os.path.join(self.file_path, file_name)
        with open(self.file_name, "w") as f:
            self.data_save_signal.emit(self.file_name)
    
    def updateFilePath(self, file_path: str) -> None:
        self.file_path = file_path
    
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

    def save_data(self) -> bool:
        data_list = self.get_data()
        if data_list[0].size == 0:
            return False
        with open(self.file_name, "a") as f:
            np.savetxt(f, np.array(data_list).transpose(), fmt="%lf", delimiter=" ")
        return True
    
    def del_thread(self) -> None:
        self.is_running = False

    def run(self) -> None:
        self.initFile(self.file_path)
        while self.is_running:
            self.save_data()
            QThread.sleep(1)
            
if __name__ == '__main__':
    d = dataSave(None, 32)
    time_start = time.time()
    for i in range(10000):
        d.put_data()
    d.save_data()
    print("Time used:"+str(time.time()-time_start)+"s")
