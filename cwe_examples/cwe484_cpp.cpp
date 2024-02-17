//CWE-484: Omitted Break Statement in Switch
#include <iostream>
using namespace std;
int main() {
int value = 1;
int result;
switch (value)
{
    case 1: result = 1;
    case 2: result = 2;
    case 3: result = 3;
    default: result = 4;
}
cout << result << endl;
}