# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\canvasTab.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_canvasTab(object):
    def setupUi(self, canvasTab):
        canvasTab.setObjectName("canvasTab")
        canvasTab.resize(681, 299)
        self.verticalLayout = QtWidgets.QVBoxLayout(canvasTab)
        self.verticalLayout.setObjectName("verticalLayout")
        self.buttonFrame = QtWidgets.QFrame(canvasTab)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.buttonFrame.sizePolicy().hasHeightForWidth())
        self.buttonFrame.setSizePolicy(sizePolicy)
        self.buttonFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.buttonFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.buttonFrame.setObjectName("buttonFrame")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.buttonFrame)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.buttonLayout = QtWidgets.QHBoxLayout()
        self.buttonLayout.setObjectName("buttonLayout")
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.buttonLayout.addItem(spacerItem)
        self.btn_1 = QtWidgets.QPushButton(self.buttonFrame)
        self.btn_1.setObjectName("btn_1")
        self.buttonLayout.addWidget(self.btn_1)
        self.btn_2 = QtWidgets.QPushButton(self.buttonFrame)
        self.btn_2.setObjectName("btn_2")
        self.buttonLayout.addWidget(self.btn_2)
        self.verticalLayout_4.addLayout(self.buttonLayout)
        self.verticalLayout.addWidget(self.buttonFrame)
        self.plotFrame = QtWidgets.QFrame(canvasTab)
        self.plotFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.plotFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.plotFrame.setObjectName("plotFrame")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.plotFrame)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.plotLayout = QtWidgets.QHBoxLayout()
        self.plotLayout.setObjectName("plotLayout")
        self.verticalLayout_2.addLayout(self.plotLayout)
        self.verticalLayout.addWidget(self.plotFrame)
        self.indexFrame = QtWidgets.QFrame(canvasTab)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.indexFrame.sizePolicy().hasHeightForWidth())
        self.indexFrame.setSizePolicy(sizePolicy)
        self.indexFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.indexFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.indexFrame.setObjectName("indexFrame")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.indexFrame)
        self.verticalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem1)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setSizeConstraint(QtWidgets.QLayout.SetDefaultConstraint)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.pushButton = QtWidgets.QPushButton(self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton.sizePolicy().hasHeightForWidth())
        self.pushButton.setSizePolicy(sizePolicy)
        self.pushButton.setObjectName("pushButton")
        self.horizontalLayout_2.addWidget(self.pushButton)
        self.pushButton_2 = QtWidgets.QPushButton(self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton_2.sizePolicy().hasHeightForWidth())
        self.pushButton_2.setSizePolicy(sizePolicy)
        self.pushButton_2.setObjectName("pushButton_2")
        self.horizontalLayout_2.addWidget(self.pushButton_2)
        self.lineEdit = QtWidgets.QLineEdit(self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lineEdit.sizePolicy().hasHeightForWidth())
        self.lineEdit.setSizePolicy(sizePolicy)
        self.lineEdit.setObjectName("lineEdit")
        self.horizontalLayout_2.addWidget(self.lineEdit)
        self.label = QtWidgets.QLabel(self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setObjectName("label")
        self.horizontalLayout_2.addWidget(self.label)
        self.pushButton_3 = QtWidgets.QPushButton(self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton_3.sizePolicy().hasHeightForWidth())
        self.pushButton_3.setSizePolicy(sizePolicy)
        self.pushButton_3.setFlat(False)
        self.pushButton_3.setObjectName("pushButton_3")
        self.horizontalLayout_2.addWidget(self.pushButton_3)
        self.pushButton_4 = QtWidgets.QPushButton(self.indexFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton_4.sizePolicy().hasHeightForWidth())
        self.pushButton_4.setSizePolicy(sizePolicy)
        self.pushButton_4.setObjectName("pushButton_4")
        self.horizontalLayout_2.addWidget(self.pushButton_4)
        self.horizontalLayout.addLayout(self.horizontalLayout_2)
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem2)
        self.verticalLayout_5.addLayout(self.horizontalLayout)
        self.verticalLayout.addWidget(self.indexFrame)

        self.retranslateUi(canvasTab)
        QtCore.QMetaObject.connectSlotsByName(canvasTab)

    def retranslateUi(self, canvasTab):
        _translate = QtCore.QCoreApplication.translate
        canvasTab.setWindowTitle(_translate("canvasTab", "Form"))
        self.btn_1.setText(_translate("canvasTab", "button1"))
        self.btn_2.setText(_translate("canvasTab", "button2"))
        self.pushButton.setText(_translate("canvasTab", "<<"))
        self.pushButton_2.setText(_translate("canvasTab", "<"))
        self.label.setText(_translate("canvasTab", "/共__"))
        self.pushButton_3.setText(_translate("canvasTab", ">"))
        self.pushButton_4.setText(_translate("canvasTab", ">>"))
