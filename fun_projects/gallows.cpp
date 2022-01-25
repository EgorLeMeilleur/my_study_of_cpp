#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <string>
using namespace std;
bool check_if_letter(char letter) //проверяем, является ли введенный символ буквой
{
	return (letter >= 'А' && letter <= 'я') || (letter == 'ё' || letter == 'Ё');
}
bool check_if_in_word(char letter, string word) //проверяем наличие введенной буквы
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
int returning_index(char letter, string word, int i) //возвращаем номер угаданной буквы
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
bool check_of_cin(string s) //проверяем сколько букв ввел ползователь
{
	if (s.length() > 1)
	{
		return false;
	}
	return true;
}
bool check_already_guessed(char letter, char* array1, char* array, int size) //проверяем, называл ли игрок эту букву раньше
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
void printing_gallows(int mistakes, char* array) //рисуем виселицу и выводим ошибки
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
		std::cout << "\nВаши ошибки - ";
		for (int i = 0; i < 7; i++)
		{
			std::cout << array[i] << " ";
		}
	}
}
void print_number_of_mistakes(int mistakes) //пишем о кол-ве ошибок 
{
	switch (mistakes)
	{
	case 1:
		std::cout << "У вас осталось " << 7 - mistakes << " попыток.";
		break;
	case 2:
		std::cout << "У вас осталось " << 7 - mistakes << " попыток.";
		break;
	case 3:
		std::cout << "У вас осталось " << 7 - mistakes << " попытки.";
		break;
	case 4:
		std::cout << "У вас осталось " << 7 - mistakes << " попытки.";
		break;
	case 5:
		std::cout << "У вас осталось " << 7 - mistakes << " попытки.";
		break;
	case 6:
		std::cout << "У вас осталась " << 7 - mistakes << " попытка.";
		break;
	}
}
void game(string word)
{
	std::cout << "Добро пожаловать в игру \"Виселица\"!";
	char* current_guessed_word = new char[word.size()];
	for (int i = 0; i < word.size(); i++) // игровое поле
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
		std::cout << "\nСлово - ";
		for (int i = 0; i < word.size(); i++)
		{
			std::cout << current_guessed_word[i] << " ";
		}
		printing_gallows(count_of_mistakes, mistakes_array);
		std::cout << "\nУгадайте букву: ";
		char letter;
		string s;
		cin >> s;
		if (!check_of_cin(s))
		{
			std::cout << "Вы ввели слишком много символов, попробуйте еще раз.";
			continue;
		}
		letter = s[0];
		bool check_char = check_if_letter(letter); //проверяем, является ли введенный знак буквой
		bool check_answer = check_if_in_word(letter, word); //проверяем, есть ли буква в слове
		bool check_repeat = check_already_guessed(letter, mistakes_array, current_guessed_word, word.size());
		if (check_char && check_answer && !check_repeat) // если буква есть в слове
		{
			unsigned int index = returning_index(letter, word, 0); //ищем ее индекс
			if (index < word.size())
			{
				current_guessed_word[index] = letter;
				count_of_guessed_letters++;
				if (count_of_guessed_letters >= word.size())
				{
					break;
				}
				for (int i = 0; i < word.size(); i++) //проверяем, есть ли в слове еще такие буквы
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
			std::cout << "Вы верно угадали букву!";
			continue;
		}
		else if (!check_char) //на случай, если символ не буква
		{
			std::cout << "Введённый вами знак не является буквой, попробуйте еще раз.\n";
			continue;
		}
		else if (check_repeat)
		{
			std::cout << "Вы уже вводили эту букву.";
			continue;
		}
		else if (!check_answer) //если буква неправильная
		{
			count_of_mistakes++;
			mistakes_array[count_of_mistakes - 1] = letter;
			if (count_of_mistakes == 7)
			{
				break;
			}
			std::cout << "Ваша буква не верна.\n";
			print_number_of_mistakes(count_of_mistakes);
		}
	}
	if (count_of_guessed_letters == word.size()) //победа
	{
		std::cout << "\nСлово - ";
		for (int i = 0; i < word.size(); i++)
		{
			std::cout << current_guessed_word[i] << " ";
		}
		printing_gallows(count_of_mistakes, mistakes_array);
		std::cout << "\nВы победили!\n";
		std::cout << word << "\n";
	}
	if (count_of_mistakes == 7)
	{
		printing_gallows(count_of_mistakes, mistakes_array); //поражение
		std::cout << "\nВы проиграли!\n" << "Ваше слово - ";
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
		cout << "Файл не может быть открыт.\n";
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