import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial.tools.list_ports
from PyQt6 import QtWidgets
from PyQt6.QtCore import pyqtSignal
# ui
from ui.filterSetting_ui.filter import Ui_formtest
# utils

class filterFrame(QtWidgets.QFrame, Ui_formtest):
    filter_update_signal = pyqtSignal(list)
    def __init__(self, parent) -> None:
        super().__init__()
        self.parent = parent
        self.initUI()
    
    def initUI(self):
        self.setupUi(self)
        self.ck_baseline.stateChanged.connect(self.filterSettingCKChanged)
        self.ck_low.stateChanged.connect(self.filterSettingCKChanged)
        self.ck_high.stateChanged.connect(self.filterSettingCKChanged)
        self.ck_notch.stateChanged.connect(self.filterSettingCKChanged)
        self.ck_band.stateChanged.connect(self.filterSettingCKChanged)
        self.sb_low.valueChanged.connect(self.filterSettingSBChanged)
        self.sb_high.valueChanged.connect(self.filterSettingSBChanged)
        self.sb_notch_cutoff.valueChanged.connect(self.filterSettingSBChanged)
        self.sb_notch_param.valueChanged.connect(self.filterSettingSBChanged)
        self.sb_band_pass.valueChanged.connect(self.filterSettingSBChanged)
        self.sb_band_stop.valueChanged.connect(self.filterSettingSBChanged)

    def getParameters(self):
        return {
            "isbaseline": self.ck_baseline.isChecked(),
            "islowpass": self.ck_low.isChecked(),
            "ishighpass": self.ck_high.isChecked(),
            "isbandstop": self.ck_notch.isChecked(),
            "isbandpass": self.ck_band.isChecked(),
            "lowpass": [int(self.sb_low.text())],
            "highpass": [int(self.sb_high.text())],
            "bandstop": [int(self.sb_notch_cutoff.text()) - int(self.sb_notch_param.text()), int(self.sb_notch_cutoff.text()) + int(self.sb_notch_param.text())],
            "bandpass": [int(self.sb_band_pass.text()), int(self.sb_band_stop.text())],
        }
    
    def filterSettingCKChanged(self):
        check_changed = [self.sender().property('whatsThis'), True if self.sender().isChecked() else False]
        self.filter_update_signal.emit(check_changed)

    def filterSettingSBChanged(self):
        value_changed = []
        if self.sender().objectName() == 'sb_low':
            if self.sb_low.value() <= self.sb_high.value():
                self.sb_low.setValue(self.sb_high.value()+1)
            value_changed = [int(self.sb_low.value())]
        elif self.sender().objectName() == 'sb_high':
            if self.sb_low.value() <= self.sb_high.value():
                self.sb_high.setValue(self.sb_low.value()-1)
            value_changed =  [int(self.sb_high.value())]
        elif self.sender().objectName() == 'sb_notch_cutoff' or self.sender().objectName() == 'sb_notch_param':
            value_changed =  [int(self.sb_notch_cutoff.value()) - int(self.sb_notch_param.value()), int(self.sb_notch_cutoff.value()) + int(self.sb_notch_param.value())]
        elif self.sender().objectName() == 'sb_band_pass':
            if self.sb_band_pass.value() >= self.sb_band_stop.value():
                self.sb_band_pass.setValue(self.sb_band_stop.value()-1)
            value_changed =  [int(self.sb_band_pass.value()), int(self.sb_band_stop.value())]
        elif self.sender().objectName() == 'sb_band_stop':
            if self.sb_band_pass.value() >= self.sb_band_stop.value():
                self.sb_band_stop.setValue(self.sb_band_pass.value()+1)
            value_changed =  [int(self.sb_band_pass.value()), int(self.sb_band_stop.value())]
        self.filter_update_signal.emit([self.sender().property('whatsThis'), value_changed])

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    filter = filterFrame(app)
    filter.show()
    sys.exit(app.exec())