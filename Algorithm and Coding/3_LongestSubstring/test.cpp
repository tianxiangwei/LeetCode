/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  最长无重复子串
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
/*  Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
解析:
    这道求最长无重复子串的题和[205]Isomorphic Strings 同构字符串很类似，我们还是建立一个256位大小的整型数组来代替哈希表，这样做的原因是ASCII表共能表示256个字符，所以可以记录所有字符，然后我们需要定义两个变量res和left，其中
res:用来记录最长无重复子串的长度，
left:指向该无重复子串左边的起始位置.
然后我们遍历整个字符串，对于每一个遍历到的字符，如果哈希表中该字符串对应的值为0，说明没有遇到过该字符，则此时计算最长无重复子串，i - left +１，其中ｉ是最长无重复子串最右边的位置，left是最左边的位置，还有一种情况也需要计算最长无重复子串，就是当哈希表中的值小于left，这是由于此时出现过重复的字符，left的位置更新了，如果又遇到了新的字符，就要重新计算最长无重复子串。最后每次都要在哈希表中将当前字符对应的值赋值为i+1
*/


#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

class Soluation {
public:
	int getlongestsubstring(string s,int *begin_index)
	{
		int m[256]={0},res=0,left=0;
		for(int i=0;i<s.size();i++)
		{
			cout<<i<<"-->s[i]:"<<s[i]<<" m[s[i]]:"<<m[s[i]]<<" left:"<<left<<endl;
			if(m[s[i]]==0 || m[s[i]]<left)
			{
				res=max(res,i-left+1);
			}
			else
			{
				left=m[s[i]];
			}
			m[s[i]]=i+1;
			cout<<"m[s[i]]:"<<m[s[i]]<<" res:"<<res<<" left:"<<left<<endl;
			cout<<"**************"<<endl;
		}
		*begin_index=left;
		return res;
	}
	
	int getlongestsubstring1(string s,int *begin_index)
	{
		vector<int> m(256,-1);
		int res=0,left=-1;
		for(int i=0;i<s.size();++i)
		{
			left=max(left,m[s[i]]);
			m[s[i]]=i;
			res=max(res,i-left);
		}
		*begin_index=left;
		return res;
	}

	int getlongestsubstring2(string s,int *begin_index)
	{
		set<char>t;
		int res=0,left=0,right=0;
		while(right<s.size())
		{
			if(t.find(s[right])==t.end())
			{
				t.insert(s[right++]);
				res=max(res,(int)t.size());
			}
			else
			{
				t.erase(s[left++]);
			}
		}
		*begin_index=left;
		return res;
	}
};

int main()
{
	int begin_index,max_len;
	string s1("abbca");
	Soluation test;
	cout<<"the initail string:"<<s1<<endl;
	//max_len=test.getlongestsubstring(s1,&begin_index);
	max_len=test.getlongestsubstring1(s1,&begin_index);
	max_len=test.getlongestsubstring2(s1,&begin_index);
	cout<<"begin_index:"<<begin_index<<" max_len:"<<max_len<<endl;
	string substr(s1,begin_index,max_len);
	cout<<"the longest substring:"<<substr<<endl;

}
