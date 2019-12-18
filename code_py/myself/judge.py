import cv2
import numpy as np
#判断是否有签字
def Decision_signature(image):
    ave=np.average(image)
    if (ave>173.7):
        num="未签字"

    else:
        num="已签字"
    return num

#引入图片
path = "C:/Users/W/Desktop/choose/12.jpg"
img = cv2.imread(path)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#调用函数
w=Decision_signature(gray)
#查看结果
print(w)







