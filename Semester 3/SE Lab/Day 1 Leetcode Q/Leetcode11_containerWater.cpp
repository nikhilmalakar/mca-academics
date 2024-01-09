#include <bits/stdc++.h>
using namespace std;


int main(){
	vector<int> nums;
	int val;
	
	cout << "Enter the height values:(enter -1 to stop) ";
	while(1) {
		cin >> val;
		if(val == -1) break;
		nums.push_back(val);	
	}
	
	int i = 0, j = nums.size() - 1;
	int result = INT_MIN;
	
	while(i < j){
		int minH = min(nums[i], nums[j]);
		result = max(result, minH * (j - i)) ;
		if(nums[i] < nums[j]) i++;
		else j--;
	}
	
	cout << "Maximum amount of water :  " << result;
	
	return 0;
}