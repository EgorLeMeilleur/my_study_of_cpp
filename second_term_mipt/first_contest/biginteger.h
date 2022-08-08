#include <iostream>
#include <vector>
#include <string>

typedef unsigned int uint;

class BigInteger
{
public:

    BigInteger() = default;
    explicit BigInteger(std::string value); 
    explicit operator bool() const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    BigInteger(const T& value) : BigInteger(std::to_string(value)) {}
   
    std::string toString() const;

    BigInteger operator+(const BigInteger& second) const;
    BigInteger operator-(const BigInteger& second) const;
    BigInteger operator*(const BigInteger& second) const;
    BigInteger operator/(const BigInteger& second) const;
    BigInteger operator%(const BigInteger& second) const;
    BigInteger operator*(const int number) const;

    BigInteger& operator+=(const BigInteger& second);
    BigInteger& operator-=(const BigInteger& second);
    BigInteger& operator*=(const BigInteger& second);
    BigInteger& operator/=(const BigInteger& second);
    BigInteger& operator%=(const BigInteger& second);

    BigInteger& operator++(); //prefix
    BigInteger operator++(int); //postfix
    BigInteger& operator--(); //prefix
    BigInteger operator--(int); //postfix

    BigInteger operator-();

    bool operator==(const BigInteger& second) const;
    bool operator!=(const BigInteger& second) const;
    bool operator>(const BigInteger& second) const;
    bool operator<(const BigInteger& second) const;
    bool operator>=(const BigInteger& second) const;
    bool operator<=(const BigInteger& second) const;

    friend std::ostream& operator<<(std::ostream& stream, const BigInteger& value);
    friend std::istream& operator>>(std::istream& out, BigInteger& value);

private:
    std::vector<uint> digits;
    bool is_positive = true;

    template <class T>
    static void reverse(T& a);
    static void delete_leading_zeros(std::vector<uint>& value);
    static void invert(std::vector<uint>& value);

    static bool less(const std::vector<uint>& first, const std::vector<uint>& second);
    static void addition(std::vector<uint>& first, const std::vector<uint>& second);
    static void subtraction(std::vector<uint>& first, const std::vector<uint>& second);
    static void multiplication(std::vector<uint>& first, unsigned long long k);
    static std::vector<uint> multiplication(const std::vector<uint>& first, const std::vector<uint>& second); 
    static std::pair<std::vector<uint>, std::vector<uint>> division(const std::vector<uint>& first, const std::vector<uint>& second); 
};

BigInteger::BigInteger(std::string value) 
{
    if (value == "") { return; }
    if (value[0] == '-') { this->is_positive = false; }
    for (int i = !this->is_positive, size = value.size(); i < size; ++i)
    {
        multiplication(this->digits, 10);
        if (value[i] != '0') 
        {
            addition(this->digits, { static_cast<uint>(value[i] - '0') });
        }
    }
    if (value.size() == 0) { this->is_positive = true; }
}

BigInteger::operator bool() const //неявное приведение к bool
{
    return this->digits.size() != 0;
}

std::string BigInteger::toString() const
{
    if (this->digits.size() == 0) { return "0"; }
    std::string s;
    std::pair<std::vector<uint>, std::vector<uint>> p = { this->digits, {} };
    for (; p.first.size() > 0;) 
    {
        p = division(p.first, { 10 });
        s += '0' + (p.second.size() > 0 ? p.second[0] : 0);
    }
    if (!this->is_positive) { s += '-'; }
    reverse(s);
    return s;
}

void BigInteger::delete_leading_zeros(std::vector<uint>& value)
{
    while (value.size() != 0 && value.back() == 0) { value.pop_back(); }
}

template <class T>
void BigInteger::reverse(T& value) 
{
    for (int i = 0, j = value.size() - 1; i < j;)
    {
        std::swap(value[i++], value[j--]);
    }
}

void BigInteger::invert(std::vector<uint>& value)
{
    bool overflow = true;
    for (int i = 0, size = value.size(); i < size; ++i)
    {
        value[i] = ~value[i] + overflow;
        overflow = value[i] == 0;
    }
}

bool BigInteger::less(const std::vector<uint>& first, const std::vector<uint>& second)
{
    if (first.size() != second.size()) { return first.size() < second.size(); }
    for (int i = first.size() - 1; i >= 0 ; --i)
    {
        if (first[i] != second[i]) { return first[i] < second[i]; }
    }
    return false;
}

void BigInteger::addition(std::vector<uint>& first, const std::vector<uint>& second) //функция сложения
{
    if (first.size() < second.size()) { first.resize(second.size()); }
    unsigned long long addition_result = 0;
    for (int i = 0, size = second.size(); i < size; ++i)
    {
        addition_result += first[i];
        addition_result += second[i];
        first[i] = addition_result;
        addition_result >>= 32;
    }
    if (addition_result > 0) { first.push_back(addition_result); }
}

void BigInteger::subtraction(std::vector<uint>& first, const std::vector<uint>& second) //функция вычитания
{
    if (first.size() < second.size()) { first.resize(second.size()); }
    long long subtraction_result = 0;
    for (int i = 0, size = second.size(); i < size; ++i)
    {
        subtraction_result += (1ll << 32) + first[i] - second[i];
        first[i] = subtraction_result;
        subtraction_result >>= 32;
        subtraction_result--;
    }
    for (int i = second.size(), size = first.size(); i < size && subtraction_result == -1; ++i)
    {
        subtraction_result += (1ll << 32) + first[i];
        first[i] = subtraction_result;
        subtraction_result >>= 32;
        subtraction_result--;
    }
    if (subtraction_result == -1) { invert(first); }
    delete_leading_zeros(first);
}

void BigInteger::multiplication(std::vector<uint>& value, unsigned long long k)
{
    unsigned long long digit = 0;
    for (int i = 0, size = value.size(); i < size; ++i) 
    {
        digit += value[i] * k;
        value[i] = digit;
        digit >>= 32;
    }
    if (digit > 0) { value.push_back(digit); }
}

std::vector<uint> BigInteger::multiplication(const std::vector<uint>& first, const std::vector<uint>& second) 
{
    std::vector<uint> result;
    unsigned long long u = (1ull << 32);
    for (int i = 0, size = second.size(); i < size; i++)
    {
        std::vector<uint> temp = first;
        multiplication(temp, second[i]);
        for (int j = 0; j < i; ++j) 
        {
            multiplication(temp, u);
        }
        addition(result, temp);
    }
    return result;
}

std::pair<std::vector<uint>, std::vector<uint>> BigInteger::division(const std::vector<uint>& first, const std::vector<uint>& second) 
{
    std::vector<uint> result;
    if (less(first, second)) 
    {
        return { result, first };
    }
    std::vector<uint> p(first.end() - second.size() + 1, first.end());
    for (int i = first.size() - second.size(); i >= 0; --i) 
    {
        p.insert(p.begin(), first[i]);
        delete_leading_zeros(p);
        uint k = 0;
        std::vector<uint> t;
        for (unsigned long long max_k = (1ll << 32), mid_k; k < max_k - 1;) 
        {
            mid_k = (max_k + k) / 2;
            t = second;
            multiplication(t, mid_k);
            if (less(p, t)) 
            {
                max_k = mid_k;
            }
            else 
            {
                k = mid_k;
            }
        }
        result.push_back(k);
        t = second;
        multiplication(t, k);
        subtraction(p, t);
    }
    reverse(result);
    delete_leading_zeros(result);
    return { result, p }; 
}

BigInteger& BigInteger::operator+=(const BigInteger& second)
{
    if (this->is_positive == second.is_positive) { addition(this->digits, second.digits); }
    else
    {
        this->is_positive = less(digits, second.digits) ? !(this->is_positive) : this->is_positive;
        subtraction(this->digits, second.digits);
    }
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& second)
{
    if (this->is_positive == second.is_positive)
    {
        this->is_positive = less(digits, second.digits) ? !(this->is_positive) : this->is_positive;
        subtraction(this->digits, second.digits);
    }
    else { addition(this->digits, second.digits); }
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& second)
{
    this->is_positive = (this->is_positive == second.is_positive) ? true : false;
    this->digits = multiplication(this->digits, second.digits);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& second)
{
    this->is_positive = (this->is_positive == second.is_positive) ? true : false;
    this->digits = division(this->digits, second.digits).first;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& second)
{
    this->digits = division(this->digits, second.digits).second;
    return *this;
}

BigInteger BigInteger::operator*(const BigInteger& second) const
{
    return BigInteger(*this) *= second;
}

BigInteger BigInteger::operator*(const int number) const
{
    return BigInteger(*this) *= BigInteger(number);
}

BigInteger BigInteger::operator+(const BigInteger& second) const
{
    return BigInteger(*this) += second;
}

BigInteger BigInteger::operator-(const BigInteger& second) const
{
    return BigInteger(*this) -= second;
}

BigInteger BigInteger::operator/(const BigInteger& second) const
{
    return BigInteger(*this) /= second;
}

BigInteger BigInteger::operator%(const BigInteger& second) const
{
    return BigInteger(*this) %= second;
}

BigInteger& BigInteger::operator++() //prefix
{
    return *this += BigInteger(1);
}

BigInteger BigInteger::operator++(int) //postfix
{
    BigInteger temp = *this;
    this->operator++();
    return temp;
}

BigInteger& BigInteger::operator--() //prefix
{
    return *this -= BigInteger(1);
}

BigInteger BigInteger::operator--(int) //postfix
{
    BigInteger temp = *this;
    this->operator--();
    return temp;
}

bool BigInteger::operator<(const BigInteger& second) const
{
    if (this->is_positive != second.is_positive) { return !(this->is_positive); }
    return (this->is_positive && less(this->digits, second.digits)) 
        || (!(this->is_positive) && less(second.digits, this->digits));
}

bool BigInteger::operator>(const BigInteger& second) const
{
    return second < *this;
}

bool BigInteger::operator==(const BigInteger& second) const
{
    return !(*this < second) && !(second < *this);
}

bool BigInteger::operator!=(const BigInteger& second) const
{
    return *this < second || second < *this;
}

bool BigInteger::operator<=(const BigInteger& second) const
{
    return *this < second || !(second < *this);
}

bool BigInteger::operator>=(const BigInteger& second) const
{
    return second < *this || !(*this < second);
}

BigInteger BigInteger::operator-() // унарный минус
{
    BigInteger temp = *this;
    temp.is_positive = !(this->is_positive);
    return temp;
}

std::ostream& operator<<(std::ostream& stream, const BigInteger& number)
{
    return stream << number.toString();
}

std::istream& operator>>(std::istream& stream, BigInteger& number)
{
    std::string s;
    stream >> s;
    number = BigInteger(s);
    return stream;
}

template <class T>
bool operator<(const T& number, const BigInteger& value)
{
    return BigInteger(number) < value;
}

template <class T>
bool operator>(const T& number, const BigInteger& value)
{
    return BigInteger(number) > value;
}

template <class T>
bool operator==(const T& number, const BigInteger& value)
{
    return BigInteger(number) == value;
}

template <class T>
bool operator!=(const T& number, const BigInteger& value)
{
    return BigInteger(number) != value;
}

template <class T>
bool operator<=(const T& number, const BigInteger& value)
{
    return BigInteger(number) <= value;
}

template <class T>
bool operator>=(const T& number, const BigInteger& value)
{
    return BigInteger(number) >= value;
}

template <class T>
BigInteger operator+(const T& number, const BigInteger& value)
{
    return BigInteger(number) + value;
}

template <class T>
BigInteger operator-(const T& number, const BigInteger& value)
{
    return BigInteger(number) - value;
}

template <class T>
BigInteger operator*(const T& number, const BigInteger& value)
{
    return BigInteger(number) * value;
}

template <class T>
BigInteger operator/(const T& number, const BigInteger& value)
{
    return BigInteger(number) / value;
}

template <class T>
BigInteger operator%(const T& number, const BigInteger& value)
{
    return BigInteger(number) % value;
}