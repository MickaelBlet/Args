#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-i", "--infinite"))
        .action(mblet::Argparsor::INFINITE)
        .help("custom infinite option message")
        .nargs(1);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--infinite"].size(); ++i) {
        std::cout << args["--infinite"][i] << std::endl;
    }
    return 0;
}