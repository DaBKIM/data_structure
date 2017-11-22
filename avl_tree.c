#include <stdio.h>
#include <stdlib.h>

FILE *fi;

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode{
    
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};



// Return the Height of the node
int Height(Position P){
    
    if (P==NULL) return -1;
    else return P->Height;
}



// Return bigger one between i and j
int Max(int i,int j){
    
    if(i>j) return i;
    else return j;
}



// Make AVL tree empty
void MakeEmpty(AVLTree T){
    
    if(T->Left != NULL)
    {
        MakeEmpty(T->Left);
        T->Left=NULL;
    }
    if(T->Right != NULL)
    {
        MakeEmpty(T->Right);
        T->Right=NULL;
    }
    free(T);
}



// Rotate the left child of a node into a parent node(include relocation)
Position SingleRotateWithLeft(Position K2){
    
    printf("Single Rotate With Left %d Node\n",K2->Element);
    
    Position K1;
    
    K1=K2->Left;
    K2->Left=K1->Right;
    K1->Right=K2;
    
    K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
    K1->Height=Max(Height(K1->Left),K2->Height)+1;
    
    return K1;
}



// Rotate the right child of a node into a parent node(include relocation)
Position SingleRotateWithRight(Position K2){
    
    printf("Single Rotate With Right %d Node\n",K2->Element);
    
    Position K1;
    
    K1=K2->Right;
    K2->Right=K1->Left;
    K1->Left=K2;
    
    K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
    K1->Height=Max(Height(K1->Right),K2->Height)+1;
    
    return K1;
}



// Rotate the node twice(left) (if it can't be in the right place when it rotate once)
Position DoubleRotateWithLeft(Position K3){
    
    printf("Double Rotate With Left %d Node\n",K3->Element);
    
    K3->Left = SingleRotateWithRight(K3->Left); // Rotate left child to right first
    
    return SingleRotateWithLeft(K3); // Rotate K3 to left again
}



// Rotate the node twice(right) (if it can't be in the right place when it rotate once)
Position DoubleRotateWithRight(Position K3){
    
    printf("Double Rotate With Right %d Node\n",K3->Element);
    
    K3->Right=SingleRotateWithLeft(K3->Right); // Rotate right child to right to left first
    
    return SingleRotateWithRight(K3); // Rotate K3 to right again
}



// Insert x to AVLTree T
AVLTree Insert(ElementType X, AVLTree T){
    
    if(T==NULL) {
        
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        
        if(T == NULL) {
            printf("Out of space!!!\n");
            return NULL;
        }
        else {
            T->Element=X;
            T->Height=0;
            T->Left=T->Right=NULL;
        }
    }
    
    else if (X<=T->Element){
        
        T->Left=Insert(X,T->Left);
        
        if(Height(T->Left)-Height(T->Right)==2){
            
            if(X<T->Left->Element) T=SingleRotateWithLeft(T);
            else T=DoubleRotateWithLeft(T);
        }
    }
    
    else if(X>=T->Element) {
        
        T->Right=Insert(X,T->Right);
        
        if(Height(T->Right)-Height(T->Left)==2){ // If the height difference is 2
            
            // x is inserted in a suitable position through proper rotation
            if(X>T->Right->Element) T=SingleRotateWithRight(T);
            else T=DoubleRotateWithRight(T);
        }
    }
    
    T->Height=Max(Height(T->Left),Height(T->Right))+1;
    return T;
}



void printInorder(AVLTree T){
    
    if(T!=NULL){
        
        printInorder(T->Left);
        printf("%d ",T->Element);
        printInorder(T->Right);
    }
}


int main(int argc, char *argv[]){
    
    fi=fopen(argv[1],"r");
    
    AVLTree T=NULL;
    int input,ck;
    
    while(1){
        
        ck=fscanf(fi,"%d",&input);
        
        if(ck<0) break;
        
        T=Insert(input, T);
        
        printf("print AVL tree inorder : ");
        
        printInorder(T);
        printf("\n\n");
    }
    
    fclose(fi);
    
    return 0;
}
