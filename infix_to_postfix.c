
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EmptyTOS -1

FILE* fi;

typedef struct StackRecord *Stack;



// Structure for saving operator
struct StackRecord{
    
    char *key;
    int top;
    int max_stack_size;
};



// Make sure that the stack empty
int IsEmpty( Stack S ){
    
    return S->top==EmptyTOS;
}



// Make sure that the stack is full or not
int IsFull(Stack S){
    
    return S->top==S->max_stack_size-1;
}



// Create the stack
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



// Return the top argument of the stack
char Top(Stack S){
    
    if(!IsEmpty(S)) return S->key[S->top];
    else printf("Empty stack\n");
    
    return 0;
}



// Push the argument x on top of the stack
void Push(char x,Stack s){
    
    if(IsFull(s)){
        printf("Full stack\n");
        return;
    }
    else
        s->key[++s->top]=x;
    
}



// Pop the top of the stack
void Pop(Stack S){
    
    if(IsEmpty(S)) printf("Empty stack\n");
    else{
        S->top--;
    }
}



// Remove all the argument in the stack
void removeStack(Stack S){
    
    if(S==NULL){
        printf("No stack exists\n");
        return;
    }
    else {
        while(!IsEmpty(S)) Pop(S);
    }
}



// Operator classification
int check(char tmp){
    
    switch(tmp){
            
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
        case '%':
            return 2;
            break;
            
    }
    return -1;
}



int main(int argc, char* argv[]){
    
    fi=fopen(argv[1],"r");
    
    Stack s;
    s=CreateStack(s,110);
    
    char inf[105],res[105];
    memset(inf,0,105);
    memset(res,0,sizeof(res));
    
    int i=0,j=0,k=-1;
    
    printf("original infix form : ");
    
    while(1){
        
        fscanf(fi,"%c",&inf[i]);
        
        if(inf[i]=='\0'||inf[i]=='\n'){
            
            i--;
            break;
        }
        
        printf("%c",inf[i]);
        i++;
    }
    printf("#\n"); // the end of the form
 
    while(inf[j]!='\0'){ // Convert infix to postfix
        
        if(inf[j]>='0'&&inf[j]<='9') res[++k]=inf[j];
        else if(inf[j]=='(') Push(inf[j],s);
        else if(inf[j]==')'){
            while(!IsEmpty(s)&&Top(s)!='('){
                res[++k]=Top(s);
                Pop(s);
            }
            if(!IsEmpty(s)&&Top(s)!='('){
                printf("Error!\n");
                return 0;
            }
            else Pop(s);
        }
        else{
            while(!IsEmpty(s)&&(check(inf[j])<=check(Top(s)))){
                res[++k]=Top(s);
                Pop(s);
            }
            Push(inf[j],s);
        }
        
        j++;
    }
    
    while(!IsEmpty(s)){
        
        if(Top(s)=='(') Pop(s);
        
        res[++k]=Top(s);
        Pop(s);
    }
    res[k]=0;
    
    printf("converted postfix form : %s#\n",res);
    
    fclose(fi);
    
    return 0;
}
