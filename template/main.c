#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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

    int T;
    fscanf(stream.in, "%d", &T);
    for (int caseIndex = 1; caseIndex <= T; caseIndex++) {

        /* Parser */

        // print result
        fprintf(stream.out, "Case #%d: ___\n", caseIndex);
    }

    // close stream
    fclose(stream.in);
    fclose(stream.out);
    return 0;
}
