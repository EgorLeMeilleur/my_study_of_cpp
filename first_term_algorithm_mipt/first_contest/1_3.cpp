//Даны четыре неотрицательных числа a, b, c и d. Сложить две рациональные дроби a/b и c/d, а их результат представить в виде несократимой дроби m/n. Вывести числа m и n. a, b, c, d ≤ 1000.
#include <iostream>
#include <algorithm>
int sum_of_fractions(int a, int b, int c, int d)
{
	int m, n, mini, i = 2;
	m = d * a + b * c;
	n = b * d;
	mini = std::min(m, n);
	for (; i <= mini; i++)
	{
		if (m % i == 0 && n % i == 0)
		{
			m /= i;
			n /= i;
			i = 1;
		}
	}
	std::cout << m << " ";
	return n;
}
int main()
{
	int a, b, c, d;
	std::cin >> a >> b >> c >> d;
	std::cout << sum_of_fractions(a, b, c, d);
	return 0;
}