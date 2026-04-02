#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10], safe[10];

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Need Matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int process, request[10];

    printf("Enter process number making request: ");
    scanf("%d", &process);

    printf("Enter request vector:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Check conditions
    for(i = 0; i < m; i++)
    {
        if(request[i] > need[process][i])
        {
            printf("Error: Request exceeds need\n");
            return 0;
        }

        if(request[i] > avail[i])
        {
            printf("Resources not available\n");
            return 0;
        }
    }

    // Temporary Allocation
    for(i = 0; i < m; i++)
    {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Initialize
    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    // Safety Algorithm
    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(!finish[i])
            {
                int flag = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found)
        {
            printf("System is NOT in Safe State\n");
            return 0;
        }
    }

    printf("System is in Safe State\nSafe Sequence: ");
    for(i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    printf("\n");

    return 0;
}
