#include <iostream>
#include <fstream>
#include <vector>
#include "Hopfield.h"
#include "Arguments.h"
#include "Utils.h"

int main(int argc, char* argv[])
{
    Arguments args = ArgumentsBuilder::fromCmd(argc, argv);

    size_t neurons = args.patternSize * args.patternSize;
    HopfieldNetwork network(neurons);
    std::cout << "Created Hopfield network with " << neurons << " neurons\n";
    std::vector<std::vector<short>> patterns;
    for (auto patternPath : args.inputs)
    {
        std::cout << "Reading pattern from '" << patternPath << "'\n";
        patterns.push_back(Utils::readSet(patternPath));
    }
    for (auto pattern : patterns)
    {
        std::cout << "Training network on pattern\n";
        Utils::writeSet(std::cout, args.patternSize, pattern);
        network.train(pattern);
    }
    auto noisePercents = { 10,20,30,35,40,45,50,60,70,80,90,100 };
    size_t patternsCount = args.inputs.size();
    for (size_t i = 0; i < patternsCount; i++)
    {
        size_t patternNumber = i + 1;
        auto resultPath = StringUtils::format("Pattern-{0}-result.txt", patternNumber);
        std::ofstream out(resultPath);
        if (!out.is_open())
        {
            std::cout << "There are problems with output file\n";
            return 1;
        }
        auto pattern = patterns[i];
        out << "Original pattern\n";
        Utils::writeSet(out, 10, pattern);
        for (auto noisePercent : noisePercents)
        {
            std::cout << "Recognising pattern " << patternNumber << " with "
                << noisePercent << "% noise\n";
            for (size_t j = 0; j < 10; j++)
            {
                auto noisy = Utils::generateNoisyPattern(pattern, noisePercent);
                out << "Pattern with " << noisePercent << "% noise\n";
                Utils::writeSet(out, args.patternSize, noisy);
                out << "Synchronous recognition result\n";
                Utils::writeSet(out, args.patternSize, network.recogniseSync(noisy));
                out << "Asynchronous recognition result\n";
                Utils::writeSet(out, args.patternSize, network.recogniseAsync(noisy));
            }
        }
        out.close();
        std::cout << "Check " << resultPath << " for results\n";
    }
    system("pause");
    return 0;
}
