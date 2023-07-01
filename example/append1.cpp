#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("-a").flag("--append").action(args.APPEND).help("custom append option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    for (std::size_t i = 0; i < args["--append"].size(); ++i) {
        std::cout << args["--append"][i] << std::endl;
    }
    return 0;
}