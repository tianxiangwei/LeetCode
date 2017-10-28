/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/26/2017 03:28:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/*
 memcpy与memmove的目的都是将N个字节的源地址内容copy到目的地址
 但是当源地址和目的地址内存区域有重叠时,memcpy会出错,而memmove能正确的执行内核拷贝
 memmove的处理措施：
 1.当源地址首地址大于目标地址首地址时，实行正向copy
 2.当源地址的首地址小于目标地址首地址时，实行反向copy
 3.当源地址的首地址和目标地址首地址相等时，不进行任何操作
 */

#include <stdio.h>
#include <stdlib.h>

void* memcpy(void *dest,const void *src,size_t n)
{
	char *d=(char *)dest;
	const char *s=(const char*)src;
	while(n--)
		*d++=*s++;
	return dest;
}

void* memmove(void *dest,const void *src,size_t n)
{
	char *tmp;
	const char *s;
	if(src>dest)
	{
		tmp=(char *)dest;
		s=(char *)src;
		while(n--)
			*tmp++=*s++;

	}
	else if(src<dest)
	{
		tmp=(char *)dest+n-1;
		s=(char *)src+n-1;
		while(n--)
			*tmp--=*s--;
	}
	return dest;
}


int main()
{
	return 0;
}
