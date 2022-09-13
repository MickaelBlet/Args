#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-a", "--append")).action(
        mblet::Argparsor::APPEND).help("custom append option message").nargs(1);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--append"].size(); ++i) {
        std::cout << args["--append"][i] << std::endl;
    }
    return 0;
}