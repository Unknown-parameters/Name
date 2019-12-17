import random
#随机模块
res0 = random.random() #从0~1中间随机产生一个小数点后16位的浮点数
# res1 = random.uniform(1,3) #从1~3中间随机产生一个小数点后16位的浮点数
#res2 = random.randint(1,3) #[1,3]
# res3 = random.randrange(1,3) #[1,3)
#
print(int(res0*10000000000000))
# print(res1)
#print(res2)
# print(res3)

# 0.2606221247506799
# 2.8556674313380523
# 3
# 1

l0_test = random.choice(["0条","1条","0套","1套","0根","1根","0个","1个","0支","1支"]) #从列表中随机选择一个元素
# l1_test = random.choices([11,22,33]) #从列表中随机选择一个元素组成一个新列表
# l2_test = random.sample([11,'22','test',33,44],3) #必须指定选择的元素个数,
#
print(l0_test,type(l0_test))
# print(l1_test,type(l1_test))
# print(l2_test)
# 22 <class 'str'>
# [11] <class 'list'>
# [44, 'test', '22']

# l_test = [1,2,3,4,5]
# random.shuffle(l_test) #将列表元素顺序打乱
# print(l_test)
# [4, 2, 3, 1, 5]

#随机生成验证码
# def v_code():
#     res = []
#     for i in range(5):
#         my_number = str(random.randint(0,9))
#         my_string = chr(random.randint(64,90))
#         my_res = random.choice([my_number,my_string])
#         res.append(my_res)
#     return ''.join(res)
#
# if __name__ == '__main__':
#     print(v_code())