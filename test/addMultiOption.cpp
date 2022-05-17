#include <gtest/gtest.h>

#include "optparsor.hpp"

GTEST_TEST(addMultiOption, invalid_shortName_and_longName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addMultiOption(NULL, NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption("", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption(NULL, "");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption("", "");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addMultiOption, invalid_shortName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addMultiOption("not -", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not start by '-' character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption("-", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument is '-'");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption("-ab", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not only one character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    optparsor.addMultiOption("-a", NULL);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption("-a", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addMultiOption, invalid_longName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addMultiOption(NULL, "not --");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument not start by '--' characters");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addMultiOption(NULL, "--");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument is '--'");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    optparsor.addMultiOption(NULL, "--abc");
    EXPECT_THROW({
        try {
            optparsor.addMultiOption(NULL, "--abc");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addMultiOption, valid_type) {
    mblet::Optparsor optparsor;
    optparsor.addMultiOption("-a", "--abc");
    EXPECT_EQ(optparsor["-a"].type, mblet::Optparsor::Option::MULTI_OPTION);
    EXPECT_EQ(optparsor["--abc"].type, mblet::Optparsor::Option::MULTI_OPTION);
}

GTEST_TEST(addMultiOption, valid_size) {
    mblet::Optparsor optparsor;
    optparsor.addMultiOption("-a", "--abc");
    EXPECT_EQ(optparsor["-a"].size(), 0);
    EXPECT_EQ(optparsor["--abc"].size(), 0);
    // with default value
    optparsor.addMultiOption("-b", "--bcd", "help", false, "NUMBER", 2, "foo", "bar");
    EXPECT_EQ(optparsor["-b"].size(), 2);
    EXPECT_EQ(optparsor["--bcd"].size(), 2);
}