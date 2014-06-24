#ifndef INTERVAL_H
#define INTERVAL_H

class NonOverlappingInterval
{
    int _begin;
    unsigned _size;
    static const NonOverlappingInterval _INVALID;
public:
    NonOverlappingInterval(int begin, unsigned size);
    bool operator=(const NonOverlappingInterval & o) const;
    bool operator<(const NonOverlappingInterval & o) const;
    bool operator>(const NonOverlappingInterval & o) const;

    int begin() const;
    unsigned size() const;
    int end() const;
    static const NonOverlappingInterval invalid();

};

#endif // INTERVAL_H
