import numpy as np
import cv2
import sys
       
src=cv2.imread("D:/test.jpg",cv2.IMREAD_ANYCOLOR)
clahe = cv2.createCLAHE(clipLimit=2.0,tileGridSize=(8,8))
B = src[:,:,0]
G = src[:,:,1]
R = src[:,:,2]

gray_image = cv2.cvtColor(src,cv2.COLOR_BGR2GRAY)

dst = clahe.apply(gray_image)

weght =dst/gray_image

src_new = np.zeros((src.shape)).astype("uint8")
src_new[:,:,0] = B*weght
src_new[:,:,1] = G*weght
src_new[:,:,2] = R*weght

cv2.imshow('yuantu',src)
cv2.imshow('zhifanghua',src_new)
cv2.waitKey()
cv2.destroyAllWindows()




#print(gray_image,dst,new_image)
# new_image = cv2.cvtColor(dst,cv2.COLOR_GRAY2BGR)
# # new=gray2rgb(image,dst)








# def compute(img, min_percentile, max_percentile):
# 	"""计算分位点，目的是去掉图1的直方图两头的异常情况"""
#     max_percentile_pixel = np.percentile(img, max_percentile)
#     min_percentile_pixel = np.percentile(img, min_percentile)

#     return max_percentile_pixel, min_percentile_pixel


# def aug(src):
# 	"""图像亮度增强"""
# 	if get_lightness(src)>130:
# 		print("图片亮度足够，不做增强")
# 	# 先计算分位点，去掉像素值中少数异常值，这个分位点可以自己配置。
# 	# 比如1中直方图的红色在0到255上都有值，但是实际上像素值主要在0到20内。
#     max_percentile_pixel, min_percentile_pixel = compute(src, 1, 99)
    
#     # 去掉分位值区间之外的值
#     src[src>=max_percentile_pixel] = max_percentile_pixel
#     src[src<=min_percentile_pixel] = min_percentile_pixel

# 	# 将分位值区间拉伸到0到255，这里取了255*0.1与255*0.9是因为可能会出现像素值溢出的情况，所以最好不要设置为0到255。
#     out = np.zeros(src.shape, src.dtype)
#     cv2.normalize(src, out, 255*0.1,255*0.9,cv2.NORM_MINMAX)

#     return out

# def get_lightness(src):
# 	# 计算亮度
#     hsv_image = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)
#     lightness = hsv_image[:,:,2].mean()
    
#     return  lightness

# img = cv2.imread(r"C:/Users/wangz/Desktop/tu/12.jpg")
# img = aug(img)
# cv2.imwrite('out.png', img)
# convert gray to rgb image

# def rgb2gray(rgb):
#         return np.dot(rgb[..., :3], [0.299, 0.587, 0.114])


 
# def gray2rgb(rgb,imggray):
#    # 原图 R G 通道不变，B 转换回彩图格式
#    R = rgb[:,:,0]
#    G = rgb[:,:,1]
#    B = ((imggray) - 0.299 * R - 0.587 * G) / 0.114
 
#    grayRgb = np.zeros((rgb.shape))
#    grayRgb[:, :, 2] = B
#    grayRgb[:, :, 0] = R
#    grayRgb[:, :, 1] = G
 
#    return grayRgb
# print(gray)
# # gray_image = rgb2gray(image)
# gray_image = (R*76.245+G*149.685+B*29.07)/255
# gray_image = np.round(gray_image)
# print(gray_image)
# src = cv2.imread("C:/Users/wangz/Desktop/tu/12.jpg")
# src_gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
# # RGB在opencv中存储为BGR的顺序,数据结构为一个3D的numpy.array,索引的顺序是行,列,通道:
# B = src[:,:,0]
# G = src[:,:,1]
# R = src[:,:,2]
# # 灰度g=p*R+q*G+t*B（其中p=0.2989,q=0.5870,t=0.1140），于是B=(g-p*R-q*G)/t。于是我们只要保留R和G两个颜色分量，再加上灰度图g，就可以回复原来的RGB图像。
# g = src_gray[:]
# p = 0.2989; q = 0.5870; t = 0.1140
# B_new = (g-p*R-q*G)/t
# B_new = np.uint8(B_new)
# src_new = np.zeros((src.shape)).astype("uint8")
# src_new[:,:,0] = B_new
# src_new[:,:,1] = G
# src_new[:,:,2] = R
# # 显示图像
# cv2.imshow("input", src)
# cv2.imshow("output", src_gray)
# cv2.imshow("result", src_new)

# cv2.waitKey(0)


# import numpy as np 
# import cv2
# import json
# from PIL import Image
# import matplotlib.pyplot as plt
# image = Image.open('C:/Users/wangz/Desktop/tu/12.jpg')
# # image = np.array(image)