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

def aruco_detect(path_to_image):
    '''
    you will need to modify the ArUco library's API using the dictionary in it to the respective
    one from the list above in the aruco_lib.py. This API's line is the only line of code you are
    allowed to modify in aruco_lib.py!!!
    '''
    
    img = cv2.imread(path_to_image)     #give the name of the image with the complete path 
    id_aruco_trace = 0
    det_aruco_list = {}
    x=720
    y=1280
    img = cv2.blur(img, (5, 5))
    img2 = img[0:x,0:y,:]   #separate out the Aruco image from the whole image
    det_aruco_list = detect_Aruco(img2)
    if det_aruco_list:
        img3 = mark_Aruco(img2,det_aruco_list)
        id_aruco_trace = calculate_Robot_State(img3,det_aruco_list)
        cv2.imwrite('result.jpg',img3)
    color_detect(path_to_image)


check="False"
def color_detect(img):
    img1=cv2.imread(img)
    img1 = cv2.blur(img1, (5, 5))
    img3 = cv2.imread("result.jpg")
    gray=cv2.cvtColor(img1,cv2.COLOR_BGR2GRAY)
    ret,thresh=cv2.threshold(gray,127,255,0)
    
    contours,hierarchy=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)[-2:]
    print('\n'+str(len(contours))+'\n')
    j = 0
    xc = []
    yc = []
    print("Colour Codes: 1. Blue \t 2. Red \t \t 3.Green")
    print("Shape Codes: 1. Triangle \t 2. Square \t 3.Circle")
    for j in range(0,2):
        colour=int(input("Enter colour of Object "+str(j+1)))
        shape=int(input ("Enter shape of Object"+str(j+1)))
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
            b=img1[cy,cx,0]
            g=img1[cy,cx,1]
            r=img1[cy,cx,2]
            font=cv2.FONT_HERSHEY_SIMPLEX

#We are detecting the colour of the object by picking up the RBG value of the pixel at the centroid
#coordinates that help to determine the colour of that pixel and hence the entite shape.

            if colour!=1 and colour!=2 and colour!=3:
                xc.append("None")
                yc.append("None")
                break
            if(b>r and b>g) and colour==1:
                check=shape_detect(shape,contours[i])
                if check=="True":
                    cv2.drawContours(img3,contours,i,(0,0,255),25)
                    cv2.putText(img3,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img3,(cx,cy),5,(0,0,0),-1)
                    xc.append(cx)
                    yc.append(cy)
                    j += 1
            if(r>b and r>g)and colour==2:
                check=shape_detect(shape,contours[i])
                if check=="True":
                    cv2.drawContours(img3,contours,i,(0,255,0),25)
                    cv2.putText(img3,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img3,(cx,cy),5,(0,0,0),-1)
                    xc.append(cx)
                    yc.append(cy)
                    j += 1
            if(g>r and g>b)and colour==3:
                check=shape_detect(shape,contours[i])
                if check=="True":
                    cv2.drawContours(img3,contours,i,(255,0,0),25)
                    cv2.putText(img3,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                    cv2.circle(img3,(cx,cy),5,(0,0,0),-1)
                    xc.append(cx)
                    yc.append(cy)
                    j +=1
    cv2.imshow("Image",img3)
    cv2.imwrite("ArUco5.jpg",img3)
    cv2.waitKey(0)
    cv2.destroyAllWindows() 
"""
#Checks if the csv file exists, if it does, appends it with the new values. If it doesnt,it creates it.

    try:
        f = open('6338_Task1.2.csv', 'r', newline='')
        if not f.readline():
            f.close()
            f = open('6338_Task1.2.csv', 'w', newline='')
            filewriter = csv.writer(f, delimiter=',',
                                    quotechar=' ', quoting=csv.QUOTE_MINIMAL)
            filewriter.writerow(['Image Name', 'ArUco ID', "\0(x.y) Object-1", "\0(x.y) Object-2"])
    except IOError:
        f = open('6338_Task1.2.csv', 'w', newline='')
        filewriter = csv.writer(f, delimiter=',',
                                quotechar=' ', quoting=csv.QUOTE_MINIMAL)
        filewriter.writerow(['Image Name', 'ArUco ID', "\0(x.y) Object-1", "\0(x.y) Object-2"])
    with open('6338_Task1.2.csv', 'a', newline='') as csvfile:
        f = open('temp.txt','r')
        idno = f.readline().strip()
        f.close()
        filewriter = csv.writer(csvfile, delimiter=',',
                                quotechar=' ', quoting=csv.QUOTE_MINIMAL)
        filewriter.writerow(['ArUco' + str(img[5]) + '.jpg', idno, ".(" + str(xc[0]) + "." + str(yc[0]) + ")",
                             ".(" + str(xc[1]) + "." + str(yc[1]) + ")"])
"""  
     


def shape_detect(shape,i):  #Function to detect shape of object by using the number of contour edges
    global check
    approx = cv2.approxPolyDP(i,0.01*cv2.arcLength(i,True),True)
    if len(approx)==3 and shape==1:
       check="True"
       
    elif len(approx)==4and shape==2:
        check="True"
    elif len(approx) > 7 and shape==3:
        check="True"
    return(check)
     
if __name__ == "__main__":    
    aruco_detect("Final_Markers.jpg")

   

