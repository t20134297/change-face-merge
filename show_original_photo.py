from tkinter import *
from PIL import Image, ImageTk
import sys
original_photo = sys.argv[2]
name = sys.argv[3]
def A():
    root=Tk()#注意Tk的大小写
    root.geometry('300x360+420+0')
    root.title("录入图片显示窗口")
    inf='系统检测到该顾客为：'+name+' 请您进一步确认!'
    textLabel=Label(root,text=inf)
    textLabel.pack()
    # s='/home/ansheng/Desktop/face_detect/test/1cp1.jpeg'
    im=Image.open(original_photo)
    tkimg=ImageTk.PhotoImage(im)
    imgLabel=Label(root,imag=tkimg)
    imgLabel.pack()
    mainloop()
A()
