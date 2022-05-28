#include <gtest/gtest.h>

#include "argparsor.h"

GTEST_TEST(addPositionnalOption, invalid_name) {
    mblet::Argparsor argparsor;
    EXPECT_THROW({
        try {
            argparsor.addPositionalArgument(NULL, NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addPositionalArgument("", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
    EXPECT_THROW({
        try {
            argparsor.addPositionalArgument("-nope", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument start by '-' character");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}

GTEST_TEST(addPositionnalOption, invalid_name_already_exist) {
    mblet::Argparsor argparsor;
    argparsor.addPositionalArgument("arg", "help", false, "default");
    EXPECT_THROW({
        try {
            argparsor.addPositionalArgument("arg", NULL);
        }
        catch (const mblet::Argparsor::ArgumentException& e) {
            EXPECT_STREQ(e.what(), "bad name argument already exist");
            throw;
        }
    }, mblet::Argparsor::ArgumentException);
}