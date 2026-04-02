#include <stdio.h>

int main()
{
    int n, i, tq, time = 0, done;
    int bt[20], wt[20], tat[20], rem[20], ct[20];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int timeline[100], timepoints[100];
    int index = 0;

    // Round Robin Logic (Preemptive)
    do
    {
        done = 1;
        for(i = 0; i < n; i++)
        {
            if(rem[i] > 0)
            {
                done = 0;

                timeline[index] = i;

                if(rem[i] > tq)
                {
                    time += tq;
                    rem[i] -= tq;
                }
                else
                {
                    time += rem[i];
                    rem[i] = 0;
                    ct[i] = time;
                }

                timepoints[index] = time;
                index++;
            }
        }
    } while(!done);

    // Calculate WT and TAT
    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];
    }

    // Output Table
    printf("\nProcess\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    printf("|");
    for(i = 0; i < index; i++)
        printf(" P%d |", timeline[i]+1);

    printf("\n0");
    for(i = 0; i < index; i++)
        printf("   %d", timepoints[i]);

    printf("\n\nAverage WT = %.2f", avgwt/n);
    printf("\nAverage TAT = %.2f\n", avgtat/n);

    return 0;
}
