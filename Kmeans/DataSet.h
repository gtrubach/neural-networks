#pragma once

#include <vector>

class Dataset
{
public:
    using Data = std::vector<double>;
private:
    size_t setSize;
    size_t dataSize;
    std::vector<Data> set;

    static void validateSet(const std::initializer_list<Data>& data, const size_t& size);
public:
    using const_iterator = std::vector<Data>::const_iterator;

    Dataset(const std::initializer_list<Data>& data);

    const_iterator begin() const;
    const_iterator end() const;

    size_t getSetSize() const;
    size_t getDataSize() const;
};