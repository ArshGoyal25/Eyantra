class AntHill:
    def __init__(self,t1,n,s1,s2):
        self.t=t1
        self.number=n
        self.service1=s1
        self.service2=s2
        #print(self.t,self.number,self.service1,self.service2)
b=[5,46,195,124]

#AH1=AntHill(b[0],b[1],b[2],b[3])
AH=[]
#a=AntHill(0,0,0,0)
ulti=[]
def getinfo(b):
    idk=["UR","UL","LL","RL"]
    for i in b:
        a = '{0:08b}'.format(i)
        d1={'00':'AH0','01':"AH1",'10':'AH2','11':"AH3"}
        d3={'0':'smokeweed','1':'thrash'}

        typ = a[0]
        num = a[1:3]
        ser2 = a[3:5]
        ser1 = a[5:7]

        tr = a[7]
        d2 = {'00': d3[tr], '01': 'honeydew', '10': 'leaves', '11': 'wood'}
        desc = []

        if typ == "0":

            desc.append("RAH")

        else:
            desc.append("QAH")
        desc.append(d1[num])
        desc.append(d2[ser2])
        desc.append(d2[ser1])
        #a=AntHill(0,0,0,0)
        a.t=desc[0];
        a.number=desc[1];
        a.service1=desc[2];
        a.service2=desc[3];
        AH.append(a)
        #for i in desc:
            #print(i)
#        AH0
        ulti.append(desc)
        #print(desc)
        if len(ulti)==4:
            trulti=(zip(idk,ulti))
           # print(list(trulti))
            #for i in list(trulti):
              #  print(i[1])
print(a.t)         
getinfo(b)
"""
AH0=AntHill()
a=0
for i in ulti:
    for j in i:
        AH0.number=j
        #AH0=AntHill(i[j],i[1],i[2],i[3])
    
print(AH0.number)
AH0.number="hi"
print(AH0.number)
"""
"""
for i in ulti:
    print(i[0])
print(i)

    #for j in i:
      #  AH0=AntHill(j)
        #print(j)
AH0=AntHill(ulti[0][0],ulti[0][1],ulti[0][2],ulti[0][3])
AH1=AntHill(ulti[1][0],ulti[1][1],ulti[1][2],ulti[1][3])
AH2=AntHill(ulti[2][0],ulti[2][1],ulti[2][2],ulti[2][3])
AH3=AntHill(ulti[3][0],ulti[3][1],ulti[3][2],ulti[3][3])
#print(AH0.service1)
"""

