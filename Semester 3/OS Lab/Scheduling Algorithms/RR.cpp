
//Round Robin CPU Scheduling
#include<bits/stdc++.h>
#include<iostream>

using namespace std;
	
	//task structure
	int quantum;
	struct rr {
		int process_id;
		int arrivalTime;
		int burstTime;
		int startTime;
		int endTime;
		int waitTime;
		int tat;
	};

	//Calculate and print table
	void printTable(vector<rr> &tasks,int n) {
		
		queue<pair<int,int>> q;
		int i=0;
		int time=tasks[i].arrivalTime;
		
		while(i<n){
			// Pushing available tasks to queue
			while(i<n&&tasks[i].arrivalTime<=time){
				q.push({i,tasks[i].burstTime});
				i++;
			}
			
			// If any tasks is in queue
			while(!q.empty()){
				
				int currTask = q.front().first;
				int currBurstTime = q.front().second;
				q.pop();
				
				
				if(currBurstTime==tasks[currTask].burstTime){
					tasks[currTask].startTime=time;
				}
				cout<<time<<" P"<<tasks[currTask].process_id<<" ";
				
				currBurstTime=currBurstTime-quantum;
				
				
				
				//If tasks is finished
				if(currBurstTime<=0){
				
					tasks[currTask].endTime= time + (quantum + currBurstTime);
					time += (quantum + currBurstTime);
					
					while(i<n && tasks[i].arrivalTime <= time){
						q.push({ i , tasks[i].burstTime});
						i++;
					}
				}
				//if task is not finished
				else {
					time += quantum;
					
					while(i<n && tasks[i].arrivalTime <= time){
						q.push({i , tasks[i].burstTime});
						i++;
					}
					
					//Pushing the executed task back to queue
					q.push({currTask , currBurstTime});
				}
				cout<<time<<"   ";
			}
			//IF queue is empty, push next available task
			if(i<n){
				time=tasks[i].arrivalTime;
			}
		}
		
		// Calculate TAT and WT
		for(int i=0;i<n;i++){
			tasks[i].tat=tasks[i].endTime-tasks[i].arrivalTime;
			tasks[i].waitTime=tasks[i].tat-tasks[i].burstTime;
		}
		cout<<endl<<endl;
		// Printing the table
		cout<<"Id  ArrivalTime BurstTime StartTime  EndTime     WaitTime     TAT"<<endl;
		for(int i=0; i<n; i++) {
			cout<<" "<<tasks[i].process_id<<"     "<<tasks[i].arrivalTime<<"         "<<tasks[i].burstTime<<"          "<<tasks[i].startTime<<"          "<<tasks[i].endTime<<"          "<<tasks[i].waitTime<<"          "<<tasks[i].tat<<endl;
		}
	}

	bool arrivalSort(struct rr f1,struct rr f2) {
		return f1.arrivalTime<f2.arrivalTime;
	}
	
	void takeInput(vector<rr> &tasks,int n) {
		for(int i=0; i<n; i++) {
			cout<<"Enter process Arrival Time : ";
			cin>>tasks[i].arrivalTime;
			cout<<"Enter process Burst Time : ";
			cin>>tasks[i].burstTime;
			tasks[i].process_id = i+1;
		}
		sort(tasks.begin(),tasks.end(), arrivalSort);
		cout<<"Enter the Time Quantum for RR : ";
		cin>>quantum;
	}

int main() {
	cout<<"Round Robin CPU Scheduling\n";
	int n;
	cout<<"Enter number of process: ";
	cin>>n;
	
	// Vector of process array
	vector<rr> tasks(n);
	
	// Input of processes
	takeInput(tasks,n);
	
	//Print table
	cout<<"\n\nGantt Chart of Round Robin \n";
	printTable(tasks,n);
		cout<<endl<<endl<<endl;
		
	float totaltat=0;
	float totalwt=0;
	
	for(int i=0;i<n;i++){
		totaltat+=(tasks[i].tat);
		totalwt+=(tasks[i].waitTime);
	}
	
	float avgtat=(totaltat)/(float(n));
	float avgwt=(totalwt)/(float)n;
	
	cout<<"Mean Turn Around Time : "<<avgtat<<endl;
	cout<<"Mean Waiting Time : "<<avgwt<<endl;
	
	return 0;
}