#include <stdio.h>

void stpnwait();
void gobackn();
void slrp();

void main()
{
    char ans;
    int n;

    do
    {
        printf("Sliding window techniques:\n");
        printf("1. Stop-and-wait ARQ\n");
        printf("2. Go Back-N ARQ\n");
        printf("3. Selective Repeat ARQ\n");
        printf("The technique to use: ");
        scanf("%d", &n);

        switch (n)
        {
            case 1:
                stpnwait();
                break;

            case 2:
                gobackn();
                break;

            case 3:
                slrp();
                break;

            default:
                printf("Invalid Option");
                break;
        }

        printf("\nDo you want to continue?");
        scanf("%s", &ans);

    } while (ans == 'y' || ans == 'Y');
}

void stpnwait()
{
    int w, i, f, frames[50];
    char a;

    printf("Enter window size: ");
    scanf("%d", &w);

    printf("Enter number of frames to transmit: ");
    scanf("%d", &f);

    printf("\nEnter %d frames:\n", f);
    for (i = 0; i < f; i++)
    {
        scanf("%d", &frames[i]);
    }

    printf("\nWith sliding window protocol the frames will be sent as follows");
    printf("\n(Assuming no corruption of frames)\n\n");
    printf("After sending %d frames at each stage, sender waits for acknowledgement\n\n", w);

    for (i = 0; i < f; i++)
    {
        printf("%d ", frames[i]);

        if ((i + 1) % w == 0 || i == f - 1)
        {
            printf("\nWaiting for acknowledgement...\n");
            printf("Did you receive the acknowledgement? (y/n): ");
            scanf(" %c", &a);

            if (a == 'n')
            {
                printf("Acknowledgement not received... Sending again\n");
                printf("Frame %d sent again and acknowledgement received\n\n", frames[i]);
            }
            else
            {
                printf("Acknowledgement received for above frames\n\n");
            }
        }
    }
}

void gobackn()
{
    int windowsize, totalframes;
    int sent = 0, ack, i;

    printf("Enter window size: ");
    scanf("%d", &windowsize);

    printf("Enter total number of frames: ");
    scanf("%d", &totalframes);

    while (sent < totalframes)
    {
        for (i = 0; i < windowsize && sent < totalframes; i++)
        {
            printf("Frame %d has been transmitted\n", sent);
            sent++;
        }

        printf("\nEnter last acknowledgement received: ");
        scanf("%d", &ack);

        if (ack < sent - 1)
        {
            printf("Acknowledgement lost or error detected\n");
            printf("Go-Back-N: Resending frames from %d\n\n", ack + 1);
            sent = ack + 1;
        }
        else
        {
            printf("All frames till %d acknowledged successfully\n\n", ack);
        }
    }

    printf("All frames transmitted and acknowledged successfully\n");
}

void slrp()
{
    int windowsize, sent = 0, ack, i, sent1;

    printf("enter window size: ");
    scanf("%d", &windowsize);

    while (1)
    {
        for (i = 0; i < windowsize; i++)
        {
            printf("Frame %d has been transmitted.\n", sent);
            sent++;

            if (sent == windowsize)
                break;
        }

        printf("Enter the packet with no acknowledgement received: \n");
        scanf("%d", &ack);

        sent1 = ack;
        printf("frame %d has been transmitted.\n", sent1);
        break;
    }
}

