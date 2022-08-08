//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш - функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.Начальный размер таблицы должен быть равным 8 - ми.
//Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3 / 4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
//Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
//i - ая проба g(k, i) = g(k, i - 1) + i(mod m).m - степень двойки.

#include <cassert>
#include <vector>
#include <iostream>
#include <string>

class HashTable
{
public:
	explicit HashTable(int table_size) :
		table(table_size), added_nodes_count(0), deleted(table_size, false), deleted_nodes_count(0) { assert(table_size > 0); }
	bool add(const std::string& key);
	bool remove(const std::string& key);
	bool has(const std::string& key) const;

private:
	std::vector<std::string> table;
	int added_nodes_count;
	int deleted_nodes_count;

	std::vector<bool> deleted;

	bool need_rehash() const;
	void rehash();

	int hash1(const std::string& key) const;

};

bool HashTable::add(const std::string& key)
{
	if (need_rehash())
	{
		rehash();
	}
	if (has(key))
	{
		return false;
	}
	else
	{
		int hash = hash1(key);
		for (int i = 0; table[hash] != ""; ++i)
		{
			if (deleted[hash])
			{
				deleted[hash] = false;
				deleted_nodes_count--;
				break;
			}
			hash = (hash + i / 2 + i * i / 2) % table.size(); //квадратичное с коэфф с1 = с2 = 0.5
		}
		table[hash] = key;
		added_nodes_count++;
		return true;
	}
}

bool HashTable::remove(const std::string& key)
{
	int hash = hash1(key);
	for (int i = 0; table[hash] != ""; ++i)
	{
		if (!deleted[hash] && table[hash] == key)
		{
			deleted[hash] = true;
			added_nodes_count--;
			deleted_nodes_count++;
			return true;
		}
		hash = (hash + i / 2 + i * i / 2) % table.size(); //квадратичное с коэфф с1 = с2 = 0.5
	}
	return false;
}

bool HashTable::has(const std::string& key) const
{
	int hash = hash1(key);
	for (int i = 0; table[hash] != ""; ++i)
	{
		if (!deleted[hash] && table[hash] == key)
		{
			return true;
		}
		hash = (hash + i / 2 + i * i / 2) % table.size();  //квадратичное с коэфф с1 = с2 = 0.5
	}
	return false;
}

int HashTable::hash1(const std::string& key) const
{
	int hash = 0;
	for (int i = 0; i < key.size(); i++)
	{
		hash = (hash * 13 + key[i]) % table.size();
	}
	return hash;
}

bool HashTable::need_rehash() const
{
	return (added_nodes_count + deleted_nodes_count) * 4 >= table.size() * 3;
}

void HashTable::rehash()
{
	HashTable new_table(table.size() * 2);
	for (int i = 0; i < deleted.size(); i++)
	{
		if (!deleted[i] && table[i] != "")
		{
			new_table.add(table[i]);
		}
	}
	*this = std::move(new_table);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	HashTable table(8);
	char command = 0;
	std::string value;
	while (std::cin >> command >> value)
	{
		if (command == '+')
		{
			std::cout << (table.add(value) ? "OK" : "FAIL") << "\n";
		}
		else if (command == '?')
		{
			std::cout << (table.has(value) ? "OK" : "FAIL") << "\n";
		}
		else if (command == '-')
		{
			std::cout << (table.remove(value) ? "OK" : "FAIL") << "\n";
		}
	}
	return 0;
}
