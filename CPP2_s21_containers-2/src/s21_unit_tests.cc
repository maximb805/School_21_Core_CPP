#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <vector>

#include "gtest/gtest.h"
#include "s21_containers.h"

using namespace s21;

TEST(list, list_test1) {
  list<int> linkedList{3, 4, 6, 7, 8, 9};
  std::list<int> stdList{3, 4, 6, 7, 8, 9};
  EXPECT_EQ(*linkedList.begin(), *stdList.begin());
}

TEST(list, list_max_size) {
  list<int> l1;
  std::list<int> l2;
  EXPECT_EQ(l1.max_size(), l2.max_size());
}

TEST(list, list_length) {
  list<int> l1(5);
  std::list<int> l2(5);
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(list, list_empty) {
  list<int> l1;
  std::list<int> l2;
  EXPECT_EQ(l1.empty(), l2.empty());
}

TEST(list, list_front) {
  list<int> l1{3, 4, 6, 7, 8, 9};
  std::list<int> l2{3, 4, 6, 7, 8, 9};
  EXPECT_EQ(l1.front(), l2.front());
}

TEST(list, list_back) {
  list<int> l1{3, 4, 6, 7, 8, 9};
  std::list<int> l2{3, 4, 6, 7, 8, 9};
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(list, list_end) {
  list<int> l1;
  std::list<int> l2;
  EXPECT_EQ(*l1.end(), *l2.end());
}

TEST(list, list_operator_plus_plus) {
  list<int>::iterator i1;
  std::list<int>::iterator i2;
  list<int> l1{0, 1, 2, 3};
  std::list<int> l2{0, 1, 2, 3};
  i1 = l1.begin();
  i2 = l2.begin();
  ++i1;
  ++i2;
  EXPECT_EQ(*i1, *i2);
}

TEST(list, list_clear) {
  list<int> l1{0, 1, 2, 3};
  l1.clear();
  std::list<int> l2{0, 1, 2, 3};
  l2.clear();
  EXPECT_EQ(*l1.end(), *l2.end());
}

TEST(list, list_move) {
  list<int> l1{0, 1, 2, 3};
  list<int> l2(std::move(l1));
  EXPECT_EQ(*l1.end(), 0);
}

TEST(list, list_swap) {
  list<int> l1{1, 2, 3}, l2{4, 5};
  list<int>::iterator it1 = l1.begin();
  list<int>::iterator it2 = l2.begin();
  it1++;
  it2++;
  int ref1 = l1.front();
  int ref2 = l2.front();
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(ref1, 1);
  EXPECT_EQ(ref2, 4);
  l1.swap(l2);
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(ref1, 1);
  EXPECT_EQ(ref2, 4);
  EXPECT_EQ(l1.front(), 4);
  EXPECT_EQ(l1.back(), 5);
  EXPECT_EQ(l2.front(), 1);
  EXPECT_EQ(l2.back(), 3);
}

TEST(list, list_iterator_insert) {
  list<int> l1{1, 2, 3};
  list<int>::iterator it1 = l1.begin();
  it1++;
  list<int>::iterator it2 = l1.insert(it1, 5);
  EXPECT_EQ(l1.front(), 1);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(*it1, 2);
}

TEST(list, list_insert) {
  list<std::string> l1{"kek", "lol"};
  l1.sort();
  std::list<std::string> l3{"kek", "lol"};
  std::list<std::string> l4 = l3;
  std::list<std::string>::iterator it1 = l4.begin();
  std::list<std::string>::iterator it2 = l3.begin();
  // EXPECT_EQ(*it1, 2);
}

TEST(list, list_move_copy) {
  list<int> l1{1, 2, 3};
  list<int> l2;
  l2 = std::move(l1);
}

TEST(list, list_sort) {
  list<int> l1{4, 5, 2, 10};
  list<int> l2{10, 4};
  l1.sort();
  l2.sort();
  EXPECT_EQ(l1.front(), 2);
  EXPECT_EQ(l1.back(), 10);
  EXPECT_EQ(l2.front(), 4);
  EXPECT_EQ(l2.back(), 10);
}

TEST(list, list_push_front) {
  list<int> l1{4, 5, 2, 10};
  l1.push_front(1);
  EXPECT_EQ(l1.front(), 1);
}

TEST(list, list_reverse) {
  list<int> l1{4, 5, 2, 10};
  l1.reverse();
  EXPECT_EQ(l1.front(), 10);
}

TEST(list, list_pop_front) {
  list<int> l1{4, 5, 2, 10};
  list<int> l2;
  l1.pop_front();
  EXPECT_EQ(l1.front(), 5);
  EXPECT_THROW(l2.pop_front(), std::logic_error);
}

TEST(list, list_pop_back) {
  list<int> l1{4, 5, 2, 10};
  list<int> l2;
  l1.pop_back();
  EXPECT_EQ(l1.back(), 2);
  EXPECT_THROW(l2.pop_back(), std::logic_error);
}

TEST(list, list_erase_end) {
  list<int> l1{4, 5, 2, 10};
  list<int>::iterator it1 = l1.end();
  EXPECT_THROW(l1.erase(it1), std::invalid_argument);
}

TEST(list, list_merge) {
  list<int> l1{4, 5, 2, 10};
  list<int> l2{9, 8, 7, 44};
  l1.merge(l2);
  std::list<int> l3{4, 5, 2, 10};
  std::list<int> l4{9, 8, 7, 44};
  l3.merge(l4);
  EXPECT_EQ(l1.size(), l3.size());
  EXPECT_EQ(l1.front(), l3.front());
  EXPECT_EQ(l1.back(), l3.back());
}

TEST(list, list_unique) {
  list<int> l1{4, 4, 5, 5, 2, 2, 10};
  l1.unique();
  EXPECT_EQ(l1.front(), 4);
  EXPECT_EQ(l1.size(), 4);
}

TEST(list, null_iterator_insert) {
  list<int> l1{4, 5, 2, 10};
  list<int>::iterator it1;
  EXPECT_THROW(l1.insert(it1, 4), std::invalid_argument);
}

TEST(list, null_iterator_next_prev) {
  list<int>::iterator it1;
  EXPECT_THROW(it1.next(), std::invalid_argument);
  EXPECT_THROW(it1.prev(), std::invalid_argument);
}

TEST(list, null_iterator_is_equal) {
  list<int>::iterator it1, it2;
  list<int>::const_iterator it3, it4;
  EXPECT_THROW(it1 == it2, std::invalid_argument);
  EXPECT_THROW(it3 == it4, std::invalid_argument);
}

TEST(list, null_iterator_get_element) {
  list<int>::iterator it1;
  list<int>::const_iterator it2;
  EXPECT_THROW(*it1, std::invalid_argument);
  EXPECT_THROW(*it2, std::invalid_argument);
}

TEST(list, iterator_get_element) {
  const list<int> l1{4, 5, 2, 10};
  list<int>::const_iterator it1 = l1.begin();
  EXPECT_EQ(*it1, 4);
}

TEST(list, iterator_is_equal) {
  const list<int> l1{4, 5, 2, 10};
  list<int> l2;
  l2 = l1;
  list<int>::const_iterator it1 = l1.begin();
  list<int>::const_iterator it2 = l1.begin();
  EXPECT_EQ(it1 == it2, 1);
}

TEST(list, iterator_is_not_equal) {
  const list<int> l1{4, 5, 2, 10};
  const list<int> l2(l1);
  list<int>::const_iterator it1 = l2.begin();
  list<int>::const_iterator it2 = l2.end();
  EXPECT_EQ(it1 != it2, 1);
}

TEST(queue, queue_front_back) {
  queue<int> q1{1, 2, 3};
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 3);
}

TEST(queue, queue_empty) {
  queue<int> q1;
  EXPECT_EQ(q1.empty(), 1);
}

TEST(queue, queue_size) {
  queue<int> q1;
  EXPECT_EQ(q1.size(), 0);
}

TEST(queue, queue_push_pop) {
  queue<int> q1;
  q1.push(1);
  q1.push(10);
  q1.push(5);
  q1.push(3);
  q1.pop();
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 10);
}

TEST(queue, queue_operator_equal) {
  queue<int> q1;
  queue<int> q2(5);
  queue<std::string> q3;
  queue<std::string> q4{"lol"};
  q1 = q2;
  q3 = std::move(q4);
  EXPECT_EQ(q1.size(), 5);
  EXPECT_EQ(q3.size(), 1);
}

TEST(queue, queue_init) {
  queue<std::string> q1{"lol", "kek", "cheburek"};
  queue<std::string> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), "lol");
}

TEST(queue, queue_init2) {
  queue<std::string> q1{"lol", "kek", "cheburek"};
  queue<std::string> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), "lol");
}

TEST(stack, stack_front_back) {
  stack<int> q1{1, 2, 3};
  EXPECT_EQ(q1.top(), 1);
}

TEST(stack, stack_empty) {
  stack<int> q1;
  EXPECT_EQ(q1.empty(), 1);
}

TEST(stack, stack_size) {
  queue<int> q1;
  EXPECT_EQ(q1.size(), 0);
}

TEST(stack, stack_push_pop) {
  stack<int> q1;
  q1.push(1);
  q1.push(10);
  q1.push(5);
  q1.push(3);
  q1.pop();
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.top(), 5);
}

TEST(stack, stack_operator_equal) {
  stack<int> q1;
  stack<int> q2(5);
  stack<std::string> q3;
  stack<std::string> q4{"lol"};
  q1 = q2;
  q3 = std::move(q4);
  EXPECT_EQ(q1.size(), 5);
  EXPECT_EQ(q3.size(), 1);
}

TEST(stack, stack_init) {
  stack<std::string> q1{"lol", "kek", "cheburek"};
  stack<std::string> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.top(), "lol");
}

TEST(stack, stack_init2) {
  stack<std::string> q1{"lol", "kek", "cheburek"};
  stack<std::string> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.top(), "lol");
}

TEST(vector, vector_init) {
  vector<int> v2{2, 5, 4, 8};
  vector<int> v1 = v2;
  std::vector<int> v4{2, 5, 4, 8};
  std::vector<int> v3 = v4;
  vector<int> v6{2, 5, 4, 8};
  vector<int> v5 = std::move(v6);
  std::vector<int> v8{2, 5, 4, 8};
  std::vector<int> v7 = std::move(v8);
  EXPECT_EQ(v1.at(3), v3.at(3));
  EXPECT_EQ(v1.at(1), v3.at(1));
  EXPECT_EQ(v5.at(3), v7.at(3));
  EXPECT_EQ(v5.at(1), v7.at(1));
}

TEST(vector, vector_at_out_of_range) {
  vector<int> v1{2, 5, 4, 8};
  EXPECT_THROW(v1.at(10), std::out_of_range);
  EXPECT_THROW(v1[10], std::out_of_range);
  EXPECT_THROW(v1.at(-10), std::out_of_range);
  EXPECT_THROW(v1[-10], std::out_of_range);
}

TEST(vector, vector_init_size_type) {
  vector<int> v1(5);
  EXPECT_EQ(v1[4], 0);
}

TEST(vector, vector_init_items) {
  vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  EXPECT_EQ(v1[2], v2[2]);
}

TEST(vector, vector_size) {
  vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  EXPECT_EQ(v1.size(), v2.size());
  v1.push_back(4);
  v2.push_back(4);
  EXPECT_EQ(v1.size(), v2.size());
}

TEST(vector, vector_max_size) {
  vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  EXPECT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector, vector_iterator) {
  vector<int> v1{1, 2, 3};
  vector<int>::iterator it1(v1.end());
  it1--;
  std::vector<int> v2{1, 2, 3};
  std::vector<int>::iterator it2(v2.end());
  it2--;
  EXPECT_EQ(*it1, *it2);
}

TEST(vector, vector_begin) {
  vector<int> v1{1, 2, 3};
  vector<int>::iterator it1(v1.begin());
  std::vector<int> v2{1, 2, 3};
  std::vector<int>::iterator it2(v2.begin());
  EXPECT_EQ(*it1, *it2);
}

TEST(vector, vector_empty) {
  vector<int> v1;
  std::vector<int> v2;
  EXPECT_EQ(v1.empty(), v2.empty());
}

TEST(vector, vector_reserve) {
  vector<int> v1;
  std::vector<int> v2;
  EXPECT_ANY_THROW(v1.reserve(2305843009213693952));
  EXPECT_ANY_THROW(v2.reserve(2305843009213693952));
}

TEST(vector, vector_capacity) {
  vector<int> v1;
  std::vector<int> v2;
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(vector, vector_pop_back) {
  vector<int> v1{1, 2, 3};
  vector<int>::iterator it1(v1.end());
  it1--;
  v1.pop_back();
  v1.pop_back();
  std::vector<int> v2{1, 2, 3};
  std::vector<int>::iterator it2(v2.end());
  it2--;
  v2.pop_back();
  v2.pop_back();
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(v1.size(), v2.size());
}

TEST(vector, vector_front_back) {
  vector<std::string> v1{"lol", "kek", "cheburek"};
  std::vector<std::string> v2{"lol", "kek", "cheburek"};
  EXPECT_EQ(v1.front(), v2.front());
  EXPECT_EQ(v1.back(), v2.back());
}

TEST(vector, vector_data) {
  vector<std::string> v1{"lol", "kek", "cheburek"};
  std::vector<std::string> v2{"lol", "kek", "cheburek"};
  EXPECT_NE(v1.data(), v2.data());
}

TEST(vector, vector_operator1) {
  vector<int> v1{1, 2, 3};
  vector<int> v2{4, 5, 6};
  v1 = std::move(v2);
  std::vector<int> v3{1, 2, 3};
  std::vector<int> v4{4, 5, 6};
  v3 = std::move(v4);
  EXPECT_EQ(v2.size(), v4.size());
}

TEST(vector, vector_shrink1) {
  vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  v2.reserve(6);
  v1.push_back(4);
  v1.push_back(4);
  v1.push_back(4);
  v1.push_back(4);
  v1.shrink_to_fit();
}

TEST(vector, vector_insert1) {
  vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  vector<int>::iterator it1 = v1.end();
  std::vector<int>::iterator it2 = v2.end();
  it1--;
  it1--;
  it2--;
  it2--;
  v1.insert(it1, 10);
  v2.insert(it2, 10);
  EXPECT_EQ(v1[2], v2[2]);
  EXPECT_EQ(v1.size(), v2.size());
}

TEST(vector, iterator_insert_throw) {
  vector<int> v1{3, 1, 44};
  vector<int>::iterator it1 = v1.begin();
  vector<int>::iterator it2 = v1.end();
  it1--;
  it2++;
  EXPECT_ANY_THROW(v1.insert(it1, 5));
  EXPECT_ANY_THROW(v1.insert(it2, 7));
}

TEST(vector, vector_erase1) {
  vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  vector<int>::iterator it1 = v1.end();
  std::vector<int>::iterator it2 = v2.end();
  it1--;
  it1--;
  it2--;
  it2--;
  v1.erase(it1);
  v2.erase(it2);
  EXPECT_EQ(v1[1], v2[1]);
  EXPECT_EQ(v1.size(), v2.size());
}

TEST(vector, iterator_erase_throw) {
  vector<int> v1{3, 1, 44};
  vector<int>::iterator it1 = v1.begin();
  vector<int>::iterator it2 = v1.end();
  it1--;
  it2++;
  EXPECT_ANY_THROW(v1.erase(it1));
  EXPECT_ANY_THROW(v1.erase(it2));
}

TEST(vector, vector_push_back_empty) {
  vector<int> v1;
  v1.push_back(4);
  EXPECT_EQ(v1[0], 4);
}

TEST(vector, iterator) {
  const vector<int> v1{3, 1, 44};
  vector<int>::iterator it1;
  vector<int>::const_iterator it2 = v1.end();
  it2--;
  EXPECT_EQ(*it2, 44);
}

TEST(vector, is_equal) {
  const vector<int> v1{3, 1, 44};
  vector<int> v2{3, 1, 44};
  vector<int>::const_iterator it1 = v1.begin();
  vector<int>::const_iterator it2;
  vector<int>::iterator it3 = v2.begin();
  vector<int>::iterator it4;
  vector<int>::const_iterator it5 = v1.end();
  vector<int>::iterator it6 = v2.end();
  EXPECT_TRUE(it1 == it1);
  EXPECT_ANY_THROW(it2 == it2);
  EXPECT_TRUE(it3 == it3);
  EXPECT_ANY_THROW(it4 == it4);
  EXPECT_TRUE(it1 != it5);
  EXPECT_TRUE(it3 != it6);
}

TEST(set, init) {
  set<int> s1;
  set<int> s2{9, 4, 1, 44};
  s1 = s2;
  set<int> s3 = s1;
  set<int> s4 = std::move(s3);
  set<int> s5;
  s1 = std::move(s5);
}

TEST(set, empty) {
  set<int> s1;
  EXPECT_TRUE(s1.empty());
}

TEST(set, size) {
  set<int> s1{9, 4, 3, 7};
  std::set<int> s2{9, 4, 3, 7};
  set<std::string> s3;
  std::set<std::string> s4;
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s3.size(), s4.size());
}

TEST(set, max_size) {
  set<int> s1{9, 4, 3, 7};
  std::set<int> s2{9, 4, 3, 7};
  set<std::string> s3{"lol", "kek", "cheburek"};
  std::set<std::string> s4{"lol", "kek", "cheburek"};
  EXPECT_EQ(s1.max_size(), s2.max_size());
  EXPECT_EQ(s3.max_size(), s3.max_size());
}

TEST(set, erase) {
  set<int> s1{9, 4, 3, 7};
  set<int>::iterator it1 = s1.begin();
  std::set<int> s2{9, 4, 3, 7};
  std::set<int>::iterator it2 = s2.begin();
  s1.erase(it1);
  s2.erase(it2);
  it1 = s1.begin();
  it2 = s2.begin();
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set, swap) {
  set<int> s1{9, 4, 3, 7};
  set<int> s2{2, 1, 55};
  set<std::string> s3{"lol", "kek", "cheburek"};
  set<std::string> s4{"umama", "azaza", "biba", "boba"};
  s1.swap(s2);
  s3.swap(s4);
  set<int>::iterator it1 = s1.begin();
  set<std::string>::iterator it2 = s3.begin();
  EXPECT_EQ(*it1, 1);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 4);
  EXPECT_EQ(*it2, "azaza");
  EXPECT_EQ(s3.size(), 4);
  EXPECT_EQ(s4.size(), 3);
}

TEST(set, merge) {
  set<int> s1{9, 4, 3, 7};
  set<int> s2{9, 4, 55};
  set<std::string> s3{"lol", "kek", "cheburek"};
  set<std::string> s4{"lol", "kek", "cheburek", "boba"};
  s1.merge(s2);
  s3.merge(s4);
  set<int>::iterator it1 = s1.begin();
  set<std::string>::iterator it2 = s3.end();
  it2--;
  EXPECT_EQ(*it1, 3);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 2);
  EXPECT_EQ(*it2, "lol");
  EXPECT_EQ(s3.size(), 4);
  EXPECT_EQ(s4.size(), 3);
}

TEST(set, iterator) {
  const set<int> s1{9, 4, 3, 7};
  set<int>::const_iterator it1 = s1.begin();
  set<int>::const_iterator it2 = s1.end();
  it2--;
  EXPECT_EQ(*it1, 3);
  EXPECT_EQ(*it2, 9);
}

TEST(set, iterator2) {
  set<int> s1{9, 4, 3, 7};
  set<int>::iterator it1;
  set<int>::iterator it2;
  EXPECT_ANY_THROW(it1++);
  EXPECT_ANY_THROW(it1--);
  EXPECT_ANY_THROW(it1 == it2);
  EXPECT_ANY_THROW(it1 != it2);
  it1 = s1.begin();
  it2 = s1.end();
  it2--;
  EXPECT_TRUE(it1 != it2);
  it1++;
  it1 = it2;
  EXPECT_TRUE(it1 == it2);
}

TEST(set, iterator3) {
  const set<int> s1{9, 4, 3, 7};
  set<int>::const_iterator it1 = s1.begin();
  set<int>::const_iterator it2 = s1.end();
  it2--;
  --it2;
  EXPECT_TRUE(it1 != it2);
  it1++;
  ++it1;
  EXPECT_TRUE(it1 == it2);
}

TEST(map, init) {
  map<int, int> m1{{1, 1}, {2, 2}, {3, 3}};
  map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2[1], 1);
  m2[4] = 4;
  EXPECT_EQ(m2[4], 4);
  EXPECT_ANY_THROW(m2.at(0));
}

TEST(map, iterator) {
  map<int, int> m1{{1, 1}, {2, 2}, {3, 3}};
  map<int, int>::iterator it1;
  map<int, int>::iterator it2;
  EXPECT_ANY_THROW(++it1);
  EXPECT_ANY_THROW(--it1);
  EXPECT_ANY_THROW(it1 == it2);
  EXPECT_ANY_THROW(*it1);
  const map<int, int> m2{{1, 1}, {2, 2}, {3, 3}};
  map<int, int>::const_iterator it3;
  map<int, int>::const_iterator it4;
  EXPECT_ANY_THROW(it3 == it4);
  EXPECT_ANY_THROW(*it3);
  it3 = m2.begin();
  const std::map<int, int> m3{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int>::const_iterator it5 = m3.begin();
  EXPECT_EQ((*it5).second, (*it3).second);
  it1 = m1.end();
  it1--;
  --it1;
  EXPECT_EQ((*it1).second, 2);
  it1++;
  EXPECT_EQ((*it1).second, 3);
}

TEST(map, iterator2) {
  map<int, int> m1{{1, 1}, {2, 2}, {3, 3}, {4, 4},
                   {5, 5}, {6, 6}, {7, 7}, {8, 8}};
  map<int, int>::iterator it1 = m1.end();
  it1--;
  --it1;
  it1--;
  --it1;
  it1--;
  --it1;
  it1--;
  --it1;
  EXPECT_EQ((*it1).second, 1);
}

TEST(map, erase) {
  map<int, int> m1{{1, 1}, {2, 2}, {3, 3}, {4, 4},
                   {5, 5}, {6, 6}, {7, 7}, {8, 8}};
  map<int, int>::iterator it1 = m1.end();
  --it1;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  --it1;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  EXPECT_EQ((*it1).second, 5);
}

TEST(map, erase2) {
  map<int, int> m1{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                   {6, 6}, {7, 7}, {8, 8}, {0, 0}};
  map<int, int>::iterator it1 = m1.begin();
  m1.erase(it1);
  it1 = m1.begin();
  it1++;
  m1.erase(it1);
  it1 = m1.begin();
  ++it1;
  it1++;
  m1.erase(it1);
  it1 = m1.begin();
  EXPECT_EQ((*it1).second, 1);
}

TEST(map, erase3) {
  map<int, int> m1{{0, 0},   {1, 1},   {2, 2},   {3, 3},   {4, 4},
                   {5, 5},   {6, 6},   {7, 7},   {8, 8},   {9, 9},
                   {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}};
  map<int, int>::iterator it1 = m1.end();
  it1--;
  --it1;
  it1--;
  m1.erase(it1);
  m1.insert_or_assign(12, 12);
  m1.insert_or_assign(14, 14);
  it1 = m1.end();
  it1--;
  it1--;
  it1--;
  it1--;
  it1--;
  it1--;
  it1--;
  m1.erase(it1);
}

TEST(map, erase4) {
  int a = 0;
  map<int, int> m1;
  map<int, int>::iterator it1 = m1.end();
  while (a < 50) {
    m1.insert(a, a);
    a++;
  }
  while (a > 44) {
    it1--;
    a--;
  }
  m1.erase(it1);
  it1 = m1.end();
  while (a > 9) {
    it1--;
    a--;
  }
  m1.erase(it1);
  it1 = m1.end();
  a = 48;
  while (a > 21) {
    it1--;
    a--;
  }
  m1.erase(it1);
}

TEST(map, erase5) {
  map<int, int> m1;
  for (int i = 10; i < 30; i++) {
    m1.insert(i, i);
  }
  auto it1 = m1.begin();
  it1++;
  it1++;
  it1++;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
  it1 = m1.end();
  it1--;
  m1.erase(it1);
}

TEST(map, erase6) {
  map<int, int> m1;
  m1.insert(5, 5);
  m1.insert(6, 6);
  m1.insert(2, 2);
  m1.insert(1, 1);
  m1.insert(4, 4);
  m1.insert(3, 3);
  auto it = --(m1.end());
  m1.erase(it);
}

TEST(map, erase7) {
  map<int, int> m1;
  m1.insert(20, 20);

  m1.insert(10, 10);
  m1.insert(25, 25);

  m1.insert(5, 5);
  m1.insert(27, 27);

  m1.insert(15, 15);
  m1.insert(23, 23);

  m1.insert(3, 3);
  m1.insert(7, 7);
  m1.insert(12, 12);
  m1.insert(17, 17);

  m1.insert(3, 3);
  m1.insert(7, 7);
  m1.insert(12, 12);
  m1.insert(17, 17);

  m1.insert(21, 21);
  m1.insert(24, 24);
  m1.insert(26, 26);
  m1.insert(28, 28);

  m1.insert(2, 2);
  m1.insert(4, 4);
  m1.insert(6, 6);
  m1.insert(8, 8);
  m1.insert(11, 11);
  m1.insert(13, 13);
  m1.insert(16, 16);
  m1.insert(18, 18);
  auto it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
}

TEST(map, erase8) {
  map<int, int> m1;
  m1.insert(20, 20);

  m1.insert(10, 10);
  m1.insert(25, 25);

  m1.insert(5, 5);
  m1.insert(27, 27);

  m1.insert(15, 15);
  m1.insert(23, 23);

  m1.insert(12, 12);
  m1.insert(17, 17);
  m1.insert(3, 3);
  m1.insert(7, 7);

  m1.insert(21, 21);
  m1.insert(24, 24);
  m1.insert(26, 26);
  m1.insert(28, 28);

  m1.insert(2, 2);
  m1.insert(4, 4);
  m1.insert(6, 6);
  m1.insert(8, 8);
  m1.insert(11, 11);
  m1.insert(13, 13);
  m1.insert(16, 16);
  m1.insert(18, 18);
  auto it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
}

TEST(map, erase9) {
  map<int, int> m1;
  m1.insert(20, 20);

  m1.insert(10, 10);
  m1.insert(25, 25);

  m1.insert(5, 5);
  m1.insert(27, 27);

  m1.insert(15, 15);
  m1.insert(23, 23);

  m1.insert(3, 3);
  m1.insert(7, 7);
  m1.insert(12, 12);
  m1.insert(17, 17);

  m1.insert(3, 3);
  m1.insert(7, 7);
  m1.insert(12, 12);
  m1.insert(17, 17);

  m1.insert(21, 21);
  m1.insert(24, 24);
  m1.insert(26, 26);
  m1.insert(28, 28);

  m1.insert(2, 2);
  m1.insert(4, 4);
  m1.insert(6, 6);
  m1.insert(8, 8);
  m1.insert(11, 11);
  m1.insert(13, 13);
  m1.insert(16, 16);
  m1.insert(18, 18);
  m1.insert(19, 19);
  m1.insert(17, 17);
  auto it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
}

TEST(map, erase10) {
  map<int, int> m1;
  m1.insert(20, 20);

  m1.insert(10, 10);
  m1.insert(25, 25);

  m1.insert(5, 5);
  m1.insert(27, 27);

  m1.insert(15, 15);
  m1.insert(23, 23);

  m1.insert(12, 12);
  m1.insert(18, 18);
  m1.insert(3, 3);
  m1.insert(7, 7);

  m1.insert(21, 21);
  m1.insert(24, 24);
  m1.insert(26, 26);
  m1.insert(28, 28);

  m1.insert(2, 2);
  m1.insert(4, 4);
  m1.insert(6, 6);
  m1.insert(8, 8);
  m1.insert(11, 11);
  m1.insert(13, 13);
  m1.insert(16, 16);
  m1.insert(18, 18);
  m1.insert(19, 19);
  m1.insert(17, 17);
  auto it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  it--;
  it--;
  m1.erase(it);
}

TEST(map, erase11) {
  map<int, int> m1;
  m1.insert(20, 20);

  m1.insert(10, 10);
  m1.insert(25, 25);

  m1.insert(5, 5);
  m1.insert(27, 27);

  m1.insert(15, 15);
  m1.insert(23, 23);

  m1.insert(3, 3);
  m1.insert(7, 7);
  m1.insert(12, 12);
  m1.insert(17, 17);

  m1.insert(3, 3);
  m1.insert(7, 7);
  m1.insert(12, 12);
  m1.insert(17, 17);

  m1.insert(21, 21);
  m1.insert(24, 24);
  m1.insert(26, 26);
  m1.insert(28, 28);

  m1.insert(2, 2);
  m1.insert(4, 4);
  m1.insert(6, 6);
  m1.insert(8, 8);
  m1.insert(11, 11);
  m1.insert(13, 13);
  m1.insert(16, 16);
  m1.insert(18, 18);
  m1.insert(14, 14);
  auto it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
  it = m1.begin();
  m1.erase(it);
}

TEST(map, erase12) {
  map<int, int> m1;
  m1.insert(20, 20);

  m1.insert(10, 10);
  m1.insert(25, 25);

  m1.insert(5, 5);
  m1.insert(27, 27);
  m1.insert(23, 23);
  m1.insert(21, 21);

  auto it = --(m1.end());
  m1.erase(it);
}

TEST(map, erase13) {
  map<float, float> m1;
  m1.insert(30, 30);
  m1.insert(10, 10);
  m1.insert(45, 45);
  m1.insert(8, 8);
  m1.insert(50, 50);
  m1.insert(20, 20);
  m1.insert(30, 30);
  m1.insert(15, 15);
  m1.insert(23, 23);
  m1.insert(3, 3);
  m1.insert(5, 5);
  m1.insert(4, 4);
  m1.insert(19, 19);
  m1.insert(17, 17);
  m1.insert(16, 16);
  m1.insert(13, 13);
  m1.insert(19.5, 19.5);
  m1.insert(18.5, 18.5);
  m1.insert(18.6, 18.6);
  auto it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
  it = --(m1.end());
  m1.erase(it);
}

TEST(map, erase14) {
  map<float, float> m1;
  m1.insert(30, 30);
  m1.insert(15, 15);
  m1.insert(45, 45);
  m1.insert(8, 8);
  m1.insert(22, 22);

  m1.insert(4, 4);
  m1.insert(12, 12);
  m1.insert(18, 18);
  m1.insert(26, 26);
  m1.insert(2, 2);
  m1.insert(6, 6);
  m1.insert(7, 7);
  m1.insert(5, 5);
  m1.insert(5.5, 5.5);
  m1.insert(4.5, 4.5);
  m1.insert(5.3, 5.3);
  m1.insert(5.7, 5.7);
  m1.insert(5.8, 5.8);
  m1.insert(19, 19);
  auto it = m1.end();
  it--;
  it--;
  it--;
  it--;
  it--;
  it--;
  it--;
  it--;
  m1.erase(it);
}

TEST(map, erase15) {
  map<float, float> m1;
  m1.insert(5, 5);
  auto it = m1.begin();
  m1.erase(it);
}

TEST(map, contains) {
  map<int, int> m1{{0, 0},   {1, 1},   {2, 2},   {3, 3},   {4, 4},
                   {5, 5},   {6, 6},   {7, 7},   {8, 8},   {9, 9},
                   {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}};
  EXPECT_TRUE(m1.contains(9));
}

TEST(map, rollangle) {
  map<int, int> m1;
  m1.insert(5, 5);
  m1.insert(7, 7);
  m1.insert(6, 6);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}