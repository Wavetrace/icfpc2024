#include "common.h"

using int_t = long long int;

string decodeString(const string& s) {
    const string in  = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const string out = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`|~ \n";

    ostringstream os;
    for (char c : s) {
        // todo: consider static map
        size_t idx = in.find(c);
        if (idx == string::npos) {
            throw error() << "wrong char: '" << c << "'" << " (" << int(c) <<")";
        }
        os << out[idx];
    }
    return os.str();
}

string getString(istream& is) {
    string s;
    is >> s;


    char space;
    space = is.get();
    // dlog << "str: '" << s << "'" << ", space: " << space << '(' << int(space) << ')' << endl;
    assert(space == ' ' || is.eof());


    return decodeString(s);
}

int_t decodeInt(string s) {
    int_t val = 0;

    for (char c : s) {
        int digit = int(c) - int('!');
        // todo: check for overload
        val = val * 93 + digit;
        // dlog << "decoding int, val = " << val << endl;
    }
    return val;
}

int_t getInt(istream& is) {
    string s;
    is >> s;

    char space;
    space = is.get();
    assert(space == ' ' || is.eof());

    return decodeInt(s);
}




int ifIndent = 0;

string indent() {
    // return string(' ', ifIndent);
    return string(ifIndent, ' ');
}

void parseToken(istream& is, ostream& os) {
    char i = is.get();
    char val = is.peek();

    if (is.eof())
        return;

    // dlog << "i: " << i << " = " << int(i) << ", v: " << val << ", pos = " << is.tellg() <<  endl;

    if (i == ' ')
        throw error("space!");
    if (i == 0)
        throw error("zero!");

    // os << indent();

    if (false) {}
    else if (i == 'S') {
        os << '"';
        os << getString(is);
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

        // operator in infix
        // os << ' ' << val << ' ';
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
        ++ifIndent;
        os << endl << indent();
        parseToken(is, os);
        os << " : ";
        os << endl << indent();
        parseToken(is, os);
        --ifIndent;
    }
    else if (i == 'L') {
        int ref = getInt(is);
        os << "( lambda n" << ref << ".";
        parseToken(is, os);
        os << " )";
    }
    else if (i == 'v') {
        int ref = getInt(is);
        os << "n" << ref;
    }
    else {
        is.unget();
        NI << " instr: '" << i << "'";
    }

    // dlog << "parsed token: " << i << endl;
    os << ' ' << flush;
}



int main() {
    // make tellg work
    string buf;
    getline(cin, buf, char(0));
    istringstream is(buf);

    try {
        parseToken(is, cout);
        if (!is.eof())
            throw error("input left");
    } catch(exception& e) {
        cerr << "error parsing at " << is.tellg() << ": " << e.what() << endl;
        string s;
        getline(is, s);
        // move rest to ex handler
        dlog << "rest: '" << s << "'" << endl;
    }

}

