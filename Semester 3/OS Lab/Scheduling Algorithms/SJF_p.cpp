#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class process{
	public:
		string pId;
		int arrivalTime;
		int CPUtime;
		int StartTime;
		int EndTime;
		int remainTime;
		int waitingTime;
		int TurnAroundTime;
		process(int At,int Cput,string pid){
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
		// cputime, arrivalTime
		if(p->remainTime == q->remainTime)
			return p->arrivalTime > q->arrivalTime;
		return p->remainTime > q->remainTime;			
	}
};

bool mycmp(pair<int,int> &p, pair<int,int> &q)
{
//	if(p.first == q.first)
//		return p.second < q.second;
	return p.first<q.first;
}
int main()
{
	int n ;
	cout<<"---------- SJF Algorithm ---------\n";
	
	cout<<"Enter the number of processes : ";
	cin>>n;
	
	process *P[n];
	vector<pair<int,int>> v;
	
	for(int i=0;i<n;i++)
	{
		int At,CPUtime;
		cout<<"Enter Arrival time for process "<<i+1<<" : ";
		cin>>At;
		cout<<"Enter the CPU time for the process "<<i+1 << " : ";
		cin>>CPUtime;
		v.push_back({At,CPUtime});
	}
//	sorting the processes based on their CPUtime - shorted job comes first
	sort(v.begin(),v.end(),mycmp);
	
	for(int i=0;i<n;i++)
	{
		int arrivalTime = v[i].first;
		int CPUtime = v[i].second;
		string pid = "P" + to_string(i+1);
		P[i] = new process(arrivalTime,CPUtime,pid);
	}
//	
//	for(int i=0;i<n;i++)
//	{
//		cout<<P[i]->CPUtime<<" ";
//	}
//	cout<<"\n";
	
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
			
		currentTime++;
		curr->remainTime--;
		
		
		while(i<n && P[i]->arrivalTime <= currentTime)
			q.push(P[i++]);
		
		if(curr->remainTime > 0)
			q.push(curr);
		else
			curr->EndTime = currentTime;
			
		if(q.empty() && i<n)
		{
			cout<<" "<<currentTime;
			cout<<" Idle ";
			currentTime = P[i]->arrivalTime;
			q.push(P[i++]);
		}
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