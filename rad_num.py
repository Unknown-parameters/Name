import random
#随机生成验证码
def v_code():
    res = []
    for i in range(13):
        my_number = str(random.randint(0,9))
        res.append(my_number)
    return ''.join(res)
    
if __name__ == '__main__':
    print(v_code())
l0_test = random.choice(["0条","1条","0套","1套","0根","1根","0个","1个","0支","1支"])
print(l0_test,type(l0_test))