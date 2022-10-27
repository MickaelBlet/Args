#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-v", "--version"))
        .action(mblet::Argparsor::VERSION)
        .help("custom help option message")
        .defaults(args.vector("multi line", "Version: 0.0.0"));
    args.parseArguments(argc, argv);
    std::cout << "do nothing" << std::endl;
    return 0;
}