#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(addNumberArgument, invalid_shortName_and_longName) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument(NULL, NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument("", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument(NULL, "");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument("", "");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addNumberArgument, invalid_shortName) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument("not -", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not start by '-' character");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument("-", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument is '-'");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument("-ab", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not only one character");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    argparsor.addNumberArgument("-a", NULL);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument("-a", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument already exist");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addNumberArgument, invalid_longName) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument(NULL, "not --");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument not start by '--' characters");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument(NULL, "--");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument is '--'");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    argparsor.addNumberArgument(NULL, "--abc");
    EXPECT_THROW({
        try {
            argparsor.addNumberArgument(NULL, "--abc");
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument already exist");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addNumberArgument, valid_type) {
    mblet::Argparsor argparsor;
    argparsor.addNumberArgument("-a", "--abc");
    EXPECT_EQ(argparsor["-a"].type, mblet::Argparsor::Argument::NUMBER_OPTION);
    EXPECT_EQ(argparsor["--abc"].type, mblet::Argparsor::Argument::NUMBER_OPTION);
}

GTEST_TEST(addNumberArgument, valid_size) {
    mblet::Argparsor argparsor;
    argparsor.addNumberArgument("-a", "--abc");
    EXPECT_EQ(argparsor["-a"].size(), 0);
    EXPECT_EQ(argparsor["--abc"].size(), 0);
    // with default value
    argparsor.addNumberArgument("-b", "--bcd", "help", false, "NUMBER", 2, "foo", "bar");
    EXPECT_EQ(argparsor["-b"].size(), 2);
    EXPECT_EQ(argparsor["--bcd"].size(), 2);
}