//Найти лексикографически - минимальную строку, построенную по z - функции, в алфавите a - z.

#include <iostream>
#include <vector>

typedef unsigned int uint;

std::string ReconstructString(const std::vector<uint>& z_func) {
	bool is_after_block = false;
	std::string result(z_func.size(), 'a');
	std::vector<uint> not_usable_indices;
	for (uint i = 1u; i < z_func.size(); ++i) {
		if (z_func[i] == 0) {
			if (is_after_block) {
				std::vector<bool> used_symbols(26);
				for (uint k : not_usable_indices) {
					used_symbols[result[k] - 'a'] = true;
				}
				unsigned char new_char = 'b';
				while (used_symbols[new_char - 'a']) {
					++new_char;
				}
				result[i] = new_char;
				is_after_block = false;
			} 
			else {
				result[i] = 'b';
			}
		}
		else {
			not_usable_indices.clear();
			uint prefix_length = z_func[i];
			for (uint j = 0u; prefix_length > 0u; ++i, ++j, --prefix_length) {
				if (z_func[i] > prefix_length) {
					prefix_length = z_func[i];
					not_usable_indices.push_back(z_func[i]);
					j = 0u;
				} 
				else if (z_func[i] == prefix_length) {
					not_usable_indices.push_back(z_func[i]);
				}
				result[i] = result[j];
			}
			--i;
			is_after_block = true;
		}
	}
	return result;
}

int main() {
	std::vector<uint> z_func;
	uint z_func_number;
	while (std::cin >> z_func_number) {
		z_func.push_back(z_func_number);
	}
	std::cout << ReconstructString(z_func) << std::endl;
	return 0;
}
