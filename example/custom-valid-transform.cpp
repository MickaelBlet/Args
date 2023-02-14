#include <iostream>
#include <sstream>

#include "mblet/argparsor.h"

class ValidCustom : public mblet::Argparsor::IValid {
  public:
    ValidCustom(const std::string& prefix, const std::string& suffix) :
        _prefix(prefix),
        _suffix(suffix) {}
    ~ValidCustom() {}

    bool isValid(std::vector<std::string>& arguments) {
        for (std::size_t i = 0; i < arguments.size(); ++i) {
            if (arguments[i] == _prefix) {
                arguments[i] += _suffix;
            }
            else {
                std::ostringstream oss("");
                oss << "\"" << arguments[i] << "\" is not \"" << _prefix << "\"";
                throw mblet::Argparsor::ParseArgumentValidException(oss.str().c_str());
            }
        }
        return true;
    }

  private:
    std::string _prefix;
    std::string _suffix;
};

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    // Add suffix on arguments if argument is "foo"
    args.addArgument("--option").help("custom option message").valid(new ValidCustom("foo", "bar")).required(true);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
    }
    catch (const mblet::Argparsor::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    return 0;
}