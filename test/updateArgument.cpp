#include <gtest/gtest.h>

#include "blet/args.h"

GTEST_TEST(updateArgument, exception) {
    blet::Args args;
    EXPECT_THROW(
        {
            try {
                args.updateArgument("--unknown");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "--unknown");
                throw;
            }
        },
        blet::Args::ArgumentException);
}

GTEST_TEST(updateArgument, help) {
    blet::Args args;
    args.updateArgument("-h").help("custom message of help");
    EXPECT_EQ(args["--help"].getHelp(), std::string("custom message of help"));
}

GTEST_TEST(updateArgument, undo_help_and_version) {
    blet::Args args;
    args.updateArgument("-h").action(args.NONE);
    EXPECT_EQ(args["--help"].getAction(), args.NONE);
    args.addArgument("-v").action(args.VERSION);
    args.updateArgument("-v").action(args.NONE);
    EXPECT_EQ(args["-v"].getAction(), args.NONE);
}