# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\fftSetting_ui\fft_setting.ui'
#
# Created by: PyQt6 UI code generator 6.4.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_formtest(object):
    def setupUi(self, formtest):
        formtest.setObjectName("formtest")
        formtest.resize(466, 154)
        self.gridLayout = QtWidgets.QGridLayout(formtest)
        self.gridLayout.setSizeConstraint(QtWidgets.QLayout.SizeConstraint.SetDefaultConstraint)
        self.gridLayout.setObjectName("gridLayout")
        self.ck_low_3 = QtWidgets.QCheckBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ck_low_3.sizePolicy().hasHeightForWidth())
        self.ck_low_3.setSizePolicy(sizePolicy)
        self.ck_low_3.setObjectName("ck_low_3")
        self.gridLayout.addWidget(self.ck_low_3, 3, 0, 1, 1)
        self.btn_rest = QtWidgets.QPushButton(parent=formtest)
        self.btn_rest.setObjectName("btn_rest")
        self.gridLayout.addWidget(self.btn_rest, 0, 0, 1, 5)
        self.sb_low_2 = QtWidgets.QSpinBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.sb_low_2.sizePolicy().hasHeightForWidth())
        self.sb_low_2.setSizePolicy(sizePolicy)
        self.sb_low_2.setMinimum(1)
        self.sb_low_2.setMaximum(100)
        self.sb_low_2.setProperty("value", 50)
        self.sb_low_2.setObjectName("sb_low_2")
        self.gridLayout.addWidget(self.sb_low_2, 1, 4, 1, 1)
        self.sb_low = QtWidgets.QSpinBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.sb_low.sizePolicy().hasHeightForWidth())
        self.sb_low.setSizePolicy(sizePolicy)
        self.sb_low.setMinimum(1)
        self.sb_low.setMaximum(100)
        self.sb_low.setProperty("value", 50)
        self.sb_low.setObjectName("sb_low")
        self.gridLayout.addWidget(self.sb_low, 1, 1, 1, 1)
        self.ck_low_2 = QtWidgets.QCheckBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ck_low_2.sizePolicy().hasHeightForWidth())
        self.ck_low_2.setSizePolicy(sizePolicy)
        self.ck_low_2.setObjectName("ck_low_2")
        self.gridLayout.addWidget(self.ck_low_2, 1, 3, 1, 1)
        self.sb_low_4 = QtWidgets.QSpinBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.sb_low_4.sizePolicy().hasHeightForWidth())
        self.sb_low_4.setSizePolicy(sizePolicy)
        self.sb_low_4.setMinimum(1)
        self.sb_low_4.setMaximum(100)
        self.sb_low_4.setProperty("value", 50)
        self.sb_low_4.setObjectName("sb_low_4")
        self.gridLayout.addWidget(self.sb_low_4, 3, 1, 1, 1)
        self.ck_low = QtWidgets.QCheckBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ck_low.sizePolicy().hasHeightForWidth())
        self.ck_low.setSizePolicy(sizePolicy)
        self.ck_low.setObjectName("ck_low")
        self.gridLayout.addWidget(self.ck_low, 1, 0, 1, 1)
        self.sb_low_3 = QtWidgets.QSpinBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.sb_low_3.sizePolicy().hasHeightForWidth())
        self.sb_low_3.setSizePolicy(sizePolicy)
        self.sb_low_3.setMinimum(1)
        self.sb_low_3.setMaximum(100)
        self.sb_low_3.setProperty("value", 50)
        self.sb_low_3.setObjectName("sb_low_3")
        self.gridLayout.addWidget(self.sb_low_3, 3, 4, 1, 1)
        self.ck_low_4 = QtWidgets.QCheckBox(parent=formtest)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ck_low_4.sizePolicy().hasHeightForWidth())
        self.ck_low_4.setSizePolicy(sizePolicy)
        self.ck_low_4.setObjectName("ck_low_4")
        self.gridLayout.addWidget(self.ck_low_4, 3, 3, 1, 1)

        self.retranslateUi(formtest)
        QtCore.QMetaObject.connectSlotsByName(formtest)

    def retranslateUi(self, formtest):
        _translate = QtCore.QCoreApplication.translate
        formtest.setWindowTitle(_translate("formtest", "Form"))
        self.ck_low_3.setWhatsThis(_translate("formtest", "islowpass"))
        self.ck_low_3.setText(_translate("formtest", "Ymin"))
        self.btn_rest.setText(_translate("formtest", "重置"))
        self.sb_low_2.setWhatsThis(_translate("formtest", "lowpass"))
        self.sb_low.setWhatsThis(_translate("formtest", "lowpass"))
        self.ck_low_2.setWhatsThis(_translate("formtest", "islowpass"))
        self.ck_low_2.setText(_translate("formtest", "Xmax"))
        self.sb_low_4.setWhatsThis(_translate("formtest", "lowpass"))
        self.ck_low.setWhatsThis(_translate("formtest", "islowpass"))
        self.ck_low.setText(_translate("formtest", "Xmin"))
        self.sb_low_3.setWhatsThis(_translate("formtest", "lowpass"))
        self.ck_low_4.setWhatsThis(_translate("formtest", "islowpass"))
        self.ck_low_4.setText(_translate("formtest", "Ymax"))
