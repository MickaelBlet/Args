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
        args.addArgument("-a", mblet::Argparsor::STORE_TRUE, "help of bool option", false);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("-a", mblet::Argparsor::STORE_TRUE, "help of bool option", false);
        args.addArgument("-b", mblet::Argparsor::EXTEND, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--boolean", mblet::Argparsor::STORE_TRUE, "help of bool option", false);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--number", mblet::Argparsor::NONE, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--simple", mblet::Argparsor::NONE, "help of bool option", false, NULL, 1);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--number", mblet::Argparsor::NONE, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--multi", mblet::Argparsor::APPEND, "help of bool option", false, NULL, 1);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--multi-number", mblet::Argparsor::APPEND, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
        args.addArgument("--multi-number-infinite", mblet::Argparsor::EXTEND, "help of bool option", false, NULL, 2);
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv), true, true);
            }
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
            catch (const mblet::Argparsor::ParseArgumentException& e) {
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
    args.addArgument("-b", mblet::Argparsor::STORE_TRUE, "help of boolean option");
    args.addArgument("-r", mblet::Argparsor::STORE_FALSE, "help of reverse boolean option");
    args.addArgument("-s", mblet::Argparsor::NONE, "help of simple option", false, NULL, 1);
    args.addArgument("--infinite", mblet::Argparsor::NONE, "help of infinite option", false, NULL, '+', args.vector("0",
                                                                                                                    "1", "2", "3"));
    args.parseArguments(argc, const_cast<char**>(argv), true, true);
    EXPECT_EQ(args["-b"].getString(), "true");
    EXPECT_EQ(args["-r"].getString(), "false");
    EXPECT_EQ(args["-s"].getString(), "Simple");
    EXPECT_EQ(args["--infinite"][0].getString(), "-o");
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
    args.addArgument("REQUIRED", mblet::Argparsor::NONE, "help of required positional argument",
                     true).valid(new mblet::Argparsor::ValidChoise(args.vector("ISREQUIRED")));
    // BOOL
    args.addArgument(args.vector("-b", "--bool"), mblet::Argparsor::STORE_TRUE, "help of bool option", false);
    args.addArgument("--notbool", mblet::Argparsor::STORE_FALSE, "help of notbool option", false);
    // SIMPLE
    args.addArgument(args.vector("-s", "--simple"), mblet::Argparsor::NONE, "help of simple option", false, "ArgOfSimple",
                     1,
                     args.vector("0"));
    // NUMBER
    args.addArgument("--number", mblet::Argparsor::NONE, "help of number option", false, "Arg1 Arg2", 2, args.vector("0",
                                                                                                                     "1"));
    // INFINITE
    args.addArgument("--infinite", mblet::Argparsor::NONE, "help of infinite option", false, NULL, '+', args.vector("0",
                                                                                                                    "1", "2", "3"));
    // MULTI
    args.addArgument(args.vector("-m", "--multi"), mblet::Argparsor::APPEND, "help of multi option", false, NULL, 1,
                     args.vector("0", "1",
                                 "2", "3"));
    // MULTI2
    args.addArgument(args.vector("--multi2"), mblet::Argparsor::APPEND, "help of multi2 option", false, NULL, 1,
                     args.vector("0", "1", "2",
                                 "3"));
    // MULTI NUMBER
    args.addArgument("--multi-number", mblet::Argparsor::APPEND, "help of multi number option", false, NULL, 2,
                     args.vector("0", "1", "2",
                                 "3"));
    // MULTI INFINITE
    args.addArgument("--multi-infinite", mblet::Argparsor::EXTEND, "help of multi-infinite option", false, NULL, 1,
                     args.vector("0", "1",
                                 "2", "3"));
    // MULTI INFINITE NUMBER
    args.addArgument("--multi-infinite-number", mblet::Argparsor::EXTEND, "help of multi-infinite-number option", false,
                     NULL, 2,
                     args.vector("0", "1", "2", "3"));

    args.parseArguments(argc, const_cast<char**>(argv), true, false);
    EXPECT_EQ(args["REQUIRED"].getString(), "ISREQUIRED");
    EXPECT_EQ(args["-b"].getString(), "true");
    EXPECT_EQ(args["--notbool"].getString(), "false");
    EXPECT_EQ(args["--simple"].getString(), "SIMPLE");
    EXPECT_EQ(args["--number"][0].getString(), "FOO");
    EXPECT_EQ(args["--number"][1].getString(), "BAR");
    EXPECT_EQ(args["--infinite"][0].getString(), "A");
    EXPECT_EQ(args["--infinite"][1].getString(), "B");
    EXPECT_EQ(args["--infinite"][2].getString(), "C");
    EXPECT_EQ(args["--infinite"][3].getString(), "D");
    EXPECT_EQ(args["--infinite"][4].getString(), "E");
    EXPECT_EQ(args["-m"][0].getString(), "A");
    EXPECT_EQ(args["-m"][1].getString(), "B");
    EXPECT_EQ(args["-m"][2].getString(), "C");
    EXPECT_EQ(args["--multi2"][0].getString(), "A");
    EXPECT_EQ(args["--multi-number"][0][0].getString(), "A");
    EXPECT_EQ(args["--multi-number"][0][1].getString(), "B");
    EXPECT_EQ(args["--multi-number"][1][0].getString(), "C");
    EXPECT_EQ(args["--multi-number"][1][1].getString(), "D");
    EXPECT_EQ(args["--multi-infinite"][0].getString(), "A");
    EXPECT_EQ(args["--multi-infinite"][1].getString(), "B");
    EXPECT_EQ(args["--multi-infinite"][2].getString(), "C");
    EXPECT_EQ(args["--multi-infinite"][3].getString(), "D");
    EXPECT_EQ(args["--multi-infinite"][4].getString(), "E");
    EXPECT_EQ(args["--multi-infinite-number"][0][0].getString(), "A");
    EXPECT_EQ(args["--multi-infinite-number"][0][1].getString(), "B");
    EXPECT_EQ(args["--multi-infinite-number"][1][0].getString(), "C");
    EXPECT_EQ(args["--multi-infinite-number"][1][1].getString(), "D");
    EXPECT_EQ(args["--multi-infinite-number"][2][0].getString(), "E");
    EXPECT_EQ(args["--multi-infinite-number"][2][1].getString(), "F");
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
    args.addArgument("--version", mblet::Argparsor::VERSION, "help of version", false, NULL, 0, "version: 0.0.0");
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
    args.addArgument("argument", mblet::Argparsor::NONE, "help of argument", true);
    EXPECT_THROW({
        try {
            args.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Argparsor::ParseArgumentRequiredException& e) {
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
    args.addArgument("--option", mblet::Argparsor::STORE_TRUE, "help of option", true);
    EXPECT_THROW({
        try {
            args.parseArguments(argc, const_cast<char**>(argv));
        }
        catch (const mblet::Argparsor::ParseArgumentRequiredException& e) {
            EXPECT_STREQ(e.what(), "option is required");
            EXPECT_STREQ(e.argument(), "--option");
            throw;
        }
    }, mblet::Argparsor::ParseArgumentRequiredException);
}


GTEST_TEST(parseArguments, validException) {

    const char* argv[] = {
        "binaryName",
        "--option", "foo"
    };
    const int argc = sizeof(argv) / sizeof(*argv);

    struct FailedTest : public mblet::Argparsor::IValid {
        bool isValid(std::vector<std::string>& /*argument*/) {
            return false;
        }
    };
    {
        mblet::Argparsor args;
        args.addArgument("--option", mblet::Argparsor::STORE_TRUE, "help of option", false).valid(new FailedTest());
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv));
            }
            catch (const mblet::Argparsor::ParseArgumentValidException& e) {
                EXPECT_STREQ(e.what(), "invalid type option for use valid");
                EXPECT_STREQ(e.argument(), "--option");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentValidException);
    }
    {
        mblet::Argparsor args;
        args.addArgument("--option", mblet::Argparsor::NONE, "help of option", false, "", 1).valid(new FailedTest());
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv));
            }
            catch (const mblet::Argparsor::ParseArgumentValidException& e) {
                EXPECT_STREQ(e.what(), "invalid check function");
                EXPECT_STREQ(e.argument(), "--option");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentValidException);
    }
    {
        mblet::Argparsor args;
        args.addArgument("--option", mblet::Argparsor::NONE, "help of option", false, "", 1).valid(new FailedTest());
        EXPECT_THROW({
            try {
                args.parseArguments(argc, const_cast<char**>(argv));
            }
            catch (const mblet::Argparsor::ParseArgumentValidException& e) {
                EXPECT_STREQ(e.what(), "invalid check function");
                EXPECT_STREQ(e.argument(), "--option");
                throw;
            }
        }, mblet::Argparsor::ParseArgumentValidException);
    }
}