/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/24/2016 02:21:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;


/*
 * There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays.
 The overall run time complexity should be O(log (m+n)).
 
 *  这道题让我们求两个有序数组的中位数，而且限制了时间复杂度为O(log (m+n))，看到这个时间复杂度，自然而然的想到了应该使用二分查找法来求解。但是这道题被定义为Hard也是有其原因的，难就难在要在两个未合并的有序数组之间使用二分法，这里我们需要定义一个函数来找到第K个元素，由于两个数组长度之和的奇偶不确定，因此需要分情况来讨论，对于奇数的情况，直接找到最中间的数即可，偶数的话需要求最中间两个数的平均值。下面重点来看如何实现找到第K个元素，首先我们需要让数组1的长度小于或等于数组2的长度，那么我们只需判断如果数组1的长度大于数组2的长度的话，交换两个数组即可，然后我们要判断小的数组是否为空，为空的话，直接在另一个数组找第K个即可。还有一种情况是当K = 1时，表示我们要找第一个元素，只要比较两个数组的第一个元素，返回较小的那个即可。
 * */

double get_median1(vector<int>&A,vector<int>&B)
{
	multiset<int> temp;
	int m,n,i;
	int size=0;
	int median1,median2;
	m=A.size();
	n=B.size();
	int mid=(m+n)/2+1;

	if(m==0&&n==0)
		return 0;


	for(i=0;i<m;i++)
		temp.insert(A[i]);
	for(i=0;i<n;i++)
		temp.insert(B[i]);
	
	size=temp.size();
	multiset<int>::iterator it=temp.begin();
	if(size==1)
		return *it;

	for(;it!=temp.end();it++)
		cout<<*it<<" ";
	cout<<endl;

	for(i=1,it=temp.begin();(i<=mid-1)&&it!=temp.end();it++,i++)
		cout<<*it<<" ";
	cout<<endl;
	median1=*it;

	if((m+n)%2!=0)
		return median1;
	else
	{
		it--;
		median2=*it;
		return (double)((median1+median2)/2.0);
	}
}

double get_median(vector<int> &A,vector<int>&B)
{
	int i=0,j=0;
	int m,n,mid;
	int size=0;
	vector<int> temp;
	m=A.size();
	n=B.size();
	mid=(m+n)/2+1;
	while(size<=mid)
	{
		if(i<m&&j<n)
		{
			if(A[i]<B[j])
			{
				temp.push_back(A[i]);
				i++;
			}
			else
			{
				temp.push_back(B[j]);
				j++;
			}
		}

		if(j==n&&i<m)
		{
			temp.push_back(A[i]);
			i++;
		}

		if(i==m&&j<n)
		{
			temp.push_back(B[j]);
			j++;
		}

		size=temp.size();
	}

	cout<<"mid:"<<mid<<endl;
	for(vector<int>::iterator iter=temp.begin();iter!=temp.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;

	if((m+n)%2!=0)
		return (double)temp[mid-1];
	else
		return (double)((double)temp[mid-1]+(double)temp[mid-2])/2;
}

double get_median2(vector<int>&A,vector<int>&B)
{
	int m,n;
	int i,j;
	m=A.size();
	n=B.size();
	if(m>n) return get_median2(B,A);
	int min=0,max=m;
	int mid=(m+n+1)/2;
	
	int median1,median2;

	while(min<=max)
	{
		i=(min+max)/2;
		j=mid-i;
		if(i>0&&j<n&&A[i-1]<B[j])
			max=i-1;
		else if(j>0&&i<m&&B[j-1]>A[i])
			min=i+1;
		else
			break;
	}
	
	if(i==0) median1=B[j-1];
	else if(j==0) median1=A[i-1];
	else
		median1=std::max(A[i-1],B[j-1]);
	if((m+n)&1)
		return median1;

	if(i==m) median2=B[j];
	else if(j==n) median2=A[i];
	else
		median2=std::min(A[i],B[j]);
	return (double)((median1+median2)/2.0);

}


class Solution{
	public:
		double findMedianSortedrrays(vector<int> &nums1,vector<int>&nums2)
		{
			int total=nums1.size()+nums2.size();
			if(total%2==1)
				return findKth(nums1,0,nums2,0,total/2+1);
			else
				return((findKth(nums1,0,nums2,0,total/2)+findKth(nums1,0,nums2,0,total/2+1))/2.0);
		}

		int findKth(vector<int>nums1,int i,vector<int>nums2,int j,int k)
		{
			if(nums1.size()-i>nums2.size()-j) return findKth(nums2,j,nums1,i,k);
			if(nums1.size()==i) return nums2[j+k-1];
			if(k==1) return min(nums1[i],nums2[j]);
			int pa=min(i+k/2,int(nums1.size())),pb=j+k-pa+i;
			cout<<"i:"<<i<<" j:"<<j<<" k"<<k<<" pa:"<<pa<<" pb:"<<pb<<endl;
			cout<<"nums1[pa-1]:"<<nums1[pa-1]<<" nums2[pb-1]:"<<nums2[pb-1]<<endl;
			if(nums1[pa-1]<nums2[pb-1])
				return findKth(nums1,pa,nums2,j,k-pa+i);
			else if(nums1[pa-1]>nums2[pb-1])
				return findKth(nums1,i,nums2,pb,k-pb+j);
			else
				return nums1[pa-1];
		}
};

class Solution1{
	public:
		double findMedianSortedrrays(vector<int> &nums1,vector<int>&nums2)
		{
			int m=nums1.size();
			int n=nums2.size();
			return (findKth(nums1,nums2,(m+n+1)/2)+findKth(nums1,nums2,(m+n+2)/2))/2.0;
		}

		int findKth(vector<int>nums1,vector<int>nums2,int k)
		{
			int m=nums1.size(),n=nums2.size();
			if(m>n)  return findKth(nums2,nums1,k);
			if(m==0) return nums2[k-1];
			if(k==1) return min(nums1[0],nums2[0]);
			int i=min(m,k/2),j=min(n,k/2);
			if(nums1[i]<nums2[j])
				return findKth(nums1,vector<int>(nums2.begin()+j,nums2.end()),k-j);
			else if(nums1[i]>nums2[j])
				return findKth(vector<int>(nums1.begin()+i,nums1.end()),nums2,k-i);
			else
				return 0;
		}
};



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	double value;
	vector<int> one_array;
	vector<int> two_array;
	cout<<"Input the first sorted array:"<<endl;
	do
	{
		cin>>value;
		if(value!=0)
			one_array.push_back(value);
	}while(value!=0);

	for(vector<int>::size_type ix=0;ix!=one_array.size();++ix)
		cout<<one_array[ix]<<" ";
	cout<<endl;

	cout<<"Input the second sorted array:"<<endl;
	do
	{
		cin>>value;
		if(value!=0)
			two_array.push_back(value);
	}while(value!=0);

	for(vector<int>::size_type ix=0;ix!=two_array.size();++ix)
		cout<<two_array[ix]<<" ";
	cout<<endl;
	
	Solution test;
	//value=get_median(one_array,two_array);
	//value=get_median1(one_array,two_array);
	//value=get_median2(one_array,two_array);
	value=test.findMedianSortedrrays(one_array,two_array);
	cout<<"the median value:"<<value<<endl;

	return 0;
}				/* ----------  end of function main  ---------- */
