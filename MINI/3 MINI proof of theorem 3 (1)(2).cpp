#include<stdio.h> 
#include<math.h>
#include<time.h>
#define u32 unsigned __int32
#define u16 unsigned __int16
#define u8 unsigned __int8
void doing() 
{
    u32 db1[4]={0};//difference of b1 
    u32 db2[4]={0};//difference of b2
    u32 db3[4]={0};//difference of b3
    u32 Mdb1[4]={0};//W^-1 M^-1(db1)
    u32 sigdb2[4]={0};//sigma(db2)
    u32 Mdb3[4]={0};//M^-1(db3)
    int k1,k2,i,flag;
    int f[4]={0};
    int ff[4]={0};
    int j,fflag=0;
    flag=0;
    printf("(1)***************************proof k1 k2 two parameters and fixed masks alpha1,alpha4\n");
	for(k1=0;k1<4;k1++)	
	for(k2=0;k2<4;k2++)	
	{
	fflag=0;
	printf("\n");
	printf("k1 %d ,k2 %d  \n",k1,k2);
		for(i=0;i<4;i++)
	{
	db3[i]=0;
	Mdb3[i]=0;
	}
	//calculate M^-1(db3)
	Mdb3[k2]=0x000000ff;
	Mdb3[(k2+1)%4]=0xff000000;
	Mdb3[(k2+2)%4]=0x00ff0000;
	Mdb3[(k2+3)%4]=0x0000ff00;
	printf("Mdb3 = ");		
	for(i=3;i>=0;i--) 
	printf("%08x  ",Mdb3[i]);	
	printf("\n");
	//describe db3 by k3
	db3[k1]=0x000000ff;
	db3[(k1+1)%4]=0x0000ff00;
	db3[(k1+2)%4]=0x00ff0000;
	db3[(k1+3)%4]=0xff000000;
	printf("db3 = ");		
	for(i=3;i>=0;i--) 
	printf("%08x  ",db3[i]);	
	printf("\n");
	//count the non-zero bytes of the every same column in db3 and M^-1(db3)
	for(i=0;i<4;i++)
	{
	flag = 0;
	if((db3[i]&0xff)==0)
	f[0]=0;
	else f[0]=1;
	if((db3[i]&0xff00)==0)
	f[1]=0;
	else f[1]=1;
	if((db3[i]&0xff0000)==0)
	f[2]=0;
	else f[2]=1;
	if((db3[i]&0xff000000)==0)
	f[3]=0;
	else f[3]=1;
	printf("db3 %d column\n",i);
    for(j=3;j>=0;j--) 
    {
	printf("%d  ",f[j]);
	flag=flag+f[j];
	}
	printf("\n");	
	
	if((Mdb3[i]&0xff)==0)
	ff[0]=0;
	else ff[0]=1;
	if((Mdb3[i]&0xff00)==0)
	ff[1]=0;
	else ff[1]=1;
	if((Mdb3[i]&0xff0000)==0)
	ff[2]=0;
	else ff[2]=1;
	if((Mdb3[i]&0xff000000)==0)
	ff[3]=0;
	else ff[3]=1;
	printf("M^-1(db3) %d column\n",i);
	for(j=3;j>=0;j--) 
	{
	printf("%d  ",ff[j]);	
	flag=flag+ff[j];
	}
	printf("\n");
	printf("the sum of db3 and M^-1(db3) %d column non-zero bytes: %d  ",i,flag);	
	printf("\n");
	// if  all the numbers of  columns <5, only
	if(flag>4)
	{	
	printf("b3 not only*******************************************************************************************\n");
	fflag=1;
	} 
    }
    if(fflag==0) printf("b3 only\n");
    }
    printf("(2)***************************proof k1 k2 two parameters and fixed masks c1,c2,alpha1,alpha4\n");
	for(k1=0;k1<4;k1++)	
	for(k2=0;k2<4;k2++)	
	{
	printf("\n");
	//set 0
	for(i=0;i<4;i++)
	{
	db1[i]=0;
	db2[i]=0;
	Mdb3[i]=0;
	}
	
	printf("k1 %d ,k2 %d  \n",k1,k2);
	//describe db1 by p(b1-alpha4)!=0
	db1[k2]=0xffffffff;
	//calculate W^-1 M^-1(db1) and db2=W^-1 M^-1(db1)
	Mdb1[k2]=0Xff;
	Mdb1[(k2+1)%4]=0Xff00;
	Mdb1[(k2+2)%4]=0Xff0000;
	Mdb1[(k2+3)%4]=0Xff000000;
	for(i=0;i<4;i++)
	db2[i]=Mdb1[i];
	//describe db2 by p(alpha1-b2)!= 0
	db2[k1]=0;
	//calculate M^-1(db3)
	Mdb3[k2]=0x000000ff;
	Mdb3[(k2+1)%4]=0xff000000;
	Mdb3[(k2+2)%4]=0x00ff0000;
	Mdb3[(k2+3)%4]=0x0000ff00;
	printf("Mdb3 = ");		
	for(i=3;i>=0;i--) 
	printf("%08x  ",Mdb3[i]);	
	printf("\n");
		

	//describe sigma(db2)
	sigdb2[0]=(db2[1]<<16)^(db2[0]>>16);
	sigdb2[1]=(db2[2]<<16)^(db2[3]>>16);
	sigdb2[2]=(db2[1]&0xffff0000)^(db2[3]&0x0000ffff);
	sigdb2[3]=(db2[2]&0xffff0000)^(db2[0]&0x0000ffff);
	//A-1(db1)=db1 and db3 = sigma(db2)&A-1(db1)
	for(i=0;i<4;i++)
	db3[i]=sigdb2[i]&db1[i];	
    printf(" db3 = ");		
	for(i=3;i>=0;i--) 
	printf("%08x  ",db3[i]);	
	printf("\n");
    //count the non-zero bytes of the same column (k2) in db3 and M^-1(db3) 
    // if the number <5, only
	if((db3[k2]&0xff)==0)
	f[0]=0;
	else f[0]=1;
	if((db3[k2]&0xff00)==0)
	f[1]=0;
	else f[1]=1;
	if((db3[k2]&0xff0000)==0)
	f[2]=0;
	else f[2]=1;
	if((db3[k2]&0xff000000)==0)
	f[3]=0;
	else f[3]=1;
	printf("db3 %d column\n",k2);
	for(i=3;i>=0;i--) 
	printf("%d  ",f[i]);	
	printf("\n");
	if((Mdb3[k2]&0xff)==0)
	ff[0]=0;
	else ff[0]=1;
	if((Mdb3[k2]&0xff00)==0)
	ff[1]=0;
	else ff[1]=1;
	if((Mdb3[k2]&0xff0000)==0)
	ff[2]=0;
	else ff[2]=1;
	if((Mdb3[k2]&0xff000000)==0)
	ff[3]=0;
	else ff[3]=1;
	printf("M^-1(db3) %d column\n",k2);
	for(i=3;i>=0;i--) 
	printf("%d  ",ff[i]);	
	printf("\n");	
	flag=0;
	for(i=0;i<4;i++)
	{   
	flag=flag+f[i]+ff[i];
	}
	printf("the sum of db3 and M^-1(db3) %d column non-zero bytes: %d  ",k2,flag);	
	printf("\n");	
    if(flag<5)
    printf("b3 only\n");
    else printf("b3 not only*******************************************************************************************\n");
	}	

}

			
    



int main()
{
	doing(); 
	return 0; 
}
