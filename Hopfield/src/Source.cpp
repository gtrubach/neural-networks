#include <iostream>
#include <vector>

#include "Hopfield.h"
#include "Utils.h"

int main(int argc, char* argv[])
{
    HopfieldNetwork network(100);

    std::vector<short> pattern1 = Utils::readSet("patterns/Pattern-3.txt");

    network.train(pattern1);
    network.train(Utils::readSet("patterns/Pattern-2.txt"));
    network.train(Utils::readSet("patterns/Pattern-1.txt"));

    auto noisy1 = Utils::generateNoisyPattern(pattern1, 20);
    Utils::writeSet(std::cout, 10, pattern1);
    Utils::writeSet(std::cout,10, noisy1);
    Utils::writeSet(std::cout, 10, network.recogniseSync(noisy1));
    
    auto res = network.recogniseAsync(noisy1);

    Utils::writeSet(std::cout, 10, res);

    system("pause");
    return 0;
}
