#include <stdio.h>

int main()
{
    int n, i;
    int at[20], bt[20], wt[20], tat[20], ct[20];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time
    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);
    }

    // FCFS Scheduling
    ct[0] = at[0] + bt[0];

    for(i = 1; i < n; i++)
    {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    // Calculate WT and TAT
    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];
    }

    // Display Table
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat/n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf(" ");
    for(i = 0; i < n; i++)
        printf("--------");

    printf("\n|");
    for(i = 0; i < n; i++)
        printf("  P%d   |", i+1);

    printf("\n ");
    for(i = 0; i < n; i++)
        printf("--------");

    printf("\n%d", at[0]);
    for(i = 0; i < n; i++)
        printf("      %d", ct[i]);

    printf("\n");

    return 0;
}
