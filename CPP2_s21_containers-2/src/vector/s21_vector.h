#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

namespace s21 {

template <typename T>
class vector {
 public:
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using value_type = T;
  using pointer = T*;

 private:
  template <typename value_type>
  class VectorIterator;
  template <typename value_type>
  class VectorConstIterator;

 public:
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;

 private:
  size_type size_;
  size_type capacity_;
  value_type* data_;

  template <typename value_type>
  class VectorIterator {
   public:
    T* data_;
    VectorIterator();
    VectorIterator(T* data);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*() const;
    bool operator==(const iterator& other) const;
    bool operator==(const const_iterator& other) const;
    bool operator!=(const iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    bool isEqual(const iterator& other) const;
    bool isEqual(const const_iterator& other) const;
  };
  template <typename value_type>
  class VectorConstIterator : public VectorIterator<value_type> {
   public:
    VectorConstIterator();
    const_reference operator*() const;
  };

 public:
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();
  vector& operator=(vector&& v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  pointer data();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);
};
}  // namespace s21

#include "./s21_vector.tpp"
#include "./s21_vector_iterators.tpp"

#endif /* S21_VECTOR_H_ */