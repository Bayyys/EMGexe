import sys
import os
sys.path.append(os.getcwd()+"\\EMG")
import serial.tools.list_ports
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow
from PyQt6 import QtCore, QtWidgets
from utils.dataSave import dataSave
from widget.main_mainWindow.mainWin import MyWindow


class DataSaveTest(MyWindow):
    def __init__(self) -> None:
        super().__init__()
        self.initUI()
    
    def initUI(self):
        super().initUI()
        self.btn_start.clicked.connect(self.btn_start_clicked)
        self.btn_stop.clicked.connect(self.btn_stop_clicked)
    
    def btn_start_clicked(self):
        self.dataSave = dataSave(self, self.et_filePath.text())
        self.dataSave.start()
        print("开始保存数据")
    
    def btn_stop_clicked(self):
        try:
            self.dataSave.del_thread()
        except:
            ...
        # 弹出提醒框, 提示保存成功, 并显示保存路径
        # QtWidgets.QMessageBox.information(self, "提示", "数据保存成功!\n保存路径: {}".format(self.et_filePath.text()), buttons=QtWidgets.QMessageBox.StandardButton.Save, defaultButton=QtWidgets.QMessageBox.StandardButton.Ok)
        box = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Icon.Information, "提示", "数据保存成功!\n保存路径: {}".format(self.et_filePath.text()))
        open_btn = box.addButton("打开", QtWidgets.QMessageBox.ButtonRole.NoRole)
        save_btn = box.addButton("另存为", QtWidgets.QMessageBox.ButtonRole.NoRole)
        yes_btn = box.addButton("确定", QtWidgets.QMessageBox.ButtonRole.NoRole)
        box.exec()

        if box.clickedButton() == open_btn:
            os.startfile(self.et_filePath.text())
        elif box.clickedButton() == save_btn:
            # 另存为 .txt
            fileName = QtWidgets.QFileDialog.getSaveFileName(self, "另存为", "./", "文本文件(*.txt)")   # 返回元组: (文件名, 文件类型)
            filePath = os.path.dirname(fileName[0])
            if fileName[0] != "":
                if os.path.exists(fileName[0]):
                    os.remove(fileName[0])
                os.rename("D:\\Download\\OneDrive - zju.edu.cn\\code\\EMGexe\\test\\3333.txt", fileName[0])
                self.et_filePath.setText(filePath)
            self.btn_stop_clicked()
        elif box.clickedButton() == yes_btn:
            ...
    
    def btn_filePath_clicked(self):
        filePath = QtWidgets.QFileDialog.getExistingDirectory(self, "选择文件路径", "./")
        if filePath:
            self.et_filePath.setText(filePath)
            self.dataSave.updateFilePath(filePath)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = DataSaveTest()
    w.show()
    sys.exit(app.exec())