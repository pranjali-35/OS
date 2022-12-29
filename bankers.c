#include <stdio.h>
#include <stdbool.h>

typedef struct process{
    int max[10];
    int allocated[10];
    int need[10];
}process;

bool applySafetyAlgo(process a[], int available[], int ans[], int n, int r){
    int is_completed[n];
    int available_copy[r];
    for(int i = 0 ; i < n ; i++)
        is_completed[i] = -1;
    for(int i = 0 ; i < r ; i++)
        available_copy[i] = available[i];
    
    bool proceed = true;
    int k = 0, complete = 0;

    while(proceed){
        proceed = false;
        for(int i = 0 ; i < n ; i++){
            bool flag = true;
            if(is_completed[i] == -1){
                for(int j = 0 ; j < r ; j++){
                    if(a[i].need[j] <= available_copy[j])
                        continue;       //to check for each resource instance of same process
                    else{
                        flag = false;
                        break;
                    }
                }if(flag == false)
                    continue;
                for(int j = 0 ; j < r ; j++)
                    available_copy[j] += a[i].allocated[j];
                is_completed[i] = 1;
                complete++;
                ans[k++] = i;
                proceed = true;
            }
        }
    }if(complete == n)
        return true;
    return false;
}

int main(){
    int n,r;
    printf("Enre the number of processes : ");
    scanf("%d",&n);
    printf("Enter the number of resource instance in the system : ");
    scanf("%d",&r);

    int available[r];
    int ans[n];
    process a[n];

    //Input
    for(int i = 0 ; i < n ; i++){
        printf("\nProcess%d\n",i);
        printf("Enter Maximum Need : ");
        for(int j = 0 ; j < r ; j++){
            scanf("%d",&a[i].max[j]);
        }printf("Enter Allocated Resources : ");
        for(int j = 0 ; j < r ; j++){
            scanf("%d",&a[i].allocated[j]);
            a[i].need[j] = a[i].max[j] - a[i].allocated[j];
        }
    }printf("\nEnter Avaliable Resources : ");
    for(int i = 0 ; i < r ; i++){
        scanf("%d",&available[i]);
    }

    //Printing the table
    printf("\nPID\t\tMaximum\t\tAllocated\tNeed\t\n");
    for(int i = 0 ; i < n ; i++){
        printf("P[%d]\t\t",i+1);
        for(int j = 0 ; j < r ; j++)
            printf("%d ",a[i].max[j]);
        printf("\t\t");
        for(int j = 0 ; j < r ; j++)
            printf("%d ",a[i].allocated[j]);
        printf("\t\t");
        for(int j = 0 ; j < r ; j++)
            printf("%d ",a[i].need[j]);
        printf("\n");
    }

    if(applySafetyAlgo(a,available,ans,n,r)){
        printf("\nSystem is in Safe State\n");
        printf("Safe Sequence is : ");
        for(int i = 0 ; i < n ; i++)
            printf("P[%d]  ",ans[i]);
    }else
        printf("\nSystem is in Unsafe State\n");

    return 0;
}