# -*- coding: utf-8 -*-
"""
Created on Thu May 19 16:51:20 2016

@author: Diego Sosa
"""
import sys
from PyQt4 import QtGui, QtCore


class GUI(QtGui.QMainWindow):

    def __init__(self):
        super(GUI, self).__init__()

        self.initUI()

    def initUI(self):

        btn1 = QtGui.QPushButton("LED1", self)
        btn1.move(30, 50)

        btn2 = QtGui.QPushButton("LED2", self)
        btn2.move(150, 50)

        btn3 = QtGui.QPushButton("LED3", self)
        btn3.move(270, 50)

        btn4 = QtGui.QPushButton("LED4", self)
        btn4.move(390, 50)

        btn1.clicked.connect(self.buttonClicked)
        btn2.clicked.connect(self.buttonClicked)
        btn3.clicked.connect(self.buttonClicked)
        btn4.clicked.connect(self.buttonClicked)

        self.statusBar()

        self.setGeometry(500, 500, 520, 150)
        self.setWindowTitle('Event sender')
        self.show()

    def buttonClicked(self):

        sender = self.sender()
        self.statusBar().showMessage(sender.text() + ' was pressed')

def main():

    app = QtGui.QApplication(sys.argv)
    ex = GUI()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
