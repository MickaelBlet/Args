#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-b", "--boolean")).action(args.STORE_TRUE).help("custom boolean option message");
    args.parseArguments(argc, argv);
    if (args["--boolean"]) {
        std::cout << "true" << std::endl;
        std::cout << "count: " << args["--boolean"].count() << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}