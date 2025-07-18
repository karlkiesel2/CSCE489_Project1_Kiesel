/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 * Karl Kiesel
 * 18 July 2025
 *************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> // Will cause an error on Windows machines, uncomment to run on Linux
#include "shellfuncts.h"

/*
* Function called when the dir command is given by user
* 
* No params
*/
void dir()
{
	// run the 'ls' command within the current directory
	execl("/bin/ls", "ls", NULL);
	exit(0);
}

/*
* Function called to create a new file in the current directory
*
* Param: commandLine - Line of input given by user in format: create <name>
*/
void create(char *commandLine)
{

	// grab the second param of the user input, which will be used as the file name
	char *token = strtok(commandLine, " ");
	token = strtok(NULL, " ");

	FILE *newFile = fopen(token, "r");

	// If newFile does not exist, it will return a NULL pointer
	if (newFile)
	{
		printf("File already exists! Ending process...\n");
		fclose(newFile);
	}
	else
	{
		// the 'w' argument will create the new file
		newFile = fopen(token, "w");
		fclose(newFile);
		printf("New file created successfully!\n");

	}

	exit(0);
}

/*
* Function called to append text to the specified file in the current directory
*
* Param: commandLine - Line of input given by user in format: update <name> <number> <text>
*/
void update(char *commandLine)
{

	// copy contents from user input into new string, since we will be splitting it off of two different delimiters
	char lineCopy[100];
	strcpy(lineCopy, commandLine);

	// grab the second parameter, which will be the file name
	char *token = strtok(commandLine, " ");
	token = strtok(NULL, " ");

	// First, check if the specified file exists
	FILE *testFile = fopen(token, "r");
	if (testFile)
	{
		// if file exists, close it and move on
		fclose(testFile);
	}
	else
	{
		// if file does not exist, stop process and return to parent
		printf("File does not exist, use 'create' command to make it. Ending process...\n");
		fclose(testFile);
		exit(0);
	}

	// since we know the file exists, open it in append mode
	FILE *writeFile = fopen(token, "a");
	// grab the next token, which is the number of times to print
	token = strtok(NULL, " ");

	// make sure each char in <number> is a numeric , and non-negative
	if (token[0] == '-')
	{
		printf("Number cannot be negative. Please try again");
		exit(0);
	}
	
	for (unsigned i = 0; i < strlen(token); i++)
	{
		if (!isdigit(token[i]))
		{
			printf("Non-numeric entry detected for <number>. Please try again");
			exit(0);
		}
		
	}
	

	// using the copy of the commandLine string, grab everything inside "".
	char *textToken = strtok(lineCopy, "\"");
	textToken = strtok(NULL, "\"");

	for (int i = 0; i < strtol(token, NULL, 10); i++)
	{
		// write <text> to file each <number> of iterations
		fprintf(writeFile, "%s\n", textToken);
		// update changes immediately
		fflush(writeFile);
		// sleep as specified in the Project1 description
		sleep(strlen(textToken) / 5);
	}
	// close file
	fclose(writeFile);
	printf("\"%s\" written %s time(s) by Process id:%i\n", textToken, token, getpid());
	exit(0);
}

/*
* Function called to read contents of file in the current directory
* 
* Param: commandLine - Line of input given by user in format: update <name> <number> <text>
*/
void list(char *commandLine) {

	// grab the second param, which is file name
	char *token = strtok(commandLine, " ");
	token = strtok(NULL, " ");

	// open file in read mode
	FILE *readFile = fopen(token, "r");

	// If newFile does not exist, it will return a NULL pointer
	if (readFile)
	{
		// if file exists, close it and move on
		fclose(readFile);
		// run the UNIX cat command to read contents of file
		printf("File contents:\n");
		execl("/bin/cat", "cat", token, NULL);
	}
	else
	{
		// if file does not exist, stop process and return to parent
		printf("File does not exist, use 'create' command to make it. Ending process...\n");
		fclose(readFile);
		exit(0);
	}

	exit(0);

}