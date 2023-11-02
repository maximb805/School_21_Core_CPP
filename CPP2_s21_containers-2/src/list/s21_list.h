#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using value_type = T;

 private:
  template <typename value_type>
  class ListIterator;
  template <typename value_type>
  class ListConstIterator;

 public:
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

 private:
  struct node {
    node* next_;
    node* prev_;
    T data_;
  };
  size_type length_;
  node* head_;
  node* tail_;
  node* end_;
  void initialize();
  void moveElement(node* prev, node* inserted, node* next, list& from);
  void quickSort(iterator first, iterator last);
  iterator partition(iterator& first, iterator& last);
  void copy(const list& other);

  template <typename value_type>
  class ListIterator {
   public:
    node* pNode_;
    void next();
    void prev();
    bool isEqual(const const_iterator& other) const;
    bool isEqual(const iterator& other) const;
    reference getElement() const;
    reference operator*() const;
    bool operator!=(const const_iterator& other) const;
    bool operator==(const const_iterator& other) const;
    bool operator!=(const iterator& other) const;
    bool operator==(const iterator& other) const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    ListIterator();
  };
  template <typename value_type>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    const_reference getElement() const;
    const_reference operator*() const;
    ListConstIterator();
  };

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l);
  list& operator=(const list& l);

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(iterator pos, list& other);
  void reverse();
  void unique();
  void sort();
};
}  // namespace s21

#include "./s21_list.tpp"
#include "./s21_list_iterators.tpp"

#endif /* S21_LIST_H_ */
