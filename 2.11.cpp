

//2.11 extends problem 1
#include<iostream>
#include<algorithm>
#include<limits>
#include<vector>
using namespace std;

//simple solution
int maxDiff(int A[],int n){

	sort(A,A+n);
	int max = A[2]-A[1];
	for(int i=3;i<n;i++){
		int d = A[i]-A[i-1];
		if(d>max){
			max = d;
		}
	}
	return max;
}

int maxDiff1(int A[],int n){
	int min=A[0],max=A[0];
	for(int i=1;i<n;i++){
		if(A[i]<min) min = A[i];
		if(A[i]>max) max = A[i];
	}
	int delta = (max-min)/(n-1);
	if(delta==0) return maxDiff(A,n);  //一种特殊情况
	//把区间分成N个桶
	vector<vector<int> > bucket(n);
	
	//相邻两个数的最大差值一定不小于delta
	for(int i=0;i<n;i++){
		int index = A[i]/(delta+1);
		bucket[index].push_back(A[i]);
	}
	//同一个桶中忽略不计
	//最大值位于某个桶的最小值与前一个桶中的最大值的差值
	int maxDiff = delta;
	int maxbefore,minthis;
	bool flag = false;  //标志存在maxbefore
	for(int i=1;i<n;i++){
		if(bucket[i-1].size()!=0){
			maxbefore = *max_element(bucket[i-1].begin(),bucket[i-1].end());
			flag = true;
		}
		if(!flag) continue;
		if(bucket[i].size()==0) continue;
		int minthis = *min_element(bucket[i].begin(),bucket[i].end());
		int diff = minthis-maxbefore;
		if(diff>maxDiff)
			maxDiff = diff;
	}
	return maxDiff;
}

int main()
{
	int A[] = {3,1,4,5,7,10};
	//cout<<maxDiff(A,6)<<endl;
	cout<<maxDiff1(A,6)<<endl;
	return 0;
}
