#include "s21_map.h"
#include "../stack/s21_stack.h"

namespace s21 {

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() {
  initialize();
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const& items) {
  initialize();
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map& m) {
  initialize();
  copy(m);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map&& m) {
  initialize();
  swap(m);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::~map() {
  traverseDest(root_);
  delete end_;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(map&& m) {
  clear();
  swap(m);
  return *this;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(
    const map& m) {
  clear();
  copy(m);
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::mapped_type&
map<key_type, mapped_type>::at(const key_type& key) {
  std::pair<node*, bool> result(nullptr, false);
  result = find(key);
  if (result.second == false) {
    throw std::out_of_range("Index out range");
  }
  return result.first->value_.second;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::mapped_type&
map<key_type, mapped_type>::operator[](const key_type& key) {
  std::pair<node*, bool> result(nullptr, false);
  result = find(key);
  if (result.second == false) {
    insert(key, mapped_type());
  }
  return at(key);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  iterator iter;
  iter.pNode_ = begin_;
  return iter;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  iterator iter;
  iter.pNode_ = end_;
  return iter;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::begin() const {
  const_iterator iter;
  iter.pNode_ = begin_;
  return iter;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::end() const {
  const_iterator iter;
  iter.pNode_ = end_;
  return iter;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() const {
  return size_ == 0;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() const {
  return size_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() const {
  return (std::numeric_limits<size_type>::max() / sizeof(node)) / 2;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  map<key_type, mapped_type> temp(std::move(*this));
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type& value) {
  node* newNode = createNode(value);
  std::pair<iterator, bool> resultPair = insertNode(newNode);
  if (resultPair.second == false) {
    delete newNode;
  }
  return resultPair;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  std::pair<iterator, bool> return_pair =
      insert(std::pair<key_type, mapped_type>(key, obj));
  return return_pair;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  std::pair<node*, bool> found = find(key);
  std::pair<iterator, bool> result;
  bool inserted = false;
  if (found.second) {
    found.first->value_.second = obj;
    result.first.pNode_ = found.first;
    result.second = false;
  } else {
    result = insert(key, obj);
  }
  return result;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  if (pos.pNode_ != end_) {
    node* thisNode = pos.pNode_;
    int childrenCount = getChildrenCount(thisNode);
    if (childrenCount == 2) {
      node* minRight = getMinRight(thisNode);
      replaceContentWithOtherNode(thisNode, minRight);
      thisNode = minRight;
      childrenCount = getChildrenCount(thisNode);
    }
    if (thisNode->is_red_) {
      simpleErase(thisNode);
    } else {
      if (childrenCount == 1) {
        node* child =
            thisNode->left_ != nullptr ? thisNode->left_ : thisNode->right_;
        replaceContentWithOtherNode(thisNode, child);
        simpleErase(child);
      } else {
        rebalance(thisNode);
        simpleErase(thisNode);
      }
    }
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
  std::swap(this->root_, other.root_);
  std::swap(this->begin_, other.begin_);
  std::swap(this->end_, other.end_);
  std::swap(this->last_, other.last_);
  std::swap(this->size_, other.size_);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  list<node*> tmp;
  other.distributeNodes(other.root_, *this, tmp);
  other.root_ = other.end_;
  other.begin_ = other.end_;
  other.last_ = other.end_;
  other.end_->parent_ = other.root_;
  other.end_->left_ = other.begin_;
  other.end_->right_ = other.last_;
  while (!tmp.empty()) {
    other.insertNode(*(tmp.begin()));
    tmp.pop_front();
  }
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) {
  std::pair<node*, bool> found = find(key);
  return found.second;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::initialize() {
  size_ = 0;
  end_ = new node();
  root_ = end_;
  begin_ = end_;
  last_ = end_;
  end_->parent_ = root_;
  end_->left_ = begin_;
  end_->right_ = last_;
  end_->is_red_ = true;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::node*
map<key_type, mapped_type>::createNode(const value_type& value) {
  node* newNode = new node(value);
  newNode->is_red_ = true;
  newNode->left_ = nullptr;
  newNode->right_ = nullptr;
  newNode->parent_ = nullptr;
  return newNode;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::copy(const map& other) {
  const_iterator iter = other.begin();
  const_iterator end = other.end();
  while (iter != other.end()) {
    value_type p(iter.pNode_->value_.first, iter.pNode_->value_.second);
    insert(p);
    ++iter;
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::checkEndPtrs() {
  begin_ = last_ = root_;
  if (end_ != root_) {
    while (last_->right_ != nullptr) {
      last_ = last_->right_;
    }
    while (begin_->left_ != nullptr) {
      begin_ = begin_->left_;
    }
  }
  end_->parent_ = root_;
  end_->left_ = begin_;
  end_->right_ = last_;
  root_->parent_ = end_;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::flip(node* flipTop) {
  if (flipTop != root_) {
    flipTop->is_red_ = !flipTop->is_red_;
  }
  flipTop->left_->is_red_ = !flipTop->left_->is_red_;
  flipTop->right_->is_red_ = !flipTop->right_->is_red_;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::solveRRConflict(node* current) {
  node* parent = current->parent_;
  while (true) {
    bool continue_ = false;
    node* grandParent = parent->parent_;
    if (grandParent->right_ == parent && parent->right_ == current) {
      continue_ = rollLine(&current, &parent, &grandParent, true);
      if (continue_) {
        continue;
      }
    }
    if (grandParent->left_ == parent && parent->left_ == current) {
      continue_ = rollLine(&current, &parent, &grandParent, false);
      if (continue_) {
        continue;
      }
    }
    if (grandParent->right_ == parent && parent->left_ == current) {
      continue_ = rollAngle(&current, &parent, &grandParent, false);
      if (continue_) {
        continue;
      }
    }
    if (grandParent->left_ == parent && parent->right_ == current) {
      continue_ = rollAngle(&current, &parent, &grandParent, true);
      if (continue_) {
        continue;
      }
    }
    break;
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rollLeft(node* rollTop) {
  node* rightChild = rollTop->right_;
  if (rightChild != nullptr) {
    if (rollTop != root_) {
      node* parent = rollTop->parent_;
      if (rollTop == parent->left_) {
        parent->left_ = rightChild;
      } else {
        parent->right_ = rightChild;
      }
      rightChild->parent_ = parent;
    } else {
      root_ = rightChild;
      rightChild->parent_ = end_;
    }
    node* rcLeft = rightChild->left_;
    if (rcLeft != nullptr) {
      rcLeft->parent_ = rollTop;
    }
    rollTop->right_ = rcLeft;
    rightChild->left_ = rollTop;
    rollTop->parent_ = rightChild;
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rollRight(node* rollTop) {
  node* leftChild = rollTop->left_;
  if (leftChild != nullptr) {
    if (rollTop != root_) {
      node* parent = rollTop->parent_;
      if (rollTop == parent->left_) {
        parent->left_ = leftChild;
      } else {
        parent->right_ = leftChild;
      }
      leftChild->parent_ = parent;
    } else {
      root_ = leftChild;
      leftChild->parent_ = end_;
    }
    node* lcRight = leftChild->right_;
    if (lcRight != nullptr) {
      lcRight->parent_ = rollTop;
    }
    rollTop->left_ = lcRight;
    leftChild->right_ = rollTop;
    rollTop->parent_ = leftChild;
  }
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::rollLine(node** current, node** parent,
                                          node** grandParent, bool on_left) {
  bool continue_ = false;
  (*grandParent)->is_red_ = true;
  (*parent)->is_red_ = false;
  if (on_left) {
    rollLeft(*grandParent);
  } else {
    rollRight(*grandParent);
  }
  if (*parent == root_) {
    (*parent)->is_red_ = false;
  } else if ((*parent)->parent_->is_red_) {
    *current = *parent;
    *parent = (*parent)->parent_;
    continue_ = true;
  }
  return continue_;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::rollAngle(node** current, node** parent,
                                           node** grandParent, bool on_left) {
  bool continue_ = false;
  (*grandParent)->is_red_ = true;
  (*current)->is_red_ = false;
  if (on_left) {
    rollLeft(*parent);
    rollRight(*grandParent);
  } else {
    rollRight(*parent);
    rollLeft(*grandParent);
  }
  if (*current == root_) {
    (*current)->is_red_ = false;
  } else if ((*current)->parent_->is_red_) {
    *parent = (*current)->parent_;
    continue_ = true;
  }
  return continue_;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::distributeNodes(node* thisNode, map& other,
                                                 list<node*>& tmp) {
  if (thisNode != nullptr) {
    distributeNodes(thisNode->left_, other, tmp);
    distributeNodes(thisNode->right_, other, tmp);
    if (!(other.find(thisNode->value_.first).second)) {
      nodeHelper(thisNode);
      other.insertNode(thisNode);
    } else {
      nodeHelper(thisNode);
      tmp.push_front(thisNode);
    }
    size_--;
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::nodeHelper(node* thisNode) {
  thisNode->is_red_ = true;
  thisNode->left_ = nullptr;
  thisNode->right_ = nullptr;
  thisNode->parent_ = nullptr;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::traverseDest(node* thisNode) {
  if (thisNode != end_ && thisNode != nullptr) {
    traverseDest(thisNode->left_);
    traverseDest(thisNode->right_);
    delete thisNode;
  }
}

// возвращаем указатель на найденный узел и true, если узел с заданным ключом
// найден иначе - узел, после которого должен был бы находиться узел с заданным
// ключом и false
template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::node*, bool>
map<key_type, mapped_type>::find(const key_type& key) {
  node* current = root_;
  node* next = nullptr;
  bool found = false;
  std::pair<node*, bool> result(current, false);
  if (root_ != end_) {
    if (current->value_.first != key) {
      next = key > current->value_.first ? current->right_ : current->left_;
      bool stop = false;
      while (!stop) {
        if (next == nullptr) {
          stop = true;
        } else {
          current = next;
          if (current->value_.first != key) {
            next =
                key > current->value_.first ? current->right_ : current->left_;
          } else {
            found = true;
            stop = true;
          }
        }
      }
    } else {
      found = true;
    }
    result.first = current;
    result.second = found;
  }
  return result;
}

template <typename key_type, typename mapped_type>
std::pair<bool, bool> map<key_type, mapped_type>::nextStepOrInsert(
    node** current, node** parent, node* newNode, bool on_left) {
  bool inserted = false;
  bool stop = false;
  *parent = *current;
  if (on_left) {
    if ((*current)->left_ != nullptr) {
      *current = (*current)->left_;
    } else {
      (*current)->left_ = newNode;
      *current = (*current)->left_;
      (*current)->parent_ = *parent;
      inserted = true;
      stop = true;
    }
  } else {
    if ((*current)->right_ != nullptr) {
      *current = (*current)->right_;
    } else {
      (*current)->right_ = newNode;
      *current = (*current)->right_;
      (*current)->parent_ = *parent;
      inserted = true;
      stop = true;
    }
  }
  return std::pair<bool, bool>(inserted, stop);
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insertNode(node* newNode) {
  if (size() == max_size()) {
    throw std::length_error("Error. Map size is greater than max size.");
  }
  iterator iter;
  std::pair<bool, bool> insertedAndStop(false, false);
  if (size_ == 0) {
    newNode->is_red_ = false;
    root_ = begin_ = last_ = newNode;
    insertedAndStop.first = true;
  } else {
    node* current = root_;
    node* parent = current->parent_;
    while (!insertedAndStop.second) {
      if (current->left_ != nullptr && current->right_ != nullptr) {
        if (current->left_->is_red_ && current->right_->is_red_) {
          flip(current);
        }
        if (current->is_red_ && parent->is_red_) {
          solveRRConflict(current);
        }
      }
      if (newNode->value_.first > current->value_.first) {
        insertedAndStop = nextStepOrInsert(&current, &parent, newNode, false);
      } else if (newNode->value_.first < current->value_.first) {
        insertedAndStop = nextStepOrInsert(&current, &parent, newNode, true);
      } else {
        insertedAndStop.second = true;
      }
    }
    if (insertedAndStop.first) {
      if (parent->is_red_) {
        solveRRConflict(current);
      }
    }
  }
  if (insertedAndStop.first) {
    ++size_;
    checkEndPtrs();
    iter.pNode_ = newNode;
  }
  return std::pair<iterator, bool>(iter, insertedAndStop.first);
}

template <typename key_type, typename mapped_type>
int map<key_type, mapped_type>::getChildrenCount(node* thisNode) {
  int result = 0;
  if (thisNode->right_ != nullptr || thisNode->left_ != nullptr) {
    if (thisNode->right_ != nullptr && thisNode->left_ != nullptr) {
      result = 2;
    } else {
      result = 1;
    }
  }
  return result;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::replaceContentWithOtherNode(node* thisNode,
                                                             node* other) {
  node* tmp = new node(value_type(other->value_.first, other->value_.second));
  tmp->is_red_ = thisNode->is_red_;
  tmp->left_ = thisNode->left_;
  tmp->right_ = thisNode->right_;
  tmp->parent_ = thisNode->parent_;
  if (tmp->left_ != nullptr) {
    tmp->left_->parent_ = tmp;
  }
  if (tmp->right_ != nullptr) {
    tmp->right_->parent_ = tmp;
  }
  if (thisNode != root_) {
    if (thisNode->parent_->left_ == thisNode) {
      tmp->parent_->left_ = tmp;
    } else {
      tmp->parent_->right_ = tmp;
    }
  } else {
    root_ = tmp;
  }
  delete thisNode;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::simpleErase(node* thisNode) {
  if (thisNode != end_) {
    node* child =
        thisNode->left_ != nullptr ? thisNode->left_ : thisNode->right_;
    node* parent = thisNode->parent_;
    if (thisNode == root_) {
      if (root_->left_ != nullptr) {
        root_ = root_->left_;
      } else if (root_->right_ != nullptr) {
        root_ = root_->right_;
      } else {
        root_ = end_;
      }
    }
    if (child != nullptr) {
      child->parent_ = parent;
    }
    if (isLeftChild(thisNode)) {
      parent->left_ = child;
    } else {
      parent->right_ = child;
    }
    checkEndPtrs();
    delete thisNode;
    --size_;
  }
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::isLeftChild(node* thisNode) {
  bool result = false;
  if (thisNode->parent_->left_ == thisNode) {
    result = true;
  }
  return result;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::node*
map<key_type, mapped_type>::getMinRight(node* thisNode) {
  node* minRight = thisNode->right_;
  node* tmp = minRight->left_;
  while (tmp != nullptr) {
    minRight = tmp;
    tmp = tmp->left_;
  }
  return minRight;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalance(node* thisNode) {
  if (thisNode == root_) {
    root_->is_red_ = false;
    return;
  }
  node* parent = thisNode->parent_;
  if (parent->left_ == thisNode) {
    node* brother = parent->right_;
    if (parent->is_red_) {
      rebalanceForLeftRedParent(thisNode, parent, brother);
    } else {
      if (brother->is_red_) {
        rebalanceForLeftBlackParentRedBrother(thisNode, parent, brother);
      } else {
        rebalanceForLeftBlackParentBlackBrother(thisNode, parent, brother);
      }
    }
  } else {
    node* brother = parent->left_;
    if (parent->is_red_) {
      rebalanceForRightRedParent(thisNode, parent, brother);
    } else {
      if (brother->is_red_) {
        rebalanceForRightBlackParentRedBrother(thisNode, parent, brother);
      } else {
        rebalanceForRightBlackParentBlackBrother(thisNode, parent, brother);
      }
    }
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalanceForLeftRedParent(node* thisNode,
                                                           node* parent,
                                                           node* brother) {
  parent->is_red_ = false;
  if ((brother->left_ == nullptr || !brother->left_->is_red_) &&
      (brother->right_ == nullptr || !brother->right_->is_red_)) {
    brother->is_red_ = true;
  } else {
    if (brother->right_ != nullptr && brother->right_->is_red_) {
      brother->is_red_ = true;
      brother->right_->is_red_ = false;
    } else {
      rollRight(brother);
    }
    rollLeft(parent);
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalanceForLeftBlackParentRedBrother(
    node* thisNode, node* parent, node* brother) {
  node* brosLeftSon = brother->left_;
  if ((brosLeftSon->left_ == nullptr || !brosLeftSon->left_->is_red_) &&
      (brosLeftSon->right_ == nullptr || !brosLeftSon->right_->is_red_)) {
    brosLeftSon->is_red_ = true;
    brother->is_red_ = false;
    rollLeft(parent);
  } else {
    if (brosLeftSon->right_ != nullptr && brosLeftSon->right_->is_red_) {
      brosLeftSon->right_->is_red_ = false;
      rollRight(brother);
      rollLeft(parent);
    } else {
      brother->is_red_ = false;
      rollLeft(parent);
      rollRight(brosLeftSon);
      rollLeft(parent);
    }
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalanceForLeftBlackParentBlackBrother(
    node* thisNode, node* parent, node* brother) {
  if ((brother->left_ == nullptr || !brother->left_->is_red_) &&
      (brother->right_ == nullptr || !brother->right_->is_red_)) {
    brother->is_red_ = true;
    rebalance(parent);
  } else {
    if (brother->left_ != nullptr && brother->left_->is_red_) {
      brother->left_->is_red_ = false;
      rollRight(brother);
    } else {
      brother->right_->is_red_ = false;
    }
    rollLeft(parent);
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalanceForRightRedParent(node* thisNode,
                                                            node* parent,
                                                            node* brother) {
  parent->is_red_ = false;
  if ((brother->left_ == nullptr || !brother->left_->is_red_) &&
      (brother->right_ == nullptr || !brother->right_->is_red_)) {
    brother->is_red_ = true;
  } else {
    if (brother->left_ != nullptr && brother->left_->is_red_) {
      brother->is_red_ = true;
      brother->left_->is_red_ = false;
    } else {
      rollLeft(brother);
    }
    rollRight(parent);
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalanceForRightBlackParentRedBrother(
    node* thisNode, node* parent, node* brother) {
  node* brosRightSon = brother->right_;
  if ((brosRightSon->left_ == nullptr || !brosRightSon->left_->is_red_) &&
      (brosRightSon->right_ == nullptr || !brosRightSon->right_->is_red_)) {
    brosRightSon->is_red_ = true;
    brother->is_red_ = false;
    rollRight(parent);
  } else {
    if (brosRightSon->left_ != nullptr && brosRightSon->left_->is_red_) {
      brosRightSon->left_->is_red_ = false;
      rollLeft(brother);
      rollRight(parent);
    } else {
      brother->is_red_ = false;
      rollRight(parent);
      rollLeft(brosRightSon);
      rollRight(parent);
    }
  }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rebalanceForRightBlackParentBlackBrother(
    node* thisNode, node* parent, node* brother) {
  if ((brother->left_ == nullptr || !brother->left_->is_red_) &&
      (brother->right_ == nullptr || !brother->right_->is_red_)) {
    brother->is_red_ = true;
    rebalance(parent);
  } else {
    if (brother->right_ != nullptr && brother->right_->is_red_) {
      brother->right_->is_red_ = false;
      rollLeft(brother);
    } else {
      brother->left_->is_red_ = false;
    }
    rollRight(parent);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::node::node() {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::node::node(const_reference value)
    : value_(value.first, value.second) {}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::displayMap() const {
  if (root_ == end_) {
    std::cout << "m is empty\n";
    return;
  }
  stack<node*> globalStack;
  globalStack.push(root_);
  int nBlanks = 48;
  bool isRowEmpty = false;
  std::cout
      << "....................................................................."
         "...............................................................\n";
  while (!isRowEmpty) {
    stack<node*> localStack;
    isRowEmpty = true;
    for (int j = 0; j < nBlanks; j++) {
      std::cout << "   ";
    }
    while (!globalStack.empty()) {
      node* temp = globalStack.top();
      globalStack.pop();
      if (temp != nullptr) {
        char ch;
        if (temp->is_red_) {
          ch = 'r';
        } else {
          ch = 'b';
        }
        std::cout << temp->value_.first << "" << ch;
        localStack.push(temp->left_);
        localStack.push(temp->right_);
        if (temp->left_ != nullptr || temp->right_ != nullptr) {
          isRowEmpty = false;
        }
      } else {
        std::cout << "---";
        localStack.push(nullptr);
        localStack.push(nullptr);
      }
      for (int j = 0; j < nBlanks * 2 - 1; j++) {
        std::cout << "   ";
      }
    }
    std::cout << "\n";
    nBlanks /= 2;
    while (!localStack.empty()) {
      globalStack.push(localStack.top());
      localStack.pop();
    }
  }
  std::cout
      << "....................................................................."
         "...............................................................\n";
}
}  // namespace s21
