//CWE119: Improper Restriction of Operations within the Bounds of a Memory Buffer
#include <cstdio>
#include <vector>
int main() {
    const std::vector<int> v = {1,2,3,4,5};
    printf("%d\n", v[-1]);
    printf("%d\n", v.at(5));
}