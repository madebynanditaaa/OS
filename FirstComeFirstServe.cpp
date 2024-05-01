#include<stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[]) {
    // Calculate waiting time for each process
    wt[0] = 0; // First process has a waiting time of 0

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        // Calculate the wait time as the difference between the previous process's finish time and the current process's arrival time
        wt[i] = (bt[i - 1] + wt[i - 1]) - (at[i] - at[i - 1]);

        // Ensure waiting time is not negative
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    // Calculate waiting time for each process
    findWaitingTime(processes, n, bt, at, wt);

    // Calculate turn around time for each process
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display process details and calculate total waiting and turn around time
    printf("Processes Burst time Waiting time Turn around time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d ", processes[i]);
        printf("\t %d ", bt[i]);
        printf("\t %d ", wt[i]);
        printf("\t %d\n", tat[i]);
    }

    // Calculate and display average waiting and turn around time
    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;
    printf("Average waiting time = %f\n", avg_wt);
    printf("Average turn around time = %f\n", avg_tat);
}

// Driver code
int main() {
    // Process IDs
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];

    // Burst times of all processes
    int burst_time[] = {10, 5, 8};

    // Arrival times of all processes
    int arrival_time[] = {0, 2, 5};

    // Call the function to calculate average times
    findavgTime(processes, n, burst_time, arrival_time);

    return 0;
}
