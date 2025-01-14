#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<math.h>

typedef unsigned __int32 u32;
typedef unsigned __int8 u8;

void Readtxt(u32 alpha1[4],u32 alpha2[4],u32 alpha3[4],u32 alpha4[4], u32 gamma3[4], u32 gamma5[4], u32 gamma7[4], u32 gamma4[4], u32 gamma6[4], u32 beta1[4], u32 beta2[4], u32 beta3[4], u32 c1[4], u32 c2[4], u32 w1[4], u32 w2[4], u32 w3[4], u32 w4[4], u32 w5[4], u32 w6[4], u32 w7[4], u32 w8[4], u32 w9[4], u32 w10[4], u32 w11[4], u32 w12[4])
{
	FILE *filename = fopen("MINI(correlation).txt", "r+");

	struct stat file;
	stat("MINI(correlation).txt", &file);
	int lenth = file.st_size;
	char *fp = (char*)malloc(lenth);

	size_t sz = fread(fp, 1, (lenth), filename);

	int i, j, k;

	for (i = 0; i < 4; i++)
	{
		alpha1[i] = 0;
        alpha2[i] = 0;
		alpha3[i] = 0;
		alpha4[i] = 0;
		gamma3[i] = 0;
		gamma5[i] = 0;
		gamma7[i] = 0;
		gamma4[i] = 0;
		gamma6[i] = 0;
		beta1[i] = 0;
		beta2[i] = 0;
		beta3[i] = 0;
		c1[i] = 0;
		c2[i] = 0;
		w1[i] = 0;
		w2[i] = 0;
		w3[i] = 0;
		w4[i] = 0;
		w5[i] = 0;
		w6[i] = 0;
		w7[i] = 0;
		w8[i] = 0;
		w9[i] = 0;
		w10[i] = 0;
		w11[i] = 0;
		w12[i] = 0;
	}
	for (i = 0; i < (lenth + 1); i++)
	{
		switch (fp[i])
		{
		case'a':
			if ((fp[i + 1] == 'l') && (fp[i + 2] == 'p') && (fp[i + 3] == 'h') && (fp[i + 4] == 'a')&& (fp[i + 5] == '1') && (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				alpha1[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'l') && (fp[i + 2] == 'p') && (fp[i + 3] == 'h') && (fp[i + 4] == 'a')&& (fp[i + 5] == '2') && (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				alpha2[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'l') && (fp[i + 2] == 'p') && (fp[i + 3] == 'h') && (fp[i + 4] == 'a')&& (fp[i + 5] == '3') && (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				alpha3[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'l') && (fp[i + 2] == 'p') && (fp[i + 3] == 'h') && (fp[i + 4] == 'a')&& (fp[i + 5] == '4') && (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				alpha4[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			break;
		case'b':
			if ((fp[i + 1] == 'e') && (fp[i + 2] == 't') && (fp[i + 3] == 'a') && (fp[i + 4] == '1') && (fp[i + 5] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 6 + j] >= '0') && (fp[i + 6 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 6 + j] - '0');
					j++;
				}
				beta1[k / 32] ^= (fp[i + 9 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'e') && (fp[i + 2] == 't') && (fp[i + 3] == 'a') && (fp[i + 4] == '2')&& (fp[i + 5] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 6 + j] >= '0') && (fp[i + 6 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 6 + j] - '0');
					j++;
				}
				beta2[k / 32] ^= (fp[i + 9 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'e') && (fp[i + 2] == 't') && (fp[i + 3] == 'a') && (fp[i + 4] == '3') && (fp[i + 5] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 6 + j] >= '0') && (fp[i + 6 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 6+ j] - '0');
					j++;
				}
				beta3[k / 32] ^= (fp[i + 9 + j] - '0') << (k % 32);
			}
			break;
		case'c':
			if ((fp[i - 1] == '\'') && (fp[i + 1] == '1')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				c1[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '2')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				c2[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			break;
		case'g':
		     if ((fp[i + 1] == 'a') && (fp[i + 2] == 'm') && (fp[i + 3] == 'm') && (fp[i + 4] == 'a')  && (fp[i + 5] == '3')&& (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				gamma3[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'a') && (fp[i + 2] == 'm') && (fp[i + 3] == 'm') && (fp[i + 4] == 'a')  && (fp[i + 5] == '5')&& (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				gamma5[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'a') && (fp[i + 2] == 'm') && (fp[i + 3] == 'm') && (fp[i + 4] == 'a')  && (fp[i + 5] == '7')&& (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				gamma7[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'a') && (fp[i + 2] == 'm') && (fp[i + 3] == 'm') && (fp[i + 4] == 'a')  && (fp[i + 5] == '4')  && (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				gamma4[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			else if ((fp[i + 1] == 'a') && (fp[i + 2] == 'm') && (fp[i + 3] == 'm') && (fp[i + 4] == 'a')  && (fp[i + 5] == '6')  && (fp[i + 6] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 7 + j] >= '0') && (fp[i + 7 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 7 + j] - '0');
					j++;
				}
				gamma6[k / 32] ^= (fp[i + 10 + j] - '0') << (k % 32);
			}
			break;
		case'w':
			if ((fp[i - 1] == '\'') && (fp[i + 1] == '1')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w1[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '2')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w2[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '3')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w3[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '4')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w4[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '5')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w5[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '6')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w6[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '7')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w7[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '8')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w8[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '9')&& (fp[i + 2] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 3 + j] >= '0') && (fp[i + 3 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 3 + j] - '0');
					j++;
				}
				w9[k / 32] ^= (fp[i + 6 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '1')&& (fp[i + 2] == '0')&& (fp[i + 3] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 4 + j] >= '0') && (fp[i + 4 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 4 + j] - '0');
					j++;
				}
				w10[k / 32] ^= (fp[i + 7 + j] - '0') << (k % 32);
			}			
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '1')&& (fp[i + 2] == '1')&& (fp[i + 3] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 4 + j] >= '0') && (fp[i + 4 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 4 + j] - '0');
					j++;
				}
				w11[k / 32] ^= (fp[i + 7 + j] - '0') << (k % 32);
			}
			else if((fp[i - 1] == '\'') && (fp[i + 1] == '1')&& (fp[i + 2] == '2')&& (fp[i + 3] == '_'))
			{
				j = 0; k = 0;
				while ((fp[i + 4 + j] >= '0') && (fp[i + 4 + j] <= '9'))
				{
					k = k * 10 + (fp[i + 4 + j] - '0');
					j++;
				}
				w12[k / 32] ^= (fp[i + 7 + j] - '0') << (k % 32);
			}						
			break;
		default:break;
		}
	}
}

int wt(u32 in)
{
	u32 temp;
	int w = 0;

	temp = in;
	while (temp != 0)
	{
		temp &= temp - 1;
		w++;
	}
	return w;
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

int Parity(u32 state[4])
{
	int i;
	u32 temp = 0;
	for (i = 0; i < 4; i++)
	{
		temp ^= state[i];
	}
	temp = ((temp >> 16) ^ temp) & 0xffff;
	temp = ((temp >> 8) ^ temp) & 0xff;
	temp = ((temp >> 4) ^ temp) & 0xf;
	temp = ((temp >> 2) ^ temp) & 0x3;
	temp = ((temp >> 1) ^ temp) & 1;
	return temp;
}

double AES_P(u32 in[4], u32 out[4], char Ch[])
{
	int i, j;
	u32 e[4];
	u32 temp[4];

	for (i = 0; i < 128; i++)
	{
		e[i / 32] = 1 << (i % 32);
		e[((i / 32) + 1) & 3] = 0;
		e[((i / 32) + 2) & 3] = 0;
		e[((i / 32) + 3) & 3] = 0;
		aes_p(e);
		for (j = 0; j < 4; j++)
		{
			temp[j] = out[j] & e[j];
		}
		if (Parity(temp) ^ ((in[i / 32] >> (i % 32)) & 1))
		{
			printf("%s AES-P fail\n", Ch);
			return 9527;
		}
		else
		{
			continue;
		}
	}
	printf("%s AES-P pass\n", Ch);
	return 0;
}

void pu(u8 S[256], int pu[256][256])   
{
	int x, a, b, i, max;
	int wt[256];

	for (x = 0; x<256; x++) 
	{
		wt[x] = 0;
		for (i = 0; i<8; i++) wt[x] ^= (x >> i) & 1;
		if (wt[x])	wt[x] = -1;
		else wt[x] = 1;
	}

	for (a = 0; a<256; a++) 
	{
		for (b = 0; b<256; b++)	
		{
			pu[a][b] = 0;
			for (x = 0; x<256; x++)
				pu[a][b] += wt[(b&S[x]) ^ (a&x)];
		}
	}
	max = 0;
	for (a = 1; a<256; a++) 
	{
		for (b = 1; b<256; b++)	
		{
			if (pu[a][b]>max) max = pu[a][b];
			else if (-pu[a][b]>max) max = -pu[a][b];
		}
	}
}

double AES_S(u32 in[4], u32 out[4], int pu[256][256], char Ch[], int sym[2])
{
	int i;
	int temp[16];
	double cor = 0;
	for (i = 0; i < 16; i++)
	{
		temp[i] = pu[(in[i / 4] >> (8 * (i & 3))) & 0xff][(out[i / 4] >> (8 * (i & 3))) & 0xff];
		if (temp[i] < 0) sym[0] ^= 1;
		if (temp != 0)
		{
			cor += log2((double)(256 / fabs(temp[i])));

		}
		else
		{
			printf("%s position: %d AES-S fail\n", Ch, i);
			return 9527;
		}
	}
	printf("%s AES-S correlation: %f\n", Ch, cor);
	return cor;
}

void doing()
{
	u32 alpha1[4];
	u32 alpha2[4];
	u32 alpha3[4];
	u32 alpha4[4];
	u32 beta1[4];
	u32 beta2[4];
	u32 beta3[4];
	u32 c1[4];
	u32 c2[4];
	u32 gamma3[4];
	u32 gamma5[4];
	u32 gamma7[4];
	u32 gamma4[4];
	u32 gamma6[4];
	u32 v1[4];
	u32 v2[4];
	u32 v3[4];
	u32 v4[4];
	u32 v5[4];
	u32 v6[4];
	u32 v7[4];
	u32 w1[4];
	u32 w2[4];
	u32 w3[4];
	u32 w4[4];
	u32 w5[4];
	u32 w6[4];
	u32 w7[4];
	u32 w8[4];
	u32 w9[4];
	u32 w10[4];
	u32 w11[4];
	u32 w12[4];

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
	int result[256][256];
	double tc = 0;
	int sym[2] = { 0,0 };
	int i, j, k, b;
	int out[13][4]={0};
    int snum[13]={0}; 
    int sum =0;
	char Ach[] = "A";
	char Bch[] = "B";
	char Cch[] = "C";
	char Dch[] = "D";
	char Ech[] = "E";
	char Fch[] = "F";
	char Gch[] = "G";
	char Hch[] = "H";
	char Ich[] = "I";
	char Jch[] = "J";
	char Kch[] = "K";
	char Lch[] = "L";
	char w1ch[] = "w1";
	char w2ch[] = "w2";
	char w3ch[] = "w3";
	char w4ch[] = "w4";
	char w5ch[] = "w5";
	char w6ch[] = "w6";
	char w7ch[] = "w7";
	char w8ch[] = "w8";
	char w9ch[] = "w9";
	char w10ch[] = "w10";
	char w11ch[] = "w11";
	char w12ch[] = "w12";
	pu(S, result);
	Readtxt(alpha1, alpha2, alpha3, alpha4, gamma3, gamma5, gamma7, gamma4, gamma6, beta1, beta2, beta3, c1, c2, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12);
	for(i=0;i<4;i++)
	{
		v2[i]=beta3[i]^alpha4[i];
		v1[i]=alpha1[i]^v2[i];
		v3[i]=gamma4[i]^gamma6[i];
		v4[i]=gamma5[i]^gamma7[i];
		v5[i]=beta2[i]^alpha2[i];
        v6[i]=beta1[i]^alpha3[i];
        v7[i]=v4[i]^gamma3[i];
	}

	printf("alpha1: %8x %8x %8x %8x\n", alpha1[3], alpha1[2], alpha1[1], alpha1[0]);
	printf("alpha2: %8x %8x %8x %8x\n", alpha2[3], alpha2[2], alpha2[1], alpha2[0]);
	printf("alpha3: %8x %8x %8x %8x\n", alpha3[3], alpha3[2], alpha3[1], alpha3[0]);
	printf("alpha4: %8x %8x %8x %8x\n", alpha4[3], alpha4[2], alpha4[1], alpha4[0]);
	printf("c1: %8x %8x %8x %8x\n", c1[3], c1[2], c1[1], c1[0]);
	printf("c2: %8x %8x %8x %8x\n", c2[3], c2[2], c2[1], c2[0]);	
	printf("beta1: %8x %8x %8x %8x\n", beta1[3], beta1[2], beta1[1], beta1[0]);
	printf("beta2: %8x %8x %8x %8x\n", beta2[3], beta2[2], beta2[1], beta2[0]);
	printf("beta3: %8x %8x %8x %8x\n", beta3[3], beta3[2], beta3[1], beta3[0]);
	printf("gamma3: %8x %8x %8x %8x\n", gamma3[3], gamma3[2], gamma3[1], gamma3[0]);
	printf("gamma5: %8x %8x %8x %8x\n", gamma5[3], gamma5[2], gamma5[1], gamma5[0]);
	printf("gamma7: %8x %8x %8x %8x\n", gamma7[3], gamma7[2], gamma7[1], gamma7[0]);
	printf("gamma4: %8x %8x %8x %8x\n", gamma4[3], gamma4[2], gamma4[1], gamma4[0]);
	printf("gamma6: %8x %8x %8x %8x\n", gamma6[3], gamma6[2], gamma6[1], gamma6[0]);
	printf("v1: %8x %8x %8x %8x\n", v1[3], v1[2], v1[1], v1[0]);
	printf("v2: %8x %8x %8x %8x\n", v2[3], v2[2], v2[1], v2[0]);
	printf("v3: %8x %8x %8x %8x\n", v3[3], v3[2], v3[1], v3[0]);
	printf("v4: %8x %8x %8x %8x\n", v4[3], v4[2], v4[1], v4[0]);
	printf("v5: %8x %8x %8x %8x\n", v5[3], v5[2], v5[1], v5[0]);	
	printf("v6: %8x %8x %8x %8x\n", v6[3], v6[2], v6[1], v6[0]);
	printf("v7: %8x %8x %8x %8x\n", v7[3], v7[2], v7[1], v7[0]);
	printf("w1: %8x %8x %8x %8x\n", w1[3], w1[2], w1[1], w1[0]);
	printf("w2: %8x %8x %8x %8x\n", w2[3], w2[2], w2[1], w2[0]);
	printf("w3: %8x %8x %8x %8x\n", w3[3], w3[2], w3[1], w3[0]);
	printf("w4: %8x %8x %8x %8x\n", w4[3], w4[2], w4[1], w4[0]);
	printf("w5: %8x %8x %8x %8x\n", w5[3], w5[2], w5[1], w5[0]);
	printf("w6: %8x %8x %8x %8x\n", w6[3], w6[2], w6[1], w6[0]);
	printf("w7: %8x %8x %8x %8x\n", w7[3], w7[2], w7[1], w7[0]);
	printf("w8: %8x %8x %8x %8x\n", w8[3], w8[2], w8[1], w8[0]);
	printf("w9: %8x %8x %8x %8x\n", w9[3], w9[2], w9[1], w9[0]);
	printf("w10: %8x %8x %8x %8x\n", w10[3], w10[2], w10[1], w10[0]);
	printf("w11: %8x %8x %8x %8x\n", w11[3], w11[2], w11[1], w11[0]);
	printf("w12: %8x %8x %8x %8x\n", w12[3], w12[2], w12[1], w12[0]);
	 
	tc += AES_P(w1, v1, w1ch);
	tc += AES_P(w2, gamma4, w2ch);
	tc += AES_P(w3, gamma3, w3ch);
	tc += AES_P(w4, beta2, w4ch);
	tc += AES_P(w5, alpha2, w5ch);
	tc += AES_P(w6, gamma6, w6ch);
	tc += AES_P(w7, v4, w7ch);
	tc += AES_P(w8, beta1, w8ch);
	tc += AES_P(w9, alpha3, w9ch);
	tc += AES_P(w10, gamma7, w10ch);
	tc += AES_P(w11, alpha4, w11ch);
	tc += AES_P(w12, alpha4, w12ch);
	tc += AES_S(gamma3, w1, result, Ach, sym);
    tc += AES_S(v2, w2, result, Bch, sym);
    tc += AES_S(gamma4, w3, result, Cch, sym);
    tc += AES_S(alpha1, w4, result, Dch, sym);
    tc += AES_S(v7, w5, result, Ech, sym);
    tc += AES_S(v2, w6, result, Fch, sym);
    tc += AES_S(v3, w7, result, Gch, sym);
    tc += AES_S(v5, w8, result, Hch, sym);
    tc += AES_S(gamma5, w9, result, Ich, sym);
    tc += AES_S(gamma6, w10, result, Jch, sym);
    tc += AES_S(v6, w11, result, Kch, sym);
    tc += AES_S(gamma7, w12, result, Lch, sym);
    for(i=0;i<4;i++)
    {
    	out[0][i]=w1[i];
    	out[1][i]=w2[i];
    	out[2][i]=w3[i];
    	out[3][i]=w4[i];
    	out[4][i]=w5[i];
    	out[5][i]=w6[i];
		out[6][i]=w7[i];
		out[7][i]=w8[i];
		out[8][i]=w9[i];
		out[9][i]=w10[i];
		out[10][i]=w11[i];
		out[11][i]=w12[i];
    
	}
    for(i=0;i<12;i++)
    {
	
    for(j=0;j<4;j++)
	{
		 for(k=0;k<4;k++)
		 {
		 	b=(out[i][j]>>(k*8))&0xff;
		 	if(b!=0)
		 	snum[i]++;
		 }
	}
	sum=sum+snum[i];
	printf("%d layer have %d active sboxes\n", i+1, snum[i]);				
    }
    printf("sum: %d active sboxes\n", sum);	
	printf("correlation: %f, symble: %d (Remark symble: 0: +; 1: -1)\n", tc, sym[0]);

}

int main()
{
	doing();
}
