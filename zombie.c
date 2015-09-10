#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void main()
{
	int pid=fork();
	if (pid == 0) {
		/* Child */
		printf("Terminating Child, PID = %d\n",
		getpid());
		exit(0);
	} else {
		printf("Running Parent, PID = %d\n",
		getpid());
		waitpid(pid,NULL,0);	
		while (1) ; /* Infinite loop */
	}
}
