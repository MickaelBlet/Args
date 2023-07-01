#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-b", "--boolean")).action(args.STORE_TRUE).help("custom boolean option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        if (args["--boolean"]) {
            std::cout << "true" << std::endl;
            std::cout << "count: " << args["--boolean"].count() << std::endl;
        }
        else {
            std::cout << "false" << std::endl;
        }
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