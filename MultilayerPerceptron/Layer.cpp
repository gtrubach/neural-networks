#include "Layer.h"

using vector = std::vector<double>;

Layer::Layer(const LayerType& type, const size_t& size)
    : type(type), size(size), neurons(size), thresholds(size)
{
    if (size <= 0)
    {
        throw new std::invalid_argument("Size must be greater that 0.");
    }
}

std::vector<double> Layer::getNeurons() const
{
    return neurons;
}

size_t Layer::getSize() const
{
    return size;
}

LayerType Layer::getType() const
{
    return type;
}