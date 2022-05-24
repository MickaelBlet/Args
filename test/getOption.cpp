#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(getOption, not_found) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.getOption("unknown");
        }
        catch (const mblet::Argparsor::AccessDeniedException& e) {
            EXPECT_STREQ(e.argument(), "unknown");
            EXPECT_STREQ(e.what(), "option not found");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}