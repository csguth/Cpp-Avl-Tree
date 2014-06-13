#include "range_tree.h"


Range_Tree::Range_Tree(int begin, int end): _begin(begin), _end(end), _size(0), _root(NULL)
{

}

Range_Tree::~Range_Tree()
{
    if(_root != NULL)
        delete _root;
}

int Range_Tree::begin()
{
    return _begin;
}

int Range_Tree::end()
{
    return _end;
}

bool Range_Tree::empty()
{
    return _size == 0;
}

bool Range_Tree::insert(int begin, int width)
{
    if(begin < _begin)
        return false;
    if(begin + width > _end)
        return false;

    bool ok = false;
    if(_size == 0)
    {
        _root = new Node(begin, width);
        ok = true;
    }
    else
        ok = _root->__insert(begin, width);

    if(ok)
    {
        _size++;
        Node * aux;
        switch(_root->balance())
        {
        case -2:
            aux = _root->_right;
            _root->__rotate_left(NULL);
            _root = aux;
            break;
        case 2:
            aux = _root->_left;
            _root->__rotate_right(NULL);
            _root = aux;
            break;
        }
    }

    return ok;
}

bool Range_Tree::check(int begin, int width)
{
    if(_root != NULL)
        return _root->__check(begin, width);
    return begin >= _begin && begin + width <= _end;
}

unsigned Range_Tree::size()
{
    return _size;
}

const Range_Tree::Node *Range_Tree::root()
{
    return _root;
}


bool Range_Tree::Node::__insert(int value, int width)
{
    if(value + width < _value.first)
        return __insert_in_side(value, width, LEFT);
    else if(value > _value.first + _value.second)
        return __insert_in_side(value, width, RIGHT);
    else
        return false;
}

bool Range_Tree::Node::__insert_in_side(int value, int width, Range_Tree::Node::Side side)
{
    bool ok = false;
    switch (side) {
    case LEFT:
        if(_left == NULL)
        {
            _left = new Node(value, width);
            ok = true;
        }
        else
        {
            ok = _left->__insert(value, width);
        }
        break;
    case RIGHT:
        if(_right == NULL)
        {
            _right = new Node(value, width);
            ok = true;
        }
        else
            ok = _right->__insert(value, width);
        break;
    default:
        assert(false);
    }
    if(ok)
    {
        __update_height();
    }

    return ok;
}

void Range_Tree::Node::__update_height()
{

    if(_left == NULL && _right == NULL)
        _height = 0;
    else if(_left == NULL)
        _height = _right->height() + 1;
    else if(_right == NULL)
        _height = _left->height() + 1;
    else
        _height = max(_right->height(), _left->height()) + 1;

}

bool Range_Tree::Node::__check(int value, int width)
{
    if(value < _value.first && value + width > _value.first)
        return false;

    if(value + width < _value.first)
    {
        if(_left == NULL)
            return true;
        return _left->__check(value, width);
    }


    if(value > _value.first && value < _value.first + _value.second)
        return false;

    if(value > _value.first + _value.second)
    {
        if(_right == NULL)
            return true;
        return _right->__check(value, width);
    }

    return false;

}

void Range_Tree::Node::__rotate_left(Node *parent)
{
    Node * aux = _right->_left;
    _right->_left = this;
    if(parent != NULL)
        parent->_right = _right;
    _right = aux;
}

void Range_Tree::Node::__rotate_right(Node *parent)
{
    Node * aux = _left->_right;
    _left->_right = this;
    if(parent != NULL)
        parent->_left = _left;
    _left = aux;
}

//void Range_Tree::Node::__balance_if_neccessary(Node * parent)
//{
//    int left_height = 0;
//    int right_height = 0;
//    if(_left != NULL)
//        left_height = _left->height() + 1;
//    if(_right != NULL)
//        right_height = _right->height() + 1;
//    if(left_height - right_height >= -1 && left_height - right_height <= 1)
//        return;
//    if(left_height - right_height == 2)
//    {

//    }
//    if(left_height - right_height == -2)
//    {

//    }


//}

Range_Tree::Node::Node(int begin, int width): _left(NULL), _right(NULL), _value(std::make_pair(begin, width)), _height(0)
{

}

Range_Tree::Node::~Node()
{
    if(_left != NULL)
        delete _left;
    if(_right != NULL)
        delete _right;
}

unsigned Range_Tree::Node::height() const
{
    return _height;
}

int Range_Tree::Node::balance() const
{
    if(_left == NULL && _right == NULL)
        return 0;
    else if(_left == NULL)
        return -_height;
    else if(_right == NULL)
        return _height;
    return _left->_height - _right->_height;
}

pair<int, int> Range_Tree::Node::value() const
{
    return _value;
}
