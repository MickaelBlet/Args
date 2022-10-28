#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    mblet::Argparsor::ValidNumber validNumber; // create a scope IValid
    args.addArgument("--option")
        .help("custom option message")
        .valid(&validNumber, false) // set deletable at false
        // or .valid(new mblet::Argparsor::ValidNumber())
        .required(true);
    try {
        args.parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
        return 0;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }
}