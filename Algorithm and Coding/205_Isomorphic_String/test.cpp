/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  同构字符串
 *
 *        Version:  1.0
 *        Created:  10/28/2017 03:28:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
/* 
 *Given two strings s and t, determine if they are isomorphic.
 Two strings are isomorphic if the characters in s can be replaced to get t.
 All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

 For example,
 Given "egg", "add", return true.

 Given "foo", "bar", return false.

 Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

这道题让我们求同构字符串，就是说原字符串中的每个字符可由另外一个字符替代，可以被其本身替代，相同的字符一定要被同一个字符替代，且一个字符不能被多个字符替代，即不能出现一对多的映射。根据一对一映射的特点，我们需要用两个哈希表分别来记录原字符串和目标字符串中字符出现情况，由于ASCII码只有256个字符，所以我们可以用一个256大小的数组来代替哈希表，并初始化为0，我们遍历原字符串，分别从源字符串和目标字符串取出一个字符然后分别在两个哈希表中查找其值，若不相等，则返回false，若想等，将其值更新为i + 1
*/

#include <iostream>
#include <string>
using namespace std;

class Soluation {
public:
	bool isIsomorphic(string s,string b)
	{
		int m[256]={0},n[256]={0};
		int len=b.size();
		for(int i=0;i<len;i++)
		{
			if(m[s[i]]!=n[b[i]])
				return false;
			m[s[i]]=i+1;
			n[b[i]]=i+1;
		}
		return true;
	}
};

int main()
{
	string s1("paper");
	string s2("title");
	Soluation test;
	cout<<test.isIsomorphic(s1,s2)<<endl;
}
