#include <iostream>
#include <cstdio>

#include "optparsor.hpp"

int main(int argc, char* argv[]) {
    mblet::Optparsor optparsor;
    optparsor.throwAtExtra(true);
    optparsor.setDescription("example of description");
    optparsor.setHelpOption("", "--help", "custom help message");
    optparsor.addBooleanOption("-b", "--boolean", "boolean option", false);
    optparsor.addSimpleOption("-s", "--simple", "little s options", false, "TESTS", "TUTU");
    optparsor.addNumberOption("-n", "--number", "number option", false, "FOO BAR", 2, "FOO", "BAR");
    optparsor.addMultiOption("-m", "--multi", "multi options", false, "TESTS", 2, "foo", "bar");
    optparsor.addInfiniteOption("-i", "--infinite", "infinite options", false, "", 2, "foo", "bar");
    optparsor.addPositionalArgument("ARG", "arg", false);
    try {
        optparsor.parseArguments(argc, argv);
        std::cout << "-b: " << optparsor["-b"] << " (count: " << optparsor["-b"].count << ")" << std::endl;
        std::cout << "-s: " << optparsor["-s"].get<std::string>() << std::endl;
        std::cout << "-n: " << optparsor["-n"] << std::endl;
        std::cout << "-m: " << optparsor["-m"] << std::endl;
        std::cout << "-i: " << optparsor["--infinite"] << std::endl;
        std::cout << "ARG: " << optparsor["ARG"] << std::endl;
    }
    catch (const mblet::Optparsor::ParseArgumentRequiredException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        optparsor.getUsage(std::cerr);
    }
    catch (const mblet::Optparsor::ParseArgumentException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        optparsor.getUsage(std::cerr);
    }
    // optparsor.getUsage(std::cerr);
    return 0;
}