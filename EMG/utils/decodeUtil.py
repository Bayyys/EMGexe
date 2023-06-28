import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import re
from scipy.signal import butter
import utils.globalParams as glo

def signalDecode(str):
    # return [ float(i) for i in re.findall('-?\d+\.?\d*', str)]
    return re.findall('-?\d+\.?\d*', str)

def bytestoFloat(data):
    '''将字节转换为浮点数
    
    Attribute:
        data: 读取到的数据

    Return:
        data: 转换后的数据
    '''
    start_index = 0
    try:
        if data[3] > 128:
            tmp1 = (~data[start_index]) & 0xff
            tmp2 = ((~data[start_index + 1]) & 0xff) << 8
            tmp3 = ((~data[start_index + 2]) & 0xff) << 16
            data = -(tmp1 + tmp2 + tmp3 + 1)
            data = data / 24
        else:
            data = int((data[start_index]) + (data[start_index + 1] << 8) + (data[start_index + 2] << 16)
                        + (data[start_index + 3] << 24))
            data = data / 24
        return data
    except:
        return 0

def LowPassFilter(cutoffFreq, fs, N=8, ripple=1):  # 低通滤波
    '''低通滤波'''
    # return cheby1(N=N, rp=ripple,
    #                 Wn=cutoffFreq,
    #                 btype='lowpass', fs=fs,
    #                 analog=False, output='sos')
    return butter(N=N, Wn=cutoffFreq, btype='lowpass', output='sos', fs=fs)

def HighPassFilter(cutoffFreq, fs, N=8, ripple=1): # 高通滤波
    '''高通滤波'''
    # return cheby1(N=N, rp=ripple,
    #                 Wn=cutoffFreq,
    #                 btype='highpass', fs=fs,
    #                 analog=False, output='sos')
    return butter(N=N, Wn=cutoffFreq, btype='highpass', output='sos', fs=fs)

def NotchFilter(cutoffFreq, filterParam, fs, N=8, ripple=1):    # 陷波滤波
    '''陷波滤波'''
    # return cheby1(N=N, rp=ripple,
    #                 Wn=[cutoffFreq - filterParam, cutoffFreq + filterParam],
    #                 btype='bandstop', fs=fs,
    #                 analog=False, output='sos')
    return butter(N=N, Wn=[cutoffFreq-filterParam, cutoffFreq+filterParam],
                  btype='bandstop', output='sos', fs=fs)

def BandPassFilter(passbandFreq, stopbandFreq, fs, N=8, ripple=1):  # 带通滤波
    '''带通滤波'''
    # return cheby1(N=N, rp=ripple,
    #                 Wn=[passbandFreq, stopbandFreq],
    #                 btype='bandpass', fs=fs,
    #                 analog=False, output='sos')
    return butter(N=N, Wn=[passbandFreq, stopbandFreq],
                  btype='bandpass', output='sos', fs=fs)

if __name__ == '__main__':
    print("decodeUtil.py")