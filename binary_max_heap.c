#include<stdio.h>
#include<stdlib.h>

FILE* fi;

typedef struct HeapStruct* PriorityQueue;
typedef int ElementType;

struct HeapStruct { // Max Heap Tree
    int Capacity;
    int Size;
    ElementType *Elements;
};



// Create a heap tree
PriorityQueue CreateHeap(int heapsize){
    
    PriorityQueue h=(PriorityQueue)malloc(sizeof(struct HeapStruct));
    
    if(h==NULL){
        printf("Out of space!\n");
        return NULL;
    }
    
    h->Elements=(ElementType*)malloc((heapsize+1)*sizeof(ElementType));
    
    if(h->Elements==NULL){
        printf("Out of space!\n");
        return NULL;
    }
    
    h->Capacity=heapsize;
    h->Size=0;
    
    return h;
}



int IsFull(PriorityQueue heap){
    
    return heap->Size==heap->Capacity;
}



int IsEmpty(PriorityQueue heap){
    
    return heap->Size==0;
}



// Insert ElementType x to Heap
void Insert(PriorityQueue heap,ElementType x){
    
    int i;
    
    if(IsFull(heap)){
        
        printf("Priority queue is FULL! Can't INSERT!\n");
        return;
    }
    
    for(i=++heap->Size;i!=1&&heap->Elements[i/2]<x;i/=2){
        
        heap->Elements[i]=heap->Elements[i/2];
    }
    
    heap->Elements[i]=x;
    
}



// Delete the biggest argument in the heap
ElementType DeleteMax(PriorityQueue heap){
    
    if(IsEmpty(heap)){
        
        printf("Priority queue is EMPTY! Can't DELETE!\n");
        return -1;
    }
    else{
        
        int i,max,child, last;
        
        max=heap->Elements[1];
        last=heap->Elements[heap->Size--];
        
        for(i=1;i*2<=heap->Size;i=child){
            
            child=i*2;
            
            if(child!=heap->Size&&heap->Elements[child]<heap->Elements[child+1]) child++;
            
            if(heap->Elements[child]>last) heap->Elements[i]=heap->Elements[child];
            else break;
        }
        
        heap->Elements[i]=last;
        
        return max;
    }
    
}



// Print all the argument in the heap
void PrintHeap(PriorityQueue heap){
    
    int i;
    
    if(IsEmpty(heap)){
        
        printf("Priority queue is EMPTY! Can't PRINT!\n");
        return;
    }
    
    for(i=1;i<=heap->Size;i++){
        printf("%d ",heap->Elements[i]);
    }
    printf("\n");
    
}

int main(int args,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    PriorityQueue heap=NULL;
    
    char choice;
    int input,ck;
    
    while(1){
        
        ck=fscanf(fi,"%c",&choice);
        
        if(ck<0) break;
        
        switch (choice) { // How to use
            
            case 'n': // Create new heap
            fscanf(fi,"%d",&input);
            heap=CreateHeap(input);
            break;
            
            case 'i': // Insert
            fscanf(fi,"%d",&input);
            Insert(heap, input);
            break;
            
            case 'd': // Delete
            DeleteMax(heap);
            break;
            
            case 'p': // Print
            PrintHeap(heap);
            break;
            
            default:
            break;
        }
    }
    
    fclose(fi);
    return 0;
    
}
