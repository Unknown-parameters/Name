# -*- coding: utf-8 -*-
# coding=utf-8
import cv2



color = (0, 0, 0)  # 设置人脸框的颜色

def findface(src):
    image1 = src.copy()
    image = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    #cv2.equalizeHist(image, image)  # 灰度图像进行直方图等距化

    # 加载OpenCv的面部特征库
    classfier = cv2.CascadeClassifier("C:/Users/W/.conda/envs/opencv/Library/etc/haarcascades/haarcascade_frontalface_alt.xml")
    # 找到人脸的位置
    # 设定最小图像的大小
   # minSize = (int(w / divisor), int(h / divisor))  # 这里加了一个取整函数
    faceRects = classfier.detectMultiScale(image, scaleFactor=1.2, minNeighbors=5)

    if len(faceRects) > 0:  # 如果人脸数组长度大于0
        for faceRect in faceRects:  # 对每一个人脸画矩形框
            x, y, w, h = faceRect
            cv2.rectangle(image1, (x, y), (x + w, y + h), color)
    cv2.imshow('img',image1)


my_img = cv2.imread("C:/Users/W/Desktop/yuce_data/9.jpg")

findface(my_img)

cv2.waitKey()
cv2.destroyAllWindows()

