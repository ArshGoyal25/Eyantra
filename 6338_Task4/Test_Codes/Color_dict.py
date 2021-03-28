import numpy
import csv
import cv2
import cv2.aruco as aruco
from aruco_lib import *

c_red=0
c_blue=0
c_green=0
blue=[]
green=[]
red=[]
def shape_detect(i):  #Function to detect shape of object by using the number of contour edges
    global check
    approx = cv2.approxPolyDP(i,0.01*cv2.arcLength(i,True),True)
    if len(approx)==4:
        check="True"
    return(check)
#s = serial.Serial("/dev/ttyUSB0",9600) # assigns the serial stream ( link between the Arduino and Pi ) to a variable s
#cap=PiCamera(resolution=(1380,720),framerate=13.6)
#rc=PiRGBArray(cap,(320,240))
#cap.framerate=13.6
cap = cv2.VideoCapture(0)

check="False"
#i=0
#for image in cap.capture_continuous(rc, format="rgb", use_video_port=True, resize=(320,240)): 
while 1:
        ret,img=cap.read()
        #img=image.array
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
                        print("Blue")
                        #c_blue+=1
                        cv2.drawContours(img,contours,i,(0,255,0),5)
                        cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                        cv2.circle(img,(cx,cy),5,(0,0,0),-1)
                        
            elif (r>b and r>g):
                    check=shape_detect(contours[i])
                    if check=="True":
                        print("Red")
                        #c_red+=1
                       # if i not in red:
                         #   red.append(i)
                        cv2.drawContours(img,contours,i,(0,255,0),5)
                        cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                        cv2.circle(img,(cx,cy),5,(0,0,0),-1)

            elif (g>r and g>b):
                    check=shape_detect(contours[i])
                    if check=="True":
                        print("Green")
                        #c_red+=1
                        #if i not in red:
                          #  red.append(i)
                        cv2.drawContours(img,contours,i,(0,255,0),5)
                        cv2.putText(img,"("+str(cx)+","+str(cy)+")", (cx,cy), font, 0.5,(0,0,0), 1,cv2.LINE_AA)
                        cv2.circle(img,(cx,cy),5,(0,0,0),-1)
            cv2.imshow("Image",img)
            if cv2.waitKey(1)==27:
                break
            #if len(red)==len(blue)==len(green)==2:
              #  exit(0)
            #rc.truncate(0)
#We are detecting the colour of the object by picking up the RBG value of the pixel at the centroid
#coordinates that help to determine the colour of that pixel and hence the entite shape.
#cv2.waitKey(0)
#print(blue,red,green)
cap.release()
cv2.destroyAllWindows()



   

