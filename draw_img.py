
from PIL import Image, ImageDraw, ImageFont
import cv2
import numpy as np
import random
#生成图片
img = np.zeros([240, 800, 3], np.uint8)+255
#生成随机数字,文字
def v_code():
    res = []
    text = random.choice(["0条","1条","0套","1套","0根","1根","0个","1个","0支","1支"])
    for i in range(13):
        my_number = str(random.randint(0,9))
        res.append(my_number)
    return ''.join(res),text
#打印
def print_chinese(img,num,text):
    #cv2.putText(img , num, (10, 40), cv2.FONT_HERSHEY_DUPLEX, 2, (0, 0, 0), 3)
    cv2img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) # cv2和PIL中颜色的hex码的储存顺序不同
    pilimg = Image.fromarray(cv2img)
    # PIL图片上打印汉字
    draw = ImageDraw.Draw(pilimg) # 图片上打印
    font = ImageFont.truetype("simhei.ttf", 70, encoding="utf-8") # 参数1：字体文件路径，参数2：字体大小
    draw.text((10, 20), num, (0, 0, 0), font=font)
    draw.text((10, 100), text, (0, 0, 0), font=font) # 参数1：打印坐标，参数2：文本，参数3：字体颜色，参数4：字体
    # PIL图片转cv2 图片
    img2 = cv2.cvtColor(np.array(pilimg), cv2.COLOR_RGB2BGR)
    return img2



for i in range(10):

    img1 = img.copy()
    num,text=v_code()
    img2=print_chinese(img1,num,text)
    #cv2.imshow('photo'+str(i), img2 )
    cv2.imwrite('C:/Users/W/Desktop/label/'+str(i)+'.jpg', img2)
