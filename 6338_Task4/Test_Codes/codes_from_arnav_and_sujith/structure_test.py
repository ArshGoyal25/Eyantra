import serial
import time

class AntHill:

    def __init__(self, t1, n, s1, s2):
        self.type = t1
        self.number = n
        self.service1 = s1
        self.service2 = s2


b={'5','46','195','124'}

def getinfo(c):
    """s = serial.Serial("/dev/ttyUSB0", 9600,
                      parity=serial.PARITY_NONE,
                      stopbits=serial.STOPBITS_ONE,
                      bytesize=serial.EIGHTBITS,
                      timeout=1)"""
    Ah_list=[]
    for i in c:
        z=int(i)
        a = '{0:08b}'.format(z)
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
    #for j in Ah_list:
        #s.write(bytes(j.type, 'utf-8'))
        #s.write(bytes(j.number,'utf-8'))
        #s.write(bytes(j.service1, 'utf-8'))
        #s.write(bytes(j.service2, 'utf-8'))

getinfo(b)




