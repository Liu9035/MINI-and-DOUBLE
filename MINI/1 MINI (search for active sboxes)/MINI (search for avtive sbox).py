import stp
import math
from time import *
import os
import sys
#import psutil
t1 = time()
s = stp.Solver()

# variables
alpha1 = [s.bitvec('alpha1_'+str(i),1) for i in range(128)]
alpha2 = [s.bitvec('alpha2_'+str(i),1) for i in range(128)]
alpha3 = [s.bitvec('alpha3_'+str(i),1) for i in range(128)]
alpha4 = [s.bitvec('alpha4_'+str(i),1) for i in range(128)]
c1 = [s.bitvec('c1_'+str(i),1) for i in range(128)]
c2 = [s.bitvec('c2_'+str(i),1) for i in range(128)]
beta1 = [s.bitvec('beta1_'+str(i),1) for i in range(128)]
beta2 = [s.bitvec('beta2_'+str(i),1) for i in range(128)]
beta3 = [s.bitvec('beta3_'+str(i),1) for i in range(128)]
gamma3 = [s.bitvec('gamma3_'+str(i),1) for i in range(128)]
gamma5 = [s.bitvec('gamma5_'+str(i),1) for i in range(128)]
gamma7 = [s.bitvec('gamma7_'+str(i),1) for i in range(128)]
gamma4 = [s.bitvec('gamma4_'+str(i),1) for i in range(128)]
gamma6 = [s.bitvec('gamma6_'+str(i),1) for i in range(128)]
v1 = [s.bitvec('v1_'+str(i),1) for i in range(128)]
v2 = [s.bitvec('v2_'+str(i),1) for i in range(128)]
v3 = [s.bitvec('v3_'+str(i),1) for i in range(128)]
v4 = [s.bitvec('v4_'+str(i),1) for i in range(128)]
v5 = [s.bitvec('v5_'+str(i),1) for i in range(128)]
v6 = [s.bitvec('v6_'+str(i),1) for i in range(128)]
v7 = [s.bitvec('v7_'+str(i),1) for i in range(128)]
w1 = [s.bitvec('w1_'+str(i),1) for i in range(128)]
w2 = [s.bitvec('w2_'+str(i),1) for i in range(128)]
w3 = [s.bitvec('w3_'+str(i),1) for i in range(128)]
w4 = [s.bitvec('w4_'+str(i),1) for i in range(128)]
w5 = [s.bitvec('w5_'+str(i),1) for i in range(128)]
w6 = [s.bitvec('w6_'+str(i),1) for i in range(128)]
w7 = [s.bitvec('w7_'+str(i),1) for i in range(128)]
w8 = [s.bitvec('w8_'+str(i),1) for i in range(128)]
w9 = [s.bitvec('w9_'+str(i),1) for i in range(128)]
w10 = [s.bitvec('w10_'+str(i),1) for i in range(128)]
w11 = [s.bitvec('w11_'+str(i),1) for i in range(128)]
w12 = [s.bitvec('w12_'+str(i),1) for i in range(128)]
A = [[s.bitvec('A_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
B = [[s.bitvec('B_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
C = [[s.bitvec('C_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
D = [[s.bitvec('D_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
E = [[s.bitvec('E_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
F = [[s.bitvec('F_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
G = [[s.bitvec('G_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
H = [[s.bitvec('H_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
I = [[s.bitvec('I_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
J = [[s.bitvec('J_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
K = [[s.bitvec('K_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
L = [[s.bitvec('L_'+str(i)+'_'+str(j),1) for j in range(16)] for i in range(8)]
SA = [s.bitvec('SA_'+str(i),32) for i in range(16)]
SB = [s.bitvec('SB_'+str(i),32) for i in range(16)]
SC = [s.bitvec('SC_'+str(i),32) for i in range(16)]
SD = [s.bitvec('SD_'+str(i),32) for i in range(16)]
SE = [s.bitvec('SE_'+str(i),32) for i in range(16)]
SF = [s.bitvec('SF_'+str(i),32) for i in range(16)]
SG = [s.bitvec('SG_'+str(i),32) for i in range(16)]
SH = [s.bitvec('SH_'+str(i),32) for i in range(16)]
SI = [s.bitvec('SI_'+str(i),32) for i in range(16)]
SJ = [s.bitvec('SJ_'+str(i),32) for i in range(16)]
SK = [s.bitvec('SK_'+str(i),32) for i in range(16)]
SL = [s.bitvec('SL_'+str(i),32) for i in range(16)]
S1 = s.bitvec('S1',32)
S2 = s.bitvec('S2',32)
S3 = s.bitvec('S3',32)
S4 = s.bitvec('S4',32)
S5 = s.bitvec('S5',32)
S6 = s.bitvec('S6',32)
S7 = s.bitvec('S7',32)
S8 = s.bitvec('S8',32)
S9 = s.bitvec('S9',32)
S10 = s.bitvec('S10',32)
S11 = s.bitvec('S11',32)
S12 = s.bitvec('S12',32)
Total = s.bitvec('Total',32)

# nonzero constraint
def nz():
    temp = alpha1[0] | alpha2[0] | alpha3[0] | alpha4[0]
    for i in range(1, 128):
        temp |= alpha1[i] | alpha2[i] | alpha3[i] | alpha4[i]
    s.add(temp == 1)
def linear():
    file = open('linear.txt', 'r')
    LFSR = file.read()
    exec(LFSR)
    file.close()

# Xor of masks
def Exchange(in1, in2, out):
    for i in range(128):
        s.add(out[i] == in1[i] ^ in2[i])

# AES_P transformation
def AES_P(inp, out):
    file = open('aes_p.txt','r')
    aes_p = file.read()
    exec(aes_p)
    file.close()

# split LCT of Sboxes

def Sbox(inp,out,Ch,sum):
    file = open('sboxR.txt','r')
    pp = file.read()
    for i in range(16):
        for j in range(len(pp)):
            if pp[j] == '(': st = 's.add(s.or_(s.not_(s.and_('
            elif pp[j] == '+': st +=', '
            elif pp[j] == ')':
                st +=')), '+str(Ch)+'['+str(i)+'] == 0))'
                exec(st)
            elif pp[j] == 'i':
                if pp[j+3] == "'": st += str(inp)+'['+str(8*i+eval(pp[j+2]))+'] == 1'
                else: st += str(inp)+'['+str(8*i+eval(pp[j+2]))+'] == 0'
            elif pp[j] == 'o':
                if pp[j+4] == "'": st += str(out)+'['+str(8*i+eval(pp[j+3]))+'] == 1'
                else: st += str(out)+'['+str(8*i+eval(pp[j+3]))+'] == 0'
        TT = 's.add(s.ite('+str(inp)+'['+str(8*i)+'] | '+str(out)+'['+str(8*i)+']'
        for j in range(1,8):
            TT += ' | '+str(inp)+'['+str(8*i+j)+'] | '+str(out)+'['+str(8*i+j)+']'
        TT += ' == 0, '+str(Ch)+'['+str(i)+'] == 0, '+str(Ch)+'['+str(i)+'] == 1))'
        exec(TT)
    com = 's.add('+str(sum)+' == '+str(Ch)+'[0]'
    for i in range(1,16): com += ' + '+str(Ch)+'['+str(i)+']'
    com += ')'
    exec(com)
    file.close()


# constraints for more trails
def cons(result):
    tempalpha1 = alpha1[0] ^ result['alpha1_0']
    tempalpha2 = alpha2[0] ^ result['alpha2_0']
    tempalpha3 = alpha3[0] ^ result['alpha3_0']
    tempalpha4 = alpha4[0] ^ result['alpha4_0']
    tempbeta1 = beta1[0] ^ result['beta1_0']
    tempbeta2 = beta2[0] ^ result['beta2_0']
    tempbeta3 = beta3[0] ^ result['beta3_0']
    tempc1 = c1[0] ^ result['c1_0']
    tempc2 = c2[0] ^ result['c2_0']
    tempgamma3 = gamma3[0] ^ result['gamma3_0']
    tempgamma5 = gamma5[0] ^ result['gamma5_0']
    tempgamma7 = gamma7[0] ^ result['gamma7_0']
    tempgamma4 = gamma4[0] ^ result['gamma4_0']
    tempgamma6 = gamma6[0] ^ result['gamma6_0']

    for i in range(1,128):
        tempalpha1 |= alpha1[i] ^ result['alpha1_'+str(i)]
        tempalpha2 |= alpha2[i] ^ result['alpha2_'+str(i)]
        tempalpha3 |= alpha3[i] ^ result['alpha3_'+str(i)]
        tempalpha4 |= alpha4[i] ^ result['alpha4_'+str(i)]
        tempgamma3 |= gamma3[i] ^ result['gamma3_'+str(i)]
        tempgamma5 |= gamma5[i] ^ result['gamma5_'+str(i)]
        tempgamma7 |= gamma7[i] ^ result['gamma7_'+str(i)]
        tempgamma4 |= gamma4[i] ^ result['gamma4_'+str(i)]
        tempgamma6 |= gamma6[i] ^ result['gamma6_'+str(i)]
        tempbeta1 |= beta1[i] ^ result['beta1_' + str(i)]
        tempbeta2 |= beta2[i] ^ result['beta2_' + str(i)]
        tempbeta3 |= beta3[i] ^ result['beta3_' + str(i)]
        tempc1 |= c1[i] ^ result['c1_' + str(i)]
        tempc2 |= c2[i] ^ result['c2_' + str(i)]


    s.add(tempalpha1 | tempalpha2 | tempalpha3 | tempalpha4 | tempbeta1 | tempbeta2 | tempbeta3 | tempc1 | tempc2  | tempgamma3 | tempgamma5 | tempgamma7 | tempgamma4  | tempgamma6  == 1)


# objective function
def obj(lim):
    s.add(Total == S1 + S2+ S3 + S4 + S5 + S6 + S7 + S8 + S9 + S10 + S11 + S12 )
    s.add(Total < lim)

def ending(result,ff):
    alpham1 = [0,0,0,0]
    alpham2 = [0,0,0,0]
    alpham3 = [0,0,0,0]
    alpham4 = [0,0,0,0]
    cm1 = [0,0,0,0]
    cm2 = [0,0,0,0]
    betam1 = [0,0,0,0]
    betam2 = [0,0,0,0]
    betam3 = [0,0,0,0]
    gammam3 = [0,0,0,0]
    gammam5 = [0,0,0,0]
    gammam7 = [0,0,0,0]
    gammam4 = [0,0,0,0]
    gammam6 = [0,0,0,0]
    vm1 = [0,0,0,0]
    vm2 = [0,0,0,0]
    vm3 = [0,0,0,0]
    vm4 = [0,0,0,0]
    vm5 = [0,0,0,0]
    vm6 = [0, 0, 0, 0]
    vm7 = [0, 0, 0, 0]
    wm1 = [0,0,0,0]
    wm2 = [0,0,0,0]
    wm3 = [0,0,0,0]
    wm4 = [0,0,0,0]
    wm5 = [0,0,0,0]
    wm6 = [0,0,0,0]
    wm7 = [0,0,0,0]
    wm8 = [0,0,0,0]
    wm9 = [0,0,0,0]
    wm10 = [0,0,0,0]
    wm11 = [0,0,0,0]
    wm12 = [0,0,0,0]

    for i in range(4):
        for j in range(32):
            alpham1[i] ^= int(result['alpha1_'+str(32*i+j)]) << j
            alpham2[i] ^= int(result['alpha2_'+str(32*i+j)]) << j
            alpham3[i] ^= int(result['alpha3_'+str(32*i+j)]) << j
            alpham4[i] ^= int(result['alpha4_'+str(32*i+j)]) << j
            cm1[i] ^= int(result['c1_'+str(32*i+j)]) << j
            cm2[i] ^= int(result['c2_'+str(32*i+j)]) << j
            betam1[i] ^= int(result['beta1_'+str(32*i+j)]) << j
            betam2[i] ^= int(result['beta2_'+str(32*i+j)]) << j
            betam3[i] ^= int(result['beta3_' + str(32 * i + j)]) << j
            gammam3[i] ^= int(result['gamma3_'+str(32*i+j)]) << j
            gammam5[i] ^= int(result['gamma5_'+str(32*i+j)]) << j
            gammam7[i] ^= int(result['gamma7_'+str(32*i+j)]) << j
            gammam4[i] ^= int(result['gamma4_'+str(32*i+j)]) << j
            gammam6[i] ^= int(result['gamma6_'+str(32*i+j)]) << j
            vm1[i] ^= int(result['v1_'+str(32*i+j)]) << j
            vm2[i] ^= int(result['v2_'+str(32*i+j)]) << j
            vm3[i] ^= int(result['v3_'+str(32*i+j)]) << j
            vm4[i] ^= int(result['v4_'+str(32*i+j)]) << j
            vm5[i] ^= int(result['v5_'+str(32*i+j)]) << j
            vm6[i] ^= int(result['v6_' + str(32 * i + j)]) << j
            vm7[i] ^= int(result['v7_' + str(32 * i + j)]) << j
            wm1[i] ^= int(result['w1_'+str(32*i+j)]) << j
            wm2[i] ^= int(result['w2_' + str(32 * i + j)]) << j
            wm3[i] ^= int(result['w3_' + str(32 * i + j)]) << j
            wm4[i] ^= int(result['w4_' + str(32 * i + j)]) << j
            wm5[i] ^= int(result['w5_' + str(32 * i + j)]) << j
            wm6[i] ^= int(result['w6_' + str(32 * i + j)]) << j
            wm7[i] ^= int(result['w7_' + str(32 * i + j)]) << j
            wm8[i] ^= int(result['w8_' + str(32 * i + j)]) << j
            wm9[i] ^= int(result['w9_' + str(32 * i + j)]) << j
            wm10[i] ^= int(result['w10_' + str(32 * i + j)]) << j
            wm11[i] ^= int(result['w11_' + str(32 * i + j)]) << j
            wm12[i] ^= int(result['w12_' + str(32 * i + j)]) << j

    print('alpha1: %08x, %08x, %08x, %08x' %(alpham1[3], alpham1[2], alpham1[1], alpham1[0]))
    print('alpha2: %08x, %08x, %08x, %08x' %(alpham2[3], alpham2[2], alpham2[1], alpham2[0]))
    print('alpha3: %08x, %08x, %08x, %08x' %(alpham3[3], alpham3[2], alpham3[1], alpham3[0]))
    print('alpha4: %08x, %08x, %08x, %08x' %(alpham4[3], alpham4[2], alpham4[1], alpham4[0]))
    print('c1: %08x, %08x, %08x, %08x' % (cm1[3], cm1[2], cm1[1], cm1[0]))
    print('c2: %08x, %08x, %08x, %08x' % (cm2[3], cm2[2], cm2[1], cm2[0]))
    print('beta1: %08x, %08x, %08x, %08x' %(betam1[3], betam1[2], betam1[1], betam1[0]))
    print('beta2: %08x, %08x, %08x, %08x' %(betam2[3], betam2[2], betam2[1], betam2[0]))
    print('beta3: %08x, %08x, %08x, %08x' %(betam3[3], betam3[2], betam3[1], betam3[0]))
    print('gamma3: %08x, %08x, %08x, %08x' %(gammam3[3], gammam3[2], gammam3[1], gammam3[0]))
    print('gamma5: %08x, %08x, %08x, %08x' %(gammam5[3], gammam5[2], gammam5[1], gammam5[0]))
    print('gamma7: %08x, %08x, %08x, %08x' %(gammam7[3], gammam7[2], gammam7[1], gammam7[0]))
    print('gamma4: %08x, %08x, %08x, %08x' %(gammam4[3], gammam4[2], gammam4[1], gammam4[0]))
    print('gamma6: %08x, %08x, %08x, %08x' %(gammam6[3], gammam6[2], gammam6[1], gammam6[0]))
    print('v1: %08x, %08x, %08x, %08x' %(vm1[3], vm1[2], vm1[1], vm1[0]))
    print('v2: %08x, %08x, %08x, %08x' %(vm2[3], vm2[2], vm2[1], vm2[0]))
    print('v3: %08x, %08x, %08x, %08x' %(vm3[3], vm3[2], vm3[1], vm3[0]))
    print('v4: %08x, %08x, %08x, %08x' %(vm4[3], vm4[2], vm4[1], vm4[0]))
    print('v5: %08x, %08x, %08x, %08x' %(vm5[3], vm5[2], vm5[1], vm5[0]))
    print('v6: %08x, %08x, %08x, %08x' % (vm6[3], vm6[2], vm6[1], vm6[0]))
    print('v7: %08x, %08x, %08x, %08x' % (vm7[3], vm7[2], vm7[1], vm7[0]))
    print('w1: %08x, %08x, %08x, %08x' %(wm1[3], wm1[2], wm1[1], wm1[0]))
    print('w2: %08x, %08x, %08x, %08x' %(wm2[3], wm2[2], wm2[1], wm2[0]))
    print('w3: %08x, %08x, %08x, %08x' %(wm3[3], wm3[2], wm3[1], wm3[0]))
    print('w4: %08x, %08x, %08x, %08x' %(wm4[3], wm4[2], wm4[1], wm4[0]))
    print('w5: %08x, %08x, %08x, %08x' %(wm5[3], wm5[2], wm5[1], wm5[0]))
    print('w6: %08x, %08x, %08x, %08x' %(wm6[3], wm6[2], wm6[1], wm6[0]))
    print('w7: %08x, %08x, %08x, %08x' %(wm7[3], wm7[2], wm7[1], wm7[0]))
    print('w8: %08x, %08x, %08x, %08x' %(wm8[3], wm8[2], wm8[1], wm8[0]))
    print('w9: %08x, %08x, %08x, %08x' %(wm9[3], wm9[2], wm9[1], wm9[0]))
    print('w10: %08x, %08x, %08x, %08x' %(wm10[3], wm10[2], wm10[1], wm10[0]))
    print('w11: %08x, %08x, %08x, %08x' %(wm11[3], wm11[2], wm11[1], wm11[0]))
    print('w12: %08x, %08x, %08x, %08x' %(wm12[3], wm12[2], wm12[1], wm12[0]))
    print('S1: %d' %result['S1'])
    print('S2: %d' %result['S2'])
    print('S3: %d' %result['S3'])
    print('S4: %d' %result['S4'])
    print('S6: %d' %result['S5'])
    print('S6: %d' %result['S6'])
    print('S7: %d' %result['S7'])
    print('S8: %d' %result['S8'])
    print('S9: %d' %result['S9'])
    print('S10: %d' %result['S10'])
    print('S11: %d' %result['S11'])
    print('S12: %d' %result['S12'])
    print('Total: %d' %result['Total'])

    print(result, file=ff)
    print('alpha1: %08x, %08x, %08x, %08x' %(alpham1[3], alpham1[2], alpham1[1], alpham1[0]),file=ff)
    print('alpha2: %08x, %08x, %08x, %08x' %(alpham2[3], alpham2[2], alpham2[1], alpham2[0]),file=ff)
    print('alpha3: %08x, %08x, %08x, %08x' %(alpham3[3], alpham3[2], alpham3[1], alpham3[0]),file=ff)
    print('alpha4: %08x, %08x, %08x, %08x' %(alpham4[3], alpham4[2], alpham4[1], alpham4[0]),file=ff)
    print('c1: %08x, %08x, %08x, %08x' % (cm1[3], cm1[2], cm1[1], cm1[0]), file=ff)
    print('c2: %08x, %08x, %08x, %08x' % (cm2[3], cm2[2], cm2[1], cm2[0]), file=ff)
    print('beta1: %08x, %08x, %08x, %08x' %(betam1[3], betam1[2], betam1[1], betam1[0]),file=ff)
    print('beta2: %08x, %08x, %08x, %08x' %(betam2[3], betam2[2], betam2[1], betam2[0]),file=ff)
    print('beta3: %08x, %08x, %08x, %08x' %(betam3[3], betam3[2], betam3[1], betam3[0]),file=ff)
    print('gamma3: %08x, %08x, %08x, %08x' %(gammam3[3], gammam3[2], gammam3[1], gammam3[0]),file=ff)
    print('gamma5: %08x, %08x, %08x, %08x' %(gammam5[3], gammam5[2], gammam5[1], gammam5[0]),file=ff)
    print('gamma7: %08x, %08x, %08x, %08x' %(gammam7[3], gammam7[2], gammam7[1], gammam7[0]),file=ff)
    print('gamma4: %08x, %08x, %08x, %08x' %(gammam4[3], gammam4[2], gammam4[1], gammam4[0]),file=ff)
    print('gamma6: %08x, %08x, %08x, %08x' %(gammam6[3], gammam6[2], gammam6[1], gammam6[0]),file=ff)
    print('v1: %08x, %08x, %08x, %08x' %(vm1[3], vm1[2], vm1[1], vm1[0]),file=ff)
    print('v2: %08x, %08x, %08x, %08x' %(vm2[3], vm2[2], vm2[1], vm2[0]),file=ff)
    print('v3: %08x, %08x, %08x, %08x' %(vm3[3], vm3[2], vm3[1], vm3[0]),file=ff)
    print('v4: %08x, %08x, %08x, %08x' %(vm4[3], vm4[2], vm4[1], vm4[0]),file=ff)
    print('v5: %08x, %08x, %08x, %08x' %(vm5[3], vm5[2], vm5[1], vm5[0]),file=ff)
    print('v6: %08x, %08x, %08x, %08x' % (vm6[3], vm6[2], vm6[1], vm6[0]), file=ff)
    print('v7: %08x, %08x, %08x, %08x' % (vm7[3], vm7[2], vm7[1], vm7[0]), file=ff)
    print('w1: %08x, %08x, %08x, %08x' %(wm1[3], wm1[2], wm1[1], wm1[0]),file=ff)
    print('w2: %08x, %08x, %08x, %08x' %(wm2[3], wm2[2], wm2[1], wm2[0]),file=ff)
    print('w3: %08x, %08x, %08x, %08x' %(wm3[3], wm3[2], wm3[1], wm3[0]),file=ff)
    print('w4: %08x, %08x, %08x, %08x' %(wm4[3], wm4[2], wm4[1], wm4[0]),file=ff)
    print('w5: %08x, %08x, %08x, %08x' %(wm5[3], wm5[2], wm5[1], wm5[0]),file=ff)
    print('w6: %08x, %08x, %08x, %08x' %(wm6[3], wm6[2], wm6[1], wm6[0]),file=ff)
    print('w7: %08x, %08x, %08x, %08x' %(wm7[3], wm7[2], wm7[1], wm7[0]),file=ff)
    print('w8: %08x, %08x, %08x, %08x' %(wm8[3], wm8[2], wm8[1], wm8[0]),file=ff)
    print('w9: %08x, %08x, %08x, %08x' %(wm9[3], wm9[2], wm9[1], wm9[0]),file=ff)
    print('w10: %08x, %08x, %08x, %08x' %(wm10[3], wm10[2], wm10[1], wm10[0]),file=ff)
    print('w11: %08x, %08x, %08x, %08x' %(wm11[3], wm11[2], wm11[1], wm11[0]),file=ff)
    print('w12: %08x, %08x, %08x, %08x' %(wm12[3], wm12[2], wm12[1], wm12[0]),file=ff)
    print('S1: %d' %result['S1'],file=ff)
    print('S2: %d' %result['S2'],file=ff)
    print('S3: %d' %result['S3'],file=ff)
    print('S4: %d' %result['S4'],file=ff)
    print('S5: %d' %result['S5'],file=ff)
    print('S6: %d' %result['S6'],file=ff)
    print('S7: %d' %result['S7'],file=ff)
    print('S8: %d' %result['S8'],file=ff)
    print('S9: %d' %result['S9'],file=ff)
    print('S10: %d' %result['S10'], file = ff)
    print('S11: %d' %result['S11'], file = ff)
    print('S12: %d' %result['S12'], file = ff)
    print('Total: %d' %result['Total'],file=ff)

# multiple solving
def ms(times):
    ff = open('MINI(active sboxes).txt', 'a')
    for i in range(times):
        if s.check() == True:
            result = s.model()
            ending(result,ff)
            cons(result)
        else:
            print('End, %d solutions' %i)
            print('End, %d solutions' %i, file = ff)
            break
    ff.close()



nz()                                       # nonzero constraint
linear()
Exchange(beta3,alpha4,v2)
Exchange(alpha1,v2,v1)                           # Xor of masks
Exchange(gamma4,gamma6,v3)
Exchange(gamma5,gamma7,v4)
Exchange(beta2,alpha2,v5)
Exchange(beta1,alpha3,v6)
Exchange(gamma3,v4,v7)
AES_P(w1,v1)                                # AES_P transformation
AES_P(w2,gamma4)
AES_P(w3,gamma3)                                # AES_P transformation
AES_P(w4,beta2)
AES_P(w5,alpha2)
AES_P(w6,gamma6)                                # AES_P transformation
AES_P(w7,v4)
AES_P(w8,beta1)
AES_P(w9,alpha3)
AES_P(w10,gamma7)
AES_P(w11,alpha4)
AES_P(w12,alpha4)
Sbox('gamma3','w1','SA','S1')            # S-boxes
Sbox('v2','w2','SB','S2')
Sbox('gamma4','w3','SC','S3')
Sbox('alpha1','w4','SD','S4')
Sbox('v7','w5','SE','S5')
Sbox('v2','w6','SF','S6')
Sbox('v3','w7','SG','S7')
Sbox('v5','w8','SH','S8')
Sbox('gamma5','w9','SI','S9')
Sbox('gamma6','w10','SJ','S10')
Sbox('v6','w11','SK','S11')
Sbox('gamma7','w12','SL','S12')
#cond()                                     # condition
i=38
obj(i)  # objective function
# searching for multiple linear trails
ms(1)
# time
t2 = time()
print(t2-t1)
