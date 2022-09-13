#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(getUsage, custom) {
    mblet::Argparsor args;
    args.setUsage("foo");
    EXPECT_EQ(args.getUsage(), "foo");
}

GTEST_TEST(getUsage, compareOption) {
    mblet::Argparsor args(false);
    args.addArgument(args.vector("-h", "--help"), mblet::Argparsor::HELP, "custom help option message");
    args.addArgument("NOTREQUIRED1", mblet::Argparsor::NONE, "help of positional argument", false);
    args.addArgument("REQUIRED1", mblet::Argparsor::NONE, "help of required1 positional argument", true);
    args.addArgument("REQUIRED2", mblet::Argparsor::NONE, "help of required2 positional argument", true);
    args.addArgument("NOTREQUIRED2", mblet::Argparsor::NONE, "help of positional argument", false);
    args.addArgument("-a", mblet::Argparsor::STORE_TRUE, "help of a short option", true);
    args.addArgument("-b", mblet::Argparsor::STORE_TRUE, "help of b short option", false);
    args.addArgument("-c", mblet::Argparsor::STORE_TRUE, "help of c short option", false);
    args.addArgument("-d", mblet::Argparsor::STORE_TRUE, "help of d short option", true);
    args.addArgument("--long1", mblet::Argparsor::STORE_TRUE, "help of long1 option", false);
    args.addArgument("--long2", mblet::Argparsor::STORE_TRUE, "help of long2 option", true);
    args.addArgument("--long3", mblet::Argparsor::STORE_TRUE, "help of long3 option", false);
    args.addArgument("--long4", mblet::Argparsor::STORE_TRUE, "help of long4 option", false);
    args.addArgument("--long5", mblet::Argparsor::STORE_TRUE, "help of long5 option", false);
    args.addArgument("--long6", mblet::Argparsor::STORE_TRUE, "help of long6 option", true);
    args.addArgument("-e", mblet::Argparsor::STORE_TRUE, "help of e short option", true);
    args.addArgument("-f", mblet::Argparsor::STORE_TRUE, "help of f short option", false);
    args.addArgument("-g", mblet::Argparsor::STORE_TRUE, "help of g short option", true);

    std::ostringstream usage("");

    usage << "usage:  -a -d -e -g --long2 --long6 [-b] [-c] [-f] [-h] [--long1] [--long3] [--long4] [--long5] -- REQUIRED1 REQUIRED2 [NOTREQUIRED1] [NOTREQUIRED2]\n";
    usage << "\n";
    usage << "positional arguments:\n";
    usage << "  REQUIRED1      help of required1 positional argument (required)\n";
    usage << "  REQUIRED2      help of required2 positional argument (required)\n";
    usage << "  NOTREQUIRED1   help of positional argument\n";
    usage << "  NOTREQUIRED2   help of positional argument\n";
    usage << "\n";
    usage << "optional arguments:\n";
    usage << "  -a             help of a short option (required)\n";
    usage << "  -d             help of d short option (required)\n";
    usage << "  -e             help of e short option (required)\n";
    usage << "  -g             help of g short option (required)\n";
    usage << "  --long2        help of long2 option (required)\n";
    usage << "  --long6        help of long6 option (required)\n";
    usage << "  -b             help of b short option\n";
    usage << "  -c             help of c short option\n";
    usage << "  -f             help of f short option\n";
    usage << "  -h, --help     custom help option message\n";
    usage << "  --long1        help of long1 option\n";
    usage << "  --long3        help of long3 option\n";
    usage << "  --long4        help of long4 option\n";
    usage << "  --long5        help of long5 option\n";

    EXPECT_EQ(args.getUsage(), usage.str());
}

GTEST_TEST(getUsage, allTypeArgument) {
    mblet::Argparsor args;
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    // POSITIONNAL
    args.addArgument("REQUIRED", mblet::Argparsor::NONE, "help of required positional argument", true);
    args.addArgument("NOTREQUIRED", mblet::Argparsor::NONE, "help of positional argument", false, NULL, 1, "DEFAULT VALUE");
    // BOOL
    args.addArgument(args.vector("-b", "--bool"), mblet::Argparsor::STORE_TRUE, "help of bool option", false);
    args.addArgument("--notbool", mblet::Argparsor::STORE_FALSE, "help of notbool option", false);
    // SIMPLE
    args.addArgument(args.vector("-s", "--simple"), mblet::Argparsor::NONE, "help of simple option", false, "ArgOfSimple",
                     1, "0");
    // NUMBER
    args.addArgument("--number", mblet::Argparsor::NONE, "help of number option", false, "Arg1 Arg2", 2, args.vector("0",
                                                                                                                     "1"));
    // INFINITE
    args.addArgument("--infinite", mblet::Argparsor::INFINITE, "help of infinite option", false, NULL, 1, args.vector("0",
                                                                                                                      "1", "2", "3"));
    // NULTI
    args.addArgument("--multi", mblet::Argparsor::APPEND, "help of multi option", false, NULL, 1, args.vector("0", "1", "2",
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

    std::ostringstream usage("");

    usage << "usage:  [-b] [-h] [-s ArgOfSimple] [--infinite INFINITE...] [--multi MULTI] [--multi-infinite MULTI-INFINITE] [--multi-infinite-number MULTI-INFINITE-NUMBER MULTI-INFINITE-NUMBER] [--multi-number MULTI-NUMBER MULTI-NUMBER] [--notbool] [--number Arg1 Arg2] -- REQUIRED [NOTREQUIRED]\n";
    usage << "\n";
    usage << "custom description message\n";
    usage << "\n";
    usage << "positional arguments:\n";
    usage << "  REQUIRED                                                             help of required positional argument (required)\n";
    usage << "  NOTREQUIRED                                                          help of positional argument (default: DEFAULT VALUE)\n";
    usage << "\n";
    usage << "optional arguments:\n";
    usage << "  -b, --bool                                                           help of bool option\n";
    usage << "  -h, --help                                                           show this help message and exit\n";
    usage << "  -s, --simple ArgOfSimple                                             help of simple option (default: 0)\n";
    usage << "  --infinite INFINITE...                                               help of infinite option (default: 0, 1, 2, 3)\n";
    usage << "  --multi MULTI                                                        help of multi option (default: 0, 1, 2, 3)\n";
    usage << "  --multi-infinite MULTI-INFINITE                                      help of multi-infinite option (default: 0, 1, 2, 3)\n";
    usage << "  --multi-infinite-number MULTI-INFINITE-NUMBER MULTI-INFINITE-NUMBER  help of multi-infinite-number option (default: (0, 1), (2, 3))\n";
    usage << "  --multi-number MULTI-NUMBER MULTI-NUMBER                             help of multi number option (default: (0, 1), (2, 3))\n";
    usage << "  --notbool                                                            help of notbool option\n";
    usage << "  --number Arg1 Arg2                                                   help of number option (default: 0, 1)\n";
    usage << "\n";
    usage << "custom epilog message\n";

    EXPECT_EQ(args.getUsage(), usage.str());
}