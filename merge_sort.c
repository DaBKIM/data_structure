#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

FILE* fi;

typedef int ElementType;

int *iter_arr;
int *recur_arr;
int *tmp;
int input[MAX];



// Merge arrays
void Merge(ElementType A[],ElementType TmpArray[],int Lpos,int Rpos,int RightEnd){
    
    int i,LeftEnd,NumElements,TmpPos,save;
    
    save=Lpos; // the first position of the left array
    LeftEnd=Rpos-1; // the last position of the left array
    TmpPos=Lpos;
    NumElements=RightEnd-Lpos+1;
    
    while(Lpos<=LeftEnd&&Rpos<=RightEnd){ // Rpos == the first position of the right array
        
        if(A[Lpos]<=A[Rpos]) TmpArray[TmpPos++]=A[Lpos++];
        else TmpArray[TmpPos++]=A[Rpos++];
    }
    
    while(Lpos<=LeftEnd) TmpArray[TmpPos++]=A[Lpos++];
    
    while (Rpos <= RightEnd) TmpArray[TmpPos++] = A[Rpos++];
    
    for (i = 0; i < NumElements; i++, RightEnd--) A[RightEnd] = TmpArray[RightEnd];
    
    for (i = 0; i <NumElements; i++) printf("%d ", TmpArray[save++]);
    
    printf("\n");
}



// Merge sort func (recursive)
void Msort_recur(ElementType A[],ElementType TmpArray[],int Left,int Right){
    
    int Center;
    
    if(Left<Right){
        Center=(Left+Right)/2; // until the size of array is 1
        Msort_recur(A, TmpArray, Left, Center);
        Msort_recur(A, TmpArray, Center+1, Right);
        Merge(A, TmpArray, Left, Center+1, Right);
    }
}



// Merge sort func (iterative)
void Msort_iter(ElementType A[],ElementType TmpArray[],int all){
    
    //Lpos == start
    int i,Lpos=0,Rpos,RightEnd,NextLpos;
    
    for(i=1;i<all;i*=2){
        
        Lpos=0;
        
        while(Lpos<all){
            
            Rpos = Lpos+(i * 2 - 1);
            RightEnd = (Lpos + Rpos) / 2;
            NextLpos = Rpos + 1;
            
            if (Rpos>=all) Rpos = all - 1;
            if (RightEnd >= Rpos) RightEnd = Rpos - 1;
            
            Merge(A, TmpArray, Lpos, RightEnd + 1, Rpos);
            Lpos = NextLpos;
        }
    }
}

int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    int cnt=0;
    
    iter_arr=(int*)malloc(sizeof(int)*MAX);
    recur_arr=(int*)malloc(sizeof(int)*MAX);
    tmp=(int*)malloc(sizeof(int)*MAX);
    
    printf("input :\n");
    while(1){
        
        int tm;
        char t;
        
        fscanf(fi,"%d",&tm);
        fscanf(fi,"%c",&t);
        
        input[cnt]=tm;
        iter_arr[cnt]=recur_arr[cnt]=tm;
        cnt++;
        printf("%d ",tm);
        
        if(t!=' ') break;
    }
    
    printf("\n\n");
    
    printf("iterative :\n");
    Msort_iter(iter_arr, tmp, cnt);
    
    printf("\n");
    printf("recursive :\n");
    Msort_recur(recur_arr, tmp, 0, cnt-1);
    
    fclose(fi);
    return 0;
    
}
