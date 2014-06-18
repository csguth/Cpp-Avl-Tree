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

class Range_Tree
{
public:
    enum Remove_Status {
        SUCCESS = 0,
        INVALID_POSITION,
        NOT_FOUND
    };
private:

    class Node {
        enum Side {
            LEFT = 0, RIGHT, CENTER
        };

        friend class Range_Tree;
        Node * _left;
        Node * _right;
        pair<int, unsigned> _value;
        unsigned _height;

        Node *__insert(int value, unsigned width, Node *parent);
        Node *__insert_in_side(int value, unsigned width, Side side);
        void __update_height();

        bool __check(int value, unsigned width);
        Node * __rotate_left(Node * parent);
        Node * __rotate_left_pre_double_rotate(Node * parent);
        Node * __rotate_right(Node * parent);
        Node * __rotate_right_pre_double_rotate(Node * parent);
        Node * __balance(Node * parent);

        Node * __remove(int value, Remove_Status & status, Node * parent, Node ** removed);
        Node * __remove_from_side(int value, Side side, Remove_Status & status, Node * parent, Node ** removed);
        Node * __remove_bigger_smaller_child();

        Node(int begin, int width);
        virtual ~Node();
        int __balance_factor() const;

        // debug
        void print_node(int offset = 0);
    };

    int _begin;
    int _end;
    int _size;
    Node * _root;

public:
    static const std::pair<int, unsigned> EMPTY_TREE_ROOT;

    Range_Tree(int begin, int end);
    virtual ~Range_Tree();
    int begin();
    int end();
    bool empty();
    bool insert(int begin, unsigned width);
    bool check(int begin, unsigned width);
    Remove_Status remove(int position);
    unsigned size();
    std::pair<int, unsigned> root();

    // DEBUG
    void print_tree();
};

#endif // RANGE_TREE_H
