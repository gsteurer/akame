#pragma once

#include <exception>

namespace akame {
template <typename T> class LinkedList {
public:
  LinkedList();
  ~LinkedList();
  T operator[](size_t idx) const;
  T &operator[](size_t idx);
  size_t Size() const;
  void PushFront(T item);
  T PopFront();
  void PushBack(T item);
  T PopBack();

private:
  struct Node {
    T data;
    Node *prev;
    Node *next;
    Node(T d) {
      data = d;
      prev = NULL;
      next = NULL;
    }
  };

  Node *m_root;
  Node *m_last;
  size_t m_num_elements;
};
} // namespace akame

#include "linkedlist.inl"