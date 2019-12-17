import cv2

cap = cv2.VideoCapture("D:/image/3.mp4")
isOpened = cap.isOpened    # 判断是否打开‘
print(isOpened)
fps = cap.get(cv2.CAP_PROP_FPS)    #帧率
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
print(fps,width,height)
i = 0
while(isOpened):
    if i == 700:
        break
    else:
        i += 1
    (flag,frame) = cap.read() # 读取每一张 flag frame 
    fileName = 'image'+str(i)+'.jpg'
    print(fileName)
    if flag == True:
        cv2.imwrite(fileName,frame,[cv2.IMWRITE_JPEG_QUALITY,100])
