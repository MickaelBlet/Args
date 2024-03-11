#include "blet/args.h"

void test(blet::Args& args, int argc, char* argv[]) {
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
}
