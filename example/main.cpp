#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    argparsor.setDescription("custom description message");
    argparsor.setHelpArgument("-h", "--help", "custom help option message");
    argparsor.addPositionalArgument("REQUIRED", "help of required positional argument", true);
    argparsor.addBooleanArgument("-b", NULL, "help of boolean option", false);
    argparsor.addBooleanArgument("-c", NULL, "help of count option", false);
    argparsor.addSimpleArgument("-s", "--simple", "help of simple option", false, "argSimple", NULL);
    argparsor.addNumberArgument("-n", "--number", "help of number", false, "ARG1 ARG2", 2, "foo", "bar");
    argparsor.addInfiniteArgument(NULL, "--infinite", "help of infinite", false);
    argparsor.addMultiArgument("-m", "--multi", "help of multi", false, "MULTI", 3, "0", "1", "2");
    try {
        argparsor.parseArguments(argc, argv);
        std::cout << "-b: " << argparsor["-b"] << std::endl;
        std::cout << "-c: " << argparsor["-c"].count << std::endl;
        std::cout << "REQUIRED: " << argparsor["REQUIRED"].get<int>() << " (" << argparsor["REQUIRED"].str() << ")" <<
                  std::endl;
        if (argparsor["-s"]) {
            std::cout << "-s: " << argparsor["-s"] << std::endl;
        }
        std::cout << "-n: [0]: " << argparsor["-n"][0] << ", [1]: " << argparsor["-n"][1].get<double>() << " (" <<
                  argparsor["-n"] << ")" << std::endl;
        if (argparsor["--infinite"]) {
            std::cout << "--infinite: " << argparsor["--infinite"] << std::endl;
        }
        std::cout << "-m: " << argparsor["-m"] << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; //END
    }
    return 0;
}