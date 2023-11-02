#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <iostream>
#include <limits>

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using value_type = T;

 private:
  list<value_type> *queue_list_;

 public:
  queue();
  queue(size_type n);
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  queue &operator=(const queue &q);
  queue &operator=(queue &&q);
  ~queue();

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);
};
}  // namespace s21

#include "s21_queue.tpp"

#endif /* S21_QUEUE_H_ */
