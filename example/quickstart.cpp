#include <iostream>

#include "blet/args.h"

enum eLogLevel {
    EMERG_LEVEL = 0,
    ALERT_LEVEL,
    CRITICAL_LEVEL,
    ERROR_LEVEL,
    WARNING_LEVEL,
    NOTICE_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExists*/, const std::string& argument) {
    if (argument == "EMERG" || argument == "0") {
        logLevel = EMERG_LEVEL;
    }
    else if (argument == "ALERT" || argument == "1") {
        logLevel = ALERT_LEVEL;
    }
    else if (argument == "CRITICAL" || argument == "2") {
        logLevel = CRITICAL_LEVEL;
    }
    else if (argument == "ERROR" || argument == "3") {
        logLevel = ERROR_LEVEL;
    }
    else if (argument == "WARNING" || argument == "4") {
        logLevel = WARNING_LEVEL;
    }
    else if (argument == "NOTICE" || argument == "5") {
        logLevel = NOTICE_LEVEL;
    }
    else if (argument == "INFO" || argument == "6") {
        logLevel = INFO_LEVEL;
    }
    else if (argument == "DEBUG" || argument == "7") {
        logLevel = DEBUG_LEVEL;
    }
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO_LEVEL;

    blet::Args args;
    // set message printed at version action option
    args.setVersion("Version: 0.0.0");
    // add required positional ARGUMENT
    args.addArgument("ARGUMENT").help("help of positional argument").required();
    // add version option (-v, --version)
    args.addArgument("-v").flag("--version").help("print version").action(args.VERSION);
    // add multiargument option (-o, --option)
    args.addArgument(args.vector("-o", "--option")).help("help of option").nargs(2).metavar("OPT1 OPT2");
    // add choise option (-l, --log-level) with "dest" function
    args.addArgument("--log-level")
        .flag("-l")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new blet::Args::ValidChoise(args.vector("0", "1", "2", "3", "4", "5", "6", "7", "EMERG", "ALERT",
                                                       "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG")))
        .defaults("INFO")
        .dest(logLevel, &argToLogLevel); // fill logLevel using argToLogLevel

    try {
        args.setStrict()                 // except with additional argument
            .setAlternative()            // accept simple '-' with a long flag
            .setAbbreviate()             // accept abbreviated long options (e.g., --ver for --version)
            .setHelpException()          // except when help flag is called
            .setVersionException()       // except when version flag is called
            .parseArguments(argc, argv); // add help option automatically
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
    // check if option exists
    if (args["--option"]) {
        std::cout << "--option: " << args["--option"][0] << ", " << args["--option"][1] << '\n';
    }
    std::cout << "--log-level: ";
    switch (logLevel) {
        case EMERG_LEVEL:
            std::cout << "EMERG";
            break;
        case ALERT_LEVEL:
            std::cout << "ALERT";
            break;
        case CRITICAL_LEVEL:
            std::cout << "CRITICAL";
            break;
        case ERROR_LEVEL:
            std::cout << "ERROR";
            break;
        case WARNING_LEVEL:
            std::cout << "WARNING";
            break;
        case NOTICE_LEVEL:
            std::cout << "NOTICE";
            break;
        case INFO_LEVEL:
            std::cout << "INFO";
            break;
        case DEBUG_LEVEL:
            std::cout << "DEBUG";
            break;
    }
    std::cout << std::endl;

    return 0;
}
