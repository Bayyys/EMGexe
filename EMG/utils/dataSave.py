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
    """
    数据保存线程
    
    Attribute:
    ----------
        parent: 父对象
        file_path: 文件夹路径
        channel: 通道数
    
    Signals:
    --------
        data_save_signal: str -> 主窗口文件名参数修改
    """
    data_save_signal = pyqtSignal(str)  # 文件名修改信号

    def __init__(self, parent: QObject | None = ..., file_path: str=os.getcwd(), channel: str|int=32) -> None:
        """
        Attribute:
        ----------
            parent: 父对象
            file_path: 文件夹路径
            channel: 通道数
        """
        super().__init__(parent)
        self.file_path = file_path  # 存放数据的文件夹路径
        self.channel = int(channel)  # 存放当前线程处理的通道数
        self.initValues()
        self.initList()
    
    def initValues(self):
        """初始化变量"""
        self.is_running: bool=True  # 线程运行标志
        self.file_name: str=""      # 文件名
        self.put_lock: QMutex=QMutex()    # 数据存取线程锁
    
    def initList(self):
        """初始化列表"""
        self.data_queue: Queue[list] = Queue()  # 存放待处理数据的队列
    
    def initFile(self, file_path: str) -> None:
        """
        初始化文件
        
        创建文件夹, 创建文件

        Attribute:
        ----------
            file_path: 文件夹路径
        """
        self.file_path = file_path+"\\MeasureData"
        if not os.path.exists(self.file_path):  # 确定文件夹是否存在
            os.mkdir(self.file_path)
        file_name = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime()) + ".txt"   # 文件名: 年-月-日-时-分-秒.txt
        self.file_name = os.path.join(self.file_path, file_name)    # 文件路径
        with open(self.file_name, "w") as f:    # 创建文件
            self.data_save_signal.emit(self.file_name)  # 发送文件名修改信号
    
    def updateFilePath(self, file_path: str) -> None:
        """
        更新文件路径

        Attribute:
        ----------
            file_path: 文件夹路径
        """
        self.file_path = file_path
    
    def put_data(self, data: list=[[1,2,3] for i in range(32)]) -> None:
        """
        将数据放入队列

        Attribute:
        ----------
            data: 数据
        """
        self.put_lock.tryLock()
        self.data_queue.put(data)
        self.put_lock.unlock()

    def get_data(self) -> list:
        """
        从队列中取出数据

        Return:
        -------
            process_list: 处理后的数据
        """
        self.put_lock.tryLock()
        self.process_list: list=[np.array([]) for i in range(self.channel)]    # 存放处理后数据的字典
        while not self.data_queue.empty():
            data: list=self.data_queue.get()
            for i in range(self.channel):
                self.process_list[i] = np.append(self.process_list[i], data[i])
        self.put_lock.unlock()
        return self.process_list

    def save_data(self) -> bool:
        """
        保存数据

        Return:
        -------
            bool: 是否保存成功(数据为空时返回False)
        """
        data_list: list=self.get_data() # 获取数据
        if data_list[0].size == 0:  # 数据为空
            return False
        with open(self.file_name, "a") as f:
            np.savetxt(f, np.array(data_list).transpose(), fmt="%lf", delimiter=" ")    # 保存数据
        return True
    
    def del_thread(self) -> None:
        """
        删除线程

        线程运行标志置为False
        """
        self.is_running = False

    def run(self) -> None:
        self.initFile(self.file_path)
        while self.is_running:
            self.save_data()
            QThread.sleep(1)    # 休眠1s
            
if __name__ == '__main__':
    d = dataSave(None, 32)
    time_start = time.time()
    for i in range(10000):
        d.put_data()
    d.save_data()
    print("Time used:"+str(time.time()-time_start)+"s")
