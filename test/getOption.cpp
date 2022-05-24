#include <gtest/gtest.h>

#include "optparsor.h"

GTEST_TEST(getOption, not_found) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.getOption("unknown");
        }
        catch (const mblet::Optparsor::AccessDeniedException& e) {
            EXPECT_STREQ(e.argument(), "unknown");
            EXPECT_STREQ(e.what(), "option not found");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}