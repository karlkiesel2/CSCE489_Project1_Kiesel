/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489
 * Karl Kiesel
 * 18 July 2025
 *************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
			/* code */
			printf("dir stuff\n");
		}
		else
		{
			printf("Try again\n");
		}

	} while (finished == false);

	return 0;
}
