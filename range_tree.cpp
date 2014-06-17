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
    if(_root == NULL)
    {
        if(begin < _begin || begin + width > _end)
            return false;
        _root = new Node(begin, width);
        _size = 1;
        return true;
    }
    Node * root_of_subtree = _root->__insert(begin, width, NULL);
    if(root_of_subtree != NULL)
    {
        _root = root_of_subtree;
        _size++;
        return true;
    }
    return false;
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

std::pair<int, unsigned> Range_Tree::root()
{
    return _root->_value;
}

void Range_Tree::print_tree()
{
    cout << "Tree: " << endl;
    if(_root == NULL)
        cout << "NULL" << endl;
    else
        _root->print_node();
}


Range_Tree::Node *  Range_Tree::Node::__insert(int value, int width, Node * parent)
{
    Node * root = this;
    if(value > _value.first + _value.second)
    {
        this->__insert_in_side(value, width, RIGHT);
        if(this->balance() == -2)
        {
            if(_right->balance() > 0)
                _right->__rotate_right_pre_double_rotate(this);
            root = this->__rotate_left(parent);
        }
    }
    else if(value > _value.first && value <= _value.first + _value.second)
        return NULL;
    else if(value + width < _value.first)
    {
        this->__insert_in_side(value, width, LEFT);
        if(this->balance() == 2)
        {
            if(_left->balance() < 0)
                _left->__rotate_left_pre_double_rotate(this);
            root = this->__rotate_right(parent);
        }
    }
    else if(value < _value.first && value + width >= _value.first)
        return NULL;
    return root;
}

Range_Tree::Node* Range_Tree::Node::__insert_in_side(int value, int width, Range_Tree::Node::Side side)
{
    Node * root = NULL;

    switch(side)
    {
    case RIGHT:
        if(_right == NULL)
        {
            _right = new Node(value, width);
            root = _right;
        } else {
            root = _right->__insert(value, width, this);
        }
        break;
    case LEFT:
        if(_left == NULL)
        {
            _left = new Node(value, width);
            root = _left;
        } else {
            root = _left->__insert(value, width, this);
        }
        break;
    }
    __update_height();
    return root;
}

void Range_Tree::Node::__update_height()
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

Range_Tree::Node * Range_Tree::Node::__rotate_left(Node *parent)
{
    Node * root = _right;
    Node * aux = _right->_left;
    _right->_left = this;
    if(parent != NULL)
        parent->_right = _right;
    _right = aux;
    __update_height();
    return root;
}

Range_Tree::Node *Range_Tree::Node::__rotate_left_pre_double_rotate(Range_Tree::Node *parent)
{
    Node * root = _right;
    Node * aux = _right->_left;
    _right->_left = this;
    if(parent != NULL)
        parent->_left = _right;
    _right = aux;
    __update_height();
    return root;
}

Range_Tree::Node *  Range_Tree::Node::__rotate_right(Node *parent)
{
    Node * root = _left;
    Node * aux = _left->_right;
    _left->_right = this;
    if(parent != NULL)
        parent->_left = _left;
    _left = aux;
    __update_height();
    return root;
}

Range_Tree::Node *Range_Tree::Node::__rotate_right_pre_double_rotate(Range_Tree::Node *parent)
{
    Node * root = _left;
    Node * aux = _left->_right;
    _left->_right = this;
    if(parent != NULL)
        parent->_right = _left;
    _left = aux;
    __update_height();
    return root;
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

Range_Tree::Node::Node(int begin, int width): _left(NULL), _right(NULL), _value(std::make_pair(begin, width)), _height(1)
{

}

Range_Tree::Node::~Node()
{
    if(_left != NULL)
        delete _left;
    if(_right != NULL)
        delete _right;
}


int Range_Tree::Node::balance() const
{
    int right_height = 1;
    int left_height = 1;
    if(_left != NULL)
        left_height = _left->_height + 1;
    if(_right != NULL)
        right_height = _right->_height + 1;
    return left_height - right_height;
}

void Range_Tree::Node::print_node(int offset)
{
    for(int i = 0; i < offset; i++)
        cout << "    ";
    cout << _value.first << ", " << _value.second << endl;
    if(_left == NULL)
    {
        for(int i = 0; i < offset+1; i++)
            cout << "    ";
        cout << "NULL" << endl;
    }
    else
        _left->print_node(offset+1);
    if(_right == NULL)
    {
        for(int i = 0; i < offset+1; i++)
            cout << "    ";
        cout << "NULL" << endl;
    }
    else
        _right->print_node(offset+1);
}
