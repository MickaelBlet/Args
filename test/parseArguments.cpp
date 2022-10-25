#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(parseArguments, parseException) {
    {
        const char* argv[] = {"binaryName", "-ba"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("-a").action(mblet::Argparsor::STORE_TRUE);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "b");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "-ba"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("-a").action(mblet::Argparsor::STORE_TRUE);
        args.addArgument("-b").action(mblet::Argparsor::EXTEND).nargs(2);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "only last option can be use a parameter");
                    EXPECT_STREQ(e.argument(), "b");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "-a"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "a");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--long"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid option");
                    EXPECT_STREQ(e.argument(), "long");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--boolean=nothing"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--boolean").action(mblet::Argparsor::STORE_TRUE);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "option cannot use with argument");
                    EXPECT_STREQ(e.argument(), "boolean");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--number=nothing"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--number").nargs(2);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "option cannot use with only 1 argument");
                    EXPECT_STREQ(e.argument(), "number");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--simple"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--simple").nargs(1);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "bad number of argument");
                    EXPECT_STREQ(e.argument(), "simple");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--number"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--number").nargs(2);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "bad number of argument");
                    EXPECT_STREQ(e.argument(), "number");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--multi"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--multi").action(mblet::Argparsor::APPEND).nargs(1);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "bad number of argument");
                    EXPECT_STREQ(e.argument(), "multi");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--multi-number", "arg"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--multi-number").action(mblet::Argparsor::APPEND).nargs(2);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "bad number of argument");
                    EXPECT_STREQ(e.argument(), "multi-number");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "--multi-number-infinite", "arg"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        args.addArgument("--multi-number-infinite").action(mblet::Argparsor::EXTEND).nargs(2);
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "bad number of argument");
                    EXPECT_STREQ(e.argument(), "multi-number-infinite");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
    {
        const char* argv[] = {"binaryName", "arg"};
        const int argc = sizeof(argv) / sizeof(*argv);

        mblet::Argparsor args;
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv), true, true);
                }
                catch (const mblet::Argparsor::ParseArgumentException& e) {
                    EXPECT_STREQ(e.what(), "invalid additional argument");
                    EXPECT_STREQ(e.argument(), "arg");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentException);
    }
}

GTEST_TEST(parseArguments, endOfInfiniteArgument) {
    // clang-format off
    const char* argv[] = {
        "binaryName", "--infinite", "-infinite", // alternative stop
        "--infinite", "-ok",                     // unknown option OK
        "--infinite", "-rb",                     // boolean option
        "--infinite", "-sSimple",                // simple option
        "--infinite", "-o",                      // unknown option OK
    };
    // clang-format on
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("-b").action(mblet::Argparsor::STORE_TRUE);
    args.addArgument("-r").action(mblet::Argparsor::STORE_FALSE);
    args.addArgument("-s").nargs(1);
    args.addArgument("--infinite").nargs('+').defaults(args.vector("0", "1", "2", "3"));
    args.parseArguments(argc, const_cast<char**>(argv), true, true);
    EXPECT_EQ(args["-b"].getString(), "true");
    EXPECT_EQ(args["-r"].getString(), "false");
    EXPECT_EQ(args["-s"].getString(), "Simple");
    EXPECT_EQ(args["--infinite"][0].getString(), "-o");
}

GTEST_TEST(parseArguments, allType) {
    // clang-format off
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
    // clang-format on

    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    // POSITIONNAL
    args.addArgument("REQUIRED").required(true).valid(new mblet::Argparsor::ValidChoise(args.vector("ISREQUIRED")));
    // BOOL
    args.addArgument(args.vector("-b", "--bool")).action(mblet::Argparsor::STORE_TRUE);
    args.addArgument("--notbool").action(mblet::Argparsor::STORE_FALSE);
    // SIMPLE
    args.addArgument(args.vector("-s", "--simple")).metavar("ArgOfSimple").nargs(1).defaults(args.vector("0"));
    // NUMBER
    args.addArgument("--number").metavar("Arg1 Arg2").nargs(2).defaults(args.vector("0", "1"));
    // INFINITE
    args.addArgument("--infinite").nargs('+').defaults(args.vector("0", "1", "2", "3"));
    // MULTI
    args.addArgument(args.vector("-m", "--multi"))
        .action(mblet::Argparsor::APPEND)
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI2
    args.addArgument(args.vector("--multi2"))
        .action(mblet::Argparsor::APPEND)
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI NUMBER
    args.addArgument("--multi-number")
        .action(mblet::Argparsor::APPEND)
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI INFINITE
    args.addArgument("--multi-infinite")
        .action(mblet::Argparsor::EXTEND)
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI INFINITE NUMBER
    args.addArgument("--multi-infinite-number")
        .action(mblet::Argparsor::EXTEND)
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"));

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
    const char* argv[] = {"binaryName", "--help"};
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    testing::internal::CaptureStdout();
    EXPECT_EXIT({ args.parseArguments(argc, const_cast<char**>(argv)); }, ::testing::ExitedWithCode(0), ".*");
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "usage: binaryName [-h]\n"
              "\n"
              "optional arguments:\n"
              "  -h, --help  show this help message and exit\n");
}

GTEST_TEST(parseArguments, version) {
    const char* argv[] = {"binaryName", "--version"};
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("--version").action(mblet::Argparsor::VERSION).defaults("version: 0.0.0");
    testing::internal::CaptureStdout();
    EXPECT_EXIT({ args.parseArguments(argc, const_cast<char**>(argv)); }, ::testing::ExitedWithCode(0), ".*");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "version: 0.0.0\n");
}

GTEST_TEST(parseArguments, argumentRequired) {
    const char* argv[] = {"binaryName"};
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("argument").required(true);
    EXPECT_THROW(
        {
            try {
                args.parseArguments(argc, const_cast<char**>(argv));
            }
            catch (const mblet::Argparsor::ParseArgumentRequiredException& e) {
                EXPECT_STREQ(e.what(), "argument is required");
                EXPECT_STREQ(e.argument(), "argument");
                throw;
            }
        },
        mblet::Argparsor::ParseArgumentRequiredException);
}

GTEST_TEST(parseArguments, optionRequired) {
    const char* argv[] = {"binaryName"};
    const int argc = sizeof(argv) / sizeof(*argv);

    mblet::Argparsor args;
    args.addArgument("--option").action(mblet::Argparsor::STORE_TRUE).required(true);
    EXPECT_THROW(
        {
            try {
                args.parseArguments(argc, const_cast<char**>(argv));
            }
            catch (const mblet::Argparsor::ParseArgumentRequiredException& e) {
                EXPECT_STREQ(e.what(), "option is required");
                EXPECT_STREQ(e.argument(), "--option");
                throw;
            }
        },
        mblet::Argparsor::ParseArgumentRequiredException);
}

GTEST_TEST(parseArguments, validException) {
    const char* argv[] = {"binaryName", "--option", "foo"};
    const int argc = sizeof(argv) / sizeof(*argv);

    struct FailedTest : public mblet::Argparsor::IValid {
        bool isValid(std::vector<std::string>& /*argument*/) {
            return false;
        }
    };
    {
        mblet::Argparsor args;
        args.addArgument("--option").action(mblet::Argparsor::STORE_TRUE).valid(new FailedTest());
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const mblet::Argparsor::ParseArgumentValidException& e) {
                    EXPECT_STREQ(e.what(), "invalid type option for use valid");
                    EXPECT_STREQ(e.argument(), "--option");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentValidException);
    }
    {
        mblet::Argparsor args;
        args.addArgument("--option").nargs(1).valid(new FailedTest());
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const mblet::Argparsor::ParseArgumentValidException& e) {
                    EXPECT_STREQ(e.what(), "invalid check function");
                    EXPECT_STREQ(e.argument(), "--option");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentValidException);
    }
    {
        mblet::Argparsor args;
        args.addArgument("--option").nargs(1).valid(new FailedTest());
        EXPECT_THROW(
            {
                try {
                    args.parseArguments(argc, const_cast<char**>(argv));
                }
                catch (const mblet::Argparsor::ParseArgumentValidException& e) {
                    EXPECT_STREQ(e.what(), "invalid check function");
                    EXPECT_STREQ(e.argument(), "--option");
                    throw;
                }
            },
            mblet::Argparsor::ParseArgumentValidException);
    }
}