#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(addSimpleArgument, invalid_shortName_and_longName) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument(NULL, NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument("", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument(NULL, "");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument("", "");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addSimpleArgument, invalid_shortName) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument("not -", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not start by '-' character");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument("-", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument is '-'");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument("-ab", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not only one character");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    argparsor.addSimpleArgument("-a", NULL);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument("-a", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument already exist");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addSimpleArgument, invalid_longName) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument(NULL, "not --");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument not start by '--' characters");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument(NULL, "--");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument is '--'");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    argparsor.addSimpleArgument(NULL, "--abc");
    EXPECT_THROW({
        try {
            argparsor.addSimpleArgument(NULL, "--abc");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument already exist");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addSimpleArgument, valid_type) {
    mblet::Argparsor argparsor;
    argparsor.addSimpleArgument("-a", "--abc");
    EXPECT_EQ(argparsor["-a"].type, mblet::Argparsor::Argument::SIMPLE_OPTION);
    EXPECT_EQ(argparsor["--abc"].type, mblet::Argparsor::Argument::SIMPLE_OPTION);
}

GTEST_TEST(addSimpleArgument, valid_size) {
    mblet::Argparsor argparsor;
    argparsor.addSimpleArgument("-a", "--abc");
    EXPECT_EQ(argparsor["-a"].size(), 0);
    EXPECT_EQ(argparsor["--abc"].size(), 0);
    // with default value
    argparsor.addSimpleArgument("-b", "--bcd", "help", false, "BCD", "foo");
    EXPECT_EQ(argparsor["-b"].size(), 1);
    EXPECT_EQ(argparsor["--bcd"].size(), 1);
}