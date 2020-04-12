#include <string>
#include <sstream>
#include <stdexcept>

template <class T>
void insert(std::string& str, int r, T&& val) {
    std::istringstream is(str);
    is >> std::noskipws;
    std::ostringstream os;
    char c; int k;

    while (is >> c) {
        if (c == '{') {
            is >> k;
            if (k == r)
                os << val;
            else
                os << '{' << k << '}';
            is >> c;
        }
        else
            os << c;
    }

    str = os.str();
}

template <class T>
void process(std::string& str, int r, int n, T&& val) {
    if (r < n)
        throw std::runtime_error("Number of args is less than {n}");
    insert(str, r, val);
}

template <class T, class... ArgsT>
void process(std::string& str, int r, int n, T&& val, ArgsT&&... args) {
    insert(str, r, val);
    process(str, r + 1, n, std::forward<ArgsT>(args)...);
}

template <class... ArgsT>
std::string format(const std::string& str, ArgsT&&... args) {
    std::string tmp = str;
    std::istringstream ss(tmp);
    ss >> std::noskipws;
    char c; int k; int n = 0;

    while (ss >> c) {
        if (c == '}')
            throw std::runtime_error("Invalid use of {}");
        if (c == '{') {
            if (ss >> k && k >= 0 && ss >> c && c == '}')
                n = std::max(n, k);
            else
                throw std::runtime_error("Invalid use of {}");
        }
    }

    if (n)
        process(tmp, 0, n, args...);
    return tmp;
}
