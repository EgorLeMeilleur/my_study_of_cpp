#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <windows.h>

class Matrix
{
	friend std::ostream& operator<< (std::ostream&, const Matrix&);
	friend std::istream& operator>> (std::istream&, Matrix&);
private:
	int lines;
	int columns;
	int** matrix;
public:
	Matrix();
	Matrix(int, int);
	Matrix(Matrix const&);
	~Matrix();

	void setMatrix();
	void printMatrix();
	int determinantMatrix();
	Matrix in_power_of2();
	Matrix& make_one_matrix();

	Matrix operator+ (const Matrix& right);
	Matrix operator- (const Matrix& right);
	Matrix operator* (const Matrix& right);

	Matrix operator* (int n);
	Matrix operator/ (int n);
	Matrix operator+ (int n);
	Matrix operator- (int n);

	Matrix& operator= (const Matrix& right);
	Matrix& operator+= (const Matrix& right);
	Matrix& operator-= (const Matrix& right);
	Matrix& operator*= (const Matrix& right);

	Matrix& operator*= (int n);
	Matrix& operator/= (int n);
	Matrix& operator+= (int n);
	Matrix& operator-= (int n);

	bool operator== (const Matrix&) const;
	bool operator!= (const Matrix& second) const;
};

void game();

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	game();
	return 0;
}

Matrix::Matrix() //конструктор по умолчанию
{
	this->lines = 2;
	this->columns = 2;
	matrix = new int*[lines];
	for (int i = 0; i < lines; i++)
	{
		matrix[i] = new int[columns];
	}
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(Matrix const& mat)
{
	this->lines = mat.lines;
	this->columns = mat.columns;
	matrix = new int* [lines];
	for (int i = 0; i < lines; i++)
	{
		matrix[i] = new int[columns];
	}
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = mat.matrix[i][j];
		}
	}
}

std::ostream& operator<< (std::ostream& output, const Matrix& mat) //перегруженный вывод
{
	for (int i = 0; i < mat.lines; i++)
	{
		for (int j = 0; j < mat.columns; j++)
		{
			output << mat.matrix[i][j];
		}
		std::cout << std::endl;
	}
	output << std::endl; 
	return output;
}

std::istream& operator>> (std::istream& input, Matrix& mat) //перегруженный ввод
{
	for (int i = 0; i < mat.lines; i++)
	{
		for (int j = 0; j < mat.columns; j++)
		{
			input >> mat.matrix[i][j];
		}	
	}
	return input; 
}

Matrix& Matrix::make_one_matrix() //делает единичную матрицу из созданной
{
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			if (i == j)
			{
				this->matrix[i][j] = 1;
			}
			else
			{
				this->matrix[i][j] = 0;
			}
		}
	}
	return *this;
}

Matrix::Matrix(int lines1, int columns1) //конструктор от двух интов
{
	this->lines = lines1;
	this->columns = columns1;
	matrix = new int* [lines];
	for (int i = 0; i < lines; i++)
	{
		matrix[i] = new int[columns];
	}
	for (int i = 0; i < lines1; i++)
	{
		for (int j = 0; j < columns1; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < lines; i++)
	{
		delete[] matrix[i];
	}	
	delete[] matrix;
}

void Matrix::setMatrix() //заполняет матрицу числами
{
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			std::cin >> matrix[i][j];
		}
	}
}

void Matrix::printMatrix() //выводит матрицу
{
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool Matrix::operator== (const Matrix& second) const //оператор сравнения
{
	if (this->columns != second.columns || this->lines != second.lines) return false;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (this->matrix[i][j] != second.matrix[i][j]) return false;
		}
	}
	return true;
}

bool Matrix::operator!= (const Matrix& second) const //оператор сравнения
{
	return !(*this == second);
}

Matrix Matrix::operator+ (const Matrix& second) //сложение матриц
{
	assert(this->columns == second.columns);
	assert(this->lines == second.lines);
	Matrix result(this->lines, this->columns);
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] + second.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator- (const Matrix& second) //вычитание матриц
{
	assert(this->columns == second.columns);
	assert(this->lines == second.lines);
	Matrix result(this->lines, this->columns);
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] - second.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator* (const Matrix& second) //умножение матриц
{
	assert(this->columns == second.lines);
	Matrix result(this->lines, second.columns);
	for (int i = 0; i < result.lines; i++)
	{
		for (int j = 0; j < result.columns; j++)
		{
			int k = 0;
			while (k < result.columns && k < result.lines)
			{
				result.matrix[i][j] += this->matrix[i][k] * second.matrix[k][j];
				k++;
			}
		}
	}
	return result;
}

Matrix Matrix::operator* (int n) //умножение матрицы на число
{
	Matrix result(this->lines, this->columns);
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] * n;
		}
	}
	return result;
}

Matrix Matrix::operator/ (int n) //деление матрицы на число
{
	Matrix result(this->lines, this->columns);
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] / n;
		}
	}
	return result;
}

Matrix& Matrix::operator+= (const Matrix& second) 
{
	assert(this->columns == second.columns);
	assert(this->lines == second.lines);
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->matrix[i][j] += second.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-= (const Matrix& second) 
{
	assert(this->columns == second.columns);
	assert(this->lines == second.lines);
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->matrix[i][j] -= second.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*= (const Matrix& second) 
{
	assert(this->columns == second.lines);
	assert(this->columns == this->lines);
	Matrix result(this->lines, this->columns);
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			int i1 = 0, j1 = j;
			int i2 = i, j2 = 0;
			while (j1 < this->columns && i1 < this->lines)
			{
				result.matrix[i][j] += this->matrix[i1][j1] * second.matrix[i2][j2];
				i1++;
				j2++;
			}
		}
	}
	*this = result;
	return *this;
}

int Matrix::determinantMatrix() //определитель
{
	assert(this->lines == this->columns);
	if (this->columns == 2)
	{
		return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
	}
	else if (this->columns == 3)
	{
		return this->matrix[0][0]*(this->matrix[2][2] * this->matrix[1][1] - this->matrix[2][1] * this->matrix[1][2]) -
			this->matrix[0][1]*(this->matrix[1][0] * this->matrix[2][2] - this->matrix[2][0] * this->matrix[1][2]) +
			this->matrix[0][2]*(this->matrix[1][0] * this->matrix[2][1] - this->matrix[1][1] * this->matrix[2][0]);
	}
	else 
	{
		std::cout << "Can not calculate this size of matrix";
		exit(1);
	}
}

Matrix& Matrix::operator= (const Matrix& right) //оператор присваивания
{
	if (right != *this)
	{
		this->lines = right.lines;
		this->columns = right.columns;
		for (int i = 0; i < right.lines; i++)
		{
			for (int j = 0; j < right.columns; j++)
			{
				this->matrix[i][j] = right.matrix[i][j];
			}	
		}
	}
	return *this;
}

Matrix Matrix::in_power_of2() //возведение в квадрат
{
	assert(this->lines == this->columns);
	Matrix result(this->lines, this->columns);
	result = (*this) * (*this);
	return result;
}

Matrix Matrix::operator+ (int n)
{
	assert(this->lines == this->columns);
	Matrix a(this->lines, this->columns);
	Matrix result(this->lines, this->columns);
	a.make_one_matrix();
	result = a + *this;
	return result;
}
Matrix Matrix::operator- (int n)
{
	assert(this->lines == this->columns);
	Matrix a(this->lines, this->columns);
	Matrix result(this->lines, this->columns);
	a.make_one_matrix();
	result = a - *this;
	return result;
}
Matrix& Matrix::operator*= (int n)
{
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->matrix[i][j] *= n;
		}
	}
	return *this;
}
Matrix& Matrix::operator/= (int n)
{
	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->matrix[i][j] *= n;
		}
	}
	return *this;
}
Matrix& Matrix::operator+= (int n)
{
	assert(this->lines == this->columns);
	Matrix a(this->lines, this->columns);
	a.make_one_matrix();
	*this += a;
	return *this;
}
Matrix& Matrix::operator-= (int n)
{
	assert(this->lines == this->columns);
	Matrix a(this->lines, this->columns);
	a.make_one_matrix();
	*this -= a;
	return *this;
}


void game()
{
	std::cout << "Что вы хотите сделать? Выберите цифру." << "\n" << "1. Умножить две матрицы." << "\n" << "2. Умножить матрицу на число." << "\n" <<
		"3. Возвести матрицу в квадрат." << "\n" << "4. Поделить матрицу на число." << "\n" << "5. Сложить две матрицы." << "\n"
		<< "6. Сложить матрицу с числом." << "\n" << "7. Вычесть из матрицы число." << "\n" << "8. Вычесть две матрицы." << "\n"
		<< "9. Посчитать определитель" << "\n";
	int answer = 0;
	std::cin >> answer;
	switch (answer)
	{
	case 1:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0, l2 = 0, c2 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите размеры второй матрицы" << "\n";
		std::cin >> l2 >> c2;
		Matrix a1(l1, c1), a2(l2, c2);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		std::cout << "Введите элементы второй матрицы" << "\n";
		a2.setMatrix();
		Matrix a3 = a1 * a2;
		std::cout << "Ответ: " << "\n";
		a3.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 2:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите число" << "\n";
		int number;
		std::cin >> number;
		Matrix a1(l1, c1);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		Matrix a2 = a1 * number;
		std::cout << "Ответ: " << "\n";
		a2.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 3:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите элементы первой матрицы" << "\n";
		Matrix a1(l1, c1);
		a1.setMatrix();
		Matrix a2 = a1.in_power_of2();
		std::cout << "Ответ: " << "\n";
		a2.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 4:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите число" << "\n";
		int number;
		std::cin >> number;
		Matrix a1(l1, c1);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		Matrix a2 = a1 / number;
		std::cout << "Ответ: " << "\n";
		a2.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 5:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0, l2 = 0, c2 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите размеры второй матрицы" << "\n";
		std::cin >> l2 >> c2;
		Matrix a1(l1, c1), a2(l2, c2);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		std::cout << "Введите элементы второй матрицы" << "\n";
		a2.setMatrix();
		Matrix a3 = a1 + a2;
		std::cout << "Ответ: " << "\n";
		a3.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 6:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите число" << "\n";
		int number;
		std::cin >> number;
		Matrix a1(l1, c1);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		Matrix a2 = a1 + number;
		std::cout << "Ответ: " << "\n";
		a2.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 7:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите число" << "\n";
		int number;
		std::cin >> number;
		Matrix a1(l1, c1);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		Matrix a2 = a1 - number;
		std::cout << "Ответ: " << "\n";
		a2.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 8:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0, l2 = 0, c2 = 0;
		std::cin >> l1 >> c1;
		std::cout << "Введите размеры второй матрицы" << "\n";
		std::cin >> l2 >> c2;
		Matrix a1(l1, c1), a2(l2, c2);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		std::cout << "Введите элементы второй матрицы" << "\n";
		a2.setMatrix();
		Matrix a3 = a1 - a2;
		std::cout << "Ответ: " << "\n";
		a3.printMatrix();
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	case 9:
	{
		std::cout << "Введите размеры первой матрицы" << "\n";
		int l1 = 0, c1 = 0;
		std::cin >> l1 >> c1;
		Matrix a1(l1, c1);
		std::cout << "Введите элементы первой матрицы" << "\n";
		a1.setMatrix();
		std::cout << "Ответ: " << a1.determinantMatrix() << "\n";
		std::cout << "Хотите продолжить? 1 - да, 0 - нет." << "\n";
		int a = 0;
		std::cin >> a;
		if (a == 1)
		{
			game();
		}
		break;
	}
	}
	return;
}
