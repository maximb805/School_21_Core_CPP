#include "s21_list.h"

namespace s21 {

template <typename T>
template <typename value_type>
list<T>::ListIterator<value_type>::ListIterator() {
  pNode_ = nullptr;
}

template <typename T>
template <typename value_type>
list<T>::ListConstIterator<value_type>::ListConstIterator() {}

template <typename T>
template <typename value_type>
void list<T>::ListIterator<value_type>::next() {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  this->pNode_ = this->pNode_->next_;
}

template <typename T>
template <typename value_type>
void list<T>::ListIterator<value_type>::prev() {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  this->pNode_ = this->pNode_->prev_;
}

template <typename T>
template <typename value_type>
bool list<T>::ListIterator<value_type>::isEqual(
    const const_iterator& other) const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return other.pNode_ == this->pNode_;
}

template <typename T>
template <typename value_type>
bool list<T>::ListIterator<value_type>::isEqual(const iterator& other) const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return other.pNode_ == this->pNode_;
}

template <typename T>
template <typename value_type>
typename list<T>::const_reference
list<T>::ListConstIterator<value_type>::getElement() const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return this->pNode_->data_;
}

template <typename T>
template <typename value_type>
typename list<T>::reference list<T>::ListIterator<value_type>::getElement()
    const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return this->pNode_->data_;
}

template <typename T>
template <typename value_type>
typename list<T>::reference list<T>::ListIterator<value_type>::operator*()
    const {
  return getElement();
}

template <typename T>
template <typename value_type>
typename list<T>::const_reference
list<T>::ListConstIterator<value_type>::operator*() const {
  return getElement();
}

template <typename T>
template <typename value_type>
bool list<T>::ListIterator<value_type>::operator!=(
    const const_iterator& other) const {
  return !isEqual(other);
}

template <typename T>
template <typename value_type>
bool list<T>::ListIterator<value_type>::operator==(
    const const_iterator& other) const {
  return isEqual(other);
}

template <typename T>
template <typename value_type>
bool list<T>::ListIterator<value_type>::operator!=(
    const iterator& other) const {
  return !isEqual(other);
}

template <typename T>
template <typename value_type>
bool list<T>::ListIterator<value_type>::operator==(
    const iterator& other) const {
  return isEqual(other);
}

template <typename T>
template <typename value_type>
typename list<T>::iterator& list<T>::ListIterator<value_type>::operator++() {
  next();
  return *this;
}

template <typename T>
template <typename value_type>
typename list<T>::iterator list<T>::ListIterator<value_type>::operator++(int) {
  iterator tmp = *this;
  next();
  return tmp;
}

template <typename T>
template <typename value_type>
typename list<T>::iterator& list<T>::ListIterator<value_type>::operator--() {
  prev();
  return *this;
}

template <typename T>
template <typename value_type>
typename list<T>::iterator list<T>::ListIterator<value_type>::operator--(int) {
  iterator tmp = *this;
  prev();
  return tmp;
}
}  // namespace s21
