"""
 * Team Id: 6338
 * Author List: Arnav,Sujith,Arsh
 * Filename: 6338_Pi_Cam
 * Theme: AntBot
 * Functions: main()
 * Global Variables: NONE
"""
import numpy
import csv
import cv2
import cv2.aruco as aruco
import serial
import time
import RPi.GPIO as GPIO
import picamera
from picamera import PiCamera
from picamera.array import PiRGBArray
import math
from aruco_lib import*

"""
*Function Name:main
*Input: NONE
*Output: Detects Aruco marker and writes the ArucoId to a text file
*Logic: The PiCam is used to detect the Aruco ID from the image feed when it recieves a positive signal from the Arduino (when it is in the right orientation)
*Example Call: Called automatically by the Operating System
"""
s = serial.Serial("/dev/ttyUSB0",9600) # assigns the serial stream ( link between the Arduino and Pi ) to a variable s
cap=PiCamera(resolution=(1380,720),framerate=13.6)
rc=PiRGBArray(cap,(320,240))
cap.framerate=13.6

for image in cap.capture_continuous(rc, format="rgb", use_video_port=True, resize=(320,240)): 
        t = s.read(1) # Reads in binary
        #print(t)
        val = str(t).strip("b'").strip("\\n").strip("\\r") # Conversion from binary to required string format 
        #print(val) 
        if (val=='S'): # Since the Arduino communicates a "S" to the serial stream when orientation is positive
            img=image.array
            cv2.GaussianBlur(img,(5,5),0) #
            id_aruco_trace = 0
            det_aruco_list = {}
            det_aruco_list = detect_Aruco(img)
            if det_aruco_list:
                    img = mark_Aruco(img,det_aruco_list)
                    id_aruco_trace = calculate_Robot_State(img,det_aruco_list)
                    cv2.imshow("frame",img)
                    cv2.imwrite('Result.jpg',img)
            cv2.imshow('frame1',img)
            cv2.waitKey(10)
            rc.truncate(0)
cv2.destroyAllWindows()
s.close() # Flushes the stream buffer and closes it

