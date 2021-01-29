from tkinter import Tk, Button
from tkinter.ttk import Combobox
from UPLS import LedInfo

tk = Tk()
values_list = []
for value in LedInfo.Led.Mode.values:
	values_list.append(value)
cmb = Combobox(tk, values=values_list, state='readonly')
cmb.current(0)
cmb.pack()

def callback():
	print(type(LedInfo.Led.Mode.values[cmb.get()]))

btn = Button(tk, text='Set', command=callback)
btn.pack()

tk.mainloop()