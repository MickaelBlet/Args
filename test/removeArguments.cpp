#include <gtest/gtest.h>

#include "blet/args.h"

GTEST_TEST(removeArguments, exception) {
    blet::Args args;
    EXPECT_THROW(
        {
            try {
                args.removeArguments(args.vector());
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid empty flag");
                EXPECT_STREQ(e.argument(), "");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.removeArguments(args.vector("--unknown"));
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "--unknown");
                throw;
            }
        },
        blet::Args::ArgumentException);
    args.removeArguments(args.vector("-h", "--help"));
    EXPECT_EQ(args.argumentExists("-h"), false);
    EXPECT_EQ(args.argumentExists("--help"), false);
}
