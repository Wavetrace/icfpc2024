#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
using namespace std;

string in  = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
string out = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`|~ \n";

int main(int argc, char** argv) {
    while (char c = cin.get()) {
        if (cin.eof() || cin.fail() || c == 0)
            break;
        if (c == '\n') {
            cout << endl;
            continue;
        }

        size_t idx = in.find(c);
        if (idx == string::npos) {
            cerr << "wrong char: " << int(c) << endl;
            throw runtime_error(string() + "wrong char: " + c);
        }
        cout << out[idx];
    }
    // cout << endl;
}
