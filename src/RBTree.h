#ifndef RbTree_H
#define RbTree_H

enum Color {
    RED,
    BLACK
};

template <class T>
class RbNode {
public:
    T data;
    Color color;
    RbNode<T> *left, *right, *parent;

    RbNode(T data);
};

template <class T>
class RbTree {
private:
    RbNode<T> *root;
    RbNode<T> *nil;

    void leftRotate(RbNode<T> *x);
    void rightRotate(RbNode<T> *x);
    void rbInsertFixup(RbNode<T> *z);
    void rbTransplant(RbNode<T> *u, RbNode<T> *v);
    RbNode<T> *treeMinimum(RbNode<T> *x);
    void rbDeleteFixup(RbNode<T> *x);
    void rbDelete(RbNode<T> *z);
    void inorder(RbNode<T> *x);
    void preorder(RbNode<T> *x);
    void postorder(RbNode<T> *x);
    RbNode<T> *search(RbNode<T> *x, T data);
    RbNode<T> *minimum(RbNode<T> *x);
    RbNode<T> *maximum(RbNode<T> *x);
    RbNode<T> *successor(RbNode<T> *x);
    RbNode<T> *predecessor(RbNode<T> *x);
    void destroy(RbNode<T> *x);
    RbNode<t> *getRoot();

public:
    RbTree();
    ~RbTree();
    void insert(T data);
    void remove(T data);
    void inorder();
    void preorder();
    void postorder();
    RbNode<T> *search(T data);
    RbNode<T> *minimum();
    RbNode<T> *maximum();
    RbNode<T> *successor(T data);
    RbNode<T> *predecessor(T data);
    bool operator==(const RbTree<T>& t);
    bool operator!=(const RbTree<T>& t);
    bool operator<(const RbTree<T>& t);
    bool operator>(const RbTree<T>& t);
    bool operator<=(const RbTree<T>& t);
    bool operator>=(const RbTree<T>& t);
};

#endif
