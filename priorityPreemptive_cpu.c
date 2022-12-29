//preemptive priority cpu scheduling algo
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct process{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    int tat;
    int wt;
    int rt;
    int priority;
}process;

int minimum(int x, int y){
    return (x < y) ? x : y;
}

int maximum(int x, int y){
    return (x > y) ? x : y;
}

int main(){
    int n, cycle_Length = 0, current_time = 0, prev = 0, idle_time = 0;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0, cpu_utl = 0, throughput = 0;

    printf("Enter the number of processes : ");
    scanf("%d",&n);

    process a[n];
    int bt_rem[n],is_completed[n], completed = 0;

    printf("Enter the at and corresponding bt of each process with its priority : \n");
    for(int i = 0 ; i < n ; i++){
        a[i].pid = i+1;
        scanf("%d%d%d",&a[i].at,&a[i].bt,&a[i].priority);

        bt_rem[i] = a[i].bt;
        is_completed[i] = -1;
    }

    while(completed != n){
        int current_process_index = -1, max_Priority = INT_MIN;
        for(int i = 0 ; i < n ; i++){       //find process with max priority
            if(a[i].at <= current_time && is_completed[i] == -1){
                if(a[i].priority > max_Priority){
                    max_Priority = a[i].priority;
                    current_process_index = i;
                }if(a[i].priority == max_Priority){
                    if(a[i].at < a[current_process_index].at){
                        max_Priority = a[i].priority;
                        current_process_index = i;
                    }
                }
            }
        }//current process index contains the index of process with max priority

        if(current_process_index != -1){
            if(bt_rem[current_process_index] == a[current_process_index].bt){       //process has arrived for the first time
                a[current_process_index].st = current_time;
                idle_time += a[current_process_index].st - prev;
            }bt_rem[current_process_index]--;
            current_time++;
            prev = current_time;

            if(bt_rem[current_process_index] == 0){
                a[current_process_index].ct = current_time;
                a[current_process_index].tat = a[current_process_index].ct - a[current_process_index].at;
                a[current_process_index].wt = a[current_process_index].tat - a[current_process_index].bt;
                a[current_process_index].rt = a[current_process_index].st - a[current_process_index].at;

                is_completed[current_process_index] = 1;
                completed++;

                avg_tat += a[current_process_index].tat;
                avg_wt += a[current_process_index].wt;
                avg_rt += a[current_process_index].rt;
            }
        }else{
            current_time++;
        }      
    }avg_tat /= n;
    avg_wt /= n;
    avg_rt /= n;

    int min_at = INT_MAX;
    int max_ct = INT_MIN;
    for(int i = 0 ; i < n ; i++){
        min_at = minimum(a[i].at,min_at);
        max_ct = maximum(a[i].ct,max_ct);
    }cycle_Length = max_ct - min_at;
    cpu_utl = ((cycle_Length - idle_time)/(float)cycle_Length)*100;
    throughput = n/(float)cycle_Length;

    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for(int i = 0 ; i < n ; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",a[i].pid,a[i].at,a[i].bt,a[i].st,a[i].ct,a[i].tat,a[i].wt,a[i].rt);
    }
    printf("\nAvg TAT = %f\nAvg WT = %f\nAvg RT = %f\n",avg_tat,avg_wt,avg_rt);
    printf("CPU Utilisation = %f\n",cpu_utl);
    printf("Throughput = %f\n",throughput);

    return 0;
}