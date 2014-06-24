#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>
#include <exception>
using std::exception;
using std::numeric_limits;

class InvalidIntervalException: public exception {
    const char * what() const throw(){
        return "Interval size must be at least 1!";
    }
};

class NonOverlappingInterval
{
    int _begin;
    unsigned _size;
    static const NonOverlappingInterval _INVALID;
public:
    NonOverlappingInterval(int begin, unsigned size);
    bool operator==(const NonOverlappingInterval & o) const;
    bool operator<(const NonOverlappingInterval & o) const;
    bool operator>(const NonOverlappingInterval & o) const;

    bool sameAs(const NonOverlappingInterval & o) const;

    int begin() const;
    unsigned size() const;
    int end() const;

    bool valid() const;

    static const NonOverlappingInterval invalid();

};

#endif // INTERVAL_H
