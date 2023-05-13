#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
void push(int item, int *stak, int *q, int n) {
  if (*q == n - 1) { // stack dolu ise
    printf("Stack overflow\n");
    return;
  }
  (*q)++;
  stak[*q] = item;
  
}

int pop(int *stak, int *q) {
  if (*q == -1) { // stack boþ ise
    printf("Stack underflow\n");
    return -1;
  }
  int i;
  i = *q;
  (*q)--;
  return stak[i];
}

typedef struct Node{
	int value,strength;
	struct Node *left, *right;
}NODE;

typedef struct Trunk{
    struct Trunk* prev;
    char* str;
}Trunk;

void showTrunks(Trunk* p){
    if (p == NULL) {
        return;
    }
    showTrunks(p->prev);
    printf("%s", p->str);
}

Trunk* newTrunk(Trunk* prev, char* str){
    Trunk* trunk = (Trunk*) malloc(sizeof(Trunk));
    trunk->prev = prev;
    trunk->str = strdup(str);
    return trunk;
}

void printTree(NODE* root, Trunk* prev, int isLeft){
    if (root == NULL) {
        return;
    }

    char* prev_str = "    ";
    Trunk* trunk = newTrunk(prev, prev_str);

    printTree(root->right, trunk, 1);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf(" %d(%d)\n", root->value,root->strength);

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, 0);
}

NODE *newNode(int x, int y){
	NODE *tmp;
	tmp = (NODE*)malloc(sizeof(NODE));
	tmp->value = x;
	tmp->strength = y;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}

NODE *insert(NODE *root, int x, int y){
	if(root == NULL)
		return newNode(x,y);
	
	if(x < root->value)
	    root->left = insert(root->left,x,y);
	else
	    root->right = insert(root->right,x,y);
	
	return root;
}

int atisYap(NODE *root, int k, int p){
	if(root->value == k){
		root->strength -= p;
		return root->strength;
	}else{
		if(k<root->value){
			if(root->left == NULL){
				return -100;
			}
			atisYap(root->left,k,p);
		}else if(k>root->value){
			if(root->right == NULL){
				return -100;
			}
			atisYap(root->right,k,p);
		}
	}
}

NODE* minValueNode(NODE* node){
    NODE* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

NODE* deleteNode(NODE* root, int k){
    if(root == NULL)
        return root;
    if(k < root->value){
        root->left = deleteNode(root->left, k);
    }else if(k > root->value){
        root->right = deleteNode(root->right, k);
    }else{
    	if(root->left == NULL && root->right == NULL){
    		NODE* temp = NULL;
    		free(root);
            return temp;
		}
        else if(root->left == NULL) {
            NODE* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return temp;
        }
        NODE* temp = minValueNode(root->right);
        root->value = temp->value;
        root->strength = temp->strength;

        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

int main(){
	int n,m;
	printf("Maksimum meyve araligini giriniz:1-"); scanf("%d",&n);
	printf("Meyve sayisini giriniz:"); scanf("%d",&m);
	int sayilar[n];
	
	int stack[m]; // stack'in tutulacaðý dizi
    int top = -1; // stack'in en üstündeki elemanýn indeksi
    
    int stack2[m]; // stack'in tutulacaðý dizi
    int top2 = -1; // stack'in en üstündeki elemanýn indeksi
    
	NODE *root = NULL;
	int i;
	for(i=0;i<n;i++){
		sayilar[i] = 0;
	}
	int x,y;
	i=0;
	srand(time(NULL));
	
	do{
		x = rand() % n + 1;
		y = x;
		if(sayilar[x-1] == 0){
		    root = insert(root,x,y);
		    sayilar[x-1]++;
		    i++;
		}
	}while(i<m);
	printTree(root, NULL, 0);
	int guc;
	int k,p; // k=>atýþ yapýlacak meyve   p=>atýþ gücü
	
	while(root!=NULL){
		printf("Atis yapacaginiz meyve numarasini giriniz:");scanf("%d",&k);
		printf("Atis gucunuzu giriniz:");scanf("%d",&p);
		guc = atisYap(root,k,p);
		if(guc == -100){
			printf("\nAgacta olmayan bir eleman girdiniz!\n\n");
		}else{
		 if(guc<=0){
			root = deleteNode(root,k);
			push(k,stack,&top,m);
		}
		 if(root != NULL){
			printTree(root, NULL, 0);
		}
	}
	}
	for(i=0;i<m;i++){
		x = pop(stack,&top);
		push(x,stack2,&top2,m);
	}
	printf("\n");
	for(i=0;i<m;i++){
		x = pop(stack2,&top2);
		printf("%d ",x);
	}
	return 0;
}

