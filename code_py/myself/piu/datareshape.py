import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
#import accel_add as ac 
import math



datafile = 'D:/data.txt'
data = np.fromfile(datafile, sep=' ')


    # 每条数据包括15项，
feature_names = [ 'roll','Pitch','Yaw',\
    'accelaration_x','accelaration_y','accelaration_z',\
    'Gyroscope_x','Gyroscope_y','Gyroscope_z',\
    'Magnetic_x','Magnetic_y','Magnetic_z',\
    'Pressure','Altitude','Temperature']

feature_num = len(feature_names)

    # 将原始数据进行Reshape，变成[N, 14]这样的形状

data = data.reshape([data.shape[0] // feature_num, feature_num])
# print(data.shape)
# print(data[:,0])#index 
# print(data[0][0])
# data0 = np.array(data[:,0])
# print(data0.shape)
# print(data0)

#huantu


#转换单位 lsb->
ACCEL = 0.000598144531
GURO = 0.0304878049
MAGN = 0.15
CHANGE = np.array([1,1,1,ACCEL,ACCEL,ACCEL,GURO,GURO,GURO,MAGN,MAGN,MAGN,1,1,1])
#单位转换后的数值，<°，°，°，m/s2,m/s2,m/s2,dps,dps,dps,miut,miut,miut,hpa,m,°C>
DATA =  data*CHANGE 

#标准样本分割==========
#样本数据分割
datachange = DATA.reshape(11,60,5,3)
print(datachange)
print('========================================================================')
print(datachange[0])
print('========================================================================')
print(datachange[0][0])
print('========================================================================')
print(datachange[0][0][0])
print('========================================================================')
print(datachange[0][0][0][0])




#遍历样本收集,由标准分割11---->601，遍历采样间隔
datalen = DATA.reshape(660*15)
datatest  =[]
for i  in range(0,9015,15):
    #data1 = data1.reshape(60,5,3)
    datatest.append(datalen[i:900+i])

datatest = np.array(datatest)
#
datatest = datatest.reshape(601,60,5,3)
print(datatest.shape)
print(datatest[600][0])

#制作标签

label = []
for i in range(601):
    label.append(0)


print(label)




