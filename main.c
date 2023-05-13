#include<stdio.h>
#include<stdlib.h>
#include <time.h>
typedef struct Node{
	int value;
	struct Node *next;
}NODE;
NODE *dondur(NODE *head, int dondurme,int m){
	int count = 1;
	NODE *curr = head;
	NODE *prev;
	if(dondurme<0){
		printf("\nSOLA KAYDIRILIYOR...\n");
		dondurme = (-1)*dondurme;
		printf("\nDONDURME=>%d...\n",dondurme);
		while(count<dondurme && curr->next!=head){
			curr = curr->next;
			count++;
		}
		prev = curr;
		head = curr;
		while(curr->next != head){
			curr = curr->next;
		}
		curr = prev;
		return head;		
	}
	else{
		printf("\n\nSAGA KAYDIRILIYOR...\n");
		while(count<m-dondurme && curr->next!=head){
		    curr = curr->next;
		    count++;
	    }
	    head = curr;
	    prev = curr;
	    while(curr->next != head){
			curr = curr->next;
		}
		curr = prev;
	    return head;
	}
}
int donme_sayisi(int x1, int x2, int m){
	if(x1>x2){
		if((x1-x2) < m-(x1-x2)){
			printf("SAGA DOGRU %d KERE KAYDIRMA\n",x1-x2);
			return x1-x2;
		}else{
			printf("SOLA DOGRU %d KERE KAYDIRMA\n",m-x1+x2);
			return (-1)*(m-x1+x2);
		}
	}
	else{
		if((x2-x1) < m-(x2-x1)){
			printf("SOLA DOGRU %d KERE KAYDIRMA\n",x2-x1);
			return (-1)*(x2-x1);
		}else{
			printf("SAGA DOGRU %d KERE KAYDIRMA\n",m-x2+x1);
			return m-x2+x1;
		}
	}
}
int konum(NODE *ptr, int ortak){
	int count=1;
	NODE *tmp = ptr;
	while(ptr->next != tmp){
		if(ptr->value == ortak){
			return count;
		}
		ptr=ptr->next;
		count++;
	}
	return -1;
}
int ortak_eleman(int *sayilar, int n){
	int i,ortak;
	for(i=0;i<n;i++){
		if(sayilar[i] == 3){
			printf("\n\nORTAK ELEMAN ==>> %d\n",i+1);
			ortak = i+1;
			break;
		}
	}
	return ortak;
}
NODE* cark_olustur(NODE *ptr, int n, int *sayilar, int ortak_sayi, int m,int x,int q,int *sayilar2){
	int count = 2;
	NODE *tmp=ptr;
	int y;
	if(x==1){
		ptr->value = ortak_sayi;
	}
	while(count<=m){
        if(count == x){
        	ptr->next = (NODE*)malloc(sizeof(NODE));
        	ptr = ptr->next;
			ptr->value = ortak_sayi;
			ptr->next = NULL;
        	count++;
		}else{
			do{
				y=rand() % n + 1;
		    }while(y == ortak_sayi || sayilar[y-1] >= q || sayilar2[y-1] >= 1);
		    ptr->next = (NODE*)malloc(sizeof(NODE));
			ptr = ptr->next;
			ptr->value = y;
			if(count == m){
		    	ptr->next = tmp;
			}else{
				ptr->next = NULL;
			}
			count++;
			sayilar[y-1]++;
			sayilar2[y-1]++;
		}
	}
	return tmp;
}
int main(){
	int n,m,ortak_sayi,x1,x2,x3,i;
	do{
		printf("Sayi araligini giriniz: 1-"); scanf("%d",&n);
		printf("Bir carktaki sayi sayisini giriniz: "); scanf("%d",&m);
	}while(n<(2*m)-1 || m<3);
	int sayilar[n];
	for(i=0;i<n;i++){
		sayilar[i] = 0;
	}
	int sayilar2[n];
	for(i=0;i<n;i++){
		sayilar2[i] = 0;
	}		
    // Ortak sayiyi oluþturma
    srand(time(NULL));
    ortak_sayi = rand() % n + 1;
    sayilar[ortak_sayi - 1] = 3;
    // Ortak sayiyi yerlestirme
    x1 = rand() % m + 1;
    do {
        x2 = rand() % m + 1; 
    } while (x2 == x1); 
    do {
        x3 = rand() % m + 1;
    } while (x3 == x1 || x3 == x2);
    
    struct Node* head1 = (struct Node*)malloc(sizeof(struct Node));
    head1->value = rand() % n + 1;
    sayilar[head1->value-1]++;
    head1 = cark_olustur(head1,n,sayilar,ortak_sayi,m,x1,1,sayilar2);
    NODE *tmp = head1;
    tmp=head1;
    printf("\n");
    int count=0;
    while(count<m){
    	printf("%d->",tmp->value);
    	tmp = tmp->next;
    	count++;
	}
	printf("\n\n");
	for(i=0;i<n;i++){
		sayilar2[i] = 0;
	}
	struct Node* head2 = (struct Node*)malloc(sizeof(struct Node));
	head2->value =  rand() % n + 1;
	sayilar[head2->value-1]++;
    head2 = cark_olustur(head2,n,sayilar,ortak_sayi,m,x2,2,sayilar2);
    tmp=head2;
    count=0;
    while(count<m){
    	printf("%d->",tmp->value);
    	tmp = tmp->next;
    	count++;
	}
	printf("\n\n");	
	for(i=0;i<n;i++){
		sayilar2[i] = 0;
	}
    struct Node* head3 = (struct Node*)malloc(sizeof(struct Node));
    head3->value =  rand() % n + 1;
    sayilar[head3->value-1]++;
    head3 = cark_olustur(head3,n,sayilar,ortak_sayi,m,x3,2,sayilar2);
    tmp = head3;
    tmp=head3;
    count=0;
    while(count<m){
    	printf("%d->",tmp->value);
    	tmp = tmp->next;
    	count++;
	}		
    ortak_sayi = ortak_eleman(sayilar,n);
    x1 = konum(head1,ortak_sayi);
    printf("1. listede ortak sayinin konumu:%d\n",x1);
    x2 = konum(head2,ortak_sayi);
    printf("2. listede ortak sayinin konumu:%d\n",x2);
    x3 = konum(head3,ortak_sayi);
	printf("3. listede ortak sayinin konumu:%d\n",x3);	
	int donme1 = donme_sayisi(x1, x2, m);
	int donme2 = donme_sayisi(x1, x3, m);
	head2 = dondur(head2,donme1,m);
    tmp=head2->next;
    count=0;
    while(count<m){
    	printf("%d->",tmp->value);
    	tmp = tmp->next;
    	count++;
	}
	printf("\n\n");
	head3 = dondur(head3,donme2,m);
    tmp = head3->next;
    count = 0;
    while(count<m){
    	printf("%d->",tmp->value);
    	tmp = tmp->next;
    	count++;
	}
	printf("\n\n");	
	return 0;
}
