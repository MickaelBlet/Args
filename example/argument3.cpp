#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("ARG").help("custom argument message").nargs(3);
    args.parseArguments(argc, argv);
    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additionnal argument(s):" << std::endl;
        for (std::size_t i = 0; i < args.getAdditionalArguments().size(); ++i) {
            std::cout << args.getAdditionalArguments()[i] << std::endl;
        }
    }
    return 0;
}