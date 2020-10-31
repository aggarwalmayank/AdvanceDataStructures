#include <bits/stdc++.h>
using namespace std;

int size;//size of ist level table 

//function to find index to hash in first level
int hashOne(int data)
{
    return data%size;
}
//function to initially init all a vectors for each hashtable in level 2
vector<vector<int>> initAllA(int m,vector<vector<int>> &a)
{
    for(int i=0;i<size;i++)
        for(int j=0;j<a[i].size();j++)
            a[i][j]=rand() % m;
    return a;
}
//function to init a vector all values will be between 0 to level 2 table size -1
vector<vector<int>> initA(vector<vector<int>> &a,int id1) 
{
    for(int i = 0; i < 10 ; i++)
        a[id1][i] = rand() % a[id1].size();
    return a;
}

//function to expand hashtable
void expandTable(vector<int> &HT,int length) 
{
    HT.resize(length*length,INT_MIN);
}
// function to shrink table if needed during deletion
void shrinkTable(vector<int> &HT)
{
    HT.resize(HT.size()/2);
}
//function to calculate index where to map 
int getIndex(int data, int m,vector<int> a) 
{
    int idx = 0;
    int masking = 1;
    for(int i=0;i<10;i++) 
    {
        if(masking&data) //using bitwise operator otherwise i would have to convert data to 1st binary and then multipy with corresponding a and sum
            idx=idx+a[i];
        masking=masking<<1;
    }
    return idx%m;
}
//function to rehash table if expansion shrinking or collision
void rehashing(vector<vector<int>> &HT,vector<int> temp,int id1,vector<vector<int>> &a) 
{
    fill(HT[id1].begin(),HT[id1].end(),INT_MIN);//clearing Hashtable by setting all to INT_MIN

    for(int i=0;i<temp.size(); i++) 
    {
        int index = getIndex(temp[i],HT[id1].size(),a[id1]);
        if(HT[id1][index] != INT_MIN)//which means already key is present at index (collision) 
        {
            a=initA(a,id1);//so new hash func and do rehashing again
            rehashing(HT, temp,id1,a);
            break;
        }
        HT[id1][index] = temp[i];
    }
}

//function to add data to hashtable
void add(vector<vector<int>> &HT, int data,vector<int> &mappedCount,vector<vector<int>> &a) 
{
    int id1=hashOne(data);//get index in 1st table
    
    if(mappedCount[id1]==0)//if initially no key mapped add directly to 0 pos
    {
        HT[id1][0]=data;
        mappedCount[id1]++;//increment no of keys mapped count
        cout << "Added successfully" << endl;
        return;
    }
    int idx=getIndex(data, HT[id1].size(),a[id1]);//get index in 2nd table
    
    if(HT[id1][idx]!=INT_MIN)//if collision
    {
        expandTable(HT[id1],HT[id1].size()+1);// expand table 2 size eual to square of no of collision in ith slot
        a=initA(a,id1);
        vector<int> temp;
        for(int i=0;i<HT[id1].size();i++) 
        //temporarily storing all keys which are mapped in temp array to rehash them again
        {
            if(HT[id1][i]!=INT_MIN)
                temp.push_back(HT[id1][i]);
        }
        temp.push_back(data);
        rehashing(HT,temp,id1,a);//now do rehashing
    }
    else
        HT[id1][idx]=data;

    mappedCount[id1]++;//increment no of keys mapped count
    cout << "Added successfully" << endl;
    return;

}
// function to search an key in table
pair<int,int> search(vector<vector<int>> HT, int data,vector<vector<int>> a) 
{
    int id1=hashOne(data);//get 1st index in table 1
    int index = getIndex(data, HT[id1].size(),a[id1]);//get 2nd index in 2nd table

    if(HT[id1][index] == data) 
        return make_pair(id1,index); //return pair of index in 1st and 2nd table

    cout << "\nno value exist" << endl;
    return make_pair(-1,-1);
}
//function to delete key from hash table
void remove(vector<vector<int>> &HT, int value,vector<vector<int>> &a,vector<int> mappedCount) 
{

    pair<int,int> p = search(HT, value,a);//find index
    if(HT[p.first].size()==1) //if only one element normally change to INTMIN and recude mapped count
    {
        HT[p.first][0]=INT_MIN;
        mappedCount[p.first]--;
        return;
    }
    if(p.first != -1) //if found
    {
        HT[p.first][p.second] = INT_MIN;//set to intmin
        mappedCount[p.first]--;//decrement size of mapped count
        if(mappedCount[p.first]== HT[p.first].size()/4) //if m=m/4 then themporarily store in temp vector and shrink table then rehashing
        {
            vector<int> temp;

            for(int i = 0; i < HT[p.first].size(); i++) //temporarily store in temp array and then rehash after shrinking
            {
                if(HT[p.first][i] != INT_MIN) 
                {
                    temp.push_back(HT[p.first][i]);
                    HT[p.first][i] = INT_MIN;
                }    
            }

            shrinkTable(HT[p.first]);
            rehashing(HT,temp,p.first,a);
        }
        cout << "\ndeleted successfully" << endl;
        return;
    }

    return;
}

//function to print hash table
void print(vector<vector<int>> HT)
{
    for(int i=0;i<HT.size();i++) 
    { 
        cout<<i<<"--|\n";
        cout<<"   |_\n";
        for(int j=0;j<HT[i].size();j++)
        {
            if (HT[i][j]!=INT_MIN) 
                cout<<"\t"<<j<<" --> "<<HT[i][j]<<endl; 
            else
                cout<<"\t"<<j<<endl;
        } 
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

    cout<<"\n\n\t\t-^-^-^-^-^-Welcome to Perfect Hashing-^-^-^-^-^-\n\n";
    cout<<"Enter first level hash Table size\t";
    cin>>size;// input of hash table size from user
    vector<vector<int>> HT(size,vector<int> (1, INT_MIN));
    vector<int> mappedCount(size,0);//vector to keep count of no of keys mapped for each 2nd level table
    vector<vector<int>> a(size,vector<int> (10, 0));//hash func is a.k mod m so vector to store digits of a fixing its size to be 10 and for every level i am using new hashfunc
    int r = 1;
    a=initAllA(1,a);
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
                        add(HT,element,mappedCount,a);
                        break;
                    }
            case 2: {//REMOVING
                        int element=getElement();
                        remove(HT,element,a,mappedCount);
                        break;
                    }
            case 3: {//PRINTING
                        print(HT);
                        break;
                    }
            case 4: {//SEARCHING    
                        int element=getElement();
                        if(search(HT,element,a).first!=-1)
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
