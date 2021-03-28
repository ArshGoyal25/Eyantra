import numpy as np
import cv2
cap = cv2.VideoCapture(0)
while(1):
    ret, img = cap.read()
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    ret,thresh = cv2.threshold(gray,100,255,0)
    contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)[-2:]

    cv2.imshow('image',img)
    print(len(contours))
    if cv2.waitKey(1) == 27:
        break
    #for i in range(1,len(contours)):
    approx = cv2.approxPolyDP(contours,0.01*cv2.arcLength(contours,True),True)
    if len(approx)==4:
        cv2.drawContours(img,contours,-1,(0,255,0),3)
"""   
    for i in range(1,len(contours)):
            b=0
            r=0
            g=0
            M=cv2.moments(contours[i])
            try:
                cx=int(M['m10']/M['m00'])
                cy=int(M['m01']/M['m00'])
            except ZeroDivisionError:
                cx=int(M['m10'])
                cy=int(M['m01'])
            b=img[cy,cx,0]
            g=img[cy,cx,1]
            r=img[cy,cx,2]
            font=cv2.FONT_HERSHEY_SIMPLEX
            approx = cv2.approxPolyDP(i,0.01*cv2.arcLength(i,True),True)
            if len(approx)==4:
                cv2.drawContours(img,contours,-1,(0,255,0),3)
"""
cv2.waitKey(0)
cap.release()
cv2.destroyAllWindows()
