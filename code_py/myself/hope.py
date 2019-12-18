# # -*- coding:utf-8 -*-
import cv2
import numpy as np 
import os

#检测特征的函数
def detect_face(img):
    #将测试图像转换为灰度图像，opencv特征检测需要灰度图像
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #加载OPENCV人脸检测分类器HAAR/分类器需要重点了解
    face_cascade = cv2.CascadeClassifier('/envs/opencv/Library/etc/haarcascades/haarcascade_frontalface_alt.xml')
    
    #检测多尺度图像，返回值是一张脸部区域信息的列表（x,y,宽,高）/基于上述分类器特征检测函数
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.2, minNeighbors=5)

    # 如果未检测到面部，则返回原始图像
    if (len(faces) == 0):
        return None, None

    for  face in faces:
         #目前假设只有一张脸，xy为左上角坐标，wh为矩形的宽高/这里改成多张
        (x, y, w, h) = face
         #返回图像的正面部分
        return gray[y:y + w, x:x + h], face

   


# 该函数将读取所有的训练图像，从每个图像检测人脸并将返回两个相同大小的列表，分别为脸部信息和标签
#训练函数
def prepare_training_data(data_folder_path):
    # 获取数据文件夹中的目录（每个主题的一个目录）
    dirs = os.listdir(data_folder_path)

    # 两个列表分别保存所有的脸部和标签
    faces = []
    labels = []

    # 浏览每个目录并访问其中的图像
    #这里的文件夹的名字就是1或者2
    for dir_name in dirs:
        # dir_name(str类型)即标签
        label = int(dir_name)
        # 建立包含当前主题主题图像的目录路径
        subject_dir_path = data_folder_path + "/" + dir_name
        # 获取给定主题目录内的图像名称
        subject_images_names = os.listdir(subject_dir_path)

        # 浏览每张图片并检测脸部，然后将脸部信息添加到脸部列表faces[]
        for image_name in subject_images_names:
            # 建立图像路径
            image_path = subject_dir_path + "/" + image_name
            # 读取图像
            image = cv2.imread(image_path)
            # 显示图像0.1s
            cv2.imshow("Training on image...", image)
            cv2.waitKey(100)

            # 检测脸部
            face, rect = detect_face(image)#调用了特征检索函数
            # 我们忽略未检测到的脸部
            if face is not None:
            #将脸添加到脸部列表并添加相应的标签
                for  fac in face:

                    faces.append(fac)
                    labels.append(label)

    cv2.waitKey(1)
    cv2.destroyAllWindows()
    #最终返回值为人脸和标签列表
    return faces, labels

#调用prepare_training_data（）函数
faces, labels = prepare_training_data("/training_data")

##===========上边都是训练数据的获取，包括删选特征，与建立标签

#创建LBPH识别器并开始训练，当然也可以选择Eigen或者Fisher识别器
face_recognizer = cv2.face.LBPHFaceRecognizer_create()
face_recognizer.train(faces, np.array(labels))
##======上边属于基于标签数据的监督学习，输入对象为<faces,labels>,输出对象为识别器face_recognizer

#根据给定的（x，y）坐标和宽度高度在图像上绘制矩形
def draw_rectangle(img, rect):
    (x, y, w, h) = rect
    cv2.rectangle(img, (x, y), (x + w, y + h), (128, 128, 0), 2)
# 根据给定的（x，y）坐标标识出人名
def draw_text(img, text, x, y):
    cv2.putText(img, text, (x, y), cv2.FONT_HERSHEY_COMPLEX, 1, (128, 128, 0), 2)

#建立标签与人名的映射列表（标签只能为整数）
subjects = ["linjunjie", "zhoujielun"]

# 此函数识别传递的图像中的人物并在检测到的脸部周围绘制一个矩形及其名称
def predict(test_img):
    #生成图像的副本，这样就能保留原始图像
    img = test_img.copy()
    #检测人脸/将预测对象规范化/同时也有检索识别对象的过程
    #若是对一张图像多个目标的检索和识别，应该从这里改
    faces, rect = detect_face(img)
    for  face in faces:

        #预测人脸
        label = face_recognizer.predict(face)
        # 获取由人脸识别器返回的相应标签的名称/这里就是调用了数组
        label_text = subjects[label[0]]

        # 在检测到的脸部周围画一个矩形
        draw_rectangle(img, rect)
        # 标出预测的名字
        draw_text(img, label_text, rect[0], rect[1] - 5)
        #返回预测的图像
    return img

#加载测试图像
test_img1 = cv2.imread("/yuce_data/1.jpg")
test_img2 = cv2.imread("/yuce_data/2.jpg")

#执行预测
predicted_img1 = predict(test_img1)
predicted_img2 = predict(test_img2)

#显示两个图像
cv2.imshow(subjects[0], predicted_img1)
cv2.imshow(subjects[1], predicted_img2)
cv2.waitKey()
cv2.destroyAllWindows()

#只能检索一个特征，如何做到在一张图片中检索多个特征，我认为这是一个调用机制的问题，
#先了解了自己分类器的训练原理就有可能成功解决上述问题