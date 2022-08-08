#pragma once
#include <iostream>
#include <stdexcept>
#include <cassert>
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, const size_t Rows, const size_t Columns>
class Matrix {
 public:
  T buffer[Rows][Columns]{};
  [[nodiscard]] size_t RowsNumber() const;
  [[nodiscard]] size_t ColumnsNumber() const;
  T& operator()(size_t idx_1, size_t idx_2);
  const T& operator()(size_t idx_1, size_t idx_2) const;
  T& At(size_t idx_1, size_t idx_2);
  const T& At(size_t idx_1, size_t idx_2) const;
  Matrix operator+(const Matrix& second) const;
  Matrix operator-(const Matrix& second) const;
  Matrix& operator+=(const Matrix& second);
  Matrix& operator-=(const Matrix& second);
  bool operator==(const Matrix& second) const;
  bool operator!=(const Matrix& second) const;

  template <class Type, size_t Rows1>
  friend void Transpose(Matrix<Type, Rows1, Rows1>& matrix);
  template <class Type, size_t Rows1>
  friend Type Trace(const Matrix<Type, Rows1, Rows1>& matrix);
  template <class Type, size_t Rows1>
  friend Type Determinant(const Matrix<Type, Rows1, Rows1>& matrix);
  template <class Type, size_t Rows1>
  friend void Inverse(Matrix<Type, Rows1, Rows1>& matrix);
  template <class Type, size_t Rows1>
  friend Matrix<Type, Rows1, Rows1> GetInversed(const Matrix<Type, Rows1, Rows1>& matrix);

  template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
  friend Matrix<Type, RowsFirst, ColumnsFirst>& operator*=(Matrix<Type, RowsFirst, ColumnsFirst>& value,
                                                           const NumberType& n);
  template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
  friend Matrix<Type, RowsFirst, ColumnsFirst>& operator/=(Matrix<Type, RowsFirst, ColumnsFirst>& value,
                                                           const NumberType& n);
  template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
  friend Matrix<Type, RowsFirst, ColumnsFirst> operator*(const Matrix<Type, RowsFirst, ColumnsFirst>& value,
                                                         const NumberType& n);
  template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
  friend Matrix<Type, RowsFirst, ColumnsFirst> operator/(const Matrix<Type, RowsFirst, ColumnsFirst>& value,
                                                         const NumberType& n);

  template <class Type, const size_t RowsFirst, const size_t ColumnsFirst>
  friend Matrix<Type, ColumnsFirst, RowsFirst> GetTransposed(const Matrix<T, RowsFirst, ColumnsFirst>& value);
  template <class Type, const size_t RowsFirst, const size_t ColumnsFirst, const size_t ColumnsSecond>
  friend Matrix<Type, RowsFirst, ColumnsSecond> operator*(const Matrix<Type, RowsFirst, ColumnsFirst>& first,
                                                          const Matrix<Type, ColumnsFirst, ColumnsSecond>& second);
  template <class Type, size_t RowsFirst, size_t ColumnsFirst, size_t ColumnsSecond>
  friend Matrix<Type, RowsFirst, ColumnsSecond>& operator*=(Matrix<Type, RowsFirst, ColumnsFirst>& first,
                                                            const Matrix<Type, ColumnsFirst, ColumnsSecond>& second);
  template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
  friend Matrix<Type, RowsFirst, ColumnsFirst> operator*(const NumberType& n,
                                                         const Matrix<Type, RowsFirst, ColumnsFirst>& value);
  template <class Type, const size_t RowsFirst, const size_t ColumnsFirst>
  friend std::ostream& operator<<(std::ostream& out, const Matrix<Type, RowsFirst, ColumnsFirst>& value);
  template <class Type, const size_t RowsFirst, const size_t ColumnsFirst>
  friend std::istream& operator>>(std::istream& in, Matrix<Type, RowsFirst, ColumnsFirst>& value);

 private:
  template <class Type, size_t Rows1>
  friend Type CountMinor(const Matrix<Type, Rows1, Rows1>& matrix);
  template <class Type, size_t Rows1>
  friend Matrix<Type, Rows1 - 1, Rows1 - 1> LowerMatrix(const Matrix<Type, Rows1, Rows1>& matrix, size_t row,
                                                        size_t column);
  template <class Type, size_t Rows1>
  friend Type CountThreeTwoOneMinor(const Matrix<Type, Rows1, Rows1>& matrix);
};

template <class T, size_t Rows, size_t Columns>
size_t Matrix<T, Rows, Columns>::RowsNumber() const {
  return Rows;
}

template <class T, size_t Rows, size_t Columns>
size_t Matrix<T, Rows, Columns>::ColumnsNumber() const {
  return Columns;
}

template <class T, size_t Rows, size_t Columns>
T& Matrix<T, Rows, Columns>::operator()(size_t idx_1, size_t idx_2) {
  return buffer[idx_1][idx_2];
}

template <class T, size_t Rows, size_t Columns>
const T& Matrix<T, Rows, Columns>::operator()(size_t idx_1, size_t idx_2) const {
  return buffer[idx_1][idx_2];
}

template <class T, size_t Rows, size_t Columns>
T& Matrix<T, Rows, Columns>::At(size_t idx_1, size_t idx_2) {
  if (idx_1 >= Rows || idx_2 >= Columns) {
    throw MatrixOutOfRange();
  }
  return buffer[idx_1][idx_2];
}

template <class T, size_t Rows, size_t Columns>
const T& Matrix<T, Rows, Columns>::At(size_t idx_1, size_t idx_2) const {
  if (idx_1 >= Rows || idx_2 >= Columns) {
    throw MatrixOutOfRange();
  }
  return buffer[idx_1][idx_2];
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator+(const Matrix<T, Rows, Columns>& second) const {
  return Matrix(*this) += second;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator-(const Matrix<T, Rows, Columns>& second) const {
  return Matrix(*this) -= second;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator+=(const Matrix<T, Rows, Columns>& second) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      operator()(i, j) += second(i, j);
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator-=(const Matrix<T, Rows, Columns>& second) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      operator()(i, j) -= second(i, j);
    }
  }
  return *this;
}

template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
Matrix<Type, RowsFirst, ColumnsFirst>& operator*=(Matrix<Type, RowsFirst, ColumnsFirst>& value, const NumberType& n) {
  for (size_t i = 0; i < RowsFirst; ++i) {
    for (size_t j = 0; j < ColumnsFirst; ++j) {
      value(i, j) *= n;
    }
  }
  return value;
}

template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
Matrix<Type, RowsFirst, ColumnsFirst>& operator/=(Matrix<Type, RowsFirst, ColumnsFirst>& value, const NumberType& n) {
  for (size_t i = 0; i < RowsFirst; ++i) {
    for (size_t j = 0; j < ColumnsFirst; ++j) {
      value(i, j) /= n;
    }
  }
  return value;
}

template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
Matrix<Type, RowsFirst, ColumnsFirst> operator*(const Matrix<Type, RowsFirst, ColumnsFirst>& value,
                                                const NumberType& n) {
  Matrix<Type, RowsFirst, ColumnsFirst> result = value;
  return result *= n;
}

template <class Type, class NumberType, size_t RowsFirst, size_t ColumnsFirst>
Matrix<Type, RowsFirst, ColumnsFirst> operator/(const Matrix<Type, RowsFirst, ColumnsFirst>& value,
                                                const NumberType& n) {
  Matrix<Type, RowsFirst, ColumnsFirst> result = value;
  return result /= n;
}

template <class T, size_t Rows, size_t Columns>
bool Matrix<T, Rows, Columns>::operator==(const Matrix<T, Rows, Columns>& second) const {
  for (size_t i = 0u; i < Rows; ++i) {
    for (size_t j = 0u; j < Columns; ++j) {
      if (operator()(i, j) != second(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <class T, size_t Rows, size_t Columns>
bool Matrix<T, Rows, Columns>::operator!=(const Matrix<T, Rows, Columns>& second) const {
  return !(*this == second);
}

template <class Type, size_t Rows1>
void Transpose(Matrix<Type, Rows1, Rows1>& matrix) {
  matrix = GetTransposed(matrix);
}

template <class Type, size_t Rows1>
Type Trace(const Matrix<Type, Rows1, Rows1>& matrix) {
  Type trace = {};
  for (size_t i = 0u; i < Rows1; ++i) {
    trace += matrix(i, i);
  }
  return trace;
}

template <class Type, size_t Rows1>
Type Determinant(const Matrix<Type, Rows1, Rows1>& matrix) {
  if (Rows1 <= 3) {
    return CountThreeTwoOneMinor(matrix);
  }
  char minor_sign = 1;
  Type result = {};
  for (size_t i = 0u; i < Rows1; ++i) {
    result += Determinant(LowerMatrix(matrix, 0, i)) * minor_sign * matrix(0, i);
    minor_sign *= -1;
  }
  return result;
}

template <class Type, size_t Rows1>
Type CountMinor(const Matrix<Type, Rows1, Rows1>& matrix) {
  if (Rows1 <= 3) {
    return CountThreeTwoOneMinor(matrix);
  }
  char minor_sign = 1;
  Type result = {};
  for (size_t i = 0u; i < Rows1; ++i) {
    result += CountMinor(LowerMatrix(matrix, 0, i)) * minor_sign;
    minor_sign *= -1;
  }
  return result;
}

template <class Type, size_t Rows1>
Type CountThreeTwoOneMinor(const Matrix<Type, Rows1, Rows1>& matrix) {
  switch (Rows1) {
    case 3: {
      return matrix(0, 0) * (matrix(1, 1) * matrix(2, 2) - matrix(2, 1) * matrix(1, 2)) -
             matrix(0, 1) * (matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0)) +
             matrix(0, 2) * (matrix(1, 0) * matrix(2, 1) - matrix(2, 0) * matrix(1, 1));
    }
    case 2: {
      return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
    }
    default: { return matrix(0, 0); }
  }
}

template <typename T>
Matrix<T, 1, 1> LowerMatrix(const Matrix<T, 1, 1>& matrix, size_t, size_t) {
  return matrix;
}

template <class Type, size_t Rows1>
Matrix<Type, Rows1 - 1, Rows1 - 1> LowerMatrix(const Matrix<Type, Rows1, Rows1>& matrix, size_t row, size_t column) {
  Matrix<Type, Rows1 - 1, Rows1 - 1> result;
  for (size_t i = 0u; i < Rows1; ++i) {
    if (i == row) {
      continue;
    }
    for (size_t j = 0u; j < Rows1; ++j) {
      if (j == column) {
        continue;
      }
      if (i > row) {
        if (j > column) {
          result(i - 1, j - 1) = matrix(i, j);
        } else {
          result(i - 1, j) = matrix(i, j);
        }
      } else {
        if (j > column) {
          result(i, j - 1) = matrix(i, j);
        } else {
          result(i, j) = matrix(i, j);
        }
      }
    }
  }
  return result;
}

template <class Type, size_t Rows1>
void Inverse(Matrix<Type, Rows1, Rows1>& matrix) {
  matrix = GetInversed(matrix);
}

template <class Type>
Matrix<Type, 1, 1> GetInversed(const Matrix<Type, 1, 1>& matrix) {
  return Matrix<Type, 1, 1>{1 / matrix(0, 0)};
}

template <class Type, size_t Rows1>
Matrix<Type, Rows1, Rows1> GetInversed(const Matrix<Type, Rows1, Rows1>& matrix) {
  Type determinant = Determinant(matrix);
  if (determinant == 0) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<Type, Rows1, Rows1> result;
  for (size_t i = 0u; i < Rows1; ++i) {
    for (size_t j = 0u; j < Rows1; ++j) {
      if ((i + j) % 2) {
        result(i, j) = -CountMinor(LowerMatrix(matrix, i, j));
      } else {
        result(i, j) = CountMinor(LowerMatrix(matrix, i, j));
      }
    }
  }
  Transpose(result);
  return result / determinant;
}

template <class T, const size_t RowsFirst, const size_t ColumnsFirst>
Matrix<T, ColumnsFirst, RowsFirst> GetTransposed(const Matrix<T, RowsFirst, ColumnsFirst>& value) {
  Matrix<T, ColumnsFirst, RowsFirst> result;
  for (size_t i = 0u; i < RowsFirst; ++i) {
    for (size_t j = 0u; j < ColumnsFirst; ++j) {
      result(j, i) = value(i, j);
    }
  }
  return result;
}

template <class Type, const size_t RowsFirst, const size_t ColumnsFirst, const size_t ColumnsSecond>
Matrix<Type, RowsFirst, ColumnsSecond> operator*(const Matrix<Type, RowsFirst, ColumnsFirst>& first,
                                                 const Matrix<Type, ColumnsFirst, ColumnsSecond>& second) {
  Matrix<Type, RowsFirst, ColumnsSecond> result;
  for (size_t i = 0u; i < RowsFirst; ++i) {
    for (size_t j = 0u; j < ColumnsSecond; ++j) {
      for (size_t k = 0u; k < ColumnsFirst; ++k) {
        result(i, j) += first(i, k) * second(k, j);
      }
    }
  }
  return result;
}

template <class Type, size_t RowsFirst, size_t ColumnsFirst, size_t ColumnsSecond>
Matrix<Type, RowsFirst, ColumnsSecond>& operator*=(Matrix<Type, RowsFirst, ColumnsFirst>& first,
                                                   const Matrix<Type, ColumnsFirst, ColumnsSecond>& second) {
  first = first * second;
  return first;
}

template <class Type, class NumberType, const size_t RowsFirst, const size_t ColumnsFirst>
Matrix<Type, RowsFirst, ColumnsFirst> operator*(const NumberType& n,
                                                const Matrix<Type, RowsFirst, ColumnsFirst>& value) {
  Matrix<Type, RowsFirst, ColumnsFirst> result = value;
  return result * n;
}

template <class Type, const size_t RowsFirst, const size_t ColumnsFirst>
std::ostream& operator<<(std::ostream& out, const Matrix<Type, RowsFirst, ColumnsFirst>& value) {
  for (size_t i = 0u; i < RowsFirst; ++i) {
    for (size_t j = 0u; j < ColumnsFirst; ++j) {
      out << value(i, j);
      if (j != ColumnsFirst - 1) {
        out << " ";
      }
    }
    out << "\n";
  }
  return out;
}

template <class Type, const size_t RowsFirst, const size_t ColumnsFirst>
std::istream& operator>>(std::istream& in, Matrix<Type, RowsFirst, ColumnsFirst>& value) {
  for (size_t i = 0u; i < RowsFirst; ++i) {
    for (size_t j = 0u; j < ColumnsFirst; ++j) {
      in >> value(i, j);
    }
  }
  return in;
}