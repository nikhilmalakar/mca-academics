#include <bits/stdc++.h>

using namespace std;

int main(){
	
	cout<<"Enter the size of array : ";
	int n;
	cin>>n;
	
	vector<int> nums(n);
	
	int num;
	cout << "Enter the array elements : ";
	for(int i=0; i<n; i++) {
		cin>>num;
		nums.push_back(num);	
	}
	
	vector<vector<int>> ans;
	
        if(nums.size() < 3) return 0;
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < nums.size()-2; ++i)
        {
            if(i != 0 && nums[i] == nums[i-1])
                continue;
            
            int a = i + 1, b = nums.size() -1, t;
            while(a < b)
            {
                t = nums[i] + nums[a] + nums[b];
                if(t > 0)
                    b--;
                else if(t < 0)
                    a++;
                else
                {
                    ans.push_back({nums[i] , nums[a] , nums[b]});
                    a++; b--;
                    while(nums[a] == nums[a-1] && a < b)
                        a++;
                    while(nums[b] == nums[b+1] && a < b)
                        b--;
                }
            }
        }
        
        for(auto x : ans){
        	for(auto y : x)
        		cout<<y<<" ";
        	cout<<endl;
		}
    
	return 0;
}