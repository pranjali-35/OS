//Write C program to create an Orphan process

/*A process whose parent process no more exists i.e. either finished or terminated without waiting for its child process to terminate is called an orphan process.
In the following code, parent finishes execution and exits while the child process is still executing and is called an orphan process now.
However, the orphan process is soon adopted by init process, once its parent process dies.*/

#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Name : Pranjali Kothari\n20012810\n\n");
	int x = fork();
	if(x == 0){	//child process
		sleep(5);
		printf("Child's process id = %d\nParent's process id = %d\n\n",getpid(),getppid());
	}else{		//parent process
		printf("Parent's process id = %d\n",getpid());
	}
	return 0;
}
