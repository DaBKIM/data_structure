#include<stdio.h>
#include<stdlib.h>

FILE* fi;

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node
{
    ElementType	element;
    Position next;
};



// Make list empty
List MakeEmpty( List L ){
    
    L=(List)malloc(sizeof(struct Node));
    L->element=0;
    L->next=NULL;
    return L;
}



// Make sure that the list empty
int IsEmpty( List L ){
    
    return L->next==NULL;
}



// Confirm the last node
int IsLast( Position P,  List L ){
    
    return P->next==NULL;
}



// Find Previous node and return its Position
Position FindPrevious ( ElementType X,  List L ){
    
    Position P;
    
    P=L;
    while(P->next!=NULL&&P->next->element!=X) P=P->next;
    return P;
}



// Find ElementType X and delete it (include connect previous node and next node)
void Delete( ElementType X,  List L ){
    
    Position P,tmp;
    
    P=FindPrevious(X,L);
    if(!IsLast(P,L)){
        
        tmp=P->next;
        P->next=tmp->next;
        free(tmp);
    }
    
}



// Find ElementType X and return the Position of X
Position Find(ElementType X, List L){
    
    Position P;
    
    P=L->next;
    while(P!=NULL&&P->element!=X) P=P->next;
    
    return P;
    
}



// Insert ElementType X at Position P
void Insert ( ElementType X,  List L, Position P ){
    
    Position tmp;
    
    tmp=(Position)malloc(sizeof(struct Node));
    
    if(tmp==NULL){
        printf("Out of space!!!\n");
        return;
    }
    
    tmp->element =X;
    tmp->next=P->next;
    P->next=tmp;
    
}



// Delete all the list
void DeleteList ( List L ){
  
    Position P,tmp;
    
    P=L->next;
    L->next=NULL;
    
    while(P!=NULL){
        
        tmp=P->next;
        free(P);
        P=tmp;
    }
}



// Show all information of the list
void ShowList(List L){
    
    Position tmp;
    tmp=L;
    
    if(tmp->next==NULL) return;
    else{
        while(tmp->next!=NULL){
            printf("key:%d  ",tmp->next->element);
            tmp=tmp->next;
        }
        printf("\n");
    }
}


int main(int argc, char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    List L;
    Position P;
    char i;
    ElementType x,y;
    
    L=(List)malloc(sizeof(struct Node));
    
    L->next=NULL;
    
    while(1){

        fscanf(fi,"%c",&i);
        
        switch(i) // How to use the Linked List
        {
            case 'i': // Insert
                fscanf(fi,"%d %d",&x,&y);
                if(y==-1) Insert(x, L, L);
                else{
                    
                    if(Find(y, L)==NULL) printf("Insertion(%d) Failed : element %d is not in the list\n",x,y);
                    else Insert(x,L,Find(y,L));
                }
                break;
            case 'd': // Delete
                fscanf(fi,"%d",&x);
                if(Find(x,L)==NULL) printf("Deletion failed : element %d is not in the list\n",x);
                else Delete(x, L);
                break;
            case 'f': // Find
                fscanf(fi,"%d",&x);
                if(Find(x,L)==NULL) printf("Could not find %d in the list\n",x);
                else if(FindPrevious(x,L)==L) printf("Key of the previous node of %d is header\n",x);
                else printf("Key of the previous node of %d is %d\n",x,FindPrevious(x,L)->element);
                break;
            case 'p': // Show all the List
                ShowList(L);
                break;
                
        }
        
        if(i=='p') return 0;
        
    }
    
    
    free(L);
    
    fclose(fi);
    
    return 0;
    
}
