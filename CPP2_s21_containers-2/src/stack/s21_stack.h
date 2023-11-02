#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>
#include <limits>

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using value_type = T;

 private:
  list<value_type> *stack_list_;

 public:
  stack();
  stack(size_type n);
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  stack &operator=(stack &&s);
  stack &operator=(const stack &s);
  ~stack();

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);
};
}  // namespace s21

#include "s21_stack.tpp"

#endif /* S21_STACK_H_ */
