#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char *argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-e", "--extend"))
        .action(mblet::Argparsor::EXTEND)
        .help("custom extend option message")
        .nargs(3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--extend"].size(); ++i) {
        for (std::size_t j = 0; j < args["--extend"][i].size(); ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << args["--extend"][i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}