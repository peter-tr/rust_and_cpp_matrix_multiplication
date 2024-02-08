// CWE457: Use of Uninitialized Variable
#include <cstdio>
int main() {
    bool a;
    int x;
    if (a) {
        x = 5;
    }
    printf("%d\n", x);
}