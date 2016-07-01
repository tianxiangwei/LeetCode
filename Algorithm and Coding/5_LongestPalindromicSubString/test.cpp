/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/2016 05:00:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <memory.h>
#include <iostream>
#include <string>
using namespace std;


//动态规划算法 时间复杂度O(n^2) 空间复杂度O(n^2)
//dp[i][j]表示字符串从i到j是否是回文
string longest_palindrome(string s)
{
	const int len=s.size();
	if (len<=1) return s;
	bool dp[len][len];
	int Left=0,Right=0;
	memset(dp,0,sizeof(dp));
	dp[0][0]=true;
	for(int i=1;i<len;i++)
	{
		dp[i][i]=true;
		dp[i][i-1]=true;
	}

	for(int k=2;k<=len;k++)
	{
		for(int i=0;i<=len-k;i++)
		{
			if(s[i]==s[i+k-1]&&dp[i+1][i+k-2])
			{
				dp[i][i+k-1]=true;
				if(Right-Left+1<k)
				{
					Left=i;
					Right=i+k-1;
				}
			}
		}
	}
	return s.substr(Left,Right-Left+1);
}

//以某个元素为中心，分别计算偶数长度的回文最大长度和奇数个数的回文最大长度
//时间复杂度为O(n^2),空间复杂度为O(1)
//
string longest_palindrome1(string s)
{
	const int len=s.size();
	if(len<=1) return s;
	int start,maxlen=0;
	int low,high;
	
	for(int i=1;i<len;i++)
	{
		//奇数长度遍历
		low=i-1;
		high=i;
		while(low>=0&&high<len&&s[low]==s[high])
		{
			low--;
			high++;
		}

		if(high-low-1>maxlen)
		{
			maxlen=high-low-1;
			start=low+1;
		}

		//偶数长度遍历
		low=i-1;
		high=i+1;
		while(low>=0&&high<len&&s[low]==s[high])
		{
			low--;
			high++;
		}

		if(high-low-1>maxlen)
		{
			maxlen=high-low-1;
			start=low+1;
		}

	}
	return s.substr(start,maxlen);
}

//Manachar算法 时间复杂度O(n) 空间复杂度O(n)

int main()
{
	string s="1221324";
	cout<<"the origin string:"<<s<<endl;
	string substr;
	//substr=longest_palindrome(s);
	substr=longest_palindrome1(s);
	cout<<"the longest substring:"<<endl;
	cout<<substr<<endl;
}
