import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import accel_add as ac 
import math




datafile = 'D:/data.txt'
data = np.fromfile(datafile, sep=' ')
print(data[10154])


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
print(DATA)

#重力值的加速度补偿：

# def init_imu_data():
#     //四元数初始化
#     Q = np.array([1.0,0.0,0.0,0.0])

# def Accel_add(guro):
#     Q = 0.5*guro*Q

data_ac = []
for data1 in DATA :
    ace=ac.updata(data1[6],data1[7],data1[8],data1[3],data1[4],data1[5])
    if math.isnan(ace[0]):
        print(data1[4])
    data_ac.append(ace)
    #print(data_ac)


data_ac_ar = np.array(data_ac)


data_travel = []
for data2 in data_ac_ar:
    travel1 = ac.travel(data2)
    data_travel.append(travel1)

#print(data_travel)
data_travel_ar = np.array(data_travel)

#打印坐标
datafile1 = 'D:/position.txt'
np.savetxt(datafile1,data_travel_ar,fmt='%0.8f')
#画3D图
# ac.show_3d(data_travel_ar)
ac.show_3d1(data_travel_ar)




#设置图片大小
plt.figure(figsize=(30, 35))

# x是1维数组，实数，每隔0.1取一个点
x = np.arange(0, 67.7, 0.1)

plt.plot(x,data_travel_ar[:,1],color='r')

currentAxis=plt.gca()
currentAxis.xaxis.set_label_text('x', fontsize=15)
currentAxis.yaxis.set_label_text('y', fontsize=15)

plt.show()



for num in range(1,16):
    # 设置两个子图窗口，将Sigmoid的函数图像画在左边
    f = plt.subplot(5,3,num)

    plt.plot(x, DATA[:,num-1], color='r')

    # 添加文字说明
    #plt.text(5., 0.9, r'', fontsize=13)
    # 设置坐标轴格式/need to change
    currentAxis=plt.gca()
    currentAxis.xaxis.set_label_text('x', fontsize=15)
    currentAxis.yaxis.set_label_text('y', fontsize=15)



plt.show()









    # 将原数据集拆分成训练集和测试集
    # 这里使用80%的数据做训练，20%的数据做测试
    # 测试集和训练集必须是没有交集的
    # ratio = 0.8
    # offset = int(data.shape[0] * ratio)
    # training_data = data[:offset]

    # # 计算train数据集的最大值，最小值，平均值
    # maximums, minimums, avgs = training_data.max(axis=0), training_data.min(axis=0), \
    #                              training_data.sum(axis=0) / training_data.shape[0]
    
    # # 记录数据的归一化参数，在预测时对数据做归一化
    # global max_values
    # global min_values
    # global avg_values
    # max_values = maximums
    # min_values = minimums
    # avg_values = avgs

    # # 对数据进行归一化处理
    # for i in range(feature_num):
    #     #print(maximums[i], minimums[i], avgs[i])
    #     data[:, i] = (data[:, i] - avgs[i]) / (maximums[i] - minimums[i])

    # # 训练集和测试集的划分比例
    # #ratio = 0.8
    # #offset = int(data.shape[0] * ratio)
    # training_data = data[:offset]
    # test_data = data[offset:]
    # return training_data, test_data



    # if __name__ == "__main__":
    #     load_data()