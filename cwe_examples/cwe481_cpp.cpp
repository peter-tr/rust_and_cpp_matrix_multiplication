//CWE481: Assigning instead of comparing

#include <iostream>
int foo(int value) {
    if ((value = 0)) 
        return 1;
    else
        return value;
}
int main() {
    printf("{}", foo(0)); 
    printf("{}", foo(1)); 
    return 0;
}
