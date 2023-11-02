#include "./s21_set.h"

namespace s21 {

template <typename Key>
template <typename key_type>
set<Key>::SetIterator<key_type>::SetIterator() {}

template <typename Key>
template <typename key_type>
set<Key>::SetConstIterator<key_type>::SetConstIterator() {}

template <typename Key>
template <typename key_type>
typename set<Key>::const_reference set<Key>::SetIterator<key_type>::operator*()
    const {
  this->checkForInit();
  return (*(this->pos_)).first;
}

template <typename Key>
template <typename key_type>
bool set<Key>::SetIterator<key_type>::operator!=(
    const const_iterator& other) const {
  checkForInit();
  return this->pos_ != other.pos_;
}

template <typename Key>
template <typename key_type>
bool set<Key>::SetIterator<key_type>::operator==(
    const const_iterator& other) const {
  checkForInit();
  return this->pos_ == other.pos_;
}

template <typename Key>
template <typename key_type>
bool set<Key>::SetIterator<key_type>::operator!=(const iterator& other) const {
  checkForInit();
  return this->pos_ != other.pos_;
}

template <typename Key>
template <typename key_type>
bool set<Key>::SetIterator<key_type>::operator==(const iterator& other) const {
  checkForInit();
  return this->pos_ == other.pos_;
}

template <typename Key>
template <typename key_type>
typename set<Key>::iterator& set<Key>::SetIterator<key_type>::operator++() {
  checkForInit();
  pos_.next();
  return *this;
}

template <typename Key>
template <typename key_type>
typename set<Key>::iterator set<Key>::SetIterator<key_type>::operator++(int) {
  checkForInit();
  iterator tmp = *this;
  pos_.next();
  return tmp;
}

template <typename Key>
template <typename key_type>
typename set<Key>::iterator& set<Key>::SetIterator<key_type>::operator--() {
  checkForInit();
  pos_.prev();
  return *this;
}

template <typename Key>
template <typename key_type>
typename set<Key>::iterator set<Key>::SetIterator<key_type>::operator--(int) {
  checkForInit();
  iterator tmp = *this;
  pos_.prev();
  return tmp;
}

template <typename Key>
template <typename key_type>
void set<Key>::SetIterator<key_type>::checkForInit() const {
  if (this->pos_.pNode_ == nullptr)
    throw std::invalid_argument("Error. Uninitialized iterator.");
}
}  // namespace s21
