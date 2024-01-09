
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class process{
	public:
		string pId;
		int priority;
		int arrivalTime;
		int CPUtime;
		int remainTime;
		int StartTime;
		int EndTime;
		int waitingTime;
		int TurnAroundTime;
		process(int At,int Cput,string pid,int pri){
			priority = pri;
			arrivalTime = At;
			CPUtime = Cput;
			remainTime = Cput;
			pId = pid;
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
int main()
{
	cout<<"---------- Priority based non-preemptive Algorithm ---------\n";
	int n,qtm;
	cout<<"Enter Number of processes : ";
	cin>>n;
	
//  to store the arrival time and the cputime of the processes
	vector<vector<int>> v;
	for(int i=0;i<n;i++)
	{
		int At,cput,priority;
		cout<<"Enter Arrival time for process "<<i+1<<" : ";
		cin>>At;
		cout<<"Enter cpu time for process" <<i+1<<" : ";
		cin>>cput;
		cout<<"Enter priority of process "<<i+1<<" : ";
		cin>>priority;
		v.push_back({priority,At,cput});
	}
	
	sort(v.begin(),v.end(),mycmp);
	
	process *P[n];
	
	for(int i=0;i<n;i++)
	{
		int priority = v[i][0];
		int arrivalTime = v[i][1];
		int CPUtime = v[i][2];
		string pid = "P" + to_string(i+1);
		P[i] = new process(arrivalTime,CPUtime,pid,priority);
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
		cout<<" "<<curr->pId;
		if(curr->remainTime == curr->CPUtime)  //first time cpu alloted to process
			curr->StartTime = currentTime;
			
		currentTime += curr->CPUtime;
		curr->remainTime =0;
		
		
		while(i<n && P[i]->arrivalTime <= currentTime)
			q.push(P[i++]);
		
		curr->EndTime = currentTime;
	}
	cout<<" "<<currentTime<<endl;
		
	int TATsum = 0;
	int TWTsum = 0;
	
//	 for the first process
	P[0]->StartTime = P[0]->arrivalTime;
	P[0]->TurnAroundTime = P[0]->EndTime - P[0]->arrivalTime;
	P[0]->waitingTime = P[0]->TurnAroundTime - P[0]->CPUtime;
	TATsum += P[0]->TurnAroundTime;
	TWTsum += P[0]->waitingTime;
	
//	for next coming processes;
	for(int i=1;i<n;i++)
	{
		P[i]->TurnAroundTime = P[i]->EndTime - P[i]->arrivalTime;
		P[i]->waitingTime = P[i]->TurnAroundTime - P[i]->CPUtime;;
		TATsum += P[i]->TurnAroundTime;
		TWTsum += P[i]->waitingTime;
	}
	float avgTAT = (float)TATsum / (n*1.0);
	float avgTWT =  (float)TWTsum / (n*1.0);
	
//	printing the process table
	
	cout<<"\n\n Process AT  CPUT  ST  ET  WT  TAT \n";
	for(int i=0;i<n;i++)
	{
		cout<<" "<<P[i]->pId<<"      "<<P[i]->arrivalTime<<"   "<<P[i]->CPUtime<<"    "<<P[i]->StartTime<<"    "<<P[i]->EndTime<<"    "<<P[i]->waitingTime<<"    "<<P[i]->TurnAroundTime<<endl;
	}
	
	cout<<"\n The Average Turn Around Time for all the processes is : "<<avgTAT<<endl;
	cout<<"\n The Average Waiting Time for all the processes is : "<<avgTWT<<endl;
	cout<<"\n\n AT - Arrival Time\n CPUT - Required CPU Time\n ST - Starting Time\n ET - Ending Time\n WT - Waiting Time \n TAT - Turn Around Time"<<endl;
	return 0;
}