#include "mblet/argparsor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-h", "--help"), mblet::Argparsor::HELP, "custom help option message");
    args.parseArguments(argc, argv);
    return 0;
}