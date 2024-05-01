#include <stdio.h>
#include <limits.h>

struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n, int wt[]) {
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++) {
        rt[i] = proc[i].bt;
    }

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int found_shortest = 0;

    // Process until all processes are completed
    while (complete != n) {
        // Find process with minimum remaining time among the processes that have arrived till the current time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                found_shortest = 1;
            }
        }

        // If no process was found in the current iteration, move time forward
        if (!found_shortest) {
            t++;
            continue;
        }

        // Decrease remaining time for the shortest process
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0) {
            minm = INT_MAX;
        }

        // If a process is completed
        if (rt[shortest] == 0) {
            // Increment the number of completed processes
            complete++;
            found_shortest = 0;

            // Calculate finish time of current process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
            if (wt[shortest] < 0) {
                wt[shortest] = 0;
            }
        }

        // Increment time
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    // Calculate turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
    }
}

// Function to calculate average waiting time and average turnaround time
void findavgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Calculate waiting time for all processes
    findWaitingTime(proc, n, wt);

    // Calculate turnaround time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display the results
    printf("P\tBT\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].bt, proc[i].art, wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Calculate average waiting time and average turnaround time
    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;

    // Print average times
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

// Driver code
int main() {
    // Define processes with their burst time and arrival time
    struct Process proc[] = {
        {1, 6, 2},
        {2, 2, 5},
        {3, 8, 1},
        {4, 3, 0},
        {5, 4, 4}
    };

    // Number of processes
    int n = sizeof(proc) / sizeof(proc[0]);

    // Calculate and print average times
    findavgTime(proc, n);

    return 0;
}
