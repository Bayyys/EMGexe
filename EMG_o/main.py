import os
import sys
import numpy as np
import utils.globalParams as glo
# 串口操作
import utils.serialUtil as serUtil
from PyQt5 import uic
from PyQt5.QtCore import QDateTime, Qt, QTimer, pyqtSignal
from PyQt5.QtWidgets import (QApplication, QComboBox, QFileDialog, QMainWindow,
                             QVBoxLayout, QWidget, QWidgetAction)
from ui.drawFrame import FFTCanvas, FFTThread, drawFrame, drawFrameFile
from ui.filterFrame import filterWidget
from ui.mainWindow import Ui_MainWindow
from ui.serFrame import serDialog


class MyWindow(QMainWindow, Ui_MainWindow):
    XDIS_SIGNAL = pyqtSignal()
    YDIS_SIGNAL = pyqtSignal()
    SAMPLE_RATE_SIGNAL = pyqtSignal()

    def __init__(self):
        super().__init__()
        if glo.ui_flag:
            self.ui = uic.loadUi('ui/mainWindow.ui', self)
        else:
            self.setupUi(self)
        self.initWidgetUI()  # 初始化控件UI
        self.initDATA()  # 初始化数据
        self.initUIFunc()   # 初始化UI界面
        self.tabWidget.setCurrentIndex(0)  # 默认显示第一个tab
        self.tabWidget.currentChanged.connect(self.updateUIIndex)  # tab切换
    
    def initWidgetUI(self):  # 初始化控件UI
        """初始化控件UI"""
        # 初始化
        self.filterWidget = filterWidget()
        # self.filterWidget.ui = uic.loadUi('ui/filter.ui', self.filterWidget)
        # 控件槽函数连接
        self.filterWidget.ck_baseline.clicked.connect(
            self.ck_all_filter_clicked)    # 基线开关
        self.filterWidget.ck_low.clicked.connect(
            self.ck_all_filter_clicked)    # 高通滤波器开关
        self.filterWidget.ck_high.clicked.connect(
            self.ck_all_filter_clicked)    # 高通滤波器开关
        self.filterWidget.ck_notch.clicked.connect(
            self.ck_all_filter_clicked)   # 陷波滤波器开关
        self.filterWidget.ck_band.clicked.connect(
            self.ck_all_filter_clicked)    # 带通滤波器开关
        self.filterWidget.sb_low.valueChanged.connect(
            self.sb_low_valueChanged)  # 高通滤波器截止频率
        self.filterWidget.sb_high.valueChanged.connect(
            self.sb_high_valueChanged)  # 高通滤波器截止频率
        self.filterWidget.sb_notch_cutoff.valueChanged.connect(
            self.sb_notch_valueChanged)   # 陷波滤波器截止频率
        self.filterWidget.sb_notch_param.valueChanged.connect(
            self.sb_notch_valueChanged)  # 陷波滤波器参数
        self.file_sb_band_pass.valueChanged.connect(
            self.sb_band_valueChanged)   # 带通滤波器通带频率
        self.filterWidget.sb_band_stop.valueChanged.connect(
            self.sb_band_valueChanged)   # 带通滤波器阻带频率
        # 添加控件
        act = QWidgetAction(self)
        act.setDefaultWidget(self.filterWidget)
        self.tb_filter.addAction(act)
        # tb_filter 点击状态改变
        self.tb_filter.clicked.connect(self.tb_filter_clicked)

    def tb_filter_clicked(self):
        """tb_filter 点击状态改变"""
        if glo.isFilter:
            self.tb_filter.setText('滤波器-OFF')
            glo.isFilter = False
        else:
            self.tb_filter.setText('滤波器-ON')
            glo.isFilter = True
            
    
    def action_ser_set_clicked(self):   # 菜单栏-串口-配置
        """菜单栏-串口-配置"""
        self.serDialog = serDialog()
        self.serDialog.show()
        result = self.serDialog.exec_()
        if result == 1:
            glo.port, glo.baudrate, glo.bytesize, glo.parity, glo.stopbits, glo.timeout, glo.control, glo.write_timeout, glo.inter_byte_timeout, glo.exclusive = port, baudrate, bytesize, parity, stopbits, timeout, control, write_timeout, inter_byte_timeout, exclusive = self.serDialog.getSerParams() 
            self.btn_connect.click()

    def initUIFunc(self):   # 初始化UI界面&槽函数
        """初始化UI界面&槽函数"""
        self.initMenuUIFunc()   # 菜单栏控件槽函数初始化
        self.initRealUIFunc()   # 实时检测界面控件槽函数初始化
        self.initFileUIFunc()   # 文件处理界面控件槽函数初始化

    def initMenuUIFunc(self):  # 菜单栏控件槽函数初始化
        """菜单栏控件槽函数初始化"""
        # 菜单栏部分
        # 文件
        self.file_open_menu.triggered.connect(
            self.action_open_clicked)    # 菜单栏-打开文件
        self.file_save_menu.triggered.connect(lambda: ...)  # 菜单栏-文件-保存文件   # WAIT
        # 连接
        self.connect_ser_menu.triggered.connect(self.action_ser_set_clicked)  # 菜单栏-串口-配置
        # Tab 部分

    def initRealUIFunc(self):  # 实时检测界面控件槽函数初始化
        """实时检测界面控件槽函数初始化"""
        #=========== 实时检测部分 ===========#
        # 连接部分
        self.btn_connect.clicked.connect(self.btn_connect_clicked)   # 连接按钮
        self.btn_disconnect.clicked.connect(
            self.btn_disconnect_clicked)    # 断开连接按钮
        # self.serDialog.box_port.currentIndexChanged.connect(
            # self.box_port_changed)  # Com 端口选择    # WAIT
        # 按钮部分
        self.btn_start.clicked.connect(self.btn_start_clicked)  # 开始按钮
        self.btn_stop.clicked.connect(self.btn_stop_clicked)    # 停止按钮
        # 其他部分
        self.btn_filePath.clicked.connect(
            self.btn_filePath_clicked)    # 文件路径按钮
        self.btn_reset.clicked.connect(self.btn_reset_clicked)  # 重置按钮
        # 信号处理部分
        self.sb_pointLow.editingFinished.connect(self.sb_pointLow_editingFinished)  # 低点阈值
        self.box_ydis.currentIndexChanged.connect(
            self.box_all_DIS_changed)  # Y轴显示范围
        self.box_xdis.currentIndexChanged.connect(
            self.box_all_DIS_changed)  # X轴显示范围
        self.box_sample_rate.currentIndexChanged.connect(
            self.box_sample_rate_changed)  # 采样率
        self.box_channel_num.currentIndexChanged.connect(
            self.box_channel_num_changed)  # 通道数

    def initFileUIFunc(self):  # 文件处理界面控件槽函数初始化
        """文件处理界面控件槽函数初始化"""
        #=========== 历史数据部分 ===========#
        # 文件操作部分
        self.file_btn_open.clicked.connect(
            self.action_open_clicked)    # 打开文件按钮
        self.file_btn_dataload.setVisible(False)    # 数据加载按钮: 隐藏
        self.file_btn_dataload.clicked.connect(
            self.file_btn_dataload_clicked)  # 数据加载按钮
        self.file_btn_draw.clicked.connect(self.file_btn_draw_clicked)  # 绘制按钮
        self.file_btn_reset.clicked.connect(
            self.file_btn_reset_clicked)    # 重置按钮
        # 信号处理部分
        self.file_box_ydis.currentIndexChanged.connect(
            self.file_box_all_DIS_changed)  # Y轴显示范围
        self.file_box_xdis.currentIndexChanged.connect(
            self.file_box_all_DIS_changed)  # X轴显示范围
        self.file_btn_delete.clicked.connect(
            self.file_btn_delete_clicked)  # 删除部分数据点按钮
        self.file_ck_baseline.clicked.connect(
            self.file_ck_all_filter_clicked)    # 基线开关
        self.file_ck_low.clicked.connect(
            self.file_ck_all_filter_clicked)    # 高通滤波器开关
        self.file_ck_high.clicked.connect(
            self.file_ck_all_filter_clicked)    # 高通滤波器开关
        self.file_ck_notch.clicked.connect(
            self.file_ck_all_filter_clicked)   # 陷波滤波器开关
        self.file_ck_band.clicked.connect(
            self.file_ck_all_filter_clicked)    # 带通滤波器开关
        self.file_sb_low.valueChanged.connect(
            self.sb_low_valueChanged)  # 高通滤波器截止频率
        self.file_sb_high.valueChanged.connect(
            self.sb_high_valueChanged)  # 高通滤波器截止频率
        self.file_sb_notch_cutoff.valueChanged.connect(
            self.sb_notch_valueChanged)   # 陷波滤波器截止频率
        self.file_sb_notch_param.valueChanged.connect(
            self.sb_notch_valueChanged)  # 陷波滤波器参数
        self.file_sb_band_pass.valueChanged.connect(
            self.sb_band_valueChanged)   # 带通滤波器通带频率
        self.file_sb_band_stop.valueChanged.connect(
            self.sb_band_valueChanged)   # 带通滤波器阻带频率
        self.file_box_sample_rate.currentIndexChanged.connect(
            self.file_box_sample_rate_changed)  # 采样率

    #============================= 实时检测界面 =============================#

    #-------------------------------  初始化 -------------------------------#

    def initDATA(self):  # 实时检测界面控件初始化
        """实时检测界面控件初始化"""
        # 串口参数设置部分
        self.searchCom()    # 启动串口更新线程
        # 连接部分
        self.lb_connect.setStyleSheet('QLabel{color: gray}')    # 连接状态(绿色)
        self.lb_start.setStyleSheet('QLabel{color: gray}')  # 启动状态(绿色)
        # 信息显示部分
        self.et_filePath.setText(os.getcwd())   # 文件路径(默认为当前路径)
        # 信号处理部分
        self.updateGlobalData()   # 更新全局参数
        # 图表显示列表部分
        self.chartFrameList = []    # 图表显示列表
        self.initChartFrame()   # 初始化图表显示列表
        # FFT部分
        self.fftcanvas = FFTCanvas(self)    # FFT图表
        self.layoutFFT.addWidget(self.fftcanvas)    # FFT图表添加到布局中

    def updateGlobalData(self): # 更新全局参数
        """更新全局参数"""
        glo.channel_num = int(self.box_channel_num.currentText())   # 通道数
        glo.sample_rate = int(self.box_sample_rate.currentText())   # 采样率
        glo.XDIS_INDEX = int(self.box_xdis.currentText())  # X轴显示范围索引
        glo.XDIS = glo.XDIS_INDEX * glo.sample_rate   # X轴显示范围
        glo.YDIS = int(self.box_ydis.currentText()) # Y轴显示范围
        glo.isLowPassFilter = self.filterWidget.ck_low.isChecked()   # 高通滤波器开关
        glo.isHighPassFilter = self.filterWidget.ck_high.isChecked() # 高通滤波器开关
        glo.isNotchFilter = self.filterWidget.ck_notch.isChecked()   # 陷波滤波器开关
        glo.isBandPassFilter = self.filterWidget.ck_band.isChecked() # 带通滤波器开关
        glo.highFilter_high = self.filterWidget.sb_high.value()  # 高通滤波器截止频率
        glo.lowFilter_low = self.filterWidget.sb_low.value() # 高通滤波器截止频率
        glo.notchFilter_cutoff = self.filterWidget.sb_notch_cutoff.value()   # 陷波滤波器截止频率
        glo.notchFilter_param = self.filterWidget.sb_notch_param.value() # 陷波滤波器参数
        glo.bandFilter_pass = self.filterWidget.sb_band_pass.value()  # 带通滤波器通带频率
        glo.bandFilter_stop = self.filterWidget.sb_band_stop.value() # 带通滤波器阻带频率

    def initChartFrame(self):   # 初始化图表 Frame
        """初始化图表 Frame"""      
        for i in range(self.layoutChart.count()):
            self.layoutChart.itemAt(i).widget().deleteLater()   # 清空垂直布局内的表格elf.chartFrameList.clear() # 清空绘图Canvas列表
        self.chartFrameList.clear() # 清空绘图Canvas列表
        for i in range(2):
            chartFrameItem = drawFrame(self)
            chartFrameItem.lb_num.setText('CH'+str(i+1))    # 设置通道号
            self.XDIS_SIGNAL.connect(chartFrameItem.updateXlim)   # 连接信号: X轴显示范围更新
            self.YDIS_SIGNAL.connect(chartFrameItem.updateYlim)  # 连接信号: Y轴显示范围更新
            self.chartFrameList.append(chartFrameItem)  # 添加到图像显示列表
            self.layoutChart.addWidget(chartFrameItem)

    def updateUIIndex(self): # 更新控件索引
        """更新控件索引"""
        #----------------- 实时检测部分 -----------------#
        self.box_ydis.setCurrentIndex(self.box_ydis.findText(str(glo.YDIS)))    # Y轴显示范围(1000)： [20, 50, 100, 200, 500, 1000, 2000, 200000]
        self.box_xdis.setCurrentIndex(self.box_xdis.findText(str(glo.XDIS_INDEX)))    # X轴显示范围(1)： [1, 2, 3, 4]
        self.box_sample_rate.setCurrentIndex(self.box_sample_rate.findText(str(glo.sample_rate))) # 采样率(8000)： [250, 500, 1000, 2000, 4000, 6000, 8000, 16000]
        self.box_channel_num.setCurrentIndex(
            self.box_channel_num.findText(str(glo.channel_num)))  # 通道数(2)： [2, 32]
        self.filterWidget.ck_baseline.setChecked(
            glo.isBaseline)   # 基线检测开关(True)
        self.filterWidget.ck_low.setChecked(
            glo.isLowPassFilter)   # 低通滤波器开关(False)
        self.filterWidget.ck_high.setChecked(
            glo.isHighPassFilter)   # 高通滤波器开关(True)
        self.filterWidget.ck_notch.setChecked(
            glo.isNotchFilter)  # 陷波滤波器开关(True)
        self.filterWidget.ck_band.setChecked(
            glo.isBandPassFilter)   # 带通滤波器开关(True)
        self.filterWidget.sb_low.setValue(glo.lowFilter_low)    # 低通滤波器截止频率(50)
        self.filterWidget.sb_high.setValue(
            glo.highFilter_high)    # 高通滤波器截止频率(1)
        self.filterWidget.sb_notch_cutoff.setValue(
            glo.notchFilter_cutoff)   # 陷波滤波器截止频率(50)
        self.filterWidget.sb_notch_param.setValue(
            glo.notchFilter_param)    # 陷波滤波器参数(10)
        self.filterWidget.sb_band_pass.setValue(
            glo.bandFilter_pass)   # 带通滤波器通带频率(1)
        self.filterWidget.sb_band_stop.setValue(
            glo.bandFilter_stop)  # 带通滤波器阻带频率(50)
        #----------------- 文件检测部分 -----------------#
        self.file_box_ydis.setCurrentIndex(self.file_box_ydis.findText(str(glo.YDIS)))    # Y轴显示范围(1000)： [20, 50, 100, 200, 500, 1000, 2000, 200000]
        self.file_box_xdis.setCurrentIndex(self.file_box_xdis.findText(str(glo.XDIS_INDEX)))    # X轴显示范围(1)： [1, 2, 3, 4]
        self.file_box_sample_rate.setCurrentIndex(self.file_box_sample_rate.findText(str(glo.sample_rate))) # 采样率(8000)： [250, 500, 1000, 2000, 4000, 6000, 8000, 16000]
        self.file_box_channel_num.setCurrentIndex(
            self.file_box_channel_num.findText(str(glo.channel_num)))  # 通道数(2)： [2, 32]
        self.file_ck_baseline.setChecked(glo.isBaseline)   # 基线检测开关(True)
        self.file_ck_low.setChecked(glo.isLowPassFilter)   # 低通滤波器开关(False)
        self.file_ck_high.setChecked(glo.isHighPassFilter)   # 高通滤波器开关(True)
        self.file_ck_notch.setChecked(glo.isNotchFilter)  # 陷波滤波器开关(True)
        self.file_ck_band.setChecked(glo.isBandPassFilter)   # 带通滤波器开关(True)
        self.file_sb_low.setValue(glo.lowFilter_low)    # 低通滤波器截止频率(50)
        self.file_sb_high.setValue(glo.highFilter_high)    # 高通滤波器截止频率(1)
        self.file_sb_notch_cutoff.setValue(glo.notchFilter_cutoff)   # 陷波滤波器截止频率(50)
        self.file_sb_notch_param.setValue(glo.notchFilter_param)    # 陷波滤波器参数(10)
        self.file_sb_band_pass.setValue(glo.bandFilter_pass)   # 带通滤波器通带频率(1)
        self.file_sb_band_stop.setValue(glo.bandFilter_stop)  # 带通滤波器阻带频率(50)
        # -------------------------------------------------#

    def action_open_clicked(self):  # 打开文件事件
        """打开文件事件"""
        if glo.scan:    # 如果已经连接设备，提示先断开连接
            self.statusBar.showMessage('请先断开连接', 3000)
            return
        dirpath, type = QFileDialog.getOpenFileName(self,
                                                    caption='打开文件', directory=self.et_filePath.text(),
                                                    filter='纯文本(*.txt) ;; CSV(*.csv) ;; All Files (*) ', initialFilter='纯文本(*.txt)')
        if glo.load_data(dirpath, type):    # 加载文件
            self.file_btn_draw.setText('绘制')
            # self.initUIIndex()  # 初始化控件索引
            self.updateUIIndex()    # 更新控件索引
            self.tabWidget.setCurrentIndex(1)   # 切换到文件读取界面
            self.file_et_path.setText(dirpath)  # 显示文件路径
            self.group_state_file.setEnabled(True)
            self.group_draw_file.setEnabled(True)
            self.group_setting_file.setEnabled(True)
            self.group_params_file.setEnabled(False)
            glo.initFilterParams()  # 初始化滤波器参数
            self.initDATAFile()
            for i in range(glo.channel_num):
                self.chartFrameList[i].close()
            self.chartFrameList.clear()
            # 清空垂直布局内的表格
            self.chartFrameList = []    # 绘图Canvas列表
            self.initChartFrameFile()   # 初始化 fileCanvas
            self.statusBar.showMessage('文件加载成功 (' + dirpath + ')', 5000)

    def btn_connect_clicked(self):  # 连接按钮点击事件
        """连接按钮点击事件"""
        if glo.get_scan():   # 当前已经连接, 避免重复连接
            self.statusBar.showMessage("已连接, 无需重复连接", 3000)
            return
        if glo.port is None:    # 未选择串口
            self.action_ser_set_clicked()  # 展开串口选择框
            return
        # 连接串口
        glo.set_ser(serUtil.serialOpen(
            glo.port.split(' ')[0],    # 串口号
            glo.baudrate,  # 波特率
            glo.timeout))  # 超时时间
        if not self.savePathDirCreate():  # 创建文件夹
            return  # 创建失败, 退出
        if serUtil.serialIsOpen(glo.get_ser()):    # 连接成功
            glo.init_history()  # 初始化历史数据
            self.statusBar.showMessage("串口连接成功, 点击<开始>按钮进行测量", 5000)
            self.group_state_file.setEnabled(False)
            self.group_params_file.setEnabled(False)
            glo.set_scan(True)  # 设置连接状态 True
            glo.set_com(glo.port.split(' ')[0])   # 设置连接的串口号
            self.btn_start.setEnabled(True) # 启用开始按钮
            self.btn_disconnect.setEnabled(True)    # 启用断开连接按钮
            self.lb_connect.setText(glo.get_com())  # 显示连接的串口号
            self.lb_connect.setStyleSheet('color: balck')   # 设置连接状态颜色(黑色)
            self.lb_start.setText('等待测量')   # 设置开始/暂停状态文本
            self.lb_start.setStyleSheet('color: green') # 设置开始/暂停状态颜色(绿色)
            # self.initUIIndex()  # 初始化控件索引
            self.updateUIIndex()    # 更新控件索引
            self.updateGlobalData() # 更新全局变量
            serUtil.serialClose(glo.get_ser)    # 关闭串口
        else:
            # 连接失败
            glo.port = None
            self.lb_connect.setText('无法连接') # 设置连接状态文本
            self.lb_connect.setStyleSheet('color: red') # 设置连接状态颜色(红色)
            self.statusBar.showMessage("连接失败", 3000)
            return
        # for i in range(self.layoutChart.count()):
        #     self.layoutChart.itemAt(i).widget().deleteLater()   # 清空垂直布局内的表格
        # self.chartFrameList.clear() # 清空绘图Canvas列表
        # self.initChartFrame()   # 初始化绘图Canvas

    def btn_disconnect_clicked(self):   # 断开连接按钮点击事件
        """断开连接按钮点击事件"""
        if glo.get_scan():
            glo.set_connected(False)    # 设置连接状态 False
            serUtil.serialClose(glo.get_ser())  # 关闭串口
            glo.set_com('') # 清空连接的串口号
            self.saveHistoryQueue() # 保存历史数据
            self.lb_connect.setText('等待连接') # 设置连接状态文本
            self.lb_connect.setStyleSheet('color: gray')    # 设置连接状态颜色(灰色)
            self.lb_start.setText('尚未连接')   # 设置开始/暂停状态文本
            self.lb_start.setStyleSheet('color: gray')  # 设置开始/暂停状态颜色(灰色)
            self.btn_start.setEnabled(False)    # 禁用开始按钮
            self.btn_stop.setEnabled(False) # 禁用停止按钮
            self.box_sample_rate.setEnabled(True)   # 启用采样率下拉框
            self.box_channel_num.setEnabled(True)   # 启用通道数下拉框
            glo.set_scan(False)
            self.renameDataFile()
        else:
            # 当前未进行测量, 无需断开连接
            self.statusBar.showMessage("未连接, 无需断开连接", 3000)
            return

    def btn_start_clicked(self):    # 开始按钮点击事件
        """开始按钮点击事件"""
        if glo.get_connected():   # 当前已经连接, 避免重复连接
            self.statusBar.showMessage("已连接, 无需重复连接", 3000)
            return
        # 连接串口
        glo.set_ser(serUtil.serialOpen(glo.port.split(' ')[0],    # 串口号
                                       glo.baudrate,  # 波特率
                                       glo.timeout))  # 超时时间
        if serUtil.serialIsOpen(glo.get_ser()):    # 连接成功
            self.initChartFrame()   # 初始化绘图Canvas
            glo.sendMessage(state='start', connect='usb',
                            sample_rate=glo.sample_rate, channel=glo.channel_num)   # 发送开始测量命令
            glo.initFilterParams()  # 初始化滤波参数

            # 连接成功后的操作
            self.connSuccess()  # 
            self.connSeialThread()  # 连接串口线程
            self.fftThread()    # FFT线程
            self.saveTimer = QTimer()   # 保存数据定时器
            self.saveTimer.timeout.connect(self.saveHistoryQueue)
            self.saveTimer.start(50)    # 50ms保存一次数据
            self.box_sample_rate.setEnabled(False)  # 禁用采样率下拉框
            self.box_channel_num.setEnabled(False)  # 禁用通道数下拉框
            self.statusBar.showMessage("开始测量", 5000)
        else:
            # 连接失败
            glo.set_connected(False)
            serUtil.serialClose(glo.get_ser())

    def btn_stop_clicked(self):  # 停止按钮点击事件: 关闭串口、停止线程
        """停止按钮点击事件
        
        flow:
        ----------------
        - 关闭线程
            - 关闭串口读取线程
            - 关闭FFT线程
        - 关闭串口
            - 发送停止测量命令
            - 关闭串口
            - 停止保存数据定时器
        - UI操作
        """
        self.serialRead.terminate() # 关闭串口读取线程
        self.fftthread.terminate()  # 关闭FFT线程
        glo.sendMessage(state='stop')   # 发送停止测量命令
        serUtil.serialClose(glo.get_ser())  # 关闭串口
        self.saveTimer.stop()   # 停止保存数据定时器
        self.btn_stop.setEnabled(False) # 禁用停止按钮
        self.lb_start.setText('已暂停')  # 设置开始/暂停状态文本
        self.lb_start.setStyleSheet('color: red')   # 设置开始/暂停状态颜色(红色)

    def box_port_changed(self):  # 串口号改变事件, 且当前串口断开
        """串口号改变事件, 且当前串口断开"""
        if glo.get_scan():  # 当前已连接，需要断开连接
            self.btn_disconnect_clicked()
            self.btn_connect_clicked()

    def savePathDirCreate(self):  # 创建数据存储文件夹以及文件
        """创建数据存储文件夹以及文件"""
        self.datalength = 0
        path = self.et_filePath.text()+'/MeasureData'
        self.saveFileName = path+QDateTime.currentDateTime().toString('/yy-MM-dd-hhmm')+'.txt'
        if not os.path.exists(path):
            os.makedirs(path)
        try:
            with open(self.saveFileName, 'a') as f:
                return True
        except:
            self.statusBar.showMessage("文件创建失败", 5000)
            return False
        ...

    def renameDataFile(self):   # 重命名数据文件
        """重命名数据文件"""
        if os.path.exists(self.saveFileName):
            fsize = os.path.getsize(self.saveFileName)
            if fsize < 1024:
                os.remove(self.saveFileName)
            else:
                os.rename(self.saveFileName, self.saveFileName.replace('.txt', '-'+str(glo.sample_rate)+'Hz'+'-'+str(int(self.datalength / glo.sample_rate))+'s.txt'))
        else:
            self.statusBar.showMessage("Error:文件不存在!", 5000)
        pointFileName = self.saveFileName.replace('.txt', '-'+str(glo.sample_rate)+'Hz'+'-'+str(int(self.datalength / glo.sample_rate))+'s-points.txt')
        try:
            with open(pointFileName, 'ab') as f:
                for i in range(len(self.chartFrameList)):
                    temp = np.array(self.chartFrameList[i].canvasTab.data_tab_point)
                    if temp.size > 0:
                        np.savetxt(f, np.column_stack(temp), fmt='%d')
                    else:
                        np.savetxt(f, np.array([0]), fmt='%d')
        except:
            self.statusBar.showMessage("<识别点文件>创建失败", 5000)
        
    def btn_filePath_clicked(self):   # 文件路径按钮点击事件
        """文件路径按钮点击事件"""
        path = QFileDialog.getExistingDirectory(
            None, "选取文件夹", self.et_filePath.text()+'/MeasureData')  # 起始路径
        if path != "":
            self.et_filePath.setText(path)

    def btn_reset_clicked(self):    # 重置按钮点击事件
        """重置按钮点击事件"""
        for chartFrame in self.chartFrameList:
            chartFrame.canvas.zoomReset()
            chartFrame.setVisible(True)
            # chartFrame.chart.zoomReset()

    def sb_pointLow_editingFinished(self):  # 识别点下限滑动条编辑完成事件
        """识别点下限滑动条编辑完成事件"""
        glo.pointLow = self.sb_pointLow.value()

    def box_all_DIS_changed(self):  # 坐标轴轴显示范围改变事件
        """坐标轴轴显示范围改变事件"""
        if self.sender().objectName() == 'box_ydis':
            glo.YDIS = int(self.box_ydis.currentText())
            self.YDIS_SIGNAL.emit()
            self.statusBar.showMessage(
                'Y轴显示范围: ' + self.box_ydis.currentText() + 'μV', 3000)
        elif self.sender().objectName() == 'box_xdis':
            glo.XDIS_INDEX = int(self.box_xdis.currentText())
            glo.XDIS = glo.XDIS_INDEX * glo.sample_rate
            self.XDIS_SIGNAL.emit()
            self.statusBar.showMessage(
                'X轴显示范围: ' + str(glo.XDIS) + 'ms', 3000)

    def ck_all_filter_clicked(self):  # 滤波器选择事件
        """滤波器选择事件"""
        if self.sender().objectName() == 'ck_baseline':
            glo.isBaseline = self.sender().property('checked')
            self.statusBar.showMessage(
                    '基线移除: ' + ('开启' if glo.isBaseline else '关闭'), 3000)
        elif self.sender().objectName() == 'ck_low':
            glo.isLowPassFilter = self.sender().property('checked')
            self.statusBar.showMessage(
                    '低通滤波器: ' + ('开启' if glo.isLowPassFilter else '关闭'), 3000)
        elif self.sender().objectName() == 'ck_high':
            glo.isHighPassFilter = self.sender().property('checked')
            self.statusBar.showMessage(
                    '高通滤波器: ' + ('开启' if glo.isHighPassFilter else '关闭'), 3000)
        elif self.sender().objectName() == 'ck_notch':
            glo.isNotchFilter = self.sender().property('checked')
            self.statusBar.showMessage(
                    '陷波滤波器: ' + ('开启' if glo.isNotchFilter else '关闭'), 3000)
        elif self.sender().objectName() == 'ck_band':
            glo.isBandPassFilter = self.sender().property('checked')
            self.statusBar.showMessage(
                    '带通滤波器: ' + ('开启' if glo.isBandPassFilter else '关闭'), 3000)

    def sb_low_valueChanged(self):     # 低通滤波器截止频率改变事件
        """低通滤波器截止频率改变事件"""
        glo.lowFilter_low = self.filterWidget.sb_low.value()
        glo.lowFilterUpdate()

    def sb_high_valueChanged(self):     # 高通滤波器截止频率改变事件
        """高通滤波器截止频率改变事件"""
        glo.highFilter_high = self.filterWidget.sb_high.value()
        glo.highFilterUpdate()

    def sb_notch_valueChanged(self):    # 陷波滤波器截止频率和参数改变事件
        """陷波滤波器截止频率和参数改变事件"""
        glo.notchFilter_cutoff = self.filterWidget.sb_notch_cutoff.value()
        glo.notchFilter_param = self.filterWidget.sb_notch_param.value()
        glo.notchFilterUpdate()

    def sb_band_valueChanged(self):    # 带通滤波器通带频率和阻带频率改变事件
        """带通滤波器通带频率和阻带频率改变事件"""
        glo.bandFilter_pass = self.filterWidget.sb_band_pass.value()
        glo.bandFilter_stop = self.filterWidget.sb_band_stop.value()
        if glo.bandFilter_stop < glo.bandFilter_pass:
            glo.bandFilter_stop += glo.bandFilter_pass
        glo.bandFilterUpdate()

    def box_sample_rate_changed(self):  # 采样率改变事件
        """采样率改变事件"""
        glo.sample_rate = int(self.box_sample_rate.currentText())
        self.statusBar.showMessage(
            '采样率: ' + str(glo.sample_rate) + 'Hz', 3000)

    def box_channel_num_changed(self):  # 通道数改变事件
        """通道数改变事件"""
        self.statusBar.showMessage(
            '通道数: ' + self.box_channel_num.currentText(), 3000)
        glo.channel_num = int(self.box_channel_num.currentText())

    #---------------------------- 串口线程操作 --------------------------#

    def searchCom(self):    # 启动更新串口号线程 --> initData()
        """启动更新串口号线程"""
        self.getComThread = serUtil.getCom()
        self.getComThread.comUpdate.connect(self.updateCom)
        self.getComThread.start()

    def updateCom(self, port_list):  # 更新串口号   --> 更新串口号线程：串口列表发生变化时触发
        """更新串口号
        
        Attribute:
        ----------
            port_list: 串口列表
        """

        if glo.get_scan():  # 当前已经连接, 避免重复连接
            if glo.get_com() not in [port_list[i][0] for i in range(len(port_list))]:
                return
            else:
                self.btn_disconnect_clicked()
        # self.serDialog.box_port.setCurrentIndex(0)
        ...

    def connSuccess(self):  # 连接成功  --> 连接按钮点击事件：连接成功时触发
        """连接成功后,进行ui操作"""
        glo.set_connected(True)  # 设置连接状态
        self.btn_stop.setEnabled(True)  # 开启停止按钮
        self.lb_start.setText('正在测量')
        self.lb_start.setStyleSheet('color: green')

    def connSeialThread(self):  # 连接串口读取线程  --> 连接按钮点击事件：连接成功时触发
        """连接串口读取线程"""
        if glo.channel_num == 2:
            self.serialRead = serUtil.serialRead2()  # 串口读取线程-双通道
        else:
            self.serialRead = serUtil.serialRead()  # 串口读取线程-32通道
        self.serialRead.serDisconnect.connect(
            self.btn_stop_clicked)    # 信号连接: 串口断开 -> 停止按钮点击事件
        self.serialRead.dateReadUpdate.connect(
            self.updateData)   # 信号连接: 串口读取数据 -> 更新图表
        self.serialRead.start()  # 开启串口读取线程

    def fftThread(self):    # 启动FFT线程  --> 连接按钮点击事件：连接成功时触发
        """启动FFT线程"""
        self.fftthread = FFTThread(self)
        self.fftthread.fftSignal.connect(self.fftcanvas.updateFFT)
        self.fftthread.start()

    def updateData(self, data_list):    # 更新数据及图表    --> 串口读取线程：串口读取数据时触发
        """更新数据及图表
        
        Attribute:
        ----------
            data_list: 读取的数据列表
        """

        glo.history.put(data_list)  # 保存历史数据(Queue)
        # time1 = time.time()
        for i in range(len(self.chartFrameList)):
            if len(data_list[i]) > 0:
                self.chartFrameList[i].addData(data_list[i])

    def saveHistoryQueue(self): # 保存历史数据(Queue) --> 1)测量状态50ms触发; 2)停止时触发.
        """保存历史数据(Queue)"""
        with open(self.saveFileName, 'ab') as f:
            while not glo.history.empty():
                value = glo.history.get()
                self.datalength += len(value[0])
                np.savetxt(f, np.transpose(value), fmt='%lf', delimiter=' ')

    #============================ 历史数据界面 ============================#

    def file_btn_dataload_clicked(self):  # 历史数据界面：数据加载按钮点击事件
        """历史数据界面：数据加载按钮点击事件"""
        self.file_btn_draw.setText('绘制')
        # self.initUIIndex()
        self.updateUIIndex()    # 更新控件索引
        self.file_btn_dataload.setVisible(False)
        self.file_et_path.setText("实时检测数据")
        self.group_state_file.setEnabled(True)
        self.group_setting_file.setEnabled(True)
        self.group_draw_file.setEnabled(True)
        self.group_params_file.setEnabled(False)
        glo.initFilterParams()
        self.initDATAFile()
        for i in range(2):
            self.chartFrameList[i].close()
        self.chartFrameList.clear()
        # 清空垂直布局内的表格
        self.chartFrameList = []
        self.initChartFrameFile()
        self.statusBar.showMessage("实时检测数据加载成功", 3000)

    def initDATAFile(self):  # 历史数据界面初始化数据
        """历史数据界面初始化数据"""
        # 信号处理部分
        glo.YDIS = int(self.file_box_ydis.currentText())
        glo.XDIS_INDEX = int(self.file_box_xdis.currentText())
        glo.XDIS = glo.XDIS_INDEX * glo.sample_rate
        glo.isHighPassFilter = self.file_ck_high.isChecked()
        glo.isNotchFilter = self.file_ck_notch.isChecked()
        glo.isBandPassFilter = self.file_ck_band.isChecked()
        glo.sample_rate = int(self.file_box_sample_rate.currentText())

    def initChartFrameFile(self):   # 初始化历史数据界面的图表显示列表
        """初始化历史数据界面的图表显示列表"""
        for i in range(2):
            chartFrameItem = drawFrameFile(self)
            self.XDIS_SIGNAL.connect(chartFrameItem.updateXlim)
            self.YDIS_SIGNAL.connect(chartFrameItem.updateYlim)
            if i == 2:
                chartFrameItem.canvas.line.set_color('orange')
            self.SAMPLE_RATE_SIGNAL.connect(chartFrameItem.updateSampleRate)
            chartFrameItem.history = glo.history[i, :]
            self.chartFrameList.append(chartFrameItem)
            self.layoutChart.addWidget(chartFrameItem)

    def file_btn_draw_clicked(self):    # 历史数据绘制按钮事件
        """历史数据绘制按钮事件"""
        self.group_params_file.setEnabled(True)
        if self.file_btn_draw.text() == '绘制':
            for i in range(2):
                self.chartFrameList[i].drawFile()
            self.file_btn_draw.setText('重新绘制')
        else:
            for i in range(2):
                self.chartFrameList[i].drawFileAgain()
    
    def file_btn_reset_clicked(self):    # 重置按钮点击事件
        """重置按钮点击事件"""
        for chartFrame in self.chartFrameList:
            chartFrame.canvas.zoomReset()
            chartFrame.setVisible(True)
            # chartFrame.chart.zoomReset()

    def file_btn_delete_clicked(self):  # 删除区间按钮点击事件
        """删除区间按钮点击事件"""
        # self.file_btn_reset_clicked()
        delete_from = int(self.file_sb_delete_low.text())
        delete_to = int(self.file_sb_delete_high.text())
        if delete_from == '' or delete_to == '':
            return
        if delete_from >= delete_to:
            self.statusBar.showMessage("区间设置错误", 3000)
        if delete_to >= glo.history.shape[1] / glo.sample_rate:
            delete_to = glo.history.shape[1] / glo.sample_rate
            return
        glo.history = np.delete(glo.history, range(
            delete_from * glo.sample_rate, delete_to * glo.sample_rate), axis=1)
        self.statusBar.showMessage(
            "删除区间：" + str(delete_from) + "s - " + str(delete_to) + "s 成功", 3000)
        for i in range(2):
            self.chartFrameList[i].history = glo.history[i, :]
            self.chartFrameList[i].drawFile()
            # chartFrame.chart.zoomReset()

    def file_box_sample_rate_changed(self):  # 采样率改变事件
        """采样率改变事件"""
        glo.sample_rate = int(self.file_box_sample_rate.currentText())
        self.SAMPLE_RATE_SIGNAL.emit()
        self.statusBar.showMessage("采样率设置为：" + str(glo.sample_rate), 3000)

    def file_box_all_DIS_changed(self):  # 坐标轴轴显示范围改变事件
        """坐标轴轴显示范围改变事件"""
        if self.sender().objectName() == 'file_box_ydis':
            glo.YDIS = int(self.file_box_ydis.currentText())
            self.YDIS_SIGNAL.emit()
            self.statusBar.showMessage("Y轴显示范围设置为: " + str(glo.YDIS), 3000)
        elif self.sender().objectName() == 'file_box_xdis':
            glo.XDIS_INDEX = int(self.file_box_xdis.currentText())
            glo.XDIS = glo.XDIS_INDEX * glo.sample_rate
            # self.XDIS_SIGNAL.emit()
            self.statusBar.showMessage(
                "X轴显示范围设置为: " + str(glo.XDIS) + '. 点击<重新绘制>按钮进行图像更新！', 3000)

    def file_ck_all_filter_clicked(self):  # 滤波器选择事件
        """滤波器选择事件"""
        if self.sender().objectName() == 'file_ck_baseline':
            glo.isBaseline = self.file_ck_baseline.isChecked()
            self.statusBar.showMessage(
                '基线移除: ' + ('开启' if glo.isBaseline else '关闭') + '. 点击<重新绘制>按钮进行图像更新！', 3000)
        elif self.sender().objectName() == 'file_ck_low':
            glo.isLowPassFilter = self.file_ck_low.isChecked()
            self.statusBar.showMessage(
                '低通滤波: ' + ('开启' if glo.isLowPassFilter else '关闭') + '. 点击<重新绘制>按钮进行图像更新！', 3000)
        elif self.sender().objectName() == 'file_ck_low':
            glo.isHighPassFilter = self.file_ck_low.isChecked()
            self.statusBar.showMessage(
                '高通滤波: ' + ('开启' if glo.isHighPassFilter else '关闭') + '. 点击<重新绘制>按钮进行图像更新！', 3000)
        elif self.sender().objectName() == 'file_ck_notch':
            glo.isNotchFilter = self.file_ck_notch.isChecked()
            self.statusBar.showMessage(
                '陷波滤波: ' + ('开启' if glo.isNotchFilter else '关闭') + '. 点击<重新绘制>按钮进行图像更新！', 3000)
        elif self.sender().objectName() == 'file_ck_band':
            glo.isBandPassFilter = self.file_ck_band.isChecked()
            self.statusBar.showMessage(
                '带通滤波: ' + ('开启' if glo.isBandPassFilter else '关闭') + '. 点击<重新绘制>按钮进行图像更新！', 3000)

    #============================ 窗口线程重写 ============================#

    def keyPressEvent(self, e):  # 重写键盘事件: 按下ESC键关闭串口
        """重写键盘事件: 按下ESC键关闭串口"""
        if e.key() == Qt.Key.Key_Escape:
            if glo.connected:
                self.btn_stop_clicked()
        elif e.key() == Qt.Key.Key_R:
            if ~glo.connected:
                self.btn_start_clicked()
        elif e.key() == Qt.Key.Key_Return:
            self.btn_reset_clicked()

    def closeEvent(self, event):    # 重写关闭事件: 关闭串口
        """重写关闭事件: 关闭串口"""
        try:
            self.serialRead.terminate()
            self.getComThread.terminate()
            self.renameDataFile()
            try:
                glo.sendMessage(state='stop')
            except:
                ...
        except:
            ...


if __name__ == '__main__':
    glo.__init__()  # 初始化全局变量
    app = QApplication(sys.argv)    # 创建应用程序
    win = MyWindow()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec_())   # 进入消息循环
