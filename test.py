#import numpy as np 
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import pylab
# a=np.arange(30)
# print(a)
# slices = [a[k:k+2] for k in range(0, 6, 2)]
# print(slices)
# b=np.array(slices)
# print(b)
# print(b.mean(axis=1))
# print(b.shape)
# print(b.std(),b.var())

# c=a.reshape([5,3,2])
# print(c,c.shape)
# print(c.mean(axis=1))
# print(c.argmax(), c.argmax(axis=0), c.argmax(axis=1))
# print(c[3][2][1])
# ##############

# image = Image.open('C:/Users/wangz/Desktop/tu/3.jpg')
# image=np.array(image)
# print(image.shape)
# plt.imshow(image)
# pylab.show()
# image2 = image[::-1, :, :]
# plt.imshow(image2)
# pylab.show()
# image3 = image[:, ::-1, :]
# plt.imshow(image3)
# pylab.show()
# #########################
# # ReLU和Sigmoid激活函数示意图
# import numpy as np
# #matplotlib inline
# import matplotlib.pyplot as plt
# import matplotlib.patches as patches

# #设置图片大小
# plt.figure(figsize=(12, 4))

# # x是1维数组，数组大小是从-10. 到10.的实数，每隔0.1取一个点
# x = np.arange(-10, 10, 0.1)
# # 计算 Sigmoid函数
# s = 1.0 / (1 + np.exp(- x))

# # 计算ReLU函数
# y = np.clip(x, a_min = 0., a_max = None)
# #tanh函数
# z=np.tanh(x)

# #########################################################
# # 以下部分为画图程序

# # 设置两个子图窗口，将Sigmoid的函数图像画在左边
# f = plt.subplot(131)
# # 画出函数曲线
# plt.plot(x, s, color='r')
# # 添加文字说明
# plt.text(-5., 0.9, r'$y=\sigma(x)$', fontsize=13)
# # 设置坐标轴格式
# currentAxis=plt.gca()
# currentAxis.xaxis.set_label_text('x', fontsize=15)
# currentAxis.yaxis.set_label_text('y', fontsize=15)

# # 将ReLU的函数图像画在左边
# f = plt.subplot(132)
# # 画出函数曲线
# plt.plot(x, y, color='g')
# # 添加文字说明
# plt.text(-3.0, 9, r'$y=ReLU(x)$', fontsize=13)
# # 设置坐标轴格式
# currentAxis=plt.gca()
# currentAxis.xaxis.set_label_text('x', fontsize=15)
# currentAxis.yaxis.set_label_text('y', fontsize=15)

# # 将tanh的函数图像画在左边
# f = plt.subplot(133)
# # 画出函数曲线
# plt.plot(x, z, color='b')
# # 添加文字说明
# plt.text(-8, 0.9, r'$z=tanh(x)$', fontsize=13)
# # 设置坐标轴格式
# currentAxis=plt.gca()
# currentAxis.xaxis.set_label_text('x', fontsize=15)
# currentAxis.yaxis.set_label_text('z', fontsize=15)

# plt.show()

p = np.random.randn(10, 10)
q = (p > 0)

print(q)

print(q.sum())