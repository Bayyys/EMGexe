# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\draw.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(668, 350)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Form.sizePolicy().hasHeightForWidth())
        Form.setSizePolicy(sizePolicy)
        Form.setMinimumSize(QtCore.QSize(0, 350))
        self.verticalLayout = QtWidgets.QVBoxLayout(Form)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.chartFrame = QtWidgets.QFrame(Form)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.chartFrame.sizePolicy().hasHeightForWidth())
        self.chartFrame.setSizePolicy(sizePolicy)
        self.chartFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.chartFrame.setFrameShadow(QtWidgets.QFrame.Plain)
        self.chartFrame.setObjectName("chartFrame")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.chartFrame)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.chartTopFrame = QtWidgets.QFrame(self.chartFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.chartTopFrame.sizePolicy().hasHeightForWidth())
        self.chartTopFrame.setSizePolicy(sizePolicy)
        self.chartTopFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.chartTopFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.chartTopFrame.setObjectName("chartTopFrame")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.chartTopFrame)
        self.horizontalLayout.setContentsMargins(6, 0, 6, 0)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.lb_num = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_num.setMinimumSize(QtCore.QSize(15, 32))
        self.lb_num.setFrameShape(QtWidgets.QFrame.NoFrame)
        self.lb_num.setObjectName("lb_num")
        self.horizontalLayout.addWidget(self.lb_num)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.lb_minInfo = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_minInfo.setObjectName("lb_minInfo")
        self.horizontalLayout.addWidget(self.lb_minInfo)
        self.lb_min = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_min.setObjectName("lb_min")
        self.horizontalLayout.addWidget(self.lb_min)
        self.lb_min_unit = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_min_unit.setObjectName("lb_min_unit")
        self.horizontalLayout.addWidget(self.lb_min_unit)
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem1)
        self.lb_maxInfo = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_maxInfo.setObjectName("lb_maxInfo")
        self.horizontalLayout.addWidget(self.lb_maxInfo)
        self.lb_max = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_max.setObjectName("lb_max")
        self.horizontalLayout.addWidget(self.lb_max)
        self.lb_max_unit = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_max_unit.setObjectName("lb_max_unit")
        self.horizontalLayout.addWidget(self.lb_max_unit)
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem2)
        self.lb_rmsInfo = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_rmsInfo.setObjectName("lb_rmsInfo")
        self.horizontalLayout.addWidget(self.lb_rmsInfo)
        self.lb_rms = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_rms.setObjectName("lb_rms")
        self.horizontalLayout.addWidget(self.lb_rms)
        self.lb_rms_unit = QtWidgets.QLabel(self.chartTopFrame)
        self.lb_rms_unit.setObjectName("lb_rms_unit")
        self.horizontalLayout.addWidget(self.lb_rms_unit)
        spacerItem3 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem3)
        self.btn_test = QtWidgets.QPushButton(self.chartTopFrame)
        self.btn_test.setMaximumSize(QtCore.QSize(80, 16777215))
        self.btn_test.setObjectName("btn_test")
        self.horizontalLayout.addWidget(self.btn_test)
        self.btn_tab = QtWidgets.QPushButton(self.chartTopFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_tab.sizePolicy().hasHeightForWidth())
        self.btn_tab.setSizePolicy(sizePolicy)
        self.btn_tab.setMaximumSize(QtCore.QSize(80, 16777215))
        self.btn_tab.setObjectName("btn_tab")
        self.horizontalLayout.addWidget(self.btn_tab)
        self.btn_reset = QtWidgets.QPushButton(self.chartTopFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_reset.sizePolicy().hasHeightForWidth())
        self.btn_reset.setSizePolicy(sizePolicy)
        self.btn_reset.setMaximumSize(QtCore.QSize(35, 16777215))
        self.btn_reset.setObjectName("btn_reset")
        self.horizontalLayout.addWidget(self.btn_reset)
        self.btn_close = QtWidgets.QPushButton(self.chartTopFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_close.sizePolicy().hasHeightForWidth())
        self.btn_close.setSizePolicy(sizePolicy)
        self.btn_close.setMaximumSize(QtCore.QSize(35, 16777215))
        self.btn_close.setObjectName("btn_close")
        self.horizontalLayout.addWidget(self.btn_close)
        self.verticalLayout_2.addWidget(self.chartTopFrame)
        self.plotFrame = QtWidgets.QFrame(self.chartFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.plotFrame.sizePolicy().hasHeightForWidth())
        self.plotFrame.setSizePolicy(sizePolicy)
        self.plotFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.plotFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.plotFrame.setObjectName("plotFrame")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.plotFrame)
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.canvasFrame = QtWidgets.QFrame(self.plotFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(1)
        sizePolicy.setHeightForWidth(self.canvasFrame.sizePolicy().hasHeightForWidth())
        self.canvasFrame.setSizePolicy(sizePolicy)
        self.canvasFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.canvasFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.canvasFrame.setObjectName("canvasFrame")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.canvasFrame)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setSpacing(0)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.canvasLayout = QtWidgets.QVBoxLayout()
        self.canvasLayout.setObjectName("canvasLayout")
        self.verticalLayout_4.addLayout(self.canvasLayout)
        self.verticalLayout_3.addWidget(self.canvasFrame)
        self.canvasTabFrame = QtWidgets.QFrame(self.plotFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(3)
        sizePolicy.setHeightForWidth(self.canvasTabFrame.sizePolicy().hasHeightForWidth())
        self.canvasTabFrame.setSizePolicy(sizePolicy)
        self.canvasTabFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.canvasTabFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.canvasTabFrame.setObjectName("canvasTabFrame")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.canvasTabFrame)
        self.verticalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_5.setSpacing(0)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.canvasTabLayout = QtWidgets.QVBoxLayout()
        self.canvasTabLayout.setSizeConstraint(QtWidgets.QLayout.SetDefaultConstraint)
        self.canvasTabLayout.setObjectName("canvasTabLayout")
        self.verticalLayout_5.addLayout(self.canvasTabLayout)
        self.verticalLayout_3.addWidget(self.canvasTabFrame)
        self.verticalLayout_2.addWidget(self.plotFrame)
        self.verticalLayout.addWidget(self.chartFrame)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.lb_num.setText(_translate("Form", "1"))
        self.lb_minInfo.setText(_translate("Form", "min:"))
        self.lb_min.setText(_translate("Form", "0.000"))
        self.lb_min_unit.setText(_translate("Form", "μV"))
        self.lb_maxInfo.setText(_translate("Form", "max:"))
        self.lb_max.setText(_translate("Form", "0.000"))
        self.lb_max_unit.setText(_translate("Form", "μV"))
        self.lb_rmsInfo.setText(_translate("Form", "rms:"))
        self.lb_rms.setText(_translate("Form", "0.000"))
        self.lb_rms_unit.setText(_translate("Form", "μV"))
        self.btn_test.setText(_translate("Form", "识别"))
        self.btn_tab.setText(_translate("Form", "∨显示"))
        self.btn_reset.setText(_translate("Form", "〇"))
        self.btn_close.setText(_translate("Form", "×"))
