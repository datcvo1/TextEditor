from math import floor
from tkinter import Tk, ttk, Label, Button, StringVar

# everything in tkinter is a widget

# main app window
root = Tk()
root.title("Calculator")
root.resizable(False, False)

# -------------------------------------------------------------------------------
# sampleString = Label(root, text="a block of text like a div")

# simple way to add widgets to window, widget will stay in the middle
# sampleString.pack()

# add widgets to window in a grid, widget will stay where you specified
# sampleString.grid(row=0, column=0)
# -------------------------------------------------------------------------------

value = StringVar(value='0')
operation = Label(root, anchor="e", textvariable=value, width=58, height= 2, bg="white", relief="groove")
operation.grid(row=0, column=0, columnspan=4, padx=10, pady=10)

# create a function for button to execute when pressed
def number(num):
    previous = value.get()
    if previous == '0':
        value.set(num)
    else:
        value.set(previous + num)

def back():
    previous = value.get()
    if previous == '0':
        return
    elif len(previous) == 1:
        value.set('0')
    else:
        value.set(value.get()[:-1])     # remove last element in string

def decimal():
    previous = value.get()
    if '.' in previous:
        return
    value.set(previous + '.')

def clear():
    value.set('0')

def add():
    return

def subtract():
    return

def multiply():
    return

def divide():
    return

Button(root, text="1", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("1")).grid(row=1,column=0)
Button(root, text="2", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("2")).grid(row=1,column=1)
Button(root, text="3", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("3")).grid(row=1,column=2)
Button(root, text="4", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("4")).grid(row=2,column=0)
Button(root, text="5", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("5")).grid(row=2,column=1)
Button(root, text="6", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("6")).grid(row=2,column=2)
Button(root, text="7", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("7")).grid(row=3,column=0)
Button(root, text="8", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("8")).grid(row=3,column=1)
Button(root, text="9", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("9")).grid(row=3,column=2)
Button(root, text="0", activebackground="#ADD8E6", padx= 51, pady= 25, command=lambda: number("0")).grid(row=4,column=1)

(Button(root, text=". ", activebackground="#ADD8E6", padx= 51, pady= 25, command=decimal)
 .grid(row=4, column=0))
(Button(root, text="BACK", activebackground="#ADD8E6", padx= 40, pady= 25, command=back)
 .grid(row=4, column=2))
(Button(root, text="CLEAR ", activebackground="#ADD8E6", padx= 36, pady= 25, command=clear)
 .grid(row=5, column=2))

(Button(root, text="+ ", activebackground="#ADD8E6", padx= 30, pady= 25, command=back)
    .grid(row=1, column=3))
(Button(root, text=" - ", activebackground="#ADD8E6", padx= 30, pady= 25, command=back)
    .grid(row=2, column=3))
(Button(root, text=" * ", activebackground="#ADD8E6", padx= 30, pady= 25, command=back)
    .grid(row=3, column=3))
(Button(root, text=" / ", activebackground="#ADD8E6", padx= 30, pady= 25, command=back)
    .grid(row=4, column=3))
(Button(root, text=" =", activebackground="#ADD8E6", padx= 30, pady= 25, command=back)
    .grid(row=5, column=3))

root.mainloop()