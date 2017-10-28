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
	
	//value=get_median(one_array,two_array);
	value=get_median1(one_array,two_array);
	//value=get_median2(one_array,two_array);
	cout<<"the median value:"<<value<<endl;

	return 0;
}				/* ----------  end of function main  ---------- */
