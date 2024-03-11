#include <gtest/gtest.h>

#include "blet/args.h"

GTEST_TEST(getVersion, empty) {
    blet::Args args;
    EXPECT_EQ(args.getVersion(), std::string(""));
}

GTEST_TEST(getVersion, version) {
    blet::Args args;
    args.setVersion("Version 0.0.0");
    args.addArgument("-v").action(blet::Args::VERSION);
    EXPECT_EQ(args.getVersion(), std::string("Version 0.0.0"));
}
