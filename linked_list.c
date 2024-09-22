#include <stdio.h>
#include <stdlib.h>
#define MAX 11

struct Node
{
	int valor;
	struct Node *nextNode;
};

struct LinkedList
{
	int tamanho;
	struct Node *head;
};

int ehVazia(struct LinkedList *lista) {
	if (lista->head == NULL){
		return 1;
	}
	return 0;
}

int getNode(struct LinkedList *lista, int index) 
{
	if (ehVazia(lista)) {
		printf("vazia irmao sai");
		return -1;
	}	

	int cur_index = 0;
	struct Node *cur_node = lista -> head;
	while (cur_index != index) {
		cur_index ++;
		cur_node = cur_node -> nextNode;	
	}	
	
	int target_val = cur_node -> valor;
	return target_val;
}

void printLista(struct LinkedList *lista) 
{
	if (ehVazia(lista)) {
		printf("lista vazia!");
		return;
	}

	struct Node *curNode = lista -> head;
	int index = 0;
	printf("-- inicio da lista ---\n");
	while (curNode != NULL) {
		printf("indice: %d | valor: %d\n", index, curNode -> valor);
		index ++;
		curNode = curNode -> nextNode;
	}	
	printf("-- fim da lista ---\n");

}

struct LinkedList* initializeList() {
	struct LinkedList *nova_lista = malloc(sizeof(struct LinkedList)); 

	if (!nova_lista) {
		printf("fudeu");
		exit(1);
	}
	nova_lista -> head = NULL;
	nova_lista -> tamanho = 0;
	return nova_lista;
}

struct Node* createNode(int val) {
	struct Node *newNode = malloc(sizeof(struct Node));
	newNode -> valor = val;
	newNode -> nextNode = NULL;

	return newNode;
}

void appendNode(struct LinkedList *lista, int val) 
{
	struct Node *newNode = createNode(val);

	if (ehVazia(lista)) {
		lista -> head = newNode;
		return;
	}

	struct Node *curNode = lista -> head;
	while (curNode -> nextNode != NULL) {
		curNode = curNode -> nextNode;
	}	

	curNode -> nextNode = newNode;
	return;
}

void removeNode(struct LinkedList *lista, int index) {
	// caso da remocao da head

	if (ehVazia(lista)) {
		printf("fodeu");
		return;
	}

	int curIndex = 0;
	struct Node *antecessor = lista -> head;

	while (curIndex + 1 != index) {
		curIndex ++;
		antecessor = antecessor -> nextNode;	
	}

	struct Node *a_ser_deletado = antecessor -> nextNode;
	antecessor -> nextNode = antecessor -> nextNode -> nextNode;
	// antecessor -> nextNode = sucessor;
	free(a_ser_deletado);	

	return;
}


void insertNode(struct LinkedList *lista,  int val, int index) {
	if (ehVazia(lista)) {
		printf("fodeu");
		return;
	}

	int curIndex = 0;
	struct Node *curNode = lista -> head;

	while (curIndex + 1 != index) {
		curIndex ++;
		curNode = curNode -> nextNode;	
	}

	struct Node *newNode = createNode(val);
	newNode -> nextNode = curNode -> nextNode;
	curNode -> nextNode = newNode;

	return;
}

int main() 
{
	struct LinkedList *minha_lista = initializeList();
	int vazio = ehVazia(minha_lista);
	if (vazio) {
		printf("Ta vazio mestre\n");
	}

	appendNode(minha_lista, 10);
	appendNode(minha_lista, 50);
	appendNode(minha_lista, 38);
	printLista(minha_lista);
	
	insertNode(minha_lista, 999, 1);
	printLista(minha_lista);

	removeNode(minha_lista, 2);
	printLista(minha_lista);

	// limpeza(minha_lista);
	// free em tudo

	return 0;
}
