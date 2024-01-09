#include <bits/stdc++.h>

using namespace std;

int main(){
	string str;
	int n;
	
	cout << "Enter String : ";
	cin >> str;
	cout << "Enter number of rows: ";
	cin >> n;
	
	vector<string> mat(n, "");
	
    if(n == 1) cout << str;
    int i = 0, col = 0;
    
    while(i < str.length()){
        for(int j = 0; j < n; j++){
            if(col % (n - 1) == 0 and i < str.length()) mat[j] += str[i++];
            else{
                int r = col % (n - 1);
                if(j == n - r - 1 and i < str.length()) mat[j] += str[i++];
            }
        }
        col ++;
    }

    string result = "";
    for(int a = 0; a < n; a++) result += mat[a];

    cout << result;
	
	return 0;
}