//Write a program to create a child process in prallel to main process define an array of numbers child process has to calculate the sum of even numbers and parent process has to calculate sum of odd numbers.

#include <stdio.h>
#include <unistd.h>

int  main(){
	int n;
	printf("Enter number of elements in array : ");
	scanf("%d",&n);
	int arr[n];
	printf("Enter array elements : ");
	for(int i = 0 ; i < n ; i++)
		scanf("%d",&arr[i]);
		
	int even_sum = 0,odd_sum = 0;
	
	int x = fork();

	if(x==0){       //child process when x = 0
	    printf("Child Process\n");
		for(int i = 0 ; i < n; i++){
			if(arr[i]%2 == 0)
				even_sum += arr[i];
		}printf("Process with id = %d calculated even sum = %d\n\n",getpid(),even_sum);
	}
	else{		//parent process when x > 0
	    printf("Parent Process\n");
		for(int i = 0 ; i < n; i++){
			if(arr[i]%2 != 0)
				odd_sum += arr[i];
		}printf("Process with id = %d calculated odd sum = %d\n\n",getpid(),odd_sum);
	}
	
	return 0;
}
