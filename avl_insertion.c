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

void preOrder(Node* root){

    if(root!=NULL){
      printf("%d ",root->data);
      preOrder(root->left);
      preOrder(root->right);
    }
}

int main(){

  Node *root=NULL;

    root = insert(root, 10);
    root = insert(root, 12);
    root = insert(root, 16);
    root = insert(root, 18);
    root = insert(root, 11);


  preOrder(root);

  return 0;
}
