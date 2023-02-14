#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.removeArguments(args.vector("-h", "--help"));
    args.addArgument(args.vector("-h", "--help")).action(args.HELP).help("custom help option message");

    try {
        args.setHelpException().parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }

    return 0;
}