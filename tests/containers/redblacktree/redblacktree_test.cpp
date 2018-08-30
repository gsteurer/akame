#include <stdlib.h>
#include <time.h>

#include "gtest/gtest.h"

#include "containers/redblacktree.hpp"

template <>
akame::rbtree::Node<int>
    akame::rbtree::Node<int>::T_NULL_NODE = akame::rbtree::Node<int>();

template <>
akame::rbtree::Node<int> *akame::rbtree::Node<int>::T_NIL =
    &akame::rbtree::Node<int>::T_NULL_NODE;

template <>
akame::rbtree::Node<float>
    akame::rbtree::Node<float>::T_NULL_NODE = akame::rbtree::Node<float>();

template <>
akame::rbtree::Node<float> *akame::rbtree::Node<float>::T_NIL =
    &akame::rbtree::Node<float>::T_NULL_NODE;

TEST(RedBlackTree, Test1) {
  akame::rbtree::Node<int> *tree = akame::rbtree::Node<int>::T_NIL;
  for (int idx = 0; idx < 10; idx++) {
    akame::rbtree::rbInsert(&tree, idx + 1);
  }

  for (int idx = 0; idx < 10; idx++) {
    auto node = akame::rbtree::rbTreeSearch(tree, idx + 1);
    ASSERT_EQ(node->Key, idx + 1);
  }
  ASSERT_EQ(akame::rbtree::rbTreeMinimum(tree)->Key, 1);
  ASSERT_EQ(akame::rbtree::rbTreeMaximum(tree)->Key, 10);

  for (int idx = 9; idx >= 0; idx--) {
    auto node = akame::rbtree::rbTreeSearch(tree, idx + 1);
    akame::rbtree::rbDelete(&tree, node);
  }
  ASSERT_EQ(tree, akame::rbtree::Node<int>::T_NIL);
}

TEST(RedBlackTree, Test2) {
  srand(time(NULL));
  akame::rbtree::Node<int> *tree = akame::rbtree::Node<int>::T_NIL;
  for (int idx = 0; idx < 10000; idx++) {
    akame::rbtree::rbInsert(&tree, (rand() % 1000) + 1);
  }
  akame::rbtree::rbInsert(&tree, 1);
  akame::rbtree::rbInsert(&tree, 1002);
  ASSERT_EQ(akame::rbtree::rbTreeMinimum(tree)->Key, 1);
  ASSERT_EQ(akame::rbtree::rbTreeMaximum(tree)->Key, 1002);

  //@@@todo complete
  /*
    for (int idx = 0; idx < 10; idx++) {
          auto node = akame::rbtree::rbTreeSearch(tree, idx+1);
          ASSERT_EQ(node->Key, idx+1);
    }
    ASSERT_EQ(akame::rbtree::rbTreeMinimum(tree)->Key, 1);
    ASSERT_EQ(akame::rbtree::rbTreeMaximum(tree)->Key, 10);

    for (int idx = 9; idx >= 0; idx--) {
          auto node = akame::rbtree::rbTreeSearch(tree, idx+1);
          akame::rbtree::rbDelete(&tree, node);
    }
    ASSERT_EQ(tree, akame::rbtree::Node<int>::T_NIL);
  */
}

//@@@ todo test tree properties
//@@@ todo what happens when deleting something with same key as null node?