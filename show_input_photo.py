from tkinter import *
from PIL import Image, ImageTk
import sys
input_photo = sys.argv[1]
def A():
    root=Tk()#注意Tk的大小写
    root.title("输入图片显示窗口")
    root.geometry('360x360+0+0')
    textLabel=Label(root,text='您输入的图片为:')
    textLabel.pack()
    # s='/home/ansheng/Desktop/face_detect/test/1cp1.jpeg'
    im=Image.open(input_photo)
    tkimg=ImageTk.PhotoImage(im)
    imgLabel=Label(root,imag=tkimg)
    imgLabel.pack()
    mainloop()
A()
