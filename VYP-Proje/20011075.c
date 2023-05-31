#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char data;
    bool isEndOfWord;
    struct Node *children[10];
    char *word;
};

struct Node *createNode(char data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->isEndOfWord = false;
    int i;
    for (i = 0; i < 10; i++) {
        newNode->children[i] = NULL;
    }
    
    return newNode;
}

void agacaEkle(const char *str, struct Node *root) {
    int i;
    struct Node *curr = root;

    for (i = 0; i < strlen(str); i++) {
        int rep;
        if (str[i] >= 'a' && str[i] <= 'c') {
            rep = 2;
        }
        else if (str[i] >= 'd' && str[i] <= 'f') {
            rep = 3;
        }
        else if (str[i] >= 'g' && str[i] <= 'i') {
            rep = 4;
        }
        else if (str[i] >= 'j' && str[i] <= 'l') {
            rep = 5;
        }
        else if (str[i] >= 'm' && str[i] <= 'o') {
            rep = 6;
        }
        else if (str[i] >= 'p' && str[i] <= 's') {
            rep = 7;
        }
        else if (str[i] >= 't' && str[i] <= 'v') {
            rep = 8;
        }
        else if (str[i] >= 'w' && str[i] <= 'z') {
            rep = 9;
        }
        
        if (curr->children[rep] == NULL) {
            curr->children[rep] = createNode(rep);
        } 
       	curr = curr->children[rep];
    }

    if(curr->isEndOfWord) {
    	struct Node *tmp = createNode('#');
    	curr->children[0] = tmp;
    	tmp->word = malloc(strlen(str) + 1);
        strcpy(tmp->word, str);
    }else {
        curr->isEndOfWord = true;
        curr->word = malloc(strlen(str) + 1);
        strcpy(curr->word, str);
    }

}


void sayiyaKarsilikAra(const char *numara, struct Node *root) {
	struct Node *curr = (struct Node *)malloc(sizeof(struct Node));
    curr = root;
    int i;
    int flag = 0;
    for(i=0; i<strlen(numara) && (flag!=1);i++){
    	int num = numara[i] - '0';
    	if(curr->children[num] == NULL){
    		flag = 1;
		}else{
			curr = curr->children[num];
		}
    }
    if(flag == 0 && curr->isEndOfWord){
    	printf("%s\n",curr->word);
    	if (curr->children[0] != NULL && curr->children[0]->data == '#') {
            printf("%s\n", curr->children[0]->word);
        }
	    
	}else{
		printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
	}
}


int main(){
	int MAX_KELIME_SAYISI = 16;
	int MAX_KELIME_UZUNLUGU = 20;
	
	FILE *dosya;
    char kelime[MAX_KELIME_UZUNLUGU];
    char kelimeListesi[MAX_KELIME_SAYISI][MAX_KELIME_UZUNLUGU];
    int i = 0;
    int j;

    dosya = fopen("Metin.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }

    while (fscanf(dosya, "%s", kelime) != EOF) {
        strcpy(kelimeListesi[i], kelime);
        i++;
    }

     
    fclose(dosya);
    
    struct Node *root = createNode(-1);
    for (j = 0; j < i; j++){
    	agacaEkle(kelimeListesi[j], root);
	}	

	char flag[MAX_KELIME_UZUNLUGU];
	
	do{
		printf("Cikmak icin q girin:\n");
        scanf("%s", flag);

       if(strcmp(flag, "q") != 0) {
            sayiyaKarsilikAra(flag, root);
       }
	}while(strcmp(flag, "q")!=0);
	
	 
	return 0;
}
