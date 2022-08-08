//Найти, на сколько нулей оканчивается n! = 1 * 2 * 3 * … * n. n ≤ 1000.
#include <iostream>
int zero_factorial(int fact)
{
	int five = 5, number_five = 0;
	while (fact >= five)
	{
		number_five += fact / five;
		five *= 5;
	}
	return number_five;
}
int main()
{
	int fact;
	std::cin >> fact;
	std::cout << zero_factorial(fact);
	return 0;
}