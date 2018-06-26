/**
 * @file PasswordVault.h
 * @author Mary Bergin
 * @date June 25th 2018
 * @Implementation of the Password Vault
 */
#ifndef _PASSWORDVAULT_
#define _PASSWORDVAULT_

#include <stdio.h>
#include <string.h>

/**Function to destroy specific data
*@param void data type
**/

void destroyData (void *data);

/**Function to print a specified data piece
*@param void data type to be printed
**/
void printData( void *toBePrinted);

/**Function determine the index at which a key is to be added
*@return an integer indicating an index
*@param size size of the hash table
*@param key
**/
int hashFunction (size_t tableSize, char key[25]);

/**Function to authorize the user to enter an existing file
*@return a number representing true or false
*@param pointer to the hashTable
*@param user entered key
*@param user entered password
**/
int authorize(HTable *hashTable, char key[25], char password[10]);

/**Function to create a new file that is to be loaded with the hashTab;e
*@param name of the file to be used to open
*@param password to be added to hashTable
**/

void newFile(char fileName[25], char password[10]);

/**Function to load an existing file into a hashTable
*@return a pointer to the new hashTable
*@param name of the file
*@param password
**/
HTable *loadFile(char fileName[25], char password[10]);

/**Function to call functions that will authorize the user and load the existing file
*@param name of the file to be used to open
*@param password
**/
void existingUser(char fileName[25], char password[10]);

/**Function to call functions to create a new file and load hashTables
*@param name of the file to be used to open
*@param password to be added to hashTable
**/
void newUser();

/**Function to take user input on what action they would like to perform
*@param name of the file to be used to open
*@param pointer to hashTable
**/
void secondMenu(HTable *hashTable, char fileName[25]);

/**Function to load hashTable into a file and quit
*@param name of the file to be used to open
*@param pointer to hashTab;e
**/
void saveToFile(HTable *hashTable, char fileName[25]);


/**Function to update an existing password
*@param pointer to hashTable
*@param name of the file to be used to open
*@param password to be updated to
**/
void updatePassword(HTable *hashTable, char key[25], void *data);

#endif
