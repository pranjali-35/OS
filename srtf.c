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
}process;

int minimum(int x, int y){
    return ((x < y) ? x : y);
}

int maximum(int x, int y){
    return ((x > y) ? x : y);
}

int main(){
    int n;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;
    printf("Enter the number of process : ");
    scanf("%d",&n);

    int bt_remaining[n];
    int is_completed[n];

    process a[n];
    for(int i = 0 ; i < n ; i++){
        a[i].pid = i+1;
        printf("Enter the Arrival Time and Burst Time of process %d : ",i+1);
        scanf("%d%d",&a[i].at,&a[i].bt);

        bt_remaining[i] = a[i].bt;
        is_completed[i] = 0;
    }

    int completed = 0, current_time = 0, prev = 0, idle_time = 0;
    while(completed != n){
        int current_process_index = -1, min_bt = INT_MAX;       //min_bt = process which has min remaining bt
        for(int i = 0 ; i < n ; i++){                           //iterate every process to find process with min bt
            if(a[i].at <= current_time && is_completed[i] == 0){
                if(bt_remaining[i] < min_bt){
                    min_bt = bt_remaining[i];
                    current_process_index = i;
                }if(bt_remaining[i] == min_bt){
                    if(a[i].at < a[current_process_index].at){
                        min_bt = bt_remaining[i];
                        current_process_index = i;
                    }
                }
            }
        }//Now current_process_index contains index of process with min bt
        if(current_process_index != -1){        // if process found
            if(bt_remaining[current_process_index] == a[current_process_index].bt){     //if process is getting cpu for first time
                a[current_process_index].st = current_time;
                idle_time += a[current_process_index].st - prev;                      //calculate idle time
            }
            bt_remaining[current_process_index]--;
            current_time++;
            prev = current_time;

            if(bt_remaining[current_process_index] == 0){
                a[current_process_index].ct = current_time;
                a[current_process_index].tat = a[current_process_index].ct - a[current_process_index].at;
                a[current_process_index].wt = a[current_process_index].tat - a[current_process_index].bt;
                a[current_process_index].rt = a[current_process_index].st - a[current_process_index].at;

                //mark process as completed
                is_completed[current_process_index] = 1;
                completed++;
            }
        }else{                                  //if process not found
            current_time++;
        }
    }//all processes are completed now

    int min_at = INT_MAX;
    int max_ct = INT_MIN;
    for(int i = 0 ; i < n ; i++){
        min_at = minimum(min_at,a[i].at);
        max_ct = maximum(max_ct,a[i].ct);
    }
    int cycleLength = max_ct - min_at;
    float cpu_utl = ((cycleLength-idle_time)/(float)cycleLength) * 100;

    printf("PID     AT      BT      ST      CT      TAT     WT      RT\n");
    for(int i = 0 ; i < n ; i++){
        printf("%d      %d      %d      %d      %d      %d      %d      %d\n",a[i].pid,a[i].at,a[i].bt,a[i].st,a[i].ct,a[i].tat,a[i].wt,a[i].rt);
        avg_tat += a[i].tat;
        avg_wt += a[i].wt;
        avg_rt += a[i].rt;
    }
    printf("Average TAT = %f\n",avg_tat/(float)n);
    printf("Average WT = %f\n",avg_wt/(float)n);
    printf("Average RT = %f\n",avg_rt/(float)n);
    printf("CPU Utilization = %f\n",cpu_utl);
    printf("Throughput = %f\n",n/(float)cycleLength);

    return 0;
}
