import sys
import os
from PyQt6 import QtGui
sys.path.append(os.getcwd()+"\\EMG")
from PyQt6.QtWidgets import QApplication
from PyQt6.QtGui import QCloseEvent
from widget.main_mainWindow.mainWin import MyWindow
from widget.canvas_frame.drawFrame import drawFrame
from widget.serial_dialog.serialDialog import serialDialog
from widget.fft_widget.fftWidget import fftWidget
# utils
from utils.getCom import getCom
from utils.serialRead import serialRead
from utils.dataProcess import dataProcess
from utils.drawFrameUpdate import dataUpdate
from utils.fftProcess import fftProcess
from utils.dataSave import dataSave
import utils.serialUtils as serialUtils

class mainWin(MyWindow):
    def __init__(self) -> None:
        super().__init__()
    
    def initUI(self):
        super().initUI()
        self.drawFrame = drawFrame()
        self.chart_frame.layout().addWidget(self.drawFrame)
        self.drawFrame.changeMode(False)
        self.fftWidget = fftWidget()
        self.layout_fft.layout().addWidget(self.fftWidget)
        self.cb_channel.currentTextChanged.connect(self.cb_channel_currentTextChanged)
        self.cb_rate.currentIndexChanged.connect(self.cb_rate_currentIndexChanged)
        self.cb_xdis.currentIndexChanged.connect(self.cb_xdis_currentIndexChanged)
        self.cb_ydis.currentIndexChanged.connect(self.cb_ydis_currentIndexChanged)
        self.btn_reset.clicked.connect(self.drawFrame.resetChart)
        self.btn_connect.clicked.connect(self.btn_connect_choose)
        self.btn_start.clicked.connect(self.btn_start_choose)
        self.btn_mode.clicked.connect(self.btn_mode_clicked)
        self.sb_fft_x.valueChanged.connect(self.cb_fft_currentIndexChanged)
    
    def cb_fft_currentIndexChanged(self):
        self.fftWidget.cb_fft_y_currentIndexChanged(int(self.sb_fft_x.value()))

    def initValues(self):
        super().initValues()

    def cb_channel_currentTextChanged(self):
        self.drawFrame.updateChart(int(self.cb_channel.currentText()))
        self.fftWidget.updateChart(int(self.cb_channel.currentText()))
    
    def cb_rate_currentIndexChanged(self):
        self.drawFrame.updateRate(int(self.cb_rate.currentText()))
        self.fftWidget.updateRate(int(self.cb_rate.currentText()))
    
    def cb_xdis_currentIndexChanged(self):
        self.drawFrame.updateXdis(int(self.cb_xdis.currentText()))

    def cb_ydis_currentIndexChanged(self):
        self.drawFrame.updateYdis(int(self.cb_ydis.currentText()))
    
    def btn_mode_clicked(self):
        if self.btn_mode.text() == "模式: 时域信号":
            self.btn_mode.setText("模式: 频域分析")
            self.drawFrame.changeMode(True)
            ...
        elif self.btn_mode.text() == "模式: 频域分析":
            self.btn_mode.setText("模式: 时域信号")
            self.drawFrame.changeMode(False)
            ...
    
    def btn_connect_choose(self):
        if self.btn_connect.text() == "连接":
            self.btn_connect_clicked()
        elif self.btn_connect.text() == "断开":
            self.btn_disconnect_clicked()

    def btn_connect_clicked(self):
        if self.ser is not None:
            self.btn_connect_repeat()
            return
        serial_dialog = serialDialog()
        serial_dialog.exec()
        if serial_dialog.result() == serialDialog.DialogCode.Accepted:
            self.port = serial_dialog.getSerParams()
            self.ser = serialUtils.serialOpen(com=self.port['port'], bps=self.port['baudrate'])
            if serialUtils.serialIsOpen(self.ser):
                self.btn_connect_success()
            else:
                self.btn_connect_failure()
        elif serial_dialog.result() == serialDialog.DialogCode.Rejected:
            self.btn_connect_init()

    def btn_disconnect_clicked(self):
        if self.data_save_thread is not None:
            try:
                self.btn_stop_clicked()
            except:
                ...
        if serialUtils.serialClose(self.ser):
            self.btn_connect_init()
            self.btn_connect.setText("连接")
        else:
            print("串口关闭失败!")

    def btn_start_choose(self):
        if self.btn_start.text() == "开始":
            self.btn_start_clicked()
        elif self.btn_start.text() == "暂停":
            self.btn_stop_clicked()

    def btn_start_clicked(self) -> None:
        if not serialUtils.serialIsOpen(self.ser):
            self.btn_start_failure()
            return
        serialUtils.serialWrite(self.ser, state='start', connect='usb', sample_rate=self.cb_rate.currentText(), channel=self.cb_channel.currentText())
        self.serial_read_thread = serialRead(self, self.ser, self.cb_channel.currentText())
        self.data_process_thread = dataProcess(self, self.cb_channel.currentText(), self.cb_rate.currentText(), True if self.btn_filter.text() == "滤波器-ON" else False, self.filterWidget.getParameters())
        self.data_update_thread = dataUpdate(self, self.drawFrame, self.fftWidget)
        # self.fft_process_thread = fftProcess(self, self.cb_channel.currentText(), self.cb_rate.currentText())
        self.data_save_thread = dataSave(self, self.et_filePath.text(), self.cb_channel.currentText())
        self.serial_read_thread.serial_read_data_decode_update_signal.connect(self.data_process_thread.put_data)
        self.serial_read_thread.serial_read_data_decode_update_signal.connect(self.data_save_thread.put_data)
        # self.data_process_thread.data_process_signal.connect(self.data_update_thread.put_data)
        self.data_process_thread.data_process_signal.connect(self.fftWidget.update_chart)
        self.data_process_thread.data_process_signal.connect(self.drawFrame.updateData)
        # self.fft_process_thread.fft_process_signal.connect(self.fftWidget.updateChart)
        self.data_save_thread.data_save_signal.connect(self.data_save_signal_slot)
        self.filterWidget.filter_update_signal.connect(self.data_process_thread.updateFilterParam)
        self.serial_read_thread.start()
        self.data_process_thread.start()
        self.data_update_thread.start()
        # self.fft_process_thread.start()
        self.data_save_thread.start()
        self.btn_start_success()

    def btn_stop_clicked(self):
        serialUtils.serialWrite(self.ser, state='stop')
        self.serial_read_thread.del_thread()
        self.data_process_thread.del_thread()
        self.data_update_thread.del_thread()
        # self.fft_process_thread.del_thread()
        self.data_save_thread.del_thread()
        self.btn_stop_success()

    def btn_filter_clicked(self):
        super(mainWin, self).btn_filter_clicked()
        try:
            self.data_process_thread.isFilter = True if self.btn_filter.text() == "滤波器-ON" else False
        except:
            ...

    def closeEvent(self, a0: QCloseEvent) -> None:
        try:
            self.btn_disconnect_clicked()
        except:
            ...
        return super().closeEvent(a0)

if __name__ == '__main__':
    app = QApplication(sys.argv)    # 创建应用程序
    win = mainWin()    # 创建窗口
    win.show()  # 显示窗口
    sys.exit(app.exec())   # 进入消息循环
