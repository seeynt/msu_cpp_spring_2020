#include <iostream>
#include <iomanip>

class BigInt {
    int* d;
    long long len;
    bool sign;
    void removeZeroes();
    bool absCmp(const BigInt& a) const;
public:
    BigInt();
    BigInt(int val);
    BigInt(const BigInt& a);
    BigInt(BigInt&& a);
    ~BigInt();
    BigInt& operator=(const BigInt& a);
    BigInt& operator=(BigInt&& a);
    BigInt operator+(const BigInt& a) const;
    BigInt operator-(const BigInt& a) const;
    BigInt operator-() const;
    bool operator==(const BigInt& a) const;
    bool operator!=(const BigInt& a) const;
    bool operator>(const BigInt& a) const;
    bool operator<(const BigInt& a) const;
    bool operator>=(const BigInt& a) const;
    bool operator<=(const BigInt& a) const;
    friend std::ostream& operator<< (std::ostream &out, const BigInt& a);
    friend std::istream& operator>> (std::istream &in, BigInt& a);
};
