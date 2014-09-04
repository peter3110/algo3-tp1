import random as rnd

file=open('testPeorCasoT','w')

for n in range(10000,100000,10000):
    c=n/100
    file.write(str(n)+' '+str(c)+' ')
    for i in range(n):
        if ((i%(c-1))==0) and (i!=0):
            print "hi", i
            file.write(str(1)+' ')
        else:
            file.write(str(0)+' ')
        #file.write(str(rnd.randint(0,1))+' ')
    file.write('\n')
file.write(str(0))
file.close()
