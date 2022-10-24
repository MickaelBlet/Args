#include <gtest/gtest.h>

#include "mblet/argparsor.h"

GTEST_TEST(getUsage, custom) {
    mblet::Argparsor args;
    args.setUsage("foo");
    EXPECT_EQ(args.getUsage(), "foo");
}

GTEST_TEST(getUsage, compareOption) {
    mblet::Argparsor args(false);
    args.addArgument(args.vector("-h", "--help")).action(mblet::Argparsor::HELP).help("custom help option message");
    args.addArgument("NOTREQUIRED1").help("help of positional argument");
    args.addArgument("REQUIRED1").help("help of required1 positional argument").required(true);
    args.addArgument("REQUIRED2").help("help of required2 positional argument").required(true);
    args.addArgument("NOTREQUIRED2").help("help of positional argument");
    args.addArgument("-a").action(mblet::Argparsor::STORE_TRUE).help("help of a short option").required(true);
    args.addArgument("-b").action(mblet::Argparsor::STORE_TRUE).help("help of b short option");
    args.addArgument("-c").action(mblet::Argparsor::STORE_TRUE).help("help of c short option");
    args.addArgument("-d").action(mblet::Argparsor::STORE_TRUE).help("help of d short option").required(true);
    args.addArgument("--long1").action(mblet::Argparsor::STORE_TRUE).help("help of long1 option");
    args.addArgument("--long2").action(mblet::Argparsor::STORE_TRUE).help("help of long2 option").required(true);
    args.addArgument("--long3").action(mblet::Argparsor::STORE_TRUE).help("help of long3 option");
    args.addArgument("--long4").action(mblet::Argparsor::STORE_TRUE).help("help of long4 option");
    args.addArgument("--long5").action(mblet::Argparsor::STORE_TRUE).help("help of long5 option");
    args.addArgument("--long6").action(mblet::Argparsor::STORE_TRUE).help("help of long6 option").required(true);
    args.addArgument("-e").action(mblet::Argparsor::STORE_TRUE).help("help of e short option").required(true);
    args.addArgument("-f").action(mblet::Argparsor::STORE_TRUE).help("help of f short option");
    args.addArgument("-g").action(mblet::Argparsor::STORE_TRUE).help("help of g short option").required(true);

    std::ostringstream usage("");

    usage << "usage:  -a -d -e -g --long2 --long6 [-b] [-c] [-f] [-h] [--long1] [--long3] [--long4] [--long5] -- "
             "REQUIRED1 REQUIRED2 [NOTREQUIRED1] [NOTREQUIRED2]\n";
    usage << "\n";
    usage << "positional arguments:\n";
    usage << "  REQUIRED1     help of required1 positional argument (required)\n";
    usage << "  REQUIRED2     help of required2 positional argument (required)\n";
    usage << "  NOTREQUIRED1  help of positional argument\n";
    usage << "  NOTREQUIRED2  help of positional argument\n";
    usage << "\n";
    usage << "optional arguments:\n";
    usage << "  -a            help of a short option (required)\n";
    usage << "  -d            help of d short option (required)\n";
    usage << "  -e            help of e short option (required)\n";
    usage << "  -g            help of g short option (required)\n";
    usage << "  --long2       help of long2 option (required)\n";
    usage << "  --long6       help of long6 option (required)\n";
    usage << "  -b            help of b short option\n";
    usage << "  -c            help of c short option\n";
    usage << "  -f            help of f short option\n";
    usage << "  -h, --help    custom help option message\n";
    usage << "  --long1       help of long1 option\n";
    usage << "  --long3       help of long3 option\n";
    usage << "  --long4       help of long4 option\n";
    usage << "  --long5       help of long5 option\n";

    EXPECT_EQ(args.getUsage(), usage.str());
}

GTEST_TEST(getUsage, allTypeArgument) {
    mblet::Argparsor args;
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    // POSITIONNAL
    args.addArgument("REQUIRED").help("help of required positional argument").required(true);
    args.addArgument("NOTREQUIRED").help("help of positional argument").defaults("DEFAULT VALUE");
    // BOOL
    args.addArgument(args.vector("-b", "--bool")).action(mblet::Argparsor::STORE_TRUE).help("help of bool option");
    args.addArgument("--notbool").action(mblet::Argparsor::STORE_FALSE).help("help of notbool option");
    // SIMPLE
    args.addArgument(args.vector("-s", "--simple"))
        .help("help of simple option")
        .metavar("ArgOfSimple")
        .nargs(1)
        .defaults("0");
    // NUMBER
    args.addArgument("--number")
        .help("help of number option")
        .metavar("Arg1 Arg2")
        .nargs(2)
        .defaults(args.vector("0", "1"));
    // INFINITE
    args.addArgument("--infinite")
        .action(mblet::Argparsor::INFINITE)
        .help("help of infinite option")
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"));
    // NULTI
    args.addArgument("--multi")
        .action(mblet::Argparsor::APPEND)
        .help("help of multi option")
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI NUMBER
    args.addArgument("--multi-number")
        .action(mblet::Argparsor::APPEND)
        .help("help of multi number option")
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI INFINITE
    args.addArgument("--multi-infinite")
        .action(mblet::Argparsor::EXTEND)
        .help("help of multi-infinite option")
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"));
    // MULTI INFINITE NUMBER
    args.addArgument("--multi-infinite-number")
        .action(mblet::Argparsor::EXTEND)
        .help("help of multi-infinite-number option")
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"));

    std::ostringstream usage("");

    usage << "usage:  [-b] [-h] [-s ArgOfSimple] [--infinite INFINITE...] [--multi MULTI] [--multi-infinite "
             "MULTI-INFINITE] [--multi-infinite-number MULTI-INFINITE-NUMBER MULTI-INFINITE-NUMBER] [--multi-number "
             "MULTI-NUMBER MULTI-NUMBER] [--notbool] [--number Arg1 Arg2] -- REQUIRED [NOTREQUIRED]\n";
    usage << "\n";
    usage << "custom description message\n";
    usage << "\n";
    usage << "positional arguments:\n";
    usage << "  REQUIRED                                                             help of required positional "
             "argument (required)\n";
    usage << "  NOTREQUIRED                                                          help of positional argument "
             "(default: DEFAULT VALUE)\n";
    usage << "\n";
    usage << "optional arguments:\n";
    usage << "  -b, --bool                                                           help of bool option\n";
    usage << "  -h, --help                                                           show this help message and exit\n";
    usage << "  -s, --simple ArgOfSimple                                             help of simple option (default: "
             "0)\n";
    usage << "  --infinite INFINITE...                                               help of infinite option (default: "
             "0, 1, 2, 3)\n";
    usage << "  --multi MULTI                                                        help of multi option (default: 0, "
             "1, 2, 3)\n";
    usage << "  --multi-infinite MULTI-INFINITE                                      help of multi-infinite option "
             "(default: 0, 1, 2, 3)\n";
    usage << "  --multi-infinite-number MULTI-INFINITE-NUMBER MULTI-INFINITE-NUMBER  help of multi-infinite-number "
             "option (default: (0, 1), (2, 3))\n";
    usage << "  --multi-number MULTI-NUMBER MULTI-NUMBER                             help of multi number option "
             "(default: (0, 1), (2, 3))\n";
    usage << "  --notbool                                                            help of notbool option\n";
    usage << "  --number Arg1 Arg2                                                   help of number option (default: "
             "0, 1)\n";
    usage << "\n";
    usage << "custom epilog message\n";

    EXPECT_EQ(args.getUsage(), usage.str());
}