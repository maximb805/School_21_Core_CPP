#include "s21_map.h"

namespace s21 {

template <typename K, typename T>
template <typename key_type, typename mapped_type>
map<K, T>::MapIterator<key_type, mapped_type>::MapIterator() {
  pNode_ = nullptr;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
map<K, T>::MapConstIterator<key_type, mapped_type>::MapConstIterator() {}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
void map<K, T>::MapIterator<key_type, mapped_type>::next() {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  if (this->pNode_->right_ != nullptr) {
    this->pNode_ = this->pNode_->right_;
    while (this->pNode_->left_ != nullptr) {
      this->pNode_ = this->pNode_->left_;
    }
  } else {
    node* tmp = this->pNode_->parent_;
    while (!nodeIsEnd(tmp) && tmp->value_.first < this->pNode_->value_.first) {
      tmp = tmp->parent_;
    }
    this->pNode_ = tmp;
  }
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
void map<K, T>::MapIterator<key_type, mapped_type>::prev() {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  if (nodeIsEnd(this->pNode_)) {
    this->pNode_ = this->pNode_->right_;
  } else if (this->pNode_->left_ != nullptr) {
    this->pNode_ = this->pNode_->left_;
    while (this->pNode_->right_ != nullptr) {
      this->pNode_ = this->pNode_->right_;
    }
  } else {
    node* tmp = this->pNode_->parent_;
    while (!nodeIsEnd(tmp) && tmp->value_.first > this->pNode_->value_.first) {
      tmp = tmp->parent_;
    }
    this->pNode_ = tmp;
  }
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::isEqual(
    const const_iterator& other) const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return other.pNode_ == this->pNode_;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::isEqual(
    const iterator& other) const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return other.pNode_ == this->pNode_;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::const_reference
map<K, T>::MapConstIterator<key_type, mapped_type>::getElement() const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return this->pNode_->value_;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::reference
map<K, T>::MapIterator<key_type, mapped_type>::getElement() const {
  if (this->pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  return this->pNode_->value_;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::reference
map<K, T>::MapIterator<key_type, mapped_type>::operator*() const {
  return getElement();
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::const_reference
map<K, T>::MapConstIterator<key_type, mapped_type>::operator*() const {
  return getElement();
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::iterator&
map<K, T>::MapIterator<key_type, mapped_type>::operator++() {
  next();
  return *this;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::iterator
map<K, T>::MapIterator<key_type, mapped_type>::operator++(int) {
  iterator tmp = *this;
  next();
  return tmp;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::iterator&
map<K, T>::MapIterator<key_type, mapped_type>::operator--() {
  prev();
  return *this;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
typename map<K, T>::iterator
map<K, T>::MapIterator<key_type, mapped_type>::operator--(int) {
  iterator tmp = *this;
  prev();
  return tmp;
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::operator==(
    const const_iterator& other) const {
  return isEqual(other);
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::operator!=(
    const const_iterator& other) const {
  return !isEqual(other);
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::operator==(
    const iterator& other) const {
  return isEqual(other);
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::operator!=(
    const iterator& other) const {
  return !isEqual(other);
}

template <typename K, typename T>
template <typename key_type, typename mapped_type>
bool map<K, T>::MapIterator<key_type, mapped_type>::nodeIsEnd(
    const node* node) {
  bool result = false;
  if (node->is_red_ && node->parent_->parent_ == node) {
    result = true;
  }
  return result;
}
}  // namespace s21
