# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\serial_ui\serial.ui'
#
# Created by: PyQt6 UI code generator 6.4.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_serialDialog(object):
    def setupUi(self, serialDialog):
        serialDialog.setObjectName("serialDialog")
        serialDialog.resize(330, 356)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Preferred, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(serialDialog.sizePolicy().hasHeightForWidth())
        serialDialog.setSizePolicy(sizePolicy)
        self.verticalLayout = QtWidgets.QVBoxLayout(serialDialog)
        self.verticalLayout.setSizeConstraint(QtWidgets.QLayout.SizeConstraint.SetFixedSize)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame = QtWidgets.QFrame(parent=serialDialog)
        self.frame.setFrameShape(QtWidgets.QFrame.Shape.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Shadow.Raised)
        self.frame.setObjectName("frame")
        self.gridLayout = QtWidgets.QGridLayout(self.frame)
        self.gridLayout.setObjectName("gridLayout")
        self.moreFrame = QtWidgets.QFrame(parent=self.frame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.moreFrame.sizePolicy().hasHeightForWidth())
        self.moreFrame.setSizePolicy(sizePolicy)
        self.moreFrame.setFrameShape(QtWidgets.QFrame.Shape.StyledPanel)
        self.moreFrame.setFrameShadow(QtWidgets.QFrame.Shadow.Raised)
        self.moreFrame.setObjectName("moreFrame")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.moreFrame)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.lb_inter_byte_timeout = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_inter_byte_timeout.sizePolicy().hasHeightForWidth())
        self.lb_inter_byte_timeout.setSizePolicy(sizePolicy)
        self.lb_inter_byte_timeout.setObjectName("lb_inter_byte_timeout")
        self.gridLayout_2.addWidget(self.lb_inter_byte_timeout, 6, 0, 1, 1)
        self.lb_bytesize = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_bytesize.sizePolicy().hasHeightForWidth())
        self.lb_bytesize.setSizePolicy(sizePolicy)
        self.lb_bytesize.setObjectName("lb_bytesize")
        self.gridLayout_2.addWidget(self.lb_bytesize, 0, 0, 1, 1)
        self.lb_write_timeout = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_write_timeout.sizePolicy().hasHeightForWidth())
        self.lb_write_timeout.setSizePolicy(sizePolicy)
        self.lb_write_timeout.setObjectName("lb_write_timeout")
        self.gridLayout_2.addWidget(self.lb_write_timeout, 5, 0, 1, 1)
        self.box_timeout = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.box_write_timeout = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.box_bytesize = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.box_parity = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.box_stopbits = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.lb_control = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_control.sizePolicy().hasHeightForWidth())
        self.lb_control.setSizePolicy(sizePolicy)
        self.lb_control.setObjectName("lb_control")
        self.gridLayout_2.addWidget(self.lb_control, 4, 0, 1, 1)
        self.box_control = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.lb_timeout = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_timeout.sizePolicy().hasHeightForWidth())
        self.lb_timeout.setSizePolicy(sizePolicy)
        self.lb_timeout.setObjectName("lb_timeout")
        self.gridLayout_2.addWidget(self.lb_timeout, 3, 0, 1, 1)
        self.lb_stopbits = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_stopbits.sizePolicy().hasHeightForWidth())
        self.lb_stopbits.setSizePolicy(sizePolicy)
        self.lb_stopbits.setObjectName("lb_stopbits")
        self.gridLayout_2.addWidget(self.lb_stopbits, 2, 0, 1, 1)
        self.box_inter_byte_timeout = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
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
        self.lb_parity = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_parity.sizePolicy().hasHeightForWidth())
        self.lb_parity.setSizePolicy(sizePolicy)
        self.lb_parity.setObjectName("lb_parity")
        self.gridLayout_2.addWidget(self.lb_parity, 1, 0, 1, 1)
        self.lb_exclusive = QtWidgets.QLabel(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_exclusive.sizePolicy().hasHeightForWidth())
        self.lb_exclusive.setSizePolicy(sizePolicy)
        self.lb_exclusive.setObjectName("lb_exclusive")
        self.gridLayout_2.addWidget(self.lb_exclusive, 7, 0, 1, 1)
        self.box_exclusive = QtWidgets.QComboBox(parent=self.moreFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_exclusive.sizePolicy().hasHeightForWidth())
        self.box_exclusive.setSizePolicy(sizePolicy)
        self.box_exclusive.setObjectName("box_exclusive")
        self.box_exclusive.addItem("")
        self.box_exclusive.addItem("")
        self.gridLayout_2.addWidget(self.box_exclusive, 7, 1, 1, 1)
        self.gridLayout.addWidget(self.moreFrame, 3, 0, 1, 2)
        self.portFrame = QtWidgets.QFrame(parent=self.frame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.portFrame.sizePolicy().hasHeightForWidth())
        self.portFrame.setSizePolicy(sizePolicy)
        self.portFrame.setFrameShape(QtWidgets.QFrame.Shape.StyledPanel)
        self.portFrame.setFrameShadow(QtWidgets.QFrame.Shadow.Raised)
        self.portFrame.setObjectName("portFrame")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.portFrame)
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.box_baudrate = QtWidgets.QComboBox(parent=self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_baudrate.sizePolicy().hasHeightForWidth())
        self.box_baudrate.setSizePolicy(sizePolicy)
        self.box_baudrate.setObjectName("box_baudrate")
        self.box_baudrate.addItem("")
        self.box_baudrate.addItem("")
        self.box_baudrate.addItem("")
        self.gridLayout_3.addWidget(self.box_baudrate, 2, 1, 1, 1)
        self.box_port = QtWidgets.QComboBox(parent=self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.box_port.sizePolicy().hasHeightForWidth())
        self.box_port.setSizePolicy(sizePolicy)
        self.box_port.setMaxCount(2147483647)
        self.box_port.setSizeAdjustPolicy(QtWidgets.QComboBox.SizeAdjustPolicy.AdjustToContentsOnFirstShow)
        self.box_port.setObjectName("box_port")
        self.gridLayout_3.addWidget(self.box_port, 0, 1, 1, 1)
        self.lb_port = QtWidgets.QLabel(parent=self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_port.sizePolicy().hasHeightForWidth())
        self.lb_port.setSizePolicy(sizePolicy)
        self.lb_port.setObjectName("lb_port")
        self.gridLayout_3.addWidget(self.lb_port, 0, 0, 1, 1)
        self.lb_baudrate = QtWidgets.QLabel(parent=self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_baudrate.sizePolicy().hasHeightForWidth())
        self.lb_baudrate.setSizePolicy(sizePolicy)
        self.lb_baudrate.setObjectName("lb_baudrate")
        self.gridLayout_3.addWidget(self.lb_baudrate, 2, 0, 1, 1)
        self.btn_more = QtWidgets.QPushButton(parent=self.portFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_more.sizePolicy().hasHeightForWidth())
        self.btn_more.setSizePolicy(sizePolicy)
        self.btn_more.setObjectName("btn_more")
        self.gridLayout_3.addWidget(self.btn_more, 3, 0, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Minimum)
        self.gridLayout_3.addItem(spacerItem, 3, 1, 1, 1)
        self.gridLayout.addWidget(self.portFrame, 0, 0, 1, 2)
        self.verticalLayout.addWidget(self.frame)
        self.buttonBox = QtWidgets.QDialogButtonBox(parent=serialDialog)
        self.buttonBox.setOrientation(QtCore.Qt.Orientation.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.StandardButton.Cancel|QtWidgets.QDialogButtonBox.StandardButton.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi(serialDialog)
        self.box_timeout.setCurrentIndex(5)
        self.box_write_timeout.setCurrentIndex(5)
        self.box_bytesize.setCurrentIndex(3)
        self.box_parity.setCurrentIndex(0)
        self.box_stopbits.setCurrentIndex(0)
        self.box_control.setCurrentIndex(0)
        self.box_inter_byte_timeout.setCurrentIndex(0)
        self.box_exclusive.setCurrentIndex(0)
        self.box_baudrate.setCurrentIndex(2)
        self.buttonBox.accepted.connect(serialDialog.accept) # type: ignore
        self.buttonBox.rejected.connect(serialDialog.reject) # type: ignore
        QtCore.QMetaObject.connectSlotsByName(serialDialog)

    def retranslateUi(self, serialDialog):
        _translate = QtCore.QCoreApplication.translate
        serialDialog.setWindowTitle(_translate("serialDialog", "串口设置"))
        self.lb_inter_byte_timeout.setText(_translate("serialDialog", "字符间隔超时"))
        self.lb_bytesize.setText(_translate("serialDialog", "数据位"))
        self.lb_write_timeout.setText(_translate("serialDialog", "写超时"))
        self.box_timeout.setItemText(0, _translate("serialDialog", "None"))
        self.box_timeout.setItemText(1, _translate("serialDialog", "1"))
        self.box_timeout.setItemText(2, _translate("serialDialog", "2"))
        self.box_timeout.setItemText(3, _translate("serialDialog", "3"))
        self.box_timeout.setItemText(4, _translate("serialDialog", "4"))
        self.box_timeout.setItemText(5, _translate("serialDialog", "5"))
        self.box_write_timeout.setItemText(0, _translate("serialDialog", "None"))
        self.box_write_timeout.setItemText(1, _translate("serialDialog", "1"))
        self.box_write_timeout.setItemText(2, _translate("serialDialog", "2"))
        self.box_write_timeout.setItemText(3, _translate("serialDialog", "3"))
        self.box_write_timeout.setItemText(4, _translate("serialDialog", "4"))
        self.box_write_timeout.setItemText(5, _translate("serialDialog", "5"))
        self.box_bytesize.setItemText(0, _translate("serialDialog", "5"))
        self.box_bytesize.setItemText(1, _translate("serialDialog", "6"))
        self.box_bytesize.setItemText(2, _translate("serialDialog", "7"))
        self.box_bytesize.setItemText(3, _translate("serialDialog", "8"))
        self.box_parity.setItemText(0, _translate("serialDialog", "无校验(NONE)"))
        self.box_parity.setItemText(1, _translate("serialDialog", "奇校验(ODD)"))
        self.box_parity.setItemText(2, _translate("serialDialog", "偶校验(EVEN)"))
        self.box_parity.setItemText(3, _translate("serialDialog", "1校验(MARK)"))
        self.box_parity.setItemText(4, _translate("serialDialog", "0校验(SPACE)"))
        self.box_stopbits.setItemText(0, _translate("serialDialog", "None"))
        self.box_stopbits.setItemText(1, _translate("serialDialog", "One"))
        self.box_stopbits.setItemText(2, _translate("serialDialog", "OnePointFive"))
        self.box_stopbits.setItemText(3, _translate("serialDialog", "Two"))
        self.lb_control.setText(_translate("serialDialog", "流控制"))
        self.box_control.setItemText(0, _translate("serialDialog", "无"))
        self.box_control.setItemText(1, _translate("serialDialog", "软件流控制"))
        self.box_control.setItemText(2, _translate("serialDialog", "硬件(RTS/CTS)控制"))
        self.box_control.setItemText(3, _translate("serialDialog", "硬件(DSR/DTR)控制"))
        self.lb_timeout.setText(_translate("serialDialog", "读超时"))
        self.lb_stopbits.setText(_translate("serialDialog", "停止位"))
        self.box_inter_byte_timeout.setItemText(0, _translate("serialDialog", "None"))
        self.box_inter_byte_timeout.setItemText(1, _translate("serialDialog", "1"))
        self.box_inter_byte_timeout.setItemText(2, _translate("serialDialog", "2"))
        self.box_inter_byte_timeout.setItemText(3, _translate("serialDialog", "3"))
        self.box_inter_byte_timeout.setItemText(4, _translate("serialDialog", "4"))
        self.box_inter_byte_timeout.setItemText(5, _translate("serialDialog", "5"))
        self.lb_parity.setText(_translate("serialDialog", "校验位"))
        self.lb_exclusive.setText(_translate("serialDialog", "独占访问模式"))
        self.box_exclusive.setItemText(0, _translate("serialDialog", "False"))
        self.box_exclusive.setItemText(1, _translate("serialDialog", "True"))
        self.box_baudrate.setItemText(0, _translate("serialDialog", "9600"))
        self.box_baudrate.setItemText(1, _translate("serialDialog", "115200"))
        self.box_baudrate.setItemText(2, _translate("serialDialog", "4608000"))
        self.lb_port.setText(_translate("serialDialog", "端口"))
        self.lb_baudrate.setText(_translate("serialDialog", "波特率"))
        self.btn_more.setText(_translate("serialDialog", "更多参数∨"))
