#include <stdio.h>

int main()
{
    int n, f, i, j;
    int page[50], frame[10];
    int faults = 0, index = 0;

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

    // FIFO Logic
    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < f; j++)
        {
            if(frame[j] == page[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frame[index] = page[i];
            index = (index + 1) % f;
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
