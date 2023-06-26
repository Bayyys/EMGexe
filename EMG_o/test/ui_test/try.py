import sys
from PyQt5.Qt import *
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *
app = QApplication(sys.argv)
window = QWidget()
window.resize(800,600)

btn = QToolButton(window)
btn.setText('menu')

# btn.clicked.connect(lambda :print('按钮被按下'))
menu = QMenu()

action_1 = QAction(menu)
action_1.setText('action1')

action_2 = QAction(menu)
action_2.setText('action2')
action_1.setData('action1 is called')   #action_1绑定数据
action_2.setData('action2 is called')   #action_2绑定数据

menu.addAction(action_1)

menu.addAction(action_2)
btn.setMenu(menu)

def btn_call(action):
    print(action.data())  #获取action里的数据

btn.triggered.connect(btn_call)
btn.setPopupMode(QToolButton.MenuButtonPopup)
# btn.setFocusPolicy(Qt.FocusPolicy.)
window.show()
sys.exit(app.exec_())

trigged信号用法