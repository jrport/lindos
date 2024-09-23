#include <stdio.h>
#include <stdlib.h>

struct Node {
  int valor;
  struct Node *proxNode;
};

struct LinkedList {
  int tamanho;
  struct Node *cabeca;
};

struct Node *createNode(int valor) {
  struct Node *node_ptr = malloc(sizeof(struct Node));
  if (!node_ptr) {
    fprintf(stderr, "error on memory allocation");
    exit(1);
  }

  node_ptr->valor = valor;
  node_ptr->proxNode = NULL;

  return node_ptr;
}

struct LinkedList *createList() {
  struct LinkedList *list_ptr = malloc(sizeof(struct LinkedList));
  if (!list_ptr) {
    fprintf(stderr, "error on memory allocation");
    exit(1);
  }

  list_ptr->tamanho = 0;
  list_ptr->cabeca = NULL;

  return list_ptr;
}

void appendNode(struct LinkedList *lista, int valor) {
  struct Node *curNode = lista->cabeca;
  struct Node *novo_node = createNode(valor);

  if (curNode == NULL) {
    lista->cabeca = novo_node;
    lista->tamanho++;
    return;
  }

  while (curNode->proxNode != NULL) {
    curNode = curNode->proxNode;
  }

  curNode->proxNode = novo_node;
  lista->tamanho++;
  return;
}

void printList(struct LinkedList *lista) {
  struct Node *curNode = lista->cabeca;
  if (curNode == NULL) {
    printf("lista vazia amg\n");
    return;
  }

  int index = 0;
  printf("---- inicio da lista ----\n");
  printf("index: %d | valor: %d\n", index, curNode->valor);
  while (curNode->proxNode != NULL) {
    curNode = curNode->proxNode;
    index++;
    printf("index: %d | valor: %d\n", index, curNode->valor);
  }
  printf("---- fim da lista ----\n");
  return;
}

void getNode(struct LinkedList *lista, int index) {
  struct Node *curNode = lista->cabeca;

  if (curNode == NULL) {
    printf("lista vazia amg\n");
    return;
  }

  if (lista->tamanho < index) {
    printf("index fora da lista\n");
    return;
  }

  int curIndex = 0;
  while (curIndex < index) {
    curNode = curNode->proxNode;
    curIndex++;
  }
  
  printf("index: %d | val: %d\n", index, curNode -> valor);
  return;
}

void insertNode(struct LinkedList *lista, int index, int valor) {
  struct Node* novo_node = createNode(valor);
  struct Node* antecessor = lista -> cabeca;

  if (index > lista -> tamanho) {
    printf("index fora da lista\n");
    return;
  }

  if (index == 0) {
    novo_node -> proxNode = lista -> cabeca;
    lista -> cabeca = novo_node;
    return;
  }

  for (int i = 0; i < index - 1; i++) { 
    antecessor = antecessor -> proxNode;
  }
  
  novo_node -> proxNode = antecessor -> proxNode;
  antecessor -> proxNode = novo_node;
}

void removeNode(struct LinkedList *lista, int index)
{
  if (lista ->tamanho < index) {
    printf("fezm merdqea");
    return;
  }  

  struct Node* antecessor = lista -> cabeca;
  if (index == 0) {
    lista -> cabeca = lista -> cabeca -> proxNode; 
    free(antecessor);
    return;
  }

  
  struct Node* alvo;
  for (int i = 0; i < index - 1; i++) { 
    antecessor = antecessor -> proxNode;
  }

  alvo = antecessor -> proxNode;
  antecessor -> proxNode = alvo -> proxNode;
  free(alvo);

  return;
}


void clearList(struct LinkedList* lista){
  // void*
  struct Node* curNode = lista -> cabeca;
  if (curNode == NULL) {
    printf("lista vazia");
    return;
  }

  struct Node* auxNode = lista -> cabeca;
  while (curNode -> proxNode != NULL) {
    curNode = curNode -> proxNode;
    free(auxNode);
    auxNode = curNode;
  }
  free(curNode);
  lista -> cabeca = NULL;

  return;
}

int main() {
  struct LinkedList *list_ptr = createList();
  insertNode(list_ptr, 0, 10);
  printList(list_ptr);

  appendNode(list_ptr, 90);
  appendNode(list_ptr, 30);
  appendNode(list_ptr, 50);
  printList(list_ptr);

  removeNode(list_ptr, 2);
  printList(list_ptr);

  return 0;
}
