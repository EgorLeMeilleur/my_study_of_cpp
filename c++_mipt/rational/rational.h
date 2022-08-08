#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(const int& value);  // NOLINT
  Rational(const int& numerator, const int& denominator);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(const int& value);
  void SetDenominator(const int& value);
  Rational operator+(const Rational& second) const;
  Rational operator-(const Rational& second) const;
  Rational operator*(const Rational& second) const;
  Rational operator/(const Rational& second) const;
  Rational& operator+=(const Rational& second);
  Rational& operator-=(const Rational& second);
  Rational& operator*=(const Rational& second);
  Rational& operator/=(const Rational& second);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  Rational operator-() const;
  Rational operator+() const;
  bool operator==(const Rational& second) const;
  bool operator!=(const Rational& second) const;
  bool operator>(const Rational& second) const;
  bool operator<(const Rational& second) const;
  bool operator>=(const Rational& second) const;
  bool operator<=(const Rational& second) const;
  friend std::ostream& operator<<(std::ostream& out, const Rational& value);
  friend std::istream& operator>>(std::istream& in, Rational& value);
  friend Rational operator+(const int& first, const Rational& second);
  friend Rational operator-(const int& first, const Rational& second);
  friend Rational operator*(const int& first, const Rational& second);
  friend Rational operator/(const int& first, const Rational& second);
  friend bool operator==(const int& first, const Rational& second);
  friend bool operator!=(const int& first, const Rational& second);
  friend bool operator>=(const int& first, const Rational& second);
  friend bool operator<=(const int& first, const Rational& second);
  friend bool operator<(const int& first, const Rational& second);
  friend bool operator>(const int& first, const Rational& second);

 private:
  int numerator_;
  int denominator_;
  void Gcd();
};
