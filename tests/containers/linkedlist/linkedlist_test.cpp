#include "gtest/gtest.h"

#include "containers/linkedlist.hpp"

TEST(LinkedList, Ctor) {
	akame::LinkedList<int> *ll = new akame::LinkedList<int>();
	ll->PushFront(4);
	// ASSERT_EQ(sample, 4);
}