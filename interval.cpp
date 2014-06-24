#include "interval.h"

const NonOverlappingInterval NonOverlappingInterval::INVALID = NonOverlappingInterval(numeric_limits<int>::infinity(), 0);
NonOverlappingInterval::NonOverlappingInterval(int begin, unsigned size)
{
}

bool NonOverlappingInterval::operator=(const NonOverlappingInterval &o) const
{
    return _begin < o._begin && int(_begin + _size) >= o._begin
}

bool NonOverlappingInterval::operator<(const NonOverlappingInterval &o) const
{
    return int(_begin + _size) < o._begin;
}

bool NonOverlappingInterval::operator>(const NonOverlappingInterval &o) const
{
    return _begin > int(o._begin + o._size);
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
    return int(_begin+_size);
}

const NonOverlappingInterval NonOverlappingInterval::invalid()
{
    return _INVALID;
}
