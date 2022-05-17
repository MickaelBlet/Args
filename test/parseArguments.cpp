#include <gtest/gtest.h>

#include "optparsor.hpp"

GTEST_TEST(parseArguments, multi_short_invalid_option) {
    const char* argv[] = {
        "binaryname",
        "-ab"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "a");
            EXPECT_STREQ(e.what(), "invalid option");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, multi_short_not_one_argument_option) {
    const char* argv[] = {
        "binaryname",
        "-ab"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    optparsor.addSimpleOption("-a", NULL);
    EXPECT_THROW({
        try {
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "a");
            EXPECT_STREQ(e.what(), "only last option can be use a parameter");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, short_invalid_option) {
    const char* argv[] = {
        "binaryname",
        "-a"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "a");
            EXPECT_STREQ(e.what(), "invalid option");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, short_number_option_with_arg) {
    const char* argv[] = {
        "binaryname",
        "-a=foo"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addNumberOption("-a", NULL, NULL, true, NULL, 0);
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "a");
            EXPECT_STREQ(e.what(), "option cannot use with only 1 argument");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, short_option_bad_narg) {
    const char* argv[] = {
        "binaryname",
        "-a",
        "--"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption("-a", NULL);
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "a");
            EXPECT_STREQ(e.what(), "bad number of argument");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, long_invalid_option) {
    const char* argv[] = {
        "binaryname",
        "--invalid"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "invalid");
            EXPECT_STREQ(e.what(), "invalid option");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, long_number_option_with_arg) {
    const char* argv[] = {
        "binaryname",
        "--foo=bar"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addNumberOption(NULL, "--foo", NULL, true, NULL, 0);
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "foo");
            EXPECT_STREQ(e.what(), "option cannot use with only 1 argument");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, long_option_bad_narg) {
    const char* argv[] = {
        "binaryname",
        "--foo",
        "--"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.addSimpleOption(NULL, "--foo");
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "foo");
            EXPECT_STREQ(e.what(), "bad number of argument");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

GTEST_TEST(parseArguments, positionnal_invalid_extra_option) {
    const char* argv[] = {
        "binaryname",
        "arg"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_THROW({
        try {
            optparsor.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Optparsor::ParseArgumentException& e) {
            EXPECT_STREQ(e.argument(), "arg");
            EXPECT_STREQ(e.what(), "invalid extra argument");
            throw;
        }
    }, mblet::Optparsor::ParseArgumentException);
}

// GTEST_TEST(parseArguments, long_number_option_with_arg) {
//     const char* argv[] = {
//         "binaryname",
//         "--foo=bar"
//     };
//     const int argc = sizeof(argv) / sizeof(*argv);
//     mblet::Optparsor optparsor;
//     EXPECT_THROW({
//         try {
//             optparsor.addNumberOption(NULL, "--foo", NULL, true, NULL, 0);
//             optparsor.parseArguments(argc, const_cast<char**>(argv));
//         }
//         catch (const mblet::Optparsor::ParseArgumentException& e) {
//             EXPECT_STREQ(e.argument(), "foo");
//             EXPECT_STREQ(e.what(), "option cannot use with only 1 argument");
//             throw;
//         }
//     }, mblet::Optparsor::ParseArgumentException);
// }

// GTEST_TEST(parseArguments, long_option_bad_narg) {
//     const char* argv[] = {
//         "binaryname",
//         "--foo",
//         "--"
//     };
//     const int argc = sizeof(argv) / sizeof(*argv);
//     mblet::Optparsor optparsor;
//     EXPECT_THROW({
//         try {
//             optparsor.addSimpleOption(NULL, "--foo");
//             optparsor.parseArguments(argc, const_cast<char**>(argv));
//         }
//         catch (const mblet::Optparsor::ParseArgumentException& e) {
//             EXPECT_STREQ(e.argument(), "foo");
//             EXPECT_STREQ(e.what(), "bad number of argument");
//             throw;
//         }
//     }, mblet::Optparsor::ParseArgumentException);
// }

GTEST_TEST(parseArguments, help) {
    const char* argv[] = {
        "binaryname",
        "-h"
    };
    const int argc = sizeof(argv) / sizeof(*argv);
    mblet::Optparsor optparsor;
    EXPECT_DEATH(optparsor.parseArguments(argc, const_cast<char**>(argv)), "");
}