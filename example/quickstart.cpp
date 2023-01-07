#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v")
        .flag("--version")
        .help("help of version option")
        .action(args.VERSION)
        .defaults("Version: 0.0.0");
    args.addArgument("--option").help("help of option");
    args.addArgument("--log-level")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new mblet::Argparsor::ValidChoise(args.vector("DEBUG", "INFO", "WARNING", "ERROR")))
        .defaults("INFO");
    try {
        args.parseArguments(argc, argv, true);
        std::cout << "ARGUMENT: " << args["ARGUMENT"] << '\n';
        if (args["--option"]) {
            std::cout << "--option: " << args["--option"] << '\n';
        }
        std::cout << "--log-level: " << args["--log-level"] << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}