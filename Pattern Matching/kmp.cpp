#include<bits/stdc++.h> 
using namespace std;

//function to calculate pi array 
void fillPiArray(string pattern, int P, vector<int> &piArray) 
{ 
	int length = 0;// variable to store length of the previous longest prefix which is also suffix  

	piArray[0] = 0; //1st entry at 0th index is always 0  

	int i = 1; 
	//loop to fill the array such that length of the maximum matching proper prefix which is also a suffix of the sub-pattern
	while(i<P) 
	{ 
		if (pattern[i]==pattern[length]) 
		{ 
			length++; 
			piArray[i++]=length; 
		} 
		else //character at pattern[i] is not equalt to character at pattern[length] 
		{ 
			if (length!=0) 
				length=piArray[length-1]; 			
			else // length is 0 
			{ 
				piArray[i++]=0;
			} 
		} 
	} 
} 
//function to search pattern in text 
void KMP(string pattern, string text,vector<int> piArray) 
{ 
	int P = pattern.length(); 
	int T = text.length(); 

	int i = 0; //index on text
	int j = 0; //index on pattern 
	while (i < T) 
	{ 
		if (pattern[j] == text[i])//if same then increment both indexes 
		{ 
			j++; 
			i++; 
		} 

		if (j == P)//if count of j is equal to pattern length means a pattern is found 
		{ 
			cout<<"pattern is at index "<<i - j<<endl; 
			j = piArray[j - 1]; 
		} 

		// if mismatch  
		else if (i < T && pattern[j] != text[i]) 
		{ 
			if (j != 0) 
				j = piArray[j - 1]; 
			else
				i++; 
		} 
	} 
} 



//main function
int main() 
{ 
	cout<<"\n\n-----------Welcome to KMP string Matching-----------";
	string text;
	string pattern;
	
	//input text
	cout<<"\nEnter Text\t";
	getline(cin, text);
	
	//input pattern
	cout<<"\nEnter Pattern\t";
	cin>>pattern;

	//vector to store pi array values
	vector<int> piArray(pattern.length());

	//fill pi array  
	fillPiArray(pattern, pattern.length(), piArray);
	
	//calling search function
	KMP(pattern, text,piArray);
} 
