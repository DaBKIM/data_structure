#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct HashTable* HashTbl;

FILE* fi;

int tablesize=0;

struct HashTable{
    int* key;
    int* state; // Empty or not
};


int Hash(ElementType key,ElementType tablesize){
    
    return key%tablesize;
}



// linear probing (Location shift)
int linear(int i,int key){
    
    return (Hash(key,tablesize)+i)%tablesize;
}



// Insert key to Hash Table
void Insert_addressing(int key,HashTbl H){
    
    int val=Hash(key,tablesize);
    int i=val;
    
    if(H->state[i]==1){ // Collision
        
        printf("%d, Collision Occurs!\n",key);
        
        while(H->state[i]==1){ // Find empty place
        
            if(H->key[i]==key){
                printf("%d, duplicated error!\n",key);
                return;
            }
        
            i=linear(i,key);
        
            if(i==val){
                printf("Ths table is full!\n");
                return;
            }
        }
    
        H->key[i]=key;
        H->state[i]=1;
    }
    else {
        H->key[i]=key;
        H->state[i]=1;
    }
    
}



// Find key in the table
int find(int key, HashTbl H){
    
    int val=Hash(key,tablesize);
    int i=val;
    
    while(H->state[i]==1){
        
        if(H->key[i]==key){
            return 1;
        }
        
        i=linear(i,key);
    }
    
    return 0;
    
}


int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    HashTbl H=NULL;
    
    int ck,cnt=0;
    int num;
    char tmp;
    fscanf(fi,"%d",&tablesize);
    
    H=(HashTbl)malloc(sizeof(struct HashTable)); //Initialize
    
    if(H==NULL) printf("HashTable, Out of space!\n");
    else{
        
        H->key=(int*)malloc(sizeof(int)*tablesize);
        H->state=(int*)malloc(sizeof(int)*tablesize);
        
        if(H->key==NULL) printf("HashTable key ,Out of Space!\n");
        else if(H->state==NULL) printf("HashTable state ,Out of Space!\n");
        
    }
    
    while(1){
        
        fscanf(fi,"%d",&num);
        fscanf(fi,"%c",&tmp);
        
        Insert_addressing(num,H);
        
        if(tmp=='\n') break;
        
    }
    
    
    while(1){
        
        printf("\n");
        cnt++;
        ck=fscanf(fi,"%d",&num);
        
        if(ck<0) break;
        
        if(find(num,H)==0) printf("%d. %d is not in the table!\n",cnt,num);
        else printf("%d. %d is in the table!\n",cnt,num);
    }
    
    fclose(fi);
    return 0;
    
}
