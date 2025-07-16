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
//#include <unistd.h> // Will cause an error on Windows machines, uncomment to run on Linux
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

	printf("Parent id :" + getpid());

	bool finished = false;
	do
	{
		// create a string to hold the entered command
		char fullName[100];
		// Prompt user to enter their command
		printf("Enter a command to run\n");
		// Grab line of text from user
		fgets(fullName, sizeof(fullName), stdin);

		printf("Command entered is %s", fullName);

		if (strncmp(fullName, "halt", 4) == 0)
		{
			finished = true;
		}
		else if (strncmp(fullName, "create", 6) == 0)
		{
			/* code */
			printf("Create stuff\n");
		}
		else if (strncmp(fullName, "update", 6) == 0)
		{
			/* code */
			printf("Update stuff\n");
		}
		else if (strncmp(fullName, "list", 4) == 0)
		{
			/* code */
			printf("List stuff\n");
		}
		else if (strncmp(fullName, "dir", 3) == 0)
		{
			//pid_t pid = fork();
			printf("dir stuff\n");
			dir();
			/* if (pid == 0)
			{
				// Child process
				dir();
				perror("exec failed");
			}
			else if (pid > 0)
			{
				// Parent process
				wait(NULL); // Wait for child to finish
				printf("Child process completed.\n");
			}
			else
			{
				// Error
				perror("fork failed");
			} */
		}
		else
		{
			printf("Try again\n");
		}

	} while (finished == false);

	return 0;
}
