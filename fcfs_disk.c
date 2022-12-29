//fcfs disk scheduling algo 
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, head, seek_dist = 0;
    printf("Enter the number of requests : ");
    scanf("%d",&n);
    int a[n];
    printf("Enter the seek time of the processes : ");
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]);
    }
    printf("Enter the position of head pointer : ");
    scanf("%d",&head);

    for(int i = 0 ; i < n ; i++){
        seek_dist += (abs(head-a[i]));
        head = a[i];
    }

    printf("Seek Sequence : ");
    for(int i = 0 ; i < n ; i++){
        printf("%d  ",a[i]);
    }printf("\nTotal Seek Distance : %d\n",seek_dist);

    return 0;
}