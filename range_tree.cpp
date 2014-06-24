#include "range_tree.h"





AVL_Tree<T>::Node *AVL_Tree::__remove(Node *root, int position, T &value)
{
    if(root == NULL)
        return NULL;

    if(position >= root->_value.first && position <= int(root->_value.first + root->_value.second))
    {
        if(value == AVL_Tree::EMPTY_TREE_ROOT)
            value = root->_value;
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
            root->_right = __remove(root->_right, temp->_value.first, value);
        }
    } else if(position < root->_value.first)
        root->_left = __remove(root->_left, position, value);
    else if(position > int(root->_value.first + root->_value.second))
        root->_right = __remove(root->_right, position, value);

    root->__update_height();
    root = root->__balance();

    return root;
}


AVL_Tree::AVL_Tree(): _size(0), _root(NULL)
{

}


AVL_Tree::~AVL_Tree()
{
    if(_root != NULL)
        delete _root;
}

bool AVL_Tree::empty()
{
    return _size == 0;
}

template <class T>
bool AVL_Tree::insert(T value)
{
    if(value < _begin || int(value + width) > _end)
        return false;

    if(_root == NULL)
    {
        _root = new Node(value, width);
        _size++;
        return true;
    }
    Node * root_of_subtree = _root->__insert(make_pair(value, width));
    if(root_of_subtree != NULL)
    {
        _root = root_of_subtree;
        _size++;
        return true;
    }
    return false;
}

T AVL_Tree::remove(int position)
{
    if(position < _begin || position > _end)
        return T::invalid();

    T value = T::invalid();
    _root = __remove(_root, position, value);
    return value;
}

unsigned AVL_Tree::size()
{
    return _size;
}

std::pair<int, unsigned> AVL_Tree::root()
{
    if(_root == NULL)
        return AVL_Tree::EMPTY_TREE_ROOT;
    return _root->_value;
}

std::pair<int, unsigned> AVL_Tree::find(int begin, unsigned width)
{
    if(_root != NULL)
        return _root->__find(begin, width);
    return AVL_Tree::EMPTY_TREE_ROOT;
}

void AVL_Tree::print_tree()
{
    cout << "Tree: " << endl;
    if(_root == NULL)
        cout << "NULL" << endl;
    else
        _root->print_node();
}

void AVL_Tree::Node::__update_height()
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
const AVL_Tree::T AVL_Tree::Node::__find(AVL_Tree::T value)
{
    //    static int count;
    //    count++;
    //    cout << "Range_Tree::Node::__find(int value, unsigned width) count = " << count << endl;
    if((value < _value.first && int(value + width) > _value.first) || (value > _value.first && value < int(_value.first + _value.second)))
        return _value;

    if(int(value + width) < _value.first)
    {
        if(_left == NULL)
            return AVL_Tree::EMPTY_TREE_ROOT;
        return _left->__find(value, width);
    }

    if(value > int(_value.first + _value.second))
    {
        if(_right == NULL)
            return AVL_Tree::EMPTY_TREE_ROOT;
        return _right->__find(value, width);
    }

    return AVL_Tree::EMPTY_TREE_ROOT;
}

AVL_Tree::Node *AVL_Tree::Node::__insert(T value)
{
    switch (__compareTo(value)) {
    case AVL_Tree::Node::GREATER_THAN:
        if(_left != NULL)
            _left = _left->__insert(value);
        else
            _left = new Node(value.first, value.second);
        break;
    case AVL_Tree::Node::LESS_THAN:
        if(_right != NULL)
            _right = _right->__insert(value);
        else
            _right = new Node(value.first, value.second);
        break;
    default:
        return NULL;
        break;
    }

    __update_height();
    Node * root = __balance();
    return root;
}

AVL_Tree::Node *AVL_Tree::Node::__max()
{
    if(_right == NULL)
        return this;
    return _right->__max();
}

AVL_Tree::Node *AVL_Tree::Node::__balance()
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

AVL_Tree::Node *AVL_Tree::Node::__RR_rotate()
{
    Node * a = _left;
    _left = a->_right;
    a->_right = this;
    __update_height();
    a->__update_height();
    return a;
}

AVL_Tree::Node *AVL_Tree::Node::__LR_rotate()
{
    _left = _left->__LL_rotate();
    return __RR_rotate();
}

AVL_Tree::Node *AVL_Tree::Node::__RL_rotate()
{
    _right = _right->__RR_rotate();
    return __LL_rotate();
}

AVL_Tree::Node *AVL_Tree::Node::__LL_rotate()
{
    Node * a = _right;
    _right = a->_left;
    a->_left = this;
    __update_height();
    a->__update_height();
    return a;
}

AVL_Tree::Node::Node(int begin, int width): _left(NULL), _right(NULL), _value(std::make_pair(begin, width)), _height(1)
{

}

AVL_Tree::Node::~Node()
{
    if(_left != NULL)
        delete _left;
    if(_right != NULL)
        delete _right;
}


int AVL_Tree::Node::__balance_factor() const
{
    int right_height = 1;
    int left_height = 1;
    if(_left != NULL)
        left_height = _left->_height + 1;
    if(_right != NULL)
        right_height = _right->_height + 1;
    return left_height - right_height;
}

//void AVL_Tree::Node::print_node(int offset)
//{
//    for(int i = 0; i < offset; i++)
//        cout << "    ";
//    cout << "value " << _value.first << " width " << _value.second << " height " << _height << endl;
//    if(_left == NULL)
//    {
//        for(int i = 0; i < offset+1; i++)
//            cout << "    ";
//        cout << "NULL" << endl;
//    }
//    else
//        _left->print_node(offset+1);
//    if(_right == NULL)
//    {
//        for(int i = 0; i < offset+1; i++)
//            cout << "    ";
//        cout << "NULL" << endl;
//    }
//    else
//        _right->print_node(offset+1);
//}
