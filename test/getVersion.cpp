#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(getVersion, empty) {
    mblet::Argparsor argparsor;
    std::ostringstream oss("");
    argparsor.getVersion(oss);
    EXPECT_EQ(oss.str(), "");
}

GTEST_TEST(getVersion, version) {
    mblet::Argparsor argparsor;
    argparsor.addArgument("-v", "version", "help of version", false, NULL, 0, "Version 0.0.0");
    std::ostringstream osss("");
    argparsor.getVersion(osss);
    EXPECT_EQ(osss.str(), "Version 0.0.0\n");
}