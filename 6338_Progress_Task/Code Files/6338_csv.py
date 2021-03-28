'''
 * Team Id: 6338
 * Author List: Arnav,Sujith,Arsh
 * Filename: 6338_csv
 * Theme: AntBot
 * Functions: --
 * Global Variables: --

    Everytime the PiCam detects an AruCo marker, we are writing the ID of the AruCo
    in a temporary text file named t.txt. We are then reading from the text file to create a .csv file
    as per the requirements'''
import csv
try:


    f = open('eYRC#AB#6338.csv', 'r', newline='')
    if not f.readline():
        f.close()
        f = open('eYRC#AB#6338.csv', 'w', newline='')
        filewriter = csv.writer(f, delimiter=',',quotechar=' ', quoting=csv.QUOTE_MINIMAL)
        filewriter.writerow(['SIM No', 'ID'])
except IOError:
    f = open('eYRC#AB#6338.csv', 'w', newline='')
    filewriter = csv.writer(f, delimiter=',',quotechar=' ', quoting=csv.QUOTE_MINIMAL)
    filewriter.writerow(['SIM No', 'ID'])
with open('eYRC#AB#6338.csv', 'a', newline='') as csvfile:
    f = open('t.txt', 'r')
    idno = f.readline().strip()
    f.close()
    for i in range(4):
        filewriter = csv.writer(csvfile, delimiter=',',quotechar=' ', quoting=csv.QUOTE_MINIMAL)
        filewriter.writerow(['SIM'+str(i),'ID Detected'])
        
