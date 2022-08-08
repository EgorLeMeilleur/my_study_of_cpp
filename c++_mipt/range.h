#pragma once
#include <iostream>
#include <iterator>
#define REVERSE_RANGE_IMPLEMENTED

class RangeIterator {
 public:
  using IteratorCategory = std::bidirectional_iterator_tag;
  using ValueType = int64_t;
  using DifferentType = int64_t;
  using Pointer = void;
  using Reference = ValueType;

  RangeIterator() : state_(0) {
  }
  explicit RangeIterator(ValueType init) : state_(init) {
  }
  RangeIterator(ValueType state, ValueType step) : state_(state), step_(step) {
  }

  RangeIterator& operator++() {
    state_ += step_;
    return *this;
  }
  RangeIterator operator++(int) {
    auto copy = *this;
    operator++();
    return copy;
  }

  RangeIterator& operator--() {
    state_ -= step_;
    return *this;
  }

  RangeIterator operator--(int) {
    auto copy = *this;
    operator--();
    return copy;
  }

  RangeIterator& operator+=(DifferentType count) {
    state_ += step_ * count;
    return *this;
  }

  RangeIterator& operator-=(DifferentType count) {
    state_ += step_ * count;
    return *this;
  }

  Reference operator[](DifferentType idx) const {
    return state_ + step_ * idx;
  }

  Reference operator*() const {
    return state_;
  }

  friend bool operator==(const RangeIterator& lhs, const RangeIterator& rhs) {
    return *lhs == *rhs;
  }

  friend bool operator!=(const RangeIterator& lhs, const RangeIterator& rhs) {
    return !(lhs == rhs);
  }

 private:
  ValueType state_;
  ValueType step_ = 1;
};

class Range {
 public:
  using Iterator = RangeIterator;
  using ValueType = Iterator::ValueType;

  explicit Range(ValueType end) : end_((end < 0) ? 0 : end) {
  }

  Range(ValueType begin, ValueType end, ValueType step = 1) : begin_(begin), end_(end), step_(step) {
    if ((end < begin) && (step > 0) || (begin < end && step < 0) || step == 0) {
      end_ = begin;
      return;
    }
    const auto residual = (end_ - begin_) % step;
    if (residual != 0) {
      end_ += step - residual;
    }
  }

  [[nodiscard]] Iterator begin() const {  // NOLINT
    return {begin_, step_};
  }

  [[nodiscard]] Iterator end() const {  // NOLINT
    return {end_, step_};
  }

  [[nodiscard]] Iterator rbegin() const {  // NOLINT
    return {end_, step_};
  }

  [[nodiscard]] Iterator rend() const {  // NOLINT
    return {begin_, step_};
  }

 private:
  ValueType begin_ = 0;
  ValueType end_ = 0;
  ValueType step_ = 1;
};
