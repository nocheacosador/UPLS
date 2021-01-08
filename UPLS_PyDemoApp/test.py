from tkinter import *
import random

root = Tk()
prompt = '      Press any key      '
label1 = Label(root, text=prompt, width=len(prompt), bg='yellow')
label1.pack()

colors = ['yellow', 'purple', 'green', 'white', 'orange']

def key(event):
    label1['bg'] = random.choice(colors)
    if event.char == event.keysym:
        msg = 'Normal Key %r' % event.char
    elif len(event.char) == 1:
        msg = 'Punctuation Key %r (%r)' % (event.keysym, event.char)
    else:
        msg = 'Special Key %r' % event.keysym
    label1.config(text=msg)

root.bind_all('<Key>', key)

root.mainloop()