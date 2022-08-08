#pragma once
#include <iostream>
#include <stdexcept>
#define ARRAY_TRAITS_IMPLEMENTED

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, const size_t N>
class Array {
 public:
  T buffer[N]{};
  T& At(const size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return buffer[idx];
  }
  const T& At(const size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return buffer[idx];
  }
  T& Back() {
    return buffer[N - 1];
  }
  const T& Back() const {
    return buffer[N - 1];
  }
  T& Front() {
    return buffer[0];
  }
  const T& Front() const {
    return buffer[0];
  }
  T* Data() {
    return buffer;
  }
  const T* Data() const {
    return buffer;
  }
  size_t Size() const {
    return N;
  }
  bool Empty() const {
    return N == 0u;
  }
  void Fill(const T& value) {
    for (size_t i = 0u; i < N; ++i) {
      buffer[i] = value;
    }
  }
  void Swap(Array<T, N>& other) {
    for (size_t i = 0u; i < N; ++i) {
      std::swap(buffer[i], other[i]);
    }
  }
  T& operator[](const size_t idx) {
    return buffer[idx];
  }
  const T& operator[](const size_t idx) const {
    return buffer[idx];
  }
};

template <class T, std::size_t N>
size_t GetSize(T (&)[N]) {
  return N;
}

template <class T>
size_t GetSize(T) {
  return 0;
}

template <class T>
int GetRank(T) {
  return 0;
}

template <class T>
int GetRank(T value[]) {
  return 1 + GetRank(value[0]);
}

template <class T>
int GetSizeOfType(T value) {
  return sizeof(value);
}

template <class T>
int GetSizeOfType(T value[]) {
  return GetSizeOfType(value[0]);
}

template <class T>
int GetNumElements(T& value) {
  return sizeof(value) / GetSizeOfType(value);
}
