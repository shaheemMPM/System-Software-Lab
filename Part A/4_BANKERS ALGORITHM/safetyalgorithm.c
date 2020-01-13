#include <stdio.h>
#include <stdlib.h>

void safetyalgo(int N, int R, int available[R], int max[N][R], int allocated[N][R], int need[N][R]) {
    int work[R], finished[N], order[N], flag, safe, counter = 0, i, j;
    for(i=0; i<N; i++) finished[i] = 1;
    for(i=0; i<R; i++) work[i] = available[i];

    printf("\n\nAvailable Resources: ");
    for(i=0; i<R; i++) printf("%d ", available[i]);
    printf("\nProcess  Max   Allocated Need");
    for(i=0; i<N; i++) {
        printf("\n   %d", i+1);
        printf("\t");
        for(j=0; j<R; j++) printf("%d ", max[i][j]);
        printf("\t");
        for(j=0; j<R; j++) printf("%d ", allocated[i][j]);
        printf("\t");
        for(j=0; j<R; j++) printf("%d ", need[i][j]);
    }

    while(1) {
        safe = 0;
        for(int i=0; i<N; i++) {
            flag = 0;
            for(j=0; j<R; j++)
                if(need[i][j] <= work[j] && finished[i] == 1) flag++;


            if(flag == R) {
                safe = 1;
                order[counter++] = i+1;
                for(j=0; j<R; j++) {
                    finished[i] = 0;
                    work[j] += allocated[i][j];
                    need[i][j] = 0;
                }
            }

        }

        int sum = 0;
        for(i=0; i<N; i++) sum += finished[i];
        if(sum == 0) break;

        if(safe == 0) break;
    }

    if(safe == 0) printf("\n\n Not in safe state");

    else {
        printf("\n\nSafe Sequence: -- ");
        for(i=0; i<N; i++) printf("P%d -- ", order[i]);
    }

}

void main() {
    int N, R;
    printf("Enter number of resources and number of processes: ");
    scanf("%d %d", &R, &N);

    int available[R], allocated[N][R], max[N][R], need[N][R], request[R], p, i, j;

    printf("Enter available resources: ");
    for(i=0; i<R; i++) scanf("%d", &available[i]);

    for(i=0; i<N; i++) {
            printf("\n\nProcess %d", i+1);
            printf("\nMaximum resources: ");
            for(j=0; j<R; j++) scanf("%d", &max[i][j]);
            printf("Allocated resources: ");
            for(j=0; j<R; j++) scanf("%d", &allocated[i][j]);
            for(j=0; j<R; j++) need[i][j] = max[i][j] - allocated[i][j];

    }

    safetyalgo(N, R, available, max, allocated, need);

    while(1) {
        printf("\n\n1. REQUEST RESOURCE");
        printf("\n2. EXIT");

        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\n\nEnter process number: ");
                scanf("%d", &p);
                printf("Additional Resource needed: ");
                for(i=0; i<R; i++) {
                    scanf("%d", &request[i]);
                    allocated[p-1][i] += request[i];
                    available[i] -= request[i];
                }
                for(i=0; i<N; i++) {
                    for(j=0; j<R; j++) need[i][j] = max[i][j] - allocated[i][j];
                }
                safetyalgo(N, R, available, max, allocated, need);
                break;

            case 2:
                exit(0);
                break;

            default: printf("Invalid Input!");
        }
    }

    printf("\n");
}
