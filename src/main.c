/**
 * @file main.c
 * @author Mary Bergin
 * @date June 25th 2018
 * @Implementation of the Password Vault
 */
#include "HashTableAPI.h"
#include "PasswordVault.h"

void destroyData (void *data){

  free(data);

  return;

}

void printData( void *toBePrinted){



  printf("Result: %s\n\n", (char*)toBePrinted );

  return;

}

void existingUser(char fileName[25], char password[10]){

  int a = 0;
  printf("hi\n");


  HTable *hashTable = loadFile(fileName, password);

  fileName[strlen(fileName)-1] = '\0';
  a = authorize(hashTable, fileName, password);
  secondMenu(hashTable, fileName);
  if(a == 1){
    secondMenu(hashTable, fileName);

  }
  else{

    secondMenu(hashTable,fileName);

  }
}

void newUser(){

  char fileName[25];
  char password[10];



  printf("\tPlease choose your file name:\n");
  fgets(fileName, 25, stdin);


  printf("\tPlease choose you password:\n");
  fgets(password, 10, stdin);


  newFile(fileName, password);


}

void secondMenu(HTable *hashTable, char fileName[25]){

  int a;
  int b = 0;
  char key[15];

  char password[25];


  printf("\t***************************\n");
  printf("\t\tWelcome!\n");
  printf("\t***************************\n\n");
  while(b!=1){
  printf("\tPlease choose one of the following options:\n\n");
  printf("\t1. Retrieve a Password\n");
  printf("\t2. Add a New Password\n");
  printf("\t3. Update Existing Password\n");
  printf("\t4. Remove Existing Password\n");
  printf("\t5. Save and Exit\n");

  scanf("%d", &a);
  getchar();

  switch (a){

    case 1 :
      printf("\tPlease enter the identifier for the password you are looking for:\n");
      fgets(key, 15, stdin);

      strcpy(password, lookupData(hashTable, key));
      key[strlen(key)-1] = '\0';

      if(password == NULL){
        printf("Sorry that password doesn't exist please try another one!\n");
      }

      printf("\n\tYour password for %s, is: %s\n\n\n", key, password);
      secondMenu(hashTable, fileName);
      b = 1;

      break;

    case 2 :
      printf("\tPlease enter an identifier for your password:\n");
      fgets(key, 15, stdin);

      printf("\tPlease enter the password you would like to add:\n");
      fgets(password, 25, stdin);
      insertData(hashTable, key, password);
      secondMenu(hashTable, fileName);
      b = 1;
      break;

    case 3:
      printf("\tPlease enter the identifier for the password you would like to updata:\n");
      fgets(key, 15, stdin);

      printf("\tPlease enter your new password:\n");
      fgets(password, 25, stdin);

      updatePassword(hashTable, key, password);
      printf("Your password is updated!\n");
      secondMenu(hashTable, fileName);
      b = 1;
      break;

    case 4:
      printf("Please enter the identifier for the password you would like to remove:\n");
      fgets(key, 15, stdin);

      removeData(hashTable, key);
      secondMenu(hashTable, fileName);
      b = 1;
      break;
    case 5:
      printf("Thank you for using Password Vault!\n");
      saveToFile(hashTable, fileName);
      return;

    default:
      printf("Sorry! That was not a valid option please try again!\n\n");
  }


  }
}

int main(){


  int a, b;
  char password[10];
  char fileName[25];

  printf("\n\t**********************************\n");
  printf("\t\tWelcome to your Password Vault!\n");
  printf("\t**********************************\n\n");
  while(b != 1){

    printf("\tPlease select one of the following options:\n\n");
    printf("\t1. Enter into existing Password Vault\n");
    printf("\t2. Create a new Password Vault\n");

    scanf("%d", &a);
    getchar();





    if(a == 1){
      printf("Please enter the file name you would like to access(do not include the extension):\n");
      fgets(fileName, 25, stdin);


      printf("\tPlease enter your Password:\n");
      fgets(password, 10, stdin);


      existingUser(fileName, password);
      b = 1;
    }
    else if( a == 2){

      newUser();

      b = 1;

    }
    else{

      printf("Sorry! That is not a valid option, please try again!\n");

    }

  }



  return 0;
}
