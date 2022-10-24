#include <stdint.h>

#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    using namespace mblet;
    char s = -1;
    std::string b = "";
    std::string c = "";
    std::vector<double> destC;
    std::vector<std::vector<double> > destD;

    Argparsor args(false);
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    args.addArgument("-h").flag("--help").action(args.HELP).help("custom help option message");
    args.addArgument("-v")
        .flag("--version")
        .help("help of version option")
        .action(args.VERSION)
        .defaults("Version: 0.0.0");
    args.addArgument("NOTREQUIRED").help("help of positional argument").defaults("foo");
    args.addArgument("REQUIRED")
        .help("help of required positional argument")
        .valid(new Argparsor::ValidPath(Argparsor::ValidPath::IS_FILE))
        .dest(s)
        .required(true);
    args.addArgument("-b").action(args.STORE_TRUE).help("help of boolean option").dest(b);
    args.addArgument("-c").action(args.STORE_FALSE).help("help of count option").dest(c);
    args.addArgument("-s")
        .flag("--simple")
        .help("help of simple option")
        .required(true)
        .metavar("argSimple")
        .nargs(1)
        .valid(new Argparsor::ValidChoise(args.vector("0", "100", "200")));
    args.addArgument("-n")
        .flag("--number")
        .help("help of number")
        .required(true)
        .metavar("ARG1 ARG2")
        .nargs(2)
        .defaults(args.vector("foo", "bar"));
    args.addArgument("--infinite").help("help of infinite").nargs('+');
    args.addArgument(args.vector("-m", "--multi"))
        .action(args.APPEND)
        .help("help of multi")
        .metavar("MULTI")
        .nargs(1)
        .defaults(args.vector("0", "1", "2"));
    args.addArgument(args.vector("-N", "--multiAppend"))
        .action(args.APPEND)
        .help("help of multi")
        .metavar("MULTI")
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(destD);
    args.addArgument(args.vector("-e", "--extend"))
        .action(args.EXTEND)
        .help("help of extend")
        .metavar("EXTEND")
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(destC);
    args.addArgument(args.vector("-E", "--extend-number"))
        .action(args.EXTEND)
        .help("help of extend")
        .metavar("EXTEND")
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"));
    try {
        args.parseArguments(argc, argv, true);
        std::cout << +s << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        std::cout << destD[0][0] << std::endl;
        std::cout << destD[0][1] << std::endl;
        std::cout << destD[1][0] << std::endl;
        std::cout << destD[1][1] << std::endl;
        std::vector<std::string> rg = args["-E"];

        std::cout << "-b: " << args["-b"] << std::endl;
        std::cout << "-c: (count) " << args["-c"].count() << std::endl;
        std::cout << "REQUIRED: " << args["REQUIRED"] << std::endl;
        std::cout << "NOTREQUIRED: " << args["NOTREQUIRED"] << std::endl;
        if (args["-s"]) {
            std::cout << "-s: " << args["-s"] << std::endl;
        }
        std::cout << "-n: [0]: " << args["-n"][0] << ", [1]: " << args["-n"][1] << " (" << args["-n"] << ")"
                  << std::endl;
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
    catch (const Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1;  // END
    }
    return 0;
}