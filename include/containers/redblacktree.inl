namespace akame {
namespace rbtree {

template <class T>
inline void rbLeftRotate(akame::rbtree::Node<T> **tree,
                         akame::rbtree::Node<T> *x) {
  akame::rbtree::Node<T> *y = x->Right;
  x->Right = y->Left;
  if (y->Left != Node<T>::T_NIL) {
    y->Left->Parent = x;
  }
  y->Parent = x->Parent;
  if (x->Parent == Node<T>::T_NIL) {
    *tree = y;
  } else if (x == x->Parent->Left) {
    x->Parent->Left = y;
  } else {
    x->Parent->Right = y;
  }
  y->Left = x;
  x->Parent = y;
}

template <class T>
inline void rbRightRotate(akame::rbtree::Node<T> **tree,
                          akame::rbtree::Node<T> *x) {
  akame::rbtree::Node<T> *y = x->Left;
  x->Left = y->Right;
  if (y->Right != Node<T>::T_NIL) {
    y->Right->Parent = x;
  }
  y->Parent = x->Parent;
  if (x->Parent == Node<T>::T_NIL) {
    *tree = y;
  } else if (x == x->Parent->Right) {
    x->Parent->Right = y;
  } else {
    x->Parent->Left = y;
  }
  y->Right = x;
  x->Parent = y;
}

template <class T> void rbInsert(akame::rbtree::Node<T> **tree, T key) {
  akame::rbtree::Node<T> *z = new akame::rbtree::Node<T>();
  z->Key = key;
  akame::rbtree::Node<T> *y = Node<T>::T_NIL;
  akame::rbtree::Node<T> *x = *tree;
  while (x != Node<T>::T_NIL) {
    y = x;
    if (z->Key < x->Key) {
      x = x->Left;
    } else {
      x = x->Right;
    }
  }
  z->Parent = y;
  if (y == Node<T>::T_NIL) {
    *tree = z;
  } else if (z->Key < y->Key) {
    y->Left = z;
  } else {
    y->Right = z;
  }
  z->Left = Node<T>::T_NIL;
  z->Right = Node<T>::T_NIL;
  z->Color = COLOR::RED;
  rbInsertFixup(tree, z);
}

template <class T>
void rbInsertFixup(akame::rbtree::Node<T> **tree, akame::rbtree::Node<T> *z) {
  while (z->Parent->Color == COLOR::RED && z->Parent != Node<T>::T_NIL) {
    if (z->Parent == z->Parent->Parent->Left) {
      akame::rbtree::Node<T> *y = z->Parent->Parent->Right;
      if (y->Color == COLOR::RED) {
        z->Parent->Color = COLOR::BLACK;
        y->Color = COLOR::BLACK;
        z->Parent->Parent->Color = COLOR::RED;
        z = z->Parent->Parent;
      } else {
        if (z == z->Parent->Right) {
          z = z->Parent;
          rbLeftRotate(tree, z);
        }
        z->Parent->Color = COLOR::BLACK;
        z->Parent->Parent->Color = COLOR::RED;
        rbRightRotate(tree, z->Parent->Parent);
      }
    } else {
      akame::rbtree::Node<T> *y = z->Parent->Parent->Left;
      if (y->Color == COLOR::RED) {
        z->Parent->Color = COLOR::BLACK;
        y->Color = COLOR::BLACK;
        z->Parent->Parent->Color = COLOR::RED;
        z = z->Parent->Parent;
      } else {
        if (z == z->Parent->Left) {
          z = z->Parent;
          rbRightRotate(tree, z);
        }
        z->Parent->Color = COLOR::BLACK;
        z->Parent->Parent->Color = COLOR::RED;
        rbLeftRotate(tree, z->Parent->Parent);
      }
    }
  }
  tree[0]->Color = COLOR::BLACK;
}

template <class T>
inline void rbTransplant(akame::rbtree::Node<T> **tree,
                         akame::rbtree::Node<T> *u, akame::rbtree::Node<T> *v) {
  if (u->Parent == Node<T>::T_NIL) {
    *tree = v;
  } else if (u == u->Parent->Left) {
    u->Parent->Left = v;
  } else {
    u->Parent->Right = v;
  }
  v->Parent = u->Parent;
}

template <class T>
inline void rbDelete(akame::rbtree::Node<T> **tree, akame::rbtree::Node<T> *z) {
  akame::rbtree::Node<T> *y = z;
  COLOR y_original_color = y->Color;
  akame::rbtree::Node<T> *x;
  if (z->Left == Node<T>::T_NIL) {
    x = z->Right;
    rbTransplant(tree, z, z->Right);
  } else if (z->Right == Node<T>::T_NIL) {
    x = z->Left;
    rbTransplant(tree, z, z->Left);
  } else {
    y = rbTreeMinimum(z->Right);
    y_original_color = y->Color;
    x = y->Right;
    if (y->Parent == z) {
      x->Parent = y;
    } else {
      rbTransplant(tree, y, y->Right);
      y->Right = z->Right;
      y->Right->Parent = y;
    }
    rbTransplant(tree, z, y);
    y->Left = z->Left;
    y->Left->Parent = y;
    y->Color = z->Color;
  }

  if (y_original_color == COLOR::BLACK) {
    rbDeleteFixup(tree, x);
  }
}

template <class T>
inline void rbDeleteFixup(akame::rbtree::Node<T> **tree,
                          akame::rbtree::Node<T> *x) {
  while (x != *tree && x->Color == COLOR::BLACK && x != Node<T>::T_NIL) {
    if (x == x->Parent->Left) {
      akame::rbtree::Node<T> *w = x->Parent->Right;
      if (w->Color == COLOR::RED) {
        w->Color = COLOR::BLACK;
        x->Parent->Color = COLOR::RED;
        rbLeftRotate(tree, x->Parent);
        w = x->Parent->Right;
      }
      if (w->Left->Color == COLOR::BLACK && w->Right->Color == COLOR::BLACK) {
        w->Color = COLOR::RED;
        x = x->Parent;
      } else {
        if (w->Right->Color == COLOR::BLACK) {
          w->Left->Color = COLOR::BLACK;
          w->Color = COLOR::RED;
          rbRightRotate(tree, w);
          w = w->Parent->Right;
        }
        w->Color = x->Parent->Color;
        x->Parent->Color = COLOR::BLACK;
        w->Right->Color = COLOR::BLACK;
        rbLeftRotate(tree, x->Parent);
        x = *tree;
      }
    } else {
      akame::rbtree::Node<T> *w = x->Parent->Left;
      if (w->Color == COLOR::RED) {
        w->Color = COLOR::BLACK;
        x->Parent->Color = COLOR::RED;
        rbRightRotate(tree, x->Parent);
        w = x->Parent->Left;
      }
      if (w->Right->Color == COLOR::BLACK && w->Left->Color == COLOR::BLACK) {
        w->Color = COLOR::RED;
        x = x->Parent;
      } else {
        if (w->Left->Color == COLOR::BLACK) {
          w->Right->Color = COLOR::BLACK;
          w->Color = COLOR::RED;
          rbLeftRotate(tree, w);
          w = w->Parent->Left;
        }
        w->Color = x->Parent->Color;
        x->Parent->Color = COLOR::BLACK;
        w->Left->Color = COLOR::BLACK;
        rbRightRotate(tree, x->Parent);
        x = *tree;
      }
    }
  }
  x->Color = COLOR::BLACK;
}

template <class T>
inline akame::rbtree::Node<T> *rbTreeMinimum(akame::rbtree::Node<T> *x) {
  while (x->Left != Node<T>::T_NIL) {
    x = x->Left;
  }
  return x;
}

template <class T>
inline akame::rbtree::Node<T> *rbTreeMaximum(akame::rbtree::Node<T> *x) {
  while (x->Right != Node<T>::T_NIL) {
    x = x->Right;
  }
  return x;
}

template <class T>
inline akame::rbtree::Node<T> *rbTreeSearch(akame::rbtree::Node<T> *x, T k) {
  while (x != Node<T>::T_NIL && k != x->Key) {
    if (k < x->Key) {
      x = x->Left;
    } else {
      x = x->Right;
    }
  }
  return x;
}

} // namespace rbtree
} // namespace akame