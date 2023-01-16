#include <iostream>
#include <sstream>

#include "mblet/argparsor.h"

// Add suffix on arguments if argument is "foo"
class ValidCustom : public mblet::Argparsor::IValid {
  public:
    ValidCustom(const std::string& suffix) :
        _suffix(suffix) {}
    ~ValidCustom() {}

    bool isValid(std::vector<std::string>& arguments) {
        for (std::size_t i = 0; i < arguments.size(); ++i) {
            if (arguments[i] == "foo") {
                arguments[i] += _suffix;
            }
            else {
                std::ostringstream oss("");
                oss << "\"" << arguments[i] << "\" is not \"foo\"";
                throw mblet::Argparsor::ParseArgumentValidException(oss.str().c_str());
            }
        }
        return true;
    }

  private:
    std::string _suffix;
};

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("--option").help("custom option message").valid(new ValidCustom("bar")).required(true);
    try {
        args.parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
        return 0;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }
}