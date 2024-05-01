#include <stdio.h>

int main() {
    // Matrix for storing Process Id, Burst Time, Arrival Time, Waiting Time, and Turn Around Time.
    int A[100][5];
    int i, j, n, total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;
    
    // Read the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    // Read burst times and arrival times
    printf("Enter Burst Time and Arrival Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &A[i][1]);
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &A[i][2]);
        A[i][0] = i + 1; // Process ID
    }
    
    // Sort processes based on arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (A[j][2] < A[i][2]) {
                // Swap process information
                for(int k = 0; k < 3; k++) {
                    int temp = A[i][k];
                    A[i][k] = A[j][k];
                    A[j][k] = temp;
                }
            }
        }
    }
    
    // Calculate waiting times
    A[0][3] = 0; // First process has a waiting time of 0
    for (i = 1; i < n; i++) {
        // Calculate waiting time for each process
        A[i][3] = A[i - 1][3] + A[i - 1][1] - (A[i][2] - A[i - 1][2]);
        
        // Ensure waiting time is not negative
        if (A[i][3] < 0) {
            A[i][3] = 0;
        }
        
        total_wt += A[i][3];
    }
    
    // Calculate turn around times
    printf("P\tBT\tAT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        // Calculate turn around time
        A[i][4] = A[i][3] + A[i][1];
        total_tat += A[i][4];
        
        // Print process information
        printf("P%d\t%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3], A[i][4]);
    }
    
    // Calculate average waiting time and average turn around time
    avg_wt = (float) total_wt / n;
    avg_tat = (float) total_tat / n;
    
    // Print the average waiting and turn around times
    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turn Around Time = %.2f\n", avg_tat);
    
    return 0;
}

