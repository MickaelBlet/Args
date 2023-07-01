#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("--option").help("custom option message").defaults("default value");
    args.addArgument("--option-number")
        .help("custom option-number message")
        .nargs(2)
        .defaults(args.vector("default1", "default2"));

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
        std::cout << args["--option-number"][0] << "|" << args["--option-number"][1] << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    return 0;
}