#include <iostream>
#include <sstream>
// #include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

#include <cassert>

using namespace std;

ostream& dlog = cerr;


class error: public runtime_error {
private:
    string Msg;

public:
    error(string s = "error: ")
        : runtime_error("unused"), Msg(s)
    {}
    /* override */ const char* what() const noexcept {
        return Msg.c_str();
    }

    template <class T> error& operator<<(const T& m) {
        ostringstream os;
        os << m;
        Msg += os.str();
        return *this;
    }
};
#define NI throw error(string() + __FUNCTION__  + " - not implemented")


void decodeString(istream& is, ostream& os) {
    const string in  = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const string out = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`|~ \n";

    while (true) {
        char c = is.get();
        if (isspace(c)) 
            return;
        // todo: consider static map
        size_t idx = in.find(c);
        if (idx == string::npos) {
            cerr << "wrong char: " << int(c) << endl;
            throw error(string() + "wrong char: " + c);
        }
        os << out[idx];
        if (is.eof())
            return;
    }
}

string decodeString(const string& s) {
    const string in  = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const string out = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`|~ \n";

    ostringstream os;
    for (char c : s) {
        // if (isspace(c)) 
        //    return;
        // todo: consider static map
        size_t idx = in.find(c);
        if (idx == string::npos) {
            cerr << "wrong char: " << int(c) << endl;
            throw error() << "wrong char: '" << c << "'" << " (" << int(c) <<")";
        }
        os << out[idx];
    }
    return os.str();
}

string getString(istream& is) {
    string s;
    is >> s;


    if (!is.eof()) {
        char space;
        space = is.get();
        dlog << "str: '" << s << "'" << ", space: " << space << '(' << int(space) << ')' << endl;
        assert(space == ' ' || is.eof());
    }


    return decodeString(s);
}

/*
void decodeInt(istream& is, ostream& os) {
    long int val = 0;
    string s;
    char space;
    is >> s; // >> space;
    // dlog << "str: '" << s << "'" << ", space: " << space << endl;
    space = is.get();
    assert(space == ' ');
    // assert(s.size() > 0);
    // reverse(s.begin(), s.end());
    for (char c : s) {
        int digit = int(c) - int('!');
        // todo: check for overload
        val = val * 93 + digit;
    }
    dlog << "decoded int: " << val << " ";
    os << val;
}
*/

int getInt(istream& is) {
    long int val = 0;
    string s;
    is >> s;

    char space;
    space = is.get();
    assert(space == ' ');

    // assert(s.size() > 0);
    // reverse(s.begin(), s.end());
    for (char c : s) {
        int digit = int(c) - int('!');
        // todo: check for overload
        val = val * 93 + digit;
    }
    // dlog << "decoded int: " << val << " ";
    return val;
}

// string decodeWord(string s) {
void parseToken(istream& is, ostream& os) {
    // string s;
    // is >> s;

    // dlog << "word: " << s << endl;
    // string skip;

    if (is.eof())
        return;


    char i = is.get();
    char val = is.peek();

    if (is.eof())
        return;

    dlog << "i: " << i << " = " << int(i) << ", v: " << val << ", pos = " << is.tellg() <<  endl;

    if (i == ' ')
        throw error("space!");
    if (i == 0)
        throw error("zero!");

    // char i = s.at(0);
    // string val = s.substr(1);

    if (false) {}
    else if (i == 'S') {
        os << '"';
        os << getString(is);
        // decodeString(is, os);
        os << '"';
    }
    else if (i == 'I')
        os << getInt(is);
    else if (i == 'U') {
        is.get(); // val
        is.get(); // space
        os << val;
        parseToken(is, os);
    }
    else if (i == 'T' || i == 'F') {
        is.get(); // space
        os << i;
    }
    else if (i == 'B') {
        is.get(); // val
        is.get(); // space
        os << '(';
        parseToken(is, os);
        os << ' ' << val << ' ';
        parseToken(is, os);
        os << ')';
    }
    else if (i == '?') {
        is.get(); // space
        // os << "if(";
        parseToken(is, os);
        os << " ? ";
        parseToken(is, os);
        os << " : ";
        parseToken(is, os);
    }
    else if (i == 'L') {
        /*
        ostringstream refs;
        decodeInt(is, refs); // ref num
        int ref;
        istringstream ris(refs.str());
        ris >> ref;
        */

        int ref = getInt(is);
        os << "( lambda n" << ref << ".";
        parseToken(is, os);
        os << " )";
    }
    else if (i == 'v') {
        /*
        ostringstream refs;
        decodeInt(is, refs); // ref num
        int ref;
        istringstream ris(refs.str());
        ris >> ref;
        */

        int ref = getInt(is);
        os << "n" << ref;
    }
    else {
        string s;
        getline(is, s);
        dlog << "rest: '" << s << "'" << endl;
        NI << " instr: " << i;
    }

    os << ' ';
    parseToken(is, os);
}



int main() {
    // throw error("oops");
    string buf;
    getline(cin, buf, char(0));
    istringstream is(buf);
    // parseToken(cin, cout);
    parseToken(is, cout);
}

