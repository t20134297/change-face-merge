from tkinter import *
from PIL import Image, ImageTk
input_photo = "../photos/init_small.jpeg"
# input_photo = "../photos/init.jpg"
def A():
    root=Tk()#注意Tk的大小写
    root.title("您的原始照片如图所示")
    root.geometry('400x300+500+0')
    # textLabel=Label(root,text='您输入的图片为:')
    # textLabel.pack()
    # s='/home/ansheng/Desktop/face_detect/test/1cp1.jpeg'
    im=Image.open(input_photo)
    tkimg=ImageTk.PhotoImage(im)
    imgLabel=Label(root,imag=tkimg)
    imgLabel.pack()
    mainloop()
A()
