import stp
import math
from time import *
import os
import sys
#import psutil
t1 = time()
s = stp.Solver()

# variables
alpha0 = [s.bitvec('alpha0_'+str(i),1) for i in range(128)]
alpha1 = [s.bitvec('alpha1_'+str(i),1) for i in range(128)]
beta0 = [s.bitvec('beta0_'+str(i),1) for i in range(128)]
beta1 = [s.bitvec('beta1_'+str(i),1) for i in range(128)]
gamma0 = [s.bitvec('gamma0_'+str(i),1) for i in range(128)]
gamma1 = [s.bitvec('gamma1_'+str(i),1) for i in range(128)]
b0 = [s.bitvec('b0_'+str(i),1) for i in range(128)]
b1 = [s.bitvec('b1_'+str(i),1) for i in range(128)]
c0 = [s.bitvec('c0_'+str(i),1) for i in range(128)]
c1 = [s.bitvec('c1_'+str(i),1) for i in range(128)]
d0 = [s.bitvec('d0_'+str(i),1) for i in range(128)]
d1 = [s.bitvec('d1_'+str(i),1) for i in range(128)]
e0 = [s.bitvec('e0_'+str(i),1) for i in range(128)]
e1 = [s.bitvec('e1_'+str(i),1) for i in range(128)]
e12 = [s.bitvec('e12_'+str(i),1) for i in range(128)]
e22 = [s.bitvec('e22_'+str(i),1) for i in range(128)]
e13 = [s.bitvec('e13_'+str(i),1) for i in range(128)]
e23 = [s.bitvec('e23_'+str(i),1) for i in range(128)]
v1 = [s.bitvec('v1_'+str(i),1) for i in range(128)]
v2 = [s.bitvec('v2_'+str(i),1) for i in range(128)]
v3 = [s.bitvec('v3_'+str(i),1) for i in range(128)]
v4 = [s.bitvec('v4_'+str(i),1) for i in range(128)]
v5 = [s.bitvec('v5_'+str(i),1) for i in range(128)]
v6 = [s.bitvec('v6_'+str(i),1) for i in range(128)]
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
w13 = [s.bitvec('w13_'+str(i),1) for i in range(128)]
w14 = [s.bitvec('w14_'+str(i),1) for i in range(128)]
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
SM = [s.bitvec('SM_'+str(i),32) for i in range(16)]
SN = [s.bitvec('SN_'+str(i),32) for i in range(16)]

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
S13 = s.bitvec('S13',32)
S14 = s.bitvec('S14',32)

Total = s.bitvec('Total',32)

# nonzero constraint
def nz():
    temp = alpha0[0] | alpha1[0] | beta0[0] | beta1[0] |  gamma0[0] | gamma1[0]
    for i in range(1, 128):
        temp |= alpha0[i] | alpha1[i] | beta0[i] | beta1[i] |  gamma0[i] | gamma1[i]
    s.add(temp == 1)
def linear():
    file = open('lineardouble.txt','r')
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


# buxiugai   constraints for more trails
def cons(result):
    tempalpha1 = alpha1[0] ^ result['alpha1_0']
    tempalpha0 = alpha0[0] ^ result['alpha0_0']
    tempbeta1 = beta1[0] ^ result['beta1_0']
    tempbeta0 = beta0[0] ^ result['beta0_0']
    tempgamma1 = gamma1[0] ^ result['gamma1_0']
    tempgamma0 = gamma0[0] ^ result['gamma0_0']
    tempd0 = d0[0] ^ result['d0_0']
    tempd1 = d1[0] ^ result['d1_0']
    tempe1 = e1[0] ^ result['e1_0']
    tempe0 = e0[0] ^ result['e0_0']
    tempb0 = b0[0] ^ result['b0_0']
    tempb1 = b1[0] ^ result['b1_0']
    tempc1 = c1[0] ^ result['c1_0']
    tempc0 = c0[0] ^ result['c0_0']
    tempe12 = e12[0] ^ result['e12_0']
    tempe22 = e22[0] ^ result['e22_0']
    tempe13= e13[0] ^ result['e13_0']
    tempe23 = e23[0] ^ result['e23_0']
    for i in range(1,128):
        tempalpha1 |= alpha1[i] ^ result['alpha1_'+str(i)]
        tempalpha0 |= alpha0[i] ^ result['alpha0_'+str(i)]
        tempbeta1 |= beta1[i] ^ result['beta1_'+str(i)]
        tempbeta0 |= beta0[i] ^ result['beta0_'+str(i)]
        tempgamma1 |= gamma1[i] ^ result['gamma1_'+str(i)]
        tempgamma0 |= gamma0[i] ^ result['gamma0_'+str(i)]
        tempd0 |= d0[i] ^ result['d0_' + str(i)]
        tempd1 |= d1[i] ^ result['d1_' + str(i)]
        tempe1 |= e1[i] ^ result['e1_' + str(i)]
        tempe0 |= e0[i] ^ result['e0_' + str(i)]
        tempb0 |= b0[i] ^ result['b0_'+str(i)]
        tempb1 |= b1[i] ^ result['b1_'+str(i)]
        tempc1 |= c1[i] ^ result['c1_'+str(i)]
        tempc0 |= c0[i] ^ result['c0_'+str(i)]
        tempe12 |= e12[i] ^ result['e12_'+str(i)]
        tempe22 |= e22[i] ^ result['e22_'+str(i)]
        tempe13 |= e13[i] ^ result['e13_'+str(i)]
        tempe23 |= e23[i] ^ result['e23_'+str(i)]

    s.add(tempalpha1 | tempalpha0 | tempbeta1 | tempbeta0 | tempgamma1 | tempgamma0 | tempd1 | tempd0 | tempe1 | tempe0| tempc1 | tempc0 | tempb1 | tempb0  | tempe12  | tempe22 | tempe13 | tempe23 == 1)

# objective function
def obj(lim):
    s.add(Total == S1 + S2 + S3 + S4 + S5 + S6 + S7 + S8 + S9 + S10 + S11 + S12 + S13 + S14 )
    s.add(Total < lim)

def ending(result,ff):
    alpham0 = [0,0,0,0]
    alpham1 = [0,0,0,0]
    betam0 = [0,0,0,0]
    betam1 = [0,0,0,0]
    gammam0 = [0,0,0,0]
    gammam1 = [0,0,0,0]
    dm0 = [0,0,0,0]
    dm1 = [0,0,0,0]
    em0 = [0,0,0,0]
    em1 = [0,0,0,0]
    bm0 = [0,0,0,0]
    bm1 = [0,0,0,0]
    cm0 = [0,0,0,0]
    cm1 = [0,0,0,0]
    em12 = [0,0,0,0]
    em22 = [0,0,0,0]
    em13 = [0,0,0,0]
    em23 = [0,0,0,0]
    vm1 = [0,0,0,0]
    vm2 = [0,0,0,0]
    vm3 = [0,0,0,0]
    vm4 = [0,0,0,0]
    vm5 = [0,0,0,0]
    vm6 = [0,0,0,0]
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
    wm13 = [0,0,0,0]
    wm14 = [0,0,0,0]

    for i in range(4):
        for j in range(32):
            alpham0[i] ^= int(result['alpha0_'+str(32*i+j)]) << j
            alpham1[i] ^= int(result['alpha1_'+str(32*i+j)]) << j
            betam0[i] ^= int(result['beta0_'+str(32*i+j)]) << j
            betam1[i] ^= int(result['beta1_'+str(32*i+j)]) << j
            gammam0[i] ^= int(result['gamma0_'+str(32*i+j)]) << j
            gammam1[i] ^= int(result['gamma1_'+str(32*i+j)]) << j
            dm0[i] ^= int(result['d0_' + str(32 * i + j)]) << j
            dm1[i] ^= int(result['d1_' + str(32 * i + j)]) << j
            em0[i] ^= int(result['e0_' + str(32 * i + j)]) << j
            em1[i] ^= int(result['e1_' + str(32 * i + j)]) << j
            bm0[i] ^= int(result['b0_' + str(32 * i + j)]) << j
            bm1[i] ^= int(result['b1_' + str(32 * i + j)]) << j
            cm0[i] ^= int(result['c0_' + str(32 * i + j)]) << j
            cm1[i] ^= int(result['c1_' + str(32 * i + j)]) << j
            em12[i] ^= int(result['e12_' + str(32 * i + j)]) << j
            em22[i] ^= int(result['e22_' + str(32 * i + j)]) << j
            em13[i] ^= int(result['e13_' + str(32 * i + j)]) << j
            em23[i] ^= int(result['e23_' + str(32 * i + j)]) << j
            vm1[i] ^= int(result['v1_'+str(32*i+j)]) << j
            vm2[i] ^= int(result['v2_'+str(32*i+j)]) << j
            vm3[i] ^= int(result['v3_'+str(32*i+j)]) << j
            vm4[i] ^= int(result['v4_'+str(32*i+j)]) << j
            vm5[i] ^= int(result['v5_'+str(32*i+j)]) << j
            vm6[i] ^= int(result['v6_'+str(32*i+j)]) << j
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
            wm13[i] ^= int(result['w13_' + str(32 * i + j)]) << j
            wm14[i] ^= int(result['w14_' + str(32 * i + j)]) << j

    print('alpha0: %08x, %08x, %08x, %08x' %(alpham0[3], alpham0[2], alpham0[1], alpham0[0]))
    print('alpha1: %08x, %08x, %08x, %08x' %(alpham1[3], alpham1[2], alpham1[1], alpham1[0]))
    print('beta0: %08x, %08x, %08x, %08x' %(betam0[3], betam0[2], betam0[1], betam0[0]))
    print('beta1: %08x, %08x, %08x, %08x' %(betam1[3], betam1[2], betam1[1], betam1[0]))
    print('gamma0: %08x, %08x, %08x, %08x' %(gammam0[3], gammam0[2], gammam0[1], gammam0[0]))
    print('gamma1: %08x, %08x, %08x, %08x' %(gammam1[3], gammam1[2], gammam1[1], gammam1[0]))
    print('b0: %08x, %08x, %08x, %08x' % (bm0[3], bm0[2], bm0[1], bm0[0]))
    print('b1: %08x, %08x, %08x, %08x' % (bm1[3], bm1[2], bm1[1], bm1[0]))
    print('c0: %08x, %08x, %08x, %08x' % (cm0[3], cm0[2], cm0[1], cm0[0]))
    print('c1: %08x, %08x, %08x, %08x' % (cm1[3], cm1[2], cm1[1], cm1[0]))
    print('d0: %08x, %08x, %08x, %08x' % (dm0[3], dm0[2], dm0[1], dm0[0]))
    print('d1: %08x, %08x, %08x, %08x' % (dm1[3], dm1[2], dm1[1], dm1[0]))
    print('e0: %08x, %08x, %08x, %08x' % (em0[3], em0[2], em0[1], em0[0]))
    print('e1: %08x, %08x, %08x, %08x' % (em1[3], em1[2], em1[1], em1[0]))
    print('e12: %08x, %08x, %08x, %08x' % (em12[3], em12[2], em12[1], em12[0]))
    print('e22: %08x, %08x, %08x, %08x' % (em22[3], em22[2], em22[1], em22[0]))
    print('e13: %08x, %08x, %08x, %08x' % (em13[3], em13[2], em13[1], em13[0]))
    print('e23: %08x, %08x, %08x, %08x' % (em23[3], em23[2], em23[1], em23[0]))
    print('v1: %08x, %08x, %08x, %08x' %(vm1[3], vm1[2], vm1[1], vm1[0]))
    print('v2: %08x, %08x, %08x, %08x' %(vm2[3], vm2[2], vm2[1], vm2[0]))
    print('v3: %08x, %08x, %08x, %08x' %(vm3[3], vm3[2], vm3[1], vm3[0]))
    print('v4: %08x, %08x, %08x, %08x' %(vm4[3], vm4[2], vm4[1], vm4[0]))
    print('v5: %08x, %08x, %08x, %08x' %(vm5[3], vm5[2], vm5[1], vm5[0]))
    print('v6: %08x, %08x, %08x, %08x' %(vm6[3], vm6[2], vm6[1], vm6[0]))
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
    print('w13: %08x, %08x, %08x, %08x' %(wm13[3], wm13[2], wm13[1], wm13[0]))
    print('w14: %08x, %08x, %08x, %08x' %(wm14[3], wm14[2], wm14[1], wm14[0]))

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
    print('S13: %d' %result['S13'])
    print('S14: %d' %result['S14'])

    print('Total: %d' %result['Total'])

    print(result, file=ff)
    print('alpha0: %08x, %08x, %08x, %08x' %(alpham0[3], alpham0[2], alpham0[1], alpham0[0]),file=ff)
    print('alpha1: %08x, %08x, %08x, %08x' %(alpham1[3], alpham1[2], alpham1[1], alpham1[0]),file=ff)
    print('beta0: %08x, %08x, %08x, %08x' %(betam0[3], betam0[2], betam0[1], betam0[0]),file=ff)
    print('beta1: %08x, %08x, %08x, %08x' %(betam1[3], betam1[2], betam1[1], betam1[0]),file=ff)
    print('gamma0: %08x, %08x, %08x, %08x' %(gammam0[3], gammam0[2], gammam0[1], gammam0[0]),file=ff)
    print('gamma1: %08x, %08x, %08x, %08x' %(gammam1[3], gammam1[2], gammam1[1], gammam1[0]),file=ff)
    print('b0: %08x, %08x, %08x, %08x' % (bm0[3], bm0[2], bm0[1], bm0[0]),file=ff)
    print('b1: %08x, %08x, %08x, %08x' % (bm1[3], bm1[2], bm1[1], bm1[0]),file=ff)
    print('c0: %08x, %08x, %08x, %08x' % (cm0[3], cm0[2], cm0[1], cm0[0]),file=ff)
    print('c1: %08x, %08x, %08x, %08x' % (cm1[3], cm1[2], cm1[1], cm1[0]),file=ff)
    print('d0: %08x, %08x, %08x, %08x' % (dm0[3], dm0[2], dm0[1], dm0[0]), file=ff)
    print('d1: %08x, %08x, %08x, %08x' % (dm1[3], dm1[2], dm1[1], dm1[0]), file=ff)
    print('e0: %08x, %08x, %08x, %08x' % (em0[3], em0[2], em0[1], em0[0]), file=ff)
    print('e1: %08x, %08x, %08x, %08x' % (em1[3], em1[2], em1[1], em1[0]), file=ff)
    print('e12: %08x, %08x, %08x, %08x' % (em12[3], em12[2], em12[1], em12[0]),file=ff)
    print('e22: %08x, %08x, %08x, %08x' % (em22[3], em22[2], em22[1], em22[0]),file=ff)
    print('e13: %08x, %08x, %08x, %08x' % (em13[3], em13[2], em13[1], em13[0]),file=ff)
    print('e23: %08x, %08x, %08x, %08x' % (em23[3], em23[2], em23[1], em23[0]),file=ff)
    print('v1: %08x, %08x, %08x, %08x' %(vm1[3], vm1[2], vm1[1], vm1[0]),file=ff)
    print('v2: %08x, %08x, %08x, %08x' %(vm2[3], vm2[2], vm2[1], vm2[0]),file=ff)
    print('v3: %08x, %08x, %08x, %08x' %(vm3[3], vm3[2], vm3[1], vm3[0]),file=ff)
    print('v4: %08x, %08x, %08x, %08x' %(vm4[3], vm4[2], vm4[1], vm4[0]),file=ff)
    print('v5: %08x, %08x, %08x, %08x' %(vm5[3], vm5[2], vm5[1], vm5[0]),file=ff)
    print('v6: %08x, %08x, %08x, %08x' %(vm6[3], vm6[2], vm6[1], vm6[0]),file=ff)
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
    print('w13: %08x, %08x, %08x, %08x' %(wm13[3], wm13[2], wm13[1], wm13[0]),file=ff)
    print('w14: %08x, %08x, %08x, %08x' %(wm14[3], wm14[2], wm14[1], wm14[0]),file=ff)
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
    print('S13: %d' %result['S13'], file = ff)
    print('S14: %d' %result['S14'], file = ff)

    print('Total: %d' %result['Total'],file=ff)

# multiple solving
def ms(times):
    ff = open('DOUBLE(active sboxes).txt', 'a')
    for i in range(times):
        if s.check() == True:
            result = s.model()
            ending(result,ff)
            print('%d' % i)
            print('%d' % i, file = ff)
            t2 = time()
            print(t2 - t1)
            print(t2 - t1, file = ff)
            cons(result)
           # print('%d' % i, file=ff)
        else:
            print('End, %d solutions' %i)
            print('End, %d solutions' %i, file = ff)
            break
    ff.close()


nz()                                       # nonzero constraint
linear()

Exchange(alpha0,c1,v1)                           # Xor of masks
Exchange(alpha1,c0,v2)
Exchange(e12,e13,v3)
Exchange(e22,e23,v4)
Exchange(b0,beta0,v5)
Exchange(b1,beta1,v6)
AES_P(w1,v1)                                # AES_P transformation
AES_P(w2,v2)
AES_P(w3,e12)
AES_P(w4,e22)                                # AES_P transformation
AES_P(w5,b0)
AES_P(w6,b1)
AES_P(w7,beta0)                                # AES_P transformation
AES_P(w8,beta1)
AES_P(w9,e13)
AES_P(w10,e23)
AES_P(w11,gamma0)
AES_P(w12,gamma1)
AES_P(w13,gamma0)
AES_P(w14,gamma1)
Sbox('e12','w1','SA','S1')            # S-boxes
Sbox('e22','w2','SB','S2')
Sbox('c0','w3','SC','S3')
Sbox('c1','w4','SD','S4')
Sbox('alpha0','w5','SE','S5')
Sbox('alpha1','w6','SF','S6')
Sbox('v3','w7','SG','S7')
Sbox('v4','w8','SH','S8')
Sbox('c0','w9','SI','S9')
Sbox('c1','w10','SJ','S10')
Sbox('v5','w11','SK','S11')
Sbox('v6','w12','SL','S12')
Sbox('e13','w13','SM','S13')
Sbox('e23','w14','SN','S14')

#cond()                                     # condition
obj(50)                                # objective function
# searching for multiple linear trails
ms(1)
# time
t2 = time()
print(t2-t1)
