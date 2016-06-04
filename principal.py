#Santiago Solorzano
#Santiago Paiz
#Diego Sosa

import serial
from tkinter import*
import tkinter

ser = serial.Serial('COM6', 9600, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)

def toggle():

    if toggle_btn.config('relief')[-1] == 'sunken':
        toggle_btn.config(relief="raised")
        toggle_btn["text"] = "Local"
    else:
        toggle_btn.config(relief="sunken")
        toggle_btn["text"] = "Remoto"

def funcionS():

    if switch1.config('relief')[-1] == 'sunken':
        switch1.config(relief="raised")
        switch1["text"] = "0"
    else:
        switch1.config(relief="sunken")
        switch1["text"] = "1"

def funcionS2():

    if switch2.config('relief')[-1] == 'sunken':
        switch2.config(relief="raised")
        switch2["text"] = "0"
    else:
        switch2.config(relief="sunken")
        switch2["text"] = "1"

def enviar():

    if switch1["text"]=="1" and switch2["text"]=="1":
        ser.write(bytes('e', 'UTF-8'))
        print('ON')
    elif switch1["text"]=="1" and switch2["text"]=="0":
        ser.write(bytes(' ', 'UTF-8'))
        print('NADA')
    elif switch1["text"]=="0" and switch2["text"]=="1":
        ser.write(bytes(' ', 'UTF-8'))
        print('DOUBLETIEF')
    elif switch1["text"]=="0" and switch2["text"]=="0":
        ser.write(bytes('a', 'UTF-8'))
        print('OFF')

def enviar2():

    if switch1["text"]=="1" and switch2["text"]=="1":
        ser.write(bytes('f', 'UTF-8'))
        print('ON')
    elif switch1["text"]=="1" and switch2["text"]=="0":
        ser.write(bytes(' ', 'UTF-8'))
        print('NADA')
    elif switch1["text"]=="0" and switch2["text"]=="1":
        ser.write(bytes(' ', 'UTF-8'))
        print('DOUBLETIEF')
    elif switch1["text"]=="0" and switch2["text"]=="0":
        ser.write(bytes('z', 'UTF-8'))
        print('OFF')

def barrita1(val):

    if switch1["text"]=="1" and switch2["text"]=="1":
        ser.write(bytes(' ', 'UTF-8'))
        print('ON')
    elif switch1["text"]=="1" and switch2["text"]=="0":
        print (bytearray([6,int(val)]))
        ser.write(bytearray([6,int(val)]))
        print('NADA')
    elif switch1["text"]=="0" and switch2["text"]=="1":
        print (bytearray([5,int(val)]))
        ser.write(bytearray([5,int(val)]))
    elif switch1["text"]=="0" and switch2["text"]=="0":
        ser.write(bytes(' ', 'UTF-8'))
        print('OFF')

control=Tk()
control.geometry("200x300")
control.title("Interfaz Remota")

#Widgets
mensaje1=Label(control,text="Interfaz Grafica", textvariable="entrada")
toggle_btn = Button(text="Local", width=12, relief="raised",command=toggle)

switch1 = Button(text="0", width=12, relief="raised",command=funcionS)
switch2 = Button(text="0", width=12, relief="raised",command=funcionS2)

led1 = Button(text="1", height=5, width=5, bg="yellow", command=enviar)
led2 = Button(text="2", height=5, width=5, bg="red", command=enviar2)



w1 = Scale(control, from_=0, to=100, resolution=1,orient=HORIZONTAL, command=barrita1)
w2 = Scale(control, from_=0, to=100, resolution=1,orient=HORIZONTAL)
entradaA = Entry(control, bd=5)

#Posiciones
mensaje1.place(x=50,y=10)
toggle_btn.place(x=40,y=270)

switch1.place(x=10,y=135)
switch2.place(x=110,y=135)

led1.place(x=10,y=175)
led2.place(x=55,y=175)


w1.place(x=40,y=45)
w2.place(x=40,y=90)

entradaA.place(x=1110,y=30)

mainloop()
