# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\Download\OneDrive - zju.edu.cn\code\EMGexe\EMG\ui\test.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_formtest(object):
    def setupUi(self, formtest):
        formtest.setObjectName("formtest")
        formtest.resize(231, 219)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(formtest)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.groupBox = QtWidgets.QGroupBox(formtest)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName("verticalLayout")
        self.radioButton = QtWidgets.QRadioButton(self.groupBox)
        self.radioButton.setObjectName("radioButton")
        self.verticalLayout.addWidget(self.radioButton)
        self.radioButton_2 = QtWidgets.QRadioButton(self.groupBox)
        self.radioButton_2.setObjectName("radioButton_2")
        self.verticalLayout.addWidget(self.radioButton_2)
        self.verticalLayout_2.addWidget(self.groupBox)
        self.btn_1 = QtWidgets.QPushButton(formtest)
        self.btn_1.setObjectName("btn_1")
        self.verticalLayout_2.addWidget(self.btn_1)
        self.pushButton_2 = QtWidgets.QPushButton(formtest)
        self.pushButton_2.setObjectName("pushButton_2")
        self.verticalLayout_2.addWidget(self.pushButton_2)

        self.retranslateUi(formtest)
        QtCore.QMetaObject.connectSlotsByName(formtest)

    def retranslateUi(self, formtest):
        _translate = QtCore.QCoreApplication.translate
        formtest.setWindowTitle(_translate("formtest", "Form"))
        self.groupBox.setTitle(_translate("formtest", "testGroup"))
        self.radioButton.setText(_translate("formtest", "rb_1"))
        self.radioButton_2.setText(_translate("formtest", "rb_2"))
        self.btn_1.setText(_translate("formtest", "btn_1"))
        self.pushButton_2.setText(_translate("formtest", "btn_2"))