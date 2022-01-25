#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <string>
using namespace std;
bool check_if_letter(char letter) //���������, �������� �� ��������� ������ ������
{
	return (letter >= '�' && letter <= '�') || (letter == '�' || letter == '�');
}
bool check_if_in_word(char letter, string word) //��������� ������� ��������� �����
{
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] == letter || letter == word[i] + 32 || letter == word[i] - 32)
		{
			return true;
		}
	}
	return false;
}
int returning_index(char letter, string word, int i) //���������� ����� ��������� �����
{
	int j = 0;
	for (; i < word.size(); i++)
	{
		if (word[i] == letter || letter == word[i] + 32 || letter == word[i] - 32)
		{
			return i;
		}
	}
	return word.size() + 1;
}
bool check_of_cin(string s) //��������� ������� ���� ���� �����������
{
	if (s.length() > 1)
	{
		return false;
	}
	return true;
}
bool check_already_guessed(char letter, char* array1, char* array, int size) //���������, ������� �� ����� ��� ����� ������
{
	for (int i = 0; i < size; i++)
	{
		if ((array[i] == letter || letter == array[i] + 32 || letter == array[i] - 32) && letter != '_')
		{
			return true;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if ((array1[i] == letter || letter == array1[i] + 32 || letter == array1[i] - 32) && letter != '_')
		{
			return true;
		}
	}
	return false;
}
void printing_gallows(int mistakes, char* array) //������ �������� � ������� ������
{
	switch (mistakes)
	{
	case 0:
		std::cout << "\n\t ______\n\t |/\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t_|______\n\t|      |";
		break;
	case 1:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t_|______\n\t|      |\n";
		break;
	case 2:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |    |\n\t |\n\t |\n\t |\n\t |\n\t |\n\t_|______\n\t|      |\n";
		break;
	case 3:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |   _|_\n\t |    |\n\t |    |\n\t |\n\t |\n\t |\n\t_|______\n\t|      |\n";
		break;
	case 4:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |   _|_\n\t |  / |\n\t |    |\n\t |\n\t |\n\t |\n\t_|______\n\t|      |\n";
		break;
	case 5:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |   _|_\n\t |  / | \\\n\t |    |\n\t |\n\t |\n\t |\n\t_|______\n\t|      |\n";
		break;
	case 6:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |   _|_\n\t |  / | \\\n\t |    |\n\t |   / \n\t |  / \n\t |\n\t_|______\n\t|      |\n";
		break;
	case 7:
		std::cout << "\n\t ______\n\t |    |\n\t |   (_)\n\t |   _|_\n\t |  / | \\\n\t |    |\n\t |   / \\\n\t |  /   \\\n\t |\n\t_|______\n\t|      |\n";
		break;
	}
	if (mistakes != 0)
	{
		std::cout << "\n���� ������ - ";
		for (int i = 0; i < 7; i++)
		{
			std::cout << array[i] << " ";
		}
	}
}
void print_number_of_mistakes(int mistakes) //����� � ���-�� ������ 
{
	switch (mistakes)
	{
	case 1:
		std::cout << "� ��� �������� " << 7 - mistakes << " �������.";
		break;
	case 2:
		std::cout << "� ��� �������� " << 7 - mistakes << " �������.";
		break;
	case 3:
		std::cout << "� ��� �������� " << 7 - mistakes << " �������.";
		break;
	case 4:
		std::cout << "� ��� �������� " << 7 - mistakes << " �������.";
		break;
	case 5:
		std::cout << "� ��� �������� " << 7 - mistakes << " �������.";
		break;
	case 6:
		std::cout << "� ��� �������� " << 7 - mistakes << " �������.";
		break;
	}
}
void game(string word)
{
	std::cout << "����� ���������� � ���� \"��������\"!";
	char* current_guessed_word = new char[word.size()];
	for (int i = 0; i < word.size(); i++) // ������� ����
	{
		current_guessed_word[i] = '_';
	}
	unsigned int count_of_mistakes = 0, count_of_guessed_letters = 0;
	char* mistakes_array = new char[7];
	for (int i = 0; i < 7; i++)
	{
		mistakes_array[i] = ' ';
	}
	while (count_of_guessed_letters < word.size() && count_of_mistakes < 7)
	{
		std::cout << "\n����� - ";
		for (int i = 0; i < word.size(); i++)
		{
			std::cout << current_guessed_word[i] << " ";
		}
		printing_gallows(count_of_mistakes, mistakes_array);
		std::cout << "\n�������� �����: ";
		char letter;
		string s;
		cin >> s;
		if (!check_of_cin(s))
		{
			std::cout << "�� ����� ������� ����� ��������, ���������� ��� ���.";
			continue;
		}
		letter = s[0];
		bool check_char = check_if_letter(letter); //���������, �������� �� ��������� ���� ������
		bool check_answer = check_if_in_word(letter, word); //���������, ���� �� ����� � �����
		bool check_repeat = check_already_guessed(letter, mistakes_array, current_guessed_word, word.size());
		if (check_char && check_answer && !check_repeat) // ���� ����� ���� � �����
		{
			unsigned int index = returning_index(letter, word, 0); //���� �� ������
			if (index < word.size())
			{
				current_guessed_word[index] = letter;
				count_of_guessed_letters++;
				if (count_of_guessed_letters >= word.size())
				{
					break;
				}
				for (int i = 0; i < word.size(); i++) //���������, ���� �� � ����� ��� ����� �����
				{
					index = returning_index(letter, word, index + 1);
					if (index < word.size())
					{
						current_guessed_word[index] = letter;
						count_of_guessed_letters++;
					}
				}
			}
			if (count_of_guessed_letters == word.size())
			{
				break;
			}
			std::cout << "�� ����� ������� �����!";
			continue;
		}
		else if (!check_char) //�� ������, ���� ������ �� �����
		{
			std::cout << "�������� ���� ���� �� �������� ������, ���������� ��� ���.\n";
			continue;
		}
		else if (check_repeat)
		{
			std::cout << "�� ��� ������� ��� �����.";
			continue;
		}
		else if (!check_answer) //���� ����� ������������
		{
			count_of_mistakes++;
			mistakes_array[count_of_mistakes - 1] = letter;
			if (count_of_mistakes == 7)
			{
				break;
			}
			std::cout << "���� ����� �� �����.\n";
			print_number_of_mistakes(count_of_mistakes);
		}
	}
	if (count_of_guessed_letters == word.size()) //������
	{
		std::cout << "\n����� - ";
		for (int i = 0; i < word.size(); i++)
		{
			std::cout << current_guessed_word[i] << " ";
		}
		printing_gallows(count_of_mistakes, mistakes_array);
		std::cout << "\n�� ��������!\n";
		std::cout << word << "\n";
	}
	if (count_of_mistakes == 7)
	{
		printing_gallows(count_of_mistakes, mistakes_array); //���������
		std::cout << "\n�� ���������!\n" << "���� ����� - ";
		std::cout << word << "\n";
	}
	delete[] current_guessed_word;
	delete[] mistakes_array;
}
int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream f("D://words_for_gallows.txt", ios_base::in);
	if (!f.is_open())
	{
		cout << "���� �� ����� ���� ������.\n";
		return 0;
	}
	string get_words;
	vector<string> words;
	while (!f.eof())
	{
		string get_words;
		f >> get_words;
		words.push_back(get_words);
	}
	game(words[rand() % words.size()]);
	return 0;
}