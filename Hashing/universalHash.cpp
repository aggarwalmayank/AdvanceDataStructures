#include <bits/stdc++.h>
using namespace std;

int currSize; //storing no of elements mapped
vector<int> a(10,0);//hash func is a.k mod m so vector to store digits of a fixing its size to be 10 

//function to init a vector whole values will be between 0 to m-1
void initA(int m) 
{
    for(int i = 0; i < 10 ; i++)
        a[i] = rand() % m;
}

//function to expand hashtable
void expandTable(vector<int> &HT) 
{
    HT.resize(2 * HT.size(),INT_MIN);
}
//function to shrink table if needed during deletion
void shrinkTable(vector<int> &HT)
{
    HT.resize(HT.size()/2);
}
//function to calculate index where to map 
int getIndex(int data, int m) 
{
    int idx = 0;
    int masking = 1;
    for(int i=0;i<6;i++) 
    {
        if(masking&data) //using bitwise operator otherwise i would have to convert data to 1st binary and then multipy with corresponding a and sum
            idx=idx+a[i];
        masking=masking<<1;
    }
    return idx%m;
}
//function to rehash table if expansion shrinking or collision
void rehashing(vector<int> &HT,vector<int> temp) 
{
    fill(HT.begin(),HT.end(),INT_MIN);//clearing Hashtable by setting all to INT_MIN
    // for(int i=0;i<HT.size();i++)
    //     HT[i] = INT_MIN;

    for(int i=0;i<temp.size(); i++) 
    {
        int index = getIndex(temp[i],HT.size());
        if(HT[index] != INT_MIN)//which means already key is present at index (collision) 
        {
            initA(HT.size());//so new hash func and do rehashing again
            rehashing(HT, temp);
            break;
        }
        HT[index] = temp[i];
    }
}
//function to add data to hashtable
void add(vector<int> &HT, int data) {
    if(currSize==0) //if hash table empty att to 0 index default case 
    {
        HT[0]=data;
        currSize++;
        return;
    }
    int flag = 0;
    if(HT.size()==currSize) //if hashtable is full so do expansion
    {
        expandTable(HT);
        flag = 1;
    }

    int idx=getIndex(data, HT.size());
    if(flag==1 || HT[idx]!=INT_MIN) //if expansion done or collision
    {
        initA(HT.size());//select new hash function
        vector<int> temp;
        for(int i=0;i<HT.size();i++) 
        //temporarily storing all keys which are mapped in temp array to rehash them again
        {
            if(HT[i]!=INT_MIN)
                temp.push_back(HT[i]);
        }
        temp.push_back(data);
        rehashing(HT, temp);
    } 
    else
        HT[idx]=data;

    currSize++;//increment no of keys mapped count
    cout << "Added successfully" << endl;
    return;
}
//function to search an key in table
int search(vector<int> HT, int data) {
    int index = getIndex(data, HT.size());

    if(HT[index] == data) 
        return index;

    cout << "\nno value exist" << endl;
    return -1;
}
//function to delete key from hash table
void remove(vector<int> &HT, int value) 
{
    if(HT.size()==1)
    {
        HT[0]=INT_MIN;
        currSize--;
        return;
    }
    int index = search(HT, value);//find index
    if(index != -1) //if found
    {
        HT[index] = INT_MIN;//set to intmin
        currSize--;//decrement size of mapped count
        if(currSize == HT.size()/4) //if m=m/4 then themporarily store in temp vector and shrink table then rehashing
        {
            vector<int> temp;

            for(int i = 0; i < HT.size(); i++) 
            {
                if(HT[i] != INT_MIN) 
                {
                    temp.push_back(HT[i]);
                    HT[i] = INT_MIN;
                }    
            }

            shrinkTable(HT);
            rehashing(HT, temp);
        }
        cout << "\ndeleted successfully" << endl;
        return;
    }

    return;
}

//function to print hash table
void print(vector<int> HT)
{
    for(int i=0;i<HT.size();i++) 
    { 
        if (HT[i]!=INT_MIN) 
            cout <<i<<" --> "<<HT[i]<<endl; 
        else
            cout<<i<<endl; 
    } 
}
//function to get input from user
int getElement(void)
{
    int ele;
    cout<<"Enter a number: ";
    cin>>ele;
    return ele;
}
// Main function
int main() {

    cout<<"\n\n\t\t-^-^-^-^-^-Welcome to Universal Hashing-^-^-^-^-^-\n\n";
    
    vector<int> HT(1, INT_MIN);
    int r = 1;
    initA(1);
    while(1)
    {
        cout<<"\n\t-----------------------";
        cout<<"\n\t\tMENU\n\n\t1. add key\n\t2. Delete key \n\t3. Print Hash table\n\t4. Search key\n\t5. Exit\n";
        cout<<"\t-----------------------\n";
        cout<<"Select any choice from menu\t";
        int choice;
        cin>>choice;
        cout<<endl<<endl;
        switch(choice)
        {
            case 1: {//ADDING
                        int element=getElement();
                        add(HT,element);
                        break;
                    }
            case 2: {//REMOVING
                        int element=getElement();
                        remove(HT,element);
                        break;
                    }
            case 3: {//PRINTING
                        print(HT);
                        break;
                    }
            case 4: {//SEARCHING    
                        int element=getElement();
                        if(search(HT,element)!=-1)
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
