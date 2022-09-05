#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none"), NULL, "custom none option message", false, NULL, 3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--none"].size(); ++i) {
        std::cout << args["--none"][i] << std::endl;
    }
    return 0;
}