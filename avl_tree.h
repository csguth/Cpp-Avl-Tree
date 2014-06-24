#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstdlib>

#include <utility>
using std::pair;
using std::make_pair;

#include <limits>
using std::numeric_limits;

#include <algorithm>
using std::max;

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class AVL_Tree
{
    class Node {
    public:
        enum Balance_Factor {
            UNBALANCED_TO_RIGHT = -2,
            BALANCED_TO_RIGHT = -1,
            BALANCED_CENTER = 0,
            BALANCED_TO_LEFT = 1,
            UNBALANCED_TO_LEFT = 2
        };

        Node * _left;
        Node * _right;
        T _value;
        unsigned _height;

        void __update_height();
        const T __find(T value);
        Node * __insert(T value);
        Node * __max();
        Node * __balance();
        Node * __RR_rotate();
        Node * __LR_rotate();
        Node * __RL_rotate();
        Node * __LL_rotate();

        Node(const T & value);
        virtual ~Node();
        int __balance_factor() const;

        // debug
        void print_node(int offset = 0);
    };

    int _size;
    Node * _root;
    Node *__remove(Node * root, const T &position, T & removed);

public:
    AVL_Tree();
    virtual ~AVL_Tree();

    bool empty();
    bool insert(const T & value);
    bool check(const T & value);

    unsigned size();

    const T root();
    const T find(const T & value);
    const T remove(const T &value);

    void print_tree();
};

// TREE
template <typename T>
AVL_Tree<T>::AVL_Tree(): _size(0), _root(NULL) {}

template <typename T>
AVL_Tree<T>::~AVL_Tree()
{
    if(_root != NULL)
        delete _root;
}

template <typename T>
bool AVL_Tree<T>::empty()
{
    return _size == 0;
}

template <typename T>
bool AVL_Tree<T>::insert(const T &value)
{
    if(_root == NULL)
    {
        _root = new Node(value);
        _size++;
        return true;
    }
    Node * root_of_subtree = _root->__insert(value);
    if(root_of_subtree != NULL)
    {
        _root = root_of_subtree;
        _size++;
        return true;
    }
    return false;
}

template <typename T>
const T AVL_Tree<T>::remove(const T & value)
{
    T removed = T::invalid();
    _root = __remove(_root, value, removed);
    return removed;
}

template <typename T>
unsigned AVL_Tree<T>::size()
{
    return _size;
}

template <typename T>
const T AVL_Tree<T>::root()
{
    if(_root == NULL)
        return T::invalid();
    return _root->_value;
}

template <typename T>
const T AVL_Tree<T>::find(const T & value)
{
    if(_root != NULL)
        return _root->__find(value);
    return T::invalid();
}

template <typename T>
void AVL_Tree<T>::print_tree()
{
    cout << "Tree: " << endl;
    if(_root == NULL)
        cout << "NULL" << endl;
    else
        _root->print_node();
}


template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::__remove(AVL_Tree::Node *root, const T & value, T &removed)
{
    if(root == NULL)
        return NULL;

    if(value == root->_value)
    {
        if(removed.sameAs(T::invalid()))
            removed = root->_value;
        if(root->_right == NULL)
        {
            Node * temp = root;
            root = root->_left;
            delete temp;
            _size--;
            return root;
        }
        else
        {
            Node * temp = root->_right;
            while(temp->_left != NULL)
                temp = temp->_left;
            root->_value = temp->_value;
            root->_right = __remove(root->_right, temp->_value, removed);
        }
    } else if(value < root->_value)
        root->_left = __remove(root->_left, value, removed);
    else if(value > root->_value)
        root->_right = __remove(root->_right, value, removed);

    root->__update_height();
    root = root->__balance();

    return root;
}


// NODE
template <typename T>
void AVL_Tree<T>::Node::__update_height()
{

    if(_left == NULL && _right == NULL)
        _height = 1;
    else if(_left == NULL)
        _height = _right->_height + 1;
    else if(_right == NULL)
        _height = _left->_height + 1;
    else
        _height = max(_right->_height, _left->_height) + 1;

}

template <typename T>
const T AVL_Tree<T>::Node::__find(T value)
{
    if(value == _value)
        return _value;
    if(value < _value)
    {
        if(_left)
            return _left->__find(value);
    } else if(value > _value)
    {
        if(_right)
            return _right->__find(value);
    }
    return T::invalid();
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__insert(T value)
{
    if(value == _value)
        return NULL;
    if(value < _value)
    {
        if(_left != NULL)
        {
            _left = _left->__insert(value);
            if(_left == NULL)
                return NULL;
        }
        else
            _left = new Node(value);
    }
    else if(value > _value)
    {
        if(_right != NULL)
        {
            _right = _right->__insert(value);
            if(_right == NULL)
                return NULL;
        }
        else
            _right = new Node(value);
    }

    __update_height();
    Node * root = __balance();
    return root;
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__max()
{
    if(_right == NULL)
        return this;
    return _right->__max();
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__balance()
{
    Node * root = this;
    switch(__balance_factor())
    {
    case UNBALANCED_TO_RIGHT:
        if(_right->__balance_factor() == BALANCED_TO_LEFT)
            root = __RL_rotate();
        else
            root = __LL_rotate();
        break;
    case UNBALANCED_TO_LEFT:
        if(_left->__balance_factor() == BALANCED_TO_RIGHT)
            root = __LR_rotate();
        else
            root = __RR_rotate();
        break;
    }

    return root;
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__RR_rotate()
{
    Node * a = _left;
    _left = a->_right;
    a->_right = this;
    __update_height();
    a->__update_height();
    return a;
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__LR_rotate()
{
    _left = _left->__LL_rotate();
    return __RR_rotate();
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__RL_rotate()
{
    _right = _right->__RR_rotate();
    return __LL_rotate();
}

template <typename T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::Node::__LL_rotate()
{
    Node * a = _right;
    _right = a->_left;
    a->_left = this;
    __update_height();
    a->__update_height();
    return a;
}

template <typename T>
AVL_Tree<T>::Node::Node(const T & value): _left(NULL), _right(NULL), _value(value), _height(1)
{

}

template <typename T>
AVL_Tree<T>::Node::~Node()
{
    if(_left != NULL)
        delete _left;
    if(_right != NULL)
        delete _right;
}


template <typename T>
int AVL_Tree<T>::Node::__balance_factor() const
{
    int right_height = 1;
    int left_height = 1;
    if(_left != NULL)
        left_height = _left->_height + 1;
    if(_right != NULL)
        right_height = _right->_height + 1;
    return left_height - right_height;
}



#endif // AVL_TREE_H
