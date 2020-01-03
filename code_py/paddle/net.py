# 加载相关库
import os
import random
import paddle
import paddle.fluid as fluid
from paddle.fluid.dygraph.nn import Conv2D, Pool2D, FC
import numpy as np
from PIL import Image

import gzip
import json
#引入matplotlib库
import matplotlib.pyplot as plt

# 定义数据集读取器
def load_data(mode='train'):

    # 读取数据文件
    datafile = 'C:/Users/wangz/Downloads/mnist.json.gz'
    print('loading mnist dataset from {} ......'.format(datafile))
    data = json.load(gzip.open(datafile))
    # 读取数据集中的训练集，验证集和测试集
    train_set, val_set, eval_set = data

    # 数据集相关参数，图片高度IMG_ROWS, 图片宽度IMG_COLS
    IMG_ROWS = 28
    IMG_COLS = 28
    # 根据输入mode参数决定使用训练集，验证集还是测试
    if mode == 'train':
        imgs = train_set[0]
        labels = train_set[1]
    elif mode == 'valid':
        imgs = val_set[0]
        labels = val_set[1]
    elif mode == 'eval':
        imgs = eval_set[0]
        labels = eval_set[1]
    # 获得所有图像的数量
    imgs_length = len(imgs)
    # 验证图像数量和标签数量是否一致
    assert len(imgs) == len(labels), \
          "length of train_imgs({}) should be the same as train_labels({})".format(
                  len(imgs), len(labels))

    index_list = list(range(imgs_length))

    # 读入数据时用到的batchsize
    BATCHSIZE = 100

    # 定义数据生成器
    def data_generator():
        # 训练模式下，打乱训练数据
        if mode == 'train':
            random.shuffle(index_list)
        imgs_list = []
        labels_list = []
        # 按照索引读取数据
        for i in index_list:
            # 读取图像和标签，转换其尺寸和类型
            img = np.reshape(imgs[i], [1, IMG_ROWS, IMG_COLS]).astype('float32')
            label = np.reshape(labels[i], [1]).astype('int64')
            imgs_list.append(img) 
            labels_list.append(label)
            # 如果当前数据缓存达到了batch size，就返回一个批次数据
            if len(imgs_list) == BATCHSIZE:
                yield np.array(imgs_list), np.array(labels_list)
                # 清空数据缓存列表
                imgs_list = []
                labels_list = []

        # 如果剩余数据的数目小于BATCHSIZE，
        # 则剩余数据一起构成一个大小为len(imgs_list)的mini-batch
        if len(imgs_list) > 0:
            yield np.array(imgs_list), np.array(labels_list)

    return data_generator


# 定义模型结构
class MNIST(fluid.dygraph.Layer):
     def __init__(self, name_scope):
         super(MNIST, self).__init__(name_scope)
         name_scope = self.full_name()
         # 定义卷积层，输出通道20，卷积核大小为5，步长为1，padding为2，使用relu激活函数
         self.conv1 = Conv2D(name_scope, num_filters=20, filter_size=5, stride=1, padding=2, act='relu')
         # 定义池化层，池化核为2，采用最大池化方式
         self.pool1 = Pool2D(name_scope, pool_size=2, pool_stride=2, pool_type='max')
         # 定义卷积层，输出通道20，卷积核大小为5，步长为1，padding为2，使用relu激活函数
         self.conv2 = Conv2D(name_scope, num_filters=20, filter_size=5, stride=1, padding=2, act='relu')
         # 定义池化层，池化核为2，采用最大池化方式
         self.pool2 = Pool2D(name_scope, pool_size=2, pool_stride=2, pool_type='max')
         # 定义全连接层，输出节点数为10，激活函数使用softmax
         self.fc = FC(name_scope, size=10, act='softmax')
         
    # 定义网络的前向计算过程
     def forward(self, inputs, label=None):
         x = self.conv1(inputs)
         x = self.pool1(x)
         x = self.conv2(x)
         x = self.pool2(x)
         x = self.fc(x)
         if label is not None:
             acc = fluid.layers.accuracy(input=x, label=label)
             return x, acc
         else:
             return x

#调用加载数据的函数
train_loader = load_data('train')
    
#在使用GPU机器时，可以将use_gpu变量设置成True
use_gpu = False
place = fluid.CUDAPlace(0) if use_gpu else fluid.CPUPlace()

with fluid.dygraph.guard(place):
    model = MNIST("mnist")
    model.train() 
    
     #四种优化算法的设置方案，可以逐一尝试效果
    #optimizer = fluid.optimizer.SGDOptimizer(learning_rate=0.01)
    #optimizer = fluid.optimizer.MomentumOptimizer(learning_rate=0.01)
    #optimizer = fluid.optimizer.AdagradOptimizer(learning_rate=0.01)
    #optimizer = fluid.optimizer.AdamOptimizer(learning_rate=0.01)
    
    #各种优化算法均可以加入正则化项，避免过拟合，参数regularization_coeff调节正则化项的权重
    #optimizer = fluid.optimizer.SGDOptimizer(learning_rate=0.01, regularization=fluid.regularizer.L2Decay(regularization_coeff=0.1))
    optimizer = fluid.optimizer.AdamOptimizer(learning_rate=0.01, regularization=fluid.regularizer.L2Decay(regularization_coeff=0.1))
    
    EPOCH_NUM = 10
    for epoch_id in range(EPOCH_NUM):
        for batch_id, data in enumerate(train_loader()):
            #准备数据
            image_data, label_data = data
            image = fluid.dygraph.to_variable(image_data)
            label = fluid.dygraph.to_variable(label_data)
            
            #前向计算的过程，同时拿到模型输出值和分类准确率
            predict, avg_acc = model(image, label)
            
            #计算损失，取一个批次样本损失的平均值
            loss = fluid.layers.cross_entropy(predict, label)
            avg_loss = fluid.layers.mean(loss)
            
            #每训练了200批次的数据，打印下当前Loss的情况
            if batch_id % 200 == 0:
                print("epoch: {}, batch: {}, loss is: {}, acc is {}".format(epoch_id, batch_id, avg_loss.numpy(),avg_acc.numpy()))
            
            #后向传播，更新参数的过程
            avg_loss.backward()
            optimizer.minimize(avg_loss)
            model.clear_gradients()

    #保存模型参数
    fluid.save_dygraph(model.state_dict(), 'mnist')
    #画出训练过程中Loss的变化曲线
    plt.figure()
    plt.title("train loss", fontsize=24)
    plt.xlabel("iter", fontsize=14)
    plt.ylabel("loss", fontsize=14)
    plt.plot(iters, losses,color='red',label='train loss') 
    plt.grid()
    plt.show()