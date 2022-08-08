//Строка называется палиндромом, если она одинаково читается как слева направо, так и справа налево.
//Например, «abba» – палиндром, а «roman» – нет.
//Для заданной строки s длины n(1 ≤ n ≤ 105) требуется подсчитать число пар(i, j), 1 ≤ i < j ≤ n таких,
//что подстрока s[i..j] является палиндромом.

#include <iostream>
#include <vector>

std::vector<int> CountPalindromes(std::string& str, bool is_even) {
	std::vector<int> count_palindromes(str.size());
	int left = 0, right = -1;
	for (int i = 0; i < str.size(); ++i) { 
		count_palindromes[i] = i > right ? 0 : std::min(right - i + 1, count_palindromes[left + (right - i) + is_even]);
		while (i + count_palindromes[i] + 1 - is_even < str.size() && i - count_palindromes[i] - 1 >= 0 &&
			str[i + count_palindromes[i] + 1 - is_even] == str[i - count_palindromes[i] - 1]) {
			++count_palindromes[i];
		}
		if (i + count_palindromes[i] - 1 > right) {
			left = i - count_palindromes[i] + 1 - is_even;
			right = i + count_palindromes[i] - 1;
		}
	}
	return count_palindromes;
}

unsigned long long ManakerAlgorythm(std::string& str) {
	const std::vector<int> odd_palindromes = CountPalindromes(str, false);
	const std::vector<int> even_palindromes = CountPalindromes(str, true);
	unsigned long long count_palindromes = 0;
	for (unsigned int i = 0; i < str.size(); ++i) {
		count_palindromes += odd_palindromes[i] + even_palindromes[i];
	}
	return count_palindromes;
}

int main() {
	std::string str;
	std::cin >> str;
	std::cout << ManakerAlgorythm(str);
	return 0;
}
