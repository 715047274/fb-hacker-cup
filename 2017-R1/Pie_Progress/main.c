#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 300
int min_cost(int N, int M, int C[MAX_SIZE][MAX_SIZE]);
int compare_rule (const void * a, const void * b);

int main () {
    int T;
    scanf("%d", &T);
    for (int caseIndex = 1; caseIndex <= T; caseIndex++) {

        int N, M;
        scanf("%d %d", &N, &M);

        int C[MAX_SIZE][MAX_SIZE] = {};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &C[i][j]);
            }
        }

        // print result
        printf("Case #%d: %d\n", caseIndex, min_cost(N, M, C));
    }

    return 0;
}

// min -> Max
int compare_rule (const void * a, const void * b) {
   return *(int*)a - *(int*)b;
}

int min_cost(int N, int M, int C[MAX_SIZE][MAX_SIZE]) {

    // O(M * N)
    for (int i = 0; i < N; i++) {
        // Ο(M log M): min -> Max
        qsort(C[i], M, sizeof(int), compare_rule);

        // add tax to each item
        for (int j = 0; j < M; j++) {
            C[i][j] += 2 * j + 1;   // tax
        }
    }

#ifdef DEBUG
    printf("N = %d, M = %d\n", N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%2d ", C[i][j]);
        }
        puts("");
    }
    puts("");
#endif

    // O(M * N)
    int cost = 0;
    int last_index_of[MAX_SIZE] = {};
    for (int i = 0; i < N; i++) {

        // find out which day has the cheapest pie
        int min_cost = 1000000 + 1;     // max cost = 1000000
        int the_day = -1;

        for (int day = 0; day <= i; day++) {
            int j = last_index_of[day];
            if (j >= M) {
                // this day has no more pie to choose
                continue;
            }

            if (C[day][j] < min_cost) {
                min_cost = C[day][j];
                the_day = day;
            }
        }

#ifdef DEBUG
        printf("%d + ", min_cost);
#endif

        last_index_of[the_day]++;
        cost += min_cost;
    }

    return cost;
}
