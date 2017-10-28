/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description: 测试 vector和map 
 *
 *        Version:  1.0
 *        Created:  06/14/2016 07:20:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/*
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Example:
 *
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;


class Solution{
	public:
		vector<int> twoSum(vector<int>&nums,int target)
		{
			unordered_map<int,int> map;
			for(int i=0;i<nums.size();i++)
			{
				if(map.count(target-nums[i]))
				{
					return {i,map[target-nums[i]]};
				}
				map[nums[i]]=i;
			}
			return {};
		}
};




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ()
{
	vector <int> ivec;
	vector <int> result;
	//for(vector<int>::size_type ix=0;ix!=10;++ix)
		//ivec.push_back(ix);
	ivec.push_back(2);
	ivec.push_back(7);
	ivec.push_back(11);
	ivec.push_back(15);

	for(vector<int>::size_type ix=0;ix!=ivec.size();++ix)
		cout<<"ix:"<<ix<<"ivect[ix]:"<<ivec[ix]<<endl;
	cout<<"ivec.size():"<<ivec.size()<<endl;
	cout<<"ivec.capacity()"<<ivec.capacity()<<endl;
	//vector<int>(ivec).swap(ivec);
	//{vector<int> tmp=ivec;ivec.swap(tmp);}
	//cout<<"vector<int>().size()"<<vector<int>(ivec).size()<<endl;
	//cout<<"vector<int>().capacity()"<<vector<int>(ivec).capacity()<<endl;
	//cout<<"ivec.size():"<<ivec.size()<<endl;
	//cout<<"ivec.capacity()"<<ivec.capacity()<<endl;
	Solution test;
	result=test.twoSum(ivec,9);
	for(vector<int>::size_type ix=0;ix!=result.size();++ix)
		cout<<"ix:"<<ix<<"result[ix]:"<<result[ix]<<endl;
	return 0;
}				/* ----------  end of function main  ---------- */
