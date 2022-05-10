#include <gtest/gtest.h>
#include <getopt.h>

#include "optparsor.hpp"

GTEST_TEST(argparsor, test1) {
    const char* argv[] = {
        "binName",
        "extraStart1",
        "-t", "retest=2",
        "yolo2",
        "--", "extraEnd1", "extraEnd2", "-h"
    };
    int argc = sizeof(argv) / sizeof(*argv);

    mblet::Optparsor argparsor;
    argparsor.extraUsage("[ARG1]");
    // argparsor.addArgument("h", "help", 0, "", false);
    argparsor.addOption("t", "test", "help test", false, "", 3, "TEST", "TUTU", "TATA");
    argparsor.addOption("T", "", "help arg test", true, "", 1, "TEST");
    try {
        argparsor.parseArguments(argc, const_cast<char**>(argv));
    }
    catch (mblet::Optparsor::ParseArgumentRequiredException& e) {
        std::cout << e.argument() << std::endl;
    }
    if (argparsor["t"]) {
        std::cout << "-t:     " << argparsor["t"] << argparsor["t"][0] << std::endl;
    }
    if (argparsor["test"]) {
        std::cout << "--test: " << argparsor["test"][0] << std::endl;
        std::cout << "--test: " << argparsor["test"][1] << std::endl;
    }
    // std::cout << "-h: " << argparsor["help"] << std::endl;
    for (std::size_t i = 0; i < argparsor.getExtraArgument().size(); ++i) {
        std::cout << "Extra:     " << argparsor.getExtraArgument()[i] << std::endl;
    }
    argparsor.getUsage();
}