//Write C programs to create a Zombie process.

/*A process which has finished the execution but still has entry in the process table to report to its parent process is known as a zombie process. A child process always first becomes a zombie before being removed from the process table. The parent process reads the exit status of the child process which reaps off the child process entry from the process table.
In the following code, the child finishes its execution using exit() system call while the parent sleeps for 5 seconds, hence doesn’t call wait() and the child process’s entry still exists in the process table.*/

#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Name : Pranjali Kothari\n20012810\n\n");
	int x = fork();
	
	if(x == 0)	//child process
		printf("Child's process id = %d\nParent's process id = %d\n\n",getpid(),getppid());
	else{		//parent process
		sleep(5);
		printf("Parent's process id = %d\n",getpid());
	}
	return 0;
}
