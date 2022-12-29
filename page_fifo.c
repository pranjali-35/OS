//fifo page replacement algo
#include <stdio.h>

int check(int val, int ans[], int r){
    for(int i = 0 ; i < r ; i++){
        if(ans[i] == val)
            return 1;
    }return 0;
}

int main(){
    int n,hit = 0, miss = 0, nf, r = 0, temp = 0;
    printf("Enter the number of pages : ");
    scanf("%d",&n);
    int a[n];
    printf("Enter the pages : ");
    for(int i = 0 ; i < n ; i++)
        scanf("%d",&a[i]);
    printf("Enter the number of frames : ");
    scanf("%d",&nf);
    int ans[nf];

    for(int i = 0 ; i < n ; i++){
        if(r < nf){
            if(!check(a[i],ans, r)){
                ans[r++] = a[i];
                miss++;
            }else
                hit++;
        }else{
            if(!check(a[i],ans,r)){
                ans[temp++] = a[i];
                miss++;
            }else
                hit++;
        }for(int i = 0 ; i < r ; i++){
            printf("%d  ",ans[i]);
        }printf("\n");
    }

    printf("Total number of page faults = %d\n",miss);
    printf("Total number of hit = %d\n",hit);

    return 0;
}