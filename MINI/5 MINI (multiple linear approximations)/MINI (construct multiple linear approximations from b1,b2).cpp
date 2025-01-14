#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include <sys/stat.h>
#include<math.h>
#include<time.h>

# define Start 0x00

typedef unsigned __int64 u64;
typedef unsigned __int32 u32;
typedef unsigned __int8 u8;


void MatrixMul(u8 A[8][8], u8 B[8][8], u8 C[8][8])     //A*B
{
	int i, j, k;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			C[i][j] = 0;
			for (k = 0; k < 8; k++)
			{
				C[i][j] ^= A[i][k] & B[k][j];
			}
		}
	}
}

u8 RVectorMul(u8 A[8][8], u8 a) 
{
	int b[8];
	int c[8];
	int i, j, k;

	for (i = 0; i < 8; i++)
	{
		b[i] = (a >> i) & 1;
		c[i] = 0;
	}
	for (i = 0; i < 8; i++)for (j = 0; j < 8; j++)c[i] ^= A[i][j] & b[7 - j];

	k = 0;
	for (i = 0; i < 8; i++)	k ^= c[7 - i] << i;
	return k;
}

void MatrixR256(u8 A[256][8][8], u8 poly)      
{
	int i, j, k;
	int a, b;
	u8 B[8][8][8];
#define ercheng(x) ((x << 1) ^ (x >> 7 ? poly : 0))

	for (i = 0; i < 8; i++)for (j = 0; j < 8; j++)B[0][i][j] = 0;

	for (i = 0; i < 8; i++)B[0][i][i] = 1;

	for (i = 0; i < 8; i++)
	{
		a = 1 << i;
		b = ercheng(a);
		for (j = 0; j < 8; j++)B[1][7 - j][7 - i] = (b >> j) & 1;         
	}

	MatrixMul(B[1], B[1], B[2]);
	MatrixMul(B[1], B[2], B[3]);
	MatrixMul(B[1], B[3], B[4]);
	MatrixMul(B[1], B[4], B[5]);
	MatrixMul(B[1], B[5], B[6]);
	MatrixMul(B[1], B[6], B[7]);

	for (i = 0; i < 256; i++)for (j = 0; j < 8; j++)for (k = 0; k < 8; k++)	A[i][j][k] = 0;

	for (i = 0; i < 256; i++)for (j = 0; j < 8; j++)
	{
		if ((i >> j) & 1)
		{
			for (a = 0; a < 8; a++)for (b = 0; b < 8; b++) A[i][a][b] ^= B[j][a][b];
		}
	}
}

void GFMul(u8 A[256][256])
{
	int i, j, k;
	u8 GF[256][8][8];

	MatrixR256(GF, 0x1b);
	for (i = 0; i < 256; i++)for (j = 0; j < 256; j++)A[i][j] = RVectorMul(GF[i], j);

	for (i = 0; i < 256; i++)for (j = 0; j < 256; j++)
	{
		if (A[i][j] != A[j][i])printf("%x * %x fail\n", i, j);
	}
}

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

void aes_p_inverse(u32 state[4], u8 R[256][256])
{
	u32 temp[4]={0};
	u32 byt[4]={0};
	int i;
	for(i=0;i<4;i++)temp[i]=state[i];
	byt[0]=R[0xe][temp[0]&0xff]^R[0xb][(temp[0]>>8)&0xff]^R[0xd][(temp[0]>>16)&0xff]^R[0x9][(temp[0]>>24)&0xff];
	byt[1]=R[0x9][temp[3]&0xff]^R[0xe][(temp[3]>>8)&0xff]^R[0xb][(temp[3]>>16)&0xff]^R[0xd][(temp[3]>>24)&0xff];
	byt[2]=R[0xd][temp[2]&0xff]^R[0x9][(temp[2]>>8)&0xff]^R[0xe][(temp[2]>>16)&0xff]^R[0xb][(temp[2]>>24)&0xff];
	byt[3]=R[0xb][temp[1]&0xff]^R[0xd][(temp[1]>>8)&0xff]^R[0x9][(temp[1]>>16)&0xff]^R[0xe][(temp[1]>>24)&0xff];
	state[0]=(byt[3]<<24)^(byt[2]<<16)^(byt[1]<<8)^byt[0];
	byt[0]=R[0xe][temp[1]&0xff]^R[0xb][(temp[1]>>8)&0xff]^R[0xd][(temp[1]>>16)&0xff]^R[0x9][(temp[1]>>24)&0xff];
	byt[1]=R[0x9][temp[0]&0xff]^R[0xe][(temp[0]>>8)&0xff]^R[0xb][(temp[0]>>16)&0xff]^R[0xd][(temp[0]>>24)&0xff];
	byt[2]=R[0xd][temp[3]&0xff]^R[0x9][(temp[3]>>8)&0xff]^R[0xe][(temp[3]>>16)&0xff]^R[0xb][(temp[3]>>24)&0xff];
	byt[3]=R[0xb][temp[2]&0xff]^R[0xd][(temp[2]>>8)&0xff]^R[0x9][(temp[2]>>16)&0xff]^R[0xe][(temp[2]>>24)&0xff];
	state[1]=(byt[3]<<24)^(byt[2]<<16)^(byt[1]<<8)^byt[0];
	byt[0]=R[0xe][temp[2]&0xff]^R[0xb][(temp[2]>>8)&0xff]^R[0xd][(temp[2]>>16)&0xff]^R[0x9][(temp[2]>>24)&0xff];
	byt[1]=R[0x9][temp[1]&0xff]^R[0xe][(temp[1]>>8)&0xff]^R[0xb][(temp[1]>>16)&0xff]^R[0xd][(temp[1]>>24)&0xff];
	byt[2]=R[0xd][temp[0]&0xff]^R[0x9][(temp[0]>>8)&0xff]^R[0xe][(temp[0]>>16)&0xff]^R[0xb][(temp[0]>>24)&0xff];
	byt[3]=R[0xb][temp[3]&0xff]^R[0xd][(temp[3]>>8)&0xff]^R[0x9][(temp[3]>>16)&0xff]^R[0xe][(temp[3]>>24)&0xff];
	state[2]=(byt[3]<<24)^(byt[2]<<16)^(byt[1]<<8)^byt[0];
	byt[0]=R[0xe][temp[3]&0xff]^R[0xb][(temp[3]>>8)&0xff]^R[0xd][(temp[3]>>16)&0xff]^R[0x9][(temp[3]>>24)&0xff];
	byt[1]=R[0x9][temp[2]&0xff]^R[0xe][(temp[2]>>8)&0xff]^R[0xb][(temp[2]>>16)&0xff]^R[0xd][(temp[2]>>24)&0xff];
	byt[2]=R[0xd][temp[1]&0xff]^R[0x9][(temp[1]>>8)&0xff]^R[0xe][(temp[1]>>16)&0xff]^R[0xb][(temp[1]>>24)&0xff];
	byt[3]=R[0xb][temp[0]&0xff]^R[0xd][(temp[0]>>8)&0xff]^R[0x9][(temp[0]>>16)&0xff]^R[0xe][(temp[0]>>24)&0xff];
	state[3]=(byt[3]<<24)^(byt[2]<<16)^(byt[1]<<8)^byt[0];
}

void a1_b2(u8 Pmask[256][256][256][16])
{
	int i,j,k,r1,r2;
	u32 temp[4]={0};
	u32 parity;
	for(i=0;i<256;i++)for(j=0;j<256;j++)for(k=0;k<256;k++)for(r1=0;r1<128;r1++)
	{
		parity=0;
		for(r2=0;r2<4;r2++)temp[r2]=0;
		temp[r1/32]=1<<(r1%32);
		aes_p(temp);
		parity=((temp[0]>>8)&i)^((temp[2]>>24)&j)^(temp[3]&k);
		parity^=parity>>16;
		parity^=parity>>8;
		parity^=parity>>4;
		parity^=parity>>2;
		parity^=parity>>1;
		parity=parity&1;
		Pmask[k][j][i][r1/8]^=parity<<(r1%8);
	}
}

void b2_b1(u8 Pmask[256][256][256][16], u8 R[256][256])
{
	int i,j,k,r1,r2;
	u32 temp[4]={0};
	u32 parity;
	for(i=0;i<256;i++)for(j=0;j<256;j++)for(k=0;k<256;k++)for(r1=0;r1<128;r1++)
	{
		parity=0;
		for(r2=0;r2<4;r2++)temp[r2]=0;
		temp[r1/32]=1<<(r1%32);
		aes_p_inverse(temp,R);
		parity=((temp[0]>>8)&i)^((temp[2]>>24)&j)^(temp[3]&k);
		parity^=parity>>16;
		parity^=parity>>8;
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
		else result[a][b] = log((double)(256 / fabs(pu[a][b])))/log(2);
	}
}

void doing()
{
	char name[10];
	FILE *fp;
	strcpy(name,""); 
	sprintf(name,"0x%02x.txt",Start);
	fp = fopen(name,"wb"); 

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
	

	u8 alpha1[16]= {0x0a,0x41,0x78,0x00, 0x00,0xe9,0x58,0x49, 0x1c,0x00,0x37,0x89, 0xed,0x66,0x00,0x37};
	u8 w[16]= {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0xbd,0x3f,0xfa,0x0b};

	u8 Pmask1[256][256][256][16];         
	u8 Pmask2[256][256][256][16];
	int i,j,k,t,r1,r2,r3;
	for(i=0;i<256;i++)for(j=0;j<256;j++)for(k=0;k<256;k++)for(t=0;t<16;t++)
	{
		Pmask1[i][j][k][t]=0;
		Pmask2[i][j][k][t]=0;
	}
	a1_b2(Pmask1);
	printf("w4: %02x, %02x, %02x, %02x\n",Pmask1[0x11][0x82][0xed][15],Pmask1[0x11][0x82][0xed][14],Pmask1[0x11][0x82][0xed][13],Pmask1[0x11][0x82][0xed][12]);

	u8 R[256][256];
	GFMul(R);
	b2_b1(Pmask2,R);
	printf("w8: %02x, %02x, %02x, %02x\n",Pmask2[0x8a][0xfe][0x56][15],Pmask2[0x8a][0xfe][0x56][14],Pmask2[0x8a][0xfe][0x56][13],Pmask2[0x8a][0xfe][0x56][12]);
	t2=time(NULL);
	printf("precomputation uses %d s\n",(t2-t1));
	t1=time(NULL);

	double cor0;
	double cor1,cor2,max;
	int sign1,sign2;
	u64 distinguisher[200][2];  //107--126
	u32 count1,count2;
	u8 bmax[6];
	u32 b1max;
	max=120;
	cor0=196-57.4028;

	int j1;
	for(i=Start;i<Start+8;i++) for(j1=0;j1<256;j1++) 
	{
		j = 0x82^j1;
		for(k=1;k<256;k++) 
		{
			count1 = k^(j<<8)^(i<<16);
			cor1=0;
			sign1=0;
			cor1+=result[alpha1[0]][Pmask1[i][j][k][0]];
			sign1^=Sign[alpha1[0]][Pmask1[i][j][k][0]];
			cor1+=result[alpha1[1]][Pmask1[i][j][k][1]];
			sign1^=Sign[alpha1[1]][Pmask1[i][j][k][1]];
			cor1+=result[alpha1[2]][Pmask1[i][j][k][2]];;
			sign1^=Sign[alpha1[2]][Pmask1[i][j][k][2]];
			if(cor1>cor0)continue;
			cor1+=result[alpha1[5]][Pmask1[i][j][k][5]];
			sign1^=Sign[alpha1[5]][Pmask1[i][j][k][5]];
			cor1+=result[alpha1[6]][Pmask1[i][j][k][6]];
			sign1^=Sign[alpha1[6]][Pmask1[i][j][k][6]];
			cor1+=result[alpha1[7]][Pmask1[i][j][k][7]];
			sign1^=Sign[alpha1[7]][Pmask1[i][j][k][7]];
			if(cor1>cor0)continue;
			cor1+=result[alpha1[8]][Pmask1[i][j][k][8]];
			sign1^=Sign[alpha1[8]][Pmask1[i][j][k][8]];
			cor1+=result[alpha1[10]][Pmask1[i][j][k][10]];
			sign1^=Sign[alpha1[10]][Pmask1[i][j][k][10]];
			cor1+=result[alpha1[11]][Pmask1[i][j][k][11]];
			sign1^=Sign[alpha1[11]][Pmask1[i][j][k][11]];
			if(cor1>cor0)continue;
			cor1+=result[alpha1[12]][Pmask1[i][j][k][12]];
			sign1^=Sign[alpha1[12]][Pmask1[i][j][k][12]];
			cor1+=result[alpha1[13]][Pmask1[i][j][k][13]];
			sign1^=Sign[alpha1[13]][Pmask1[i][j][k][13]];
			cor1+=result[alpha1[15]][Pmask1[i][j][k][15]];
			sign1^=Sign[alpha1[15]][Pmask1[i][j][k][15]];
			if(cor1>cor0)continue;

			for(r1=1;r1<256;r1++)for(r2=1;r2<256;r2++)for(r3=1;r3<256;r3++)
			{
				cor2=cor1;
				sign2=sign1;
				cor2+=result[i][r1];
				sign2^=Sign[i][r1];
				if(cor2>cor0)continue;
				cor2+=result[j][r2];
				sign2^=Sign[j][r2];
				if(cor2>cor0)continue;
				cor2+=result[k][r3];
				sign2^=Sign[k][r3];
				if(cor2>cor0)continue;
				count2 = r3^(r2<<8)^(r1<<16);
				cor2+=result[Pmask2[r1][r2][r3][12]][w[12]];
				sign2^=Sign[Pmask2[r1][r2][r3][12]][w[12]];
				if(cor2>cor0)continue;
				cor2+=result[Pmask2[r1][r2][r3][13]][w[13]];
				sign2^=Sign[Pmask2[r1][r2][r3][13]][w[13]];
				if(cor2>cor0)continue;
				cor2+=result[Pmask2[r1][r2][r3][14]][w[14]];
				sign2^=Sign[Pmask2[r1][r2][r3][14]][w[14]];
				if(cor2>cor0)continue;
				cor2+=result[Pmask2[r1][r2][r3][15]][w[15]];
				sign2^=Sign[Pmask2[r1][r2][r3][15]][w[15]];
				if(cor2>cor0)continue;

				if(cor2<max)
				{
					max=cor2;
					bmax[0]=k;
					bmax[1]=j;
					bmax[2]=i;
					bmax[3]=r3;
					bmax[4]=r2;
					bmax[5]=r1;
					b1max=(u32)(Pmask2[r1][r2][r3][12])^((u32)(Pmask2[r1][r2][r3][13])<<8)^((u32)(Pmask2[r1][r2][r3][14])<<16)^((u32)(Pmask2[r1][r2][r3][15])<<24);
	
				}
				distinguisher[(int)(ceil(cor2+57.4028))][sign2]++;
			}
		} 
		if((j1&7)==7) 
		{
			t2=time(NULL);
			t = (t2-t1)*(32*(i-Start)+(j1>>3))/256;
			printf("i=%02x,j=%02x over, complete %d/256, use %d hour %d minute %d second\n",i,j1,32*(i-Start)+(j1>>3)+1,(t2-t1)/3600, ((t2-t1)%3600)/60,(t2-t1)%60,t/3600, (t%3600)/60);

		}
	} 

	t2=time(NULL);
	fprintf(fp,"Start=%02x--Start=%02x over,use %d hour %d minute %d second\n",Start,Start+8,(t2-t1)/3600, ((t2-t1)%3600)/60,(t2-t1)%60);	

	printf("Start=%02x--Start=%02x over,use %d hour %d minute %d second\n",Start,Start+8,(t2-t1)/3600, ((t2-t1)%3600)/60,(t2-t1)%60);	


	fprintf(fp,"    int result0[61] = { // The numbers of linear approximations with positive corelations between 2^-100 and 2^-160 \n");
	for(i=100;i<161;i++) fprintf(fp,"%I64d,",distinguisher[i][0]);
	fprintf(fp,"\n    };\n");

	fprintf(fp,"    int result1[61] = { // The numbers of linear approximations with negative corelations between 2^-100 and 2^-160 \n");
	for(i=100;i<161;i++) fprintf(fp,"%I64d,",distinguisher[i][1]);
	fprintf(fp,"\n    };\n");

	fprintf(fp,"The masks of the linear approximation with biggest correlation: 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%08x\n\n",bmax[0],bmax[1],bmax[2],bmax[3],bmax[4],bmax[5],b1max);
	for(i=100;i<161;i++) fprintf(fp,"Correlation-2^-%d: positive %I64d, negative %I64d\n",i,distinguisher[i][0],distinguisher[i][1]);
	

	fclose(fp);
}
int main()
{
	doing();
	return 0;

}
