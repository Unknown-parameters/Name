import cv2
path = "C:/Users/W/Desktop/train2/pos/"
img = cv2.imread(path+'40'+'.jpg')
for i in range(1, 51):
    
    cv2.imwrite('C:/Users/W/Desktop/stone/'+str(i)+'.jpg', img)