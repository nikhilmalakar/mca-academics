#include<bits/stdc++.h>
using namespace std;
	
	//Calculate start Time
	void startTimeCalculate(vector<vector<int>>tasks, vector<int> &startTime, int n){
		startTime[0] = 0;
		for(int i=1; i<n; i++){
			startTime[i] = tasks[i-1][2] + startTime[i-1];
		}
	}
	
	//Calculate finish Time
	void finishTimeCalculate(vector<vector<int>>tasks, vector<int> &finishTime, int n){
		finishTime[0] = tasks[0][2];
		for(int i=1; i<n; i++){
			finishTime[i] = tasks[i][2] + finishTime[i-1];
		}
	}
	
	//Calculate turn around Time
	void turnAroundTimeCalculate(vector<vector<int>>tasks, vector<int> &turnAroundTime, int n, 
			 vector<int> &finishTime){
		for(int i=0; i<n; i++){
			turnAroundTime[i] = finishTime[i] - tasks[i][1];
		}
	}
	
	//Calculate waiting Time
	void waitingTimeCalculate(vector<vector<int>>tasks, vector<int> &waitingTime, vector<int> &turnAroundTime, int n){
		for(int i=0; i<n; i++){
			waitingTime[i] = turnAroundTime[i] - tasks[i][2];
		}
	}
	
	//Calculate mean Time
	double mean( vector<int> vec){
		double sum=0;
		for(int i=0; i<vec.size(); i++){
			sum += vec[i];
		}
		return sum / vec.size();
	}
	
	bool mycomp(vector<int> v1, vector<int> v2){
		return v1[1] < v2[1];
	}
	
//Main function call
int main(){
	
	// Enter number of tasks
	int n = 0;
	cout<<"Enter number of tasks : ";
	cin>>n;
	vector<vector<int>> tasks(n, vector<int>(3));
	
	//Take input of arrival and end time of tasks
	for(int i =0; i<n; i++){
		tasks[i][0] = i+1;
		cout<<"Enter arrival time of task "<< i<< " : ";
		cin>> tasks[i][1];
		cout<<"Enter end time of task "<< i<< " : ";
		cin>> tasks[i][2];
		cout<<endl;
	}
	
	//Sort them on arrival time
	sort(tasks.begin(), tasks.end(), mycomp);
	
	vector<int> startTime(n), finishTime(n), waitingTime(n), turnAroundTime(n);
	
	//calculating required times of tasks
	startTimeCalculate(tasks, startTime, n);
	finishTimeCalculate(tasks, finishTime, n);
	turnAroundTimeCalculate(tasks, turnAroundTime, n, finishTime);
	waitingTimeCalculate(tasks, waitingTime, turnAroundTime, n);
	
	cout<<"Task   ";
	cout<<"Start Time  ";
	cout<<"Finish Time  ";
	cout<<"Turn Around Time  ";
	cout<<"Waiting Time"<<endl;
	
	for(int i=0; i<n; i++){
		cout<<"  "<<tasks[i][0]<<"      ";
		cout<<"  "<<startTime[i]<<"          ";
		cout<<"  "<<finishTime[i]<<"          ";
		cout<<"  "<<turnAroundTime[i]<<"              ";
		cout<<"  "<<waitingTime[i]<<"        "<<endl;
	}
	
	cout<<endl<<endl;
//	
//	cout<<"---Gantt Chart---\n";
//	for(int i=0; i<n; i++){
//		cout<<" P"<<i+1<<" | ";
//	}
//	cout<<endl;
//	for(int i=0; i<n; i++){
//		cout<<waitingTime[i]<<" "<<finishTime[i]<<" | ";
//	}
	
	cout<<endl<<endl;
	
	//Average Time
	cout<<"Average Turn Around Time : "<<mean(turnAroundTime)<<endl;
	cout<<"Average Waiting Time : "<<mean(waitingTime)<<endl;
	
	return 0;
}