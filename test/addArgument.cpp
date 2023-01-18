#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(addArgument, argumentException) {
    mblet::Argparsor args;
    EXPECT_THROW(
        {
            try {
                args.addArgument("");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "bad name argument");
                EXPECT_STREQ(e.argument(), "");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("foo");
                args.addArgument("foo");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "bad name argument already exist");
                EXPECT_STREQ(e.argument(), "foo");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument(args.vector());
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
                args.addArgument("-1").flag("1");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag not start by '-' character");
                EXPECT_STREQ(e.argument(), "1");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-2").flag("-");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag not be only '-' character");
                EXPECT_STREQ(e.argument(), "-");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-3").flag("--");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag not be only '--' characters");
                EXPECT_STREQ(e.argument(), "--");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-4").flag("-no");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid short flag has not only one character");
                EXPECT_STREQ(e.argument(), "-no");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-n");
                args.addArgument("-n");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag already exist");
                EXPECT_STREQ(e.argument(), "-n");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-m");
                args.addArgument("-a").flag("-m");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid flag already exist");
                EXPECT_STREQ(e.argument(), "-m");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("A").flag("nop");
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "can't add flag in positionnal argument");
                EXPECT_STREQ(e.argument(), "nop");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("B").action(mblet::Argparsor::APPEND);
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "positional argument cannot use with this action or this nargs");
                EXPECT_STREQ(e.argument(), "B");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-b").action(mblet::Argparsor::HELP);
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "help action already defined");
                EXPECT_STREQ(e.argument(), "-b");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("--version").action(mblet::Argparsor::VERSION);
                args.addArgument("--bad-version").action(mblet::Argparsor::VERSION);
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "version action already defined");
                EXPECT_STREQ(e.argument(), "--bad-version");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("--long").nargs(1).defaults(args.vector("1", "2"));
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "--long");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-s").nargs(1).defaults(args.vector("1", "2"));
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "-s");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-t").nargs(2).defaults(args.vector("1"));
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "-t");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
    EXPECT_THROW(
        {
            try {
                args.addArgument("-u").action(mblet::Argparsor::APPEND).nargs(2).defaults(args.vector("1"));
            }
            catch (const mblet::Argparsor::ArgumentException& e) {
                EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
                EXPECT_STREQ(e.argument(), "-u");
                throw;
            }
        },
        mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addArgument, helpOption) {
    mblet::Argparsor args(false);
    args.addArgument(args.vector("-h", "--help", "--help-me-please", "-?")).action(mblet::Argparsor::HELP);
    EXPECT_FALSE(args["-h"]);
    EXPECT_FALSE(args["--help"]);
    EXPECT_FALSE(args["--help-me-please"]);
    EXPECT_FALSE(args["-?"]);
}

GTEST_TEST(addArgument, versionOption) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-v", "--version"))
        .action(mblet::Argparsor::VERSION)
        .defaults(args.vector("multline", "version: 0.0.0"));
    EXPECT_EQ(args["-v"].getDefault(), "multline\nversion: 0.0.0");
    EXPECT_EQ(args["--version"].getDefault(), "multline\nversion: 0.0.0");
}

GTEST_TEST(addArgument, positionnalArgument) {
    mblet::Argparsor args;
    args.addArgument("argument1").defaults("default");
    EXPECT_EQ(args["argument1"].getString(), "default");
}

GTEST_TEST(addArgument, storeTrueFalse) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-b", "--bool", "-c")).action(mblet::Argparsor::STORE_TRUE);
    EXPECT_FALSE(args["-b"]);
    EXPECT_FALSE(args["--bool"]);
    EXPECT_FALSE(args["-c"]);
    args.addArgument("--unbool").action(mblet::Argparsor::STORE_FALSE);
    EXPECT_FALSE(!args["--unbool"]);
}

GTEST_TEST(addArgument, append) {
    mblet::Argparsor args;
    args.addArgument("--append").action(mblet::Argparsor::APPEND);
    EXPECT_FALSE(args["--append"]);
}

GTEST_TEST(addArgument, positionnal) {
    mblet::Argparsor args;
    args.addArgument("ARG").action(args.NONE).action(args.INFINITE).nargs(4).nargs(1);
    EXPECT_EQ(args["ARG"].getAction(), args.INFINITE);
}