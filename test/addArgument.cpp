#include <gtest/gtest.h>

#include "blet/args.h"

GTEST_TEST(addArgument, argumentException) {
    blet::Args args;
    EXPECT_THROW(
        {
            try {
                args.addArgument("");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "bad name argument");
                EXPECT_STREQ(e.argument(), "");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("foo");
                args.addArgument("foo");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "bad name argument already exist");
                EXPECT_STREQ(e.argument(), "foo");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument(args.vector());
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
                args.addArgument("-1").flag("1");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag not start by '-' character");
                EXPECT_STREQ(e.argument(), "1");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-2").flag("-");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag not be only '-' character");
                EXPECT_STREQ(e.argument(), "-");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-3").flag("--");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag not be only '--' characters");
                EXPECT_STREQ(e.argument(), "--");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-4").flag("-no");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid short flag has not only one character");
                EXPECT_STREQ(e.argument(), "-no");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-n");
                args.addArgument("-n");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag already exist");
                EXPECT_STREQ(e.argument(), "-n");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-m");
                args.addArgument("-a").flag("-m");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag already exist");
                EXPECT_STREQ(e.argument(), "-m");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("A").flag("nop");
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "can't add flag in positionnal argument");
                EXPECT_STREQ(e.argument(), "nop");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("B").action(blet::Args::APPEND);
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "positional argument cannot use with this action or this nargs");
                EXPECT_STREQ(e.argument(), "B");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-b").action(blet::Args::HELP);
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "help action already defined");
                EXPECT_STREQ(e.argument(), "-b");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("--version").action(blet::Args::VERSION);
                args.addArgument("--bad-version").action(blet::Args::VERSION);
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "version action already defined");
                EXPECT_STREQ(e.argument(), "--bad-version");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("--long").nargs(1).defaults(args.vector("1", "2"));
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "--long");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-s").nargs(1).defaults(args.vector("1", "2"));
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "-s");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-t").nargs(2).defaults(args.vector("1"));
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "-t");
                throw;
            }
        },
        blet::Args::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-u").action(blet::Args::APPEND).nargs(2).defaults(args.vector("1"));
            }
            catch (const blet::Args::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "-u");
                throw;
            }
        },
        blet::Args::ArgumentException);
}

GTEST_TEST(addArgument, helpOption) {
    blet::Args args(false);
    args.addArgument(args.vector("-h", "--help", "--help-me-please", "-?")).action(blet::Args::HELP);
    EXPECT_EQ(args["-h"].isExists(), false);
    EXPECT_EQ(args["--help"].isExists(), false);
    EXPECT_EQ(args["--help-me-please"].isExists(), false);
    EXPECT_EQ(args["-?"].isExists(), false);
}

GTEST_TEST(addArgument, versionOption) {
    blet::Args args;
    args.addArgument(args.vector("-v", "--version")).action(blet::Args::VERSION);
    EXPECT_EQ(args["-v"].getAction(), blet::Args::VERSION);
    args.removeArguments("-v");
    args.removeArguments("--version");
    EXPECT_EQ(args.argumentExists("-v"), false);
    EXPECT_EQ(args.argumentExists("--version"), false);
}

GTEST_TEST(addArgument, positionnalArgument) {
    blet::Args args;
    args.addArgument("argument1").defaults("default");
    EXPECT_EQ(args["argument1"].getString(), std::string("default"));
}

GTEST_TEST(addArgument, storeTrueFalse) {
    blet::Args args;
    args.addArgument(args.vector("-b", "--bool", "-c")).action(blet::Args::STORE_TRUE);
    EXPECT_EQ(args["-b"].isExists(), false);
    EXPECT_EQ(args["--bool"].isExists(), false);
    EXPECT_EQ(args["-c"].isExists(), false);
    args.addArgument("--unbool").action(blet::Args::STORE_FALSE);
    EXPECT_EQ(!args["--unbool"].isExists(), true);
}

GTEST_TEST(addArgument, append) {
    blet::Args args;
    args.addArgument("--append").action(blet::Args::APPEND);
    EXPECT_EQ(args["--append"].isExists(), false);
}

GTEST_TEST(addArgument, positionnal) {
    blet::Args args;
    args.addArgument("ARG").action(args.NONE).action(args.INFINITE).nargs(4).nargs(1);
    EXPECT_EQ(args["ARG"].getAction(), args.INFINITE);
}