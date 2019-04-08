#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node* left;
    struct node* right;
    int height;
}Node;

// function prototypes

int height(Node* p);
int max(int a,int b);
Node* makeNode(int key);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int getBalance(Node* n);
Node* insert(Node* root,int key);
void preOrder(Node* root);
Node* minValue(Node* root);
Node* delete(Node* root,int key);

int height(Node* p){

  if(p==NULL){
    return 0;
  }
  else
  {
    return p->height;
  }
}

int max(int a,int b){
  return (a>b)?a:b;
}

Node* makeNode(int key)
{
  Node* n=(Node*)malloc(sizeof(Node));
  n->data=key;
  n->left=NULL;
  n->right=NULL;
  n->height=1; // new node is added at last

  return n;
}

Node* rightRotate(Node* y){

    Node* x=y->left;
    Node* t=y->right;

    // rotation
    x->right=y;
    y->left=t;//x->right

    //height updation
    x->height=1+max(height(x->left),height(x->right));
    y->height=1+max(height(y->left),height(y->right));

    return x;

}

Node* leftRotate(Node* x){

    Node* y=x->right;
    Node* t=y->left;

    // rotation
    y->left=x;
    x->right=t;

    //height updation
    x->height=1+max(height(x->left),height(x->right));
    y->height=1+max(height(y->left),height(y->right));

    return y;

}

int getBalance(Node* n)
{
    if(n!=NULL){
      return (height(n->left)-height(n->right));
    }
}

Node* insert(Node* root,int key){

    if(root==NULL){
      return (makeNode(key));
    }
    if(key<root->data){
      root->left=insert(root->left,key);
    }
    else if(key>root->data){
      root->right=insert(root->right,key);
    }
    else{
      return root;
    }

    // updation of height for previous nodes
    root->height=1+max(height(root->left),height(root->right));

    int bf=getBalance(root);

    // LL
    if(bf>1 && key<((root->left)->data)){
      return rightRotate(root);
    }

    // RR
    if(bf<-1 && key>((root->right)->data)){
      return leftRotate(root);
    }

    // LR
    if(bf>1 && key>((root->left)->data)){
      root->left=leftRotate(root->left);
      return rightRotate(root);
    }

    // RL
    if(bf<-1 && key<((root->right)->data)){
      root->right=rightRotate(root->right);
      return leftRotate(root);
    }

    return root;

}

Node* minValue(Node* root){

    Node* temp=root;
    while(temp->left!=NULL){
      temp = temp->left;
    }

    return temp;
}

Node* delete(Node* root,int key){


    if (root==NULL) {
      return NULL;
    }
    else if(key<root->data){
      root->left=delete(root->left,key);
    }
    else if(key>root->data){
      root->right=delete(root->right,key);
    }
    // key is same as root data
    else
    {
        //root with any one child
        if(root->left==NULL){
        Node* temp=root->right;
          free(root);
          return temp;

        }
        else if(root->right==NULL){
          Node* temp=root->left;
            free(root);
            return temp;

        }
        //root with both the children
        else
        {
          Node* temp=minValue(root->right);

          root->data=temp->data;

          root->right=delete(root->right,temp->data);
        }


    }

    if (root == NULL)
return root;
    //updation of height

    root->height=1+max(height(root->left),height(root->right));

    int bf=getBalance(root);

   // LL
    if(bf>1 && getBalance(root->left)>=0){
      return rightRotate(root);
    }
    // LR
     if(bf>1 && getBalance(root->left)<0){
       root->left=leftRotate(root->left);
       return rightRotate(root);
     }
     // RR
      if(bf<-1 && getBalance(root->right)<=0){
        return leftRotate(root);
      }
      // RL
       if(bf<-1 && getBalance(root->right)>0){
         root->right=rightRotate(root->right);
         return leftRotate(root);
       }

       return root;

}

void preOrder(Node* root){

    if(root!=NULL){
      printf("%d ",root->data);
      preOrder(root->left);
      preOrder(root->right);
    }
}



int main()
{
  Node *root = NULL;

  /* Constructing tree given in the above figure*/
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6*/


    printf("Preorder traversal of the constructed AVL "
           "tree is \n");
    preOrder(root);

    root = delete(root, 10);

    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6*/


    printf("\nPreorder traversal after deletion of 10 \n");
    preOrder(root);

    return 0;
}
