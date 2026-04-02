#include <stdio.h>

int main()
{
    int n, f, i, j;
    int page[50], frame[10], time[10];
    int faults = 0, pos, min;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &page[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize
    for(i = 0; i < f; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrames\n");

    // LRU Logic
    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < f; j++)
        {
            if(frame[j] == page[i])
            {
                time[j] = i;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            min = time[0];
            pos = 0;

            for(j = 1; j < f; j++)
            {
                if(time[j] < min)
                {
                    min = time[j];
                    pos = j;
                }
            }

            frame[pos] = page[i];
            time[pos] = i;
            faults++;
        }

        // Print frame status
        printf("%d\t", page[i]);
        for(j = 0; j < f; j++)
        {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
