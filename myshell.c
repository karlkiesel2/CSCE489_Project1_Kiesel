/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489
 * Karl Kiesel
 * 18 July 2025
 *************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // Will cause an error on Windows machines, uncomment to run on Linux
#include <unistd.h> // Will cause an error on Windows machines, uncomment to run on Linux
#include "shellfuncts.h"
/*
Implementation of myshell for Project 1
*/
int main(int argv, const char *argc[])
{
	(void)argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void)argc; // Make compile warnings go away - be sure to delete this line if you use the param

	// used to check if the shell should be terminated. Start as false
	bool finished = false;
	// create a string to hold the entered command, and copies for tokenizing
	char commandLine[100], checkForTwoParams[100], checkForFourParams[100], checkForThreeParams[100];
	// iterate through do-while loop until the 'halt' command is entered
	do
	{
		// print parent process id at the start of loop
		printf("Parent process id: %i\n", getpid());
		// Prompt user to enter their command
		printf("Enter a command to run:\n");
		// Grab line of text from user, contaning 1 or more parameters. 1st parameter is the name of the command to be executed
		fgets(commandLine, sizeof(commandLine), stdin);
		// remove the trailing newline character
		commandLine[strcspn(commandLine, "\n")] = 0;

		// These lines are used to check if the last two characters of a line are " &", indicating that the child process should run in the background
		bool background = false;
		char lastChar = commandLine[strlen(commandLine) - 1];
		char secondLastChar = commandLine[strlen(commandLine) - 2];
		if ((lastChar == '&') && (secondLastChar == ' '))
		{
			background = true;
		}
		

		// show user the command that they entered
		printf("Command entered is: %s\n", commandLine);

		// make copy of text entered by user. Then split by the space delimiter. Grab the second parameter
		strcpy(checkForTwoParams, commandLine);
		char *checkForTwoParamsToken = strtok(checkForTwoParams, " ");
		checkForTwoParamsToken = strtok(NULL, " ");

		
		// make copy of text entered by user. Then split by the space delimiter. Grab the third parameter
		strcpy(checkForThreeParams, commandLine);
		char *checkForThreeParamsToken = strtok(checkForThreeParams, " ");
		for (int i = 0; i < 2; i++)
		{
			checkForThreeParamsToken = strtok(NULL, " ");
		}

		// make copy of text entered by user. Then split by the space delimiter. Grab the fourth parameter
		strcpy(checkForFourParams, commandLine);
		char *checkForFourParamsToken = strtok(checkForFourParams, " ");
		for (int i = 0; i < 3; i++)
		{
			checkForFourParamsToken = strtok(NULL, " ");
		}

		// if command is 'halt', set finished to true, thus ending the program
		if (strcmp(commandLine, "halt") == 0)
		{
			finished = true;
		}
		// check if first 7 chars of user input are "create ". Also make sure at least two params are given. Lastly, check for background mode
		else if ((strncmp(commandLine, "create ", 7) == 0) && (checkForTwoParamsToken != NULL) && ((checkForThreeParamsToken == NULL) || (background == true)))
		{

			// fork process
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				create(commandLine);
				printf("exec failed\n");
			}
			// This handles the background process case for parent
			else if ((pid > 0) && (background == true))
			{
				// do not wait for the child process to finish
				printf("Child process working in background.\n\n");
				
			}
			else if (pid > 0)
			{
				// Parent process
				waitpid(pid, 0, 0); // waitpid for child to finish
				printf("Child process completed.\n\n");
			}
			else
			{
				// Error
				printf("fork failed\n");
			}
		}
		// check if first 7 chars of user input are "update " and the fourth parameter is a non-NULL value that starts with quotation marks
		else if ((strncmp(commandLine, "update ", 7) == 0) && ((checkForFourParamsToken != NULL)) && (checkForFourParamsToken[0] == '"'))
		{
			// fork process
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				update(commandLine);
				printf("exec failed");
			}
			// This handles the background process case for parent
			else if ((pid > 0) && (background == true))
			{
				printf("Child process working in background.\n\n");
				
			}
			// Foreground process case for parent
			else if (pid > 0)
			{
				// Parent process
				waitpid(pid, 0, 0); // waitpid for child to finish
				printf("Child process completed.\n\n");
			}
			else
			{
				// Error
				printf("fork failed");
			}
		}
		// check if first 5 chars of user input are "list ". Also make sure at least two params are given. Lastly, check for background mode
		else if ((strncmp(commandLine, "list ", 5) == 0) && (checkForTwoParamsToken != NULL) && ((checkForThreeParamsToken == NULL) || (background == true)))
		{
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				list(commandLine);
				printf("exec failed");
			}
			// This handles the background process case for parent
			else if ((pid > 0) && (background == true))
			{
				printf("Child process working in background.\n\n");
				
			}
			else if (pid > 0)
			{
				// Parent process
				waitpid(pid, 0, 0); // waitpid for child to finish
				printf("\nChild process completed.\n\n");
			}
			else
			{
				// Error
				printf("fork failed");
			}
		}
		// check if value in command line is "dir" or "dir &". Also make sure there is never a third parameter given
		else if (((strcmp(commandLine, "dir") == 0) || ((strncmp(commandLine, "dir ", 4) == 0) && (background == true))) && (checkForThreeParamsToken == NULL))
		{
			// fork process
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				dir();
				printf("exec failed");
			}
			// This handles the background process case for parent
			else if ((pid > 0) && (background == true))
			{
				printf("Child process working in background.\n\n");
				
			}
			else if (pid > 0)
			{
				// Parent process
				waitpid(pid, 0, 0); // waitpid for child to finish
				printf("Child process completed.\n\n");
			}
			else
			{
				// Error
				printf("fork failed");
			}
		}
		// None of the command requirements were met
		else
		{
			// prompt the user to try again
			printf("Unrecognized command. Try again.\n");
		}

		// Continue looping until halt is entered
	} while (finished == false);

	return 0;
}
