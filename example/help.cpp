#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args(false); // disable automatic help option
    args.addArgument(args.vector("-h", "--help")).action(args.HELP).help("custom help option message");
    args.parseArguments(argc, argv);
    return 0;
}