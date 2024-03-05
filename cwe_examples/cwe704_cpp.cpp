//CWE-704: Incorrect Type Conversion or Cast

#include <cstdio>
#include <string>
#include <vector>

using Vec = std::vector<std::string>;

int main() {
    const Vec x = {"a", "b"};
    printf("%s\n", x.at(0).c_str());
    const Vec y = {{"c", "d"}};
    printf("%s\n", y.at(0).c_str());
}