#include "s21_stack.h"

namespace s21 {
template <typename value_type>
stack<value_type>::stack() {
  stack_list_ = new list<value_type>();
}

template <typename value_type>
stack<value_type>::stack(size_type n) {
  stack_list_ = new list<value_type>(n);
}

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const& items) {
  stack_list_ = new list<value_type>(items);
}

template <typename value_type>
stack<value_type>::stack(const stack& s) {
  stack_list_ = new list<value_type>(*(s.stack_list_));
}

template <typename value_type>
stack<value_type>::stack(stack&& s) {
  stack_list_ = nullptr;
  swap(s);
}

template <typename value_type>
stack<value_type>::~stack() {
  delete stack_list_;
}

template <typename value_type>
stack<value_type>& stack<value_type>::operator=(stack&& s) {
  stack_list_->clear();
  swap(s);
  return *this;
}

template <typename value_type>
stack<value_type>& stack<value_type>::operator=(const stack& s) {
  stack_list_->clear();
  *(stack_list_) = *(s.stack_list_);
  // stack_list_->copy(*(s.stack_list_));
  return *this;
}

template <typename value_type>
typename stack<value_type>::const_reference stack<value_type>::top() {
  return stack_list_->front();
}

template <typename value_type>
bool stack<value_type>::empty() {
  return stack_list_->empty();
}

template <typename value_type>
typename stack<value_type>::size_type stack<value_type>::size() {
  return stack_list_->size();
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  stack_list_->push_front(value);
}

template <typename value_type>
void stack<value_type>::pop() {
  stack_list_->pop_front();
}

template <typename value_type>
void stack<value_type>::swap(stack& s) {
  std::swap(stack_list_, s.stack_list_);
}
}  // namespace s21
