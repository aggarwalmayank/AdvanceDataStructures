#include<bits/stdc++.h>
using namespace std;

//function to get input from user
int getElement(void)
{
    int ele;
    cout<<"Enter a number: ";
    cin>>ele;
    return ele;
}
//function to calculate hash value
int hashFunc(int data,int size)
{
	return data%size;
}
//function to add key in hashtable
void add(int data, vector<vector<int>> &HT)
{
	int key=hashFunc(data,HT.size());
	HT[key].push_back(data);
}
//function to search data in hashtable
bool search(int data,vector<vector<int>> HT)
{
	int key=hashFunc(data,HT.size());
	for(int i=0;i<HT[key].size();i++)
		if(data==HT[key][i])
			return true;
	return false;
}
//function to remove data from hash table
void remove(int data,vector<vector<int>> &HT)
{
	int i;
	int key=hashFunc(data,HT.size());
	for (auto i = HT[key].begin(); i != HT[key].end(); ++i) { 
		if (*i == data) { 
          	// cout<<*i<<" ";
			HT[key].erase(i); 
			i--; 
		} 
	}
}
//function to print hash table
void print(vector<vector<int>> HT)
{
	for(int i=0;i<HT.size();i++)
	{
		cout<<"Key="<<i<<"   ";
		for(int j=0;j<HT[i].size();j++)
			cout<<"-->"<<HT[i][j];
		cout<<endl;
	}
}
int main()
{
	cout<<"\n\n\t\t-^-^-^-^-^-Welcome to Uniform Hashing-^-^-^-^-^-\n\n";
	cout<<"Enter hash Table size\t";
	int size;
	cin>>size;// input of hash table size from user
	vector<vector<int>> HT(size); //declaring hashtable as dynamic 2d array using vectors
    while(1)
    {
        cout<<"\n\t-----------------------";
        cout<<"\n\t\tMENU\n\n\t1. Insert key\n\t2. Delete key \n\t3. Print Hash table\n\t4. Search key\n\t5. Exit\n";
        cout<<"\t-----------------------\n";
        cout<<"Select any choice from menu\t";
        int choice;
        cin>>choice;
        cout<<endl<<endl;
        switch(choice)
        {
            case 1: {//ADDING
                        int element=getElement();
                        add(element,HT);
                        break;
                    }
            case 2: {//REMOVING
                    	int element=getElement();
                        remove(element,HT);
                        break;
                    }
            case 3: {//PRINTING
            			print(HT);
                        break;
                	}
            case 4: {//SEARCHING	
		            	int element=getElement();
		            	if(search(element,HT)==true)
		            		cout<<"\nElement found\n";
		            	else
		            		cout<<"\nNo Element found\n";
                        break;
                	}
            case 5: exit(1);
                    break;
            default: cout<<"Invalid Choice!!\n\n";
        }
    }
}
