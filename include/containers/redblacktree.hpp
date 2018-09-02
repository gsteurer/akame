#pragma once

namespace akame {
namespace rbtree {

enum COLOR { RED = 0, BLACK = 1 };

template <typename T> struct Node {
  Node<T> *Parent;
  Node<T> *Left;
  Node<T> *Right;
  COLOR Color;
  T Key;
  Node() {
    Parent = NULL;
    Left = NULL;
    Right = NULL;
    Color = COLOR::RED;
  }
  static Node<T> T_NULL_NODE;
  static Node<T> *T_NIL;
};

template <class T> void rbInsert(akame::rbtree::Node<T> **tree, T key);

template <class T> void rbDelete(akame::rbtree::Node<T> **tree, akame::rbtree::Node<T> *z);

template <class T> akame::rbtree::Node<T> *rbTreeSearch(akame::rbtree::Node<T> *x, T k);

template <class T> akame::rbtree::Node<T> *rbTreeMaximum(akame::rbtree::Node<T> *x);

template <class T> akame::rbtree::Node<T> *rbTreeMinimum(akame::rbtree::Node<T> *x);


} // namespace rbtree
} // namespace akame

#include "redblacktree.inl"