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
    class Node {
        enum Side {
            LEFT = 0, RIGHT
        };

        friend class Range_Tree;
        Node * _left;
        Node * _right;
        pair<int, int> _value;
        unsigned _height;

        Node *__insert(int value, int width, Node * parent);
        Node *__insert_in_side(int value, int width, Side side);
        void __update_height();

        bool __check(int value, int width);
        void __rotate_left(Node * parent);
        void __rotate_right(Node * parent);
    public:
        Node(int begin, int width);
        virtual ~Node();
        unsigned height() const;
        int balance() const;
        pair<int, int> value() const;

        // debug
        void print_node(int offset = 0);
    };

private:


    int _begin;
    int _end;
    int _size;
    Node * _root;

public:


    Range_Tree(int begin, int end);
    virtual ~Range_Tree();
    int begin();
    int end();
    bool empty();
    bool insert(int begin, int width);
    bool check(int begin, int width);
    unsigned size();
    const Range_Tree::Node * root();

    // DEBUG
    void print_tree();
};

#endif // RANGE_TREE_H
