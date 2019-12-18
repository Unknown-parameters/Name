import cv2
path = "/caiyang2/"
for i in range(1, 81):
    print(path+str(i)+'.jpg')
    img = cv2.imread(path+str(i)+'.png', cv2.IMREAD_GRAYSCALE)
    img5050 = cv2.resize(img, (120,50))
    cv2.imshow("img", img5050)
    cv2.waitKey(20)
    cv2.imwrite('C:/Users/W/Desktop/same2/'+str(i)+'.jpg', img5050)