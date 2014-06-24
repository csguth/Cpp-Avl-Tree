#ifndef RANGE_TREE_H
#define RANGE_TREE_H

#include <cstdlib>

#include <utility>
using std::pair;
using std::make_pair;

#include <limits>
using std::numeric_limits;

#include <cassert>

#include <algorithm>
using std::max;

#include <iostream>
using std::cout;
using std::endl;

template <class T>
class AVL_Tree
{
    class Node {

        enum Balance_Factor {
            UNBALANCED_TO_RIGHT = -2,
            BALANCED_TO_RIGHT = -1,
            BALANCED_CENTER = 0,
            BALANCED_TO_LEFT = 1,
            UNBALANCED_TO_LEFT = 2
        };

        friend class AVL_Tree;
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

        Node(T value);
        virtual ~Node();
        int __balance_factor() const;

        // debug
        void print_node(int offset = 0);
    };

    int _size;
    Node * _root;

    Node * __remove(Node * root, int position, T & value);

public:

    AVL_Tree();
    virtual ~AVL_Tree();
    bool empty();
    bool insert(T value);
    bool check(T value);


    unsigned size();
    T root();
    T find(T value);
    T remove(int position);

};

#endif // RANGE_TREE_H
