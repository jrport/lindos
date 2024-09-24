#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;                  // 4bytes
  char key;                 // 1byte
  struct Node *nextNodePtr; // 8bytes
} Node;

typedef struct hashTable {
  Node *table[10];
} hashTable;

Node *createNode(char key, int val) {
  Node *new_node = malloc(sizeof(Node));
  if (!new_node) {
    printf("error on mem allcoation");
    exit(EXIT_FAILURE);
  }

  new_node->key = key;
  new_node->val = val;
  new_node->nextNodePtr = NULL;
  return new_node;
}

hashTable *initTable() {
  hashTable *new_table_ptr = malloc(sizeof(hashTable));

  for (int i = 0; i < 10; i++) {
    new_table_ptr->table[i] = NULL;
  }

  return new_table_ptr;
}

// (k2 + k) % 10
// 97
int hashingFunc(char key) {
  int hashIndex = ((key * key) + key) % 10;
  return hashIndex;
}

void insertKeyVal(hashTable *hashtable_ptr, char key, int val) {
  int hashedIndex = hashingFunc(key);
  Node *new_node_ptr = createNode(key, val);

  if (hashtable_ptr->table[hashedIndex] == NULL) {
    hashtable_ptr->table[hashedIndex] = new_node_ptr;
    return;
  }

  Node *target_table_ptr = hashtable_ptr->table[hashedIndex];
  while (target_table_ptr->nextNodePtr != NULL) {
    target_table_ptr = target_table_ptr->nextNodePtr;
  }

  target_table_ptr->nextNodePtr = new_node_ptr;
  return;
}

// [&1 &2 &3 &4] = -> soma do comprimento de todos os enderecos
// soma do comprimento de todos os enderecos / comprimento de 1 endereco
//  -> a qtd de enderecos
void printTable(hashTable *hashtable_ptr) {
  /* int hashtable_len = sizeof(hashtable_ptr -> table) / sizeof(Node*); */
  int hashtable_len = 10;

  printf("---- inicio da table ----\n");
  for (int i = 0; i < hashtable_len; i++) {
    Node *cur_ptr = hashtable_ptr->table[i];
    if (cur_ptr == NULL) {
      printf("index %d vazio\n", i);
      continue;
    }
    while (cur_ptr != NULL) {
      printf("index: %d | key: %c | val: %d -> ", i, cur_ptr->key,
             cur_ptr->val);
      cur_ptr = cur_ptr->nextNodePtr;
    }
    printf("\n");
  }
  printf("---- fim da table ----\n");
}

void printKey(hashTable *table_ptr, char key) {
  int hashed_key = hashingFunc(key);

  if (table_ptr->table[hashed_key] == NULL) {
    printf("não ta aqui\n");
    return;
  }

  Node* curNode_ptr = table_ptr -> table[hashed_key];
  if (curNode_ptr->key == key) {
    printf("key: %c | val: %d\n", curNode_ptr->key, curNode_ptr->val);
    return;
  } 
  while (curNode_ptr -> nextNodePtr != NULL) {
    curNode_ptr = curNode_ptr -> nextNodePtr;
    if (curNode_ptr->key == key) {
      printf("key: %c | val: %d\n", curNode_ptr->key, curNode_ptr->val);
      return;
    } 
  }
  
  printf("nao tem amg\n");
}

void removeKey(hashTable* table_ptr, char key)
{
  int hashed_key = hashingFunc(key);

  if (table_ptr->table[hashed_key] == NULL) {
    printf("não ta aqui\n");
    return;
  }

  Node* antecessor_ptr = table_ptr -> table[hashed_key];
  Node* matador_ptr = table_ptr -> table[hashed_key];
  
  // quero matar a cabeca
  if (antecessor_ptr->key == key) {
    table_ptr -> table[hashed_key] = table_ptr -> table[hashed_key] -> nextNodePtr;
    free(matador_ptr);
    return;
  } 

  // quero encontrar o membro pra matar salvando os filhos
  while (antecessor_ptr -> nextNodePtr != NULL) {
    /* antecessor_ptr = antecessor_ptr -> nextNodePtr; */
    matador_ptr = matador_ptr -> nextNodePtr;
    if (matador_ptr->key == key) {
      antecessor_ptr -> nextNodePtr = matador_ptr -> nextNodePtr;
      free(matador_ptr);
      return;
    } 

    antecessor_ptr = antecessor_ptr -> nextNodePtr;
  }
  
  printf("nao tem amg\n");

}

int main() {
  hashTable *new_table_ptr = initTable();
  insertKeyVal(new_table_ptr, 'd', 10);
  insertKeyVal(new_table_ptr, 'h', 90);
  insertKeyVal(new_table_ptr, 'a', 70);
  printTable(new_table_ptr);

  removeKey(new_table_ptr, 'd');
  printTable(new_table_ptr);
}
