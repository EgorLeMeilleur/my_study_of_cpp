#include "rational.h"

Rational::Rational() : numerator_(0), denominator_(1) {
}
Rational::Rational(const int& value) : numerator_(value), denominator_(1) {
}
Rational::Rational(const int& numerator, const int& denominator) : numerator_(numerator), denominator_(denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  Gcd();
}
int Rational::GetNumerator() const {
  return numerator_;
}
int Rational::GetDenominator() const {
  return denominator_;
}
void Rational::SetNumerator(const int& value) {
  numerator_ = value;
  Gcd();
}
void Rational::SetDenominator(const int& value) {
  if (value == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = value;
  Gcd();
}
void Rational::Gcd() {
  int gcd = std::gcd(numerator_, denominator_);
  if (gcd != 1) {
    numerator_ /= gcd;
    denominator_ /= gcd;
  }
  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}
Rational& Rational::operator+=(const Rational& second) {
  numerator_ = numerator_ * second.denominator_ + denominator_ * second.numerator_;
  denominator_ = denominator_ * second.denominator_;
  Gcd();
  return *this;
}
Rational& Rational::operator-=(const Rational& second) {
  numerator_ = numerator_ * second.denominator_ - denominator_ * second.numerator_;
  denominator_ = denominator_ * second.denominator_;
  Gcd();
  return *this;
}
Rational& Rational::operator*=(const Rational& second) {
  numerator_ = numerator_ * second.numerator_;
  denominator_ = denominator_ * second.denominator_;
  Gcd();
  return *this;
}
Rational& Rational::operator/=(const Rational& second) {
  if (second.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (second.numerator_ < 0) {
    numerator_ = numerator_ * -second.denominator_;
    denominator_ = denominator_ * std::abs(second.numerator_);
  } else {
    numerator_ = numerator_ * second.denominator_;
    denominator_ = denominator_ * std::abs(second.numerator_);
  }
  Gcd();
  return *this;
}
Rational Rational::operator+(const Rational& second) const {
  return Rational(*this) += second;
}
Rational Rational::operator-(const Rational& second) const {
  return Rational(*this) -= second;
}
Rational Rational::operator*(const Rational& second) const {
  return Rational(*this) *= second;
}
Rational Rational::operator/(const Rational& second) const {
  return Rational(*this) /= second;
}
Rational& Rational::operator++() {
  return *this += Rational(1);
}
Rational Rational::operator++(int) {
  Rational temp = *this;
  operator++();
  return temp;
}
Rational& Rational::operator--() {
  return *this -= Rational(1);
}
Rational Rational::operator--(int) {
  Rational temp = *this;
  operator--();
  return temp;
}
Rational Rational::operator-() const {
  return Rational(-numerator_, denominator_);
}
Rational Rational::operator+() const {
  return *this;
}
bool Rational::operator==(const Rational& second) const {
  return (denominator_ == second.denominator_ && numerator_ == second.numerator_);
}
bool Rational::operator!=(const Rational& second) const {
  return !(*this == second);
}
bool Rational::operator>(const Rational& second) const {
  Rational temp = *this - second;
  return temp.numerator_ > 0;
}
bool Rational::operator<(const Rational& second) const {
  return !(*this >= second);
}
bool Rational::operator>=(const Rational& second) const {
  return *this == second || *this > second;
}
bool Rational::operator<=(const Rational& second) const {
  return !(*this > second);
}
std::ostream& operator<<(std::ostream& out, const Rational& value) {
  if (value.denominator_ == 1) {
    out << value.numerator_;
  } else {
    out << value.numerator_ << "/" << value.denominator_;
  }
  return out;
}
std::istream& operator>>(std::istream& in, Rational& value) {
  std::string str;
  in >> str;
  auto slash = str.find('/');
  if (slash != std::string::npos) {
    value = Rational(std::stoi(str.substr(0, slash)), std::stoi(str.substr(slash + 1, str.size() - slash - 1)));
  } else {
    value.numerator_ = std::stoi(str);
    value.denominator_ = 1;
  }
  return in;
}
Rational operator+(const int& first, const Rational& second) {
  return Rational(first) + second;
}
Rational operator-(const int& first, const Rational& second) {
  return Rational(first) - second;
}
Rational operator*(const int& first, const Rational& second) {
  return Rational(first) * second;
}
Rational operator/(const int& first, const Rational& second) {
  return Rational(first) / second;
}
bool operator==(const int& first, const Rational& second) {
  return Rational(first) == second;
}
bool operator!=(const int& first, const Rational& second) {
  return Rational(first) != second;
}
bool operator>=(const int& first, const Rational& second) {
  return Rational(first) >= second;
}
bool operator<=(const int& first, const Rational& second) {
  return Rational(first) <= second;
}
bool operator<(const int& first, const Rational& second) {
  return Rational(first) < second;
}
bool operator>(const int& first, const Rational& second) {
  return Rational(first) > second;
}
