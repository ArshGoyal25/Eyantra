# -*- coding: utf-8 -*-
"""
**************************************************************************
*                  E-Yantra Robotics Competition
*                  ================================
*  This software is intended to check version compatiability of open source software
*  Theme: ANT BOT
*  MODULE: Task1.1
*  Filename: Task1.1.py
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
"""

import numpy
import cv2
import cv2.aruco as aruco

def aruco_gen(id_aruco, num_pixels):
    aruco_dict = aruco.Dictionary_get(aruco.DICT_5X5_250)     #replace n with no. of bits per pixel and C with the no. of combinations
                                                                                                                        #select n and C from the list mentioned above'''
    img = aruco.drawMarker(aruco_dict, id_aruco, num_pixels - 50)
    cimg=cv2.cvtColor(img,cv2.COLOR_GRAY2BGR)                                                                                           #Converts image to RBG format
    bimg=cv2.copyMakeBorder(cimg,25,25,25,25,cv2.BORDER_CONSTANT, value=(255,255,255))                 #Draws a border on the image
    font=cv2.FONT_HERSHEY_SIMPLEX
    fimg=cv2.putText(bimg, 'ArUco Id = ' + str(id_aruco), (150, 20), font, 0.5,(0,0,255), 1,cv2.LINE_AA)           #Put the text on the image
    cv2.imwrite('ArUco' + str(id_aruco) + '.jpg',fimg)                                                                                          #Displays the image
    cv2.imshow('ArUco' + str(id_aruco) + '.jpg',fimg)                                                                                           #Saves the image
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__":    
   aruco_id=int(input('enter id:'))
   pixels=int(input('enter num pixels:'))
   aruco_gen(aruco_id,pixels)
   





