#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(accessDenied, exception) {
    mblet::Argparsor args;
    EXPECT_THROW(
        {
            try {
                args[""];
            }
            catch (const mblet::Argparsor::AccessDeniedException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "");
                throw;
            }
        },
        mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW(
        {
            try {
                args["foo"];
            }
            catch (const mblet::Argparsor::AccessDeniedException& e) {
                EXPECT_STREQ(e.what(), "argument not found");
                EXPECT_STREQ(e.argument(), "foo");
                throw;
            }
        },
        mblet::Argparsor::AccessDeniedException);
}