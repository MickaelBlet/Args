#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(getVersion, empty) {
    mblet::Argparsor argparsor;
    EXPECT_EQ(argparsor.getVersion(), std::string(""));
}

GTEST_TEST(getVersion, version) {
    mblet::Argparsor argparsor;
    argparsor.setVersion("Version 0.0.0");
    argparsor.addArgument("-v").action(mblet::Argparsor::VERSION);
    EXPECT_EQ(argparsor.getVersion(), std::string("Version 0.0.0"));
}