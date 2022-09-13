#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-b", "--boolean"), mblet::Argparsor::STORE_TRUE, "custom booblean option message", false);
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