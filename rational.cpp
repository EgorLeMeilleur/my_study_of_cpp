#include "rational.h"

Rational::Rational()
{
	this->SetNumerator(0);
	this->SetDenominator(1);
}
Rational::Rational(int value)
{
	this->SetNumerator(value);
	this->SetDenominator(1);
}
Rational::Rational(int numerator, int denominator)
{
	if (denominator < 0) 
	{ 
		denominator = -denominator;
		numerator = -numerator; 
	}
	this->SetNumerator(numerator);
	this->SetDenominator(denominator);
}

int Rational::GetNumerator() const
{
	return this->numerator;
}
int Rational::GetDenominator() const
{
	return this->denominator;
}
void Rational::SetNumerator(const int value)
{
	this->numerator = value;
	this->gcd_();
}
void Rational::SetDenominator(const int value)
{
	this->denominator = std::abs(value);
	this->gcd_();
}

Rational& Rational::gcd_()
{ 
	if (numerator == 0 || numerator == 1 || numerator == -1 || denominator == 1) return *this;
	int temp_a = std::abs(this->numerator), temp_b = std::abs(this->denominator);
	while (temp_a > 0 && temp_b > 0)
	{
		if (temp_a > temp_b) { temp_a %= temp_b; }
		else { temp_b %= temp_a; }
	}
	this->numerator /= temp_a + temp_b;
	this->denominator /= temp_a + temp_b;
	return *this;
}

Rational& Rational::operator+=(const Rational& second)
{
	this->numerator = this->numerator * second.denominator + this->denominator * second.numerator;
	this->denominator = this->denominator * second.denominator;
	this->gcd_();
	return *this;
}
Rational& Rational::operator-=(const Rational& second)
{
	this->numerator = this->numerator * second.denominator - this->denominator * second.numerator;
	this->denominator = this->denominator * second.denominator;
	this->gcd_();
	return *this;
}
Rational& Rational::operator*=(const Rational& second)
{
	this->numerator = this->numerator * second.numerator;
	this->denominator = this->denominator * second.denominator;
	this->gcd_();
	return *this;
}
Rational& Rational::operator/=(const Rational& second)
{
	if (second.numerator < 0)
	{
		this->numerator = this->numerator * -second.denominator;
		this->denominator = this->denominator * std::abs(second.numerator);
	}
	else
	{
		this->numerator = this->numerator * second.denominator;
		this->denominator = this->denominator * std::abs(second.numerator);
	}
	this->gcd_();
	return *this;
}

Rational Rational::operator+(const Rational& second) const
{
	return Rational(*this) += second;
}
Rational Rational::operator-(const Rational& second) const
{
	return Rational(*this) -= second;
}
Rational  Rational::operator*(const Rational& second) const
{
	return Rational(*this) *= second;
}
Rational Rational::operator/(const Rational& second) const
{
	return Rational(*this) /= second;
}

Rational& Rational::operator++() //prefix
{
	return *this += Rational(1);
}
Rational Rational::operator++(int) //postfix
{
	Rational temp = *this;
	this->operator++();
	return temp;
}
Rational& Rational::operator--()
{
	return *this -= Rational(1);
}
Rational Rational::operator--(int)
{
	Rational temp = *this;
	this->operator--();
	return temp;
}

Rational Rational::operator-()
{
	Rational temp = *this;
	temp.SetNumerator(-temp.numerator);
	return temp;
}
Rational Rational::operator+()
{
	Rational temp = *this;
	return temp;
}

bool Rational::operator==(const Rational& second) const
{
	return (this->denominator == second.denominator && this->numerator == second.numerator);
}
bool Rational::operator!=(const Rational& second) const
{
	return !(*this == second);
}
bool Rational::operator>(const Rational& second) const
{
	Rational temp = *this - second;
	return temp.numerator > 0;
}
bool Rational::operator<(const Rational& second) const
{
	return  !(*this >= second);
}
bool Rational::operator>=(const Rational& second) const
{
	return *this == second || *this > second;
}
bool Rational::operator<=(const Rational& second) const
{
	return !(*this > second);
}

std::ostream& operator<<(std::ostream& out, const Rational& value)
{
	if (value.denominator == 1)
	{
		out << value.numerator;
	}
	else if (value.numerator == 0)
	{
		out << 0;
	}
	else
	{
		out << value.numerator << "/" << value.denominator;
	}
	return out;
}
std::istream& operator>>(std::istream& in, Rational& value)
{
	std::string str = "";
	std::string result = "";
	in >> str;
	if (!(str.find('/') != std::string::npos))
	{
		value = std::stoi(str);
		return in;
	}
	while(str[0] != '/' || str.find('/'))
	{
		result += str[0];
		str.erase(0, 1);
	}
	str.erase(0, 1);
	int a = std::stoi(result);
	result = "";
	for (int i = 0; i < str.size(); ++i)
	{
		result += str[i];
	}
	int b = std::stoi(result);
	if (b < 0)
	{
		a = -a;
		b = -b;
	}
	value.numerator = a;
	value.denominator = b;
	value.gcd_();
	return in;
}

int main()
{
	Rational a;
	Rational b = -1;
	Rational c(2, -4);
	std::cout << a << ' ' << b << ' ' << c << ' ';
	//RationalEqual(c, -1, 2);

	a.SetNumerator(6);
	a.SetDenominator(21);
	//RationalEqual(a, 2, 7);
	std::cout << a << ' ' << b << ' ' << c << ' ';

	a += b;
	b -= c;
	c *= a;
	b /= a;
	std::cout << +a << ' ' << -b << ' ' << c << ' ';

	std::cout << std::endl;

	//RationalEqual(+a, -5, 7);
	//RationalEqual(-b, -7, 10);
	//RationalEqual(c, 5, 14);

	std::cout << a + c << std::endl;
	std::cout << a - b << std::endl;
	std::cout << b * c << std::endl;
	std::cout << c / a << std::endl;

	std::cout << ++b << std::endl;
	std::cout << b++ << std::endl;
	std::cout << b-- << std::endl;
	std::cout << --b << std::endl;

	//RationalEqual(a + c, -5, 14);
	//RationalEqual(a - b, -99, 70);
	//RationalEqual(b * c, 1, 4);
	//RationalEqual(c / a, -1, 2);

	//RationalEqual(++b, 17, 10);
	//RationalEqual(b++, 17, 10);
	//RationalEqual(b--, 27, 10);
	//RationalEqual(--b, 7, 10);

	//REQUIRE(a < b);
	//REQUIRE(b > c);
	//REQUIRE_FALSE(a == c);
	if (a == c)
	{
		Rational g = 4;
		std::cout << g << std::endl;
	}
	else
	{
		Rational g = 5;
		std::cout << g << std::endl;
	}
	//std::stringstream is("-7/3 4/6 7");
	//is >> a >> b >> c;
	std::cin >> a >> b >> c;
	std::cout << a << ' ' << b << ' ' << c;
	//std::stringstream os;
	//os << a << ' ' << b << ' ' << c;
	//REQUIRE(os.str() == "-7/3 2/3 7");
}


