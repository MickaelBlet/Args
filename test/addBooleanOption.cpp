#include <gtest/gtest.h>

#include "optparsor.hpp"

GTEST_TEST(addBooleanOption, invalid_shortName_and_longName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption(NULL, NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption("", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption(NULL, "");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption("", "");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName and longName arguments");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addBooleanOption, invalid_shortName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption("not -", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not start by '-' character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption("-", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument is '-'");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption("-ab", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument not only one character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    optparsor.addBooleanOption("-a", NULL);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption("-a", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid shortName argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addBooleanOption, invalid_longName) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption(NULL, "not --");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument not start by '--' characters");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption(NULL, "--");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument is '--'");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    optparsor.addBooleanOption(NULL, "--abc");
    EXPECT_THROW({
        try {
            optparsor.addBooleanOption(NULL, "--abc");
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "invalid longName argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addBooleanOption, valid_type) {
    mblet::Optparsor optparsor;
    optparsor.addBooleanOption("-a", "--abc");
    EXPECT_EQ(optparsor["-a"].type, mblet::Optparsor::Option::BOOLEAN_OPTION);
    EXPECT_EQ(optparsor["--abc"].type, mblet::Optparsor::Option::BOOLEAN_OPTION);
}

GTEST_TEST(addBooleanOption, valid_size) {
    mblet::Optparsor optparsor;
    optparsor.addBooleanOption("-a", "--abc");
    EXPECT_EQ(optparsor["-a"].size(), 0);
    EXPECT_EQ(optparsor["--abc"].size(), 0);
}