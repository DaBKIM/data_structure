#include<stdio.h>
#include<stdlib.h>

FILE *fi;

typedef int ElementType;
typedef struct RBNode *RBTree;

struct RBNode{
    
    ElementType Elemnet;
    char color;
    RBTree left;
    RBTree right;
    RBTree parent;
    
};

RBTree Root=NULL;



// Rotate x to left (include relocation)
void leftRotate(RBTree x){
    
    RBTree y;
    
    y=x->right; // Connect y with the right node of the x (Rotate to left)
    x->right=y->left;
    
    // Relocation
    if(y->left!=NULL) y->left->parent=x;
    
    y->parent=x->parent;
    
    if(x->parent==NULL) Root=y;
    else if(x->parent->left!=NULL&&x->Elemnet==x->parent->left->Elemnet)
        x->parent->left=y;
    else x->parent->right=y;
    
    y->left=x;
    x->parent=y;
    
    return;
    
}



// Rotate x to right (include relocation)
void rightRotate(RBTree y){
    
    RBTree x;
    
    x=y->left; // Connect x with the left node of the y (Rotate to right)
    y->left=x->right;
    
    // Relocation
    if(x->right!=NULL) x->right->parent=y;
    
    x->parent=y->parent;
    
    if(y->parent==NULL) Root=x;
    else if(y->parent->left!=NULL&&y->Elemnet==y->parent->left->Elemnet)
        y->parent->left=x;
    else y->parent->right=x;
    
    x->right=y;
    y->parent=x;
    
    return;
    
}



// Change the color of the node
void RedBlack(RBTree T){
    
    RBTree X=NULL;
    
    while(T->parent!=NULL&&T->parent->color=='r'){ // If the color of parent node is red
        
        if(T->parent->parent->left!=NULL&&T->parent->Elemnet==T->parent->parent->left->Elemnet){
            
           if(T->parent->parent->right!=NULL) X=T->parent->parent->right;
            
            // Change the color and relocation
            if(X!=NULL&&X->color=='r'){
                T->parent->color='b';
                X->color='b';
                T->parent->parent->color='r';
                
                if(T->parent->parent!=NULL)T=T->parent->parent;
            }
            else {
                if(T->parent->right!=NULL&&T->Elemnet==T->parent->right->Elemnet){
                   
                    T=T->parent;
                    leftRotate(T);
                }
                
                T->parent->color='b';
                T->parent->parent->color='r';
                rightRotate(T->parent->parent);
            }
            
        }
        else{
            
            if(T->parent->parent->left!=NULL) X=T->parent->parent->left;
            
            // Change the color and relocation
            if(X!=NULL&&X->color=='r'){
                
                T->parent->color='b';
                X->color='b';
                T->parent->parent->color='r';
                
                if(T->parent->parent!=NULL) T=T->parent->parent;
            }
            else {
                
                if(T->parent->left!=NULL&&T->Elemnet==T->parent->left->Elemnet){
                    
                    T=T->parent;
                    rightRotate(T);
                }
                
                T->parent->color='b';
                T->parent->parent->color='r';
                leftRotate(T->parent->parent);
            }
            
        }
    }
    
    Root->color='b'; // Root is balck
}



// Insert the node
void Insert(ElementType x){
    
    RBTree T=(RBTree)malloc(sizeof(struct RBNode));
    
    T->Elemnet=x;
    T->left=NULL;
    T->right=NULL;
    T->color='r';
    
    RBTree X=Root;
    RBTree Y=NULL;
    
    if(Root==NULL){
        Root=T;
        Root->color='b';
        Root->parent=NULL;
        return;
    }
    
    while(X!=NULL){
        
        Y=X;
        
        if(T->Elemnet<X->Elemnet) X=X->left;
        else
            X=X->right;
        
    }
    
    T->parent=Y;
    
    if(Y==NULL) Root=T;
    else if(T->Elemnet<Y->Elemnet) Y->left=T;
    else
        Y->right=T;
    
    RedBlack(T);
    
}



// Print the red black tree by inorder
void printLevelByLevel(RBTree root){
    
    RBTree tmp=root;
    
    if(tmp!=NULL){
        
        printLevelByLevel(tmp->left);
        printf("%d(%c) ",tmp->Elemnet,tmp->color);
        printLevelByLevel(tmp->right);
    }
}


int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    int i,ck;
    int line=0;
    
    while(1){
        
        line++;
        ck=fscanf(fi,"%d",&i);
        
        if(ck<0) break;
        
        Insert(i);
        
        printf("%d. ",line);
        printLevelByLevel(Root);
        printf("\n\n");
        
    }
    
    fclose(fi);
    
    return 0;
}
