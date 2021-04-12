#include <stdio.h>
#include <stdlib.h>
#define MAX 7

typedef int itemType;
typedef struct {
	itemType data[MAX];
	int front;
	int rear;
	int count;
} queue;

typedef struct {
	itemType data[MAX];
	int count;
} stack; 

void initialisasiS(stack *s);
void initialisasiQ(queue *q);

int penuhS(stack *s);
int kosongS(stack *s);

void push(itemType x, stack *s);
itemType pop(stack *s);

void normalisasiQueue(int y, stack *s, queue *q);

int penuhQ(queue *q);
int kosongQ(queue *q);

void tambah(queue *q);
void enqueue(itemType x, queue *q);

void ambil(stack *s, queue *q);
itemType dequeue(itemType x, stack *s, queue *q);

void tampil(queue *q);

void menu(queue *q, stack *s);
int pilihan;
int nopol = 0;

int main(){
	queue q;
	stack s;
	itemType x;
	
	initialisasiS(&s);
	initialisasiQ(&q);
	
	do {
		menu(&q, &s);
	} while(pilihan != 4);
}

void menu(queue *q, stack *s){
	printf("========================\n");
	printf(" Menu Parkiran\n");
	printf("========================\n");
	printf("1. Tambah Mobil\n");
	printf("2. Keluarkan Mobil\n");
	printf("3. Tampilkan Mobil\n");
	printf("4. Keluar\n");
	printf("%-25s", "Pilih Menu"); printf(": ");
	scanf("%d", &pilihan);
	fflush(stdin);
	
	if(q->count == 0 && pilihan >= 2 && pilihan <= 3)
		printf("Parkiran masih kosong gan :)\n");
	else {
		switch(pilihan){
			case 1:
				tambah(q);
				break;
			case 2:
				ambil(s, q);
				break;
			case 3:
				tampil(q);
				break;
		}
	}
	
}
 
void initialisasiS(stack *s) {
	s->count =  0;
}
void initialisasiQ(queue *q) {
	q->count = 0;
	q->front = 0;
	q->rear  = 0;
}

int penuhS(stack *s) {
	return(s->count == MAX);
}
int kosongS(stack *s) {
	return(s->count == 0);
}

void push(itemType x, stack *s) {
	if(penuhS(s)){
		printf("Tampungan Stack Penuh\n");
	} else {
		s->count++;
		s->data[s->count] = x;
	}
}

itemType pop(stack *s) {
	itemType x;
 
 	if(kosongS(s)){
 		printf("Tampungan Stack Kosong\n");
	} else {
		x = s->data[s->count];
	 	s->count--;
	 	return(x);
	}
}

int penuhQ(queue *q) {
	return(q->count==MAX);
}
int kosongQ(queue *q) {
	return(q->count==0);
}

void normalisasiQueue(int y, stack *s, queue *q){
	do{
		q->data[y]=q->data[y+1];
  		y++;
 	} while(y < q->rear);
 
 	q->rear--;
 	q->count--;
 
 	do{
  		q->front--;
  		q->data[q->front]=pop(s);
  		q->count++; 
 	} while(s->count != 0);
}

void tambah(queue *q){
	itemType x;
	
	nopol = nopol + 1;
	x = nopol;
	
	enqueue(x, q);
}

void enqueue(itemType x, queue *q) {
	if(penuhQ(q)){
		printf("Parkiran Penuh Gan \n");
		nopol = nopol - 1;
	} else {
		q->data[q->rear] = x;
		(q->rear)++;
		(q->count)++;
	}
}

void ambil(stack *s, queue *q){
	itemType x;
	
	printf("%-25s", "Mobil yang keluar"); printf(": ");
	scanf("%d", &x);
	fflush(stdin);
	
	dequeue(x, s, q);
}

int cek_data(itemType x, queue *q) {
	int i, hasil = -1;
	
 	for(i=q->front; i<q->rear; i++){
		if(q->data[i] == x){
   			hasil = i;
   			break;
  		} 
 	}
	
 	return(hasil);
}

itemType dequeue(itemType x, stack *s, queue *q) {
	int y, i;
	if(kosongQ(q)){
		printf("Parkiran Kosong Gan\n");
	} else {
		if(cek_data(x, q) == -1){
			printf("Mobil yang dicari tidak ada\n");
		} else if((cek_data(x, q) == q->front) && (q->count>1)){
			q->front++;
  			q->count--;
		} else if((cek_data(x, q) == q->front) && (q->count==1))
			initialisasiQ(q);
		else {
			y=cek_data(x,q);
  			printf("\nMobil yang keluar sementara : \n");
		  	for(i=q->front; i<y; i++){
		  		printf("- Mobil %d\n", q->data[i]);
		   		push(q->data[i], s);
		   		q->front++;
		   		q->count--;
		  	}
		  	normalisasiQueue(y,s,q);
		}
	}
}

void tampil(queue *q) {
	int i, j, y;
	itemType x;
	
	j = q->front;
	y = q->count;
	
	for(i=0; i<MAX; i++){
		if(y == 0)
			break;
		else {
			x = q->data[j];
			j = (j + 1) % MAX;
			y--;
			printf("%d ", x);
		}
	}
	printf("\n");
}
