#include<bits/stdc++.h>
#include<iostream>
using namespace std;

// round robin structure
struct roundrobinp {
	char process;
	int priority;
	int arrivalTime;
	int burstTime;
	int startTime;
	int endTime;
	int wt;
	int tat;
};

vector<roundrobinp> arr;
//priortiy queue comp
struct mycmp{
	bool operator()(pair<pair<int,int>,int> &a,pair<pair<int,int>,int> &b){
		if(arr[a.first.first].priority==arr[b.first.first].priority){
			return a.first.second>b.first.second;
		}
		return arr[a.first.first].priority>arr[b.first.first].priority;
	}	
};

int timeqt;

//print table function
void printTable(vector<roundrobinp> &arr,int n,string &gc) {
	
	priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,mycmp> q;
	int i=0;
	int time=arr[i].arrivalTime;
	gc+=to_string(time);
	while(i<n){
		//Pushing the available process in queue
		while(i<n&&arr[i].arrivalTime<=time){
				q.push({{i,arr[i].arrivalTime},arr[i].burstTime});
				i++;
		}
		
//		executing available process
		while(q.empty()==false){
		   	pair<pair<int,int>,int> p=q.top();q.pop();
		   	gc+=' ';
		   	gc+=(arr[p.first.first].process);
		   	gc+=' ';
	
			if(p.second==arr[p.first.first].burstTime){
				p.first.second=time;
				arr[p.first.first].startTime=time;
			}
			p.second=p.second-timeqt;
			if(p.second<=0){//finished
				arr[p.first.first].endTime=time+(timeqt+p.second);
				time+=(timeqt+p.second);
				p.first.second=time;
				while(i<n&&arr[i].arrivalTime<=time){
				q.push({{i,arr[i].arrivalTime},arr[i].burstTime});
				i++;
			}
			}
			//not finished
			else {
				time+=timeqt;
				p.first.second=time;
				while(i<n&&arr[i].arrivalTime<=time){
				q.push({{i,arr[i].arrivalTime},arr[i].burstTime});
				i++;
			}
			
				q.push({{p.first.first,p.first.second},p.second});
			}
			gc+=(to_string(time));
			
		}
		
		//if CPU is idle
		if(i<n){
			
			time=arr[i].arrivalTime;
			gc+=(" IDLE ");gc+=(to_string(time));
		}
	}
	for(int i=0;i<n;i++){
		arr[i].tat=arr[i].endTime-arr[i].arrivalTime;
		arr[i].wt=arr[i].tat-arr[i].burstTime;
	}
	
	//Printing out the details
	cout<<"arrivalT   burstT      startT      endTime       WT       TAT"<<endl;
	for(int i=0; i<n; i++) {
		cout<<"   "<<arr[i].arrivalTime<<"         "<<arr[i].burstTime<<"          "<<arr[i].startTime<<"          "<<arr[i].endTime<<"          "<<arr[i].wt<<"          "<<arr[i].tat<<endl;
	}
}

//Comparator for queue
bool comp(struct roundrobinp f1,struct roundrobinp f2) {
	return f1.arrivalTime<f2.arrivalTime;
}

//taking input of process
void takeInput(vector<roundrobinp> &arr,int n) {
	for(int i=0; i<n; i++) {
		cout<<"Enter ARRIVAL - BURST - PRIORITY of process : ";
		cin>>arr[i].arrivalTime>>arr[i].burstTime>>arr[i].priority;

	}
	sort(arr.begin(),arr.end(),comp);
	for(int i=0;i<n;i++){
		arr[i].process=char('A'+i);
	}
	cout<<"Enter the time quantum: ";
	cin>>timeqt;
}

//Main driver function
int main() {
	cout<<"----- Round Robin with Priority -----\n";
	int n;
	cout<<"Enter number of process : ";
	cin>>n;
	vector<roundrobinp> temp(n);
	takeInput(temp,n);
	arr=temp;
	string genttchart="";
	printTable(arr,n,genttchart);
		cout<<"\n\n";
	float totaltat=0;
	float totalwt=0;
	for(int i=0;i<n;i++){
		totaltat+=(arr[i].tat);
		totalwt+=(arr[i].wt);
	}
	float avgtat=(totaltat)/(float(n));
	float avgwt=(totalwt)/(float)n;
	
	//Print gantt chart
	cout<<"GANTT CHART"<<endl;
	cout<<genttchart<<"\n\n";
	cout<<"AVERAGE TURN AROUND TIME : "<<avgtat<<endl;
	cout<<"AVERAGE WAITING TIME : "<<avgwt<<endl;
	return 0;
}