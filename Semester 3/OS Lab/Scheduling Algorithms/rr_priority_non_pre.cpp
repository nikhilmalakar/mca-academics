#include <bits/stdc++.h>
using namespace std;

int space = 6;

void printCell(string s) {
	cout << s;
	for(int i=0; i<space-s.size(); i++) {
		cout << " ";
	}
}

int main() {
	int n;
	cout<<"---------- Priority - Round Robin Algorithm ---------\n\n";
	cout << "Enter the number of processes: ";
	cin >> n;
	
	vector<vector<int>> pro;
	for(int i=0; i<n; i++) {
		cout << "ArrivalTime, BurstTime, Priority of P" << i+1 << " : ";
		int at, et, prio;
		cin >> at >> et >> prio;
		pro.push_back({at, prio, et, i+1});
	}
	cout<<endl;
	
	sort(pro.begin(), pro.end());
	map<int, queue<vector<int>>> mpp;
	int t = 0;
	int idx = 0;
	
	vector<vector<int>> ans;
	set<int> stt;
	
	while(idx < n || mpp.size()) {
		while(idx < n && pro[idx][0] <= t) {
			int prio = pro[idx][1];
			int et = pro[idx][2];
			int pn = idx;
			
			mpp[prio].push({-1, et, idx});
			stt.insert(prio);
			idx++;
			continue;
		}
		if(mpp.size() == 0) {
			cout << " I ";
			t++;
			continue;
		}
		int prio = *stt.begin();
		vector<int> temp = mpp[prio].front();
		mpp[prio].pop();
		
		cout<<t<<" ";
		cout << " P" << pro[temp[2]][3] << " "; 
		temp[1]--;
		if(temp[0] == -1) {
			temp[0] = t;
		}
		t++;
		if(temp[1] == 0) {
			ans.push_back({temp[2], temp[0], t});
			if(mpp[prio].size() == 0) {
				mpp.erase(prio);
				stt.erase(prio);
			}
		}else {
			mpp[prio].push(temp);
		}
	}
	cout<<t<<endl;
	cout << endl << endl;
	cout << "Process   AT    P  ET    ST    FT    WT    TAT   " << endl;
	
	int totalTAT = 0;
	int totalWT = 0;
	
	for(int i=0; i<ans.size(); i++) {
		int ind = ans[i][0];
		int st = ans[i][1];
		int ft = ans[i][2];
		int at = pro[ind][0];
		int et = pro[ind][2];
		int prio = pro[ind][1];
		int pn = pro[ind][3];
		int tat = ft - at;
		int wt = tat - et;
		
		printCell("P"+to_string(pn));
		printCell(to_string(at));
		printCell(to_string(prio));
		printCell(to_string(et));
		printCell(to_string(st));
		printCell(to_string(ft));
		printCell(to_string(wt));
		printCell(to_string(tat));
		
		totalWT += wt;
		totalTAT += tat;
		
		cout << endl;
	}
	
	cout<<"\nThe Average Turn Around Time for all the processes is : "<<totalTAT/n<<endl;
	cout<<"\nThe Average Waiting Time for all the processes is : "<<totalWT/n<<endl;
	
	return 0;
}




