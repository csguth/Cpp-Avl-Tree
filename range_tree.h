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

        enum Balance_Factor {
            UNBALANCED_TO_RIGHT = -2,
            BALANCED_TO_RIGHT = -1,
            BALANCED_CENTER = 0,
            BALANCED_TO_LEFT = 1,
            UNBALANCED_TO_LEFT = 2
        };

        friend class Range_Tree;
        Node * _left;
        Node * _right;
        pair<int, unsigned> _value;
        unsigned _height;
        void __update_height();
        std::pair<int, unsigned> __find(int value, unsigned width);

        Node * __insert(std::pair<int, unsigned> value);
        Node * __max();
        Node * __balance();
        Node * __RR_rotate();
        Node * __LR_rotate();
        Node * __RL_rotate();
        Node * __LL_rotate();

        enum Comparison_Result {
            LESS_THAN = 0,
            GREATER_THAN,
            INTERSECT
        };

        Comparison_Result __compareTo(std::pair<int, unsigned> value);


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

    Node * __remove(Node * root, int position, std::pair<int, unsigned> & value);

public:
    static const std::pair<int, unsigned> EMPTY_TREE_ROOT;

    Range_Tree(int begin, int end);
    virtual ~Range_Tree();
    int begin();
    int end();
    bool empty();
    bool insert(int begin, unsigned width);
    bool check(int begin, unsigned width);


    unsigned size();
    std::pair<int, unsigned> root();
    std::pair<int, unsigned> find(int begin, unsigned width);
    std::pair<int, unsigned> remove(int position);

    // DEBUG
    void print_tree();
};

#endif // RANGE_TREE_H
