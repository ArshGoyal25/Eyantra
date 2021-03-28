import RPi.GPIO as GPIO
import picamera
from picamera import PiCamera
from picamera.array import PiRGBArray
import numpy
import csv
import cv2
import cv2.aruco as aruco
from aruco_lib import *
import time
import serial
val=0
flag=1
def shape_detect(i):  #Function to detect shape of object by using the number of contour edges
    global check
    approx = cv2.approxPolyDP(i,0.01*cv2.arcLength(i,True),True)
    if len(approx)==4:
        check="True"
    return(check)

s = serial.Serial("/dev/ttyACM0",9600) # assigns the serial stream ( link between the Arduino and Pi ) to a variable s

n1=y1=0

t=s.read(1)
val = str(t).strip("b'").strip("\\n").strip("\\r")
if(val=='S'):
        cap=PiCamera(resolution=(1380,720),framerate=13.6)
        rc=PiRGBArray(cap,(320,240))
        cap.framerate=13.6
        check="False"

        for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320,240)):
                img=image.array
                cv2.imshow("framee",img)
                img = cv2.GaussianBlur(img, (5, 5),0)
                gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
                ret,thresh=cv2.threshold(gray,100,255,0)
                contours,hierarchy=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)[-2:]
                cv2.imshow("test",img)
                cv2.imshow("Image",img)
                 #i+=1
                #if cv2.waitKey(1) == 27:
                #break
                for i in range(1,len(contours)):
                    #print("hii")
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
                    i=0
                    if(r>100 and g>75 and b<75):
                        check=shape_detect(contours[i])
                        if check=="True":
                            print("Y")
                            y1+=1
                            cv2.drawContours(img,contours,i,(0,255,0),5)
                            cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                            cv2.circle(img,(cx,cy),5,(0,0,0),-1)
                    else:
                        check=shape_detect(contours[i])
                        if check=="True":
                            print("N")
                            n1+=1
                            cv2.drawContours(img,contours,i,(0,255,0),5)
                            cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                            cv2.circle(img,(cx,cy),5,(0,0,0),-1)
                                                         
                    if(y1>50):
                        print("Trash Detected")
                        s.write(bytes("Y",'utf-8'))
                        break
                    elif(n1>50):
                        print("No Trash Detected")
                        s.write(bytes("N",'utf-8'))
                        break
                if (y1>50 or n1>50):
                    break;
                cv2.waitKey(10)
                rc.truncate(0)

        cap.close()
    #if(len(s1)==6):
        #break

cv2.destroyAllWindows()

