import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial.tools.list_ports
from PyQt6 import QtWidgets
from PyQt6.QtWidgets import QMainWindow, QWidget
# ui
from widget.filter_frame.filterFrame import filterFrame

class mainWin(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.vl = QtWidgets.QVBoxLayout()
        self.btn_setting = QtWidgets.QToolButton()
        self.btn_setting.setText('设置')
        self.btn_setting.setPopupMode(QtWidgets.QToolButton.ToolButtonPopupMode.InstantPopup)
        self.et_setting = QtWidgets.QTextEdit(self)
        self.vl.addWidget(self.btn_setting)
        self.vl.addWidget(self.et_setting)
        self.widget = QWidget()
        self.widget.setLayout(self.vl)
        self.setCentralWidget(self.widget)
        self.setWindowTitle('filterFrame_test')
        # self.btn_setting.clicked.connect(self.btn_setting_clicked)
        self.serialFrame = filterFrame(self)
        act = QtWidgets.QWidgetAction(self)
        act.setDefaultWidget(self.serialFrame)
        self.btn_setting.addAction(act)
        self.serialFrame.ck_baseline.stateChanged.connect(self.filterSettingCKChanged)
        self.serialFrame.ck_low.stateChanged.connect(self.filterSettingCKChanged)
        self.serialFrame.ck_high.stateChanged.connect(self.filterSettingCKChanged)
        self.serialFrame.ck_notch.stateChanged.connect(self.filterSettingCKChanged)
        self.serialFrame.ck_band.stateChanged.connect(self.filterSettingCKChanged)
        self.serialFrame.sb_low.valueChanged.connect(self.filterSettingSBChanged)
        self.serialFrame.sb_high.valueChanged.connect(self.filterSettingSBChanged)
        self.serialFrame.sb_notch_cutoff.valueChanged.connect(self.filterSettingSBChanged)
        self.serialFrame.sb_notch_param.valueChanged.connect(self.filterSettingSBChanged)
        self.serialFrame.sb_band_pass.valueChanged.connect(self.filterSettingSBChanged)
        self.serialFrame.sb_band_stop.valueChanged.connect(self.filterSettingSBChanged)

    
    def filterSettingCKChanged(self):
        changed = "Nothing changed"
        if self.sender().objectName() == 'ck_baseline':
            changed = str('ck_baseline'+str("checked" if self.serialFrame.ck_baseline.isChecked() else "unchecked"))
        elif self.sender().objectName() == 'ck_low':
            changed = str('ck_low'+str("checked" if self.serialFrame.ck_low.isChecked() else "unchecked"))
        elif self.sender().objectName() == 'ck_high':
            changed = str('ck_high'+str("checked" if self.serialFrame.ck_high.isChecked() else "unchecked"))
        elif self.sender().objectName() == 'ck_notch':
            changed = str('ck_notch'+str("checked" if self.serialFrame.ck_notch.isChecked() else "unchecked"))
        elif self.sender().objectName() == 'ck_band':
            changed = str('ck_band'+str("checked" if self.serialFrame.ck_band.isChecked() else "unchecked"))
        self.et_setting.append(changed)
    
    def filterSettingSBChanged(self):
        value_changed = {}
        if self.sender().objectName() == 'sb_low':
            if self.serialFrame.sb_low.value() >= self.serialFrame.sb_high.value():
                self.serialFrame.sb_low.setValue(self.serialFrame.sb_high.value()-1)
            value_changed = {'low':self.serialFrame.sb_low.value()}
        elif self.sender().objectName() == 'sb_high':
            if self.serialFrame.sb_high.value() <= self.serialFrame.sb_low.value():
                self.serialFrame.sb_high.setValue(self.serialFrame.sb_low.value()+1)
            value_changed =  {'high':self.serialFrame.sb_high.value()}
        elif self.sender().objectName() == 'sb_notch_cutoff':
            value_changed =  {'notch_cutoff':self.serialFrame.sb_notch_cutoff.value(), 'notch_param':self.serialFrame.sb_notch_param.value()}
        elif self.sender().objectName() == 'sb_notch_param':
            value_changed =  {'notch_cutoff':self.serialFrame.sb_notch_cutoff.value(), 'notch_param':self.serialFrame.sb_notch_param.value()}
        elif self.sender().objectName() == 'sb_band_pass':
            if self.serialFrame.sb_band_pass.value() >= self.serialFrame.sb_band_stop.value():
                self.serialFrame.sb_band_pass.setValue(self.serialFrame.sb_band_stop.value()-1)
            value_changed =  {'band_pass':self.serialFrame.sb_band_pass.value(), 'band_stop':self.serialFrame.sb_band_stop.value()}
        elif self.sender().objectName() == 'sb_band_stop':
            if self.serialFrame.sb_band_pass.value() >= self.serialFrame.sb_band_stop.value():
                self.serialFrame.sb_band_stop.setValue(self.serialFrame.sb_band_pass.value()+1)
            value_changed =  {'band_pass':self.serialFrame.sb_band_pass.value(), 'band_stop':self.serialFrame.sb_band_stop.value()}
        self.et_setting.append(str(value_changed))


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = mainWin()
    win.show()
    sys.exit(app.exec())
    