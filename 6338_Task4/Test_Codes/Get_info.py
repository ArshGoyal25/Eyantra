b=[6,33,208,99]
def getinfo(key):
    for i in b:
        a = '{0:08b}'.format(i)
        d1={'00':'AH0','01':"AH1",'10':'AH2','11':"AH3"}
        d3={'0':'none','1':'thrash'}

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
        #for i in desc:
            #print(i)
        print(desc)
#for i in b:
getinfo(64)

'''if desc(0)=="QAH":
    #Service that first
    #some function
void box_pickup():
    if desc(3)=="leaves":
        s.write(bytes(g, 'utf-8'))
    elif desc(3) == "wood":
        s.write(bytes(b, 'utf-8'))
    if desc(3) == "honeydew":
        s.write(bytes(r, 'utf-8'))
'''
