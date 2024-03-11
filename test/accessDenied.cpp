#include <gtest/gtest.h>

#include "blet/args.h"

GTEST_TEST(accessDenied, exception) {
    blet::Args args;
    EXPECT_THROW(
        {
            try {
                args[""];
            }
            catch (const blet::Args::AccessDeniedException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "");
                const blet::Args::ArgumentException* ce = &e;
                EXPECT_STREQ(ce->what(), "argument not found");
                EXPECT_STREQ(ce->argument(), "");
                throw;
            }
        },
        blet::Args::AccessDeniedException);
    EXPECT_THROW(
        {
            try {
                args["foo"];
            }
            catch (const blet::Args::Exception& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                // EXPECT_STREQ(e.argument(), "foo");
                throw;
            }
        },
        blet::Args::Exception);
}
