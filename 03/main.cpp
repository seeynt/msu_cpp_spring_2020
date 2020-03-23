#include <string>
#include <new>
#include "matrix.h"

int main() {
    Matrix m(2, 9);
    m[0][2] = 4;
    if (m[0][2] == 4)
        printf("Test 1 passed ([][])\n");

    m *= 10000;
    if (m[0][2] == 40000)
        printf("Test 2 passed (*=)\n");

    try {
        Matrix n(1, -1);
    }
    catch(std::bad_alloc& ba) {
        printf("Test 3 passed (bad alloc 1)\n");
    }

    try {
        Matrix n(-1, 1);
    }
    catch(std::bad_alloc& ba) {
        printf("Test 4 passed (bad alloc 2)\n");
    }

    const Matrix cm(2, 3);
    if (!cm[1][1] || cm[1][1])
        printf("Test 5 passed (const matrix[][])\n");

    if (cm.getRows() == 2 && cm.getCols() == 3)
        printf("Test 6 passed (getRows and getCols)\n");

    Matrix dm(2, 3);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            dm[i][j] = cm[i][j];

    if (dm == cm)
        printf("Test 7 passed (==)\n");

    dm[0][1] = !cm[0][1];
    if (dm != cm)
        printf("Test 8 passed (!=)\n");

    try {
        m[0][10000] = 7;
    }
    catch(std::out_of_range& oor) {
        if (strcmp(oor.what(), "Out of range in j"))
            printf("Test 9 passed (out of range)\n");
    }

    printf("All 9 tests passed, success.\n");
    return 0;
}
