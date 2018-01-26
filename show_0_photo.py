from tkinter import *
from PIL import Image, ImageTk
input_photo = "../photos/results/0.jpg"
def A():
    root=Tk()#注意Tk的大小写
    root.title("换脸结果1")
    root.geometry('280x360+120+360')
    # textLabel=Label(root,text='您输入的图片为:')
    # textLabel.pack()
    # s='/home/ansheng/Desktop/face_detect/test/1cp1.jpeg'
    im=Image.open(input_photo)
    tkimg=ImageTk.PhotoImage(im)
    imgLabel=Label(root,imag=tkimg)
    imgLabel.pack()
    mainloop()
A()
