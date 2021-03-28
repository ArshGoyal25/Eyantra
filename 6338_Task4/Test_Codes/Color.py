# -*- coding: utf-8 -*-
"""
**************************************************************************
*                  E-Yantra Robotics Competition
*                  ================================
*  This software is intended to check version compatiability of open source software
*  Theme: ANT BOT
*  MODULE: Task1.2
*  Filename: Task1.2.py
*  Version: 1.0.0  
*  Date: October 31, 2018
*  
*  Author: e-Yantra Project, Department of Computer Science
*  and Engineering, Indian Institute of Technology Bombay.
*  
*  Software released under Creative Commons CC BY-NC-SA
*
*  For legal information refer to:
*        http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode 
*     
*
*  This software is made available on an “AS IS WHERE IS BASIS”. 
*  Licensee/end user indemnifies and will keep e-Yantra indemnified from
*  any and all claim(s) that emanate from the use of the Software or 
*  breach of the terms of this agreement.
*  
*  e-Yantra - An MHRD project under National Mission on Education using 
*  ICT(NMEICT)
*
**************************************************************************
"""

"""
ArUco ID Dictionaries: 4X4 = 4-bit pixel, 4X4_50 = 50 combinations of a 4-bit pixel image
List of Dictionaries in OpenCV's ArUco library:
DICT_4X4_50	 
DICT_4X4_100	 
DICT_4X4_250	 
DICT_4X4_1000	 
DICT_5X5_50	 
DICT_5X5_100	 
DICT_5X5_250	 
DICT_5X5_1000	 
DICT_6X6_50	 
DICT_6X6_100	 
DICT_6X6_250	 
DICT_6X6_1000	 
DICT_7X7_50	 
DICT_7X7_100	 
DICT_7X7_250	 
DICT_7X7_1000	 
DICT_ARUCO_ORIGINAL

Reference: http://hackage.haskell.org/package/opencv-extra-0.2.0.1/docs/OpenCV-Extra-ArUco.html
Reference: https://docs.opencv.org/3.4.2/d9/d6a/group__aruco.html#gaf5d7e909fe8ff2ad2108e354669ecd17
"""

import numpy
import csv
import cv2
import cv2.aruco as aruco
from aruco_lib import *


def shape_detect(i):  #Function to detect shape of object by using the number of contour edges
    global check
    approx = cv2.approxPolyDP(i,0.01*cv2.arcLength(i,True),True)
    if len(approx)==4:
        check="True"
    return(check)
#s = serial.Serial("/dev/ttyUSB0",9600) # assigns the serial stream ( link between the Arduino and Pi ) to a variable s
cap=PiCamera(resolution=(1380,720),framerate=13.6)
rc=PiRGBArray(cap,(320,240))
cap.framerate=13.6
check="False"
#i=0
for image in cap.capture_continuous(rc, format="rgb", use_video_port=True, resize=(320,240)): 
        img=image.array
#for i in range(0,1):
            #img=cv2.imread("Image1.jpg")
        #ret, img = cap.read()
        img = cv2.blur(img, (5, 5))
        gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        ret,thresh=cv2.threshold(gray,100,255,0)
        contours,hierarchy=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)[-2:]
        cv2.imshow("test",img)
        if cv2.waitKey(1) == 27:
            break
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
            if(b>r and b>g):
                check=shape_detect(contours[i])
                if check=="True":
                    print("Red")
                    cv2.drawContours(img,contours,i,(0,255,0),5)
                    cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img,(cx,cy),5,(0,0,0),-1)
            cv2.imshow("Image",img)
            cv2.waitKey(10)
            rc.truncate(0)
#We are detecting the colour of the object by picking up the RBG value of the pixel at the centroid
#coordinates that help to determine the colour of that pixel and hence the entite shape.
#if(b>r and b>g):
"""
                check=shape_detect(contours[i])
                if check=="True":
                    print("Blue")
                    cv2.drawContours(img,contours,i,(0,0,255),25)
                    cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img,(cx,cy),5,(0,0,0),-1)
            if(r>b and r>g):
                check=shape_detect(contours[i])
                if check=="True":
                    print("Red")
                    cv2.drawContours(img,contours,i,(0,255,0),25)
                    cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img,(cx,cy),5,(0,0,0),-1)
            if(g>r and g>b):
                check=shape_detect(contours[i])
                if check=="True":
                    print("green")
                    cv2.drawContours(img,contours,i,(255,0,0),25)
                    cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img,(cx,cy),5,(0,0,0),-1)#
"""          
#cv2.waitKey(0)
cap.release()
cv2.destroyAllWindows()



   

