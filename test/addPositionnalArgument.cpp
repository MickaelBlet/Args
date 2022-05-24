#include <gtest/gtest.h>

#include "optparsor.h"

GTEST_TEST(addPositionnalOption, invalid_name) {
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addPositionalArgument(NULL, NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addPositionalArgument("", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
    EXPECT_THROW({
        try {
            optparsor.addPositionalArgument("-nope", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument start by '-' character");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}

GTEST_TEST(addPositionnalOption, invalid_name_already_exist) {
    mblet::Optparsor optparsor;
    optparsor.addPositionalArgument("arg", NULL);
    EXPECT_THROW({
        try {
            optparsor.addPositionalArgument("arg", NULL);
        }
        catch (const mblet::Optparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument already exist");
            throw;
        }
    }, mblet::Optparsor::ArgumentException);
}