#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.setVersion("multi line\nVersion: 0.0.0");
    args.addArgument("-v").flag("--version").action(args.VERSION).help("custom help version message");
    args.parseArguments(argc, argv);
    std::cout << "do nothing" << std::endl;
    return 0;
}