#include<bits/stdc++.h>
using namespace std;
//Class defining structure of a node
class Node
{
    public:
        int data; //to store node value
        Node *left;//to store node left child address
        Node *right;//to store node right child address
        Node *parent;//to store node parent address
        char color;//to store color of node
};

//Function to create new node which take argument as data value of node
Node* createNewNode(int val)
{
    Node* node = new Node();
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = 'r';  //red color=r black color =b by default red color as whenever node is added its color is red
    return node;
}

//function to perform left rotation
Node* rotateLeft(Node* root,Node *node)
{
    Node *child=node->right;
    node->right = child->left;
    if (node->right != NULL)
        node->right->parent = node;
    child->parent = node->parent;
    if(node->parent==NULL)
        root=child;
    else
    {
        if(node==node->parent->left)
            node->parent->left=child;
        else
            node->parent->right=child;
    }
    child->left=node;
    node->parent=child;
    return root;
}

//function to perform right rotation
Node* rotateRight(Node* root,Node *node)
{
    Node* child = node->left;
    node->left=child->right;
    if(node->left!=NULL)
        node->left->parent=node;
    child->parent=node->parent;
    if(node->parent==NULL)
        root=child;
    else
    {
        if(node==node->parent->left)
            node->parent->left=child;
        else
            node->parent->right=child;
    }
    child->right=node;
    node->parent=child;
    return root;
}

//Function to perform balancing after insertion
Node* doInsertBalancing(Node* newnode, Node* root)
{
    Node* parent = NULL;
    Node* grandParent = NULL;
    while( newnode != root && newnode->color != 'b' && newnode->parent->color == 'r')//checking if there is still red-red conflict
    {
        parent = newnode->parent;
        grandParent = newnode->parent->parent;

        //Parent of newnode is left child of grand parent
        if (parent == grandParent->left)
        {
            Node* uncle = grandParent->right;
            //   if sibling of parent of newnode is also red Only recoloring required and check again
            if (uncle != NULL && uncle->color == 'r')
            {
                grandParent->color = 'r';
                parent->color = 'b';
                uncle->color = 'b';
                newnode = grandParent;
            }

            else
            {
                //   if newnode is right child of its parent left rotation required on parent
                if (newnode == parent->right) //if this condition is true then we will have LR case else LL case
                {
                    root=rotateLeft(root, parent);
                    newnode = parent;
                    parent = newnode->parent;
                }
                //newnode is left child of its parent right rotation required on Grandparent
                root=rotateRight(root, grandParent);
                swap(parent->color, grandParent->color);
                newnode = parent;
            }
        }


          // parent of newnode is right child of grandparent
        else
        {
            Node *uncle = grandParent->left;
            //The sibling of parent of newnode is also red so only recoloring required and check again
            if ((uncle != NULL) && (uncle->color == 'r'))
            {
                grandParent->color = 'r';
                parent->color = 'b';
                uncle->color = 'b';
                newnode = grandParent;
            }
            else
            {
                //   if newnode is left child of its parent right rotation required on parent
                if (newnode == parent->left)//if this condition is true then we will have RL case else RR case
                {
                    root=rotateRight(root, parent);
                    newnode = parent;
                    parent = newnode->parent;
                }

                //newnode is right child of its parent left rotation required on Grandparent
                root=rotateLeft(root, grandParent);
                swap(parent->color, grandParent->color);
                newnode = parent;
            }
        }
    }
    root->color = 'b'; //root is always black
    return root;
}

//Function to insert a node in tree
Node* insert(int val, Node* root)
{
    Node* newnode=createNewNode(val); // function call to create new node
    if(root==NULL) //if root is null assign new node as root
    {
        root=newnode;
        root->parent=NULL;
    }
    else    // else finding right position (whether in left subtree of right subtree ) to insert new node
    {
        Node* parent=NULL, *current=root;
        while(current!=NULL)
        {
            parent=current;
            if(current->data < newnode->data)
                current=current->right;
            else
                current=current->left;
        }
        //now newnode will be child of the parent pointer
        newnode->parent=parent;
        if(parent->data < newnode->data)
            parent->right=newnode;
        else
            parent->left=newnode;
    }
    //after normal BST insertion calling this function to make tree balance accprding to properties
    return doInsertBalancing(newnode,root);
}

//Function to search a node in tree returns the corresponding node
Node* search(Node* root, int val)
{
    if (root == NULL || root->data == val)
       return root;
    if (root->data < val)// searching in right subtree
       return search(root->right, val);
   return search(root->left, val);//searching in left subtree
}

//Function to find inorder successor
Node* successor(Node *node) {
    Node *succ = node;
    while (succ->left != NULL)
      succ = succ->left;
    return succ;
}

//Function to balance doublr black conditions
Node* balanceDoubleBlack(Node *x,Node* root)
{
    Node* sibling;
    if(x==root)
        return root;

    Node* parent=x->parent;

    if (x->parent == NULL)
        sibling=NULL;
    else if (x==x->parent->left)
        sibling= x->parent->right;
    else
        sibling= x->parent->left;

    if(!sibling) //there is no sibling to double black have to pushed
        root=balanceDoubleBlack(parent,root);
    else
    {
        if(sibling->color=='r')//red sibling so
        {
            parent->color='r';
            sibling->color='b';
            if(sibling==sibling->parent->left)
                root=rotateRight(root,parent);// left case
            else
                root=rotateLeft(root,parent);
            root=balanceDoubleBlack(x,root);// right  case
        }
        else//black sibling
        {
        	//sibling has atleast one red child
            if((sibling->left != NULL && sibling->left->color == 'r') || (sibling->right != NULL && sibling->right->color == 'r'))
            {
                if(sibling->left!=NULL && sibling->left->color=='r')
                {
                    if(sibling==sibling->parent->left)//left left case
                    {
                        sibling->left->color=sibling->color;
                        sibling->color=parent->color;
                        root=rotateRight(root,parent);
                    }
                    else// right left case so color swap then right rotation and then left
                    {
                        sibling->left->color=parent->color;
                        root=rotateRight(root,sibling);
                        root=rotateLeft(root,parent);
                    }
                }
                else
                {	// left right case so color swap then left rotation and then right
                    if(sibling==sibling->parent->left)// LR case
                    {
                        sibling->right->color=parent->color;
                        root=rotateLeft(root,sibling);
                        root=rotateRight(root,parent);
                    }
                    else // right right case so color swap and leftrotation
                    {
                        sibling->right->color=sibling->color;
                        sibling->color=parent->color;
                        root=rotateLeft(root,parent);
                    }
                }
                parent->color='b';
            }
            else//2 black children
            {
                sibling->color='r';
                if(parent->color=='b')
                    root=balanceDoubleBlack(parent,root);
                else
                    parent->color='b';
            }
        }
    }
    return root;
}
// Function to swap node data values
void swapping(Node *a, Node *b) {
	int temp;
	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

//Function for performing deletion
Node* remove(Node* node, Node* root)
{
    Node* toreplace;
    if (node->left != NULL and node->right != NULL)
        toreplace= successor(node->right);
    // when leaf node
    else if (node->left == NULL and node->right == NULL)
        toreplace= NULL;
    // when node to be deleted has single child
    else if (node->left != NULL)
        toreplace= node->left;
    else
        toreplace= node->right;

    bool bothblack=false;
    // checking whether the node to be deleted and its successor are of black color or not
    if(toreplace==NULL || toreplace->color=='b' && node->color=='b')
        bothblack=true;

    Node* parent=node->parent;

    if(toreplace==NULL)// node is leaf if to toreplace==null
    {
        if(node==root)
            root=NULL;
        else
        {
            if(bothblack)//since both are black and node was leaf so double black condition 
                root=balanceDoubleBlack(node,root);
            else//any of or both are red
            {
                Node* sibling;
                if (node->parent == NULL)
                    sibling=NULL;
                else if (node==node->parent->left)
                    sibling= node->parent->right;
                else
                    sibling= node->parent->left;

                if(sibling!=NULL) //if sibling is is not null making it red 
                    sibling->color='r';
            }
            if(node==node->parent->left)//checking of node is left child or not
            {
                parent->left=NULL;
            }
            else
                parent->right=NULL;
        }
        delete node; //deleting or free that node
        return root;//we are done here only when node is leaf node
    }
    if (node->left == NULL || node->right == NULL)//node has 1 child
    {
        if(node==root)
        {
        	// node is root so assigning value of toreplace to node and deleting toreplace
            node->data=toreplace->data;
            node->left=node->right=NULL;
            delete toreplace;
        }
        else
        {
            if(node==node->parent->left)
                parent->left=toreplace;
            else
                parent->right=toreplace;
            delete node;
            toreplace->parent=parent;
            if(bothblack)//again if both black then fixing double black condn
                root=balanceDoubleBlack(node,root);
            else
                toreplace->color='b';
        }
        return root;
    }
    swapping(node,toreplace);// swap the values of toreplace and node
    root=remove(toreplace,root);// recursively deletion toreplace node
    return root;
}

//Function to take an user input if integer
int getElement(void)
{
    int ele;
    cout<<"Enter a number: ";
    cin>>ele;
    return ele;
}

//function to print inorder traversal
void inorder(Node* root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    //will print color of the node along with value 
    cout<<"Value:- "<<root->data<<"   Color:- "<<root->color<<endl;
    inorder(root->right);
}
//function to print preorder traversal
void preorder(Node* root)
{
    if(root==NULL)
        return;
    //will print color of the node along with value
    cout<<"Value:- "<<root->data<<"   Color:- "<<root->color<<endl;
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    cout<<"\n\tWelcome to Red-Black Tree Program\n";

    Node* root=NULL;
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
                        root=insert(element,root);
                        cout<<"\nInserted Successfully\n";
                        break;
                    }
            case 2: {//DELETION
                        if(root==NULL)
                            cout<<"\nNO TREE EXIST\n";
                        else
                        {
                        	int element=getElement();
                            Node* ele=search(root,element);
                            if(ele)
                            {
                                 root=remove(ele,root);
                                cout<<"\nDeleted Successfully\n";
                            }
                            else
                                cout<<"\nNO SUCH ELEMENT\n";
                        }
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
                            Node* node=search(root,element);
                            if(node!=NULL)
                            	cout<<"\nElement Found in tree\n";
                            else
                            	cout<<"\nNo Element exist\n"

                            ;
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
