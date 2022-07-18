#include "argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none"), NULL, "custom none option message", false, NULL, 1);
    args.parseArguments(argc, argv);
    std::cout << args["--none"] << std::endl;
    return 0;
}