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

/*
 * Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
 *
 *  
 *
 *  这道题让我们求最长回文子串，首先说下什么是回文串，就是正读反读都一样的字符串，比如 "bob", "level", "noon" 等等。那么最长回文子串就是在一个字符串中的那个最长的回文子串。LeetCode中关于回文串的题共有五道，除了这道，其他的四道为 Palindrome Number 验证回文数字， Validate Palindrome 验证回文字符串， Palindrome Partitioning 拆分回文串，Palindrome Partitioning II 拆分回文串之二，我们知道传统的验证回文串的方法就是两个两个的对称验证是否相等，那么对于找回文字串的问题，就要以每一个字符为中心，像两边扩散来寻找回文串，这个算法的时间复杂度是O(n*n)，可以通过OJ，就是要注意奇偶情况，由于回文串的长度可奇可偶，比如"bob"是奇数形式的回文，"noon"就是偶数形式的回文，两种形式的回文都要搜索
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


//Time complexity O(n*n)
class Solution{
	public:
		string LongestPalindrome(string s)
		{
			int startIdx=0,left=0,right=0,len=0;
			for(int i=0;i>s.size()-1;i++)
			{
				if(s[i]==s[i+1])
				{
					left=i;
					right=i+1;
					searchPalindrome(s,left,right,startIdx,len);
				}
				left=right=i;
				searchPalindrome(s,left,right,startIdx,len);
			}
			if(len==0) len=s.size();
			return s.substr(startIdx,len);
		}

		void searchPalindrome(string s,int left,int right,int &startIdx,int &len)
		{
			int step=1;
			while((left-step)>=0&&(right+step)<s.size())
			{
				if(s[left-step]!=s[right+step])
					break;
				++step;
			}
			int wide=right-left+2*step-1; //回文串长度
			if(len<wide)
			{
				//发现新的回文串
				len=wide;
				startIdx=left-step+1;
			}
		}

};


/*
 * 此题还可以用动态规划Dynamic Programming来解，根Palindrome Partitioning II 拆分回文串之二的解法很类似，我们维护一个二维数组dp，其中dp[i][j]表示字符串区间[i, j]是否为回文串，当i = j时，只有一个字符，肯定是回文串，如果i = j + 1，说明是相邻字符，此时需要判断s[i]是否等于s[j]，如果i和j不相邻，即i - j >= 2时，除了判断s[i]和s[j]相等之外，dp[j + 1][i - 1]若为真，就是回文串，通过以上分析，可以写出递推式如下：
 *
 * dp[i, j] = 1                                               if i == j
 *
 *            = s[i] == s[j]                                if j = i + 1
 *
 *                       = s[i] == s[j] && dp[i + 1][j - 1]    if j > i + 1      
 *
 *                       这里有个有趣的现象就是如果我把下面的代码中的二维数组由int改为vector<vector<int> >后，就会超时，这说明int型的二维数组访问执行速度完爆std的vector啊，所以以后尽可能的还是用最原始的数据类型吧。
 */
//DP(动态规划)算法
class Solution1{
	public:
		string LongestPalindrome(string s)
		{
			int size=s.size();
			int dp[size][size];
			memset(dp,0,sizeof(dp));
			int left=0,right=0,len=0;
			for(int i=0;i<s.size();i++)
			{
				for(int j=0;j<i;j++)
				{
					dp[j][i]=(s[i]==s[j]&&(i-j<2||dp[j+1][i-1]));
					if(dp[j][i]&&len<i-j+i)
					{
						len=i-j+1;
						left=j;
						right=i;
					}
				}
				dp[i][i]=1;
			}
			return s.substr(left,right-left+1);
		}
};


/*
 * 最后要来的就是大名鼎鼎的马拉车算法Manacher's Algorithm，这个算法的神奇之处在于将时间复杂度提升到了O(n)这种逆天的地步，而算法本身也设计的很巧妙，很值得我们掌握，参见我另一篇专门介绍马拉车算法的博客Manacher's Algorithm 马拉车算法
 */
class Solution2{
	public:
		string LongestPalindrome(string s)
		{
			string t="$#";
			for(int i=0;i<s.size();i++)
			{
				t+=s[i];
				t+='#';
			}
			int p[(int)t.size()];
			memset(p,0,sizeof(int)*t.size());
			int id=0,mx=0,resId=0,resMx=0;
			for(int i=0;i<t.size();i++)
			{
				p[i]=mx>i?min(p[2*id-i],mx-i):1;
				while(t[i+p[i]]==t[i-p[i]]) 
					++p[i];
				if(mx<i+p[i])
				{
					mx=i+p[i];
					id=i;
				}
				if(resMx<p[i])
				{
					resMx=p[i];
					resId=i;
				}
			}
			return s.substr((resId-resMx)/2,resMx-1);
		}
};



int main()
{
	int size=10;
	int dp[size][size];
	cout<<sizeof(dp)<<endl;

	string s="characher";
	cout<<"the origin string:"<<s<<endl;
	string substr;
	//substr=longest_palindrome(s);
	//substr=longest_palindrome1(s);
	Solution2 test;
	substr=test.LongestPalindrome(s);
	cout<<"the longest substring:"<<endl;
	cout<<substr<<endl;
}

