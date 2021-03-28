import numpy
import csv
import cv2
import cv2.aruco as aruco
from aruco_lib import *
#import os
print(b)
cap=cv2.VideoCapture(0)
while(1):
    #cap=cv2.VideoCapture(0)
    ret,frame=cap.read()
    id_aruco_trace = 0
    det_aruco_list = {}
    det_aruco_list = detect_Aruco(frame)
    cv2.imshow('f',frame)
    if det_aruco_list:
        img = mark_Aruco(frame,det_aruco_list)
        id_aruco_trace = calculate_Robot_State(img,det_aruco_list)
        #print(str(key),str(angle))
        cv2.imshow("frame",img)
        cv2.imwrite('Result.jpg',img)
        if cv2.waitKey(1)==27:
            break
f=open('temp.txt','a')
for i in b:
    f.write(i)
cap.release()
cv2.destroyAllWindows()

