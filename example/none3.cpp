#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message").nargs(3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--none"].size(); ++i) {
        std::cout << args["--none"][i] << std::endl;
    }
    return 0;
}