// recode string from stdin to stdout.
// by default decode the string
// with "-e" flag encode it instead of decoding
// with "-i" flag delete / append the string indicator
// with "-n" flag echo newline at the end
// 
// WARNING: all the flags should be in the first arg, e.g. tr_str -es

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
    bool indicator = false;
    bool newline = false;

    if (argc > 1) {
        string arg = argv[1];
        if (arg.find('e') != string::npos)
            decode = false;
        if (arg.find('i') != string::npos)
            indicator = true;
        if (arg.find('n') != string::npos)
            newline = true;
    }

    if (indicator) {
        if (decode) {
            // skip the indicator char
            char i = cin.get();
            if (i != 'S')
                throw runtime_error("the -i flag was set and the first char is not 'S'");
        }
        else {
            // encode
            cout << 'S';
        }
    }

    recode(decode);
    // for convenience; maybe remove
    if (newline)
        cout << endl;
}

