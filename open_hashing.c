#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct ListNode* Position;
typedef Position List;
typedef struct HashTable* HashTbl;

FILE* fi;



// Hashing Node
struct ListNode{
    ElementType element;
    Position Next; // Connect
};



// Hashing Table
struct HashTable{
    
    int tablesize;
    List* thelist; // List node
};



// Hashing func (classification)
int Hash(ElementType key, ElementType tablesize){
    
    return key%tablesize;
}



// Find ElementType key
Position Find(ElementType key, HashTbl H){
    
    Position P;
    List L;
    
    L=H->thelist[Hash(key,H->tablesize)];
    P=L->Next;
    
    while(P!=NULL&&P->element!=key) P=P->Next;
    
    return P;
    
}



// Insert the ElementType key into Hash Table
void Insert(ElementType key, HashTbl H){
    
    Position newCell;
    List L;
    
    L=H->thelist[Hash(key, H->tablesize)];
    
    if(L->Next!=NULL){ // Collision
        
        printf("%d, Collision Occurs!\n",key);
        
        Position Pos=Find(key,H);
        
        if(Pos!=NULL){
            printf("%d, duplicated error!\n",key);
            return;
        }
        
        newCell=(Position)malloc(sizeof(struct ListNode));
        
        if(newCell==NULL) printf("newCell, Out of Space!\n");
        else{
            L=H->thelist[Hash(key,H->tablesize)];
            
            newCell->Next=L->Next;
            newCell->element=key;
            L->Next=newCell;
        }
    }
    else{
        
        newCell=(Position)malloc(sizeof(struct ListNode));
        
        if(newCell==NULL) printf("newCell, Out of Space!\n");
        else{
            L=H->thelist[Hash(key,H->tablesize)];
            
            newCell->Next=L->Next;
            newCell->element=key;
            L->Next=newCell;
        }
        
    }
    
}

int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    HashTbl H=NULL;
    
    int t,i,ck,cnt=0;
    int num;
    char tmp;
    fscanf(fi,"%d",&t);
    
    H=(HashTbl)malloc(sizeof(struct HashTable));
    
    if(H==NULL) printf("HashTable, Out of space!\n");
    else{
        
        H->tablesize=t;
        H->thelist=(List*)malloc(sizeof(List)*H->tablesize);
        
        if(H->thelist==NULL) printf("HashTable list ,Out of Space!\n");
        else{
            
            for(i=0;i<H->tablesize;i++){ // Initialize
                
                H->thelist[i]=(List)malloc(sizeof(struct ListNode));
                
                if(H->thelist[i]==NULL) printf("HashTable list ,Out of Space!\n");
                else H->thelist[i]->Next=NULL;
            }
        }
    }
    
    while(1){
        
        fscanf(fi,"%d",&num);
        fscanf(fi,"%c",&tmp);
        
        Insert(num,H);
        
        if(tmp=='\n') break;
        
    }
    
    
    while(1){
        
        printf("\n");
        cnt++;
        ck=fscanf(fi,"%d",&num);
        
        if(ck<0) break;
        
        if(Find(num,H)==NULL) printf("%d. %d is not in the table!\n",cnt,num);
        else printf("%d. %d is in the table!\n",cnt,num);
    }
    
    fclose(fi);
    return 0;
    
}
