/**
 * @file PasswordVault.c
 * @author Mary Bergin
 * @date June 25th 2018
 * @PasswordVault functions
 */

#include "HashTableAPI.h"
#include "PasswordVault.h"

int hashFunction(size_t tableSize, char key[25]){

  int i;
  int sum = 0;

  for( i = 0; i<=strlen(key); i++){

    sum += key[i];

  }

  return(sum % tableSize);

}


int authorize(HTable *hashTable, char key[25], char password[10]){


  char password1[25];

  strcpy(password1, lookupData(hashTable, key));

  if(strcmp(password1, password) == 0){
    return 1;
  }
  else{

    return 0;
  }
  return 0;
}


void newFile(char fileName[25], char password[10]){



  FILE *fp;
  char extension[25] = "bin";
  char key[25];

  strcpy(key, fileName);
  fileName[strlen(fileName) - 1] ='.';
  strcat(fileName, extension);

  fp = fopen( fileName, "wb");
  fclose(fp);


  HTable *hashTable = malloc(sizeof(HTable));

  hashTable = createTable(11, hashFunction, destroyData, printData);

  insertData(hashTable, key, password);

  secondMenu(hashTable, key);


}

HTable *loadFile(char fileName[25], char password[10]){


  ;
  FILE *fp;
  char extension[25] = "bin";
  char file[25];
  char fileData[10];
  char key[525];
  int count = 0;
  strcpy(file, fileName);
  file[strlen(file) - 1] ='.';

  strcat(file, extension);


  fp = fopen( file, "rb");




  HTable *hashTable = createTable(11, hashFunction, destroyData, printData);

  while( !feof(fp) ){


    count++;


    fgets(key,50,fp);

    fgets(fileData,50,fp);
    fileData[strlen(fileData)-1] = '\0';

    insertData(hashTable, key, fileData);


  }
  fclose(fp);

  return hashTable;
}


void updatePassword(HTable *hashTable, char key[25], void *data){

  int i;


  if(hashTable != NULL){

    i = hashTable->hashFunction(hashTable->size, key);

    if(hashTable->table[i] == NULL){

      return;
    }



    Node *tempNode;
    tempNode = hashTable->table[i];

    while(tempNode!=NULL){

      if(strcmp(tempNode->key, key) == 0){

        tempNode->data = data;
      }

      tempNode = tempNode->next;

    }
  }

}

void removePassword(){


}

void saveToFile(HTable *hashTable, char fileName[25]){


  int i;
  FILE *fp;
  char extension[25] = "bin";
  char key[25];
  char fileData[10];

  strcpy(key, fileName);
  fileName[strlen(fileName) - 1] ='.';
  strcat(fileName, extension);

  fp = fopen( fileName, "wb");


  Node *tempNode = malloc(sizeof(Node));
  for( i=0; i<=hashTable->size; i++){

    while(hashTable->table[i] != NULL){

      strcpy(fileData, (char*)hashTable->table[i]->data);
      tempNode = hashTable->table[i];
      fprintf(fp, "%s %s\n", hashTable->table[i]->key, fileData);


      if(tempNode->next != NULL){
        tempNode = tempNode->next;
      }
      i++;
    }
 }

  fclose(fp);


}
