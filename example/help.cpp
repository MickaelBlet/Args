#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.removeArguments(args.vector("-h", "--help"));
    args.addArgument(args.vector("-h", "--help")).action(args.HELP).help("custom help option message");
    args.parseArguments(argc, argv);
    return 0;
}