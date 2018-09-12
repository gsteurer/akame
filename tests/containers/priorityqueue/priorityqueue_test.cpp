#include "gtest/gtest.h"
#include <stdlib.h>
#include <time.h>

#include "containers/priorityqueue.hpp"

void TestMaxHeapProperty(akame::PriorityQueue<int> *q) {
  for (int idx = q->Size() - 1; idx >= 0; idx--) {
    auto parent = q->At((idx - 1) / 2);
    auto child = q->At(idx);
    ASSERT_GE(parent, child);
  }
}

// break set -E c++
TEST(PriorityQueueTest, Ctor) {
  akame::PriorityQueue<int> *q = new akame::PriorityQueue<int>();

  // Push and pop one element.
  q->Push(5);
  ASSERT_EQ(q->Size(), 1);
  int ret = q->Pop();
  ASSERT_EQ(q->Size(), 0);
  ASSERT_EQ(ret, 5);

  // Pop an empty queue
  ASSERT_THROW(q->Pop(), std::underflow_error);
  ASSERT_EQ(q->Size(), 0);
}

TEST(PriorityQueueTest, InsertRemove) {
  akame::PriorityQueue<int> *q = new akame::PriorityQueue<int>();
  int NUM_ELEMENTS = 999;
  // Push n elements
  for (int cycle = 0; cycle < 10; cycle++) {
    for (int idx = 0; idx < NUM_ELEMENTS; idx++) {
      q->Push(idx);
      ASSERT_EQ(q->Size(), idx + 1);
    }

    // Pop n elements
    for (int idx = NUM_ELEMENTS - 1; idx >= 0; idx--) {
      int ret = q->Pop();
      ASSERT_EQ(ret, idx);
      ASSERT_EQ(q->Size(), idx);
    }
  }
}

TEST(PriorityQueueTest, InsertRemoveRand) {
  akame::PriorityQueue<int> *q = new akame::PriorityQueue<int>();
  int NUM_ELEMENTS = 999;
  srand(time(NULL));
  // Push n elements
  for (int cycle = 0; cycle < 10; cycle++) {
    for (int idx = 0; idx < NUM_ELEMENTS; idx++) {
      q->Push(rand() % NUM_ELEMENTS + 1);
      ASSERT_EQ(q->Size(), idx + 1);
      TestMaxHeapProperty(q);
    }

    // Pop n elements
    int last = 0;
    for (int idx = NUM_ELEMENTS - 1; idx >= 0; idx--) {
      int ret = q->Pop();
      if (idx < NUM_ELEMENTS - 1)
        ASSERT_GE(last, ret);
      last = ret;
      ASSERT_EQ(q->Size(), idx);
      TestMaxHeapProperty(q);
    }
  }
}
