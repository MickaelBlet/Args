#include <iostream>

#include "blet/args.h"

#define LOREM_IPSUM                                                                                                    \
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "   \
    "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo "  \
    "consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "         \
    "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est " \
    "laborum."

int main(int /*argc*/, char* /*argv*/[]) {
    blet::Args args;
    args.addArgument("ARGUMENT").help(LOREM_IPSUM).required(true);
    args.addArgument("--option0").help(LOREM_IPSUM).metavar("LOREM IPSUM");
    args.addArgument("--option1");
    args.addArgument("--option2");
    args.addArgument("--option3");
    args.addArgument("--option4");
    args.addArgument("--option5");
    args.addArgument("--option6");
    args.addArgument("--option7");
    args.addArgument("--option8");
    args.addArgument("--option9");
    args.setUsageWidth(2, 20, 2, 56); // default
    std::cout << args.getUsage() << std::endl;
    args.setUsageWidth(2, 30, 2, 15);
    std::cout << args.getUsage() << std::endl;
    args.setUsageWidth(1, 21, 1, 30);
    std::cout << args.getUsage() << std::endl;
}