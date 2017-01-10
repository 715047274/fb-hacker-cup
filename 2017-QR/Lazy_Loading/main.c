#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct {
    int w;
    int k;
} Criteria [14] = {
    { .w = 50, .k =  1 },
    { .w = 25, .k =  2 },
    { .w = 17, .k =  3 },
    { .w = 13, .k =  4 },
    { .w = 10, .k =  5 },
    { .w =  9, .k =  6 },
    { .w =  8, .k =  7 },
    { .w =  7, .k =  8 },
    { .w =  6, .k =  9 },
    { .w =  5, .k = 10 },
    { .w =  4, .k = 13 },
    { .w =  3, .k = 17 },
    { .w =  2, .k = 25 },
    { .w =  1, .k = 50 }
};

int compare_rule (const void * a, const void * b);
int max_trip (int W[100], int N);

#ifdef TEST
#include "mocha.h"
#define assert_max_trip(R, W...)        \
    int w[] = { W };                    \
    int k = sizeof(w) / sizeof(int);    \
    assert(max_trip(w, k) == R);        \
    return 0

int one_big () {
    assert_max_trip(1, 93);
}

int two_big () {
    assert_max_trip(2, 66, 66);
}

int many_big () {
    assert_max_trip(
        10,
        50, 50, 50, 50, 50,
        50, 50, 50, 50, 50
    );
}
#endif

int main () {
    struct {
        FILE * in;
        FILE * out;
    } stream = {
        .in  = stdin,
        .out = stdout
    };

#ifdef DEBUG
    stream.in = fopen("input.txt", "r");
    // stream.out = fopen("output.txt", "w");
#endif

#ifdef TEST
    describe(
        "lazy loading",
        one_big,
        two_big,
        many_big
    );
    return 0;
#endif

    int T;
    fscanf(stream.in, "%d", &T);
    for (int caseIndex = 1; caseIndex <= T; caseIndex++) {

        int N;
        fscanf(stream.in, "%d", &N);

        int W[100] = {};
        for (int i = 0; i < N; i++) {
            fscanf(stream.in, "%d", &W[i]);
        }

#if (DEBUG == 2)
        fprintf(stream.out, "Case #%d:\n", caseIndex);
        max_trip(W, N);
#else
        fprintf(stream.out, "Case #%d: %d\n", caseIndex, max_trip(W, N));
#endif
    }

    fclose(stream.in);
    fclose(stream.out);
    return 0;
}

int compare_rule (const void * a, const void * b) {
   return *(int*)b - *(int*)a;
}

int max_trip (int W[100], int N) {
    // sort W with descend order: Max -> min
    // Ο(n log n)
    qsort(W, N, sizeof(int), compare_rule);

    int counter = 0;
    int level = 0;  // Criteria level

    int i = 0, j = N - 1;
    while (i <= j && level < 14) {

        if (W[i] < Criteria[level].w) {
            level++;
            continue;
        }

        if (j - i + 1 < Criteria[level].k) {
#if (DEBUG == 2)
            printf("too short\n");
#endif
            break;
        }

#if (DEBUG == 2)
        printf("%2d. %d ", counter + 1, W[i]);
        for (int k = j; k > j - Criteria[level].k + 1; k--) {
            printf("%d ", W[k]);
        }
        puts("");
#endif

        counter++;
        i = i + 1;
        j = j - Criteria[level].k + 1;
    }

#if (DEBUG == 2)
    int remain = j - i + 1;
    printf("Remain List (%d): ", remain);   // i ~ j
    for (int k = i; k <=j; k++) {
        printf("%d ", W[k]);
    }
    printf("\ncounter = %d\n\n\n", counter);
#endif

    return counter;
}
