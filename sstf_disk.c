//sstf disk scheduling algo
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    int n, head, seek_dist = 0, count = 0, min_index;
    printf("Enter the number of requests : ");
    scanf("%d",&n);

    int a[n], ans[n];
    printf("Enter the seek time of each request : ");
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]);
    }

    printf("Enter the position of head pointer : ");
    scanf("%d",&head);

    while(count != n){
        int min_dist = INT_MAX;
        for(int i = 0 ; i < n ; i++){
            if( (a[i] != -1) && (abs(head-a[i]) < min_dist) ){
                min_dist = abs(head - a[i]);
                min_index = i;
            }
        }seek_dist += abs(a[min_index]-head);
        ans[count] = a[min_index];
        head = a[min_index];
        a[min_index] = -1;
        count++;
    }

    printf("Seek Sequence is : ");
    for(int i = 0 ; i < n ; i++){
        printf("%d  ",ans[i]);
    }printf("\nTotal Seek Distance is %d\n",seek_dist);

    return 0;
}