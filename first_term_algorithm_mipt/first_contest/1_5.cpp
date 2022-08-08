//Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания(умножением пользоваться нельзя).n ≤ 1000.
#include <iostream>
int out_squares(int number)
{
	int prev = 1, squares = 1;
	for (int i = 0; i < number - 1; i++)
	{
		std::cout << squares << " ";
		prev += 2; // квадрат n можно получить, сложив n первых нечетных чисел
		squares += prev;
	}
	return squares;
}
int main()
{
	int number;
	std::cin >> number;
	std::cout << out_squares(number);
	return 0;
}