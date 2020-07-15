#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct
{
       int pid;
       int burst_time;
       int waiting_time;
       int turnaround_time;
} Process;

int input() 
{ 
    int number; 
    scanf("%d", &number); 
    return (number); 
} 
//FOR FCFS
void print_table(Process p[], int n)
{
       int i;

       puts(" PID  BT  WT   TT");

       for (i = 0; i < n; i++)
       {
              printf(" %2d  %2d    %2d     %2d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
       }
}

void print_gantt_chart(Process p[], int n)
{
       int i, j;
       // print top bar
       printf(" ");
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time; j++)
                     printf(" ");
              printf(" ");
       }
       printf("\n|");

       // printing process id in the middle
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time - 1; j++)
                     printf(" ");
              printf("P%d", p[i].pid);
              for (j = 0; j < p[i].burst_time - 1; j++)
                     printf(" ");
              printf("|");
       }
       printf("\n ");
       // printing bottom bar
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time; j++)
                     printf(" ");
              printf(" ");
       }
       printf("\n");

       // printing the time line
       printf("0");
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time; j++)
                     printf("  ");
              if (p[i].turnaround_time > 9)
                     printf("\b"); // backspace : remove 1 space
              printf("%d", p[i].turnaround_time);
       }
       printf("\n");
}

void fcfs()
{
       Process p[MAX];
       int i, j, n;
       int sum_waiting_time = 0, sum_turnaround_time;
       printf("First Come First Serve\n");
       printf("Enter total number of process: ");
       scanf("%d", &n);
       printf("Enter burst time for each process:\n");
       for (i = 0; i < n; i++)
       {
              p[i].pid = i + 1;
              printf("P[%d] : ", i + 1);
              scanf("%d", &p[i].burst_time);
              p[i].waiting_time = p[i].turnaround_time = 0;
       }

       // calculate waiting time and turnaround time
       p[0].turnaround_time = p[0].burst_time;

       for (i = 1; i < n; i++)
       {
              p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
              p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
       }

       // calculate sum of waiting time and sum of turnaround time
       for (i = 0; i < n; i++)
       {
              sum_waiting_time += p[i].waiting_time;
              sum_turnaround_time += p[i].turnaround_time;
       }

       // print table
       puts(""); // Empty line
       print_table(p, n);
       puts(""); // Empty Line
       printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
       printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double)n);
       printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
       printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double)n);

       // print Gantt chart
       puts(""); // Empty line
       puts("          GANTT CHART          ");
       puts("          ***********          ");
       print_gantt_chart(p, n);
}

//FOR SJF
double average_waiting_time, average_turnaround_time;
int total_waiting_time;
int sum_turnaround_time;
void calculate_waiting_time(Process p[], int n)
{
       int i;
       total_waiting_time = 0;
       p[0].waiting_time = 0;
       for (i = 1; i < n; i++)
       {
              p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
              total_waiting_time += p[i].waiting_time;
              p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
              sum_turnaround_time += p[i].turnaround_time;
       }
}

void sort_process_by_burst_time(Process p[], int n)
{
    int i, j;
    Process temp;
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-1-i; j++) {
            if(p[j].burst_time > p[j+1].burst_time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void print_gantt_chart_sjf(Process p[], int n)
{
       int i, j;
       int last = p[n - 1].burst_time + (n == 1 ? 0 : p[n - 1].waiting_time);
       // printing top bar
       printf(" ");
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time; j++)
                     printf(" ");
              printf(" ");
       }
       printf("\n|");
       // middle position
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time - 1; j++)
                     printf(" ");
              printf("p%d", p[i].pid);
              for (j = 0; j < p[i].burst_time - 1; j++)
                     printf(" ");
              printf("|");
       }
       printf("\n ");
       // bottom bar
       for (i = 0; i < n; i++)
       {
              for (j = 0; j < p[i].burst_time; j++)
                     printf(" ");
              printf(" ");
       }
       printf("\n");

       // printing waiting time
       int minus = 0;
       for (i = 0; i < n; i++)
       {
              if (p[i].waiting_time > 9)
                     printf(" ");
              printf("%d", p[i].waiting_time);
              if (p[i + 1].waiting_time > 9)
              {
                     minus = 1;
              }
              if (i + 1 == n)
                     if (last > 9)
                            minus = 1;
              for (j = 0; j < p[i].burst_time - minus; j++)
                     printf("  ");
       }
       if (last > 9)
              printf(" ");
       printf("%d\n", last);
}
void sjf()
{
       Process p[MAX];
       int n, i, j;
       puts("SJF");
       printf("Enter total process: ");
       scanf("%d", &n);
       printf("Enter burst time for each process:\n");
       for (i = 0; i < n; i++)
       {
              printf("P[%d]: ", i + 1);
              scanf("%d", &p[i].burst_time);
              p[i].pid = i + 1;
       }

       sort_process_by_burst_time(p, n);
       calculate_waiting_time(p, n);

       average_waiting_time = (double)((double)total_waiting_time / (double)n);
       average_turnaround_time = (double)((double) sum_turnaround_time / (double)n);

       puts("");
       printf("Average Waiting Time: %.2lf\n", average_waiting_time);
       printf("Average TurnAround Time : %.21f\n", average_turnaround_time);
       printf("Gantt Chart:\n");
       print_gantt_chart(p, n);
}

//FOR SRTF
struct sjf
{
       int bt, at, wt, st, pno, tt, cbt;
};

int get(struct sjf arr[], int t, int n)
{
       int imin, min = 9999, i;
       for (i = 0; i < n; i++)
       {
              if (arr[i].at <= t && arr[i].st == 0)
                     if (min > arr[i].bt)
                     {
                            min = arr[i].bt;
                            imin = i;
                     }
       }
       return imin;
}

void gantt_chart(struct sjf arr[], int p[], int n, int nop)
{
       int i, a[100], s = 0;
       float avgtt = 0, avgwt = 0;
       printf("GANTT CHART\n");
       printf("0");
       for (i = 0; i < n - 1; i++)
       {
              while (i < n - 1 && p[i] == p[i + 1])
              {
                     s++;
                     i++;
              }

              s++;
              printf(" --- [P%d] --- %d", arr[p[i]].pno, s);
              arr[p[i]].wt = s - arr[p[i]].at - arr[p[i]].tt;
       }
       for (i = 0; i < nop; i++)
       {
              arr[i].tt += arr[i].wt;
              avgwt += arr[i].wt;
              avgtt += arr[i].tt;
       }
       printf("PID\tAT\tBT\tTT\tWT\n");
       for (i = 0; i < nop; i++)
       {
              printf("[P%d]\t%d\t%d\t%d\t%d\n", arr[i].pno, arr[i].at, arr[i].cbt, arr[i].tt, arr[i].wt);
       }
       avgwt = avgwt / nop;
       avgtt = avgtt / nop;
       printf("Average Waiting Time : %.2f\n", avgwt);
       printf("Average Turnaround Time : %.2f\n", avgtt);
       return;
}

int iscomplite(struct sjf arr[], int n)
{
       int i;
       for (i = 0; i < n; i++)
              if (arr[i].st == 0)
                     return 0;
       return 1;
}
void srtf()
{
       int n, i, a, t = 0;
       int p[100];
       float avgwt = 0, avgtt = 0;
       struct sjf arr[100];
       printf("Shortest Remainig Job First\n");
       printf("Enter Number of Processes\n");
       scanf("%d", &n);
       for (i = 0; i < n; i++)
       {
              printf("Enter Arrival Time & Burst Time for Process [P%d]\n", i);
              scanf("%d%d", &arr[i].at, &arr[i].bt);
              arr[i].pno = i;
              arr[i].cbt = arr[i].bt;
              arr[i].st = 0;
              arr[i].tt = arr[i].bt;
              arr[i].wt = 0;
       }
       i = 0;
       while (1)
       {
              if (iscomplite(arr, n))
                     break;
              a = get(arr, t, n);
              p[i] = a;
              arr[a].bt -= 1;
              if (arr[a].bt == 0)
                     arr[a].st = 1;
              t = t + 1;
              i++;
       }
       gantt_chart(arr, p, i, n);
}

//FOR RR

void rr()
{
       int at[100], bt[100], rt[100], temp[100];
       float wait_time = 0, turn_time = 0;
       int c, j, n, time, r, flag = 0, time_q, ltt, i, wt = 0;
       printf("Round Robin\n");
       printf("Enter no.of process:");
       scanf("%d", &n);
       r = n;
       for (c = 0; c < n; c++)
       {
              printf("Enter arrival time of p%d:\t", c + 1);
              scanf("%d", &at[c]);
              printf("Enter burst time of p%d: \t", c + 1);
              scanf("%d", &bt[c]);
              rt[c] = bt[c];
              temp[c] = bt[c];
              printf("\n");
       }
       printf("Enter time quantum:\t");
       scanf("%d", &time_q);
       printf("\n\n\tPID\tAT\tTT\tWT\n\n");
       for (time = 0, c = 0; r != 0;)
       {
              if (rt[c] <= time_q && rt[c] > 0)
              {
                     time = time + rt[c];
                     rt[c] = 0;
                     flag = 1;
              }
              else if (rt[c] > 0)
              {
                     rt[c] = rt[c] - time_q;
                     time = time + time_q;
              }
              if (rt[c] == 0 && flag == 1)
              {
                     wt = 0;
                     wt = time - at[c] - bt[c];
                     r--;
                     printf("\tP%d\t%d\t%d\t%d\n", c + 1, at[c], time - at[c], wt);
                     ltt = time - at[c];
                     wait_time = wait_time + time - at[c] - bt[c];
                     turn_time = turn_time + time - at[c];
                     flag = 0;
              }
              if (c == n - 1)
                     c = 0;
              else if (at[c + 1] <= time)
                     c++;
              else
                     c = 0;
       }
       j = 0;
       printf("\n\n\n");
       printf("GANTT CHART ");
       printf("\n\n\n");
       printf("\t");
       for (i = at[0]; i < time;)
       {
              if (bt[j] >= time_q)
              {
                     printf("P%d\t", j + 1);
                     i += time_q;
                     bt[j] = bt[j] - time_q;
              }
              else if (bt[j] > 0)
              {
                     printf("p%d\t", j + 1);
                     i += bt[j];
                     bt[j] = 0;
              }
              j++;
              if (j >= n)
              {
                     j = 0;
              }
       }
       printf("\n");

       j = 0;
       printf("\t");
       for (i = at[0]; i < time;)
       {
              if (temp[j] >= time_q)
              {
                     printf("%d\t", i + time_q);
                     i += time_q;
                     temp[j] = temp[j] - time_q;
              }
              else if (temp[j] > 0)
              {
                     printf("%d\t", i + temp[j]);
                     i += temp[j];
                     temp[j] = 0;
              }
              j++;
              if (j >= n)
              {
                     j = 0;
              }
       }

       printf("\n\n\n");
       printf("\nAverage_waiting_time=%f\n", wait_time / n);
       printf("Average_turn_around_time=%f\n", turn_time / n);
       printf("\n\n");
}

int main()
{
       int choice;

       while (true)
       {
              printf("Press 1 for FCFS\n");
              printf("Press 2 for SJF\n");
              printf("Press 3 for SRTF\n");
              printf("Press 4 for RR\n");
              printf("Press 5 to Exit\n");

              printf("\nEnter your choice : \n");
              choice = input();
              
              switch (choice)
              {
              case 1:
              {
                     fcfs();
                     break;
              }
              case 2:
              {
                     sjf();
                     break;
              }
              case 3:
                     srtf();
                     break;
              case 4:
                     rr();
                     break;
              case 5:
                     exit(0);
                     break;
              default:
                     printf("Please enter valid option.\n");
              }
       }
}

