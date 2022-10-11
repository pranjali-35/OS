//Zombie process implementation
#include <stdio.h>
#include <unistd.h>

int main(){
    int x = fork();
    if(x == 0){     //child process
        printf("\nChild Process\n");
        printf("Child process id = %d\n",getpid());
        printf("Parent process id accessed from child process = %d\n",getppid());
    }else{          //parent process
        printf("\nParent Process\n");
        sleep(5);
        printf("Parent process id = %d\n",getpid());
    }
    
    return 0;
}
