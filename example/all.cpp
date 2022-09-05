#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    args.addArgument(args.vector("-h", "--help"), "help", "custom help option message");
    args.addArgument(args.vector("-v", "--version"), "version", "help of version option", false, NULL, 0, "Version: 0.0.0");
    args.addArgument("NOTREQUIRED", NULL, "help of positional argument", false);
    args.addArgument("REQUIRED", NULL, "help of required positional argument", true);
    args.addArgument("-b", "store_true", "help of boolean option");
    args.addArgument("-c", "store_false", "help of count option");
    args.addArgument(args.vector("-s", "--simple"), NULL, "help of simple option", true, "argSimple", 1);
    args.addArgument(args.vector("-n", "--number"), NULL, "help of number", true, "ARG1 ARG2", 2, args.vector("foo", "bar"));
    args.addArgument("--infinite", NULL, "help of infinite", false, NULL, '+');
    args.addArgument(args.vector("-m", "--multi"), "append", "help of multi", false, "MULTI", 1, args.vector("0", "1", "2"));
    args.addArgument(args.vector("-N", "--multiAppend"), "append", "help of multi", false, "MULTI", 2, args.vector("0", "1", "2", "3"));
    args.addArgument(args.vector("-e", "--extend"), "extend", "help of extend", false, "EXTEND", 1, args.vector("0", "1", "2", "3"));
    args.addArgument(args.vector("-E", "--extend-number"), "extend", "help of extend", false, "EXTEND", 2, args.vector("0", "1", "2", "3"));
    try {
        args.parseArguments(argc, argv, true);
        std::cout << "-b: " << args["-b"] << std::endl;
        std::cout << "-c: (count) " << args["-c"].count() << std::endl;
        std::cout << "REQUIRED: " << args["REQUIRED"] << std::endl;
        if (args["-s"]) {
            std::cout << "-s: " << args["-s"] << std::endl;
        }
        std::cout << "-n: [0]: " << args["-n"][0] << ", [1]: " << args["-n"][1] << " (" << args["-n"] << ")" <<
                  std::endl;
        if (args["--infinite"]) {
            std::cout << "--infinite: " << args["--infinite"] << std::endl;
        }
        std::cout << "-m: " << args["-m"] << std::endl;
        std::cout << "-N: ";
        for (std::size_t i = 0; i < args["-N"].size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << '(' << args["-N"][i][0] << ", " << args["-N"][i][1] << ')';
        }
        std::cout << std::endl;
        std::cout << "-e: ";
        for (std::size_t i = 0; i < args["-e"].size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << args["-e"][i];
        }
        std::cout << std::endl;
        std::cout << "-E: ";
        for (std::size_t i = 0; i < args["-E"].size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << '(' << args["-E"][i][0] << ", " << args["-E"][i][1] << ')';
        }
        std::cout << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; //END
    }
    return 0;
}