#include "mblet/argparsor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message").nargs(1);
    args.parseArguments(argc, argv);
    std::cout << args["--none"] << std::endl;
    return 0;
}