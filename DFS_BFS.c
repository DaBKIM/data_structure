#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EmptyTOS -1

FILE* fi;

typedef struct CircularQueue *Queue;
int arr[1000000];
int check_queue[100000];
int check_stack_iter[100000];
int check_stack_recur[100000];
int graph[1000][1000];
int recur=0;
int resul[1000];

struct CircularQueue{
    
    int *key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

Queue CreateQueue(int max_queue_size){
    
    Queue Q=(Queue) malloc(sizeof(struct CircularQueue));
    
    Q->max_queue_size=max_queue_size;
    Q->first=Q->qsize=0;
    Q->rear=max_queue_size-1;
    Q->key=(int*)malloc(Q->max_queue_size*sizeof(int));
    return Q;
    
}

void MakeEmpty(Queue Q){
    
    Q->qsize=0;
    Q->first=1;
    Q->rear=0;
    
}

int IsEmpty_q( Queue Q){
    
    return Q->qsize==0;
}

int IsFull_q(Queue Q){
    
    return Q->qsize==Q->max_queue_size-1;
}


int Dequeue(Queue Q){
    
    if(IsEmpty_q(Q)){
        printf("Dequeue Failed : Queue is Empty!!\n");
        return -1;
    }
    else{
        
        int tmp = Q->key[Q->first];
        Q->qsize--;
        Q->first=(Q->first+1)%Q->max_queue_size;
        return tmp;
    }
    
}

void Enqueue(Queue Q,int X){
    
    if(IsFull_q(Q)){
        printf("Insertion Failed : Queue is Full!!\n");
        return;
    }
    else{
        Q->qsize++;
        Q->rear=(Q->rear+1)%Q->max_queue_size;
        Q->key[Q->rear]=X;
    }
    
}

typedef struct StackRecord *Stack;


struct StackRecord{
    
    char *key;
    int top;
    int max_stack_size;
};


int IsEmpty_s(Stack S){
    
    return S->top==EmptyTOS;
}

int IsFull_s(Stack S){
    
    return S->top==S->max_stack_size-1;
}


Stack CreateStack(Stack S,int max){
    
    S=(Stack)malloc(sizeof(struct StackRecord));
    memset(S,0,sizeof(struct StackRecord));
    
    if(S==NULL)
        printf("Out of space!!!\n");
    
    S->key=(char*)malloc(sizeof(char)*max);
    
    if(S->key==NULL)
        printf("Out of space!!!\n");
    
    S->max_stack_size=max;
    S->top=EmptyTOS;
    
    return S;
    
}


int Top(Stack S){
    
    if(!IsEmpty_s(S)) return S->key[S->top];
    else printf("Empty stack\n");
    
    return -1;
}


void Push(int x,Stack s){
    
    if(IsFull_s(s)){
        printf("Full stack\n");
        return;
    }
    else
        s->key[++s->top]=x;
    
}


int Pop(Stack S){
    
    if(IsEmpty_s(S)){
        printf("Empty stack\n");
        return 0;
    }
    else{
        
        int tmp= Top(S);
        S->top--;
        return tmp;
    }
}

void removeStack(Stack S){
    
    if(S==NULL){
        printf("No stack exists\n");
        return;
    }
    else {
        while(!IsEmpty_s(S)) Pop(S);
    }
}

int findnode(int num,int cnt){
    
    int i;
    for(i=0;i<cnt;i++){
        if(arr[i]==num) return i;
    }
    return -1;
}



// Depth-First Search(DFS) by stack (itertative)
void DFS_iter(int from,int to,int cnt,int input2){
    
    Stack S=NULL;
    S=CreateStack(S, 100000);
    int i,ck=0;
    
    Push(from,S);
    
    printf("<DFS iterative search>\n");
    
    while(!IsEmpty_s(S)){
        
        int now=Pop(S);
        
        if(now==-1) return;
        if(check_stack_iter[now]==1) continue;
        
        check_stack_iter[now]=1;
        printf("%d ",arr[now]);
        
        if(now==to){
            ck=1;
        }
        
        for(i=0;i<cnt;i++){
            
            if(graph[now][i]==1&&check_stack_iter[i]==0){
                Push(i,S);
            }
            
        }
    }
    
    if(ck==1) printf("\n%d in the graph.\n\n",input2);
    else printf("\n%d not in the graph.\n\n",input2);
    
}



// Depth-First Search(DFS) (recursive)
void DFS_recur(int from,int to, int cnt){
    
    int i;
    printf("%d ",arr[from]);
    check_stack_recur[from]=1;
    
    if(from==to) recur=1;
    
    for(i=0;i<cnt;i++){
        
        if(graph[from][i]==1&&check_stack_recur[i]==0){
            
            DFS_recur(i,to,cnt);
        }
    }
}



// Breath-First Search by queue
void BFS(int from,int to,int cnt,int input2){
    
    Queue Q=NULL;
    Q=CreateQueue(100000);
    MakeEmpty(Q);
    int i,ck=0;
    
    Enqueue(Q, from);
    check_queue[from]=1;
    
    printf("<BFS search>\n");
    
    while(!IsEmpty_q(Q)){
        
        int now=Dequeue(Q);
        if(now==-1) return;
        
        printf("%d ",arr[now]);
        
        if(now==to){
            ck=1;
            
        }
        
        for(i=0;i<cnt;i++){
            if(graph[now][i]==1&&check_queue[i]==0){
                check_queue[i]=1;
                Enqueue(Q, i);
            }
        }
        
        
    }
    
    if(ck==1) printf("\n%d in the graph.\n",input2);
    else printf("\n%d not in the graph.\n",input2);
    
    
}


int main(int argc,char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    int input,input2;
    char tmp;
    int cnt=0;
    int st,ed;
    int from,to;
    
    while(1){
        
        fscanf(fi,"%d",&input);
        fscanf(fi,"%c",&tmp);
        
        
        arr[cnt]=input;
        cnt++;
        
        if(tmp=='\n') break;
    }
    
    while(1){ // Connect
        
        fscanf(fi,"%d%c%d",&input,&tmp,&input2);
        fscanf(fi,"%c",&tmp);
        
        st=findnode(input, cnt);
        ed=findnode(input2, cnt);
        
        if(st==-1) printf("Error : %d doesn't exist!\n",input);
        else if(ed==-1) printf("Error : %d doesn't exist!\n",input2);
        else graph[st][ed]=1;
        
        if(tmp=='\n') break;
    }
    
    fscanf(fi,"%d%c%d",&input,&tmp,&input2);
    from=findnode(input, cnt); // Start
    to=findnode(input2, cnt); // End
    
    DFS_iter(from, to, cnt,input2);
    printf("<DFS recursive search>\n");
    DFS_recur(from, to, cnt);
    if(recur==1) printf("\n%d in the graph.\n\n",input2);
    else printf("\n%d not in the graph.\n\n",input2);
    BFS(from, to, cnt,input2);
    
    fclose(fi);
    return 0;
    
}
