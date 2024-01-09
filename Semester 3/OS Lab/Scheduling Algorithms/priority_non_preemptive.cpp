#include<iostream>
#include<bits/stdc++.h>

using namespace std;
	
//class based implementation of task
class process{
	public:
		int process_id;
		int priority;
		int arrivalTime;
		int burstTime;
		int remainTime;
		int StartTime;
		int EndTime;
		int waitingTime;
		int TurnAroundTime;
		
		process(int arrival,int burst,int id,int p){
			priority = p;
			arrivalTime = arrival;
			burstTime = burst;
			remainTime = burst;
			process_id = id;
		}
};

class mycomp{
	public:
	bool operator()(process * &p,process *&q)
	{
		// priority, arrivalTime
		if(p->priority == q->priority)
			return p->arrivalTime > q->arrivalTime;
		return p->priority > q->priority;			
	}
};

bool mycmp(vector<int> &p, vector<int> &q)
{
	if(p[1] == q[1])
		return p[0]<q[0];
	return p[1] <q[1];
}

//Main driver code
int main()
{
	cout<<"--- Priority Based Non-Preemptive Scheduling ---\n";
	
	int n,qtm;
	cout<<"Enter Number of processes : ";
	cin>>n;
	
	//Taking inputs to process
	vector<vector<int>> v;
	for(int i=0;i<n;i++)
	{
		int At,cput,priority;
		
		cout<<"Enter Arrival time of process "<<i+1<<" : ";
		cin>>At;
		cout<<"Enter burst time for process" <<i+1<<" : ";
		cin>>cput;
		cout<<"Enter priority of process "<<i+1<<" : ";
		cin>>priority;
		v.push_back({priority,At,cput});
	}
	cout<<endl;
	
	//Sorting based on priority
	sort(v.begin(),v.end(),mycmp);
	
	process *P[n];
	
	//Creating process objects
	for(int i=0;i<n;i++)
	{
		int priority = v[i][0];
		int arrivalTime = v[i][1];
		int burstTime = v[i][2];
		int process_id = i+1;
		P[i] = new process(arrivalTime,burstTime,process_id,priority);
	}
	
	priority_queue<process *,vector<process *>,mycomp> q;
	
	
	int i=0;
	int currentTime = P[i]->arrivalTime;

	q.push(P[i++]);
	
	cout<<" \n GANTT CHART : \n";

	
	while(!q.empty())
	{
		process * curr = q.top();
		q.pop();
		
		cout<<" "<<currentTime;
		cout<<" P"<<curr->process_id;
		
		//New task is introduced
		if(curr->remainTime == curr->burstTime)  
			curr->StartTime = currentTime;
			
		currentTime += curr->burstTime;
		curr->remainTime =0;
		
		
		while(i<n && P[i]->arrivalTime <= currentTime)
			q.push(P[i++]);
		
		curr->EndTime = currentTime;
	}
	cout<<"  "<<currentTime<<endl;
	cout<<endl;
		
	int TATsum = 0;
	int TWTsum = 0;

	//Calculating Average TAT and WT
	P[0]->StartTime = P[0]->arrivalTime;
	P[0]->TurnAroundTime = P[0]->EndTime - P[0]->arrivalTime;
	P[0]->waitingTime = P[0]->TurnAroundTime - P[0]->burstTime;
	TATsum += P[0]->TurnAroundTime;
	TWTsum += P[0]->waitingTime;
	
	for(int i=1;i<n;i++)
	{
		P[i]->TurnAroundTime = P[i]->EndTime - P[i]->arrivalTime;
		P[i]->waitingTime = P[i]->TurnAroundTime - P[i]->burstTime;;
		TATsum += P[i]->TurnAroundTime;
		TWTsum += P[i]->waitingTime;
	}
	float avgTAT = (float)TATsum / (n*1.0);
	float avgTWT =  (float)TWTsum / (n*1.0);
	
	//Printing table
	cout<<"ArrivalTime BurstTime StartTime  EndTime     WaitTime     TAT"<<endl;
	for(int i=0; i<n; i++) {
		cout<<" "<<P[i]->arrivalTime<<"         "<<P[i]->burstTime<<"          "<<P[i]->StartTime<<"          "<<P[i]->EndTime<<"          "<<P[i]->waitingTime<<"          "<<P[i]->TurnAroundTime<<endl;
	}
//	cout<<"\n\n Process AT  CPUT  ST  ET  WT  TAT \n";
//	for(int i=0;i<n;i++)
//	{
//		cout<<" P"<<P[i]->process_id<<"      "<<P[i]->arrivalTime<<"   "<<P[i]->burstTime<<"    "<<P[i]->StartTime<<"    "<<P[i]->EndTime<<"    "<<P[i]->waitingTime<<"    "<<P[i]->TurnAroundTime<<endl;
//	}
	
	cout<<"\n Average Turn Around Time  : "<<avgTAT<<endl;
	cout<<"\n Average Waiting Time  : "<<avgTWT<<endl;
	return 0;
}