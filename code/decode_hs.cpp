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
    assert(space == ' ' || is.eof());

    return decodeString(s);
}

int_t decodeInt(string s) {
    int_t val = 0;

    for (char c : s) {
        int digit = int(c) - int('!');
        // todo: check for overload
        val = val * 94 + digit;
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
    return string(ifIndent, ' ');
}

void parseToken(istream& is, ostream& os) {
    char i = is.get();
    char val = is.peek();

    if (is.eof())
        return;

    if (i == ' ')
        throw error("space!");
    if (i == 0)
        throw error("zero!");

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
        os << "(";
        if (val == '-')
            os << val;
        else if (val == '!')
            os << "not ";
        else if (val == '#')
            os << "toInt";
        else if (val == '$')
            os << "toStr";
        else throw error() << "unknown unary: " << val;

        parseToken(is, os);
        os << ")";
    }
    else if (i == 'T' || i == 'F') {
        is.get(); // space
        os << (i == 'T' ? "True" : "False");
    }
    else if (i == 'B') {
        is.get(); // val
        is.get(); // space

/*
        if (val == '$') {
            // app
            os << '(';
            parseToken(is, os);
            os << ' ';
            parseToken(is, os);
            os << ')';
        }
        else if (val == '$') {
*/
        map<char, string> ops = {
            {'/', "`div`"},
            {'%', "`mod`"},
            {'=', "=="},
            {'|', "||"},
            {'&', "&&"},
            {'T', "`take`"},
            {'D', "`drop`"},
            {'$', ""},
        };

        string op;
        if (ops.count(val))
            op = ops[val];
        else
            op = val;

        os << '(';
        parseToken(is, os);
        os << ' ' << op << ' ';
        parseToken(is, os);
        os << ')';
    }
    else if (i == '?') {
        is.get(); // space
        os << "if ";
        parseToken(is, os);
        // os << " if ";
        ++ifIndent;
        // os << endl << indent() << "then ";
        os << " then ";
        parseToken(is, os);
        // os << endl << indent() << "else ";
        os << " else ";
        parseToken(is, os);
        --ifIndent;
    }
    else if (i == 'L') {
        int ref = getInt(is);
        os << "( \\ n" << ref << " -> ";
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
