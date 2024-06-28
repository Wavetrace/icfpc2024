// recode string from stdin to stdout.
// by default decode the string
// with "-e" flag encode it

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
using namespace std;

const string in  = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const string out = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`|~ \n";

void recode(bool decode) {
    const string* inp = &::in;
    const string* outp = &::out;

    // if we encode, swap the tables
    if (!decode)
        swap(inp, outp);

    const string& in = *inp;
    const string& out = *outp;

    while (char c = cin.get()) {
        if (cin.eof())
            break;
        // if we encode, encode \n as well
        if (c == '\n' && decode) {
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
}

int main(int argc, char** argv) {
    bool decode = true;
    if (argc > 1 && argv[1] == string("-e"))
        decode = false;

    recode(decode);
    // for convenience; maybe remove
    cout << endl;
}

