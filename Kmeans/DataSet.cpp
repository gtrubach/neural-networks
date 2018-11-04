#include "DataSet.h"


void Dataset::validateSet(const std::initializer_list<Data>& data, const size_t& size)
{
    for (Data data : data)
    {
        if (size != data.size())
        {
            throw new std::invalid_argument("Data length in set must be the same.");
        }
    }
}

Dataset::Dataset(const std::initializer_list<Data>& data)
{
    size_t setSize = data.size();
    if (setSize)
    {
        size_t dataSize = data.begin()->size();
        validateSet(data, dataSize);
        this->setSize = setSize;
        this->dataSize = dataSize;
        set.reserve(setSize);
        set.insert(set.end(), data);
    }
}

Dataset::const_iterator Dataset::begin() const
{
    return set.begin();
}

Dataset::const_iterator Dataset::end() const
{
    return set.end();
}

size_t Dataset::getSetSize() const
{
    return setSize;
}

size_t Dataset::getDataSize() const
{
    return dataSize;
}