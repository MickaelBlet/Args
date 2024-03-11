#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message").nargs(3);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        for (std::size_t i = 0; i < args["--none"].size(); ++i) {
            std::cout << args["--none"][i] << std::endl;
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
