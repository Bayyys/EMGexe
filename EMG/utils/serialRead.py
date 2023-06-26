import serial
import serial.tools.list_ports
from PyQt6.QtCore import QObject, QThread, pyqtSignal


class serialRead(QThread):  # 读取串口数据线程(32通道)
    '''读取串口数据线程
    (读取串口数据, 并进行解码, 发送更新数据信号)
    
    Signal:
    ----------------
        dateReadUpdate_new: 读取到的数据更新信号
            emit: None
        serDisconnect: 串口断开信号
            emit: num_list: 读取到的数据列表
    '''
    serDisconnect = pyqtSignal()
    dataReadUpdate = pyqtSignal(list)
    dataUpdate = pyqtSignal(bytes)
    dataDecodeUpdate = pyqtSignal(dict)
    is_running = True

    def __init__(self, parent: QObject | None = ..., serial: serial.Serial = ..., channel: int | str=32) -> None:
        super().__init__(parent)
        self.ser = serial
        self.channel = int(channel)
        self.initUI()
        self.initValues()
    
    def initUI(self):
        ...
    
    def initValues(self):
        self.data_remain = b''
        # 包序号
        dataLen = self.computeBytes(self.channel)
        dataEnd = 8 + dataLen
        self.packetNum = 0 # 包序号: 4Bytes(0-3)
        self.packetMark = 4 # 标志位: 2Bytes(4-5)
        self.packetRemain = 6 # 保留值: 1Byte(6)
        self.packetFlag = 7 # Flag: 1Byte(7)
        self.packetIndex = [i for i in range(8, dataEnd, 4)]    # 通道数据起始位置: channel*4Bytes(8-135/8-15)
        if self.channel == 2:
            self.packetPfall =  dataEnd # Pfall: 1Byte(16)
            self.packetNfall = dataEnd+1 # Nfall: 1Byte(17)
            self.packetParity = dataEnd+2 # 校验位: 1Bytes(18)
        else:
            self.packetPfall =  dataEnd # Pfall: 4Byte(136-139)
            self.packetNfall = dataEnd+4 # Nfall: 4Byte(140-143)
            self.packetParity = dataEnd+5 # 校验位: 1Bytes(144)
        self.fall = b''
        ...
    
    def __del__(self):
        self.is_running = False
        self.quit()
        self.wait()

    def run(self):
        print("serialRead start")
        while(self.is_running):
            try:
                if self.ser.is_open:
                    if self.ser.in_waiting:
                        data = self.ser.read(self.ser.in_waiting)
                        self.dataUpdate.emit(self.fall)
                        self.dataDecodeUpdate.emit(self.bytesSplit(data))
                else:   # 串口断开
                    print("serialRead stop")
            except:
                print("serialRead stop")
            QThread.msleep(10)
    
    def bytesSplit(self, data) -> dict:
        '''解码数据
        
        Attribute:
        ----------------
            data: 读取到的数据
        
        Return:
        ----------------
            num_list: 解码后的数据列表
        '''
        num_dict = {}
        self.fall = b''
        if len(self.data_remain) > 0:
            data = self.data_remain + data
        while len(data) > 145:
            if data[self.packetMark] == 0xa5 and data[self.packetMark + 1] == 0x5a: # 找到标志位
                for index in range(self.channel):
                    take = 0x01 << (index % 8)
                    offset = index // 8
                    if data[self.packetPfall + offset] & take or data[self.packetNfall + offset] & take: # 判断通道数据是否有效
                        num_dict[index] = 0.0
                    else:
                        num_dict[index] = self.bytestoFloat(data[self.packetIndex[index]: self.packetIndex[index] + 4])
                self.fall += data[self.packetPfall: self.packetParity]
                data = data[self.packetParity+1:]
            else:
                data = data[1:]
        self.data_remain = data
        return num_dict

    @staticmethod
    def bytestoFloat(data: bytes=b'') -> float:
        '''将字节转换为浮点数
        
        Attribute:
        ----------------
            data: 读取到的数据
        
        Return: 
        ----------------
            data: 转换后的数据
        '''
        start_index = 0
        try:
            if data[3] > 128:
                tmp1 = (~data[start_index]) & 0xff
                tmp2 = ((~data[start_index + 1]) & 0xff) << 8
                tmp3 = ((~data[start_index + 2]) & 0xff) << 16
                num = -(tmp1 + tmp2 + tmp3 + 1)
                num = num / 24
            else:
                num = int((data[start_index]) + (data[start_index + 1] << 8) + (data[start_index + 2] << 16)
                            + (data[start_index + 3] << 24))
                num = num / 24
            return num
        except:
            return 0.0
    
    @staticmethod
    def computeBytes(channel: int=32) -> int:
        return 4 * channel

    @staticmethod
    def computeFall(channel: int=32, index: int=0): # WAIT
        # 计算校验位
        # 校验位分为Pfall和Nfall两部分, 分别代表32通道正校验位和负校验位, 用于判断数据是否丢失, 0代表连接正常, 1代表数据丢失
        # 依次为 8-1, 16-9, 24-17, 32-25
        # 返回通道连接状态列表, 0代表连接正常, 1代表数据丢失
        compute = 0x01 << (index % 8)
        ...

if __name__ == '__main__':
    port_list = list(serial.tools.list_ports.comports())
    print(type(port_list))
    print(port_list)
    print([f"{port.device} {port.description}" for port in port_list])
