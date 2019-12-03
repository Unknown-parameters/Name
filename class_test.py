# -*- coding: utf-8 -*-
# coding=utf-8

import cv2

# 待检测的图片路径
path="C:/Users/W/Desktop/train/data/cascade_zhen.xml"
path1="D:/image/wangzhen.jpg"


# 加载面部特征库

name_cascade = cv2.CascadeClassifier(path)

# 读取图片
image = cv2.imread(path1)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 探测图片中的签名
names = name_cascade.detectMultiScale(gray, scaleFactor=1.15, minNeighbors=5, minSize=(5, 5), flags=cv2.CASCADE_SCALE_IMAGE)
print ("发现{0}个签名".format(len(names)))

for (x, y, w, h) in names:
    cv2.circle(image, (int((x + x + w) / 2), int((y + y + h) / 2)), int(w / 2), (0, 255, 0), 2)

cv2.imshow("Find names!", image)
cv2.waitKey(0)
