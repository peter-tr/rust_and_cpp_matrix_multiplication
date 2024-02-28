// CWE-691: Insufficient Control Flow Management
#include <cstdio>

int get_rand() { }

int main() {
    printf("random number: %d\n", get_rand());
}