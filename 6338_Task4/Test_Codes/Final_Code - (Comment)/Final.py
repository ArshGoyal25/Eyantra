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
###############################################################################
def ArUco_Detect():
    print("Starting ArUco Detect")
    a = "1"
    d = 0
    print(type(a))
    c = "E"
    s = serial.Serial("/dev/ttyUSB0", 9600,
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)

    cap = PiCamera(resolution=(1380, 720), framerate=13.6)
    rc = PiRGBArray(cap, (320, 240))
    cap.framerate = 13.6
    for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320, 240)):
        t = s.read(1)
        val = str(t).strip("b'").strip("\\n").strip("\\r")
        if (val == 'S'):
            img = image.array
            cv2.GaussianBlur(img, (5, 5), 0)
            id_aruco_trace = 0
            det_aruco_list = {}
            det_aruco_list = detect_Aruco(img)

            if det_aruco_list:
                img = mark_Aruco(img, det_aruco_list)
                id_aruco_trace = calculate_Robot_State(img, det_aruco_list)
                cv2.imshow("frame", img)
                cv2.imwrite('Result.jpg', img)
                print(b)
                if len(b) == 4:
                    s.write(bytes(c, 'utf-8'))
                    print("ArUco Detect Done")
                    break
                else:
                    s.write(bytes(a, 'utf-8'))
                    print(a)
                    a = int(a) + 1
                    print(a)
                    a = str(a)
            cv2.imshow('frame1', img)
        cv2.waitKey(10)
        rc.truncate(0)
    cv2.destroyAllWindows()
    cap.close()
##############################################################################
def getinfo(c):
    s = serial.Serial("/dev/ttyUSB0", 9600,
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)
    Ah_list=[]
    for i in c:
        a = '{0:08b}'.format(i)
        d0={'0':'R','1':'Q'}
        d1={'00':'0','01':"1",'10':'2','11':"3"}
        d3={'0':'N','1':'T'}

        typ = a[0]
        num = a[1:3]
        ser2 = a[3:5]
        ser1 = a[5:7]
        tr = a[7]
        d2 = {'00': d3[tr], '01': 'R', '10': 'G', '11': 'B'}
        Ah_list.append(AntHill(d0[typ],d1[num],d2[ser1],d2[ser2]))
    for j in Ah_list:
        s.write(bytes(j.type, 'utf-8'))
        s.write(bytes(j.number,'utf-8'))
        s.write(bytes(j.service1, 'utf-8'))
        s.write(bytes(j.service2, 'utf-8'))
############################################################################
def shape_detect(i):  # Function to detect shape of object by using the number of contour edges
    global check
    approx = cv2.approxPolyDP(i, 0.01 * cv2.arcLength(i, True), True)
    check="False"
    if len(approx) == 4:
        check = "True"
    return (check)
##############################################################################
def Colour_Detect():
    print("Colour Detect has Started")
    s = serial.Serial("/dev/ttyUSB0", 9600,
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)
    s1 = list()
    s2 = list()
    r1 = g1 = b1 = 0
    while True:
        t = s.read(1)
        val = str(t).strip("b'").strip("\\n").strip("\\r")
        if (val == 'C'):
            cap = PiCamera(resolution=(1380, 720), framerate=13.6)
            rc = PiRGBArray(cap, (320, 240))
            cap.framerate = 13.6
            for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320, 240)):
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
                    M = cv2.moments(contours[i])
                    try:
                        cx = int(M['m10'] / M['m00'])
                        cy = int(M['m01'] / M['m00'])
                    except ZeroDivisionError:
                        cx = int(M['m10'])
                        cy = int(M['m01'])
                    b = img[cy, cx, 0]
                    g = img[cy, cx, 1]
                    r = img[cy, cx, 2]
                    font = cv2.FONT_HERSHEY_SIMPLEX
                    i = 0
                    if (r > b and r > g):
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("R")
                            r1 += 1
                            cv2.drawContours(img, contours, i, (0, 255, 0), 5)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)
                    elif (g > r and g > b):
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("G")
                            g1 += 1
                            cv2.drawContours(img, contours, i, (255, 0, 0), 25)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)
                    elif (b > r and b > g):
                        check = shape_detect(contours[i])
                        if check == "True":
                            print("B")
                            b1 += 1
                            cv2.drawContours(img, contours, i, (0, 255, 0), 25)
                            cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                        cv2.LINE_AA)
                            cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)

                    if (r1 > 50):
                        print("RED")
                        s1.append("red")
                        s2.append("HoneyDew")
                        print(s1)
                        print(s2)
                        s.write(bytes("R", 'utf-8'))
                        break
                    elif (g1 > 50):
                        print("GREEN")
                        s1.append("green")
                        s2.append("Leaves")
                        print(s1)
                        print(s2)
                        s.write(bytes("G", 'utf-8'))
                        break
                    elif (b1 > 50):
                        print("BLUE")
                        s1.append("blue")
                        s2.append("Wood")
                        print(s1)
                        print(s2)
                        s.write(bytes("B", 'utf-8'))
                        break
                if (b1 > 50 or g1 > 50 or r1 > 50):
                    val = " "
                    r1 = b1 = g1 = 0
                    print(r1, b1, g1)
                    break
                cv2.waitKey(10)
                rc.truncate(0)

            cap.close()
            cv2.destroyAllWindows()

        if (len(s1) == 6):
            break
##############################################################################
def Trash_Detect():
    print("Trash Detect has Started")
    s = serial.Serial("/dev/ttyUSB0", 9600,
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)
    n1 = y1 = 0
    t = s.read(1)
    val = str(t).strip("b'").strip("\\n").strip("\\r")
    if (val == 'Detect'):
        cap = PiCamera(resolution=(1380, 720), framerate=13.6)
        rc = PiRGBArray(cap, (320, 240))
        cap.framerate = 13.6
        for image in cap.capture_continuous(rc, format="bgr", use_video_port=True, resize=(320, 240)):
            img = image.array
            img = cv2.GaussianBlur(img, (5, 5), 0)
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            ret, thresh = cv2.threshold(gray, 100, 255, 0)
            contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2:]
            for i in range(1, len(contours)):
                b = 0
                r = 0
                g = 0
                M = cv2.moments(contours[i])
                try:
                    cx = int(M['m10'] / M['m00'])
                    cy = int(M['m01'] / M['m00'])
                except ZeroDivisionError:
                    cx = int(M['m10'])
                    cy = int(M['m01'])
                b = img[cy, cx, 0]
                g = img[cy, cx, 1]
                r = img[cy, cx, 2]
                font = cv2.FONT_HERSHEY_SIMPLEX
                i = 0
                if (r > 100 and g > 75 and b < 75):
                    check = shape_detect(contours[i])
                    if check == "True":
                        print("Y")
                        y1 += 1
                        cv2.drawContours(img, contours, i, (0, 255, 0), 5)
                        cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                    cv2.LINE_AA)
                        cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)
                else:
                    check = shape_detect(contours[i])
                    if check == "True":
                        print("N")
                        n1 += 1
                        cv2.drawContours(img, contours, i, (0, 255, 0), 5)
                        cv2.putText(img, "(" + str(cx) + "," + str(cy) + ")", (cx, cy), font, 0.5, (0, 0, 0), 1,
                                    cv2.LINE_AA)
                        cv2.circle(img, (cx, cy), 5, (0, 0, 0), -1)

                if (y1 > 50):
                    print("Trash Detected")
                    s.write(bytes("Y", 'utf-8'))
                    break
                elif (n1 > 50):
                    print("No Trash Detected")
                    s.write(bytes("N", 'utf-8'))
                    break
            if (y1 > 50 or n1 > 50):
                break;
            cv2.waitKey(10)
            rc.truncate(0)

        cap.close()
        cv2.destroyAllWindows()
##############################################################################
if __name__ == '__main__':
    ArUco_Detect()
    getinfo(b)
    Colour_Detect()
    Trash_Detect()

