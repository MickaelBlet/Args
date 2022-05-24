// #include <iostream>

// #include "argparsor.hpp"

// int main(int argc, char* argv[]) {
//     mblet::Argparsor argparsor;
//     // argparsor.throwAtExtra(true);
//     // argparsor.setDescription("example of description");
//     // argparsor.setHelpArgument("", "--help", "custom help message");
//     // argparsor.addBooleanArgument("-b", "--boolean", "boolean option", false);
//     // argparsor.addSimpleArgument("-s", "--simple", "little s options", false, "TESTS", "TUTU");
//     // argparsor.addNumberArgument("-n", "--number", "number option", false, "FOO BAR", 2, "FOO", "BAR");
//     // argparsor.addMultiArgument("-m", "--multi", "multi options", false, "TESTS", 2, "foo", "bar");
//     // argparsor.addInfiniteArgument("-i", "--infinite", "infinite options", false, "", 2, "foo", "bar");
//     argparsor.addPositionalArgument("REQUIRED", "required", true);
//     argparsor.addPositionalArgument("ARGUMENT", "argument", false, "defaultValue");
//     // argparsor.addPositionalArgument("ARG", "arg", false);
//     try {
//         argparsor.parseArguments(argc, argv);
//         // std::cout << "-b: " << argparsor["-b"] << " (count: " << argparsor["-b"].count << ")" << std::endl;
//         // std::cout << "-s: " << argparsor["-s"].get<std::string>() << std::endl;
//         // std::cout << "-n: " << argparsor["-n"] << std::endl;
//         // std::cout << "-m: " << argparsor["-m"] << std::endl;
//         // std::cout << "-i: " << argparsor["--infinite"] << std::endl;
//         // std::cout << "ARG: " << argparsor["ARG"] << std::endl;
//     }
//     catch (const mblet::Argparsor::ParseArgumentException& e) {
//         std::cerr << argparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
//         argparsor.getUsage(std::cerr);
//         throw;
//     }
//     // argparsor.getUsage(std::cerr);
//     return 0;
// }

#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    argparsor.addBooleanArgument("-r", "--required", "help of required", true);
    argparsor.addBooleanArgument("-s", "--simple", "help of simple", false);
    try {
        argparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "-r: " << argparsor["-r"].c_str() << std::endl;
    std::cout << "-s: " << argparsor["-s"].c_str() << std::endl;
    return 0;
}