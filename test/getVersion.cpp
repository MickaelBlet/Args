#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(getVersion, empty) {
    mblet::Argparsor argparsor;
    EXPECT_EQ(argparsor.getVersion(), "");
}

GTEST_TEST(getVersion, version) {
    mblet::Argparsor argparsor;
    argparsor.addArgument("-v").action(mblet::Argparsor::VERSION).defaults("Version 0.0.0");
    EXPECT_EQ(argparsor.getVersion(), "Version 0.0.0\n");
}