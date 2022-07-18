#include "argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("--no-boolean", "store_false", "custom not booblean option message", false);
    args.parseArguments(argc, argv);
    if (args["--no-boolean"]) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}