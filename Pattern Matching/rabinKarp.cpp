#include<bits/stdc++.h>
using namespace std;
 
#define charCount 62 //this charCount will be used in calculating hash value 62 covers all the upper and lower case character with 0-9 10 digits so 26+26+10=62 

void rabinKarp(string pattern, string text, int prime) 
{ 
	int P = pattern.length(); 
	int T = text.length(); 
	int i, j; 
	int pattHash = 0; // hash value for pattern 
	int txtHash = 0; // hash value for text 
	
	

	// Calculate the hash value of pattern and first P characters of text
	for (i=0;i<P;i++) 
	{ 
		pattHash=(charCount*pattHash+pattern[i])%prime; 
		txtHash=(charCount*txtHash+text[i])%prime; 
	} 

	// using sliding window technique sliding over each character
	for(i=0;i<=T-P;i++) 
	{ 
		//if both the hash are equal then comparing every character of pattern and text so that to avoid suprious hits
		if (pattHash==txtHash) 
		{ 
			for(j=0;j<P;j++) 
			{ 
				if (text[i+j]!=pattern[j])//suprious hit encountered i.e same hash but no string matching 
					break; 
			} 
			//if no suprious hit 
			if (j==P) 
				cout<<"found at index"<<i<<endl; 
		} 
		//calculating hash value of next window by removing 1st character of previous window and adding last character of new window
		if (i<T-P) 
		{ 
			txtHash=(charCount*(txtHash-text[i]*((int)pow(charCount,P-1)%prime))+text[i+P])%prime; 
			if(txtHash<0)//if txtHash is negative then make is positive 
				txtHash=(txtHash+prime); 
		} 
	} 
} 


int main() 
{ 
	cout<<"\t\t-----------Welcome to RabinKarp string Matching-----------";
	string text;
	string pattern;
	
	//input text
	cout<<"\nEnter Text\t";
	getline(cin, text);
	
	//input pattern
	cout<<"\nEnter Pattern\t";
	cin>>pattern;
	
	//calling function to search pattern in string
	rabinKarp(pattern, text, 101); 
	return 0; 
} 
