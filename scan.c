//scan disk scheduling algo
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, seek_dist = 0, count = 0, dir, head, disk_size ;
    printf("Enter the disk size : ");
    scanf("%d",&disk_size);
    printf("Enter the number of requests : ");
    scanf("%d",&n);
    int a[n], ans[n+1];
    printf("Enter the seek time of each process : ");
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]);
    }
    printf("Enter the position of head pointer : ");
    scanf("%d",&head);
    printf("Enter direction : 0 for low and 1 for high : ");
    scanf("%d",&dir);

    //sorting the array
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n-i-1 ; j++){
            if(a[j] > a[j+1]){
                int temp;
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    int l_count = 0;
    for(int i = 0 ; i < n ; i++){
        if(a[i] > head){
            l_count = i;
            break;
        }
    }
    int j = 0;
    if(dir == 1){
        for(int i = l_count ; i < n ; i++){
            seek_dist += abs(head - a[i]);
            ans[j++] = a[i];
            head = a[i];
        }seek_dist += abs(head - (disk_size-1));
        ans[j++] = disk_size-1;
        head = disk_size - 1;

        for(int i = l_count-1 ; i >= 0 ; i--){
            seek_dist += abs(head - a[i]);
            ans[j++] = a[i];
            head = a[i];
        }
    }
    else if(dir == 0){
        for(int i = l_count-1 ; i >= 0 ; i--){
            seek_dist += abs(head - a[i]);
            ans[j++] = a[i];
            head = a[i];
        }seek_dist += abs(head - 0);
        ans[j++] = 0;
        head = 0;

        for(int i = l_count ; i < n ; i++){
            seek_dist += abs(head - a[i]);
            ans[j++] = a[i];
            head = a[i];
        }
    }
    printf("Seek sequence : ");
    for(int i = 0 ; i < j ; i++)
        printf("%d  ",ans[i]);
    printf("Seek distance = %d\n",seek_dist);

    return 0;
}



/*#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, seek_dist = 0, count = 0, dir, head, disk_size , k = 0;
    printf("Enter the disk size : ");
    scanf("%d",&disk_size);
    printf("Enter the number of requests : ");
    scanf("%d",&n);
    int a[n], ans[n+1];
    printf("Enter the seek time of each process : ");
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]);
    }
    printf("Enter the position of head pointer : ");
    scanf("%d",&head);
    printf("Enter direction : 0 for low and 1 for high : ");
    scanf("%d",&dir);

    //sorting the array
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n-i-1 ; j++){
            if(a[j] > a[j+1]){
                int temp;
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    int l_count = 0, r_count = 0;
    for(int i = 0 ; i < n ; i++){
        if(a[i] > head)
            break;
        else
            l_count++;
    }

    if(dir == 1){
        r_count = n-l_count+1;

        int left[l_count], right[r_count];
        for(int i = l_count-1, j = 0; i >= 0 ; i--, j++){
            left[j] = a[i];
        }for(int i = l_count, j = 0; i < n ; i++, j++){
            right[j] = a[i];
        }right[r_count-1] = disk_size-1;

        for(int i = 0 ; i < r_count ; i++){
            seek_dist += abs(head-right[i]);
            ans[k++] = right[i];
            head = right[i];
        }for(int i = 0 ; i < l_count ; i++){
            seek_dist += abs(head - left[i]);
            ans[k++] = left[i];
            head = left[i];
        }
    }
    
    else if(dir == 0){
        l_count++;
        r_count = n-l_count+1;

        int left[l_count], right[r_count];
        for(int i = l_count-2, j = 0 ; i >= 0 ; i--, j++){
            left[j] = a[i];
        }left[l_count-1] = 0;
        for(int i = l_count-1, j = 0 ; i < n ; i++, j++){
            right[j] = a[i];
        }

        for(int i = 0 ; i < l_count ; i++){
            seek_dist += abs(head - left[i]);
            ans[k++] = left[i];
            head = left[i];
        }for(int i = 0 ; i < r_count ; i++){
            seek_dist += abs(head - right[i]);
            ans[k++] = right[i];
            head = right[i];
        } 
    }
    printf("Seek sequence : ");
    for(int i = 0 ; i < k ; i++){
        printf("%d  ",ans[i]);
    }printf("\nSeek distance = %d",seek_dist);

    return 0;
}*/