#include <iostream>
using namespace std;

// just output the base94 charset
int main() {
    for (auto i = 33; i < 127; ++i) {
        cout << char(i);
    }
}
