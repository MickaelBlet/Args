#include <iostream>

#include "mblet/argparsor.h"

enum eLogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExists*/, const std::string& argument) {
    static const std::pair<std::string, eLogLevel> pairLogLevels[] = {
        std::pair<std::string, eLogLevel>("DEBUG", DEBUG), std::pair<std::string, eLogLevel>("INFO", INFO),
        std::pair<std::string, eLogLevel>("WARNING", WARNING), std::pair<std::string, eLogLevel>("ERROR", ERROR)};
    static const std::map<std::string, eLogLevel> logLevels(
        pairLogLevels, pairLogLevels + sizeof(pairLogLevels) / sizeof(*pairLogLevels));

    logLevel = logLevels.at(argument);
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO;

    mblet::Argparsor args;
    args.setVersion("Version: 0.0.0");
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v").flag("--version").help("help of version option").action(args.VERSION);
    args.addArgument(args.vector("-o", "--option")).help("help of option").nargs(2).metavar("OPT1 OPT2");
    args.addArgument("--log-level")
        .flag("-l")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new mblet::Argparsor::ValidChoise(args.vector("DEBUG", "INFO", "WARNING", "ERROR")))
        .defaults("INFO")
        .dest(logLevel, &argToLogLevel); // fill logLevel by argToLogLevel
    try {
        args.setStrict().setAlternative().setHelpException().setVersionException(); // activate all parse options
        args.parseArguments(argc, argv);
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
    }
    catch (const mblet::Argparsor::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}