#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("ARG").help("custom argument message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const mblet::Argparsor::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additionnal argument(s):" << std::endl;
        for (std::size_t i = 0; i < args.getAdditionalArguments().size(); ++i) {
            std::cout << args.getAdditionalArguments()[i] << std::endl;
        }
    }

    return 0;
}