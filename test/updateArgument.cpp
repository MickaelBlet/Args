#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(updateArgument, exception) {
    mblet::Argparsor args;
    EXPECT_THROW(
        {
            try {
                args.updateArgument("--unknown");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "--unknown");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
}

GTEST_TEST(updateArgument, help) {
    mblet::Argparsor args;
    args.updateArgument("-h").help("custom message of help");
    EXPECT_EQ(args["--help"].getHelp(), std::string("custom message of help"));
}

GTEST_TEST(updateArgument, undo_help_and_version) {
    mblet::Argparsor args;
    args.updateArgument("-h").action(args.NONE);
    EXPECT_EQ(args["--help"].getAction(), args.NONE);
    args.addArgument("-v").action(args.VERSION);
    args.updateArgument("-v").action(args.NONE);
    EXPECT_EQ(args["-v"].getAction(), args.NONE);
}