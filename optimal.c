#include <stdio.h>

int main()
{
    int n, f, i, j, k;
    int page[50], frame[10];
    int faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &page[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nPage\tFrames\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        // Check if page already present
        for(j = 0; j < f; j++)
        {
            if(frame[j] == page[i])
            {
                found = 1;
                break;
            }
        }

        // If not found → Page Fault
        if(!found)
        {
            int pos = -1, farthest = i+1;

            // Find optimal replacement
            for(j = 0; j < f; j++)
            {
                int next_use = -1;

                for(k = i+1; k < n; k++)
                {
                    if(frame[j] == page[k])
                    {
                        next_use = k;
                        break;
                    }
                }

                if(next_use == -1)
                {
                    pos = j;
                    break;
                }

                if(next_use > farthest)
                {
                    farthest = next_use;
                    pos = j;
                }
            }

            if(pos == -1)
                pos = 0;

            frame[pos] = page[i];
            faults++;
        }

        // Print frames
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
