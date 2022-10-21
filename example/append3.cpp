#include "mblet/argparsor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-a", "--append")).action(
        mblet::Argparsor::APPEND).help("custom append option message").nargs(3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--append"].size(); ++i) {
        for (std::size_t j = 0; j < args["--append"][i].size() ; ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << args["--append"][i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}