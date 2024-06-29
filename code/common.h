#include <iostream>
#include <sstream>
// #include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

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

