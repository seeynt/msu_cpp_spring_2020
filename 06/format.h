#include <string>
#include <sstream>
#include <stdexcept>

template <class T>
void insert(std::string& str, int r, T&& val) {
    std::ostringstream os;
    int k, j, len = str.length();

    for (int i = 0; i < len; ++i) {
        if (str[i] == '{') {
            j = 0, ++i;
            while (isdigit(str[i + j]))
                ++j;

            k = atoi(str.substr(i, j).c_str());
            if (k == r)
                os << val;
            else
                os << '{' << k << '}';
            i += j;
        }
        else
            os << str[i];
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
    int k, j; int n = 0, len = tmp.length();

    for (int i = 0; i < len; ++i) {
        if (tmp[i] == '}')
            throw std::runtime_error("Invalid use of {}");
        if (tmp[i] == '{') {
            j = 0, ++i;
            while (isdigit(tmp[i + j]))
                ++j;

            k = atoi(tmp.substr(i, j).c_str());
            if (k < 0 || tmp[i + j] != '}')
                throw std::runtime_error("Invalid use of {}");

            i += j;
            n = std::max(n, k);
        }
    }

    if (n)
        process(tmp, 0, n, std::forward<ArgsT>(args)...);
    return tmp;
}
