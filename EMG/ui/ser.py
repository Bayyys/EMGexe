# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\ser.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_serDialog(object):
    def setupUi(self, serDialog):
        serDialog.setObjectName("serDialog")
        serDialog.resize(330, 356)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(serDialog.sizePolicy().hasHeightForWidth())
        serDialog.setSizePolicy(sizePolicy)
        self.verticalLayout = QtWidgets.QVBoxLayout(serDialog)
        self.verticalLayout.setSizeConstraint(QtWidgets.QLayout.SetFixedSize)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame = QtWidgets.QFrame(serDialog)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.gridLayout = QtWidgets.QGridLayout(self.frame)
        self.gridLayout.setObjectName("gridLayout")
        self.moreFrame = QtWidgets.QFrame(self.frame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.moreFrame.sizePolicy().hasHeightForWidth())
        self.moreFrame.setSizePolicy(sizePolicy)
        self.moreFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.moreFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.moreFrame.setObjectName("moreFrame")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.moreFrame)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.lb_inter_byte_timeout = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_inter_byte_timeout.sizePolicy().hasHeightForWidth())
        self.lb_inter_byte_timeout.setSizePolicy(sizePolicy)
        self.lb_inter_byte_timeout.setObjectName("lb_inter_byte_timeout")
        self.gridLayout_2.addWidget(self.lb_inter_byte_timeout, 6, 0, 1, 1)
        self.lb_bytesize = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_bytesize.sizePolicy().hasHeightForWidth())
        self.lb_bytesize.setSizePolicy(sizePolicy)
        self.lb_bytesize.setObjectName("lb_bytesize")
        self.gridLayout_2.addWidget(self.lb_bytesize, 0, 0, 1, 1)
        self.lb_write_timeout = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_write_timeout.sizePolicy().hasHeightForWidth())
        self.lb_write_timeout.setSizePolicy(sizePolicy)
        self.lb_write_timeout.setObjectName("lb_write_timeout")
        self.gridLayout_2.addWidget(self.lb_write_timeout, 5, 0, 1, 1)
        self.box_timeout = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_timeout.sizePolicy().hasHeightForWidth())
        self.box_timeout.setSizePolicy(sizePolicy)
        self.box_timeout.setObjectName("box_timeout")
        self.box_timeout.addItem("")
        self.box_timeout.addItem("")
        self.box_timeout.addItem("")
        self.box_timeout.addItem("")
        self.box_timeout.addItem("")
        self.box_timeout.addItem("")
        self.gridLayout_2.addWidget(self.box_timeout, 3, 1, 1, 1)
        self.box_write_timeout = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_write_timeout.sizePolicy().hasHeightForWidth())
        self.box_write_timeout.setSizePolicy(sizePolicy)
        self.box_write_timeout.setObjectName("box_write_timeout")
        self.box_write_timeout.addItem("")
        self.box_write_timeout.addItem("")
        self.box_write_timeout.addItem("")
        self.box_write_timeout.addItem("")
        self.box_write_timeout.addItem("")
        self.box_write_timeout.addItem("")
        self.gridLayout_2.addWidget(self.box_write_timeout, 5, 1, 1, 1)
        self.box_bytesize = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_bytesize.sizePolicy().hasHeightForWidth())
        self.box_bytesize.setSizePolicy(sizePolicy)
        self.box_bytesize.setObjectName("box_bytesize")
        self.box_bytesize.addItem("")
        self.box_bytesize.addItem("")
        self.box_bytesize.addItem("")
        self.box_bytesize.addItem("")
        self.gridLayout_2.addWidget(self.box_bytesize, 0, 1, 1, 1)
        self.box_parity = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_parity.sizePolicy().hasHeightForWidth())
        self.box_parity.setSizePolicy(sizePolicy)
        self.box_parity.setObjectName("box_parity")
        self.box_parity.addItem("")
        self.box_parity.addItem("")
        self.box_parity.addItem("")
        self.box_parity.addItem("")
        self.box_parity.addItem("")
        self.gridLayout_2.addWidget(self.box_parity, 1, 1, 1, 1)
        self.box_stopbits = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_stopbits.sizePolicy().hasHeightForWidth())
        self.box_stopbits.setSizePolicy(sizePolicy)
        self.box_stopbits.setObjectName("box_stopbits")
        self.box_stopbits.addItem("")
        self.box_stopbits.addItem("")
        self.box_stopbits.addItem("")
        self.box_stopbits.addItem("")
        self.gridLayout_2.addWidget(self.box_stopbits, 2, 1, 1, 1)
        self.lb_control = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_control.sizePolicy().hasHeightForWidth())
        self.lb_control.setSizePolicy(sizePolicy)
        self.lb_control.setObjectName("lb_control")
        self.gridLayout_2.addWidget(self.lb_control, 4, 0, 1, 1)
        self.box_control = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_control.sizePolicy().hasHeightForWidth())
        self.box_control.setSizePolicy(sizePolicy)
        self.box_control.setObjectName("box_control")
        self.box_control.addItem("")
        self.box_control.addItem("")
        self.box_control.addItem("")
        self.box_control.addItem("")
        self.gridLayout_2.addWidget(self.box_control, 4, 1, 1, 1)
        self.lb_timeout = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_timeout.sizePolicy().hasHeightForWidth())
        self.lb_timeout.setSizePolicy(sizePolicy)
        self.lb_timeout.setObjectName("lb_timeout")
        self.gridLayout_2.addWidget(self.lb_timeout, 3, 0, 1, 1)
        self.lb_stopbits = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_stopbits.sizePolicy().hasHeightForWidth())
        self.lb_stopbits.setSizePolicy(sizePolicy)
        self.lb_stopbits.setObjectName("lb_stopbits")
        self.gridLayout_2.addWidget(self.lb_stopbits, 2, 0, 1, 1)
        self.box_inter_byte_timeout = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_inter_byte_timeout.sizePolicy().hasHeightForWidth())
        self.box_inter_byte_timeout.setSizePolicy(sizePolicy)
        self.box_inter_byte_timeout.setObjectName("box_inter_byte_timeout")
        self.box_inter_byte_timeout.addItem("")
        self.box_inter_byte_timeout.addItem("")
        self.box_inter_byte_timeout.addItem("")
        self.box_inter_byte_timeout.addItem("")
        self.box_inter_byte_timeout.addItem("")
        self.box_inter_byte_timeout.addItem("")
        self.gridLayout_2.addWidget(self.box_inter_byte_timeout, 6, 1, 1, 1)
        self.lb_parity = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_parity.sizePolicy().hasHeightForWidth())
        self.lb_parity.setSizePolicy(sizePolicy)
        self.lb_parity.setObjectName("lb_parity")
        self.gridLayout_2.addWidget(self.lb_parity, 1, 0, 1, 1)
        self.lb_exclusive = QtWidgets.QLabel(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_exclusive.sizePolicy().hasHeightForWidth())
        self.lb_exclusive.setSizePolicy(sizePolicy)
        self.lb_exclusive.setObjectName("lb_exclusive")
        self.gridLayout_2.addWidget(self.lb_exclusive, 7, 0, 1, 1)
        self.box_exclusive = QtWidgets.QComboBox(self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_exclusive.sizePolicy().hasHeightForWidth())
        self.box_exclusive.setSizePolicy(sizePolicy)
        self.box_exclusive.setObjectName("box_exclusive")
        self.box_exclusive.addItem("")
        self.box_exclusive.addItem("")
        self.gridLayout_2.addWidget(self.box_exclusive, 7, 1, 1, 1)
        self.gridLayout.addWidget(self.moreFrame, 3, 0, 1, 2)
        self.portFrame = QtWidgets.QFrame(self.frame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.portFrame.sizePolicy().hasHeightForWidth())
        self.portFrame.setSizePolicy(sizePolicy)
        self.portFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.portFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.portFrame.setObjectName("portFrame")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.portFrame)
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.box_baudrate = QtWidgets.QComboBox(self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_baudrate.sizePolicy().hasHeightForWidth())
        self.box_baudrate.setSizePolicy(sizePolicy)
        self.box_baudrate.setObjectName("box_baudrate")
        self.box_baudrate.addItem("")
        self.box_baudrate.addItem("")
        self.box_baudrate.addItem("")
        self.gridLayout_3.addWidget(self.box_baudrate, 2, 1, 1, 1)
        self.box_port = QtWidgets.QComboBox(self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_port.sizePolicy().hasHeightForWidth())
        self.box_port.setSizePolicy(sizePolicy)
        self.box_port.setMaxCount(2147483647)
        self.box_port.setSizeAdjustPolicy(QtWidgets.QComboBox.AdjustToContentsOnFirstShow)
        self.box_port.setObjectName("box_port")
        self.gridLayout_3.addWidget(self.box_port, 0, 1, 1, 1)
        self.lb_port = QtWidgets.QLabel(self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_port.sizePolicy().hasHeightForWidth())
        self.lb_port.setSizePolicy(sizePolicy)
        self.lb_port.setObjectName("lb_port")
        self.gridLayout_3.addWidget(self.lb_port, 0, 0, 1, 1)
        self.lb_baudrate = QtWidgets.QLabel(self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_baudrate.sizePolicy().hasHeightForWidth())
        self.lb_baudrate.setSizePolicy(sizePolicy)
        self.lb_baudrate.setObjectName("lb_baudrate")
        self.gridLayout_3.addWidget(self.lb_baudrate, 2, 0, 1, 1)
        self.btn_more = QtWidgets.QPushButton(self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_more.sizePolicy().hasHeightForWidth())
        self.btn_more.setSizePolicy(sizePolicy)
        self.btn_more.setObjectName("btn_more")
        self.gridLayout_3.addWidget(self.btn_more, 3, 0, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_3.addItem(spacerItem, 3, 1, 1, 1)
        self.gridLayout.addWidget(self.portFrame, 0, 0, 1, 2)
        self.verticalLayout.addWidget(self.frame)
        self.buttonBox = QtWidgets.QDialogButtonBox(serDialog)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi(serDialog)
        self.box_timeout.setCurrentIndex(5)
        self.box_write_timeout.setCurrentIndex(5)
        self.box_bytesize.setCurrentIndex(3)
        self.box_parity.setCurrentIndex(0)
        self.box_stopbits.setCurrentIndex(0)
        self.box_control.setCurrentIndex(0)
        self.box_inter_byte_timeout.setCurrentIndex(0)
        self.box_exclusive.setCurrentIndex(0)
        self.box_baudrate.setCurrentIndex(2)
        self.buttonBox.accepted.connect(serDialog.accept)
        self.buttonBox.rejected.connect(serDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(serDialog)

    def retranslateUi(self, serDialog):
        _translate = QtCore.QCoreApplication.translate
        serDialog.setWindowTitle(_translate("serDialog", "串口设置"))
        self.lb_inter_byte_timeout.setText(_translate("serDialog", "字符间隔超时"))
        self.lb_bytesize.setText(_translate("serDialog", "数据位"))
        self.lb_write_timeout.setText(_translate("serDialog", "写超时"))
        self.box_timeout.setItemText(0, _translate("serDialog", "None"))
        self.box_timeout.setItemText(1, _translate("serDialog", "1"))
        self.box_timeout.setItemText(2, _translate("serDialog", "2"))
        self.box_timeout.setItemText(3, _translate("serDialog", "3"))
        self.box_timeout.setItemText(4, _translate("serDialog", "4"))
        self.box_timeout.setItemText(5, _translate("serDialog", "5"))
        self.box_write_timeout.setItemText(0, _translate("serDialog", "None"))
        self.box_write_timeout.setItemText(1, _translate("serDialog", "1"))
        self.box_write_timeout.setItemText(2, _translate("serDialog", "2"))
        self.box_write_timeout.setItemText(3, _translate("serDialog", "3"))
        self.box_write_timeout.setItemText(4, _translate("serDialog", "4"))
        self.box_write_timeout.setItemText(5, _translate("serDialog", "5"))
        self.box_bytesize.setItemText(0, _translate("serDialog", "5"))
        self.box_bytesize.setItemText(1, _translate("serDialog", "6"))
        self.box_bytesize.setItemText(2, _translate("serDialog", "7"))
        self.box_bytesize.setItemText(3, _translate("serDialog", "8"))
        self.box_parity.setItemText(0, _translate("serDialog", "无校验(NONE)"))
        self.box_parity.setItemText(1, _translate("serDialog", "奇校验(ODD)"))
        self.box_parity.setItemText(2, _translate("serDialog", "偶校验(EVEN)"))
        self.box_parity.setItemText(3, _translate("serDialog", "1校验(MARK)"))
        self.box_parity.setItemText(4, _translate("serDialog", "0校验(SPACE)"))
        self.box_stopbits.setItemText(0, _translate("serDialog", "None"))
        self.box_stopbits.setItemText(1, _translate("serDialog", "One"))
        self.box_stopbits.setItemText(2, _translate("serDialog", "OnePointFive"))
        self.box_stopbits.setItemText(3, _translate("serDialog", "Two"))
        self.lb_control.setText(_translate("serDialog", "流控制"))
        self.box_control.setItemText(0, _translate("serDialog", "无"))
        self.box_control.setItemText(1, _translate("serDialog", "软件流控制"))
        self.box_control.setItemText(2, _translate("serDialog", "硬件(RTS/CTS)控制"))
        self.box_control.setItemText(3, _translate("serDialog", "硬件(DSR/DTR)控制"))
        self.lb_timeout.setText(_translate("serDialog", "读超时"))
        self.lb_stopbits.setText(_translate("serDialog", "停止位"))
        self.box_inter_byte_timeout.setItemText(0, _translate("serDialog", "None"))
        self.box_inter_byte_timeout.setItemText(1, _translate("serDialog", "1"))
        self.box_inter_byte_timeout.setItemText(2, _translate("serDialog", "2"))
        self.box_inter_byte_timeout.setItemText(3, _translate("serDialog", "3"))
        self.box_inter_byte_timeout.setItemText(4, _translate("serDialog", "4"))
        self.box_inter_byte_timeout.setItemText(5, _translate("serDialog", "5"))
        self.lb_parity.setText(_translate("serDialog", "校验位"))
        self.lb_exclusive.setText(_translate("serDialog", "独占访问模式"))
        self.box_exclusive.setItemText(0, _translate("serDialog", "False"))
        self.box_exclusive.setItemText(1, _translate("serDialog", "True"))
        self.box_baudrate.setItemText(0, _translate("serDialog", "9600"))
        self.box_baudrate.setItemText(1, _translate("serDialog", "115200"))
        self.box_baudrate.setItemText(2, _translate("serDialog", "4608000"))
        self.lb_port.setText(_translate("serDialog", "端口"))
        self.lb_baudrate.setText(_translate("serDialog", "波特率"))
        self.btn_more.setText(_translate("serDialog", "更多参数∨"))
