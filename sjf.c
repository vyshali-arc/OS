#include <stdio.h>

int main()
{
    int n, i, j;
    int bt[20], wt[20], tat[20];
    int p[20];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        p[i] = i+1;
        printf("Enter BT for P%d: ", i+1);
        scanf("%d", &bt[i]);
    }

    // Sorting based on Burst Time (SJF)
    int temp;
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(bt[i] > bt[j])
            {
                // Swap BT
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap Process ID
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    wt[0] = 0;
    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
    }

    printf("\nProcess\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        avgwt += wt[i];
        avgtat += tat[i];

        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for(i = 0; i < n; i++)
        printf("--------");

    printf("\n|");
    for(i = 0; i < n; i++)
        printf("  P%d   |", p[i]);

    printf("\n ");
    for(i = 0; i < n; i++)
        printf("--------");

    printf("\n0");
    int time = 0;
    for(i = 0; i < n; i++)
    {
        time += bt[i];
        printf("      %d", time);
    }

    printf("\n\nAverage WT = %.2f", avgwt/n);
    printf("\nAverage TAT = %.2f\n", avgtat/n);

    return 0;
}
