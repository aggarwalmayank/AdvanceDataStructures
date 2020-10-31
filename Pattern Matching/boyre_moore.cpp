#include <bits/stdc++.h> 
using namespace std; 
# define charCount 256  
  
//function to calculate or preprocess tha bad character rule heuristic
void badCharPreprocessing(string patt, int m, vector<int> &badChar) 
{  
    for (int i = 0; i < m; i++) 
        badChar[patt[i]] = i;  
}  
//function to calculate or preprocess tha good suffix rule heuristic
void goodSuffixPreprocessing(string patt, int m, vector<int> &goodSuffix) 
{ 
    int k = 1; 
    goodSuffix[m-1] = 1; 
    int j = 2; 
    while (m-j >= 0) 
    { 
        if (patt[m-j] == patt[m-k]) 
        {  
            goodSuffix[m-j] = j-k; 
            k++; 
            j++;
        } 
        else 
        { 
            if (k != 1) 
            { 
                k = goodSuffix[m-k+1]; 
            } 
            else 
            { 
                goodSuffix[m-j] = j; 
                j++; 
            } 
        } 
    } 
}

//function to find tha pattern in text
void boyerMoore(string text, string patt) 
{  
    int m = patt.size();  
    int n = text.size();  

    //do good suffix preprocessing
    vector<int> goodSuffix(m);
    goodSuffixPreprocessing(patt, m, goodSuffix);
    //do bad character rule preprocessing
    vector<int> badChar(charCount, -1);
    badCharPreprocessing(patt, m, badChar);
  

    int i = m-1;
    int j = m-1;
    int k = i;
    //using both heuristics finding the pattern in the text
    while(i < n) 
    {
        if(patt[j]==text[i]) 
        {
            if(j==0)//pattern found 
            {
                cout << "patt found at " << i << endl;
                i += (i + m < n)? m-badChar[text[i + m]] : 1;  
            } 
            else 
            {
                i--;
                j--;
            }
        } 
        else //do necessary shifting acc to bad char and good suffix
        {
            i = max(i+m-min(j,1+badChar[text[i]]), goodSuffix[j] + k);
            j = m-1;
            k = i;
        }
    } 
}  

int main() 
{  
    string text,patt;
    cout<<"\t______Welcome to Boyer Moore Pattern Matching______\n";
    
    cout<<"\nEnter Text\t";
    getline(cin,text);
    
    cout<<"\nEnter Pattern\t";
    cin>>patt;
    
    boyerMoore(text, patt);
    
    return 0;  
}  