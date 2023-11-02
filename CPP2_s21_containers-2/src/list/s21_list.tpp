#include "s21_list.h"

namespace s21 {
template <typename value_type>
list<value_type>::list() {
  initialize();
}

template <typename value_type>
list<value_type>::list(size_type n) {
  initialize();
  while (n > 0) {
    push_back(0);
    n--;
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const& items) {
  initialize();
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename value_type>
list<value_type>::list(const list& l) {
  initialize();
  copy(l);
}

template <typename value_type>
list<value_type>::list(list&& l) {
  initialize();
  swap(l);
}

template <typename value_type>
list<value_type>::~list() {
  node* temp = head_;
  while (temp != end_) {
    temp = temp->next_;
    delete head_;
    head_ = temp;
  }
  delete end_;
  end_ = nullptr;
  tail_ = nullptr;
  head_ = nullptr;
  length_ = 0;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(list&& l) {
  clear();
  swap(l);
  return *this;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& l) {
  clear();
  copy(l);
  return *this;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return head_->data_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  return tail_->data_;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  iterator iter;
  iter.pNode_ = head_;
  return iter;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  iterator iter;
  iter.pNode_ = end_;
  return iter;
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::begin() const {
  const_iterator iter;
  iter.pNode_ = head_;
  return iter;
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::end() const {
  const_iterator iter;
  iter.pNode_ = end_;
  return iter;
}

template <typename value_type>
bool list<value_type>::empty() {
  return length_ == 0;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return length_;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(node)) / 2;
}

template <typename value_type>
void list<value_type>::clear() {
  list<value_type> temp(std::move(*this));
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos.pNode_ == nullptr) {
    throw std::invalid_argument("Error. Uninitialized iterator.");
  }
  node* newNode = new node();
  newNode->data_ = value;
  newNode->prev_ = pos.pNode_->prev_;
  newNode->next_ = pos.pNode_;
  pos.pNode_->prev_->next_ = newNode;
  pos.pNode_->prev_ = newNode;
  if (pos.pNode_ == head_) {
    head_ = newNode;
  }
  if (pos.pNode_ == end_) {
    tail_ = newNode;
  }
  pos--;
  length_++;
  return pos;
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (pos.pNode_ == end_) {
    throw std::invalid_argument("Error. Iterator's position is out or fange");
  }
  pos.pNode_->prev_->next_ = pos.pNode_->next_;
  pos.pNode_->next_->prev_ = pos.pNode_->prev_;
  if (pos.pNode_ == head_) {
    head_ = pos.pNode_->next_;
  }
  if (pos.pNode_ == tail_) {
    tail_ = pos.pNode_->prev_;
  }
  delete pos.pNode_;
  length_--;
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (empty()) {
    throw std::logic_error("List is empty");
  }
  erase(--end());
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (empty()) {
    throw std::logic_error("List is empty");
  }
  erase(begin());
}

template <typename value_type>
void list<value_type>::swap(list& other) {
  std::swap(length_, other.length_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(end_, other.end_);
}

template <typename value_type>
void list<value_type>::merge(list& other) {
  iterator iterThis = begin();
  iterator iterOther = other.begin();
  while (iterThis != end() && other.length_ > 0) {
    if (*iterOther < *iterThis) {
      moveElement(iterThis.pNode_->prev_, iterOther.pNode_, iterThis.pNode_,
                  other);
      iterOther = other.begin();
    } else {
      iterThis++;
    }
  }
  splice(iterThis, other);
}

template <typename value_type>
void list<value_type>::splice(iterator pos, list& other) {
  iterator iterOther = other.begin();
  while (other.length_ > 0) {
    moveElement(pos.pNode_->prev_, iterOther.pNode_, pos.pNode_, other);
    iterOther = other.begin();
  }
}

template <typename value_type>
void list<value_type>::reverse() {
  size_type step = 0;
  for (iterator iter = begin(); step <= length_; iter++, step++) {
    std::swap(iter.pNode_->prev_, iter.pNode_->next_);
  }
  std::swap(head_, tail_);
}

template <typename value_type>
void list<value_type>::unique() {
  iterator iter = begin();
  iterator forErase = iter;
  forErase++;
  while (forErase != end()) {
    if (*iter == *forErase) {
      erase(forErase);
      forErase = iter;
      forErase++;
    } else {
      iter++;
      forErase++;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  quickSort(begin(), --end());
}

template <typename value_type>
void list<value_type>::initialize() {
  length_ = 0;
  end_ = new node();
  end_->next_ = end_;
  end_->prev_ = end_;
  head_ = end_;
  tail_ = end_;
}

template <typename value_type>
void list<value_type>::moveElement(node* prev, node* inserted, node* next,
                                   list& from) {
  if (inserted != end_) {
    // полностью отбираем элемент у листа from
    inserted->next_->prev_ = inserted->prev_;
    inserted->prev_->next_ = inserted->next_;
    from.length_--;
    from.end_->data_ = from.length_;
    // если вдруг элемент был головой или хвостом
    from.head_ = from.end_->next_;
    from.tail_ = from.end_->prev_;

    // отдаём этот элемент листу this
    inserted->prev_ = prev;
    inserted->next_ = next;
    next->prev_ = inserted;
    prev->next_ = inserted;
    length_++;
    end_->data_ = length_;
    // если вдруг элемент стал головой или хвостом
    head_ = end_->next_;
    tail_ = end_->prev_;
  }
}

template <typename value_type>
void list<value_type>::quickSort(iterator first, iterator last) {
  if (first != last) {
    if (first.pNode_->next_ == last.pNode_) {
      if (first.pNode_->data_ > last.pNode_->data_) {
        moveElement(last.pNode_, first.pNode_, last.pNode_->next_, *this);
      }
    } else {
      iterator pivot = partition(first, last);
      quickSort(pivot, last);
      if (pivot != begin()) {
        quickSort(first, --pivot);
      }
    }
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::partition(
    iterator& first, iterator& last) {
  value_type pivot_value = last.pNode_->data_;
  iterator forSwap = first;
  iterator iter = first;
  iterator pivot = last;
  iter--;
  while (forSwap != pivot) {
    if (*forSwap >= pivot_value) {
      if (forSwap == first) {
        first++;
      }
      moveElement(last.pNode_, forSwap.pNode_, last.pNode_->next_, *this);
      forSwap = iter;
      forSwap++;
      last++;
    } else {
      iter++;
      forSwap++;
    }
  }
  return pivot;
}

template <typename value_type>
void list<value_type>::copy(const list& other) {
  const_iterator iter = other.begin();
  while (iter != other.end()) {
    this->push_back(*iter);
    iter++;
  }
}
}  // namespace s21
