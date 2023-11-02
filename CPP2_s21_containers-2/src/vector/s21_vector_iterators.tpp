#include "s21_vector.h"

namespace s21 {

template <typename T>
template <typename value_type>
vector<T>::VectorIterator<value_type>::VectorIterator() {
  data_ = nullptr;
}

template <typename T>
template <typename value_type>
vector<T>::VectorIterator<value_type>::VectorIterator(T* data) {
  data_ = data;
}

template <typename T>
template <typename value_type>
vector<T>::VectorConstIterator<value_type>::VectorConstIterator() {}

template <typename T>
template <typename value_type>
typename vector<T>::iterator&
vector<T>::VectorIterator<value_type>::operator++() {
  data_++;
  return *this;
}

template <typename T>
template <typename value_type>
typename vector<T>::iterator vector<T>::VectorIterator<value_type>::operator++(
    int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T>
template <typename value_type>
typename vector<T>::iterator&
vector<T>::VectorIterator<value_type>::operator--() {
  data_--;
  return *this;
}

template <typename T>
template <typename value_type>
typename vector<T>::iterator vector<T>::VectorIterator<value_type>::operator--(
    int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T>
template <typename value_type>
typename vector<T>::reference vector<T>::VectorIterator<value_type>::operator*()
    const {
  return *this->data_;
}

template <typename T>
template <typename value_type>
typename vector<T>::const_reference
vector<T>::VectorConstIterator<value_type>::operator*() const {
  return *this->data_;
}

template <typename T>
template <typename value_type>
bool vector<T>::VectorIterator<value_type>::operator==(
    const iterator& other) const {
  return isEqual(other);
}

template <typename T>
template <typename value_type>
bool vector<T>::VectorIterator<value_type>::operator==(
    const const_iterator& other) const {
  return isEqual(other);
}

template <typename T>
template <typename value_type>
bool vector<T>::VectorIterator<value_type>::operator!=(
    const iterator& other) const {
  return !isEqual(other);
}

template <typename T>
template <typename value_type>
bool vector<T>::VectorIterator<value_type>::operator!=(
    const const_iterator& other) const {
  return !isEqual(other);
}

template <typename T>
template <typename value_type>
bool vector<T>::VectorIterator<value_type>::isEqual(
    const iterator& other) const {
  if (data_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return other.data_ == data_;
}

template <typename T>
template <typename value_type>
bool vector<T>::VectorIterator<value_type>::isEqual(
    const const_iterator& other) const {
  if (data_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return other.data_ == data_;
}
}  // namespace s21
