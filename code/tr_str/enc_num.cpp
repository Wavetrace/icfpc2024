#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <algorithm>
using namespace std;

using int_t = long long int;

string encode(int_t i) {
    bool negative;
    if (i < 0) {
        i *= -1;
        negative = true;
    }

    ostringstream os;
    while (i != 0) {
        os << char(i % 93 + '!');
        i /= 93;
    }

    string res = os.str();
    reverse(res.begin(), res.end());
    res = 'I' + res;

    if (negative)
        res = "U- " + res;

    return res;
}

int main(int argc, char** argv) {
    int_t i;
    cin >> i;
    cout << encode(i) << endl;
}

