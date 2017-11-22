#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 21474836
#define MAX_VERTICES 1000
#define INF 10000

int weight[MAX_VERTICES][MAX_VERTICES];
int d[MAX_VERTICES];
int visit[MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];
int check[MAX_VERTICES];


typedef struct Node{
    int vertex[1000];
    int size;
}Node;



// Initialize the path and the weight
void path_init(int path[][MAX_VERTICES],int vertexnum){
    
    int i, j;
    
    for (i = 0; i<vertexnum; i++){
        for (j = 0; j < vertexnum; j++){
            path[i][j] = INF;
            weight[i][j] = INF;
        }
    }
}



// Find the node in the shortest path
int choose(int d[],int n,int visit[]){
    
    int i, min, minpos;
    
    min = INT_MAX;
    minpos = -1;
    
    for (i = 0; i<n; i++){
        
        if (d[i]<min && !visit[i]){ // Not visit && shorter than distance
            
            min = d[i];
            
            minpos = i;
            
        }
    }
    
    return minpos;
    
}



// Algorithm of the shortest path
void dijikstra(int start, int vertexnum){ // start == start node, vertexum == total node
    
    int i, j, u, w;
    
    for (i = 0; i<vertexnum; i++){ // Initialize
        
        d[i] = weight[start][i];
        visit[i] = 0;
        check[i] = 1;
        path[i][0] = start;
        
    }
    
    visit[start] = 1;
    d[start] = 0;
    
    for (i = 0; i<vertexnum - 2; i++){
        
        u = choose(d,vertexnum,visit);
        visit[u] = 1;
        
        for (w = 0; w<vertexnum; w++){
            if (!visit[w]){
                if (d[u] + weight[u][w] < d[w]){
                    if (i == 0){
                        
                        path[w][check[w]] = u;
                        check[w]++;
                    }
                    else{
                        for (j = 0; j<(check[u] + 1); j++){
                            
                            path[w][j] = path[u][j];
                            path[w][j + 1] = u;
                            check[w]++;
                        }
                    }
                    
                    d[w] = d[u] + weight[u][w];
                }
            }
        }
    }
}



// Find number
int findnumber(int num, Node *V){
    
    int i;
    for (i = 0; i < V->size;i++){
        if (V->vertex[i] == num) return i;
    }
    
    return -1;
}



int main(int argc,char* argv[]){
    
    FILE* fi=fopen(argv[1],"r");
    
    int i, j;
    
    int max = -1;
    int start,ck;
    int input,input2,input3;
    char c,c2;
    int st,ed;
    
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->size = 0;
    
    
    i = 0;
    
    while (1){
        
        fscanf(fi,"%d", &input);
        fscanf(fi,"%c", &c);
        
        node->vertex[i++] = input;
        node->size++;
        
        if(max<input) max=input;
        
        if(c=='\n') break;
    }
    
    
    path_init(path,node->size);
    
    while (1){
        
        ck=fscanf(fi,"%d%c%d%c%d",&input,&c,&input2,&c2,&input3);
        
        if(ck<0) break;
        
        st = findnumber(input, node);
        ed = findnumber(input2, node);
        weight[st][ed] = input3;
    }
    
    start = findnumber(max, node);
    
    
    dijikstra(start, node->size);
    
    printf("-------print current found shortest paths-------\n");
    
    for (i = 0; i< node->size; i++){
        
        printf("from %d to %d : ",max,node->vertex[i]);
        
        for(j=0;j<node->size;j++){
            
            if(max==node->vertex[i]) break;
            if(path[i][j]!=INF) printf("%d->",node->vertex[path[i][j]]);
        }
        
        printf("%d (cost %d)\n",node->vertex[i],d[i]);
    }
    printf("---------------------done---------------------\n");
    
    fclose(fi);
    return 0;
}

