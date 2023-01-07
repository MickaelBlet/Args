#include <iostream>

#include "mblet/argparsor.h"
#include "test/already_include.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("ARG").help("custom argument message");
    try {
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
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test(args, argc, argv);
    return 0;
}