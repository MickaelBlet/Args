#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message");
    args.parseArguments(argc, argv);
    std::cout << args["--none"] << std::endl;
    return 0;
}