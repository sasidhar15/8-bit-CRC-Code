#include<stdio.h>
#include<string.h>

#define SIZE_INPUT 10
#define SIZE_TEMP_DATA SIZE_INPUT+1
main()
{
	unsigned char inputdata[SIZE_INPUT],tempdata[SIZE_TEMP_DATA+1],quodata=0x00,dividekey = 0xAA,tempkey = 0x00, tempquodata = 0x00;
	int i,j,k,count = 7,tempcount=0;
	unsigned char interdata=0x0;
	unsigned int inputsize_in_bits,loopcount,keysize_in_bits;
	inputsize_in_bits = sizeof(inputdata) * 8;
	keysize_in_bits = sizeof(dividekey) * 8;
	loopcount = inputsize_in_bits ;
	
	memset(inputdata,0,sizeof(inputdata));
	memset(tempdata,0,sizeof(tempdata));
	
	printf("Enter Inputdata : ");
	scanf("%[^\n]s",inputdata);
	strcpy(tempdata,inputdata);
	tempdata[sizeof(inputdata)] = quodata;
//	printf("inputdata = %s\ntempdata = %s\n",inputdata,tempdata);
//	printf("tempdata = %x\n",tempdata[sizeof(inputdata)]);
	quodata = tempdata[0];
	tempkey = dividekey;
	
	for(i=0;i<loopcount;i++)
	{
		tempquodata = 0;
		if(count == -1)
		count = 7;

		if(((quodata >> 7) ^ (tempkey >> 7)) & 1)
		{
			for(j=7;j>=0;j--)
			{
				tempquodata |= ((quodata >> j) ^ (tempkey >> j)) << j;						
			}
			tempkey = dividekey;
			quodata = tempquodata;
			i--;
		}
		else
		{
			for(j=6;j>=0;j--)
			{
				tempquodata |= ((quodata >> j) ^ (tempkey >> j)) << j+1;							
			}
			if(i%8 == 0)
			{
				tempcount++;
				interdata = tempdata[tempcount];	
			}
			tempquodata |= ((interdata >> count)&1) ;
			count --;
			if(!((tempquodata >> 7) & 1))
			{
				tempkey = 0x00;
			}
			else
			{
				tempkey = dividekey;					
			}		
			quodata = tempquodata;
		}
		
	}
	printf("Checksum = %x\n",quodata);
		for(k=7;k>=0;k--)
		printf("%d ",(quodata >> k)&1);
		printf("\n");

}
