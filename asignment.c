#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sortat(int p[], int at[], int bt[], int n) {
    // Sort processes based on arrival time and burst time.
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                swap(&p[i], &p[j]);
                swap(&at[i], &at[j]);
                swap(&bt[i], &bt[j]);
            } else if (at[i] == at[j]) {
                if (bt[i] > bt[j]) {
                    swap(&p[i], &p[j]);
                    swap(&at[i], &at[j]);
                    swap(&bt[i], &bt[j]);
                }
            }
        }
    }
}

void tatwt(int ct[], int at[], int bt[], int tat[], int wt[], int n) {
    // Calculate Turnaround Time (TAT) and Waiting Time (WT) for each process.
    int i;
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];   // TAT = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i];   // WT = TAT - Burst Time
    }
}

int main() {
    int *p, *at, *bt, *tat, *wt, *ct, pos, i, j, min = 1000, n;
    float awt = 0, atat = 0;

    // Input the number of processes.
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Allocate memory for arrays to store process details.
    p = (int *)malloc(n * sizeof(int));
    at = (int *)malloc(n * sizeof(int));
    bt = (int *)malloc(n * sizeof(int));
    ct = (int *)malloc(n * sizeof(int));
    wt = (int *)malloc(n * sizeof(int));
    tat = (int *)malloc(n * sizeof(int));

    // Input process details (Process No., Arrival Time, Burst Time).
    printf("Enter Process No., Arrival Time, and Burst Time separated by commas:\n");
    for (i = 0; i < n; i++) {
        do {
            printf("For process P%d:\n", i + 1);
            printf("Arrival Time: ");
            scanf("%d", &at[i]);
            if (at[i] == 0) {
                printf("Arrival time cannot be zero. Please re-enter.\n");
            }
        } while (at[i] == 0);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Assign process number
    }

    // Sort processes based on arrival time and burst time.
    sortat(p, at, bt, n);
    ct[0] = at[0] + bt[0]; // Completion time for the first process.

    for (i = 1; i < n; i++) {
        for (j = i; j < n; j++) {
            if (at[j] <= ct[i - 1]) {
                if (bt[j] < min) {
                    min = bt[j];
                    pos = j;
                }
            }
        }

        // Swap processes to schedule the shortest job next.
        swap(&p[i], &p[pos]);
        swap(&at[i], &at[pos]);
        swap(&bt[i], &bt[pos]);
        min = 1000;
        ct[i] = ct[i - 1] + bt[i] + 2; // Calculate completion time.
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT) for each process.
    tatwt(ct, at, bt, tat, wt, n);

    // Output the process details and results.
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    for (i = 0; i < n; i++) {
        atat += tat[i];
        awt += wt[i];
    }

    atat = atat / n; // Calculate the average Turnaround Time.
    awt = awt / n;   // Calculate the average Waiting Time.

    printf("Average Turnaround Time: %.2f\n", atat);
    printf("Average Waiting Time: %.2f\n", awt);
    printf("Total time taken by the processor: %d\n", ct[n - 1]);

    return 0;
}
