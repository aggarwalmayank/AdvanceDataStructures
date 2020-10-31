#include<bits/stdc++.h>
using namespace std;

class Node
{
    public:
        int data;
        Node *left;
        Node *right;
        int height;
};
Node* createNewNode(int val)
{
    Node* node = new Node();
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
int getHeight(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}
int getHeightFactor(Node *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left)-getHeight(node->right);
}

Node* rotateLeft(Node *gp)
{
    Node *target = gp->right;
    Node *targetLeft = target->left;
    target->left = gp;
    gp->right = targetLeft;

    int gpLeftHeight= (gp->left!=NULL)?gp->left->height:0;
    int gpRightHeight= (gp->right!=NULL)?gp->right->height:0;
    gp->height = max(gpRightHeight,gpLeftHeight) + 1;

    int targetLeftHeight= (target->left!=NULL)?target->left->height:0;
    int targetRightHeight= (target->right!=NULL)?target->right->height:0;
    target->height = max(targetRightHeight,targetRightHeight) + 1;

    return target;
}
Node* rotateRight(Node *gp)
{
    Node *target = gp->left;
    Node *targetRight = target->right;
    target->right = gp;
    gp->left = targetRight;

    int gpLeftHeight= (gp->left!=NULL)?gp->left->height:0;
    int gpRightHeight= (gp->right!=NULL)?gp->right->height:0;
    gp->height = max(gpRightHeight,gpLeftHeight) + 1;

    int targetLeftHeight= (target->left!=NULL)?target->left->height:0;
    int targetRightHeight= (target->right!=NULL)?target->right->height:0;
    target->height = max(targetRightHeight,targetRightHeight) + 1;

    return target;
}
Node* insert(int val, Node* node)
{
    if(node==NULL)
        return createNewNode(val);
    else if(val>node->data)
        node->right=insert(val,node->right);
    else if(val<node->data)
        node->left=insert(val,node->left);

    // int leftHeight= (node->left!=NULL)?node->left->height:0;
    // int rightHeight= (node->right!=NULL)?node->right->height:0;

    node->height=1+max(getHeight(node->left),getHeight(node->right));

    int heightFactor= getHeightFactor(node);

    if (heightFactor > 1 && val < node->left->data)
        return rotateRight(node);
    if (heightFactor < -1 && val > node->right->data)
        return rotateLeft(node);
    if (heightFactor > 1 && val > node->left->data)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (heightFactor < -1 && val < node->right->data)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}
Node* remove(int val, Node* node)
{
    if(node==NULL)
        return node;
    if(val<node->data)
        node->left=remove(val,node->left);
    else if(val>node->data)
        node->right=remove(val,node->right);
    else
    {
        if(node->left==NULL)
        {
            Node* temp=node->right;
            free(node);
            return temp;
        }
        else if(node->right==NULL)
        {
            Node* temp=node->left;
            free(node);
            return temp;
        }

        Node* inorderSucc = node;
        while (inorderSucc && inorderSucc->left != NULL)
            inorderSucc = inorderSucc->left;

        node->data=inorderSucc->data;
        node->right=remove(inorderSucc->data,node->right);
    }
    if(node==NULL)
        return NULL;

    // int leftHeight= (node->left!=NULL)?node->left->height:0;
    // int rightHeight= (node->right!=NULL)?node->right->height:0;

    node->height=1+max(getHeight(node->left),getHeight(node->right));

    // int heightFactor= (node!=NULL)?leftHeight-rightHeight:0;
    int heightFactor=getHeightFactor(node);

    if (heightFactor > 1)
    {
        // int leftHeight= (node->left!=NULL)?node->left->height:0;
        // int rightHeight= (node->right!=NULL)?node->right->height:0;
        // int heightFac= (node->left!=NULL)?leftHeight-rightHeight:0;

        if(getHeightFactor(node->left)>= 0)
        {
            return rotateRight(node);
        }
        else
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (heightFactor < -1)
    {
        // int leftHeight= (node->left!=NULL)?node->left->height:0;
        // int rightHeight= (node->right!=NULL)?node->right->height:0;
        // int heightFac= (node!=NULL)?leftHeight-rightHeight:0;

        if(getHeightFactor(node->right) <= 0)
        {
            return rotateLeft(node);
        }
        else
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;

}
int getElement(void)
{
    int ele;
    cout<<"Enter a number: ";
    cin>>ele;
    return ele;
}
void inorder(Node* root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
void preorder(Node* root)
{
    if(root==NULL)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
Node* search(Node* node,int val)
{
	if (node == NULL || node->data == val) 
       return node;
    if (node->data < val) 
       return search(node->right, val);
    return search(node->left, val); 
}
int main()
{
    cout<<"\n\tWelcome to AVL Tree Program\n";

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
        switch(choice)
        {
            case 1: {
                        int element=getElement();
                        root=insert(element,root);
                        break;
                    }
            case 2: {
                        if(root==NULL)
                            cout<<"\nNO TREE EXIST\n";
                        else
                        {
                        	int element=getElement();
                            root=remove(element,root);
                        }
                        break;
                    }
            case 3: {	if(root==NULL)
                        	cout<<"\nNO TREE EXIST\n";
                        else
                        {
		            		cout<<"\nINORDER TRAVERSAL\n";
		                    inorder(root);
                    		cout<<endl;
                        }
                        break;
                	}
            case 4: {	if(root==NULL)
                        	cout<<"\nNO TREE EXIST\n";
                        else
                        {
		            		cout<<"\nPREORDER TRAVERSAL\n";
                   			preorder(root);
                    		cout<<endl;
                        }
                        break;
                	}
            case 5: {
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
            case 6: exit(1);
                    break;
            default: cout<<"Invalid Choice!!\n\n";
        }
    }
}
