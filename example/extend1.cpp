#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-e", "--extend"), "extend", "custom extend option message", false, NULL, 1);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--extend"].size(); ++i) {
        std::cout << args["--extend"][i] << std::endl;
    }
    return 0;
}