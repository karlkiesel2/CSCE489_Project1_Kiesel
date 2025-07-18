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
// #include <unistd.h> // Will cause an error on Windows machines, uncomment to run on Linux
#include "shellfuncts.h"

int main(int argv, const char *argc[])
{
	(void)argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void)argc; // Make compile warnings go away - be sure to delete this line if you use the param

	// If they just ran myshell, say Hello World--if they included a parameter, speak Australian
	// if (argv == 1)
	//	hello(1);
	// else
	//	hello(0);
	bool finished = false;
	// create a string to hold the entered command
	char commandLine[100];
	// iterate through do-while loop until the 'halt' command is entered
	do
	{
		// print parent process id at the start of loop
		printf("Parent process id: %i\n", getpid());
		// Prompt user to enter their command
		printf("Enter a command to run:\n");
		// Grab line of text from user
		fgets(commandLine, sizeof(commandLine), stdin);
		commandLine[strcspn(commandLine, "\n")] = 0;

		// These lines are used to check if the last two characters of a line are " &", indicating that the child process should run in the background
		char lastChar = commandLine[strlen(commandLine) - 1];
		char secondLastChar = commandLine[strlen(commandLine) - 1];

		printf("Command entered is: %s\n", commandLine);

		if (strcmp(commandLine, "halt") == 0)
		{
			finished = true;
		}
		else if (strncmp(commandLine, "create ", 7) == 0)
		{

			// fork process
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				create(commandLine);
				perror("exec failed");
			}
			else if (pid > 0)
			{
				// Parent process
				wait(NULL); // Wait for child to finish
				printf("Child process completed.\n\n");
			}
			else
			{
				// Error
				perror("fork failed");
			}
		}
		else if (strncmp(commandLine, "update ", 7) == 0)
		{
			// fork process
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				update(commandLine);
				perror("exec failed");
			}
			// This handles the background process case
			else if ((pid > 0) && (lastChar == '&') && (secondLastChar == ' '))
			{
				printf("In the background!");
				wait(NULL); // Wait for child to finish
				printf("Child process completed.\n\n");
				// background stuff
			}
			else if (pid > 0)
			{
				// Parent process
				wait(NULL); // Wait for child to finish
				printf("Child process completed.\n\n");
			}
			else
			{
				// Error
				perror("fork failed");
			}
		}
		else if (strncmp(commandLine, "list ", 5) == 0)
		{
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				list(commandLine);
				perror("exec failed");
			}
			else if (pid > 0)
			{
				// Parent process
				wait(NULL); // Wait for child to finish
				printf("\nChild process completed.\n\n");
			}
			else
			{
				// Error
				perror("fork failed");
			}
		}
		// condition for 'dir' command
		else if (strcmp(commandLine, "dir") == 0)
		{
			// fork process
			int pid = fork();
			if (pid == 0)
			{
				// Child process
				printf("Child process id: %i\n", getpid());
				dir();
				perror("exec failed");
			}
			else if (pid > 0)
			{
				// Parent process
				wait(NULL); // Wait for child to finish
				printf("Child process completed.\n\n");
			}
			else
			{
				// Error
				perror("fork failed");
			}
		}
		else
		{
			printf("Unrecognized command. Try again.\n");
		}

	} while (finished == false);

	return 0;
}
