#include <iostream>

#include "optparsor.hpp"

int main(int argc, char* argv[]) {
    mblet::Optparsor optparsor;
    optparsor.addOption("-t", "--test", "test options", false, "TITI TOTO TUTU", 3, "TESTS", "TUTU", "TATA");
    optparsor.addOption("-s", "", "little s options", false, "TESTS", 1, "TUTU");
    optparsor.addArgument("PLOUF", "plouf arg", true);
    try {
        optparsor.parseArguments(argc, argv);
        for (std::size_t i = 0 ; i < optparsor["-t"].size() ; ++i) {
            std::cout << "-t" << '[' << i << ']' << ": " << optparsor["-t"][i].get<double>() << std::endl;
        }
        for (std::size_t i = 0 ; i < optparsor["-s"].size() ; ++i) {
            std::cout << "-s" << '[' << i << ']' << ": " << optparsor["-s"][i] << std::endl;
        }
        if (optparsor["PLOUF"]) {
            std::cout << "PLOUF" << ": " << optparsor["PLOUF"] << std::endl;
        }
    }
    catch (const mblet::Optparsor::ParseArgumentRequiredException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        optparsor.getUsage(std::cerr);
    }
    catch (const mblet::Optparsor::ParseArgumentException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        optparsor.getUsage(std::cerr);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    optparsor.getUsage(std::cerr);
    return 0;
}