__author__ = 'Ted'

from PyQt5.Qt import *
from pyqtgraph import PlotWidget
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget
import numpy as np
import pyqtgraph as pq


class Window(QWidget):
    def __init__(self):
        super().__init__()
        # 设置下尺寸
        self.resize(600,600)
        # 添加 PlotWidget 控件
        self.plotWidget_ted = PlotWidget(self)
        # 设置该控件尺寸和相对位置
        self.plotWidget_ted.setGeometry(QtCore.QRect(25,25,1100,1100))

        # 仿写 mode1 代码中的数据
        # 生成 300 个正态分布的随机数
        self.data1 = np.random.normal(size=8000)

        self.curve1 = self.plotWidget_ted.plot(self.data1, name="mode1")

        # 设定定时器
        self.timer = pq.QtCore.QTimer()
        # 定时器信号绑定 update_data 函数
        self.timer.timeout.connect(self.update_data)
        # 定时器间隔50ms，可以理解为 50ms 刷新一次数据
        self.timer.start(1)

    # 数据左移
    def update_data(self):
        self.data1[:-1000] = self.data1[1000:]
        self.data1[-1000:] = np.random.normal(size=1000)
        # 数据填充到绘制曲线中
        self.curve1.setData(self.data1)


if __name__ == '__main__':
    import sys
    # PyQt5 程序固定写法
    app = QApplication(sys.argv)

    # 将绑定了绘图控件的窗口实例化并展示
    window = Window()
    window.show()

    # PyQt5 程序固定写法
    sys.exit(app.exec())
