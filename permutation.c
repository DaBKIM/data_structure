#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fi;
FILE *fo;


void swap1(char* a,char* b){ // swap
    
    int tp;
    tp=*a;
    *a=*b;
    *b=tp;
    
}


void perm(char* list,int i,int n){ //  i: start point, n: end point, permutation
    
    int j;
    
    if(i==n){
        for(j=0;j<=n;j++) {
            
            if(j==0) {
                fprintf(fo,"{%c,",list[j]);
            }
            else if(j<n){
                fprintf(fo,"%c,",list[j]);
            }
            else fprintf(fo,"%c}\n",list[j]);
		
        }
    }
    else{
        for(j=i;j<=n;j++){ // use recursive algorithm to find the result
            
            swap1(&list[i],&list[j]);
            perm(list,i+1,n);
            swap1(&list[i],&list[j]);
            
        }
    }
}




int main(int argc,char* argv[]){
    
    char* list;
    list=(char*)malloc(sizeof(char)*105);
    
    fi=fopen(argv[1],"r");
    fo=fopen(argv[2],"w");
    
    int n=0;
    
    while(1){
        
        char tmp;
        fscanf(fi,"%c",&tmp);
        
        if(tmp=='{'||tmp==',') continue;
        else if(tmp=='}') break;
        else {list[n]=tmp;n++;}
    }
    
    perm(list,0,n-1);
    
    free(list);
    
    fclose(fi);
    fclose(fo);
}
