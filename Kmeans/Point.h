#pragma once

#include <vector>

template <typename T>
class Point
{
private:
    size_t size;
    std::vector<T> coordinates;
public:
    Point(std::initializer_list<T>);

    T& operator[](const size_t& index);
};