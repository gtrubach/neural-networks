#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Hopfield.h"

char toOutput(const short& state);

void printVector(const std::vector<short>& vector)
{
    for (auto i : vector)
        std::cout << i << ' ';
    std::cout << '\n';
}

void printSet(const size_t& size, const std::vector<short>& vector)
{
    size_t j = 0;
    for (auto i : vector)
    {
        std::cout << toOutput(i) << ' ';
        if (!(++j % size))
        {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}

std::vector<short> readSet(const char* fileName);

void NN4();

short getState(const char& c);


int main(int argc, char* argv[])
{
    HopfieldNetwork network(100);

    network.train(readSet("patterns/Pattern-1.txt"));
    network.train(readSet("patterns/Pattern-2.txt"));
    network.train(readSet("patterns/Pattern-3.txt"));

    std::vector<short> result = network.recognise(readSet("patterns/Pattern-3_noisy_10.txt"));
    printSet(10, result);

    system("pause");
    return 0;
}

void NN4()
{
    HopfieldNetwork network(4);

    network.train({ -1,1,-1,1 });
    network.train({ 1,-1,1,1 });
    network.train({ -1,1,-1,-1 });

    std::vector<short> recognised = network.recognise({ 1,-1,1,-1 });

    printVector(recognised);
}

std::vector<short> readSet(const char* fileName)
{
    std::ifstream infile(fileName);
    if (!infile)
    {
        throw new std::exception("There are problems with reading file.");
    }
    std::vector<short> trainingSet;
    char c;
    while (infile.get(c))
    {
        if (c != '\n')
        {
            short state = getState(c);
            trainingSet.push_back(state);
        }
    }
    return trainingSet;
}

short getState(const char& c)
{
    short state;
    switch (c)
    {
    case '0':
        state = -1;
        break;
    case '1':
        state = 1;
        break;
    default:
        throw new std::exception("Invalid pattern character. Only 0 and 1 are allowed.");
    }
    return state;
}

char toOutput(const short& state)
{
    switch (state)
    {
    case -1:
        return '0';
    case 1:
        return '1';
    default:
        throw new std::exception("Invalid pattern character. Only 0 and 1 are allowed.");
    }
}
