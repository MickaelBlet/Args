#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(parseArguments, parseException) {
    {
        const char* argv[] = {
            "binaryName",
            "-ba"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("-a", "store_true", "help of bool option", false);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "invalid option");
                EXPECT_STREQ(e.argument(), "b");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "-ba"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("-a", "store_true", "help of bool option", false);
        args.addArgument("-b", "extend", "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "only last option can be use a parameter");
                EXPECT_STREQ(e.argument(), "b");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "-a"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "invalid option");
                EXPECT_STREQ(e.argument(), "a");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--long"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "invalid option");
                EXPECT_STREQ(e.argument(), "long");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--boolean=nothing"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--boolean", "store_true", "help of bool option", false);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "option cannot use with argument");
                EXPECT_STREQ(e.argument(), "boolean");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--number=nothing"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--number", NULL, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "option cannot use with only 1 argument");
                EXPECT_STREQ(e.argument(), "number");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--simple"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--simple", NULL, "help of bool option", false, NULL, 1);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "bad number of argument");
                EXPECT_STREQ(e.argument(), "simple");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--number"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--number", NULL, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "bad number of argument");
                EXPECT_STREQ(e.argument(), "number");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--multi"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--multi", "append", "help of bool option", false, NULL, 1);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "bad number of argument");
                EXPECT_STREQ(e.argument(), "multi");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--multi-number", "arg"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--multi-number", "append", "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "bad number of argument");
                EXPECT_STREQ(e.argument(), "multi-number");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "--multi-number-infinite", "arg"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--multi-number-infinite", "extend", "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "bad number of argument");
                EXPECT_STREQ(e.argument(), "multi-number-infinite");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {
            "binaryName",
            "arg"
        };
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException &e) {
                EXPECT_STREQ(e.what(), "invalid additional argument");
                EXPECT_STREQ(e.argument(), "arg");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentException);
    }
}

GTEST_TEST(parseArguments, endOfInfiniteArgument) {
    const char* argv[] = {
        "binaryName",
        "--infinite", "-infinite", // alternative stop
        "--infinite", "-ok", // unknown option OK
        "--infinite", "-rb", // boolean option
        "--infinite", "-sSimple", // simple option
        "--infinite", "-o", // unknown option OK
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("-b", "store_true", "help of boolean option");
    args.addArgument("-r", "store_false", "help of reverse boolean option");
    args.addArgument("-s", NULL, "help of simple option", false, NULL, 1);
    args.addArgument("--infinite", NULL, "help of infinite option", false, NULL, '+', args.vector("0", "1", "2", "3"));
    args.parseArguments(argc, const_cast<char**>(argv), true, true);
    EXPECT_EQ(args["-b"].str(), "true");
    EXPECT_EQ(args["-r"].str(), "false");
    EXPECT_EQ(args["-s"].str(), "Simple");
    EXPECT_EQ(args["--infinite"][0].str(), "-o");
}

GTEST_TEST(parseArguments, allType) {
    const char* argv[] = {
        "binaryName",
        "--notbool",
        "-bsSIMPLE",
        "--simple", "SIMPLE",
        "--number", "FOO", "BAR",
        "--infinite=A",
        "--infinite", "A", "B", "C", "D", "E",
        "-m=A",
        "-multi", "B",
        "--multi", "C",
        "-multi2", "A",
        "--multi-number", "A", "B",
        "--multi-number", "C", "D",
        "--multi-infinite", "A", "B", "C",
        "--multi-infinite", "D", "E",
        "--multi-infinite-number", "A", "B",
        "--multi-infinite-number", "C", "D", "E", "F",
        "--",
        "ISREQUIRED",
        "ADDITIONNAL"
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    // POSITIONNAL
    args.addArgument("REQUIRED", NULL, "help of required positional argument", true);
    // BOOL
    args.addArgument(args.vector("-b", "--bool"), "store_true", "help of bool option", false);
    args.addArgument("--notbool", "store_false", "help of notbool option", false);
    // SIMPLE
    args.addArgument(args.vector("-s", "--simple"), NULL, "help of simple option", false, "ArgOfSimple", 1, args.vector("0"));
    // NUMBER
    args.addArgument("--number", NULL, "help of number option", false, "Arg1 Arg2", 2, args.vector("0", "1"));
    // INFINITE
    args.addArgument("--infinite", NULL, "help of infinite option", false, NULL, '+', args.vector("0", "1", "2", "3"));
    // MULTI
    args.addArgument(args.vector("-m", "--multi"), "append", "help of multi option", false, NULL, 1, args.vector("0", "1", "2", "3"));
    // MULTI2
    args.addArgument(args.vector("--multi2"), "append", "help of multi2 option", false, NULL, 1, args.vector("0", "1", "2", "3"));
    // MULTI NUMBER
    args.addArgument("--multi-number", "append", "help of multi number option", false, NULL, 2, args.vector("0", "1", "2", "3"));
    // MULTI INFINITE
    args.addArgument("--multi-infinite", "extend", "help of multi-infinite option", false, NULL, 1, args.vector("0", "1", "2", "3"));
    // MULTI INFINITE NUMBER
    args.addArgument("--multi-infinite-number", "extend", "help of multi-infinite-number option", false, NULL, 2, args.vector("0", "1", "2", "3"));

    args.parseArguments(argc, const_cast<char**>(argv), true, false);
    EXPECT_EQ(args["REQUIRED"].str(), "ISREQUIRED");
    EXPECT_EQ(args["-b"].str(), "true");
    EXPECT_EQ(args["--notbool"].str(), "false");
    EXPECT_EQ(args["--simple"].str(), "SIMPLE");
    EXPECT_EQ(args["--number"][0].str(), "FOO");
    EXPECT_EQ(args["--number"][1].str(), "BAR");
    EXPECT_EQ(args["--infinite"][0].str(), "A");
    EXPECT_EQ(args["--infinite"][1].str(), "B");
    EXPECT_EQ(args["--infinite"][2].str(), "C");
    EXPECT_EQ(args["--infinite"][3].str(), "D");
    EXPECT_EQ(args["--infinite"][4].str(), "E");
    EXPECT_EQ(args["-m"][0].str(), "A");
    EXPECT_EQ(args["-m"][1].str(), "B");
    EXPECT_EQ(args["-m"][2].str(), "C");
    EXPECT_EQ(args["--multi2"][0].str(), "A");
    EXPECT_EQ(args["--multi-number"][0][0].str(), "A");
    EXPECT_EQ(args["--multi-number"][0][1].str(), "B");
    EXPECT_EQ(args["--multi-number"][1][0].str(), "C");
    EXPECT_EQ(args["--multi-number"][1][1].str(), "D");
    EXPECT_EQ(args["--multi-infinite"][0].str(), "A");
    EXPECT_EQ(args["--multi-infinite"][1].str(), "B");
    EXPECT_EQ(args["--multi-infinite"][2].str(), "C");
    EXPECT_EQ(args["--multi-infinite"][3].str(), "D");
    EXPECT_EQ(args["--multi-infinite"][4].str(), "E");
    EXPECT_EQ(args["--multi-infinite-number"][0][0].str(), "A");
    EXPECT_EQ(args["--multi-infinite-number"][0][1].str(), "B");
    EXPECT_EQ(args["--multi-infinite-number"][1][0].str(), "C");
    EXPECT_EQ(args["--multi-infinite-number"][1][1].str(), "D");
    EXPECT_EQ(args["--multi-infinite-number"][2][0].str(), "E");
    EXPECT_EQ(args["--multi-infinite-number"][2][1].str(), "F");
}

GTEST_TEST(parseArguments, help) {
    const char* argv[] = {
        "binaryName",
        "--help"
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    testing::internal::CaptureStdout();
    EXPECT_EXIT({
        args.parseArguments(argc, const_cast<char**>(argv));
    }, ::testing::ExitedWithCode(0), ".*");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "usage: binaryName [-h]\n"
    "\n"
    "optional arguments:\n"
    "  -h, --help  show this help message and exit\n");
}

GTEST_TEST(parseArguments, version) {
    const char* argv[] = {
        "binaryName",
        "--version"
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("--version", "version", "help of version", false, NULL, 0, "version: 0.0.0");
    testing::internal::CaptureStdout();
    EXPECT_EXIT({
        args.parseArguments(argc, const_cast<char**>(argv));
    }, ::testing::ExitedWithCode(0), ".*");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "version: 0.0.0\n");
}

GTEST_TEST(parseArguments, argumentRequired) {
    const char* argv[] = {
        "binaryName"
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("argument", NULL, "help of argument", true);
    EXPECT_THROW({
        try {
            args.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Argparsor::ParseArgumentRequiredException &e) {
            EXPECT_STREQ(e.what(), "argument is required");
            EXPECT_STREQ(e.argument(), "argument");
            throw;
        }
    }, mblet::Argparsor::ParseArgumentRequiredException);
}

GTEST_TEST(parseArguments, optionRequired) {
    const char* argv[] = {
        "binaryName"
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("--option", "store_true", "help of option", true);
    EXPECT_THROW({
        try {
            args.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Argparsor::ParseArgumentRequiredException &e) {
            EXPECT_STREQ(e.what(), "option is required");
            EXPECT_STREQ(e.argument(), "--option");
            throw;
        }
    }, mblet::Argparsor::ParseArgumentRequiredException);
}