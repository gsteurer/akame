#include <stdlib.h>     
#include <time.h>       

#include "gtest/gtest.h"

#include "containers/redblacktree.hpp"

template<>
akame::rbtree::Node<int> akame::rbtree::Node<int>::T_NULL_NODE = akame::rbtree::Node<int>();

template<>
akame::rbtree::Node<int>* akame::rbtree::Node<int>::T_NIL = &akame::rbtree::Node<int>::T_NULL_NODE;

TEST(RedBlackTree, Test1) {
	srand (time(NULL));
	akame::rbtree::Node<int>::T_NULL_NODE.Key = 69;
	akame::rbtree::Node<int> *tree = akame::rbtree::Node<int>::T_NIL;

	for (int idx = 0; idx < 10000; idx++) {
		akame::rbtree::rbInsert(&tree, rand() % 1000);	
	}
	
}