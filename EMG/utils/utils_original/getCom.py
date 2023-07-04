import serial
import serial.tools.list_ports
from PyQt6.QtCore import QThread, pyqtSignal
from PyQt6.QtWidgets import QComboBox

class getCom(QThread):  # 获取串口号线程
    """获取串口号线程

    Signal:
    ----------------
        comUpdate: 串口号更新信号(检测串口的变化, 发生变化传递更新串口号列表)
            emit: port_list_orignal: 串口号列表
    """
    getCom_portChanged = pyqtSignal(bool, list)
    is_running = True

    def __init__(self, cb_port: QComboBox):
        super().__init__()
        self.cb_port = cb_port
        self.port_list_orignal = [] # 串口号记录
        self.initPort()
    
    def __del__(self):
        getCom.is_running = False
        self.wait()
    
    def run(self):
        while(getCom.is_running):
            port_list = self.getCom()   # 获取最新的串口号列表
            if set(port_list) != set(self.port_list_orignal):  # 判断串口号列表是否发生变化
                self.port_list_orignal = port_list[:]
                current_port = self.cb_port.currentText()
                if current_port not in port_list:
                    self.getCom_portChanged.emit(False, port_list)
                    self.cb_port.setCurrentIndex(0)
                else:
                    self.getCom_portChanged.emit(True, port_list)
                    self.cb_port.setCurrentText(current_port)
            QThread.sleep(1)
                
    def initPort(self):
        self.port_list_orignal = port_list = self.getCom()
        for port in port_list:
            self.cb_port.addItem(str(port))
            if port.find('XR21B1411') != -1:
                self.cb_port.setCurrentIndex(self.cb_port.count()-1)
    
    def updatePort(self, port_list: list=[]): # BUG: 串口号清空导致出错
        self.cb_port.removeItem(0)
        for port in port_list:
            self.cb_port.addItem(str(port))
    
    @staticmethod 
    def getCom():
        port_list = list(serial.tools.list_ports.comports())
        # 按照端口号进行排序
        port_list.sort(key=lambda x: int(x[0].split('COM')[1]))
        return [str(port) for port in port_list]
