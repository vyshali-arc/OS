#include <stdio.h>

int main()
{
    int n, i, j;
    int bt[20], pr[20], wt[20], tat[20];
    int p[20];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        p[i] = i+1;
        printf("Enter BT and Priority for P%d: ", i+1);
        scanf("%d%d", &bt[i], &pr[i]);
    }

    // Sorting based on Priority (lower value = higher priority)
    int temp;
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(pr[i] > pr[j])
            {
                // Swap Priority
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;

                // Swap BT
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;

                // Swap Process ID
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    // Calculate WT
    wt[0] = 0;
    for(i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    printf("\nProcess\tBT\tPR\tWT\tTAT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        avgwt += wt[i];
        avgtat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
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
