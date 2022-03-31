#pragma once
#include <iostream>
#include <algorithm>
#include <string>

class Rational 
{
public:
	Rational();
    Rational(int); // NOLINT
	Rational(int, int);

	int GetNumerator() const;
	int GetDenominator() const;
	void SetNumerator(const int);
	void SetDenominator(const int);

    Rational operator+(const Rational& second) const;
    Rational operator-(const Rational& second) const;
    Rational operator*(const Rational& second) const;
    Rational operator/(const Rational& second) const;

    Rational& operator+=(const Rational& second);
    Rational& operator-=(const Rational& second);
    Rational& operator*=(const Rational& second);
    Rational& operator/=(const Rational& second);

    Rational& operator++(); //prefix
    Rational operator++(int); //postfix
    Rational& operator--(); //prefix
    Rational operator--(int); //postfix

    Rational operator-();
    Rational operator+();

    bool operator==(const Rational& second) const;
    bool operator!=(const Rational& second) const;
    bool operator>(const Rational& second) const;
    bool operator<(const Rational& second) const;
    bool operator>=(const Rational& second) const;
    bool operator<=(const Rational& second) const;

    friend std::ostream& operator<<(std::ostream& stream, const Rational& value);
    friend std::istream& operator>>(std::istream& out, Rational& value);
private:
	int numerator = 0;
	int denominator = 1;

    Rational& gcd_();
};