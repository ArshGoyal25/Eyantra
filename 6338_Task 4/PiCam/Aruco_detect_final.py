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
from aruco_lib import *
value=0
a="1"
d=0
print(type(a))
c="0"
s = serial.Serial("/dev/ttyUSB0",9600,
        parity=serial.PARITY_NONE,
       stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1)
        
cap=PiCamera(resolution=(1380,720),framerate=13.6)
rc=PiRGBArray(cap,(320,240))
cap.framerate=13.6
cap.led=True
for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320,240)):
    t = s.read(1)
    val = str(t).strip("b'").strip("\\n").strip("\\r")
    if (val == 'S'):
        img=image.array
        print('smd')
        #cv2.imwrite('image.jpg',img)
        #img=cv2.imread('image.jpg')
        cv2.GaussianBlur(img,(5,5),0)
        id_aruco_trace = 0
        det_aruco_list = {}
        det_aruco_list = detect_Aruco(img)

        if det_aruco_list:
            img = mark_Aruco(img,det_aruco_list)
            id_aruco_trace = calculate_Robot_State(img,det_aruco_list)
            cv2.imshow("frame",img)
            cv2.imwrite('Result.jpg',img)
            print(b)
            if len(b)==4:
                s.write(bytes(c, 'utf-8'))
                print("DONE")
                break
            else:
                s.write(bytes(a, 'utf-8'))
                print(a)
                a=int(a)+1
                print(a)
                a=str(a)
        cv2.imshow('frame1',img)
        
    cv2.waitKey(10)                                                                                                     
    rc.truncate(0)
    #a=a+1
    #print(a)
    #col_img= cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
       
#cap.release()
cv2.destroyAllWindows()



 

