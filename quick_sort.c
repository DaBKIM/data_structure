#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000

FILE* fi;

typedef int ElementType;
typedef struct Quicksort* Qsort;

struct Quicksort{
    int Capacity;
    int size;
    ElementType *Elements;
};

void swap(int* a,int* b){
    
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}



// Print right array, left array and pivot based on pivot
void printQsort(int s,int left,int right,ElementType* Q){
    
    int i;
    
    printf("< ");
    for(i=left;i<s;i++) printf("%d ",Q[i]);
    printf("> ");
    
    printf("< %d > ",Q[s]);
    
    printf("< ");
    for(i=s+1;i<=right;i++) printf("%d ",Q[i]);
    printf(">");
    printf("\n");
    
}



// Sort the array (put the leftmost into a pivot)
int LeftP(ElementType elements[],int left,int right){
    
    int pivot,l,r;
    
    pivot=elements[left];
    l=left;
    r=right;
    
    while(l<r){
        
        while(l<r&&elements[r]>pivot) r--;
        
        if(l!=r) elements[l++]=elements[r];
        
        while(l<r&&elements[l]<=pivot) l++;
        
        if(l!=r) elements[r--]=elements[l];
    }
    
    elements[l]=pivot;
    printQsort(l,left,right,elements);
    return l;
}



// Sort the array (put the middle one into a pivot)
int MiddleP(ElementType elements[],int left,int right){
    
    int pivot,l,r;
    
    pivot=elements[(right+1+left)/2];
    l=left;
    r=right;
    
    while(1){
        
        while(l<r&&elements[l]<pivot) l++;
        
        while(l<r&&elements[r]>pivot) r--;
        
        if(l<r) swap(&elemets[l],&elements[r]);
        else{
            printQsort(l, left, right, elements);
            return l;
        }
    }
}



// Sort the array (put the rightmost into a pivot)
int RightP(ElementType elements[],int left,int right){
    
    int pivot,r,l;
    
    pivot=elements[right];
    l=left;
    r=right;
    
    while(l<r){
        
        while(l<r&&elements[l]<=pivot) l++;
        
        if(l!=r) elements[r--]=elements[l];
        
        while(l<r&&elements[r]>pivot) r--;
        
        if(l!=r) elements[l++]=elements[r];
    }
    
    elements[r]=pivot;
    printQsort(r, left, right, elements);
    return r;
}



// Based on the criteria for determining the pivot to execute the sort (recursive)
void qSort(ElementType elements[],int left,int right, char tmp){
    
    int i;
    
    if(left>=right) return;
    
    if(tmp=='l') i=LeftP(elements, left, right);
    else if(tmp=='m') i=MiddleP(elements, left, right);
    else i=RightP(elements, left, right);
    
    qSort(elements,left,i-1,tmp);
    qSort(elements,i+1,right,tmp);
}



int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    Qsort Q;
    char what[MAX];
    char first;
    int i,j;
    
    Q=(Qsort)malloc(sizeof(struct Quicksort));
    Q->Capacity=MAX;
    Q->size=0;
    Q->Elements=(ElementType*)malloc(sizeof(int)*Q->Capacity);
    
    for(i=0;i<3;i++){
        
        Q->size=0;
        fscanf(fi,"%s",what);
        printf("%s :\n",what);
        first=what[0];
        
        while(1){
            
            int tmp;
            char t;
            fscanf(fi,"%d",&tmp);
            fscanf(fi,"%c",&t);
            
            Q->Elements[Q->size++]=tmp;
            
            if(t!=' ') break;
        }
        
        qSort(Q->Elements,0,Q->size-1,first);
        
        printf("\nresult\n");
        for(j=0;j<Q->size;j++) printf("%d ",Q->Elements[j]);
        printf("\n\n");
    }
    
    fclose(fi);
    return 0;
}
