#include "interval.h"

const NonOverlappingInterval NonOverlappingInterval::_INVALID = NonOverlappingInterval(numeric_limits<int>::max()-1, 1);
NonOverlappingInterval::NonOverlappingInterval(int begin, unsigned size) : _begin(begin), _size(size)
{
    if(size == 0)
        throw new InvalidIntervalException();
}

bool NonOverlappingInterval::operator==(const NonOverlappingInterval &o) const
{
    return (_begin >= o._begin && _begin <= o.end()) ||
           (end() >= o._begin && end() <= o.end());
}

bool NonOverlappingInterval::operator<(const NonOverlappingInterval &o) const
{
    return end() < o._begin;
}

bool NonOverlappingInterval::operator>(const NonOverlappingInterval &o) const
{
    return _begin > o.end();
}

bool NonOverlappingInterval::sameAs(const NonOverlappingInterval &o) const
{
    return _begin == o._begin && _size == o._size;
}

int NonOverlappingInterval::begin() const
{
    return _begin;
}

unsigned NonOverlappingInterval::size() const
{
    return _size;
}

int NonOverlappingInterval::end() const
{
    return int(_begin + _size - 1);
}

bool NonOverlappingInterval::valid() const
{
    return _size > 0;
}

const NonOverlappingInterval NonOverlappingInterval::invalid()
{
    return _INVALID;
}
