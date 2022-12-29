#include <stdio.h>
#include <stdlib.h>

typedef struct process{
	int pid;
	int at;
	int bt;
	int st;
	int ct;
	int tat;
	int wt;
	int rt;
	int tempbt;
}process;

int cmpfunc(const void *p1, const void *p2){
	int a = ((process *)p1)->at;
	int b = ((process *)p2)->at;

	if(a < b)
		return -1;
	else
		return 1;
}

int q[50]; //queue

int start=-1;
int rear=-1;

void push (int ele)
{
	if(start==-1)
	{
		start=0;
		rear=0;
	}
	
	q[rear]=ele;
	rear++;
}

int front()
{
	return q[start];
}

void pop()
{
	start++;
	
	if(start==rear)
	{
		start=-1;
		rear=-1;
	}
}

int main(){
	int n;
	printf("Enter the number of processes : ");
	scanf("%d",&n);

	process a[n];
	for(int i = 0 ; i < n ; i++){
		a[i].pid = i+1;
		printf("Enter the Arrival time and Burst time of process %d : ",i+1);
		scanf("%d%d",&a[i].at,&a[i].bt);
		
		a[i].tempbt = a[i].bt;
		a[i].st=-1;
	}
    
    int quant;
    printf("Enter Quant size : ");
    scanf("%d",&quant);
	
	qsort((void *)a, n, sizeof(process), cmpfunc);
	
	
	int completed=0;
	int timer=0,prevtimer=0;
	int idle_time=0;
	
	push(0);
	
	while(completed!=n)
	{
		int curr = front();
		
		if(a[curr].st==-1) // to set starting time
		{
		    if(a[curr].at >timer)
		    {
		        idle_time+=(a[curr].at - timer);
		        prevtimer=timer;
		        timer = a[curr].at;
		    }
		    
			a[curr].st = timer;
		}
		
		// calculating bt
		if(a[curr].tempbt > quant)
		{
			a[curr].tempbt -=quant;
			prevtimer=timer;
			timer+=quant;
		}
		else if(a[curr].tempbt<=quant)
		{
		    prevtimer=timer;
			timer+=a[curr].tempbt;
			a[curr].tempbt=0;
			a[curr].ct=timer;
			completed++;
		}
		
		pop();
		for(int i=0 ;i<n ;i++)
		{
			if(a[i].at>prevtimer && a[i].at <= timer)
			{
				push(i);
			}
		}
		if(a[curr].tempbt!=0)
			push(curr);
	}
	
	float avg_tat = 0, avg_wt = 0, avg_rt = 0;
	for (int i = 0; i < n; i++)
    {
        a[i].tat = a[i].ct - a[i].at;
        a[i].wt = a[i].tat - a[i].bt;
        a[i].rt = a[i].st - a[i].at;
        avg_tat += a[i].tat;
        avg_wt += a[i].wt;
        avg_rt += a[i].rt;
    }
	printf("PID		AT		BT		ST		CT		TAT		WT		RT\n");
	for(int i = 0 ; i < n ; i++){
		printf("%d		%d		%d		%d		%d		%d		%d		%d\n",a[i].pid,a[i].at,a[i].bt,a[i].st,a[i].ct,a[i].tat,a[i].wt,a[i].rt);
	}
	avg_tat /= n;
	avg_wt /= n;
	avg_rt /= n;

	int cycleLength = a[n-1].ct - a[0].st;
	float cpu_utl = ((cycleLength - idle_time)/(float)cycleLength)*100;
	float throughput = n/(float)cycleLength;

	printf("CPU Utilization = %f\n",cpu_utl);
	printf("Throughput = %f\n",throughput);
	printf("Average TAT = %f\n",avg_tat);
	printf("Average WT = %f\n",avg_wt);
	printf("Average RT = %f\n",avg_rt);

	return 0;
}