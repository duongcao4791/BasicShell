#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 80 /* The maximum length command */

int main(void)
{
	char *args[MAXLINE/2 + 1]; 			/* command line with max 40 arguments */
	int maxLine = MAXLINE/2 +1;
	char command[maxLine];
	int pid;
	char* token;						/* token of the character array */
	int should_wait =1;					/* determine the wait status of parent */
	int should_run = 1; 				/* flag to determine when to exit program */
	printf("Shell from Duong Cao\n"); /* replace w/ name */
	while (should_run) {
		printf("Duong>"); 				/* prompt- replace FirstName and L3SID */
		fflush(stdout);
		/* After reading user input, the steps are:
		* (1) if the command is exit, set should_run to 0 to exit the while loop
		* (2) fork a child process using fork()
		* (3) the child process will invoke execvp()
		* (4) if the command line included &, parent will NOT invoke wait()
		*/
		fgets(command, maxLine, stdin);
		int length = strlen(command);

		if (strcmp(command, "exit\n") == 0)
				{
					should_run = 0;
					break;
				}
		else{
			if(command[length-1]=='\n')
				command[length-1]= '\0';		/* replaces new line by null character */
			token=strtok(command, " ");			/* input with " " */

			int i=0;							/* counter */
			while (token!=NULL){
					args[i++] = token;
					token = strtok(NULL, " ");
			}//end while

			if (strcmp(args[i-1], "&") == 0) {
				should_wait = 0;				/* set wait status of parent to 0 when '&' appear */
				args[i-1] = '\0';				/* replace & by Null */
			}else
				args[i] = '\0';					/* starts token by Null */
			}

		pid = fork();							/* create new process */
		if(pid < 0)
		{
			printf("ERROR: fork error\n");
		}
		else if (pid == 0) {					/* child process */
			if (execvp(args[0], args)!= 0) {	/* if execvp fails */
				printf("ERROR: execvp!!! Invalid command. \n");	/* print error */
				exit(-2);
			}
		}
		else {
			if (should_wait == 1) {				/* parent wait for child process terminates */
				while (pid != wait(NULL));
			}
		}
	}
	return 0;
}
