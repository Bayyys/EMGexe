# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\test\utils\serialUtil\serial_util_test_ui.ui'
#
# Created by: PyQt6 UI code generator 6.4.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_serialUtilTestWin(object):
    def setupUi(self, serialUtilTestWin):
        serialUtilTestWin.setObjectName("serialUtilTestWin")
        serialUtilTestWin.resize(604, 437)
        self.centralwidget = QtWidgets.QWidget(parent=serialUtilTestWin)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.lb_port = QtWidgets.QLabel(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_port.sizePolicy().hasHeightForWidth())
        self.lb_port.setSizePolicy(sizePolicy)
        self.lb_port.setObjectName("lb_port")
        self.horizontalLayout.addWidget(self.lb_port)
        self.cb_port = QtWidgets.QComboBox(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(5)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cb_port.sizePolicy().hasHeightForWidth())
        self.cb_port.setSizePolicy(sizePolicy)
        self.cb_port.setObjectName("cb_port")
        self.horizontalLayout.addWidget(self.cb_port)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.lb_bps = QtWidgets.QLabel(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_bps.sizePolicy().hasHeightForWidth())
        self.lb_bps.setSizePolicy(sizePolicy)
        self.lb_bps.setObjectName("lb_bps")
        self.horizontalLayout_4.addWidget(self.lb_bps)
        self.cb_bps = QtWidgets.QComboBox(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(5)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cb_bps.sizePolicy().hasHeightForWidth())
        self.cb_bps.setSizePolicy(sizePolicy)
        self.cb_bps.setObjectName("cb_bps")
        self.horizontalLayout_4.addWidget(self.cb_bps)
        self.verticalLayout.addLayout(self.horizontalLayout_4)
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.lb_rate = QtWidgets.QLabel(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_rate.sizePolicy().hasHeightForWidth())
        self.lb_rate.setSizePolicy(sizePolicy)
        self.lb_rate.setObjectName("lb_rate")
        self.horizontalLayout_7.addWidget(self.lb_rate)
        self.cb_rate = QtWidgets.QComboBox(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(5)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cb_rate.sizePolicy().hasHeightForWidth())
        self.cb_rate.setSizePolicy(sizePolicy)
        self.cb_rate.setObjectName("cb_rate")
        self.horizontalLayout_7.addWidget(self.cb_rate)
        self.verticalLayout.addLayout(self.horizontalLayout_7)
        self.horizontalLayout_6 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.lb_channel = QtWidgets.QLabel(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_channel.sizePolicy().hasHeightForWidth())
        self.lb_channel.setSizePolicy(sizePolicy)
        self.lb_channel.setObjectName("lb_channel")
        self.horizontalLayout_6.addWidget(self.lb_channel)
        self.cb_channel = QtWidgets.QComboBox(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(5)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cb_channel.sizePolicy().hasHeightForWidth())
        self.cb_channel.setSizePolicy(sizePolicy)
        self.cb_channel.setObjectName("cb_channel")
        self.horizontalLayout_6.addWidget(self.cb_channel)
        self.verticalLayout.addLayout(self.horizontalLayout_6)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.btn_refresh = QtWidgets.QPushButton(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_refresh.sizePolicy().hasHeightForWidth())
        self.btn_refresh.setSizePolicy(sizePolicy)
        self.btn_refresh.setObjectName("btn_refresh")
        self.horizontalLayout_2.addWidget(self.btn_refresh)
        self.btn_filter = QtWidgets.QPushButton(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_filter.sizePolicy().hasHeightForWidth())
        self.btn_filter.setSizePolicy(sizePolicy)
        self.btn_filter.setObjectName("btn_filter")
        self.horizontalLayout_2.addWidget(self.btn_filter)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.btn_connect = QtWidgets.QPushButton(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_connect.sizePolicy().hasHeightForWidth())
        self.btn_connect.setSizePolicy(sizePolicy)
        self.btn_connect.setObjectName("btn_connect")
        self.horizontalLayout_3.addWidget(self.btn_connect)
        self.btn_start = QtWidgets.QPushButton(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_start.sizePolicy().hasHeightForWidth())
        self.btn_start.setSizePolicy(sizePolicy)
        self.btn_start.setObjectName("btn_start")
        self.horizontalLayout_3.addWidget(self.btn_start)
        self.btn_pause = QtWidgets.QPushButton(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_pause.sizePolicy().hasHeightForWidth())
        self.btn_pause.setSizePolicy(sizePolicy)
        self.btn_pause.setObjectName("btn_pause")
        self.horizontalLayout_3.addWidget(self.btn_pause)
        self.btn_disconnect = QtWidgets.QPushButton(parent=self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_disconnect.sizePolicy().hasHeightForWidth())
        self.btn_disconnect.setSizePolicy(sizePolicy)
        self.btn_disconnect.setObjectName("btn_disconnect")
        self.horizontalLayout_3.addWidget(self.btn_disconnect)
        self.verticalLayout.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.et_original = QtWidgets.QTextEdit(parent=self.centralwidget)
        self.et_original.setObjectName("et_original")
        self.horizontalLayout_5.addWidget(self.et_original)
        self.et_decode = QtWidgets.QTextEdit(parent=self.centralwidget)
        self.et_decode.setObjectName("et_decode")
        self.horizontalLayout_5.addWidget(self.et_decode)
        self.verticalLayout.addLayout(self.horizontalLayout_5)
        serialUtilTestWin.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(parent=serialUtilTestWin)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 604, 23))
        self.menubar.setObjectName("menubar")
        serialUtilTestWin.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(parent=serialUtilTestWin)
        self.statusbar.setObjectName("statusbar")
        serialUtilTestWin.setStatusBar(self.statusbar)

        self.retranslateUi(serialUtilTestWin)
        QtCore.QMetaObject.connectSlotsByName(serialUtilTestWin)

    def retranslateUi(self, serialUtilTestWin):
        _translate = QtCore.QCoreApplication.translate
        serialUtilTestWin.setWindowTitle(_translate("serialUtilTestWin", "MainWindow"))
        self.lb_port.setText(_translate("serialUtilTestWin", "串口列表："))
        self.lb_bps.setText(_translate("serialUtilTestWin", "波特率："))
        self.lb_rate.setText(_translate("serialUtilTestWin", "采样率："))
        self.lb_channel.setText(_translate("serialUtilTestWin", "通道数："))
        self.btn_refresh.setText(_translate("serialUtilTestWin", "刷新"))
        self.btn_filter.setText(_translate("serialUtilTestWin", "过滤"))
        self.btn_connect.setText(_translate("serialUtilTestWin", "连接"))
        self.btn_start.setText(_translate("serialUtilTestWin", "开始"))
        self.btn_pause.setText(_translate("serialUtilTestWin", "暂停"))
        self.btn_disconnect.setText(_translate("serialUtilTestWin", "断开"))
