//Write a program to use fork function to create process
#include <stdio.h>
#include <unistd.h>

int  main(){
	int n=fork();
	printf("%d\n",n);
	printf("Process id = %d\n",getpid());
	
	return 0;
}
