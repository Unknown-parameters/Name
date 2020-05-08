import numpy as np 
import  cmath
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator
import matplotlib.pyplot as plt
#输入加速度单位m/s2;
Q0 = np.array([1.0,0.0,0.0,0.0])
g0 = np.array([0.0,0.0,9.8])

def updata(wx,wy,wz,ax,ay,az):
    #跟新循环
    global Q0
    global g0
    print('Q0_u=',Q0)
    #归一化处理
    norm = 1/cmath.sqrt(wx*wx+wy*wy+wz*wz)
    wx = wx*norm
    wy = wy*norm
    wz = wz*norm



    #获取实时的转换矩阵
    gyro =np.array([[0.0,-wx,-wy,-wz],[wx,0.0,wz,-wy],[wy,-wz,0.0,wx],[wz,wy,-wx,0.0]])
    accel = np.array([ax,ay,az])


    #获取时刻对应的四元数
    
    Q0 = 0.5*np.dot(gyro,Q0)

    #获取重力加速度分量的转换矩阵
    q00 = Q0[0]*Q0[0]
    q01 = Q0[0]*Q0[1]
    q02 = Q0[0]*Q0[2]
    q03 = Q0[0]*Q0[3]
    q11 = Q0[1]*Q0[1]
    q12 = Q0[1]*Q0[2]
    q13 = Q0[1]*Q0[3]
    q22 = Q0[2]*Q0[2]
    q23 = Q0[2]*Q0[3]
    q33 = Q0[3]*Q0[3]
    QMAX =[[q00+q11-q22-q33,2*(q12-q03),2*(q13+q02)],\
           [2*(q12+q03),q00-q11+q22-q33,2*(q23-q01)],\
           [2*(q13-q02),2*(q23+q01),q00-q11-q22+q33]]
    #获取重力加速度分量
    g1 = np.dot(QMAX,g0)
    #对加速度计分量进行修正
    accel = accel-g1
    print('Q0_p=',Q0)
    return accel





V0 = np.array([0.0,0.0,0.0])
P0 = np.array([0.0,0.0,0.0])
A0 = np.array([0.0,0.0,0.0])
#绝对坐标系下的轨迹位置更新
def travel(acce):

    #初始速度，初始位置，初始加速度
    global V0
    global P0
    global A0

    xx = 0.005*(acce+A0)
    V0 = V0 +xx
    P0 = P0 +V0*0.01+0.5*xx
    A0 = acce
    return P0


#画3D的轨迹图
def show_3d(acce):
    # new a figure and set it into 3d
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    first_2000 = acce[:, 0]
    second_2000 = acce[:, 1]
    third_2000 = acce[:, 2]


    # set figure information
    ax.set_title("3D_Curve")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")

    # draw the figure, the color is r = read
    #ax.plot(accel[:,0])... /\
    figure = ax.plot(first_2000, second_2000, third_2000, c='r')
    plt.show()



def show_3d1(acce):
    #定义坐标轴
    fig = plt.figure()
    ax1 = plt.axes(projection='3d')
    z = acce[:, 2]
    x = acce[:, 0]
    y = acce[:, 1]
    # zd = 13*np.random.random(100)
    # xd = 5*np.sin(zd)
    # yd = 5*np.cos(zd)
    #ax1.scatter3D(x,y,z, cmap='b')  #绘制散点图
    ax1.plot3D(x,y,z,'gray')    #绘制空间曲线
    plt.show()























# if __name__ == "__main__":
#     wx = 1
#     wy = 2
#     wz = 3
#     ax = 34
#     ay = 17
#     az = 45


#     Q0 = np.array([1.0,0.0,0.0,0.0])
#     g0 = np.array([0.0,0.0,9.8])
#     accel=updata(wx,wy,wz,ax,ay,az)
#     print(accel)


