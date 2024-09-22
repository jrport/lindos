#include <stdio.h>
#include <stdlib.h>

struct Tuple {
  int val;
  int key;
};

struct HashTable {
  struct Tuple *table_ptr[7];
};

struct Tuple *createTuple(int key, int val) {
  struct Tuple *new_tuple = malloc(sizeof(struct Tuple));
  if (!new_tuple) {
    printf("error on mem alloc");
    exit(1);
  }

  new_tuple->key = key;
  new_tuple->val = val;
  return new_tuple;
}

int keyAlphabetValue(char key) {
  if (key > 99) {
    printf("so pode maisculo");
    exit(1);
  }

  int position = key - 64;
  int hash_key = ((key * key) + key) % 7;

  return hash_key;
}

struct HashTable *initializeHashTable() {
  struct HashTable *nova_table = malloc(sizeof(struct HashTable));

  for (int i = 0; i < 7; i++) {
    nova_table->table_ptr[i] = NULL;
  }

  return nova_table;
}

int GetKey(struct HashTable *hash_table, char key) {
  int hashed_key = keyAlphabetValue(key);

  struct Tuple *key_pair_ptr = hash_table->table_ptr[hashed_key];
  if (key_pair_ptr == NULL) {
    printf("tem nada aqui amigo\n");
    return -1;
  }

  int val;
  val = key_pair_ptr -> val;
  while (key_pair_ptr -> key != key && key_pair_ptr -> key != -1) {
    hashed_key++;
    if (hashed_key == 6) {
      printf("nao tem irmao\n");    
      return -1;
    }
    key_pair_ptr = hash_table->table_ptr[hashed_key];
    // if (key_pair_ptr == NULL || hashed_key == 6) {
    //     printf("nao tem irmao\n");    
    //     return -1;
    // }
    val = key_pair_ptr -> val;
  }
  return val;
}

void removeTuple(struct HashTable *hash_table, char key) 
{
  int hashed_key = keyAlphabetValue(key);
  struct Tuple **arr_tuple_ptr = &(hash_table->table_ptr[hashed_key]);
  struct Tuple *key_pair_ptr = hash_table->table_ptr[hashed_key];

    if (key_pair_ptr->key == key) {
        free(key_pair_ptr);
        *arr_tuple_ptr = createTuple(-1, -1);
    }
    
    return;
}

void InsertTuple(struct HashTable *hash_table, char key, int val) {
  int hashed_key = keyAlphabetValue(key);
  struct Tuple **key_pair_ptr = &(hash_table->table_ptr[hashed_key]);
  struct Tuple *new_tuple_ptr = createTuple(key, val);

  while (*key_pair_ptr != NULL) {
    hashed_key++;
    if (hashed_key < 7) {
      key_pair_ptr = &(hash_table->table_ptr[hashed_key]);
    }else {
      printf("no more space for dick");
    }
  }

  *key_pair_ptr = new_tuple_ptr;
}

void printTable(struct HashTable *hash_table) {
  struct Tuple *key_pair_ptr = hash_table->table_ptr[0];

  for (int cur_index = 0; cur_index < 7; cur_index++) {
    key_pair_ptr = hash_table->table_ptr[cur_index];
    printf("index: %d | key: %d | value: %d", cur_index, key_pair_ptr->key,
           key_pair_ptr->val);
  }
}

int main() {
  struct HashTable *hash_table = initializeHashTable();
  InsertTuple(hash_table, 'P', 99);
  int val = GetKey(hash_table, 'P');
  printf("val %d\n", val);
  InsertTuple(hash_table, 'I', 2);
  val = GetKey(hash_table, 'I');
  printf("val %d\n", val);
  InsertTuple(hash_table, 'D', 50);
  val = GetKey(hash_table, 'D');
  printf("val %d\n", val);
  removeTuple(hash_table, 'I');
  val = GetKey(hash_table, 'D');
  printf("val %d\n", val);
  InsertTuple(hash_table, 'B', 22);
  val = GetKey(hash_table, 'B');
  printf("val %d\n", val);

  return 0;
}
