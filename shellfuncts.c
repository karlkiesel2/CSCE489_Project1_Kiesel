/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 * Karl Kiesel
 * 18 July 2025
 *************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "shellfuncts.h"

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *		Params:	param1 - I explain my parameters, like this is 1 for American, 2 for
 *                      Australian
 *
 *		Returns: always returns 1, no matter what. Fairly useless.
 *
 *************************************************************************************/

int hello(int param1)
{
	// I'm commenting to explain that this checks param and changes the message
	if (param1 == 1)
		send_msg("Hello world!\n");
	else
		send_msg("G'day world!\n");

	// Return 1 because, why not.
	return 1;
}

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *    Params:  param2 - not a very good parameter name - something better might be
 *                      say, msgstr or sendtext
 *
 *************************************************************************************/

void send_msg(const char *param2)
{
	printf("%s", param2);
}

/*
Function called when the dir command is given by user
*/
void dir()
{
	// run the 'ls' command within the current directory
	execl("/bin/ls", "ls", NULL);
	exit(0);
}

/*
Function called to create a new file in the current directory

Param: commandLine - Line of input given by user in format: create <name>
*/
void create(char *commandLine)
{

	FILE *newFile = fopen("someName", "r");

	// If newFile does not exist, it will return a NULL pointer
	if (newFile)
	{
		printf("File already exists! Ending process...\n");
		fclose(newFile);
	}
	else
	{
		printf("New file created successfully!\n");
		newFile = fopen("someName", "w");
		fclose(newFile);
	}

	exit(0);
}

/*
Function called to append text to the specified file in the current directory

Param: commandLine - Line of input given by user in format: update <name> <number> <text>
*/
void update(char *commandLine)
{

	// First, check if the specified file exists
	FILE *testFile = fopen("someName", "r");
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
	FILE *writeFile = fopen("someName", "a");
	for (int i = 0; i < 5; i++)
	{
		// write <text> to file each <number> of iterations
		fprintf(writeFile, "This is a test\n");
		// update changes immediately
		fflush(writeFile);
	}
	// close file
	fclose(writeFile);

	exit(0);
}

/*
Function called to read contents of file in the current directory

Param: commandLine - Line of input given by user in format: update <name> <number> <text>
*/
void list(char *commandLine) {

	char *token = strtok(commandLine, " ");
	token = strtok(NULL, " ");

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