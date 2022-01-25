//Дан отсортированный массив различных целых чисел A[0..n - 1] и массив целых чисел B[0..m - 1].
//Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//n ≤ 110000, m ≤ 1000.

#include <iostream>
#include <vector>
#include <cmath> 
int binary_search(std::vector<int>& array_1, int& element) //т.к. первый массив отсортирован, бинарным поиском находим место вставки элемента второго массив в первый массив
{
	int first = 0;
	int last = array_1.size() - 1;
	while (first < last) {
		int mid = (first + last) / 2;
		if (array_1[mid] < element) first = mid + 1;
		else last = mid;
	}
	return first;
}
int finding_twins(std::vector<int>& array_1, std::vector<int>& array_2, int i)
{
	int min_abs = 0;
	int position_of_insertion = binary_search(array_1, array_2[i]); //возвращаем позицию вставки
	if (position_of_insertion == 0) min_abs = 0;
	else if (position_of_insertion == array_1.size()) min_abs = array_1.size() - 1;
	else
	{
		if (abs(array_1[position_of_insertion - 1] - array_2[i]) <= abs(array_1[position_of_insertion] - array_2[i]))
		{
			min_abs = position_of_insertion - 1;
		}
		else
		{
			min_abs = position_of_insertion;
		}
		return min_abs;
	}
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, m;
	std::cin >> n;
	std::vector<int> array_1(n);
	for (int i = 0; i < n; i++) std::cin >> array_1[i];
	std::cin >> m;
	std::vector<int> array_2(m);
	for (int i = 0; i < m; i++) std::cin >> array_2[i];
	for (int i = 0; i < m; i++) std::cout << finding_twins(array_1, array_2, i) << " ";
	return 0;
}
