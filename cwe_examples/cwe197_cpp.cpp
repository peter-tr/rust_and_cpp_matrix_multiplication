//CWE-197: Numeric Truncation Error

#include <iostream>
#include <cmath>
double process(double val) {
    float temp = val;
    return temp;
}
int main() {
    const double PI = acos(-1);
    printf("%.10f ?= %.10f\n", PI, process(PI));
}