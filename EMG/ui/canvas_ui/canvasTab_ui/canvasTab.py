# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\canvas_ui\canvasTab_ui\canvasTab.ui'
#
# Created by: PyQt6 UI code generator 6.4.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_canvasTab(object):
    def setupUi(self, canvasTab):
        canvasTab.setObjectName("canvasTab")
        canvasTab.resize(681, 297)
        self.verticalLayout = QtWidgets.QVBoxLayout(canvasTab)
        self.verticalLayout.setContentsMargins(0, -1, 0, 0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.plotFrame2 = QtWidgets.QFrame(parent=canvasTab)
        self.plotFrame2.setFrameShape(QtWidgets.QFrame.Shape.StyledPanel)
        self.plotFrame2.setFrameShadow(QtWidgets.QFrame.Shadow.Raised)
        self.plotFrame2.setObjectName("plotFrame2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.plotFrame2)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.verticalLayout.addWidget(self.plotFrame2)
        self.plotFrame = QtWidgets.QScrollArea(parent=canvasTab)
        self.plotFrame.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.plotFrame.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.plotFrame.setWidgetResizable(True)
        self.plotFrame.setObjectName("plotFrame")
        self.plotLayout = QtWidgets.QWidget()
        self.plotLayout.setGeometry(QtCore.QRect(0, 0, 679, 259))
        self.plotLayout.setObjectName("plotLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.plotLayout)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.plotLayout2 = QtWidgets.QHBoxLayout()
        self.plotLayout2.setSizeConstraint(QtWidgets.QLayout.SizeConstraint.SetFixedSize)
        self.plotLayout2.setObjectName("plotLayout2")
        self.horizontalLayout.addLayout(self.plotLayout2)
        self.plotFrame.setWidget(self.plotLayout)
        self.verticalLayout.addWidget(self.plotFrame)
        self.indexFrame = QtWidgets.QFrame(parent=canvasTab)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Preferred, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.indexFrame.sizePolicy().hasHeightForWidth())
        self.indexFrame.setSizePolicy(sizePolicy)
        self.indexFrame.setFrameShape(QtWidgets.QFrame.Shape.StyledPanel)
        self.indexFrame.setFrameShadow(QtWidgets.QFrame.Shadow.Raised)
        self.indexFrame.setObjectName("indexFrame")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.indexFrame)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.btn_head = QtWidgets.QPushButton(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_head.sizePolicy().hasHeightForWidth())
        self.btn_head.setSizePolicy(sizePolicy)
        self.btn_head.setMaximumSize(QtCore.QSize(30, 23))
        self.btn_head.setObjectName("btn_head")
        self.horizontalLayout_2.addWidget(self.btn_head)
        self.btn_pre = QtWidgets.QPushButton(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_pre.sizePolicy().hasHeightForWidth())
        self.btn_pre.setSizePolicy(sizePolicy)
        self.btn_pre.setMaximumSize(QtCore.QSize(23, 23))
        self.btn_pre.setObjectName("btn_pre")
        self.horizontalLayout_2.addWidget(self.btn_pre)
        self.sb_page = QtWidgets.QSpinBox(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.sb_page.sizePolicy().hasHeightForWidth())
        self.sb_page.setSizePolicy(sizePolicy)
        self.sb_page.setMaximumSize(QtCore.QSize(40, 23))
        self.sb_page.setButtonSymbols(QtWidgets.QAbstractSpinBox.ButtonSymbols.NoButtons)
        self.sb_page.setKeyboardTracking(True)
        self.sb_page.setProperty("showGroupSeparator", False)
        self.sb_page.setSuffix("")
        self.sb_page.setMinimum(1)
        self.sb_page.setMaximum(9999)
        self.sb_page.setObjectName("sb_page")
        self.horizontalLayout_2.addWidget(self.sb_page)
        self.lb_page = QtWidgets.QLabel(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_page.sizePolicy().hasHeightForWidth())
        self.lb_page.setSizePolicy(sizePolicy)
        self.lb_page.setMaximumSize(QtCore.QSize(40, 23))
        self.lb_page.setObjectName("lb_page")
        self.horizontalLayout_2.addWidget(self.lb_page)
        self.lb_all = QtWidgets.QLabel(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lb_all.sizePolicy().hasHeightForWidth())
        self.lb_all.setSizePolicy(sizePolicy)
        self.lb_all.setMaximumSize(QtCore.QSize(60, 23))
        self.lb_all.setObjectName("lb_all")
        self.horizontalLayout_2.addWidget(self.lb_all)
        self.btn_next = QtWidgets.QPushButton(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_next.sizePolicy().hasHeightForWidth())
        self.btn_next.setSizePolicy(sizePolicy)
        self.btn_next.setMaximumSize(QtCore.QSize(23, 23))
        self.btn_next.setFlat(False)
        self.btn_next.setObjectName("btn_next")
        self.horizontalLayout_2.addWidget(self.btn_next)
        self.btn_tail = QtWidgets.QPushButton(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_tail.sizePolicy().hasHeightForWidth())
        self.btn_tail.setSizePolicy(sizePolicy)
        self.btn_tail.setMaximumSize(QtCore.QSize(30, 23))
        self.btn_tail.setObjectName("btn_tail")
        self.horizontalLayout_2.addWidget(self.btn_tail)
        self.btn_to = QtWidgets.QPushButton(parent=self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Policy.Fixed, QtWidgets.QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btn_to.sizePolicy().hasHeightForWidth())
        self.btn_to.setSizePolicy(sizePolicy)
        self.btn_to.setMaximumSize(QtCore.QSize(40, 23))
        self.btn_to.setObjectName("btn_to")
        self.horizontalLayout_2.addWidget(self.btn_to)
        self.verticalLayout.addWidget(self.indexFrame, 0, QtCore.Qt.AlignmentFlag.AlignHCenter)

        self.retranslateUi(canvasTab)
        QtCore.QMetaObject.connectSlotsByName(canvasTab)

    def retranslateUi(self, canvasTab):
        _translate = QtCore.QCoreApplication.translate
        canvasTab.setWindowTitle(_translate("canvasTab", "Form"))
        self.btn_head.setText(_translate("canvasTab", "<<"))
        self.btn_pre.setText(_translate("canvasTab", "<"))
        self.lb_page.setText(_translate("canvasTab", "---"))
        self.lb_all.setText(_translate("canvasTab", "/共__"))
        self.btn_next.setText(_translate("canvasTab", ">"))
        self.btn_tail.setText(_translate("canvasTab", ">>"))
        self.btn_to.setToolTip(_translate("canvasTab", "当前最多存储20个标记点，跳转时请注意！"))
        self.btn_to.setText(_translate("canvasTab", "跳转"))
