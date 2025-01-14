#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<math.h>
#include<time.h>

//"-Wl,--stack=0xffffffffff"

typedef unsigned __int64 u64;
typedef unsigned __int32 u32;
typedef unsigned __int8 u8;

void aes_p(u32 state[4])
{
	u32 result[4];
#define ROTL32(word32, offset) ((word32 << offset) | (word32 >> (32 - offset)))
#define SB(index, offset) (((u32)(sb[(index) % 16])) << (offset * 8))
#define MKSTEP(j)\
w = SB(j * 4 + 0, 3) | SB(j * 4 + 5, 0) | SB(j * 4 + 10, 1) | SB(j * 4 + 15, 2);\
t = ROTL32(w, 16) ^ ((w << 1) & 0xfefefefeUL) ^ (((w >> 7) & 0x01010101UL) * 0x1b);\
result[j] = w ^ t ^ ROTL32(t, 8)
	u32 w, t;
	u8 sb[16];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			sb[i * 4 + j] = (state[i] >> (j * 8)) & 0xff;
	MKSTEP(0);
	MKSTEP(1);
	MKSTEP(2);
	MKSTEP(3);
	for (int k = 0; k < 4; k++) state[k] = result[k];
}

void InverseP1(u8 Pmask[256][16]) 
{
	u32 i,j,k;
	u32 temp[4]={0};
	u32 parity;
	for(i=0;i<256;i++)for(j=0;j<128;j++)
	{
		parity=0;
		for(k=0;k<4;k++)temp[k]=0;
		temp[j/32]=1<<(j%32);
		aes_p(temp);
		parity=temp[3]&i;
		parity^=parity>>4;
		parity^=parity>>2;
		parity^=parity>>1;
		parity=parity&1;
		Pmask[i][j/8]^=parity<<(j%8);
	}
}

void InverseP3(u8 Pmask[256][256][256][16]) 
{
	u32 i,j,k,r1,r2;
	u32 temp[4]={0};
	u32 parity;
	for(i=0;i<256;i++)for(j=0;j<256;j++)for(k=0;k<256;k++)for(r1=0;r1<128;r1++)
	{
		parity=0;
		for(r2=0;r2<4;r2++)temp[r2]=0;
		temp[r1/32]=1<<(r1%32);
		aes_p(temp);
		parity=((temp[3]>>8)&i)^((temp[3]>>16)&j)^((temp[3]>>24)&k);
		parity^=parity>>4;
		parity^=parity>>2;
		parity^=parity>>1;
		parity=parity&1;
		Pmask[k][j][i][r1/8]^=parity<<(r1%8);
	}
}

void pu(u8 S[256], double result[256][256], int Sign[256][256]) 
{
	int x, a, b, i;
	int pu[256][256];
	int wt[256];

	for (x = 0; x<256; x++) 
	{
		wt[x] = 0;
		for (i = 0; i<8; i++) wt[x] ^= (x >> i) & 1;
		if (wt[x])	wt[x] = -1;
		else wt[x] = 1;
	}
	for (a = 0; a<256; a++)for (b = 0; b<256; b++)pu[a][b] = 0;

	for (a = 0; a<256; a++)for (b = 0; b<256; b++)	
	{
		for (x = 0; x<256; x++)pu[a][b] += wt[(b&S[x]) ^ (a&x)];
	}
	for (a = 0; a<256; a++)for (b = 0; b<256; b++)
	{
		if(pu[a][b]<0)Sign[a][b]=1;
		else Sign[a][b]=0;
	}
	for (a = 0; a<256; a++)for (b = 0; b<256; b++)
	{
		if (pu[a][b]==0) result[a][b]=(double)9527;
		else result[a][b] = log2((double)(256 / fabs(pu[a][b])));
	}
}

void doing()
{
	time_t t1,t2;
	t1=time(NULL);

	u8 S[256] = {
		0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
		0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
		0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
		0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
		0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
		0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
		0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
		0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
		0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
		0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
		0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
		0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
		0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
		0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
		0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
		0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
	};
	double result[256][256];
	int Sign[256][256];
	pu(S,result,Sign);
	//printf("%lf,%lf,%lf,%lf\n",result[0][0],result[0][1],result[1][0],result[1][1]);

	u8 c0[16]= {0x00,0xb0,0x00,0x00, 0x00,0x00,0x90,0x00, 0x00,0x00,0x00,0x12, 0xfb,0x00,0x00,0x00};
	u8 c1[16]= {0x00,0xf2,0x00,0x00, 0x00,0x00,0xc9,0x00, 0x00,0x00,0x00,0xb5, 0xc5,0x00,0x00,0x00};
	u8 w1[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x62,0x00,0x00,0x00};
	u8 w2[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x44,0x00,0x00,0x00};
	u8 w7[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x0d,0x99,0xbb,0x31};
	u8 w8[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x1d,0xfb,0x69,0x8f};
	u8 w13[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x79,0x4a,0x31};
	u8 w14[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x3e,0x89,0xf7};

	u8 Pmask1[256][16];         
	u8 Pmask2[256][256][256][16];
	u32 i,j,k,t,r1,r2,r3;
	for(i=0;i<256;i++)for(j=0;j<16;j++)Pmask1[i][j]=0;
	for(i=0;i<256;i++)for(j=0;j<256;j++)for(k=0;k<256;k++)for(t=0;t<16;t++)Pmask2[i][j][k][t]=0;

	InverseP1(Pmask1);
//	printf("w3: %02x, %02x, %02x, %02x\n",Pmask1[0x04][12],Pmask1[0x04][11],Pmask1[0x04][6],Pmask1[0x04][1]);

	InverseP3(Pmask2);
//	printf("w9: %02x, %02x, %02x, %02x\n",Pmask2[0x0e][0x0f][0x0e][12],Pmask2[0x0e][0x0f][0x0e][11],Pmask2[0x0e][0x0f][0x0e][6],Pmask2[0x0e][0x0f][0x0e][1]);

	double cor1,cor2,max,total1,total2,sy;
	int sign1,sign2;

	//zeta31,zeta51
	for(i=1;i<256;i++) //zeta31 
	{
		cor1=0;
		sign1=0;
		cor1+=result[i][w1[12]];         //zeta31-->alpha0+c1
		sign1^=Sign[i][w1[12]];
		cor1+=result[i][w7[12]];         //zeta31+zeta51-->beta0
		sign1^=Sign[i][w7[12]];
		if(cor1>5000)continue;
		cor1+=result[c0[1]][Pmask1[i][1]];           //c0-->zeta31
		sign1^=Sign[c0[1]][Pmask1[i][1]];
		cor1+=result[c0[6]][Pmask1[i][6]];
		sign1^=Sign[c0[6]][Pmask1[i][6]];
		cor1+=result[c0[11]][Pmask1[i][11]];
		sign1^=Sign[c0[11]][Pmask1[i][11]];
		cor1+=result[c0[12]][Pmask1[i][12]];
		sign1^=Sign[c0[12]][Pmask1[i][12]];
		if(cor1>5000)continue;
		for(j=1;j<256;j++)for(k=1;k<256;k++)for(t=1;t<256;t++) //zeta51 
		{
			cor2=cor1;
			sign2=sign1;
			cor2+=result[j][w7[15]];         //zeta31+zeta51-->beta0
			sign2^=Sign[j][w7[15]];
			cor2+=result[k][w7[14]];
			sign2^=Sign[k][w7[14]];
			cor2+=result[t][w7[13]];
			sign2^=Sign[t][w7[13]];
			if(cor2>5000)continue;
			cor2+=result[j][w13[15]];        //zeta51-->gamma0
			sign2^=Sign[j][w13[15]];
			cor2+=result[k][w13[14]];
			sign2^=Sign[k][w13[14]];
			cor2+=result[t][w13[13]];
			sign2^=Sign[t][w13[13]];
			if(cor2>5000)continue;
			cor2+=result[c0[1]][Pmask2[j][k][t][1]];            //c0-->zeta51
			sign2^=Sign[c0[1]][Pmask2[j][k][t][1]];
			cor2+=result[c0[6]][Pmask2[j][k][t][6]];
			sign2^=Sign[c0[6]][Pmask2[j][k][t][6]];
			cor2+=result[c0[11]][Pmask2[j][k][t][11]];
			sign2^=Sign[c0[11]][Pmask2[j][k][t][11]];
			cor2+=result[c0[12]][Pmask2[j][k][t][12]];
			sign2^=Sign[c0[12]][Pmask2[j][k][t][12]];
			total1+=pow(2,(80-cor2))*pow((-1),sign2);
		}
	}
	if(total1<0)sy=-1;
	else sy=1;
	printf("rho2 correlation %f, symble %d (0: +;1: -1)\n",(log2(fabs(total1))-80),sy);

	//zeta32,zeta52
	for(i=1;i<256;i++) //zeta32 
	{
		cor1=0;
		sign1=0;
		cor1+=result[i][w2[12]];         //zeta32-->alpha1+c0
		sign1^=Sign[i][w2[12]];
		cor1+=result[i][w8[12]];         //zeta32+zeta52-->beta1
		sign1^=Sign[i][w8[12]];
		if(cor1>5000)continue;
		cor1+=result[c1[1]][Pmask1[i][1]];           //c1-->zeta32
		sign1^=Sign[c1[1]][Pmask1[i][1]];
		cor1+=result[c1[6]][Pmask1[i][6]];
		sign1^=Sign[c1[6]][Pmask1[i][6]];
		cor1+=result[c1[11]][Pmask1[i][11]];
		sign1^=Sign[c1[11]][Pmask1[i][11]];
		cor1+=result[c1[12]][Pmask1[i][12]];
		sign1^=Sign[c1[12]][Pmask1[i][12]];
		if(cor1>5000)continue;
		for(j=1;j<256;j++)for(k=1;k<256;k++)for(t=1;t<256;t++) //zeta52 
		{
			cor2=cor1;
			sign2=sign1;
			cor2+=result[j][w8[15]];         //zeta32+zeta52-->beta1
			sign2^=Sign[j][w8[15]];
			cor2+=result[k][w8[14]];
			sign2^=Sign[k][w8[14]];
			cor2+=result[t][w8[13]];
			sign2^=Sign[t][w8[13]];
			if(cor2>5000)continue;
			cor2+=result[j][w14[15]];        //zeta52-->gamma1
			sign2^=Sign[j][w14[15]];
			cor2+=result[k][w14[14]];
			sign2^=Sign[k][w14[14]];
			cor2+=result[t][w14[13]];
			sign2^=Sign[t][w14[13]];
			if(cor2>5000)continue;
			cor2+=result[c1[1]][Pmask2[j][k][t][1]];            //c1-->zeta52
			sign2^=Sign[c1[1]][Pmask2[j][k][t][1]];
			cor2+=result[c1[6]][Pmask2[j][k][t][6]];
			sign2^=Sign[c1[6]][Pmask2[j][k][t][6]];
			cor2+=result[c1[11]][Pmask2[j][k][t][11]];
			sign2^=Sign[c1[11]][Pmask2[j][k][t][11]];
			cor2+=result[c1[12]][Pmask2[j][k][t][12]];
			sign2^=Sign[c1[12]][Pmask2[j][k][t][12]];
			total2+=pow(2,(80-cor2))*pow((-1),sign2);
		}
	}
	if(total2<0)sy=-1;
	else sy=1;
	printf("rho3 correlation %f, symble %d (0: +;1: -1)\n",(log2(fabs(total2))-80),sy);


	t2=time(NULL);
	printf("time %d s\n",(t2-t1));
}

int main()
{
	doing();
}
