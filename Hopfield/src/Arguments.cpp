#include "Arguments.h"
#include "CommandParser.h"

Arguments ArgumentsBuilder::fromCmd(int argc, char* argv[])
{
    Arguments args;
    CommandParser cmdParser(argc, argv);
    args.patternSize = cmdParser.getArgument<size_t>("-p");
    args.inputs = cmdParser.getSplitArguments("-in", ',');
    args.outputDir = cmdParser.getArgument("-out", "");
    return args;
}
