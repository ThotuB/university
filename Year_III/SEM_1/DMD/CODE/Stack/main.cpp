#include <iostream>
#include <cstdlib>

int a[3] = {1, 2, 3};
int *p = (int*)malloc(3 * sizeof(int));

int sum(int *p, int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        sum += p[i];
    }
    return sum;
}

int main() {
    sum(a, 3);
}