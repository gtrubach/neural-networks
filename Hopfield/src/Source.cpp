#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Hopfield.h"
#include "Utils.h"

char toOutput(const short& state);
void printSet(const size_t& size, const std::vector<short>& vector);
std::vector<short> readSet(const char* fileName);
short getState(const char& c);

int main(int argc, char* argv[])
{
    HopfieldNetwork network(100);

    std::vector<short> pattern1 = readSet("patterns/Pattern-1.txt");

    network.train(pattern1);
    network.train(readSet("patterns/Pattern-2.txt"));
    network.train(readSet("patterns/Pattern-3.txt"));

    generateNoisyPattern(pattern1, 10);

    /*std::vector<short> noisySet = readSet("patterns/Pattern-3_noisy_10.txt");
    printSet(10, noisySet);
    std::vector<short> result = network.recognise(noisySet);
    printSet(10, result);*/

    system("pause");
    return 0;
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
    case '-':
        state = -1;
        break;
    case '*':
        state = 1;
        break;
    default:
        throw new std::exception("Invalid pattern character. Only - and * are allowed.");
    }
    return state;
}

char toOutput(const short& state)
{
    switch (state)
    {
    case -1:
        return '-';
    case 1:
        return '*';
    default:
        throw new std::exception("Invalid state. Only -1 and 1 are allowed.");
    }
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
