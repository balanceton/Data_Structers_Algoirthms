#include<stdio.h>
#include <stdlib.h>

struct node{
	int vertex;
	struct node* next;
};

struct Graph{
	int numberOfVertices;
	struct node** adjList;
};

struct node* createNode(int v){
	struct node* newV =(struct node*)malloc(sizeof(struct node));
	newV->vertex = v;
	newV->next = NULL;
	return newV;
}

struct Graph* createGraph(int nVertices){
	int i;
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->numberOfVertices = nVertices;
	graph->adjList = (struct node**)malloc(nVertices * sizeof(struct node*));
	for(i=0;i<nVertices;i++){
		graph->adjList[i] = NULL;
	}
	return graph;
}

void addEdge(struct Graph* graph, int u, int v){
	struct node* newNode = createNode(v);
	newNode->next = graph->adjList[u];
	graph->adjList[u] = newNode;
}

void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->numberOfVertices; ++v) {
        struct node *currentNode = graph->adjList[v];
        printf("Ders-%d: ", v+1);
        while (currentNode) {
            printf("%d -> ", currentNode->vertex+1);
            currentNode = currentNode->next;
        }
        printf("NULL\n");
    }
}

void onKosulHesapla(struct Graph* graph) {
    int v, count;
    for (v = 0; v < graph->numberOfVertices; ++v) {
        count = 0;
        struct node* currentNode = graph->adjList[v];
        while (currentNode) {
            count++;
            currentNode = currentNode->next;
        }
        printf("Ders-%d icin on kosullu ders sayisi: %d\n", v+1, count);
    }
}

void donem_sayisini_hesapla(struct Graph* graph, int numNodes) {
    int* inDegree = calloc(numNodes, sizeof(int));
    int* semester = calloc(numNodes, sizeof(int));
    int i;

    // Calculate in-degree for each node
    for (i = 0; i < numNodes; ++i) {
        struct node* currentNode = graph->adjList[i];
        while (currentNode) {
            inDegree[currentNode->vertex]++;
            currentNode = currentNode->next;
        }
    }

    // Queue for storing nodes with zero in-degree
    int* queue = malloc(numNodes * sizeof(int));
    int front = 0, rear = 0;

    // Add nodes with zero in-degree to the queue
    for (i = 0; i < numNodes; ++i) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Process the nodes in the queue
    while (front != rear) {
        int u = queue[front++];

        struct node* currentNode = graph->adjList[u];
        while (currentNode) {
            int v = currentNode->vertex;
            inDegree[v]--;

            // Update the semester for the dependent node
            if (semester[u] + 1 > semester[v])
                semester[v] = semester[u] + 1;

            if (inDegree[v] == 0)
                queue[rear++] = v;

            currentNode = currentNode->next;
        }
    }

    // Find the maximum semester
    int maxSemester = 0;
    for (i = 0; i < numNodes; ++i) {
        if (semester[i] > maxSemester)
            maxSemester = semester[i];
    }

    printf("\n\nOgrenci en erken %d donemde bolumden mezun olabilir\n", maxSemester);

    // Free allocated memory
    free(inDegree);
    free(semester);
    free(queue);
}



/*
0 0 0 0 0
1 0 0 0 0
0 0 0 0 0
0 1 0 0 0
0 0 1 1 0
*/

int main(){
	
	int n,e,i,j;
	printf("Kac tane ders secilecegini giriniz:"); scanf("%d",&n);
	printf("On kosulu olan ders sayisini giriniz:"); scanf("%d",&e);
	int adj[n][n];
	printf("On sart grafinin matrisini giriniz:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&adj[i][j]);
		}
	}
	printf("\n\n");
	struct Graph* graph = createGraph(n);
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(adj[i][j] == 1){
				addEdge(graph, i, j);
			}
		}
	}
	printGraph(graph);
	printf("\n\n");
	onKosulHesapla(graph);
	printf("\n\n");
	
	donem_sayisini_hesapla(graph, n);
	printGraph(graph);
	

	
	
	
	return 0;
}
