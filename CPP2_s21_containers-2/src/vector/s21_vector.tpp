#include "s21_vector.h"

namespace s21 {

template <typename value_type>
vector<value_type>::vector() : size_(0), capacity_(0), data_(nullptr) {}

template <typename value_type>
vector<value_type>::vector(size_type n) {
  size_ = n;
  capacity_ = n;
  data_ = new value_type[n];
  for (size_type i = 0; i < n; i++) {
    data_[i] = 0;
  }
}

template <class value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& items)
    : vector() {
  reserve(items.size());
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename value_type>
vector<value_type>::vector(const vector& v) : vector(v.size_) {
  for (size_type i = 0; i < size_; i++) {
    data_[i] = v.data_[i];
  }
}

template <typename value_type>
vector<value_type>::vector(vector&& v) : vector() {
  swap(v);
}

template <typename value_type>
vector<value_type>::~vector() {
  clear();
  capacity_ = 0;
}

template <typename value_type>
typename vector<value_type>::vector& vector<value_type>::operator=(vector&& v) {
  if (this != &v) {
    clear();
    swap(v);
  }
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos < 0 || pos >= size_) {
    throw std::out_of_range("Index out range");
  }
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return at(pos);
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  return *data_;
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  return data_[size_ - 1];
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() {
  return data_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  iterator iter;
  iter.data_ = data_;
  return iter;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  iterator iter;
  iter.data_ = data_ + size_;
  return iter;
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::begin() const {
  const_iterator iter;
  iter.data_ = data_;
  return iter;
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::end() const {
  const_iterator iter;
  iter.data_ = data_ + size_;
  return iter;
}

template <typename value_type>
bool vector<value_type>::empty() {
  return data_ == nullptr;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::bad_alloc();
  }
  if (size > capacity_) {
    value_type* new_data = new value_type[size];
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
  return capacity_;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (size_ != capacity_) {
    vector<value_type> tmp(size_);
    for (size_type i = 0; i < size_; ++i) {
      tmp.data_[i] = data_[i];
    }
    *this = std::move(tmp);
  }
}

template <typename value_type>
void vector<value_type>::clear() {
  if (data_) {
    delete[] data_;
  }
  data_ = nullptr;
  size_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type position = &(*pos) - data_;
  if (0 > position || position > size_) {
    throw std::out_of_range("Index out ot range");
  }
  if (size_ == capacity_) {
    reserve(capacity_ * 2);
  }
  size_++;
  for (size_type i = size() - 1; i >= position; i--)
    if (i == position) {
      data_[i] = value;
    } else {
      data_[i] = data_[i - 1];
    }
  return data_ + position;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  size_type position = &(*pos) - data_;
  if (0 > position || position > size_) {
    throw std::out_of_range("Index out ot range");
  }
  for (size_type i = position; i < size_ - 1; i++) {
    data_[i] = data_[i + 1];
  }
  size_--;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ == capacity_) {
    if (capacity_) {
      reserve(capacity_ * 2);
    } else {
      reserve(1);
    }
  }
  data_[size_] = value;
  size_++;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (size_ > 0) {
    size_--;
  }
}
template <typename value_type>
void vector<value_type>::swap(vector& other) {
  std::swap(other.size_, size_);
  std::swap(other.capacity_, capacity_);
  std::swap(other.data_, data_);
}
}  // namespace s21
