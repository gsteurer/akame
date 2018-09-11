template <typename T> akame::PriorityQueue<T>::PriorityQueue() {
  m_capacity = 10;
  m_data = new T[m_capacity];
  m_size = 0;
}

template <typename T> akame::PriorityQueue<T>::~PriorityQueue() {
  delete[] m_data;
}

template <typename T> void akame::PriorityQueue<T>::Resize() {
  m_capacity = m_capacity + static_cast<size_t>(ceil(log2(m_capacity)));
  T *tmp = new T[m_capacity];
  for (int idx = 0; idx < m_size; idx++)
    tmp[idx] = m_data[idx];
  delete[] m_data;
  m_data = tmp;
}

// must preserve m_data[Parent(i)] >= m_data[i]
template <typename T> void akame::PriorityQueue<T>::MaxHeapify(size_t i) {
  auto l = Left(i);
  auto r = Right(i);
  auto largest = (l <= m_size) && (m_data[l] > m_data[i]) ? l : i;
  largest = (r <= m_size) && (m_data[r] > m_data[largest]) ? r : largest;
  if (largest != i) {
    Swap(i, largest);
    MaxHeapify(largest);
  }
}

template <typename T> T akame::PriorityQueue<T>::Pop() {
  if (m_size < 1) {
    throw std::underflow_error("priority queue underflow");
  }
  T max = m_data[0];
  m_data[0] = m_data[m_size - 1];
  m_size--;
  MaxHeapify(0);
  return max;
}

template <typename T>
void akame::PriorityQueue<T>::HeapIncreaseKey(size_t i, T key) {
  /*if (key < m_data[i]) {
    throw std::runtime_error("The implementation is wrong.");
  }*/
  m_data[i] = key;
  while ((i > 0) && (m_data[Parent(i)] < m_data[i])) {
    Swap(i, Parent(i));
    i = Parent(i);
  }
}

template <typename T> void akame::PriorityQueue<T>::Push(T key) {
  if (m_size >= m_capacity) {
    Resize();
  }
  m_size++;
  HeapIncreaseKey(m_size - 1, key);
}