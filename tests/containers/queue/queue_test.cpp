#include "gtest/gtest.h"

#include "containers/queue.hpp"
#include <exception>
TEST(QueueTest, Ctor) {
  akame::Queue<int> *q = new akame::Queue<int>();

  // Push and pop one element.
  q->Push(5);
  ASSERT_EQ(q->Size(), 1);
  int ret = q->Pop();
  ASSERT_EQ(q->Size(), 0);
  ASSERT_EQ(ret, 5);

  // Pop an empty queue
  ASSERT_THROW(q->Pop(), std::out_of_range);
  ASSERT_EQ(q->Size(), 0);

  // Push n elements
  for (int idx = 0; idx < 5; idx++) {
    q->Push(idx + 1);
    ASSERT_EQ(q->Size(), idx + 1);
  }

  // Pop n elements
  int size_1 = q->Size();
  for (int idx = 0; idx < 5; idx++) {
    int ret = q->Pop();
    ASSERT_EQ(ret, idx + 1);
    ASSERT_EQ(q->Size(), --size_1);
  }
}
