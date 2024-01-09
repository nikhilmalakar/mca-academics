
//SJF 
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

	struct sjf{
		int process_id;
		int arrivalTime;
		int burstTime;
		int startTime;
		int endTime;
		int waitTime;
		int tat;
	};

	vector<sjf> arr;
	
	//Comparater for ARRAY sort
	bool comp(struct sjf f1,struct sjf f2){
		return f1.arrivalTime < f2.arrivalTime;
	}
	
	bool printcomp(struct sjf f1,struct sjf f2){
		return f1.startTime < f2.startTime;
	}
	
	//Comparater for Priority Queue
	struct mycmp{
		bool operator()(int &a,int &b){
			return  arr[a].burstTime > arr[b].burstTime;
		}
	};

	//Calculations
	void takeInput(vector<sjf> &arr,int n){
		
		//Taking Input
		for(int i=0;i<n;i++){
			cout<<"Enter Arrival Time : ";
			cin>>arr[i].arrivalTime;
			cout<<"Enter Burst Time : ";
			cin>>arr[i].burstTime;
			arr[i].process_id = i+1;
		}
		
		//Sort on arrival time
		sort(arr.begin(),arr.end(),comp);
		
		//sort on burst time
		priority_queue<int,vector<int>,mycmp> pq;
		
		int time=arr[0].arrivalTime;
		int i=0;
		
		while(i<n){
			
			//Push Available Tasks
			while(i<n&&arr[i].arrivalTime<=time){
				pq.push(i);
				i++;
			}
			
			while(!pq.empty()){
				int idx=pq.top();
				pq.pop();
				
				arr[idx].startTime=time;
				time += arr[idx].burstTime;
				
				arr[idx].endTime  = arr[idx].startTime + arr[idx].burstTime;
			    arr[idx].tat = arr[idx].endTime - arr[idx].arrivalTime;
			    arr[idx].waitTime  = arr[idx].tat - arr[idx].burstTime;
			    
			    //Push Available
				while(i<n&&arr[i].arrivalTime<=time){
					pq.push(i);
					i++;
				}
			}
			
			//If queue is empty
			if(i<n){
				time=arr[i].arrivalTime;
			}
		}
	}
	
	//Print table
	void printTable(vector<sjf> &arr,int n){
		
		sort(arr.begin(), arr.end(), printcomp);
		
		cout<<"id  arrivalTime burstTime startTime  endTime    waitTime    tat"<<endl;
		
		for(int i=0;i<n;i++){
			cout<<" "<<arr[i].process_id<<"    "<<arr[i].arrivalTime<<"         "<<arr[i].burstTime<<"          "<<arr[i].startTime<<"          "<<arr[i].endTime<<"          "<<arr[i].waitTime<<"          "<<arr[i].tat<<endl;
		}
	}
	
int main(){
	
	cout<<"SJF -Shortest Job First\n";
	int n; 
	cout<<"Enter number of tasks: ";
	cin>>n;
	
	//vector of process
    vector<sjf> v(n);
    
    arr=v;
    
	takeInput(arr,n);
	cout<<endl<<endl;
	
	printTable(arr,n);
	cout<<"\n\n";
	
	float totaltat=0;
	float totalwt=0;
	
	for(int i=0;i<n;i++){
		totaltat+=(arr[i].tat);
		totalwt+=(arr[i].waitTime);
	}
	
	float avgtat=(totaltat)/(float(n));
	float avgwt=(totalwt)/(float)n;
	
		cout<<"Mean Turn Around Time : "<<avgtat<<endl;
		cout<<"Mean Waiting Time: "<<avgwt<<endl;
		
	return 0;
}
