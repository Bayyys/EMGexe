import serial
import serial.tools.list_ports
from time import sleep

def serialOpen(com: str = "", bps: str = '4608000', timeout: str = '8') -> serial.Serial | None:    # 打开串口
    """打开串口

    Attributes:
    ----------------
        com: 串口号
        bps: 波特率
        timeout: 超时时间

    Return:
    ---------------- 
        ser: 串口对象
    """
    try:
        ser = serial.Serial(com.split(' ')[0], int(bps), timeout=int(timeout))
        if serialIsOpen(ser):
            print('open success')
            return ser
        else:
            print('open failed')
            return None
    except:
        print("serialOpen: 串口不存在")
        return None
    finally:
        ...

def serialClose(ser: serial.Serial | None = ...) -> bool:   # 关闭串口
    '''关闭串口
    
    Attribute:
    ----------------
        ser: 串口对象
    '''
    if ser is None or not serialIsOpen(ser):
        print("serialClose: 串口不存在或已关闭")
        return False
    try:
        ser.reset_input_buffer()
        ser.reset_output_buffer()
        ser.close()
        return True
    except:
        print("serialClose: 串口关闭失败")
        return False

def serialIsOpen(ser: serial.Serial | None = ...) -> bool:  # 判断串口是否打开
    ''' 判断串口是否打开
    
    Attribute:
    ----------------
        ser: 串口对象
    
    Return:
    ----------------
        True/False: 是否打开
    '''
    try:
        if ser is not None and ser.is_open == True:
            return True
        else:
            return False
    except:
        return False

def serialWrite(ser: serial.Serial | None= ..., state: str='start', connect: str='usb', sample_rate: int | str=1000, channel: int | str=32):
    '''发送命令

    Attributes:
    ----------
        state: start/stop
        connect: usb/wifi
        sample_rate: 250/500/1000/2000/4000/8000/16000
        channel: 32/2
    '''
    if ser is None or not serialIsOpen(ser):
        print("serialWrite: 串口不存在或已关闭")
    else:
        sample_rate=int(sample_rate)
        channel=int(channel)
        message = {'usb': [0xaa, 0x08, 0x01], 'wifi': [0xaa, 0x08, 0x02],  # 连接方式: 0xAA 0x08 + 0x01:usb, 0x02:wifi
                # 采样率: 0xAA 0x03 + 0x01 + 0x96:250Hz, 0x95:500Hz, 0x94:1000Hz, 0x93:2000Hz, 0x92:4000Hz, 0x91:8000Hz, 0x90:16000Hz
                250: [0xaa, 0x03, 0x01, 0x96], 500: [0xaa, 0x03, 0x01, 0x95], 1000: [0xaa, 0x03, 0x01, 0x94], 2000: [0xaa, 0x03, 0x01, 0x93], 4000: [0xaa, 0x03, 0x01, 0x92], 8000: [0xaa, 0x03, 0x01, 0x91], 16000: [0xaa, 0x03, 0x01, 0x90],
                # 通道数: 0xAA 0x07 + 0x20:32, 0x02:2
                32: [0xaa, 0x07, 0x20], 2: [0xaa, 0x07, 0x02],
                'stop': [0xaa, 0x06, 0x00], 'start': [0xaa, 0x06, 0x01]}   # 开始/停止采集: 0xAA 0x06 + 0x00:stop, 0x01:start
        ser.reset_input_buffer()
        ser.reset_output_buffer()
        if state == 'start':
            ser.write(bytes(message[connect]))
            sleep(0.1)
            ser.write(bytes(message[sample_rate]))
            sleep(0.1)
            ser.write(bytes(message[channel]))
            sleep(0.1)
            ser.write(bytes(message[state]))
            sleep(0.1)
        elif state == 'stop':
            for i in range(3):
                ser.write(bytes(message[state]))
                sleep(0.1)
        else:
            print('Send Message Error!')
