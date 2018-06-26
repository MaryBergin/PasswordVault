
/**
 * @file HashTableAPI.c
 * @author Mary Bergin
 * @date June 25th 2018
 * @Implementation of a Hash Table
 */
#include "HashTableAPI.h"



HTable *createTable(size_t size,
  int (*hashFunction)(size_t tableSize, char key[25]),
  void (*destroyData)(void *data),
  void (*printData)(void *toBePrinted)){

    HTable *newTable;
    newTable = malloc(sizeof(HTable));

    newTable->table = calloc(size, sizeof(Node));

    newTable->hashFunction = hashFunction;
    newTable->destroyData = destroyData;
    newTable->printData = printData;
    newTable->size = size;

    return newTable;


  }

Node *createNode(char key[25], void *data){

  Node *newNode;

  newNode = malloc(sizeof(Node));


  strcpy(newNode->key, key);
  newNode->next = NULL;
  newNode->data = data;


  return newNode;

}

void destroyTable(HTable *hashTable){


  int i;
  Node *temp;
  Node *delete;


  if(hashTable!=NULL){
    for(i=0; i<=hashTable->size; i++){

      temp = hashTable->table[i];

      while(temp!= NULL){

        delete = temp;
        temp = temp->next;
        hashTable->destroyData(delete->data);
        free(delete);
      }


    }

  free(hashTable->table);

  }


  free(hashTable);

}

void insertData(HTable *hashTable, char key[25], void *data){


  int i;


  key[strlen(key)-1] = '\0';


  if(hashTable !=NULL){

    Node *newNode = createNode(key, data);

    Node *tempNode = malloc(sizeof(Node));

    i = hashTable->hashFunction(hashTable->size, key);



    if(hashTable->table[i]!=NULL){
      //Checks first element else adds to end
      if(hashTable->table[i]->key == key){

      hashTable->table[i] = newNode;

      }
      else{

        tempNode = hashTable->table[i];
        while(tempNode->next !=NULL){
          tempNode = tempNode->next;
        }
        tempNode->next = newNode;
        newNode->next = NULL;


      }
    }

    else{

      hashTable->table[i] = newNode;

    }



  }

}

void removeData(HTable *hashTable, char key[25]){


  int i;

  Node *newNode;
  Node *temp;


  if(hashTable!=NULL){

    i = hashTable->hashFunction(hashTable->size, key);

    if(hashTable->table[i]!= NULL){

      newNode = hashTable->table[i];
      temp = NULL;


      while(newNode->key != key){

        temp = newNode;
        newNode = newNode->next;
      }

      if(newNode->key == key){
        //if head of list
        if(temp == NULL){

          hashTable->table[i]= hashTable->table[i]->next;


          hashTable->destroyData(newNode->data);
          free(newNode);

        }
        else{

          temp->next = newNode->next;
          hashTable->destroyData(newNode->data);
        }
      }

    }
  }
}

void *lookupData(HTable *hashTable, char key[25]){



  int i;


  if(hashTable != NULL){

    i = hashTable->hashFunction(hashTable->size, key);

    if(hashTable->table[i] == NULL){

      return NULL;
    }



    Node *tempNode;
    tempNode = hashTable->table[i];

    while(tempNode!=NULL){

      if(strcmp(tempNode->key, key) == 0){


        return tempNode->data;
      }

      tempNode = tempNode->next;

    }
  }

  return NULL;

}
