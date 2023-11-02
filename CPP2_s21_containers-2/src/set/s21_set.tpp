#include "s21_set.h"

namespace s21 {
template <typename key_type>
set<key_type>::set() {
  treeMap = new map<key_type, key_type>();
}

template <typename key_type>
set<key_type>::set(std::initializer_list<value_type> const& items) {
  treeMap = new map<key_type, key_type>();
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename key_type>
set<key_type>::set(const set& s) {
  treeMap = new map<key_type, key_type>(*(s.treeMap));
}

template <typename key_type>
set<key_type>::set(set&& s) {
  treeMap = new map<key_type, key_type>();
  std::swap(treeMap, s.treeMap);
}

template <typename key_type>
set<key_type>::~set() {
  delete treeMap;
}

template <typename key_type>
set<key_type>& set<key_type>::operator=(set&& s) {
  clear();
  std::swap(treeMap, s.treeMap);
  return *this;
}

template <typename key_type>
set<key_type>& set<key_type>::operator=(const set& s) {
  clear();
  *treeMap = *(s.treeMap);
  return *this;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::begin() {
  iterator iter;
  iter.pos_ = treeMap->begin();
  return iter;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::end() {
  iterator iter;
  iter.pos_ = treeMap->end();
  return iter;
}

template <typename key_type>
typename set<key_type>::const_iterator set<key_type>::begin() const {
  const_iterator iter;
  iter.pos_ = treeMap->begin();
  return iter;
}

template <typename key_type>
typename set<key_type>::const_iterator set<key_type>::end() const {
  const_iterator iter;
  iter.pos_ = treeMap->end();
  return iter;
}

template <typename key_type>
bool set<key_type>::empty() const {
  return treeMap->empty();
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::size() const {
  return treeMap->size();
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::max_size() const {
  return treeMap->max_size();
}

template <typename key_type>
void set<key_type>::clear() {
  treeMap->clear();
}

template <typename key_type>
std::pair<typename set<key_type>::iterator, bool> set<key_type>::insert(
    const value_type& value) {
  std::pair<typename map<key_type, key_type>::iterator, bool> mapPair =
      treeMap->insert(value, value);
  std::pair<typename set<key_type>::iterator, bool> resultPair;
  resultPair.first.pos_ = mapPair.first;
  resultPair.second = mapPair.second;
  return resultPair;
}

template <typename key_type>
void set<key_type>::erase(iterator pos) {
  treeMap->erase(pos.pos_);
}

template <typename key_type>
void set<key_type>::swap(set& other) {
  treeMap->swap(*(other.treeMap));
}

template <typename key_type>
void set<key_type>::merge(set& other) {
  treeMap->merge(*(other.treeMap));
}
}  // namespace s21
