#include <gtest/gtest.h>

#include "optparsor.h"

GTEST_TEST(addSimpleOption, invalid_shortName_and_longName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption(NULL, NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption(NULL, "");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("", "");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addSimpleOption, invalid_shortName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("not -", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not start by '-' character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("-", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument is '-'");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("-ab", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not only one character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    optparsor.addSimpleOption("-a", NULL);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("-a", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addSimpleOption, invalid_longName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption(NULL, "not --");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument not start by '--' characters");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption(NULL, "--");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument is '--'");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    optparsor.addSimpleOption(NULL, "--abc");
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption(NULL, "--abc");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addSimpleOption, valid_type) {
    mblet::Optparsor optparsor;
    optparsor.addSimpleOption("-a", "--abc");
    EXPECT_EQ(optparsor["-a"].type, mblet::Optparsor::Option::SIMPLE_OPTION);
    EXPECT_EQ(optparsor["--abc"].type, mblet::Optparsor::Option::SIMPLE_OPTION);
}

GTEST_TEST(addSimpleOption, valid_size) {
    mblet::Optparsor optparsor;
    optparsor.addSimpleOption("-a", "--abc");
    EXPECT_EQ(optparsor["-a"].size(), 0);
    EXPECT_EQ(optparsor["--abc"].size(), 0);
    // with default value
    optparsor.addSimpleOption("-b", "--bcd", "help", false, "BCD", "foo");
    EXPECT_EQ(optparsor["-b"].size(), 1);
    EXPECT_EQ(optparsor["--bcd"].size(), 1);
}