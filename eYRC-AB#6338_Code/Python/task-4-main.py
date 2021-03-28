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
from aruco_lib import *
##############################################################################
class AntHill:
    def __init__(self, t1, n, s1, s2):
        self.type = t1
        self.number = n
        self.service1 = s1
        self.service2 = s2
#############################

"""
*Function Name:start
*Input: None
*Output: Writes back to the serial stream 
*Logic: Recieves  a signal from Arduino  indicating it is ready for process and then writes back to the serial stream to start processing of the Arduino code (Boots up the robot and establishes connection between the Arduino and Pi)
*Example Call: start();
"""

def start():
    s = serial.Serial("/dev/ttyUSB2", 9600,        #Attaches serial stream to an object s
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)
    while True:                                             #Starts  up the bot when the python file is executed
        t = s.read(1)                                       #Reads a byte from the serial stream
        val = str(t).strip("b'").strip("\\n").strip("\\r")  #Strips the strings to appropriate format
        if (val=='X'):                                      #Checks for the right value
            s.write(bytes('Z', 'utf-8'))                    #Writes back to the Arduino starting up the bot when the Python file is executed
            print("Started")
            break
    


    
###############################################################################


"""
*Function Name: ArUco_Detect
*Input: None
*Output: Creates a list with all the ArUco Id's 
*Logic:  Recieves a signal from the Arduino when the bot is in the right orientation, captures images through the PiCam and detects the ArUco Id's using ArUco library functions 
*Example Call: AeUco_Detect();
"""


def ArUco_Detect():
    print("Starting ArUco Detect")
    cntr = "1"                                      #Declaring counter variable as 1 (Counts the no. of ArUco's detected)
    exit_response = "E"                             #Used to signal that all the ArUco's are detected
    s = serial.Serial("/dev/ttyUSB2", 9600,         # assigns the serial stream ( link between the Arduino and Pi ) to an object s
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)

    cap = PiCamera(resolution=(1380, 720), framerate=13.6)
    rc = PiRGBArray(cap, (320, 240))
    cap.framerate = 13.6
    for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320, 240)):
        t = s.read(1)                                #Reads a byte from the Serial Stream and assigns it to variable t
        val = str(t).strip("b'").strip("\\n").strip("\\r")  #Strips the string to appropriate format
        
        if (val == 'S'):                             # Since the Arduino communicates a "S" to the serial stream when orientation is positive
            img = image.array
            cv2.GaussianBlur(img, (5, 5), 0)
            id_aruco_trace = 0
            det_aruco_list = {}
            det_aruco_list = detect_Aruco(img)

            if det_aruco_list:
                img = mark_Aruco(img, det_aruco_list)
                id_aruco_trace = calculate_Robot_State(img, det_aruco_list)
                cv2.imshow("frame", img)
                #cv2.imwrite('Result.jpg', img)
                print(b)
                if len(b) == 4:
                    s.write(bytes(exit_response, 'utf-8'))   #When 4 ArUco's are detected it sends the exit_response communicating that all the ArUco's are detected_
                    print("ArUco Detect Done")
                    break
                elif (len(b)==int(cntr)):
                    s.write(bytes(cntr, 'utf-8'))            #Writes the no. of ArUco's detected to the Serial Stream
                    print(cntr)
                    cntr = int(cntr) + 1
                    print(cntr)
                    cntr = str(cntr)
            cv2.imshow('frame1', img)
        cv2.waitKey(10)
        rc.truncate(0)                              #Clears the image array in every iteration in order to capture live video
    cv2.destroyAllWindows()
    cap.close()                                     # Flushes the stream buffer and closes it
##############################################################################

"""
*Function Name: getinfo
*Input: List of ArUco Id's 
*Output: Decodes the information in each ArUco and sends it to the Serial stream 
*Logic:  Converts the Id's to binary format and picks up information from the required bits. Stores the information in a list of objects  
         and passes all the information in each object of the list one by one to the Arduino
*Example Call: getinfo([195,546,124,6])
"""

def getinfo(c):
    s = serial.Serial("/dev/ttyUSB2", 9600,                         #Assigns the serial stream ( link between the Arduino and Pi )
                      parity=serial.PARITY_NONE,                    #to an object s
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)
    Ah_list=[]                                                     #The list that contains objects of type AntHill
    for i in c:
        a = '{0:08b}'.format(i)
        d0={'0':'R','1':'Q'}
        d1={'00':'0','01':'1','10':'2','11':'3'}
        d3={'0':'N','1':'T'}

        typ = a[0]                                                  #Binary string broken into the right bits to extract respective information from each of them
        num = a[1:3]
        ser2 = a[3:5]
        ser1 = a[5:7]
        tr = a[7]
        d2 = {'00': d3[tr], '01': 'R', '10': 'G', '11': 'B'}
        Ah_list.append(AntHill(d0[typ],d1[num],d2[ser1],d2[ser2]))  #Adding objects with all the informaation of an Anthill to list Ah_list
    for j in Ah_list:
        s.write(bytes(j.type, 'utf-8'))                             #Writing all the information to the stream
        s.write(bytes(j.number,'utf-8'))
        s.write(bytes(j.service1, 'utf-8'))
        s.write(bytes(j.service2, 'utf-8'))
    print("get data done")
############################################################################
"""
*Function Name: shape_detect
*Input:  The contour detected
*Output: Checks if it is a square of 4 units
*Logic:  Detects the  shape of object by using the number of contour edges  
"""
def shape_detect(i):  # Function to detect shape of object by using the number of contour edges
    global check
    approx = cv2.approxPolyDP(i, 0.01 * cv2.arcLength(i, True), True)
    check="False"
    if len(approx) == 4:
        check = "True"
    return (check)
##############################################################################

"""
*Function Name: Colour_Detect()
*Input: None
*Output: Detects and prints the colour of the box. Adds it to the Serial Stream to send it to the Arduino
*Logic:  Captures continous images and finds the RGB values of the centroid of the shape detected.(The box given with side length 4 cms.) 
         Decides the colour of the boxes based on these RGB values.
*Example Call: Colour_Detect()
"""



def Colour_Detect():
    print("Colour Detect has Started")
    s = serial.Serial("/dev/ttyUSB2", 9600,                                 #Assigns the serial stream ( link between the Arduino and Pi ) to an object s
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)

    r1 = g1 = b1 = 0                                                        #Variables that count the no. of red, green and blue values respectively
    colour=list()                                                           #List that stores all the box colours in order
    item=list()                                                             #List that stores the items corresponding to each block (e.g.: Blue - Wood)
    while True:
        read_Byte = s.read(1)                                               #Reads a byte from the Serial Stream and stores it in variable read_Byte
        val = str(read_Byte).strip("b'").strip("\\n").strip("\\r")
        if (val == 'C'):
            cap = PiCamera(resolution=(1380, 720), framerate=13.6)
            rc = PiRGBArray(cap, (320, 240))
            cap.framerate = 13.6
            for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320, 240)):    #Captures continous images to produce a video
                img = image.array
                img = cv2.GaussianBlur(img, (5, 5), 0)
                gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                ret, thresh = cv2.threshold(gray, 100, 255, 0)
                contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2:]
                cv2.imshow("Image", img)
                for i in range(1, len(contours)):
                    b = 0
                    r = 0
                    g = 0
                    M = cv2.moments(contours[i])     #To find the centroid
                    try:
                        cx = int(M['m10'] / M['m00'])
                        cy = int(M['m01'] / M['m00'])
                    except ZeroDivisionError:
                        cx = int(M['m10'])
                        cy = int(M['m01'])
                    b = img[cy, cx, 0]               #To find the BGR values of the centroid respectively
                    g = img[cy, cx, 1]
                    r = img[cy, cx, 2]
                    font = cv2.FONT_HERSHEY_SIMPLEX
                    i = 0
                    if (r > b and r > g):                #If Red value of the pixel at the centroid is greatest then increment red counter
                        check = shape_detect(contours[i]) #Only if the shape is a square of 4 units
                        if check == "True":
                            print("R")
                            r1 += 1
                            cv2.drawContours(img, contours, i, (0, 255, 0), 5)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)
                    elif (g > r and g > b):                 #If Green value of the pixel at the centroid is greatest then increment green counte
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("G")
                            g1 += 1
                            cv2.drawContours(img, contours, i, (255, 0, 0), 25)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)
                    elif (b > r and b > g):                #If Blue value of the pixel at the centroid is greatest then increment blue count
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("B")
                            b1 += 1
                            cv2.drawContours(img, contours, i, (0, 255, 0), 25)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)

                    if (r1 > 50):                           #If pixel at the centroid is detected as red 50 times (To improve accuracy as sometimes contours are not detected properly)
                        colour.append("blue")
                        item.append("Wood")
                        print(colour)
                        print(item)
                        s.write(bytes('B','utf-8'))
                        break
                    elif (g1 > 50):                          #If pixel at the centroid is detected as green 50 times
                        colour.append("green")
                        item.append("Leaves")
                        print(colour)
                        print(item)
                        s.write(bytes('G', 'utf-8'))
                        break
                    elif (b1 > 50):                          #If pixel at the centroid is detected as blue 50 times
                        colour.append("red")
                        item.append("HoneyDew")
                        print(colour)
                        print(item)
                        s.write(bytes('R', 'utf-8'))
                        break
                if (b1 > 50 or g1 > 50 or r1 > 50):         #Resetting the counter values back to zero for the next iteration
                    val = " "
                    r1 = b1 = g1 = 0
                    break
                cv2.waitKey(10)
                rc.truncate(0)

            cap.close()
            cv2.destroyAllWindows()

        if (len(colour) == 6):                              #If all six boxes are detected then break out of the loop
            break
##############################################################################

"""
*Function Name: Trash_Detect()
*Input: None
*Output: Detects whether thrash is present at a certain location or not and passes the information to the Arduino
*Logic:  Captures continous images and finds the RGB values of the centroid of the shape detected.(The box given with side length 4 cms.) 
         Decides the colour of the boxes based on these RGB values.
*Example Call: Colour_Detect()
"""

def Trash_Detect():
    print("Trash Detect has Started")
    s = serial.Serial("/dev/ttyUSB0", 9600,                   #Assigns the serial stream ( link between the Arduino and Pi) to an object s
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)
    n1 = y1 = 0                                               #Initializes counter variables (n1,y1)for nothing and thrash respectively to zero
    t = s.read(1)                                             #Reads a single byte from the serial stream and stores it in variable t
    val = str(t).strip("b'").strip("\\n").strip("\\r")
    while True:
        if (val == 'Detect'):                                  #If arduino is in the right orientation and PiCam can be turned on to capture images
            cap = PiCamera(resolution=(1380, 720), framerate=13.6)
            rc = PiRGBArray(cap, (320, 240))
            cap.framerate = 13.6
            for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320, 240)): #To provide continous image feedd
                img = image.array
                img = cv2.GaussianBlur(img, (5, 5), 0)
                gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                ret, thresh = cv2.threshold(gray, 100, 255, 0)
                contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2:]
                for i in range(1, len(contours)):
                    b = 0
                    r = 0
                    g = 0
                    M = cv2.moments(contours[i])             #To find the centroid
                    try:
                        cx = int(M['m10'] / M['m00'])
                        cy = int(M['m01'] / M['m00'])
                    except ZeroDivisionError:
                        cx = int(M['m10'])
                        cy = int(M['m01'])
                    b = img[cy, cx, 0]                       #To find the BGR values of the centroid respectively
                    g = img[cy, cx, 1]
                    r = img[cy, cx, 2]
                    font = cv2.FONT_HERSHEY_SIMPLEX
                    i = 0
                    if (r > 100 and g > 75 and b < 75):      #Conditional statement, executed when colour of the centroid is yellow
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("Y")
                            y1 += 1                          #Increments the yellow counter
                            cv2.drawContours(img, contours, i, (0, 255, 0), 5)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)
                    else:
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("N")
                            n1 += 1                           #Increments the counter for nothing if yellow is not detected
                            cv2.drawContours(img, contours, i, (0, 255, 0), 5)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)

                    if (y1 > 50):                             #If pixel at the centroid is detected yellow 50 times
                        print("Trash Detected")
                        s.write(bytes("Y", 'utf-8'))
                        break
                    elif (n1 > 50):                             #If nothing(not yellow) is detected 50 times
                        print("No Trash Detected")
                        s.write(bytes("N", 'utf-8'))
                        break
                if (y1 > 50 or n1 > 50):                       #Resetting the counter variables to zero
                    break;
                cv2.waitKey(10)
                rc.truncate(0)

            cap.close()
            cv2.destroyAllWindows()
            break
##############################################################################

"""
*Function Name:main
*Input: NONE
*Output: Executes all the functions defined in the file
*Example Call: Called automatically by the Operating System
"""
if __name__ == '__main__':
    start()
    ArUco_Detect()
    Colour_Detect()
    getinfo(b)    
    Trash_Detect()

