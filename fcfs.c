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
}process;

int cmpfunc(const void *p1, const void *p2){
	int a = ((process *)p1)->at;
	int b = ((process *)p2)->at;

	if(a < b)
		return -1;
	else
		return 1;
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
	}

	qsort((void *)a, n, sizeof(process), cmpfunc);

	a[0].st = a[0].at;
	a[0].ct = a[0].st + a[0].bt;
	a[0].tat = a[0].ct - a[0].at;
	a[0].wt = a[0].tat - a[0].bt;
	a[0].rt = a[0].st - a[0].at;

	int idle_time = 0;
	for(int i = 1 ; i < n ; i++){
		a[i].st = (a[i-1].ct > a[i].at) ? a[i-1].ct : a[i].at;
		a[i].ct = a[i].st + a[i].bt;
		a[i].tat = a[i].ct - a[i].at;
		a[i].wt = a[i].tat - a[i].bt;
		a[i].rt = a[i].st - a[i].at;

		if(a[i].st > a[i-1].ct)
			idle_time += (a[i-1].ct - a[i].st);
	}

	float avg_tat = 0, avg_wt = 0, avg_rt = 0;
	printf("PID		AT		BT		ST		CT		TAT		WT		RT\n");
	for(int i = 0 ; i < n ; i++){
		printf("%d		%d		%d		%d		%d		%d		%d		%d\n",a[i].pid,a[i].at,a[i].bt,a[i].st,a[i].ct,a[i].tat,a[i].wt,a[i].rt);
		avg_tat += a[i].tat;
		avg_wt += a[i].wt;
		avg_rt += a[i].rt;
	}avg_tat /= n;
	avg_wt /= n;
	avg_rt /= n;

	float cpu_utl = ((a[n-1].ct - idle_time)/a[n-1].ct)*100;
	float throughput = n/(float)a[n-1].ct;

	printf("CPU Utilization = %f\n",cpu_utl);
	printf("Through put = %f\n",throughput);
	printf("Average TAT = %f\n",avg_tat);
	printf("Average WT = %f\n",avg_wt);
	printf("Average RT = %f\n",avg_rt);

	return 0;
}
