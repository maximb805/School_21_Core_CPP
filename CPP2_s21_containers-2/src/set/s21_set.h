#ifndef S21_SET_H_
#define S21_SET_H_

#include <iostream>
#include <limits>

#include "../map/s21_map.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using mapped_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 private:
  template <typename key_type>
  class SetIterator;
  template <typename key_type>
  class SetConstIterator;

 public:
  using iterator = SetIterator<key_type>;
  using const_iterator = SetConstIterator<key_type>;

 private:
  map<key_type, key_type>* treeMap;
  template <typename key_type>
  class SetIterator {
   public:
    typename map<key_type, key_type>::iterator pos_;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    const_reference operator*() const;
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    SetIterator();

   protected:
    void checkForInit() const;
  };
  template <typename key_type>
  class SetConstIterator : public SetIterator<key_type> {
   public:
    SetConstIterator();
  };

 public:
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();
  set& operator=(set&& s);
  set& operator=(const set& s);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
};
}  // namespace s21

#include "./s21_set.tpp"
#include "./s21_set_iterator.tpp"

#endif /* S21_SET_H_ */
