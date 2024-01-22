#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "RBTree.h"
template <class T>
RbNode<T>::RbNode(T data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

template <class T>
RbTree<T>::RbTree() {
    nil = new RbNode<T>(T());
    nil->color = BLACK;
    root = nil;
}

template <class T>
RbTree<T>::~RbTree() {
    destroy(root);
    delete nil;
}

template <class T>
void RbTree<T>::destroy(RbNode<T> *x) {
    if (x != nil) {
        destroy(x->left);
        destroy(x->right);
        delete x;
    }
}

template <class T>
void RbTree<T>::leftRotate(RbNode<T> *x) {
    RbNode<T> *y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <class T>
void RbTree<T>::rightRotate(RbNode<T> *x) {
    RbNode<T> *y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template <class T>
void RbTree<T>::rbInsertFixup(RbNode<T> *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RbNode<T> *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            RbNode<T> *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <class T>
void RbTree<T>::rbTransplant(RbNode<T> *u, RbNode<T> *v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template <class T>
RbNode<T> *RbTree<T>::treeMinimum(RbNode<T> *x) {
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

template <class T>
void RbTree<T>::rbDeleteFixup(RbNode<T> *x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            RbNode<T> *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            RbNode<T> *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

template <class T>
void RbTree<T>::rbDelete(RbNode<T> *z) {
    RbNode<T> *y = z;
    RbNode<T> *x;
    Color yOriginalColor = y->color;
    if (z->left == nil) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK) {
        rbDeleteFixup(x);
    }
}

template <class T>
void RbTree<T>::insert(T data) {
    RbNode<T> *z = new RbNode<T>(data);
    RbNode<T> *y = nil;
    RbNode<T> *x = root;
    while (x != nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    rbInsertFixup(z);
}

template <class T>
void RbTree<T>::remove(T data) {
    RbNode<T> *z = search(root, data);
    if (z != nil) {
        rbDelete(z);
    }
}

template <class T>
void RbTree<T>::inorder() {
    inorder(root);
}

template <class T>
void RbTree<T>::inorder(RbNode<T> *x) {
    if (x != nil) {
        inorder(x->left);
        std::cout << "\n";
        // You can customize the formatting based on your desired output
        std::cout << std::left << x->data << " [" << (x->color == RED ? "R" : "B") << "] ";

        inorder(x->right);
    }
}

template <class T>
void RbTree<T>::preorder() {
    preorder(root);
    std::cout << "\n";
}

template <class T>
void RbTree<T>::preorder(RbNode<T> *x) {
    if (x != nil) {
        std::cout << x->data << " ";
        preorder(x->left);
        preorder(x->right);
    }
}

template <class T>
void RbTree<T>::postorder() {
    postorder(root);
    std::cout << "\n";
}

template <class T>
void RbTree<T>::postorder(RbNode<T> *x) {
    if (x != nil) {
        postorder(x->left);
        postorder(x->right);
        std::cout << x->data << " ";
    }
}

template <class T>
RbNode<T> *RbTree<T>::search(RbNode<T> *x, T data) {
    while (x != nil && x->data != data) {
        if (data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x == nil ? nullptr : x;
}

template <class T>
RbNode<T> *RbTree<T>::search(T data) {
    return search(root, data);
}

template <class T>
RbNode<T> *RbTree<T>::minimum() {
    return minimum(root);
}

template <class T>
RbNode<T> *RbTree<T>::minimum(RbNode<T> *x) {
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

template <class T>
RbNode<T> *RbTree<T>::maximum() {
    return maximum(root);
}

template <class T>
RbNode<T> *RbTree<T>::maximum(RbNode<T> *x) {
    while (x->right != nil) {
        x = x->right;
    }
    return x;
}

template <class T>
RbNode<T> *RbTree<T>::successor(T data) {
    RbNode<T> *x = search(root, data);
    if (x != nil) {
        return successor(x);
    }
    return nil;
}

template <class T>
RbNode<T> *RbTree<T>::successor(RbNode<T> *x) {
    if (x->right != nil) {
        return minimum(x->right);
    }
    RbNode<T> *y = x->parent;
    while (y != nil && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

template <class T>
RbNode<T> *RbTree<T>::predecessor(T data) {
    RbNode<T> *x = search(root, data);
    if (x != nil) {
        return predecessor(x);
    }
    return nil;
}

template <class T>
RbNode<T> *RbTree<T>::predecessor(RbNode<T> *x) {
    if (x->left != nil) {
        return maximum(x->left);
    }
    RbNode<T> *y = x->parent;
    while (y != nil && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

template <class T>
RbNode<T> *RbTree<T>::getRoot() {
    return root;
}

