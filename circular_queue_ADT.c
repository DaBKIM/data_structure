#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fi;

typedef struct CircularQueue *Queue;

struct CircularQueue{
    
    int *key; // adress
    int first; // first arg
    int rear; // last arg
    int qsize; // queue size
    int max_queue_size;
};



// Create a queue
Queue CreateQueue(int max_queue_size){
    
    Queue Q=(Queue) malloc(sizeof(struct CircularQueue));
    
    Q->max_queue_size=max_queue_size;
    Q->first=Q->qsize=0;
    Q->rear=max_queue_size-1;
    Q->key=(int*)malloc(Q->max_queue_size*sizeof(int));
    return Q;
    
}



// Make queue empty
void MakeEmpty(Queue Q){
    
    Q->qsize=0;
    Q->first=1;
    Q->rear=0;
   
}



// Make sure that queue empty
int IsEmpty( Queue Q){
    
    return Q->qsize==0;
}



// Make sure that queue is full
int IsFull(Queue Q){
    
    return Q->qsize==Q->max_queue_size-1;
}



// Delete first argument of the queue
void Dequeue(Queue Q){
    
    if(IsEmpty(Q)){
        printf("Dequeue Failed : Queue is Empty!!\n");
        return;
    }
    else{
        
        int tmp = Q->key[Q->first];
        Q->qsize--;
        Q->first=(Q->first+1)%Q->max_queue_size;
        printf("Dequeue Success : %d\n",tmp);
    }
    
}



// Insert argument at the last of queue
void Enqueue(Queue Q,int X){
    
    if(IsFull(Q)){
        printf("Insertion Failed : Queue is Full!!\n");
        return;
    }
    else{
        Q->qsize++;
        Q->rear=(Q->rear+1)%Q->max_queue_size;
        Q->key[Q->rear]=X;
        printf("Insertion Success : %d\n",X);
    }
    
}



// Print first argument of queue
void PrintFirst (Queue Q){
    
    if(IsEmpty(Q)){
        printf("Print failed : Queue is Empty!!\n");
        return;
    }
    else{
        printf("Front of Queue : %d\n", Q->key[Q->first]);
    }
    
}



// Print last argument of queue
void PrintRear (Queue Q){
    
    if(IsEmpty(Q)){
        printf("Print failed : Queue is Empty!!\n");
        return;
    }
    else{
        printf("Rear of Queue : %d\n",Q->key[Q->rear]);
    }
}



// Delete all the information of queue
void DeleteQueue (Queue Q){
    
    if(Q == NULL){
        printf("DeleteQueue Failed : No queue exists!!\n");
        return;
    }
    else{
        while(!IsEmpty(Q)){
            Dequeue(Q);
            printf("DeleteQueue Success : Queue is Deleted!!\n");
        }
        
    }
}

int main(int argc, char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    Queue Q = NULL;

    char input;
    int in, chk;
    
    while(1){
        
        chk = fscanf(fi,"%c",&input);
        
	if(chk < 0)
		return 0;
        
	switch(input){ // How to use the circular queue
            case 'n': // Make new queue
                fscanf(fi,"%d",&in);
                Q=CreateQueue(in+1);
                break;
            case 'e': // Enqueue
                fscanf(fi,"%d",&in);
                Enqueue(Q, in);
                break;
            case 'd': // Dequeue
                Dequeue(Q);
                break;
            case 'f': // Print first argument
                PrintFirst(Q);
                break;
            case 'r': // Print last argument
                PrintRear(Q);
                break;
            default:
                break;
                
        }
    }
    
    fclose(fi);
    return 0;
    
}
