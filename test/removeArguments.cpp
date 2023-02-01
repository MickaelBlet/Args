#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(removeArguments, exception) {
    mblet::Argparsor args;
    EXPECT_THROW(
        {
            try {
                args.removeArguments(args.vector());
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid empty flag");
                EXPECT_STREQ(e.argument(), "");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.removeArguments(args.vector("--unknown"));
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "--unknown");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    args.removeArguments(args.vector("-h", "--help"));
    EXPECT_EQ(args.argumentExists("-h"), false);
    EXPECT_EQ(args.argumentExists("--help"), false);
}