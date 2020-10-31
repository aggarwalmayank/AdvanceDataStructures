#include<bits/stdc++.h>
using namespace std;

int currentSize;// store size of hashtable
int prime; // prime number use in 2nd hash function

//function to get input from user
int getElement(void)
{
    int ele;
    cout<<"Enter a number: ";
    cin>>ele;
    return ele;
}
// function toh check if a number is prime or not
bool isPrime(int n){
    bool flg=true;
    for(int i=2; i<=n/2; i++) {
       if(n%i==0) {
          flg = false;
          break;
       }
    }
    return flg;
}
//function to calculate 1st hash value
int hashFunc1(int data,int size)
{
	return data%size;
}
//function to calculate 2nd hash value
int hashFunc2(int data,int size)
{
    
    return (prime-(data%prime));
}
//function to add key in hashtable
void add(int data, vector<int> &HT)
{
    //if hash table is full
    if(currentSize==HT.size())
    {
        cout<<"\nHash Table Already Full\n";
        return;
    }

    //calculate index from 1st hash function
	int idx=hashFunc1(data,HT.size());
    
    // if collision occurs 
    if (HT[idx]!= -1) 
    { 
        // getting index2 from second hash 
        int idx2 = hashFunc2(data,HT.size()); 
        int i = 1; 
        while(1) 
        { 
            // get newIndex 
            int newIdx = (idx+i*idx2) % HT.size(); 
             // if no collision occurs, store 
            // the key 
            if (HT[newIdx] == -1)
            { 
                HT[newIdx] = data; 
                break; 
            
            } 
            i++; 
        } 
    }  
   // if no collision occurs 
    else
        HT[idx] = data; 
    currentSize++; 
}
//function to search data in hashtable
int search(int data,vector<int> HT)
{
    //calculating index using both hash function
	int idx1 = hashFunc1(data,HT.size()); 
    int idx2 = hashFunc2(data,HT.size()); 
    int i = 0; 
    //if collison using i to get next index
    while (HT[(idx1 + i * idx2) % HT.size()] != data) 
    { 
        if (HT[(idx1 + i * idx2) % HT.size()] == -1)//not found 
            return -1;  
        i++; 
    } 
    return (idx1 + i * idx2) % HT.size(); //found at this index
}
//function to remove data from hash table
void remove(int data,vector<int> &HT)
{
	int idx=search(data,HT);//search index
    HT[idx]=-1;//initialize with -1 at that index
}
//function to print hash table
void print(vector<int> HT)
{
	for(int i=0;i<HT.size();i++) 
    { 
        if (HT[i]!=-1) 
            cout <<i<<" --> "<<HT[i]<<endl; 
        else
            cout<<i<<endl; 
    } 
}
//function to fix prime value < size of hash table for hash function
void fixPrime(int size)
{
    if(size==3)
        prime=2;
    else
        for(int i=size-1;i>=3;i--)
            if(isPrime(i))
            {
                prime=i;
                break;
            }
}
int main()
{
	cout<<"\n\n\t\t-^-^-^-^-^-Welcome to Double Hashing-^-^-^-^-^-\n\n";
	cout<<"Enter hash Table size\t";
	int size;
	cin>>size;// input of hash table size from user
	vector<int> HT(size,-1);// initializing all entry in hashtable with -1 

    fixPrime(size);//fixing prime

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
		            	if(search(element,HT)!=-1)
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
