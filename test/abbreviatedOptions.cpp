#include <gtest/gtest.h>

#include "blet/args.h"

// Test isAbbreviate_ flag (via setAbbreviate and isAbbreviate methods)
GTEST_TEST(abbreviatedOptions, isAbbreviate) {
    // Test default value
    {
        blet::Args args;
        EXPECT_FALSE(args.isAbbreviate());
    }

    // Test setting to true
    {
        blet::Args args;
        args.setAbbreviate(true);
        EXPECT_TRUE(args.isAbbreviate());
    }

    // Test setting to false explicitly
    {
        blet::Args args;
        args.setAbbreviate(false);
        EXPECT_FALSE(args.isAbbreviate());
    }

    // Test default parameter (should be true)
    {
        blet::Args args;
        args.setAbbreviate();
        EXPECT_TRUE(args.isAbbreviate());
    }

    // Test chaining
    {
        blet::Args args;
        args.setAbbreviate().setStrict();
        EXPECT_TRUE(args.isAbbreviate());
        EXPECT_TRUE(args.isStrict());
    }

    // Test toggling
    {
        blet::Args args;
        args.setAbbreviate(true);
        EXPECT_TRUE(args.isAbbreviate());
        args.setAbbreviate(false);
        EXPECT_FALSE(args.isAbbreviate());
    }
}

// Test findAbbreviatedOption_ - successful unique match
GTEST_TEST(abbreviatedOptions, findAbbreviatedOption_uniqueMatch) {
    // Test simple abbreviation
    {
        const char* argv[] = {"binaryName", "--ver", "1.0.0"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--version"].getString(), std::string("1.0.0"));
    }

    // Test very short abbreviation
    {
        const char* argv[] = {"binaryName", "--v", "test"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--verbose"].getString(), std::string("test"));
    }

    // Test full option name (should also work with abbrev enabled)
    {
        const char* argv[] = {"binaryName", "--version", "2.0.0"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--version"].getString(), std::string("2.0.0"));
    }

    // Test abbreviation with boolean option
    {
        const char* argv[] = {"binaryName", "--verb"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose").action(blet::Args::STORE_TRUE);
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_TRUE(args["--verbose"].operator bool());
    }

    // Test abbreviation with option that has value with equals sign
    {
        const char* argv[] = {"binaryName", "--out=file.txt"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--output");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--output"].getString(), std::string("file.txt"));
    }
}

// Test findAbbreviatedOption_ - ambiguous match (should throw)
GTEST_TEST(abbreviatedOptions, findAbbreviatedOption_ambiguousMatch) {
    // Test ambiguous abbreviation
    {
        const char* argv[] = {"binaryName", "--ver", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");
        args.addArgument("--verbose");
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.argument(), "ver");
                    std::string whatStr = e.what();
                    EXPECT_NE(whatStr.find("ambiguous"), std::string::npos);
                    EXPECT_NE(whatStr.find("--version"), std::string::npos);
                    EXPECT_NE(whatStr.find("--verbose"), std::string::npos);
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test another ambiguous case
    {
        const char* argv[] = {"binaryName", "--o", "file"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--output");
        args.addArgument("--outfile");
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.argument(), "o");
                    std::string whatStr = e.what();
                    EXPECT_NE(whatStr.find("ambiguous"), std::string::npos);
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test three-way ambiguity
    {
        const char* argv[] = {"binaryName", "--v"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose").action(blet::Args::STORE_TRUE);
        args.addArgument("--version").action(blet::Args::STORE_TRUE);
        args.addArgument("--validate").action(blet::Args::STORE_TRUE);
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.argument(), "v");
                    std::string whatStr = e.what();
                    EXPECT_NE(whatStr.find("ambiguous"), std::string::npos);
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }
}

// Test findAbbreviatedOption_ - no match (should throw)
GTEST_TEST(abbreviatedOptions, findAbbreviatedOption_noMatch) {
    // Test non-existent abbreviation
    {
        const char* argv[] = {"binaryName", "--xyz"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version").action(blet::Args::STORE_TRUE);
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "xyz");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test abbreviation that doesn't match any option
    {
        const char* argv[] = {"binaryName", "--abc", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");
        args.addArgument("--verbose");
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "abc");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }
}

// Test that abbreviation doesn't work when disabled
GTEST_TEST(abbreviatedOptions, abbreviationDisabled) {
    // Test that abbreviation fails when setAbbreviate is not called
    {
        const char* argv[] = {"binaryName", "--ver", "1.0.0"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "ver");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test that abbreviation fails when explicitly disabled
    {
        const char* argv[] = {"binaryName", "--verb"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose").action(blet::Args::STORE_TRUE);
        args.setAbbreviate(false);

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "verb");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }
}

// Test that short options are not affected by abbreviation
GTEST_TEST(abbreviatedOptions, shortOptionsUnaffected) {
    // Test that short options work the same with or without abbrev
    {
        const char* argv[] = {"binaryName", "-v"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("-v").flag("--verbose").action(blet::Args::STORE_TRUE);
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_TRUE(args["--verbose"].operator bool());
    }

    // Test that short options still throw when invalid
    {
        const char* argv[] = {"binaryName", "-x"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("-v").flag("--verbose").action(blet::Args::STORE_TRUE);
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "x");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }
}

// Test mixed scenarios
GTEST_TEST(abbreviatedOptions, mixedScenarios) {
    // Test multiple abbreviated options in single command
    {
        const char* argv[] = {"binaryName", "--verb", "--out", "file.txt"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose").action(blet::Args::STORE_TRUE);
        args.addArgument("--output");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_TRUE(args["--verbose"].operator bool());
        EXPECT_EQ(args["--output"].getString(), std::string("file.txt"));
    }

    // Test abbreviation with positional arguments
    {
        const char* argv[] = {"binaryName", "--verb", "file1", "file2"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose").action(blet::Args::STORE_TRUE);
        args.addArgument("files").nargs(2);
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_TRUE(args["--verbose"].operator bool());
        EXPECT_EQ(args["files"].size(), 2);
        EXPECT_EQ(args["files"][0].getString(), std::string("file1"));
        EXPECT_EQ(args["files"][1].getString(), std::string("file2"));
    }

    // Test that exact match takes precedence over abbreviation
    {
        const char* argv[] = {"binaryName", "--ver", "match"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--ver");
        args.addArgument("--version");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        // Exact match should be used
        EXPECT_EQ(args["--ver"].getString(), std::string("match"));
        EXPECT_FALSE(args["--version"].isExists());
    }
}

// Test edge cases
GTEST_TEST(abbreviatedOptions, edgeCases) {
    // Test minimum abbreviation (just "--" + one char)
    {
        const char* argv[] = {"binaryName", "--v", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--verbose"].getString(), std::string("value"));
    }

    // Test abbreviation doesn't match short options
    {
        const char* argv[] = {"binaryName", "--v"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("-v").action(blet::Args::STORE_TRUE);
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "v");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test abbreviation with nargs
    {
        const char* argv[] = {"binaryName", "--fil", "a.txt", "b.txt"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--files").action(blet::Args::EXTEND).nargs(2);
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--files"].size(), 1);
        EXPECT_EQ(args["--files"][0][0].getString(), std::string("a.txt"));
        EXPECT_EQ(args["--files"][0][1].getString(), std::string("b.txt"));
    }

    // Test that clear() resets isAbbreviate_ to false
    {
        blet::Args args;
        args.setAbbreviate(true);
        EXPECT_TRUE(args.isAbbreviate());
        args.clear();
        EXPECT_FALSE(args.isAbbreviate());
    }
}

// Test the abbreviated match algorithm specifically
GTEST_TEST(abbreviatedOptions, abbreviatedMatchAlgorithm) {
    // Test that only long options (key.size() > 2 && starts with "--") are matched
    // Short options should be ignored even if they could match as prefix
    {
        const char* argv[] = {"binaryName", "--v", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("-v");        // Single dash (should be ignored)
        args.addArgument("--verbose"); // Double dash (should match)
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--verbose"].getString(), std::string("value"));
        EXPECT_FALSE(args["-v"].isExists());
    }

    // Test prefix matching: key.compare(0, option.size(), option) == 0
    // Ensures that only options starting with the abbreviation are matched
    {
        const char* argv[] = {"binaryName", "--ver", "test"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version"); // Starts with "ver" - should match
        args.addArgument("--verbose"); // Starts with "ver" - should match (ambiguous)
        args.addArgument("--reverse"); // Contains "ver" but doesn't start - should not match
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    std::string whatStr = e.what();
                    // Should be ambiguous between --version and --verbose only
                    EXPECT_NE(whatStr.find("ambiguous"), std::string::npos);
                    EXPECT_NE(whatStr.find("--version"), std::string::npos);
                    EXPECT_NE(whatStr.find("--verbose"), std::string::npos);
                    // --reverse should not be mentioned
                    EXPECT_EQ(whatStr.find("--reverse"), std::string::npos);
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test that key.size() >= option.size() is checked
    // Abbreviated option cannot be longer than the full option
    {
        const char* argv[] = {"binaryName", "--verbosity", "high"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose"); // Shorter than "--verbosity"
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "verbosity");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test matchCount == 0: no matches found
    {
        const char* argv[] = {"binaryName", "--xyz", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--abc");
        args.addArgument("--def");
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "xyz");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test matchCount == 1: exactly one match (success case)
    {
        const char* argv[] = {"binaryName", "--verb", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose");
        args.addArgument("--output"); // Doesn't match
        args.addArgument("--input");  // Doesn't match
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--verbose"].getString(), std::string("value"));
    }

    // Test matchCount > 1: multiple matches (ambiguous)
    {
        const char* argv[] = {"binaryName", "--opt", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--option");
        args.addArgument("--optimize");
        args.addArgument("--optional");
        args.setAbbreviate();

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    std::string whatStr = e.what();
                    EXPECT_NE(whatStr.find("ambiguous"), std::string::npos);
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test that exact match takes precedence (it won't enter the abbreviation code)
    {
        const char* argv[] = {"binaryName", "--version", "1.0"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");
        args.addArgument("--verbose");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--version"].getString(), std::string("1.0"));
        EXPECT_FALSE(args["--verbose"].isExists());
    }

    // Test that the algorithm only runs when isAbbreviate_ is true
    // (covered by abbreviationDisabled test, but worth emphasizing)
    {
        const char* argv[] = {"binaryName", "--ver", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--version");
        // isAbbreviate_ is false by default

        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const blet::Args::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    throw;
                }
            },
            blet::Args::ParseArgumentException);
    }

    // Test minimum valid long option size (3 chars: "--" + at least 1 char)
    {
        const char* argv[] = {"binaryName", "--v", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--verbose");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--verbose"].getString(), std::string("value"));
    }

    // Test that options with exactly 2 characters (e.g., "--") would be ignored
    // This is a pathological case but tests the key.size() > 2 condition
    // Note: This would require manually adding such an option, which is invalid,
    // so we test that normal 3-char options work correctly
    {
        const char* argv[] = {"binaryName", "--a", "value"};
        const int argc = sizeof(argv) / sizeof(*argv);

        blet::Args args;
        args.addArgument("--alpha");
        args.setAbbreviate();

        EXPECT_NO_THROW(args.parseArguments(argc, const_cast<char**>(argv)));
        EXPECT_EQ(args["--alpha"].getString(), std::string("value"));
    }
}

// Test the abbreviated match algorithm specifically with infinite option
GTEST_TEST(abbreviatedOptions, abbreviatedMatchWithInfinite) {
    // clang-format off
    const char* argv[] = {
        "binaryName", "--infinite", "-infinite", // alternative stop
        "--infinite", "-ok",                     // unknown option OK
        "--infinite", "-rb",                     // boolean option
        "--infinite", "--sim=Simple"             // abreviate to simple option KO
    };
    // clang-format on
    const int argc = sizeof(argv) / sizeof(*argv);

    blet::Args args;
    args.addArgument("-b").action(blet::Args::STORE_TRUE);
    args.addArgument("-r").action(blet::Args::STORE_FALSE);
    args.addArgument("-s").flag("--simple").nargs(1);
    args.addArgument("-S").flag("--simply").nargs(1);
    args.addArgument("--infinite").nargs('+').defaults(args.vector("0", "1", "2", "3"));
    args.setAlternative().setStrict().setAbbreviate();
    args.parseArguments(argc, const_cast<char**>(argv));
    EXPECT_EQ(args["-b"].getString(), std::string("true"));
    EXPECT_EQ(args["-r"].getString(), std::string("false"));
    EXPECT_EQ(args["--infinite"][0].getString(), std::string("--sim=Simple"));
}
