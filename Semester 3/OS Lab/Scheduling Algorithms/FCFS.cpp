#include<bits/stdc++.h>
using namespace std;
	
	//Calculate start Time
	void startTimeCalculate(vector<pair<int, int>>tasks, vector<int> &startTime, int n){
		startTime[0] = 0;
		for(int i=1; i<n; i++){
			startTime[i] = tasks[i-1].second + startTime[i-1];
		}
	}
	
	//Calculate finish Time
	void finishTimeCalculate(vector<pair<int, int>>tasks, vector<int> &finishTime, int n){
		finishTime[0] = tasks[0].second;
		for(int i=1; i<n; i++){
			finishTime[i] = tasks[i].second + finishTime[i-1];
		}
	}
	
	//Calculate turn around Time
	void turnAroundTimeCalculate(vector<pair<int, int>>tasks, vector<int> &turnAroundTime, int n, 
			 vector<int> &finishTime){
		for(int i=0; i<n; i++){
			turnAroundTime[i] = finishTime[i] - tasks[i].first;
		}
	}
	
	//Calculate waiting Time
	void waitingTimeCalculate(vector<pair<int, int>>tasks, vector<int> &waitingTime, vector<int> &turnAroundTime, int n){
		for(int i=0; i<n; i++){
			waitingTime[i] = turnAroundTime[i] - tasks[i].second;
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

//Main function call
int main(){
	
	// Enter number of tasks
	int n = 0;
	cout<<"Enter number of tasks : ";
	cin>>n;
	vector<pair<int, int>> tasks(n);
	
	//Take input of arrival and end time of tasks
	for(int i =0; i<n; i++){
		cout<<"Enter arrival time of task "<< i<< " : ";
		cin>> tasks[i].first;
		cout<<"Enter end time of task "<< i<< " : ";
		cin>> tasks[i].second;
		cout<<endl;
	}
	
	//Sort them on arrival time
	sort(tasks.begin(), tasks.end());
	
	vector<int> startTime(n), finishTime(n), waitingTime(n), turnAroundTime(n);
	
	//calculating required times of tasks
	startTimeCalculate(tasks, startTime, n);
	finishTimeCalculate(tasks, finishTime, n);
	turnAroundTimeCalculate(tasks, turnAroundTime, n, finishTime);
	waitingTimeCalculate(tasks, waitingTime, turnAroundTime, n);
	
	cout<<"Start Time  ";
	cout<<"Finish Time  ";
	cout<<"Turn Around Time  ";
	cout<<"Waiting Time"<<endl;
	
	for(int i=0; i<n; i++){
		cout<<"  "<<startTime[i]<<"          ";
		cout<<"  "<<finishTime[i]<<"          ";
		cout<<"  "<<turnAroundTime[i]<<"              ";
		cout<<"  "<<waitingTime[i]<<"        "<<endl;
	}
	
	cout<<endl<<endl;
	
	cout<<endl<<endl;
	
	//Average Time
	cout<<"Average Turn Around Time : "<<mean(turnAroundTime)<<endl;
	cout<<"Average Waiting Time : "<<mean(waitingTime)<<endl;
	
	return 0;
}