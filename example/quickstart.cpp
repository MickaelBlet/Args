#include <iostream>

#include "blet/args.h"

enum eLogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExists*/, const std::string& argument) {
    if (argument == "DEBUG") {
        logLevel = DEBUG;
    }
    else if (argument == "INFO") {
        logLevel = INFO;
    }
    else if (argument == "WARNING") {
        logLevel = WARNING;
    }
    else if (argument == "ERROR") {
        logLevel = ERROR;
    }
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO;

    blet::Args args;
    args.setVersion("Version: 0.0.0");
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v").flag("--version").help("help of version option").action(args.VERSION);
    args.addArgument(args.vector("-o", "--option")).help("help of option").nargs(2).metavar("OPT1 OPT2");
    args.addArgument("--log-level")
        .flag("-l")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new blet::Args::ValidChoise(args.vector("DEBUG", "INFO", "WARNING", "ERROR")))
        .defaults("INFO")
        .dest(logLevel, &argToLogLevel); // fill logLevel by argToLogLevel

    try {
        args.setStrict()           // except with additional argument
            .setAlternative()      // accept simple '-' with a long flag
            .setHelpException()    // except when help flag is called
            .setVersionException() // except when version flag is called
            .parseArguments(argc, argv);
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    std::cout << "ARGUMENT: " << args["ARGUMENT"] << '\n';
    // check if option is exists
    if (args["--option"]) {
        std::cout << "--option: " << args["--option"][0] << ", " << args["--option"][1] << '\n';
    }
    std::cout << "--log-level: ";
    switch (logLevel) {
        case DEBUG:
            std::cout << "DEBUG";
            break;
        case INFO:
            std::cout << "INFO";
            break;
        case WARNING:
            std::cout << "WARNING";
            break;
        case ERROR:
            std::cout << "ERROR";
            break;
    }
    std::cout << std::endl;

    return 0;
}
