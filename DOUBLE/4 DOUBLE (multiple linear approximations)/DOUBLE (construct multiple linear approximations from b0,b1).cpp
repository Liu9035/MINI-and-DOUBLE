#include<stdio.h> 
#include<math.h>
#include<time.h>
#include <sys/stat.h>
#include<stdlib.h>
#define u32 unsigned __int32
#define u16 unsigned __int16
#define u8 unsigned __int8

void AES_S_pu(double Walsh[256][256],int sign_S[256][256],int wt2[256]) 
{
	static int S[256]={	
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
	int a,b,x,z;
	int pu[256][256];

	for(a=0;a<256;a++) for(b=0;b<256;b++)
	{
		sign_S[a][b] = 0;
		pu[a][b] = 0;
		for(x=0;x<256;x++) 
		{
			z = wt2[(a&x) ^ (b&S[x])];
			if(z) pu[a][b] --;
			else  pu[a][b] ++;
		}
	}
	for(a=0;a<256;a++) for(b=0;b<256;b++) 
	{
		if(pu[a][b]>0)		 sign_S[a][b] = 1;
		else if(pu[a][b]<0) {sign_S[a][b] = -1; pu[a][b] = -pu[a][b];}

		if(pu[a][b]==0) Walsh[a][b] = 4321;
		else Walsh[a][b] = 8 - (log(pu[a][b])/log(2));  
	}
}

void shift(u32 a[4],u32 b[4])  
{
/*	int z[16] = { 0, 4,  8,12,                       0, 4, 8,12,
				  1, 5,  9,13,						 5, 9,13, 1,
				  2, 6, 10,14,						10,14, 2, 6,
				  3, 7, 11,15};                  	15, 3, 7,11 ,  
	*/
	int z[16] = {	0, 5,10,15,
					4, 9,14, 3,
					8,13, 2, 7,
					12,1,6,11};
	u32 A[16],B[16];
	int i,j;
	int D[16][16];

	for(i=0;i<16;i++) 	for(j=0;j<16;j++) D[i][j] = 0;
	for(i=0;i<16;i++) 	D[z[i]][i] = 1; 
	for(i=0;i<4;i++) 	for(j=0;j<4;j++)  A[4*i+j] = (a[i]>>(8*j))&255;	
	for(i=0;i<16;i++) 	
	{
		B[i] = 0;
		for(j=0;j<16;j++) if(D[i][j]) B[i] ^= A[j];
	}
	for(i=0;i<4;i++) 	
	{ 
		b[i] = 0; 
		for(j=0;j<4;j++)  b[i] ^= B[4*i+j]<<(8*j);
	}	
}
void liehunhe(u32 D[32])  
{
	static int mix[4][4] = {  2, 3, 1, 1,
							  1, 2, 3, 1,
							  1, 1, 2, 3,
							  3, 1, 1, 2}; 
	int M[4][256];		
	u32 e,y,z,A[4];
	int i,j,k;	
	
	for(y=0;y<256;y++) 
	{
		M[0][y] = 0;			M[1][y] = y;
		z =     ((y<<1)&255) ^ (y&128? 0x1b:0);		M[2][y] = z;	
		z ^= y;										M[3][y] = z;	
	}

	for(k=0;k<32;k++) 
	{
		e = 1<<k;
		for(i=0;i<4;i++) A[i] = (e>>(8*i))&255;
		y = 0;
		for(i=0;i<4;i++)
		{
			z = 0;
			for(j=0;j<4;j++) z ^= M[mix[i][j]][A[j]];
			y ^= z<<(8*i);
		}
		D[k] = y; 
	}
}

u32 liehunhe_mask(u32 b,u32 D[32],int wt2[256]) 
{		

	u32 y,z;
	int i,k;

	z = 0;
	for(i=0;i<32;i++)
	{
		y = D[i]&b;
		k = wt2[y&255] ^ wt2[(y>>8)&255] ^ wt2[(y>>16)&255] ^ wt2[(y>>24)&255];
		z ^= k<<i;
	}
	return z;
}
double pu_AES_round(u32 a[4], u32 b[4],double pu[256][256],int sign_S[256][256],int sign[2],u32 D[32],int wt2[256])
{				   
	u32 d[4],c[4]; 
	int i,j,A[16],B[16];
	double pior;

	for(i=0;i<4;i++) d[i] = liehunhe_mask(b[i],D,wt2); 

	shift(d,c);  

	for(i=0;i<4;i++) for(j=0;j<4;j++)
	{
		A[4*i+j] = (a[i]>>(8*j))&255;
		B[4*i+j] = (c[i]>>(8*j))&255;
	}
	pior = 0;		
	sign[0] = 1;
	for(i=0;i<16;i++) 
	{
		if(pu[A[i]][B[i]]==4321) 
		{ 
			sign[0] = 0; 
			return 4321; 
		}
		else 
		{ 
			pior += pu[A[i]][B[i]]; 
			sign[0] *= sign_S[A[i]][B[i]];
		}
	}
	return pior;
}

void doing()
{
	int wt2[256],i,j;
	for(i=0;i<256;i++) { wt2[i]=0; for(j=0;j<8;j++) wt2[i] ^= (i>>j)&1;} 
	double pu[256][256];
	int sign_S[256][256];
	AES_S_pu(pu, sign_S, wt2); 
	double pior,piorr,piorrr,Temp;
	int sign2[2],sign,signn,signnn,temp;
	u32  T[32];
	liehunhe(T); 
	double youshi;
	int count,num;
	FILE *fp;
	fp = fopen("0x00.txt", "a");//change the start point 
	u32 al0[4]={0xf200,0xc90000,0xb5000000,0x4e16ff00}; 
	u32 al1[4]={0xb000,0x900000,0x12000000,0xc9d2e00}; 
	u32 be0[4]={0x92b7bbaf,0xb1a4ec42,0x8ca6d96a,0x4ccf4ac4}; 
	u32 be1[4]={0x95bedd79,0x9063a43e,0x9a591c24,0x3e79b0ea}; 
	u32 ga0[4]={0x92b7bbaf,0x26fe0391,0x886a4dd6,0}; 
	u32 ga1[4]={0x384934b2,0x5cf7183a,0xd6067799,0};
	u32 b0[4]; 
	u32 b1[4];
	u32 bm0[4]; 
	u32 bm1[4]; 
	u32 x0[4]={0}; 
	u32 x1[4]={0}; 
	int n[2][20];
	double min=100000;
	int mins,k,ff;
	time_t t1,t2;
	for(i=0;i<256;i++) { wt2[i]=0; for(j=0;j<8;j++) wt2[i] ^= (i>>j)&1;} 
	AES_S_pu(pu, sign_S, wt2); 
	liehunhe(T); 
	t1=time(NULL);
	for(i=0;i<=0x1f;i++)//change the start point 
	{	
//	printf("i:%0x \n",i);
	for(ff=0;ff<=0xffff;ff++)
{   
  

	
	count=0;
    pior =92.65;
	sign = 1;  
	x0[3]=(i<<24)^(ff<<8);	
	

    Temp = pu_AES_round(x0, ga0 ,pu,sign_S,sign2,T,wt2);
	if(Temp==4321) continue; 
	pior += Temp;
	sign *= sign2[0];
	for(j=0;j<4;j++)
	b0[j]=x0[j]^be0[j];
    Temp = pu_AES_round(al0, b0 ,pu,sign_S,sign2,T,wt2);
	if(Temp==4321) continue; 
	pior += Temp;
	sign *= sign2[0];
	piorr=pior;
	signn=sign;

	for(k=1;k<=0xffffff;k++) 
	{	
	
	   pior=piorr;
       sign=signn;
	   x1[3]=k<<8;		
	 Temp = pu_AES_round(x1, ga1 ,pu,sign_S,sign2,T,wt2);
	 if(Temp==4321) continue; 
	pior += Temp;
	sign *= sign2[0];
	for(j=0;j<4;j++)
	b1[j]=x1[j]^be1[j];
    Temp = pu_AES_round(al1, b1 ,pu,sign_S,sign2,T,wt2);
	if(Temp==4321) continue; 
	pior += Temp;
	sign *= sign2[0];

	 if(pior<min)
         	{
         		min=pior;
         		mins=sign;
         	for(j=0;j<4;j++)
         	{
         		bm0[j]=b0[j];
         		bm1[j]=b1[j];
			 }
			}
			if(sign==1)
			{
			    if(pior>=166)
				n[0][19]++;
				else n[0][int(ceil(pior))-147]++;
			}
			if(sign==-1)
			{
				 if(pior>=166)
				n[1][19]++;
				else n[1][int(ceil(pior))-147]++;
			}
   }
   
}	
}
t2=time(NULL);
printf("time %d s\n",(t2-t1)); 
fprintf(fp,"time %d s\n",(t2-t1));
printf("b0 = ");		for(i=3;i>=0;i--) printf("%08x  ",bm0[i]);	printf("\n");
printf("b1 = ");		for(i=3;i>=0;i--) printf("%08x  ",bm1[i]);	printf("\n");	
printf("biggest correlation %3.8f, symble %d (1: +;-1: -)\n",min,mins);	

fprintf(fp,"b0 =");		for(i=3;i>=0;i--) fprintf(fp,"%08x  ",bm0[i]);	fprintf(fp,"\n");
fprintf(fp,"b1 = ");		for(i=3;i>=0;i--) fprintf(fp,"%08x  ",bm1[i]);	fprintf(fp,"\n");	
fprintf(fp,"biggest correlation %3.8f, symble %d (0: +;1: -)\n",min,mins);	
for(i=0;i<20;i++)
{
printf("%d,",n[0][i]);
fprintf(fp,"%d,",n[0][i]);
}
printf("\n");
fprintf(fp,"\n");
for(i=0;i<20;i++)
{
printf("%d,",n[1][i]);
fprintf(fp,"%d,",n[1][i]);
}
printf("\n");
fprintf(fp,"\n");
printf("positive\n");
fprintf(fp,"positive\n");
for(i=0;i<19;i++)
{
if(n[0][i]!=0)
{
printf("correlation %d; number %d\n",i+147,n[0][i]);			
fprintf(fp,"correlation %d; number %d\n",i+147,n[0][i]);	
}
}
if(n[0][19]!=0)
{
printf("correlation <= 2^(-166) number %d\n",n[0][19]);	
fprintf(fp,"correlation <= 2^(-166) number %d\n",n[0][19]);
}
printf("negative\n");	
fprintf(fp,"negative\n");	
for(i=0;i<19;i++)
{
if(n[1][i]!=0)
{
printf("correlation %d; number %d\n",i+147,n[1][i]);	
fprintf(fp,"correlation %d; number %d\n",i+147,n[1][i]);	
}
}
if(n[1][19]!=0)
{
printf("correlation <= 2^(-166) number %d\n",n[1][19]);
fprintf(fp,"correlation <= 2^(-166) number %d\n",n[1][19]);
}
}	




int main()
{
 
	doing();//¾ÛºÏ 
	return 0; 
}
