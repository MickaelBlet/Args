#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.setVersion("multi line\nVersion: 0.0.0");
    args.addArgument("-v").flag("--version").action(args.VERSION).help("custom help version message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << "do nothing" << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}