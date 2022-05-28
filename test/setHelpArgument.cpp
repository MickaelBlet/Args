#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(setHelpArgument, disable) {
    mblet::Argparsor argparsor;
    argparsor.addBooleanArgument("-b");
    argparsor.setHelpArgument();
    const char* argv[] = {
        "binaryname",
        "-h"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    EXPECT_THROW({
        try {
            argparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Argparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "h");
            EXPECT_STREQ(e.what(), "invalid option");
            throw;
        }
    }, mblet::Argparsor::ParseArgumentException);
}

GTEST_TEST(setHelpArgument, replace) {
    mblet::Argparsor argparsor;
    argparsor.addBooleanArgument("-b");
    argparsor.setHelpArgument("-z");
    const char* argv[] = {
        "binaryname",
        "-z"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    EXPECT_DEATH(argparsor.parseArguments(argc, const_cast<char**>(argv)), "");
}