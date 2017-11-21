
#include<stdio.h>
#include<stdlib.h>

FILE* fi;

typedef struct Tree* SearchTree;
typedef struct Tree* Node;

struct Tree {
    int value;
    SearchTree left;
    SearchTree right;
};



// Find int x at SearchTree T
void findNode(SearchTree T,int x){
    
    if(T==NULL){
        printf("%d is not in the tree\n",x);
        return;
    }
    
    if(x<T->value) return findNode(T->left,x);
    else if(x>T->value) return findNode(T->right,x);
    else{
        
        printf("%d is in the tree\n",x);
        return;
    }
}



// Find the smallest node
Node findMin(SearchTree T){
    
    if(T==NULL) return NULL;
    else if(T->left==NULL) return T;
    else return findMin(T->left);
}



// Insert int x at SearchTree T
SearchTree insertNode(SearchTree T,int x){
    
    if(T==NULL){
        
        T=(SearchTree)malloc(sizeof(struct Tree));
        
        if(T==NULL){
            printf("Out of space!!!\n");
            return NULL;
        }
        else{
            T->value=x;
            T->left=T->right=NULL;
        }
    }
    else if(x<T->value) T->left=insertNode(T->left, x);
    else if(x>T->value) T->right=insertNode(T->right, x);
    else if(x==T->value){
        printf("Already Exists!!\n");
        return NULL;
    }
    return T;
}



// Find int x and delete the node whose value is x(include relocation)
SearchTree deleteNode(SearchTree T,int x){
    
    Node Tmp;
    
    if(T==NULL){
        printf("Element not FOUND!!\n");
        return NULL;
    }
    else if(x<T->value) T->left=deleteNode(T->left,x);
    else if(x>T->value) T->right=deleteNode(T->right,x);
    else if(T->left&&T->right){
        
        Tmp=findMin(T->right);
        T->value=Tmp->value;
        T->right=deleteNode(T->right, T->value);
    }
    else{
        Tmp=T;
        
        if(T->left==NULL) T=T->right;
        else if(T->right==NULL) T=T->left;
        free(Tmp);
    }
    
    return T;
}



// Search BST as Inorder and Print these all
void printInorder(SearchTree T){
    
    if(T){
        printInorder(T->left);
        printf("%d ",T->value);
        printInorder(T->right);
    }
}



// Search BST as Preorder and Print these all
void printPreorder(SearchTree T){
    
    if(T){
        printf("%d ",T->value);
        printPreorder(T->left);
        printPreorder(T->right);
    }
}



// Search BST as Postorder and Print these all
void printPostorder(SearchTree T){
    
    if(T){
        printPostorder(T->left);
        printPostorder(T->right);
        printf("%d ",T->value);
    }
}



int main(int args,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    SearchTree T=NULL;
    char choice[2];
    int input,chk;
    int i;
    
    while(1){
        
        for(i=0;i<2;i++){
            chk=fscanf(fi,"%1c",&choice[i]);
            if(choice[i]!='p') break;
        }
        if(chk<0) break;
        
        switch(choice[0]){ // How to use it
            
            case'i': // insert a node
                fscanf(fi,"%d",&input);
                T=insertNode(T,input);
                break;
            case'd': // Delete the node
                fscanf(fi,"%d",&input);
                T=deleteNode(T, input);
                break;
            case'f': // Find the nod
                fscanf(fi,"%d",&input);
                findNode(T, input);
                break;
            case 'p':
                if(choice[1]=='i'){
                    printInorder(T); // Inorder
                    printf("\n");
                }
                else if(choice[1]=='r'){
                    printPreorder(T); // Preorder
                    printf("\n");
                }
                else if(choice[1]=='o'){
                    printPostorder(T); // Postorder
                    printf("\n");
                }
                else printf("No other order!\n");
                break;
            
        }
        
    }
    
    fclose(fi);
    return 0;
}
