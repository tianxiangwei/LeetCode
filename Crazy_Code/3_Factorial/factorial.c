/*
 * =====================================================================================
 *
 *       Filename:  factorial.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/26/2017 02:26:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int factorail(int n)
{
	if(n==1)
		return n;
	else
		return n*factorail(n-1);
}
int main()
{
	int n=5;
	printf("%d!=%d\n",n,factorail(n));
	return 0;
}
