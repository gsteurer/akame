
namespace akame {
namespace rbtree {

enum COLOR {RED = 0, BLACK = 1};
template <typename T> struct Node {
  Node<T> *Parent;
  Node<T> *Left;
  Node<T> *Right;
  COLOR Color; 
  T Key;
  Node() {
  	Parent = NULL;
  	Left = NULL;
  	Right = NULL;
  	Color = COLOR::RED;
  }
  static Node<T> T_NULL_NODE;
  static Node<T>* T_NIL;
};



template <class T>
void rbLeftRotate(akame::rbtree::Node<T> **tree, akame::rbtree::Node<T> *x) {
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
void rbRightRotate(akame::rbtree::Node<T> **tree, akame::rbtree::Node<T> *x) {
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

template <class T>
void rbInsert(akame::rbtree::Node<T> **tree, T key) {
	akame::rbtree::Node<T> *z = new akame::rbtree::Node<T>();
	z->Key = key;
	akame::rbtree::Node<T> *y = Node<T>::T_NIL;
	akame::rbtree::Node<T> *x = *tree;
	while (x != Node<T>::T_NIL) {
		y = x;
		if (z->Key < x->Key) {
			x = x->Left;
		}else {
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
	while(z->Parent->Color == COLOR::RED && z->Parent != Node<T>::T_NIL) {
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

} // namespace rbtree
} // namespace akame