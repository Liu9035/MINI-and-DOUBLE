
from scipy.stats import norm
from scipy.stats import poisson
from scipy.stats import binom
import math
n=256

num=[0 for i in range(9)]
nu=[[20,2187,51377,583225,4317501,24970178,120348912,494642170,1767822958],
  [27,2220,51425,583268,4321145,24974297,120353655,494620973,1767810857]]
nus=0
B=15
for i in range(0, 9):
    num[i]=nu[0][i]+nu[1][i]
    print("absolute correlation 2^-%d, number %d = 2^%f\n" % (i+119,num[i],math.log(num[i], 2)))
for i in range(0, 9):
    nus=nus+num[i]
print("total number %d,2^%f\n" %(nus,math.log(nus,2)))

for B in range(15, 16):
  NN= 250
  N = 2 ** (NN)
  for th in range(140000,120000,-1):
    #print("%d\n" %(th))
    flag=0
    thh=th/1000
    #th=2**(thh)
    sum = 0
    nus=0
    nus0=0
    nus1=0
    sum0=0
    sum1=0
    for i in range(0, 9):
        if(nu[0][i]!=0):
            cc=0-(i+119)
            c=2**(cc)
            m=nu[0][i]
            nus=nus+m
            if(-3<(math.pow(2,thh-NN/2)-math.pow(2,cc+NN/2))<3):
              e1=(1-norm.cdf(math.pow(2,thh-NN/2)-math.pow(2,cc+NN/2),loc=0,scale=1))
              sum = sum + m * (2 ** (-B)) * e1
            elif ((math.pow(2,thh-NN/2)-math.pow(2,cc+NN/2))>3):
              e11=math.log(math.e,2)*(-2**(249-NN))*((2**(thh-125)-2**(cc+NN-125))**2)
              e1=math.pow(2,e11)
              sum = sum + m * (2 ** (-B+e11))
            elif ((math.pow(2,thh-NN/2) - math.pow(2,cc+NN/2)) <-3):
              e11 = math.log(math.e, 2) * (-2**(249-NN))*((2**(thh-125)-2**(cc+NN-125))**2)
              e1 = math.pow(2, e11)
              sum = sum + m * (2 ** (-B)) -  m * (2 ** (-B+e11))

    sum0=sum
    for i in range(0, 9):
        if(nu[1][i]!=0):
            cc=0-(i+119)
            c=2**(cc)
            m=nu[1][i]
            nus = nus + m
            if (-3 < (math.pow(2,thh-NN/2) - math.pow(2,cc+NN/2)) < 3):
                e2 = (1-norm.cdf(math.pow(2,thh-NN/2)-math.pow(2,cc+NN/2),loc=0,scale=1))
                sum = sum + m * (2 ** (-B)) * e2
            elif ((math.pow(2,thh-NN/2) - math.pow(2,cc+NN/2)) > 3):
                e22 = math.log(math.e, 2) * (-2**(249-NN))*((2**(thh-125)-2**(cc+NN-125))**2)
                e2 = math.pow(2,e22)
                sum = sum + m * (2 ** (-B+e22))
            elif ((math.pow(2,thh-NN/2) - math.pow(2,cc+NN/2)) < -3):
                e22 = math.log(math.e, 2) * (-2**(249-NN))*((2**(thh-125)-2**(cc+NN-125))**2)
                e2 = math.pow(2, e22)
                sum = sum + m * (2 ** (-B)) -m * (2 ** (-B+e22))


    sum1=sum-sum0
    nus1 =nus-nus0
    sumff=math.log(math.e,2)*(-math.pow(2,2*thh-1-NN))
    sumf = (math.pow(2,sumff-B+1+math.log(nus,2)))*((math.pow(2,n-math.log(nus,2)))-1)
    if (sum >9):
       print("B %d,N 2^%f,th 2^%f,the number of associated states passing the first filtering %f, the number of candidate states without associated states passing the first filtering  2^%f, the number of above candidate states after matrix operations 2^%f and define theta = %f \n" % (B,math.log(N,2),thh,sum,math.log(sumf,2),math.log((math.pow(2, sumff - B + 2*math.log(nus, 2))) * ((math.pow(2, n - math.log(nus, 2))) - 1+(sum0*nus0+sum1*nus1)/(math.pow(2, sumff - B + 2*math.log(nus, 2))) ),2),math.log((math.pow(2, sumff - B + 2*math.log(nus, 2))) * ((math.pow(2, n - math.log(nus, 2))) - 1+(sum0*nus0+sum1*nus1)/(math.pow(2, sumff - B + 2*math.log(nus, 2))) ),2)))
       flag = 1
       break
  if(flag==1):
    thp = 3
    ll1=(math.pow(2, sumff - B + 2*math.log(nus, 2))) * ((math.pow(2, n - math.log(nus, 2))) -1+(sum0*nus0+sum1*nus1)/(math.pow(2, sumff - B + 2*math.log(nus, 2))) )
    pff=-125.901
    pf=2**(pff)
    l2 = sum
    ps = (1 - poisson.cdf(thp-1, mu=l2))
    sumf2=(math.pow(2, sumff+pff - B + 2*math.log(nus, 2))) * ((math.pow(2, n - math.log(nus, 2))) - 1+(sum0*nus0+sum1*nus1)/(math.pow(2, sumff - B + 2*math.log(nus, 2))) )
    print("pf:the probability of a possible initial state but the real one passing the second filtering 2^%f, the number of final candidate state 2^%f\n" % (math.log(pf,2),math.log(sumf2,2)))
    t1 = nus
    t2 = (n - B) * 2 ** (n - B) + N
    t3 = (math.pow(2, sumff - B + 2*math.log(nus, 2))) * ((math.pow(2, n - math.log(nus, 2))) - 1+(sum0*nus0+sum1*nus1)/(math.pow(2, sumff - B + 2*math.log(nus, 2))) )*(math.log((sumf*nus/2+sum0*nus0+sum1*nus1),2)+1)
    t4 =  (2 ** 128)+ (2 ** (128+math.log(sumf2,2)))
    T=t1+t2+t3+t4
    D=N
    M=max(nus,N,2**(n-B),sum0+sum1+sumf,sumf*nus/2+sum0*nus0+sum1*nus1)
    print("success probability %f\n" % (ps))
    print("t1 %f,t2 %f,t3 %f,t4 %f\n" % (math.log(t1, 2), math.log(t2, 2), math.log(t3, 2),math.log(t4, 2)))
    print("T %f,D %f,M %f\n" % (math.log(T,2), math.log(D,2), math.log(M,2) ))
    print("Remark: The accuracy of py is not enough to calculate pf(=2^pff), so we should manually input the corresponding parameters in the software-Wolfram Mathematica to calculate pff using formula Log[2, Probability[x >= thp, x ≈ PoissonDistribution[2^(theta - 256)]]].\n")




