#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("--option").help("custom option message").defaults("default value");
    args.addArgument("--option-number")
        .help("custom option-number message")
        .nargs(2)
        .defaults(args.vector("default1", "default2"));
    args.parseArguments(argc, argv);
    std::cout << args["--option"] << std::endl;
    std::cout << args["--option-number"][0] << "|" << args["--option-number"][1] << std::endl;
    return 0;
}