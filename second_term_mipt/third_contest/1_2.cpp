//Найдите все вхождения шаблона в строку.Длина шаблона – p, длина строки – n.Время O(n + p), доп.память – O(p).
//p ≤ 30000, n ≤ 300000. (z-функция)

#include <iostream>
#include <vector>

typedef unsigned int uint;

std::vector<uint> CalcZFunction(const std::string& str) {
	std::vector<uint> z_func(str.size());
	for (uint i = 1u, left = 0u, right = 0u; i < str.size(); ++i) {
		if (i < right) {
			z_func[i] = std::min(right - i, z_func[i - left]);
		}
		while (i + z_func[i] < str.size() && str[z_func[i]] == str[i + z_func[i]]) {
			++z_func[i];
		}
		if (i + z_func[i] > right) {
			left = i;
			right = i + z_func[i];
		}
	}
	return z_func;
}

std::vector<uint> SearchSubstring(const std::string& pattern, const std::string& text) {
	std::vector<uint> z_func = CalcZFunction(pattern + "#" + text);
	std::vector<uint> result;
	for (uint i = 0u; i < text.size(); ++i) {
		if (z_func[pattern.size() + i + 1] == pattern.size()) {
			result.push_back(i);
		}
	}
	return result;
}

int main() {
	std::string pattern = "", text = "";
	std::cin >> pattern >> text;
	std::vector<uint> result = SearchSubstring(pattern, text);
	for (uint i : result) {
		std::cout << i << " ";
	}
	return 0;
}
