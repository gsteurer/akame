template <typename T> akame::Queue<T>::Queue() {
  m_root = NULL;
  m_last = NULL;
  m_num_elements = 0;
}

template <typename T> akame::Queue<T>::~Queue() {
  while (m_root != NULL) {
    Pop();
  }
}

template <typename T> size_t akame::Queue<T>::Size() const {
  return m_num_elements;
}

template <typename T> void akame::Queue<T>::Push(T data) {
  Node *next = new akame::Queue<T>::Node(data);
  if (m_root == NULL) {
    m_root = next;
    m_last = m_root;
  } else {
    m_last->next = next;
    next->prev = m_last;
    m_last = next;
  }
  m_num_elements++;
}

template <typename T> T akame::Queue<T>::Pop() {

  if (m_root == NULL) {
    throw std::out_of_range("cannot pop empty queue");
  }
  Node *root = m_root;
  root->prev = NULL;
  m_root = root->next;
  m_num_elements--;
  T data = root->data;
  delete root;
  return data;
}

template <typename T> T akame::Queue<T>::operator[](size_t idx) const {}
