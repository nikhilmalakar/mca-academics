#include<bits/stdc++.h> 
using namespace std; 

void check(vector<int>&elements, int buffer) 
{ 
	int n = elements.size();
	int faults = 0, miss = 0; 
	set<int> s; 
	queue<int> slots; 

	for (int i=0; i<n; i++) 
	{ 
		// If empty and not available
		if (s.size() < buffer && s.find(elements[i])==s.end()) 
		{ 
			s.insert(elements[i]); 
			slots.push(elements[i]); 
			faults++; 
		} 
		// If not available
		else if (s.find(elements[i])==s.end()){
			int val = slots.front(); 
			slots.pop(); 
			s.erase(val); 
			s.insert(elements[i]); 
			slots.push(elements[i]); 
			faults++; 
		}
		
		//Printing the buffer
		for(int i=0; i<slots.size(); i++){
			cout<<slots.front()<<" ";
			slots.push(slots.front());
			slots.pop();	
		}
		cout<<endl;
	} 
	cout<<" Page Faults " << Faults <<endl;
} 

int main() 
{ 
	cout<<"FIFO - Page Replacement Memory Management"<<endl;
	int n;
	cout<<"Number of elements : ";
	cin>>n;
	
	vector<int> elements;
	cout<<"Enter "<<n<<" elements : ";
	for(int i=0; i<n; i++){
		int t;
		cin>>t;
		elements.push_back(t);
	}
	
	//	1 2 3 4 3 1 5 6 2 4
	//	
	
	int buffer;
	cout<<"\nBuffer Size: ";
	cin>>buffer;
	
	cout << "Number of page replacements : \n";
	check(elements, buffer); 
	
	return 0; 
} 
