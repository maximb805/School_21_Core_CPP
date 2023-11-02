#include "s21_queue.h"

namespace s21 {
template <typename value_type>
queue<value_type>::queue() {
  queue_list_ = new list<value_type>();
}

template <typename value_type>
queue<value_type>::queue(size_type n) {
  queue_list_ = new list<value_type>(n);
}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const& items) {
  queue_list_ = new list<value_type>(items);
}

template <typename value_type>
queue<value_type>::queue(const queue& q) {
  queue_list_ = new list<value_type>(*(q.queue_list_));
}

template <typename value_type>
queue<value_type>::queue(queue&& q) {
  queue_list_ = nullptr;
  swap(q);
}

template <typename value_type>
queue<value_type>::~queue() {
  delete queue_list_;
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(const queue& q) {
  queue_list_->clear();
  *(queue_list_) = *(q.queue_list_);
  // queue_list_->copy(*(q.queue_list_));
  return *this;
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(queue&& q) {
  queue_list_->clear();
  swap(q);
  return *this;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() {
  return queue_list_->front();
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() {
  return queue_list_->back();
}

template <typename value_type>
bool queue<value_type>::empty() {
  return queue_list_->empty();
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() {
  return queue_list_->size();
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  queue_list_->push_back(value);
}

template <typename value_type>
void queue<value_type>::pop() {
  queue_list_->pop_front();
}

template <typename value_type>
void queue<value_type>::swap(queue& q) {
  std::swap(queue_list_, q.queue_list_);
}
}  // namespace s21
