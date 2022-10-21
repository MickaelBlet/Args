#include "mblet/argparsor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("--no-boolean", mblet::Argparsor::STORE_FALSE, "custom not booblean option message", false);
    args.parseArguments(argc, argv);
    if (args["--no-boolean"]) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}