#include <bits/stdc++.h>
using namespace std;

//Structure if the Node
struct Node 
{
    int *keys; // dunamic array to store keys
    Node **P; // dynamic pointer array to store childrens
    int keysCount;// count of the keys in a node
    bool leaf;// to check is node is leaf or not
};

int deg=0;//declaring variable holding the degree/order of tree globally

void deleteKey(Node* root, int predecessor);

// Function to create a new node
Node* createNode(bool leafstatus) 
{
    Node* newNode = new Node();
	newNode -> keys = new int[2*deg - 1]; //allocationg size to keys array
    newNode -> P = new Node *[2*deg]; // allocating size to array of pointer to children
    newNode -> keysCount = 0; // initial key count is 0
    newNode -> leaf = leafstatus; //assigning status to the leaf as true if leaf node and false if not a leaf node
    return newNode;
}

//function to print inorder traversal
void inorder(Node* root) 
{
    int idx; 
    for (idx = 0; idx < root -> keysCount; idx++)
    { 
        if (root -> leaf == false)
            inorder(root -> P[idx]);//if node is not a leaf node then recursively calling to its child
      
        cout << root -> keys[idx] << " "; //if not a leaf node then printing all elements of that node 
    } 
  
    if (root -> leaf == false)//reecursively going to the right tree
        inorder(root -> P[idx]);
}

//function to print preorder traversal
void preorder(Node* root) 
{
    int idx; 
    for (idx = 0; idx < root -> keysCount; idx++)
    { 
        cout << root -> keys[idx] << " "; // print element at node which commes in tha path 1st
        if (root -> leaf == false) //if that node is leaf node traverse to its child
            preorder(root -> P[idx]);
    } 
  
    if (root -> leaf == false) 
        preorder(root -> P[idx]);
}

void doSplitting(int pos, Node* nodeToSplit, Node* parent) 
{
    Node* splitNode = createNode(nodeToSplit -> leaf);//creating new node which will store the deg-1 keys

    splitNode -> keysCount = deg - 1; //assigning keycount of splitnode as deg-1

    for(int i = 0; i < deg - 1; i++)// assigning 1st deg-1 keys of node to be split to the new created node
        splitNode -> keys[i] = nodeToSplit -> keys[i + deg];

    if(nodeToSplit -> leaf == false)//if node to be splitted is not a leaf node than copying las deg-1 keys from node to split ot splitnode
        for(int i = 0; i < deg ; i++)
            splitNode -> P[i] = nodeToSplit -> P[i + deg];


    nodeToSplit -> keysCount = deg - 1;// decrementing keycount in nodetosplit node

    //ponter shifting to create space for new node as split node will bw child of parent 
    for (int i = parent -> keysCount; i >= pos + 1; i--)
        parent -> P[i+1] = parent -> P[i]; 
 
    parent -> P[pos+ 1] = splitNode; // linking new node to the parent
  
  	//moving all greater keys 1 space ahead
    for (int i = parent -> keysCount - 1; i >= pos; i--) 
        parent -> keys[i+1] = parent -> keys[i]; 
   

    parent -> keys[pos] = nodeToSplit -> keys[deg-1]; //copying middle key
    parent -> keysCount = parent -> keysCount + 1;//incrementing parent key count
}

void add(Node* root, int ele) 
{

    int idx = root->keysCount - 1;

    //if root is leaf node
    if(root->leaf == true) 
    {
    	//finding position to add value
        while(idx >= 0 && ele < root->keys[idx]) 
        {
            root->keys[idx + 1] = root->keys[idx];
            idx--;
        }

        root->keys[idx + 1] = ele;// adding element to position idx+1
        root->keysCount = root->keysCount + 1;//incerement keycount after adding a key
    } 
    else //if root is not leaf node
    {
    	//finding suitable position
        while(idx >= 0 && ele < root->keys[idx])
            idx--;

        //if chils at position idx+1 have keycount 2*deg-1 (max count)
        if(root->P[idx + 1]->keysCount == (2*deg - 1)) 
        {
        	//perform splitting
            doSplitting(idx + 1, root->P[idx + 1], root);

            if(ele > root->keys[idx + 1])
                idx++;
        }
        //recursively call add at idx+1 chils of root
        add(root->P[idx + 1], ele);
    }
    return;
}

// function to inser a element to tree
void insert(Node* &root, int ele) 
{
    if(root == NULL)// if tree doesn't exist root=null 
    {
        root = createNode(true);// createnode
        root -> keys[0] = ele;// insert element to to node
        root -> keysCount = 1;//increment key count from 0 to 1
    } 
    else 
    {
        if(root -> keysCount == (2*deg - 1)) // if root was not null and root node is full
        {
            Node* newNode = createNode(false);// create node later which will be our new root
            newNode->P[0] = root;// making old root as its child
            doSplitting(0, root, newNode);//splitting root node

            if(ele<newNode->keys[0])// if element is less than the newNode 
                add(newNode-> P[0],ele);
            else
                add(newNode-> P[1],ele);

            root = newNode;
        } 
        else// if root was not exhausted
            add(root,ele);
    }
}

//function to borrow from previous child
void borrowFromPrevious(Node* root, int index) 
{ 
    Node* child = root -> P[index]; 
    Node* sibling= root -> P[index - 1]; 
  
    for (int i = child -> keysCount -1; i >= 0; i--) {
        child -> keys[i+1] = child -> keys[i];
    }  
  
  	// if not leaf then move pointers 1 step ahead
    if (child -> leaf == false) { 
        for(int i = child -> keysCount; i >= 0; i--) {
            child -> P[i+1] = child->P[i];
        }             
    } 
  
    child -> keys[0] = root -> keys[index-1]; //changing 1st key to idx-1 key of current node
  
    if(child -> leaf == false) {
        child -> P[0] = sibling-> P[sibling -> keysCount];
    } 
  
  	// Move the key from the sibling to the parent 
    root -> keys[index-1] = sibling -> keys[sibling -> keysCount - 1]; 
  
    child -> keysCount = child -> keysCount + 1; //incrementing child key count and decrementing sibling key count
    sibling-> keysCount = sibling -> keysCount - 1; 
  
    return; 
}

//function to borrow from next child
void borrowFromNext(Node* root, int index) 
{ 
    Node* child = root -> P[index]; 
    Node* sibling = root -> P[index + 1]; 
  
    child -> keys[child -> keysCount] = root -> keys[index]; 
   
   	//sibling first child is inserted as the last child
    if(child -> leaf == false) { 
        child -> P[child -> keysCount + 1] = sibling -> P[0]; 
    }

    root -> keys[index] = sibling -> keys[0]; 
  
  	//move all keys 1 step ahead
    for (int i = 1; i < sibling -> keysCount; i++) {
        sibling->keys[i-1] = sibling->keys[i]; 
    }     
  	//moving child pointed behind
    if (sibling -> leaf == false) { 
        for(int i=1; i <= sibling -> keysCount; i++) {
            sibling -> P[i-1] = sibling -> P[i];
        }          
    } 
  
    child -> keysCount = child -> keysCount + 1; 
    sibling-> keysCount = sibling -> keysCount - 1; 
  
    return; 
}
//function to merge root->P[idx] with root->P[idx+1]
void merge(Node* root, int index) 
{ 
    Node* child = root -> P[index]; 
    Node* sibling = root -> P[index + 1]; 
  
    child->keys[deg - 1] = root -> keys[index];// inserting key from root to child
  
  	//copying key from index +1 to index at end
    for (int i = 0; i < sibling -> keysCount; i++)
        child -> keys[i+deg] = sibling -> keys[i];
  
	//copying child pointer  
    if (child -> leaf == false)
        for(int i=0; i <= sibling -> keysCount; i++)
            child -> P[i + deg] = sibling -> P[i];
    //moving all keys after idx+1
    for (int i = index + 1; i < root -> keysCount; i++)
        root -> keys[i-1] = root -> keys[i];
    
    //moving child pointers after idx+1
    for (int i = index + 2; i <= root -> keysCount; i++)
        root -> P[i-1] = root -> P[i];
  
    child -> keysCount = child -> keysCount + sibling -> keysCount + 1;//updating key count 
    root -> keysCount = root -> keysCount - 1; 
   
    delete sibling; //deleting sibling node to free up memory
    return; 
} 

//function to fill the nodes having keys less than degree 
void fill(Node* root, int index) 
{
	//if prev child has more keys borrowing from that child
    if(index != 0 && root -> P[index - 1] -> keysCount >= deg) 
        borrowFromPrevious(root, index);
    //if next child has more keys borrowing from that child
    else if(index != root -> keysCount && root -> P[index + 1] -> keysCount >= deg) 
        borrowFromNext(root, index);
    else 	//merging with sibling
    {
        if(index != root -> keysCount)// if not last child merge with next sibling
            merge(root, index);
        else //otherwise merge with prev sibling
            merge(root, index - 1);
    }

    return;
}


//function to get inorder predecessor
int inorderPredecessor(Node* root, int index) 
{
    Node* pred = root -> P[index];

    while (pred -> leaf == false)
        pred = pred -> P[pred -> keysCount];
    return pred->keys[pred->keysCount - 1];
}
//function to get inorder successor
int inorderSuccessor(Node* root, int index)
{ 
    Node* succ = root -> P[index + 1]; 
    while (succ -> leaf == false) 
        succ = succ -> P[0]; 
    return succ -> keys[0]; 
}

//function to delete key from non leaf node
void deleteFromNonLeaf(Node* root, int index) 
{ 

    int key = root -> keys[index]; 

    if (root -> P[index] -> keysCount >= deg)//if the precedesor child of root have atleat deg keys
    { 
        int pred = inorderPredecessor(root, index); //replaceing key by predecosor and deleting predecesor
        root -> keys[index] = pred; 
        deleteKey(root -> P[index], pred); 
    } 
    else if (root -> P[index + 1] -> keysCount >= deg)//if in above alteast deg keys were not so checking for index+1 
    {
        int succ = inorderSuccessor(root, index); 
        root -> keys[index] = succ; //replace by succ and recursivley deleting successor
        deleteKey(root -> P[index + 1], succ);
    } 
    else //both having less than deg keys 	
    { 
        merge(root, index); //merging and deleting
        deleteKey(root -> P[index], key); 
    } 

    return; 
} 

//search key in tree
Node *search(int key, Node *root)
{
    int i;
    for (i = 0; i < root->keysCount && key < root->keys[i]; i++)
        ;
    if (key == root->keys[i])
        return root;
    else if (root->leaf == false)
        return search(key, root->P[i]);
    else
        return NULL;
}

//function to search a key in node
int searchInNode(Node* root, int key) 
{
    int index = 0;
    while(index < root -> keysCount && key > root -> keys[index])
        index ++;
    return index;
}


//utility func to delete key from node
void deleteKey(Node* root, int key) 
{
	// searching index of the key
    int index = searchInNode(root, key);


    if(index < root -> keysCount && root -> keys[index] == key) 
    {
        if(root -> leaf==true)//if root is leaf node 
            // deleteFromLeaf(root, index);//delete from leaf node
        {
        	//shifting keys to left side
        	for (int i = index + 1; i < root -> keysCount; i++)
	    	    root -> keys[i-1] = root -> keys[i];
	    	
	    	root -> keysCount = root -> keysCount - 1;//decrementing key count 
        }
        else
            deleteFromNonLeaf(root, index);//delete from non leaf

    } 
    else 
    {
        if(root -> leaf==true)//if root is leaf 
        {
            cout<<"\nNo key present in tree\n"; 
            return;
        }
        bool lastChild=false;
        if(index==root->keysCount)//if index is equal to key count in root
        {
        	lastChild=true;
        }

        if(root -> P[index] -> keysCount < deg)
            fill(root, index);

        if (lastChild && index > root -> keysCount)
            deleteKey(root -> P[index - 1], key);
        else
            deleteKey(root -> P[index], key);
    }

    return;
}

//function to remove a element from tree
void remove(Node* &root, int ele) 
{
	//if root null element doeesn't exist in tree
    if (root == NULL) 
    { 
        cout<<"\nNo such key exist in tree\n"; 
        return; 
    }
    //calling delete function
    deleteKey(root, ele);


    if(root -> keysCount == 0) //no element in root
    {
        if(root -> leaf == true) //and root is leaf
            root = NULL; //then making tree as null
        else //making root as 1st child of root
        {
            Node* t = root;
            root = root -> P[0];
            delete t;
        }
    }

    return;
}

//function to get integer element from the user
int getElement(void)
{
    int ele;
    cout<<"Enter a number: ";
    cin>>ele;
    return ele;
}

int main() 
{
    cout<<"\n\tWelcome to B-Tree Program\n";

    Node* root = NULL;// declaring root for tree as null
    cout<<"\nEnter the order/degree of tree\t";
    cin>>deg;// taking degree of tree as input from user

    while(1)
    {
        cout<<"\n\t-----------------------";
        cout<<"\n\t\tMENU\n\n\t1. Insert\n\t2. Delete\n\t3. Inorder Traversal\n\t4. Preorder Traversal\n\t5. Search\n\t6. Exit\n";
        cout<<"\t-----------------------\n";
        cout<<"Select any choice from menu\t";
        int choice;
        cin>>choice;
        cout<<endl<<endl;
        switch(choice)// switch statement for choices
        {
            case 1: {// INSERTION
                        int element=getElement();
                        insert(root, element);
                        cout<<"\nInserted Successfully\n";
                        break;
                    }
            case 2: {//DELETION
                        int element=getElement();
                        remove(root, element);
                        cout<<"\nDeleted Successfully\n";
                        break;
                    }
            case 3: {// INORDER
                        if(root==NULL)
                            cout<<"\nNO TREE EXIST\n";
                        else
                        {
                            cout<<"\nINORDER TRAVERSAL\n";
                            inorder(root);
                            cout<<endl;
                        }
                        break;
                    }
            case 4: {//PREORDER
                        if(root==NULL)
                            cout<<"\nNO TREE EXIST\n";
                        else
                        {
                            cout<<"\nPREORDER TRAVERSAL\n";
                            preorder(root);
                            cout<<endl;
                        }
                        break;
                    }
            case 5: {//SEARCH
                        if(root==NULL)
                            cout<<"\nNO TREE EXIST\n";
                        else
                        {
                            int element=getElement();
                            if(search(element,root) != NULL) 
                                cout<<"\nFound\n";
                            else
                                cout<<"\nNot found\n";    

                        }
                        break;
                    }
            case 6: //EXIT
                    exit(1);
                    break;
            default: cout<<"Invalid Choice!!\n\n";
        }
    }
}
