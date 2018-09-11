#pragma once
#include <exception>
#include <math.h>
namespace akame {

template <class T> class PriorityQueue {
public:
  PriorityQueue();
  ~PriorityQueue();
  T Pop();
  void Push(T key);
  inline size_t Size() { return m_size; }
  inline size_t Capacity() { return m_capacity; }
  const T At(size_t idx) const { return m_data[idx]; }

private:
  inline size_t Parent(size_t i) { return (i - 1) / 2; }
  inline size_t Left(size_t i) { return (2 * i) + 1; }
  inline size_t Right(size_t i) { return (2 * i) + 2; }
  inline void Swap(size_t lhs, size_t rhs) {
    T tmp = m_data[lhs];
    m_data[lhs] = m_data[rhs];
    m_data[rhs] = tmp;
  }
  inline void HeapMaximum(size_t i) { return m_data[0]; }
  inline void MaxHeapify(size_t i);
  inline void HeapIncreaseKey(size_t i, T key);

  void Resize();
  T *m_data;
  // 0 <= size <= capacity
  size_t m_size;
  size_t m_capacity;
};
} // namespace akame

#include "priorityqueue.inl"