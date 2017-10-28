/*
 * =====================================================================================
 *
 *       Filename:  revert.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/22/2017 05:23:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/*
 逐bit逆序一个整数*/

#include <stdio.h>
#include <stdlib.h>

unsigned int revert_number(unsigned int num,int n)
{
	num=(num<<16)|(num>>16);
	printf("0x%x\n",num);
	
	num=((num<<8)&(0xFF00FF00))|((num>>8)&(0x00FF00FF));
	printf("0x%x\n",num);
	
	num=((num<<4)&(0xF0F0F0F0))|((num>>4)&(0x0F0F0F0F));
	printf("0x%08x\n",num);
	
	num=((num<<2)&(0xCCCCCCCC))|((num>>2)&(0x33333333));
	printf("0x%08x\n",num);
	
	num=((num<<1)&(0xAAAAAAAA))|((num>>1)&(0x55555555));
	printf("0x%08x\n",num);
	return num;

}

/*
 将一个整数逆序输出到数组
 例如 12345得到数组54321
*/
void convert(int *result,int n)
{
	if(n>=10)
	{
		convert(result+1,n/10);
	}
	*result=n%10;
}

void main()
{
	/*  unsigned int revert_num=0;
	unsigned int num=0x12345678;
	revert_num=revert_number(num,32);
	printf("0x%x Revert to 0x%x\n",num,revert_num);
	*/
	int i=0;
	int n=100;
	int result[10]={0};
	convert(result,n);
	for(i=0;i<10;i++)
		printf("result[%d]=%d\n",i,result[i]);

}

