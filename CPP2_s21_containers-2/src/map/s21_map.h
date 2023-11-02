#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <iostream>
#include <limits>

#include "../list/s21_list.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 private:
  template <typename key_type, typename mapped_type>
  class MapIterator;
  template <typename key_type, typename mapped_type>
  class MapConstIterator;

 public:
  using iterator = MapIterator<key_type, mapped_type>;
  using const_iterator = MapConstIterator<key_type, mapped_type>;

 private:
  struct node {
    node();
    node(const_reference value);
    bool is_red_;
    node* left_;
    node* right_;
    node* parent_;
    value_type value_;
  };
  node* root_;
  node* end_;
  node* begin_;
  node* last_;
  size_type size_;

  template <typename key_type, typename mapped_type>
  class MapIterator {
   public:
    node* pNode_;
    MapIterator();
    void next();
    void prev();
    bool isEqual(const const_iterator& other) const;
    bool isEqual(const iterator& other) const;
    reference getElement() const;
    reference operator*() const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

   protected:
    bool nodeIsEnd(const node* node);
  };
  template <typename key_type, typename mapped_type>
  class MapConstIterator : public MapIterator<key_type, mapped_type> {
   public:
    const_reference getElement() const;
    const_reference operator*() const;
    MapConstIterator();
  };
  void initialize();
  node* createNode(const value_type& value);
  void copy(const map& other);
  void checkEndPtrs();
  void flip(node* flipTop);
  void solveRRConflict(node* current);
  void rollLeft(node* rollTop);
  void rollRight(node* rollTop);
  bool rollLine(node** current, node** parent, node** grandParent,
                bool on_left);
  bool rollAngle(node** current, node** parent, node** grandParent,
                 bool on_left);
  void distributeNodes(node* thisNode, map& other, list<node*>& tmp);
  void nodeHelper(node* thisNode);
  void traverseDest(node* thisNode);

  std::pair<node*, bool> find(const key_type& key);
  std::pair<bool, bool> nextStepOrInsert(node** current, node** parent,
                                         node* newNode, bool on_left);
  std::pair<iterator, bool> insertNode(node* newNode);
  int getChildrenCount(node* thisNode);
  void replaceContentWithOtherNode(node* thisNode, node* other);
  void simpleErase(node* thisNode);
  bool isLeftChild(node* thisNode);
  node* getMinRight(node* thisNode);
  void rebalance(node* thisNode);
  void rebalanceForLeftRedParent(node* thisNode, node* parent, node* brother);
  void rebalanceForLeftBlackParentRedBrother(node* thisNode, node* parent,
                                             node* brother);
  void rebalanceForLeftBlackParentBlackBrother(node* thisNode, node* parent,
                                               node* brother);
  void rebalanceForRightRedParent(node* thisNode, node* parent, node* brother);
  void rebalanceForRightBlackParentRedBrother(node* thisNode, node* parent,
                                              node* brother);
  void rebalanceForRightBlackParentBlackBrother(node* thisNode, node* parent,
                                                node* brother);

 public:
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(map&& m);
  map& operator=(const map& m);

  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const key_type& key);

  void displayMap() const;
};
}  // namespace s21

#include "./s21_map.tpp"
#include "./s21_map_iterator.tpp"

#endif /* S21_MAP_H_ */
