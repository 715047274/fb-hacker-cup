#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

bool isInside (int P, int X, int Y);

#ifdef TEST
#include "mocha.h"
int p_is_0 () {
    int P = 0;
    assert(isInside(P,  0,  0) == false);
    assert(isInside(P, 10, 10) == false);
    return 0;
}

int at_the_center () {
    assert(isInside(  0, 0, 0) == false);
    assert(isInside( 25, 0, 0) == true);
    assert(isInside( 75, 0, 0) == true);
    assert(isInside(100, 0, 0) == true);
    return 0;
}

int radius_too_long () {
    assert(isInside(50,  50, 50) == false);
    assert(isInside(100, 50, 50) == false);
    assert(isInside(50,  50, 40) == false);
    assert(isInside(100, 50, 40) == false);
    return 0;
}

int at_the_axis () {
    int P = 0;
    assert(isInside(P,   0,  50) == false);
    assert(isInside(P,  50,   0) == false);
    assert(isInside(P,   0, -50) == false);
    assert(isInside(P, -50,   0) == false);

    P = 25;
    assert(isInside(P,   0,  50) == true);
    assert(isInside(P,  50,   0) == true);
    assert(isInside(P,   0, -50) == false);
    assert(isInside(P, -50,   0) == false);

    P = 50;
    assert(isInside(P,   0,  50) == true);
    assert(isInside(P,  50,   0) == true);
    assert(isInside(P,   0, -50) == true);
    assert(isInside(P, -50,   0) == false);

    P = 75;
    assert(isInside(P,   0,  50) == true);
    assert(isInside(P,  50,   0) == true);
    assert(isInside(P,   0, -50) == true);
    assert(isInside(P, -50,   0) == true);

    P = 100;
    assert(isInside(P,   0,  50) == true);
    assert(isInside(P,  50,   0) == true);
    assert(isInside(P,   0, -50) == true);
    assert(isInside(P, -50,   0) == true);
    return 0;
}

int same_zone () {
    // zone 1
    assert(isInside(12, 10, 10)   == false);
    assert(isInside(13, 10, 10)   == true);

    // zone 2
    assert(isInside(37, 10, -10)  == false);
    assert(isInside(38, 10, -10)  == true);

    // zone 3
    assert(isInside(62, -10, -10) == false);
    assert(isInside(63, -10, -10) == true);

    // zone 4
    assert(isInside(87, -10, 10)  == false);
    assert(isInside(88, -10, 10)  == true);
    return 0;
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
    stream.in  = fopen("input.txt", "r");
    // stream.out = fopen("output.txt", "w");
#endif

#ifdef TEST
    describe(
        "Progress Pie",
        p_is_0,
        at_the_center,
        radius_too_long,
        at_the_axis,
        same_zone
    );
    return 0;
#endif

    int T;
    fscanf(stream.in, "%d", &T);
    for (int caseIndex = 1; caseIndex <= T; caseIndex++) {

        int P, X, Y;
        fscanf(stream.in, "%d %d %d", &P, &X, &Y);

        // show result
        fprintf(stream.out, "Case #%d: %s\n", caseIndex, isInside(P, X, Y) ? "black" : "white");
    }

    fclose(stream.in);
    fclose(stream.out);
    return 0;
}

// O(n)
bool isInside (const int P, const int X, const int Y) {
    const double R = 50;

#ifdef TEST
    // center is already at (0, 0), do not shift.
    const double x = X;
    const double y = Y;
#else
    const double x = X - 50;
    const double y = Y - 50;
#endif

    // 1. P = 0
    if (P == 0) return false;

    // 2. at the center
    if (x == 0 && y == 0) return true;

    // 3. Radius too long
    if (sqrt(x * x + y * y) > R) return false;

    // 4. on y-axis
    if (x == 0) {
        if (y > 0)  return P > 0;
        if (y < 0)  return P >= 50;
    }

    // 5. on x-axis
    if (y == 0) {
        if (x > 0)  return P >= 25;
        if (x < 0)  return P >= 75;
    }

    // 4. compare zone
    int zone;
    if      (x > 0 && y > 0)  zone = 1;
    else if (x > 0 && y < 0)  zone = 2;
    else if (x < 0 && y < 0)  zone = 3;
    else                      zone = 4;

    int pZone;
    if      (P <= 25)   pZone = 1;
    else if (P <= 50)   pZone = 2;
    else if (P <= 75)   pZone = 3;
    else                pZone = 4;

    if (pZone != zone) {
        return pZone > zone;
    }

    double radian = 2 * M_PI * P / 100;
    double h;
    switch (zone) {
        case 1:
            h = x * tan(M_PI / 2 - radian);
            return y >= h;

        case 2:
            h = x * tan(radian - M_PI / 2);
            return y >= -h;

        case 3:
            h = -x * tan(M_PI * 3 / 2 - radian);
            return y <= -h;

        case 4:
            h = -x * tan(radian - M_PI * 3 / 2);
            return y <= h;
    }

    return false;
}
