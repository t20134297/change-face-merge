# #coding=utf-8
# import cv2 as cv
#
# import time
#
# if __name__ == '__main__':
#
#     cv.namedWindow("camera",1)
#     #开启ip摄像头
#     video="http://admin:admin@10.13.231.53:8081/"
#     #capture =cv.CaptureFromFile(video)
#     capture =cv.VideoCapture(video)
#
#     num = 0;
#     while True:
#         #img = cv.QueryFrame(capture)
#         ret,img=capture.read()
#         #cv.ShowImage("camera",img)
#         cv.imshow('camera',img)
#
#     #按键处理，注意，焦点应当在摄像头窗口，不是在终端命令行窗口
#         key = cv.WaitKey(10)
#
#         if key == 27:
#         #esc键退出
#             print("esc break...")
#             break
#         if key == ord(' '):
#              #保存一张图像
#             num = num+1
#             filename = "frames_%s.jpg" % num
#             cv.SaveImage(filename,img)
#
#
#     del(capture)
#     cv.DestroyWindow("camera")



import numpy as np
import cv2
import time
video="http://admin:admin@219.216.99.57:8081/"
#video="E:/Movies/YDTL0085.mp4"
cap = cv2.VideoCapture(video)
time.sleep(10)
#if not cap.isOpened():
#	print('dhsaufhdg')
#time.sleep(2)
# cap.set(3,1920)
# cap.set(4,1080)
# print(cap.get(3))
# print(cap.get(4))

num=0
while(True):

    print("ddjsda")
    ret, frame = cap.read()
    print type(frame)
    cv2.imshow('frame',frame)
    key = cv2.waitKey(10)
    if key==27:
        print("esc break...")
        break
    if key == ord(' '):
        #保存一张图像
        num = num+1
        filename = "frames_%s.jpg" % num
        filename1 = "frames1_%s.png" % num
        #jpg格式
        cv2.imwrite(filename,frame,[int(cv2.IMWRITE_JPEG_QUALITY),100])
        print('save {} done.'.format(filename))
        #png格式
        #cv2.imwrite(filename1,frame,[int(cv2.IMWRITE_PNG_COMPRESSION),0])

cap.release()
cv2.destroyAllWindows()
