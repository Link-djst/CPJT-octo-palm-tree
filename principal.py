#Santiago Solorzano
#Santiago Paiz
#Diego Sosa

import serial
try:
    # for Python2
    from Tkinter import *
except ImportError:
    # for Python3
    from tkinter import *

# ser = serial.Serial('COM6', 9600, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)

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
        # ser.write(bytes('d', 'UTF-8'))
        print('F4')
    elif switch1["text"]=="0" and switch2["text"]=="0":
        # ser.write(bytes('a', 'UTF-8'))
        print('++')

def enviar2():
    if switch1["text"]=="1" and switch2["text"]=="1":
        # ser.write(bytes('c', 'UTF-8'))
        print('F4')
    elif switch1["text"]=="0" and switch2["text"]=="0":
        # ser.write(bytes('z', 'UTF-8'))
        print('--')

def barrita1(val):
    if switch1["text"]=="0" and switch2["text"]=="1":
        if (var1.get() == 1):
            print val
            #ser.write(bytes(val, 'UTF-8'))

def barrita2(val):
    if switch1["text"]=="1" and switch2["text"]=="0":
        if (var2.get() == 1):
            print val
            #ser.write(bytes(val, 'UTF-8'))

def barrita1checkb():
    print var1.get()
    #ser.write(bytes('s', 'UTF-8'))

def barrita2checkb():
    print var2.get()
    #ser.write(bytes('x', 'UTF-8'))

control=Tk()
control.geometry("215x300")
control.title("Interfaz Remota")
var1 = IntVar()
var2 = IntVar()

#Widgets
mensaje1=Label(control,text="Interfaz Grafica", textvariable="entrada")
toggle_btn = Button(text="Local", width=12, relief="raised",command=toggle)

switch1 = Button(text="0", width=12, relief="raised",bg="#00ACC1",command=funcionS)
switch2 = Button(text="0", width=12, relief="raised", bg="#00ACC1",command=funcionS2)

led1 = Button(text="1", height=5, width=5, bg="#04CAE2", command=enviar)
led2 = Button(text="2", height=5, width=5, bg="#04CAE2", command=enviar2)

w1 = Scale(control, from_=0, to=100, resolution=1,orient=HORIZONTAL, command=barrita1)
b1 = Checkbutton(control, text="Barra 1", variable=var1,command=barrita1checkb)
w2 = Scale(control, from_=0, to=100, resolution=1,orient=HORIZONTAL, command=barrita2)
b2 = Checkbutton(control, text="Barra 2", variable=var2,command=barrita2checkb)
entradaA = Entry(control, bd=5)

#Posiciones
mensaje1.place(x=50,y=10)
toggle_btn.place(x=40,y=270)

switch1.place(x=10,y=135)
switch2.place(x=110,y=135)

led1.place(x=10,y=175)
led2.place(x=55,y=175)


w1.place(x=20,y=45)
b1.place(x=130, y=62.5)
w2.place(x=20,y=90)
b2.place(x=130, y=107.5)

entradaA.place(x=1110,y=30)

mainloop()
