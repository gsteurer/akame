template <typename T> akame::LinkedList<T>::LinkedList() {
  m_root = NULL;
  m_last = NULL;
  m_num_elements = 0;
}

template <typename T> akame::LinkedList<T>::~LinkedList() {
  while (m_root != NULL) {
    PopBack();
  }
}

template <typename T> size_t akame::LinkedList<T>::Size() const {
  return m_num_elements;
}

template <typename T> void akame::LinkedList<T>::PushFront(T data) {
  Node *next = new akame::LinkedList<T>::Node(data);
  if (m_root == NULL) {
    m_root = next;
    m_last = m_root;
  } else {
    m_root->prev = next;
    next->next = m_root;
    m_root = next;
  }
  m_num_elements++;
}

template <typename T> void akame::LinkedList<T>::PushBack(T data) {
  Node *next = new akame::LinkedList<T>::Node(data);
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

template <typename T> T akame::LinkedList<T>::PopFront() {

  if (m_root == NULL) {
    throw std::out_of_range("cannot pop empty list");
  }
  Node *root = m_root;
  root->prev = NULL;
  m_root = root->next;
  m_num_elements--;
  T data = root->data;
  delete root;
  return data;
}

template <typename T> T akame::LinkedList<T>::PopBack() {

  if (m_last == NULL) {
    throw std::out_of_range("cannot pop empty list");
  }
  Node *last = m_last;
  m_last = last->prev;
  if (m_last != NULL) {
    m_last->next = NULL;
  }
  m_num_elements--;
  T data = last->data;
  delete last;
  return data;
}

template <typename T> T akame::LinkedList<T>::operator[](size_t idx) const {
  if (idx >= m_num_elements) {
    throw std::out_of_range("index out of bounds");
  }
  akame::LinkedList<T>::Node *current = m_root;
  for (int i = 0; i < idx; idx++) {
    current = current->next;
  }
  return current->data;
}

template <typename T> T &akame::LinkedList<T>::operator[](size_t idx) {
  if (idx >= m_num_elements) {
    throw std::out_of_range("index out of bounds");
  }
  akame::LinkedList<T>::Node *current = m_root;
  for (int i = 0; i < idx; idx++) {
    current = current->next;
  }

  return &(current->data);
}
