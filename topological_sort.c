
#include <stdio.h>
#include <stdlib.h>

FILE* fi;

int inde[505];
int indegree[505];
int arr[505][505];

typedef struct CircularQueue *Queue;

struct CircularQueue{
    
    int *key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

Queue Q;

Queue CreateQueue(int max_queue_size){
    
    Queue Q=(Queue) malloc(sizeof(struct CircularQueue));
    
    Q->max_queue_size=max_queue_size;
    Q->first=1;
    Q->qsize=0;
    Q->rear=0;
    Q->key=(int*)malloc(Q->max_queue_size*sizeof(int));
    return Q;
    
}

void MakeEmpty(Queue Q){
    
    Q->qsize=0;
    Q->first=1;
    Q->rear=0;
    
}

int IsEmpty( Queue Q){
    
    return Q->qsize==0;
}

int IsFull(Queue Q){
    
    return Q->qsize==Q->max_queue_size-1;
}

int Dequeue(Queue Q){
    
    if(IsEmpty(Q)){
        printf("Dequeue Failed : Queue is Empty!!\n");
        return 0;
    }
    else{
        
        int tmp = Q->key[Q->first];
        Q->qsize--;
        Q->first=(Q->first+1)%Q->max_queue_size;
        return tmp;
    }
    
}

void Enqueue(Queue Q,int X){
    
    if(IsFull(Q)){
        printf("Insertion Failed : Queue is Full!!\n");
        return;
    }
    else{
        Q->rear=(Q->rear+1)%Q->max_queue_size;
        Q->key[Q->rear]=X;
        Q->qsize++;
    }
    
}



// Print all the node, sort by circular queue(topological sort)
void Topsort(int x){ // x == total number of the node
    
    int v,w,i,tmp;
    int* ckdegree=(int*)malloc(x*sizeof(int));
    
    int cnt=0;

    Q=CreateQueue(x);
    
    
    for(v=1;v<=x;v++)
        if(indegree[v]==0) Enqueue(Q,inde[v]);
    
    while(!IsEmpty(Q)){
        
        tmp=Dequeue(Q);
        ckdegree[cnt++]=tmp;
        
        for(w=1;w<=x;w++){
            
            if(--indegree[w]==0) { // If indegree of the node is 0, put the node in queue
                Enqueue(Q, inde[w]);
            }
        }
    }
    
    printf("Topological Sort : ");
    for(i=0;i<x;i++){
        
        printf("%d ",ckdegree[i]);
    }
    printf("\n");
    
    free(ckdegree);
    
}


int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    char tmp;
    int in,cnt=0;
    int to,i,ck;
    int start=0,end=0;
    int tmpi,tmpj;
    
    while(1){ // Node name
        
        fscanf(fi,"%d",&in);
        fscanf(fi,"%c",&tmp);
        
        inde[++cnt]=in;
        
        if(tmp=='\n') break;
        
    }
    
    while(1){ // Node connect
        
        ck=fscanf(fi,"%d%c%d",&in,&tmp,&to);
        
        if(ck<0) break;
        
        for(i=1;i<=cnt;i++){
            if(inde[i]==in) start=i;
            if(inde[i]==to) end=i;
        }
        
        arr[start][end]=1;
        indegree[end]++;
        
        printf("%d-%d\n",in,to);
        for(tmpi=1;tmpi<=cnt;tmpi++){
            for(tmpj=1;tmpj<=cnt;tmpj++){
                printf("%d ",arr[tmpi][tmpj]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    Topsort(cnt);
    
    fclose(fi);
    return 0;
    
}

