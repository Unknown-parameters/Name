import paddle
import paddle.fluid as fluid
from paddle.fluid.dygraph.nn import FC
import numpy as np
import os
import gzip
import json
import random
#数据处理部分之后的代码，数据读取的部分调用Load_data函数
# 定义网络结构，同上一节所使用的网络结构
class MNIST(fluid.dygraph.Layer):
    def __init__(self, name_scope):
        super(MNIST, self).__init__(name_scope)
        name_scope = self.full_name()
        self.fc = FC(name_scope, size=1, act=None)

    def forward(self, inputs):
        outputs = self.fc(inputs)
        return outputs


with fluid.dygraph.guard():
    model = MNIST("mnist")
    model.train()
    #调用加载数据的函数
    train_loader = load_data('train')
    # 创建异步数据读取器
    place = fluid.CPUPlace()
    data_loader = fluid.io.DataLoader.from_generator(capacity=5, return_list=True)
    data_loader.set_batch_generator(train_loader, places=place)
    
    optimizer = fluid.optimizer.SGDOptimizer(learning_rate=0.001)
    EPOCH_NUM = 3
    for epoch_id in range(EPOCH_NUM):
        for batch_id, data in enumerate(data_loader):
            image_data, label_data = data
            image = fluid.dygraph.to_variable(image_data)
            label = fluid.dygraph.to_variable(label_data)
            
            predict = model(image)
            
            loss = fluid.layers.square_error_cost(predict, label)
            avg_loss = fluid.layers.mean(loss)
            
            if batch_id % 200 == 0:
                print("epoch: {}, batch: {}, loss is: {}".format(epoch_id, batch_id, avg_loss.numpy()))
            
            avg_loss.backward()
            optimizer.minimize(avg_loss)
            model.clear_gradients()

    fluid.save_dygraph(model.state_dict(), 'mnist')