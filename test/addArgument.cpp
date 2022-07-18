#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(addArgument, argumentException) {
    mblet::Argparsor args;
    EXPECT_THROW({
        try {
            args.addArgument("");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument");
            EXPECT_STREQ(e.argument(), "");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("foo");
            args.addArgument("foo");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument already exist");
            EXPECT_STREQ(e.argument(), "foo");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument(args.vector());
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid empty flag");
            EXPECT_STREQ(e.argument(), "");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument(args.vector("-1", "1", "2"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid flag not start by '-' character");
            EXPECT_STREQ(e.argument(), "1");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument(args.vector("-1", "-"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid flag not be only '-' character");
            EXPECT_STREQ(e.argument(), "-");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument(args.vector("-v", "--"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid flag not be only '--' characters");
            EXPECT_STREQ(e.argument(), "--");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument(args.vector("-a", "-no"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid short flag has not only one character");
            EXPECT_STREQ(e.argument(), "-no");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("-n");
            args.addArgument(args.vector("-a", "-n"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid flag already exist");
            EXPECT_STREQ(e.argument(), "-n");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("--long", NULL, "", false, "", 1, args.vector("1", "2"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "--long");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("-s", NULL, "", false, "", 1, args.vector("1", "2"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "-s");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("--long", NULL, "", false, "", 2, args.vector("1"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "--long");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("-s", NULL, "", false, "", 2, args.vector("1"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "-s");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("--long", "append", "", false, "", 2, args.vector("1"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "--long");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("-s", "append", "", false, "", 2, args.vector("1"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "-s");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("--long", "store_true", "", false, "", 1, args.vector("1"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "--long");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            args.addArgument("-s", "store_true", "", false, "", 1, args.vector("1"));
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid number of argument with number of default argument");
            EXPECT_STREQ(e.argument(), "-s");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addArgument, helpOption) {
    mblet::Argparsor args;
    args.addArgument("--bool", "store_true", "help", false, "", 0);
    EXPECT_EQ(args["--bool"], false);
    args.addArgument(args.vector("-g", "--gelp", "--gelp-me-please", "-!"), "help", "help message", false);
    EXPECT_EQ(args["-g"], false);
    EXPECT_EQ(args["--gelp"], false);
    EXPECT_EQ(args["--gelp-me-please"], false);
    EXPECT_EQ(args["-!"], false);
    args.addArgument(args.vector("-h", "--help", "--help-me-please", "-?"), "help", "help message", false);
    EXPECT_EQ(args["-h"], false);
    EXPECT_EQ(args["--help"], false);
    EXPECT_EQ(args["--help-me-please"], false);
    EXPECT_EQ(args["-?"], false);
    // check erase last help argument
    EXPECT_THROW({
        try {
            args["-g"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "-g");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["--gelp"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "--gelp");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["--gelp-me-please"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "--gelp-me-please");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["-!"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "-!");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    // disable help
    args.addArgument(args.vector(), "help");
    EXPECT_THROW({
        try {
            args["-h"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "-h");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["--help"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "--help");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["--help-me-please"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "--help-me-please");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["-?"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "-?");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
}

GTEST_TEST(addArgument, versionOption) {
    mblet::Argparsor args;
    args.addArgument("--bool", "store_true", "help", false, "", 0);
    EXPECT_EQ(args["--bool"], false);
    args.addArgument(args.vector("-w", "--wersion"), "version", "help message", false, NULL, 0, args.vector("multline", "version: 0.0.0"));
    EXPECT_EQ(args["-w"].getDefault(), "multline\nversion: 0.0.0");
    EXPECT_EQ(args["--wersion"].getDefault(), "multline\nversion: 0.0.0");
    args.addArgument(args.vector("-v", "--version"), "version", "help message", false, NULL, 0, args.vector("multline", "version: 0.0.0"));
    EXPECT_EQ(args["-v"].getDefault(), "multline\nversion: 0.0.0");
    EXPECT_EQ(args["--version"].getDefault(), "multline\nversion: 0.0.0");
    // check erase last help argument
    EXPECT_THROW({
        try {
            args["-w"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "-w");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["--wersion"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "--wersion");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    // disable version
    args.addArgument(args.vector(), "version");
    EXPECT_THROW({
        try {
            args["-v"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "-v");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
    EXPECT_THROW({
        try {
            args["--version"];
        }
        catch (const mblet::Argparsor::AccessDeniedException &e) {
            EXPECT_STREQ(e.what(), "argument not found");
            EXPECT_STREQ(e.argument(), "--version");
            throw;
        }
    }, mblet::Argparsor::AccessDeniedException);
}

GTEST_TEST(addArgument, positionnalArgument) {
    mblet::Argparsor args;
    args.addArgument("argument1", "default", "help", false, "", 0);
    args.addArgument("argument2", NULL, "help", false, "", 1, "default");
    EXPECT_EQ(args["argument1"].str(), "default");
    EXPECT_EQ(args["argument2"].str(), "default");
}

GTEST_TEST(addArgument, storeTrueFalse) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-b", "--bool", "-c"), "store_true", "help", false, "", 0);
    EXPECT_EQ(args["-b"], false);
    EXPECT_EQ(args["--bool"], false);
    EXPECT_EQ(args["-c"], false);
    args.addArgument("--unbool", "store_false", "help", false, "", 0);
    EXPECT_EQ(args["--unbool"], true);
}

GTEST_TEST(addArgument, append) {
    mblet::Argparsor args;
    args.addArgument("--append", "append", "help", false, "", 0);
    EXPECT_EQ(args["--append"], false);
}