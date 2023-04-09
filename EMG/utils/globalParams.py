import sys
sys.path.append('..')
from utils import decodeUtil
from time import sleep
import pandas as pd
import numpy as np
from PyQt5.QtCore import QMutex
import queue

def __init__():
    global scan, connected, ser, history2, data, mutex_history, mutex_data, time, com, isBaseline, isLowPassFilter, isHighPassFilter, isNotchFilter, isBandPassFilter, XDIS, YDIS, sample_rate, channel_num, sos_low, sos_high, sos_notch, sos_band, lowFilter_low, highFilter_low, highFilter_high, notchFilter_cutoff, notchFilter_param, bandFilter_pass, bandFilter_stop, message, time_all, time_temp
    scan = False
    connected = False
    ser = None
    history = np.array([[], []])
    history2 = queue.Queue()
    mutex_history = QMutex()
    mutex_data = QMutex()
    com = ""
    isBaseline = True
    isLowPassFilter = False
    isHighPassFilter = False
    isNotchFilter = False
    isBandPassFilter = False
    XDIS = 8000
    YDIS = 200000
    sample_rate = 1000
    channel_num = 2
    sos_low = None
    sos_high = None
    sos_notch = None
    sos_band = None
    lowFilter_low = 50
    highFilter_high = 1
    notchFilter_cutoff = 50
    notchFilter_param = 10
    bandFilter_pass = 1
    bandFilter_stop = 50
    message = {'usb': [0xaa, 0x08, 0x01], 'wifi': [0xaa, 0x08, 0x02],  # 连接方式: 0xAA 0x08 + 0x01:usb, 0x02:wifi
               # 采样率: 0xAA 0x03 + 0x01 + 0x96:250Hz, 0x95:500Hz, 0x94:1000Hz, 0x93:2000Hz, 0x92:4000Hz, 0x91:8000Hz, 0x90:16000Hz
               250: [0xaa, 0x03, 0x01, 0x96], 500: [0xaa, 0x03, 0x01, 0x95], 1000: [0xaa, 0x03, 0x01, 0x94], 2000: [0xaa, 0x03, 0x01, 0x93], 4000: [0xaa, 0x03, 0x01, 0x92], 8000: [0xaa, 0x03, 0x01, 0x91], 16000: [0xaa, 0x03, 0x01, 0x90],
               # 通道数: 0xAA 0x07 + 0x20:32, 0x02:2
               32: [0xaa, 0x07, 0x20], 2: [0xaa, 0x07, 0x02],
               'stop': [0xaa, 0x06, 0x00], 'start': [0xaa, 0x06, 0x01]}   # 开始/停止采集: 0xAA 0x06 + 0x00:stop, 0x01:start
    time_all = 0
    time_temp = 0


def sendMessage(state, connect='usb', sample_rate=1000, channel=32):
    '''发送命令
    state: start/stop
    connect: usb/wifi
    sample_rate: 250/500/1000/2000/4000/8000/16000
    channel: 32/2'''
    global ser, message
    ser.flushInput()
    ser.flushOutput()
    if state == 'start':
        ser.write(message[connect])
        sleep(0.1)
        ser.write(message[sample_rate])
        sleep(0.1)
        ser.write(message[channel])
        print(channel)
        sleep(0.1)
        ser.write(message['start'])
        sleep(0.1)
    elif state == 'stop':
        for i in range(3):
            ser.write(message['stop'])
            sleep(0.1)
    else:
        print('error')


def initFilterParams():
    global sos_low, sos_high, sos_notch, sos_band
    sos_low = decodeUtil.LowPassFilter(lowFilter_low, sample_rate)
    sos_high = decodeUtil.HighPassFilter(highFilter_high, sample_rate)
    sos_notch = decodeUtil.NotchFilter(
        notchFilter_cutoff, notchFilter_param, sample_rate)
    sos_band = decodeUtil.BandPassFilter(
        bandFilter_pass, bandFilter_stop, sample_rate)


def lowFilterUpdate():
    global sos_low, lowFilter_low
    sos_low = decodeUtil.LowPassFilter(lowFilter_low, sample_rate)


def highFilterUpdate():
    global sos_high, highFilter_high
    sos_high = decodeUtil.HighPassFilter(highFilter_high, sample_rate)


def notchFilterUpdate():
    global sos_notch, notchFilter_cutoff, notchFilter_param
    sos_notch = decodeUtil.NotchFilter(
        notchFilter_cutoff, notchFilter_param, sample_rate)


def bandFilterUpdate():
    global sos_band, bandFilter_pass, bandFilter_stop
    sos_band = decodeUtil.BandPassFilter(
        bandFilter_pass, bandFilter_stop, sample_rate)


def get_scan():
    return scan


def set_scan(value):
    global scan
    scan = value


def get_connected():
    return connected


def set_connected(value):
    global connected
    connected = value


def get_ser():
    return ser


def set_ser(value):
    global ser
    ser = value


def init_history():
    global history
    mutex_history.lock()
    history = np.array([[], []])
    mutex_history.unlock()


def add_history(value):
    global history, history2
    # add_data(value)
    mutex_history.lock()
    history = np.concatenate((history, value), axis=1)
    history2.put(value)
    mutex_history.unlock()


def len_history():
    global history
    return history.shape[1]


def get_com():
    return com


def set_com(value):
    global com
    com = value

def save_data(fileName, type):
    try:
        if type == "纯文本(*.txt)":
            np.savetxt(fileName, np.array(history), fmt='%lf', delimiter=' ',
                       newline='\n', header='', footer='', comments='# ', encoding=None)
        elif type == "CSV(*.csv)":
            pd.DataFrame(history).to_csv(
                fileName, mode='a', index=False, header=False)
        print(np.array(history).shape)
        return True
    except Exception as e:
        print("error")
        return False
    ...


def load_data(fileName, type):
    global history
    try:
        if type == "CSV(*.csv)":
            data = pd.read_csv(fileName, header=None)
            history = np.array(data.values)
            return True
        elif type == "纯文本(*.txt)":
            # history = np.loadtxt(fileName, dtype=float)
            history = np.transpose(np.loadtxt(fileName, dtype=float)) / 24.0
            
            return True
        else:
            return False
    except Exception as e:
        print("error")
        return False
    ...


if __name__ == '__main__':
    __init__()
    # test = pd.DataFrame(history)
    # df = test.to_csv('test.csv', mode='a', index=False, header=False)
    # print(test)
    # data = pd.read_csv('test.csv', header=None)
    # print(data.loc[:, 0])
    # history = [str(i + 1) for i in range(100)]
    # data = np.array(history)
    # print(data)
    # np.savetxt('test.txt', data, fmt='%.2lf', delimiter='\t\n',
    #            newline='', header='', footer='', comments='# ', encoding=None)
    # data2 = np.loadtxt('test.txt', dtype=str)
    # print(data2)
    print(history.shape)
    add_history([[1, 2], [3, 4]])
    add_history([[5, 6], [7, 8]])
    print(history)
    ...
