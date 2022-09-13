#include "mblet/argparsor.h"
#include <stdint.h>

int main(int argc, char* argv[]) {
    using namespace mblet;
    char s = -1;
    std::string b = "";
    std::string c = "";
    std::vector<std::vector<double> > destD;

    Argparsor args(false);
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    args.addArgument("-h").flag("--help").action(args.HELP).help("custom help option message");
    args.addArgument("-v").flag("--version").help("help of version option")
    .action(args.VERSION).defaults("Version: 0.0.0");
    args.addArgument("NOTREQUIRED").help("help of positional argument").defaults("foo");
    args.addArgument("REQUIRED").help("help of required positional argument").valid(new Argparsor::ValidPath())
    .dest(s).required(true);
    args.addArgument("-b", args.STORE_TRUE, "help of boolean option").dest(b);
    args.addArgument("-c", args.STORE_FALSE, "help of count option").dest(c);
    args.addArgument("-s").flag("--simple").help("help of simple option").required(true).metavar("argSimple")
    .nargs(1).valid(new Argparsor::ValidChoise(args.vector("0", "100", "200")));
    args.addArgument("-n").flag("--number").help("help of number").required(true).metavar("ARG1 ARG2").nargs(2)
    .defaults(args.vector("foo", "bar"));
    args.addArgument("--infinite").help("help of infinite").nargs('+');
    args.addArgument(args.vector("-m", "--multi"), args.APPEND, "help of multi", false, "MULTI", 1,
                     args.vector("0", "1", "2"));
    args.addArgument(args.vector("-N", "--multiAppend"), args.APPEND, "help of multi", false, "MULTI", 2,
                     args.vector("0", "1", "2", "3"), NULL, destD);
    args.addArgument(args.vector("-e", "--extend"), args.EXTEND, "help of extend", false, "EXTEND", 1,
                     args.vector("0", "1", "2", "3"));
    args.addArgument(args.vector("-E", "--extend-number"), args.EXTEND, "help of extend", false, "EXTEND", 2,
                     args.vector("0", "1", "2", "3"));
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
    catch (const Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; //END
    }
    return 0;
}