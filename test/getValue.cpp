#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(get, get_value) {
    mblet::Argparsor argparsor;
    argparsor.addSimpleArgument("-a");
    argparsor.addSimpleArgument("-b");
    argparsor.addSimpleArgument("-c");
    argparsor.addSimpleArgument("-d");
    argparsor.addSimpleArgument("-e");
    argparsor.addSimpleArgument("-f");
    argparsor.addSimpleArgument("-g");
    const char* argv[] = {
        "binaryname",
        "-a", "-42",
        "-b", "042",
        "-c", "0x42",
        "-d", "0b01",
        "-e", "TRUE",
        "-f", "FALSE",
        "-g", "foo"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    argparsor.parseArguments(argc, const_cast<char**>(argv));
    EXPECT_EQ(argparsor["-a"].get<int>(), -42);
    EXPECT_EQ(argparsor["-b"].get<int>(), 042);
    EXPECT_EQ(argparsor["-c"].get<int>(), 0x42);
    EXPECT_EQ(argparsor["-d"].get<int>(), 1);
    EXPECT_EQ(argparsor["-e"].get<bool>(), true);
    EXPECT_EQ(argparsor["-f"].get<bool>(), false);
    EXPECT_EQ(argparsor["-g"].str(), "foo");
}