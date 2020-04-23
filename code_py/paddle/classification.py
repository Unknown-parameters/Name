import paddle
import paddle.fluid as fluid
import paddle.fluid.dygraph as dygraph
from paddle.fluid.dygraph import FC
import numpy as np
import os
import random


def  load_data():
    #从文件导入数据
    datafile = 'path'
    data = np.fromfile(datafile,sep='')
    #每条数据包括14项
    feature_names = ['CRIM','ZN','INDUS','CHAS']
    feature_num = len (feature_names)

    #reshape
    data  =data.reshape([data.shape[0]//feature_num,feature_num])


    ratio = 0.8
    offset = int(data.shape[0]*ratio)
    training_data = data[:offset]

    maximums,minimuns,avgs = training_data.max(axis=0),traing_data.min(axis=0),\
        training_data.sum(axis=0)/training_data.shape[0]

    #归一化处理
    global max_values
    global min_values
    global avg_values
     
     max_values = maximums
     min_values = minimuns
     avg_values = avgs

     for i in range(feature_num):
         data[:,i] = (data[:,i]) - avg[i])/(maximums[i]-minimuns[i])


    training_data = data[:offset]
    test_data = data[offset] 





