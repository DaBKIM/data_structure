#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EmptyTos -1

FILE* fi;

typedef struct StackRecord *Stack;



struct StackRecord {
    int *key;
    int top;
    int max_stack_size;
};



int IsEmpty(Stack S){
    return S->top==EmptyTos;
}



int IsFull(Stack S){
    
    return S->top==S->max_stack_size-1;
}



Stack CreateStack(Stack S, int max){
    
    S=(Stack)malloc(sizeof(struct StackRecord));
    
    memset(S,0,sizeof(struct StackRecord));
    
    if(S==NULL)
        printf("Out of space!!!\n");
    
    S->key=(int*)malloc(sizeof(int)*max);
    
    if(S->key==NULL)
        printf("Out of space!!!\n");
    
    S->max_stack_size=max;
    S->top=EmptyTos;
    
    return S;
}



int Top(Stack S){
    
    if(!IsEmpty(S)) return S->key[S->top];
    else printf("Empty Stack!\n");
    
    return 0;
}



void Push(int x,Stack S){
    if(IsFull(S)){
        printf("Full Stack!\n");
        return;
    }
    else
        S->key[++S->top]=x;
}



void Pop(Stack S){
    
    if(IsEmpty(S)){
        printf("Empty Stack!\n");
        return;
    }

    else
        S->top--;
}



void removeStack(Stack S){
    if(S==NULL){
        printf("No Stack Exists!\n");
        return;
    }
    else while(!IsEmpty(S)) Pop(S);
}



// Calculate according to the operator
int calculate(int op1,int op2,char oper){
    
    if(oper=='*') return op1*op2;
    else if(oper=='%') return op1%op2;
    else if(oper=='+') return op1+op2;
    else if(oper=='-') return op1-op2;
    else if(oper=='/') return op1/op2;
    else return 0;
}



int main(int argc, char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    Stack S;
    
    S=CreateStack(S, 110);
    
    char inf[105];
    memset(inf,0,105);
    
    int i=0;
    int j=0;
    int res=0;
    int operand1=0;
    int operand2=0;
    
    printf("converted postfix form : ");
    
    while(1){
        
        fscanf(fi,"%c",&inf[i]);
        
        if(inf[i]=='#') break; // the end of the information
        
        printf("%c",inf[i]);
        i++;
    }
    
    printf("\n");
    
    while(inf[j]!='#'){ // Evaluation : stack
        
        if(inf[j]>='0'&&inf[j]<='9') Push(inf[j]-'0',S);
        else{
            
            if(!IsEmpty(S)){
                operand2=Top(S);
                Pop(S);
                operand1=Top(S);
                Pop(S);
                
                res=calculate(operand1,operand2,inf[j]);
                
                Push(res,S);
            }
            else{
                printf("Error!\n");
                return 0;
            }
        }
        j++;
    }
    
    printf("evaluation result : %d\n",res);
    
    fclose(fi);
    return 0;
}
