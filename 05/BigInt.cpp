#include "BigInt.h"

static const int base = 1000 * 1000 * 1000;
static const int log_base = 9;

BigInt::BigInt() {
    len = 0;
    sign = 0;
    d = nullptr;
}

BigInt::BigInt(int val) {
    len = 1;
    d = new int[1];
    d[0] = abs(val);
    sign = val < 0 ? 1 : 0;
}

BigInt::BigInt(const BigInt& a) {
    len = a.len;
    sign = a.sign;
    d = new int[len];
    for (long long i = 0; i < len; ++i)
        d[i] = a.d[i];
}

BigInt::BigInt(BigInt&& a) {
    len = a.len;
    sign = a.sign;
    d = a.d;
    a.d = nullptr;
    a.len = 0;
}

BigInt::~BigInt() {
    if (len > 0)
        delete[] d;
}

BigInt& BigInt::operator=(const BigInt& a) {
    if (this == &a)
        return *this;
    len = a.len;
    sign = a.sign;
    int* ptr = new int[len];
    delete[] d;
    d = ptr;
    for (long long i = 0; i < len; ++i)
        d[i] = a.d[i];
    return *this;

}

BigInt& BigInt::operator=(BigInt&& a) {
    len = a.len;
    sign = a.sign;
    delete[] d;
    d = a.d;
    a.d = nullptr;
    a.len = 0;
    return *this;
}

BigInt BigInt::operator+(const BigInt& a) const {
    BigInt b;

    if (sign == a.sign) {
        b.sign = sign;
        if (len != a.len)
            b.len = std::max(len, a.len);
        else
            b.len = d[len - 1] + a.d[len - 1] > 0 ? len : len + 1;

        b.d = new int[b.len];
        int carry = 0;
        for (long long i = 0; i < b.len; ++i) {
            b.d[i] += carry;
            b.d[i] += (i < len ? d[i] : 0);
            b.d[i] += (i < a.len ? a.d[i] : 0);
            carry = (b.d[i] >= base);
            if (carry)
                b.d[i] -= base;
        }
    }


    if (sign != a.sign) {
        const BigInt *l, *r;
        if (this->absCmp(a))
            l = this, r = &a, b.sign = sign, b.len = len;
        else
            r = this, l = &a, b.sign = a.sign, b.len = a.len;

        b.d = new int[b.len];
        int carry = 0;
        for (long long i = 0; i < b.len || carry; ++i) {
            b.d[i] = l->d[i];
            b.d[i] -= carry + (i < r->len ? r->d[i] : 0);
            carry = (b.d[i] < 0);
            if (carry)
                b.d[i] += base;
        }
    }

    b.removeZeroes();
    return b;
}

BigInt BigInt::operator-(const BigInt& a) const {
    BigInt b;
    if (sign != a.sign) {
        b.sign = sign;
        if (len != a.len)
            b.len = std::max(len, a.len);
        else
            b.len = d[len - 1] + a.d[len - 1] >= base ? len : len + 1;

        b.d = new int[b.len];
        int carry = 0;
        for (long long i = 0; i < b.len; ++i) {
            b.d[i] += carry;
            b.d[i] += (i < len ? d[i] : 0);
            b.d[i] += (i < a.len ? a.d[i] : 0);
            carry = (b.d[i] >= base);
            if (carry)
                b.d[i] -= base;
        }
    }

    if (sign == a.sign) {
        const BigInt *l, *r;
        if (this->absCmp(a))
            l = this, r = &a, b.sign = sign, b.len = len;
        else
            r = this, l = &a, b.sign = !a.sign, b.len = a.len;

        b.d = new int[b.len];
        int carry = 0;
        for (long long i = 0; i < b.len || carry; ++i) {
            b.d[i] = l->d[i];
            b.d[i] -= carry + (i < r->len ? r->d[i] : 0);
            carry = (b.d[i] < 0);
            if (carry)
                b.d[i] += base;
        }
    }

    b.removeZeroes();
    return b;
}

BigInt BigInt::operator-() const {
    BigInt b(*this);
    b.sign = !sign;
    return b;
}

bool BigInt::operator==(const BigInt& a) const {
    if (this == &a)
        return 1;
    if (sign != a.sign)
        return 0;
    if (len != a.len)
        return 0;
    for (long long i = 0; i < len; ++i)
        if (d[i] != a.d[i])
            return 0;
    return 1;
}

bool BigInt::operator!=(const BigInt& a) const {
    return !(*this == a);
}

bool BigInt::operator>(const BigInt& a) const {
    if (this == &a)
        return 0;
    if (sign < a.sign)
        return 1;
    if (sign > a.sign)
        return 0;
    if (len > a.len)
        return 1;
    for (long long i = len - 1; i >= 0; --i) {
        if ((d[i] > a.d[i]))
            return !sign;
        if (d[i] < a.d[i])
            return sign;
    }
    return 0;
}

bool BigInt::operator<(const BigInt& a) const {
    if (this == &a)
        return 0;
    if (sign > a.sign)
        return 1;
    if (sign < a.sign)
        return 0;
    if (len < a.len)
        return 1;
    for (long long i = len - 1; i >= 0; --i) {
        if (d[i] < a.d[i])
            return !sign;
        if (d[i] > a.d[i])
            return sign;
    }
    return 0;
}

bool BigInt::operator>=(const BigInt& a) const {
    return !(*this < a);
}

bool BigInt::operator<=(const BigInt& a) const {
    return !(*this > a);
}

std::ostream& operator<< (std::ostream &out, const BigInt& a) {
    if (!a.len) {
        out << 0;
        return out;
    }

    if (a.sign)
        out << '-';

    out << a.d[a.len - 1];
    if (a.len == 1)
        return out;

    for (long long i = a.len - 2; i >= 0; --i)
        out << std::setw(log_base) << std::setfill('0') << a.d[i];

    return out;
}

std::istream& operator>> (std::istream &in, BigInt& a) {
    std::string s;
    in >> s;
    if (s.empty())
        return in;

    if (s[0] == '-') {
        a.sign = 1;
        s = s.substr(1);
    }
    else
        a.sign = 0;

    a.len = (s.length() + (log_base - 1)) / log_base;
    int *ptr = new int[a.len];
    delete[] a.d;
    a.d = ptr;

    int j = 0;
    for (long long i = s.length(); i >= 0; i -= log_base, ++j) {
        if (i < log_base)
            a.d[j] = atoi(s.substr(0, i).c_str());
        else
            a.d[j] = atoi(s.substr(i - log_base, log_base).c_str());
    }

    a.removeZeroes();
    return in;
}

void BigInt::removeZeroes() {
    long long diff = 0;
    for (long long i = len - 1; i >= 0; --i) {
        if (!d[i])
            ++diff;
        else
            break;
    }

    if (diff) {
        len -= diff;
        if (len) {
            int *ptr = new int[len];
            for (long long i = 0; i < len; ++i)
                ptr[i] = d[i];
            delete[] d;
            d = ptr;
        }
        else {
            delete[] d;
            d = nullptr;
            sign = 0;
        }
    }
}

bool BigInt::absCmp(const BigInt& a) const {
    if (len < a.len)
        return 0;
    if (len > a.len)
        return 1;
    for (long long i = len; i >= 0; --i) {
        if (d[i] < a.d[i])
            return 0;
    }
    return 1;
}
