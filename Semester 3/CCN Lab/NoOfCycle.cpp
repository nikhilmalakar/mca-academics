#include<iostream>
using namespace std;
#define N 6
int main()
{
	
		//assumption is graph is undirected and connected 
		int graph[N][N] = { 
						  {0,4,5,0,0,0},
                     	  {4,0,11,9,7,0},
						  {5,11,0,0,3,0},
						  {0,9,0,0,13,2},
						  {0,7,3,13,0,6},
						  {0,0,0,2,6,0}};
	    int edges=0;
	    for(int i=0;i<N;i++)
	    {
	    	for(int j=0;j<N;j++)
	    	{
	    		if(graph[i][j]!=0)
	    		{
	    			edges++;
				}
			}
		}
		
		edges=edges/2;
		
		//no of cycles is without any inner cycles
		cout<<" Number of cycles = "<<(edges-V)+1;
	return 0;
}