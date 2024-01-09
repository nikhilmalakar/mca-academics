#include<iostream>
#define N 6
using namespace std;
int maxi=INT_MAX;
string shortp="";

void shortPath(int graph[N][N],int src,int dest,int sum,string path,int visited[N])
{
	if(src==dest)
	{
		//Destination reached - check maximum
		if(sum<maxi)
		{
			maxi=sum;
			shortp=path;
		}
		
	}
	//make the node visited
	visited[src]=1;
	
	for(int i=0;i<N;i++)
	{
		
		//calling adjacent unvisited node 
		if(graph[src][i]!=0 && visited[i]==0)
		{
			shortPath(graph,i,dest,sum+graph[src][i],path+to_string(i)+" ",visited);
		}
	}
	//make that node again unvisited
	visited[src]=0;
	
}
int main()
{
		//INPUT Graph
		int graph[N][N] = { {0,4,5,0,0,0},
                     	{4,0,11,9,7,0},
						 {5,11,0,0,3,0 },
						 { 0,9,0,0,13,2},
						 {0,7,3,13,0,6},
						 { 0,0,0,2,6,0}};
		
		//Visited nodes array
		int visited[N]={0,0,0,0,0,0};
		int source;
		int dest;
		cout<<"Enter source node ";
		cin>>source;
		
		cout<<"\nEnter destination node ";
		cin>>dest;
		
		
		//this function will show path from a sigle source to single destination
		shortPath(graph,source,dest,0,""+to_string(source)+" ",visited);
		cout<<" Shortest path is "<<shortp<<" with cost "<<maxi;

	return 0;
}




