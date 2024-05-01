#include <stdio.h>

// To calculate the number of page faults
void pageFaults(int frame_size, int* ref, int len, int ctime) {
    // Count variable to count the
    // number of page faults
    int cnt = 0;
    // Arr to simulate frames
    int arr[frame_size][2];

    // To initialise the array
    int i;
    for (i = 0; i < frame_size; i++) {
        arr[i][0] = -1;
        arr[i][1] = ctime;
    }

    int page;

    for (i = 0; i < len; i++) {
        page = ref[i];
        int found = 0;

        int j;
        for (j = 0; j < frame_size; j++) {
            if (arr[j][0] == page) {
                found = 1;
                // update the value of
                // current time
                arr[j][1] = ctime;
                break;
            }
        }

        // If page is not found
        if (!found) {
            // Find the page with min value of ctime,
            // as it will be the least recently used
            int min_index = 0;
            int min = arr[0][1];
            for (j = 1; j < frame_size; j++) {
                if (arr[j][1] < min) {
                    min_index = j;
                    min = arr[j][1];
                }
            }

            // Replace the page at min_index
            arr[min_index][0] = page;
            arr[min_index][1] = ctime;
            cnt++;
        }
        ctime++;
    }
    printf("The number of page faults is : %d\n", cnt);
}

int main() {
    int ref[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int len = sizeof(ref) / sizeof(ref[0]);
    int frame_size = 3;

    int ctime = 0;
    pageFaults(frame_size, ref, len, ctime);
    return 0;
}
