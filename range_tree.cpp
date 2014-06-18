#include "range_tree.h"

const std::pair<int, unsigned> Range_Tree::EMPTY_TREE_ROOT = std::make_pair(numeric_limits<int>::infinity(), 0);

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

bool Range_Tree::insert(int begin, unsigned width)
{
    if(_root == NULL)
    {
        if(begin < _begin || int(begin + width) > _end)
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

bool Range_Tree::check(int begin, unsigned width)
{
    if(_root != NULL)
        return _root->__check(begin, width);
    return begin >= _begin && int(begin + width) <= _end;
}

Range_Tree::Remove_Status Range_Tree::remove(int position)
{
    if(position < _begin || position > _end)
        return INVALID_POSITION;
    if(_root == NULL)
        return NOT_FOUND;
    Remove_Status status;
    Node * removed = NULL;
    Node * root_of_subtree = _root->__remove(position, status, NULL, &removed);
    if(status == SUCCESS)
    {
        removed->_left = NULL;
        removed->_right = NULL;
        delete removed;
        if(root_of_subtree != NULL)
            root_of_subtree->__update_height();
        _root = root_of_subtree;
        _size--;
    }
    return status;
}

unsigned Range_Tree::size()
{
    return _size;
}

std::pair<int, unsigned> Range_Tree::root()
{
    if(_root == NULL)
        return Range_Tree::EMPTY_TREE_ROOT;
    return _root->_value;
}

std::pair<int, unsigned> Range_Tree::find(int begin, unsigned width)
{
    if(_root != NULL)
        return _root->__find(begin, width);
    return Range_Tree::EMPTY_TREE_ROOT;
}

void Range_Tree::print_tree()
{
    cout << "Tree: " << endl;
    if(_root == NULL)
        cout << "NULL" << endl;
    else
        _root->print_node();
}


Range_Tree::Node *  Range_Tree::Node::__insert(int value, unsigned width, Node * parent)
{
    Side side = RIGHT;
    if(value > int(_value.first + _value.second))
        side = RIGHT;
    else if(int(value + width) < _value.first)
        side = LEFT;
    else if((value < _value.first && int(value + width) >= _value.first) || (value > _value.first && value <= int(_value.first + _value.second)))
        return NULL;

    this->__insert_in_side(value, width, side);
    Node * root = __balance(parent);

    return root;
}

Range_Tree::Node * Range_Tree::Node::__balance(Node * parent)
{
    Node * root = this;
    switch(this->__balance_factor())
    {
    case 2:
        if(_left->__balance_factor() < 0)
            _left->__rotate_left_pre_double_rotate(this);
        root = this->__rotate_right(parent);
        break;
    case -2:
        if(_right->__balance_factor() > 0)
            _right->__rotate_right_pre_double_rotate(this);
        root = this->__rotate_left(parent);
        break;
    }
    return root;
}

Range_Tree::Node *Range_Tree::Node::__remove(int value, Range_Tree::Remove_Status &status, Range_Tree::Node *parent, Node ** removed)
{
    Side side = LEFT;
    if(value < _value.first)
        side = LEFT;
    else if(value > int(_value.first + _value.second))
        side = RIGHT;
    else
        side = CENTER;

    Node * root = __remove_from_side(value, side, status, (side==CENTER?parent:this), removed);
    if(status != SUCCESS)
        return NULL;
    if(side == CENTER)
        return root;
    return __balance(parent);
}

Range_Tree::Node *Range_Tree::Node::__remove_from_side(int value, Range_Tree::Node::Side side, Range_Tree::Remove_Status &status, Node * parent, Node ** removed)
{
    Node * root = NULL;
    (*removed) = NULL;
    switch(side)
    {
    case LEFT:
        if(_left == NULL)
            status = NOT_FOUND;
        else
            root = _left->__remove(value, status, this, removed);
        break;
    case RIGHT:
        if(_right == NULL)
            status = NOT_FOUND;
        else
            root = _right->__remove(value, status, this, removed);
        break;
    case CENTER:
        status = SUCCESS;
        root = __remove_bigger_smaller_child();
        if(root != NULL)
        {
            root->_right = _right;
            root->_left = _left;
        }
        if(parent != NULL)
        {
            if(parent->_right == this)
                parent->_right = root;
            else if(parent->_left == this)
                parent->_left = root;
        }
        (*removed) = this;
        break;
    }
    if(status == SUCCESS && root != NULL)
        root = root->__balance(parent);
    return root;
}

Range_Tree::Node *Range_Tree::Node::__remove_bigger_smaller_child()
{
    Node * max = _left;
    Node * right_child = NULL;
    Node * parent = this;
    if(max == NULL)
        return NULL;
    right_child = max->_right;
    while(right_child != NULL)
    {
        parent = max;
        max = right_child;
        right_child = max->_right;
    }
    if(parent->_right == max)
        parent->_right = NULL;
    if(parent->_left == max)
        parent->_left = NULL;
    return max;
}



Range_Tree::Node* Range_Tree::Node::__insert_in_side(int value, unsigned width, Range_Tree::Node::Side side)
{
    Node * root = NULL;

    switch(side)
    {
    case RIGHT:
        if(_right == NULL)
        {
            _right = new Node(value, width);
            root = _right;
        } else
            root = _right->__insert(value, width, this);
        break;
    case LEFT:
        if(_left == NULL)
        {
            _left = new Node(value, width);
            root = _left;
        } else
            root = _left->__insert(value, width, this);
        break;
    case CENTER:
        return NULL;
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

bool Range_Tree::Node::__check(int value, unsigned width)
{
    if((value < _value.first && int(value + width) > _value.first) || (value > _value.first && value < int(_value.first + _value.second)))
        return false;

    if(int(value + width) < _value.first)
    {
        if(_left == NULL)
            return true;
        return _left->__check(value, width);
    }

    if(value > int(_value.first + _value.second))
    {
        if(_right == NULL)
            return true;
        return _right->__check(value, width);
    }

    return false;
}

std::pair<int, unsigned> Range_Tree::Node::__find(int value, unsigned width)
{
    static int count;
    count++;
    cout << "Range_Tree::Node::__find(int value, unsigned width) count = " << count << endl;
    if((value < _value.first && int(value + width) > _value.first) || (value > _value.first && value < int(_value.first + _value.second)))
        return _value;

    if(int(value + width) < _value.first)
    {
        if(_left == NULL)
            return Range_Tree::EMPTY_TREE_ROOT;
        return _left->__find(value, width);
    }

    if(value > int(_value.first + _value.second))
    {
        if(_right == NULL)
            return Range_Tree::EMPTY_TREE_ROOT;
        return _right->__find(value, width);
    }

    return Range_Tree::EMPTY_TREE_ROOT;
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


int Range_Tree::Node::__balance_factor() const
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
    cout << "value " << _value.first << " width " << _value.second << " height " << _height << endl;
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
