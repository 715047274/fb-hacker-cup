#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifdef TEST
#include "mocha.h"
int test_case () {
    assert(1 == 1);
    assert(2 == 2);
    return 0;
}
#endif

int main () {
#ifdef TEST
    describe(
        "test case",
        test_case
    );
    return 0;
#endif

#ifdef DEBUG
    printf("Debug Messages\n");
#endif

    int T;
    scanf("%d", &T);
    for (int caseIndex = 1; caseIndex <= T; caseIndex++) {

        /* Parser */

        // print result
        printf("Case #%d: ___\n", caseIndex);
    }

    return 0;
}
