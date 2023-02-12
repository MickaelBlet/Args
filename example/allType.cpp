#include <iostream>

#include "mblet/argparsor.h"

struct CustomStruct {
    std::string a;
    double b;
};

int main(int argc, char* argv[]) {
    using namespace mblet;

    struct {
        char notrequired[32];
        const char* required;
        bool b;
        bool c;
        double simple;
        std::vector<std::string> number;
        std::vector<std::string> infinite;
        std::vector<std::string> multi;
        std::vector<std::vector<double> > multiAppend;
        std::vector<std::string> extend;

        std::vector<CustomStruct> extendNumber;

        static void toExtendNumber(std::vector<CustomStruct>& extendNumber, bool /*isExists*/,
                                   const std::vector<std::string>& arguments) {
            for (std::size_t i = 0; i < arguments.size(); i += 2) {
                CustomStruct number = {arguments[i], ::strtod(arguments[i + 1].c_str(), NULL)};
                extendNumber.push_back(number);
            }
        }
    } options;

    ::memcpy(options.notrequired, "default notrequired", sizeof("default notrequired"));
    options.required = "default required";
    options.b = false;
    options.c = false;

    Argparsor args(false); // disable automatic help option
    args.setVersion("Version: 0.0.0");
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    args.addArgument("-h").flag("--help").action(args.HELP).help("custom help option message");
    args.addArgument("-v").flag("--version").help("help of version option").action(args.VERSION);
    args.addArgument("NOTREQUIRED").help("help of positional argument").defaults("foo").dest(options.notrequired);
    args.addArgument("REQUIRED")
        .help("help of required positional argument")
        .valid(new Argparsor::ValidNumber())
        .dest(options.required)
        .required(true);
    args.addArgument("-b").action(args.STORE_TRUE).help("help of boolean option").dest(options.b);
    args.addArgument("-c").action(args.STORE_FALSE).help("help of count option").dest(options.c);
    args.addArgument("-s")
        .flag("--simple")
        .help("help of simple option")
        .required(true)
        .metavar("argSimple")
        .nargs(1)
        .valid(new Argparsor::ValidChoise(args.vector("0", "100", "200")))
        .dest(options.simple);
    args.addArgument("-n")
        .flag("--number")
        .help("help of number")
        .required(true)
        .metavar("ARG1 ARG2")
        .nargs(2)
        .dest(options.number);
    args.addArgument("--infinite").help("help of infinite").nargs('+').dest(options.infinite);
    args.addArgument(args.vector("-m", "--multi"))
        .action(args.APPEND)
        .help("help of multi")
        .metavar("MULTI")
        .nargs(1)
        .defaults(args.vector("0", "1", "2"))
        .dest(options.multi);
    args.addArgument(args.vector("-N", "--multiAppend"))
        .action(args.APPEND)
        .help("help of multi")
        .metavar("MULTI")
        .nargs(2)
        .valid(new Argparsor::ValidNumber())
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(options.multiAppend);
    args.addArgument(args.vector("-e", "--extend"))
        .action(args.EXTEND)
        .help("help of extend")
        .metavar("EXTEND")
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(options.extend);
    args.addArgument(args.vector("-E", "--extend-number"))
        .action(args.EXTEND)
        .help("help of extend")
        .metavar("EXTEND")
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(options.extendNumber, &options.toExtendNumber);
    try {
        args.setAlternative().setHelpException().setVersionException();
        args.parseArguments(argc, argv);

        // ---------------------------------------------------------------------
        // ACCESS BY MAP
        // ---------------------------------------------------------------------

        std::cout << "--- MAP ---" << std::endl;

        if (args["NOTREQUIRED"]) {
            std::cout << "NOTREQUIRED: " << args["NOTREQUIRED"] << std::endl;
        }
        std::cout << "REQUIRED: " << args["REQUIRED"] << std::endl;

        std::cout << "-b: " << args["-b"] << std::endl;
        std::cout << "-c: " << args["-c"] << std::endl;

        if (args["--simple"]) {
            std::cout << "--simple: " << args["--simple"] << std::endl;
        }
        if (args["--number"]) {
            std::cout << "--number: " << args["--number"] << std::endl;
        }
        if (args["--infinite"]) {
            std::cout << "--infinite: " << args["--infinite"] << std::endl;
        }
        if (args["--multi"]) {
            std::cout << "--multi: " << args["--multi"] << std::endl;
        }
        if (args["--multiAppend"]) {
            std::cout << "--multiAppend: " << args["--multiAppend"] << std::endl;
        }
        if (args["--extend"]) {
            std::cout << "--extend: " << args["--extend"] << std::endl;
        }
        if (args["--extend-number"]) {
            std::cout << "--extend-number: " << args["--extend-number"] << std::endl;
        }

        // ---------------------------------------------------------------------
        // ACCESS BY DEST
        // ---------------------------------------------------------------------
        std::cout << "\n--- DEST ---" << std::endl;

        std::cout << "NOTREQUIRED: " << options.notrequired << std::endl;
        std::cout << "REQUIRED: " << options.required << std::endl;
        std::cout << "-b: " << options.b << std::endl;
        std::cout << "-c: " << options.c << std::endl;
        std::cout << "--simple: " << options.simple << std::endl;
        std::cout << "--number: [0]:" << options.number[0] << ", [1]:" << options.number[1] << std::endl;
        std::cout << "--infinite: ";
        for (std::size_t i = 0; i < options.infinite.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << options.infinite[i];
        }
        std::cout << std::endl;

        std::cout << "--multi: ";
        for (std::size_t i = 0; i < options.multi.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << options.multi[i];
        }
        std::cout << std::endl;

        std::cout << "--multiAppend: ";
        for (std::size_t i = 0; i < options.multiAppend.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << options.multiAppend[i][0];
            std::cout << ", " << options.multiAppend[i][1];
        }
        std::cout << std::endl;

        std::cout << "--extend: ";
        for (std::size_t i = 0; i < options.extend.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << options.extend[i];
        }
        std::cout << std::endl;

        std::cout << "--extend-number: ";
        for (std::size_t i = 0; i < options.extendNumber.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << options.extendNumber[i].a;
            std::cout << ", " << options.extendNumber[i].b;
        }
        std::cout << std::endl;
    }
    catch (const Argparsor::HelpException& e) {
        std::cout << args.getUsage() << std::endl;
    }
    catch (const Argparsor::VersionException& e) {
        std::cout << args.getVersion() << std::endl;
    }
    catch (const Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}