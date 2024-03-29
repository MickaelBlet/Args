#include <iostream>
#include <sstream>

#include "blet/args.h"

class ValidCustom : public blet::Args::IValid {
  public:
    ValidCustom(const std::string& prefix, const std::string& suffix) :
        prefix_(prefix),
        suffix_(suffix) {}
    ~ValidCustom() {}

    bool isValid(std::vector<std::string>& arguments) {
        for (std::size_t i = 0; i < arguments.size(); ++i) {
            if (arguments[i] == prefix_) {
                arguments[i] += suffix_;
            }
            else {
                std::ostringstream oss("");
                oss << "\"" << arguments[i] << "\" is not \"" << prefix_ << "\"";
                throw blet::Args::ParseArgumentValidException(oss.str().c_str());
            }
        }
        return true;
    }

  private:
    std::string prefix_;
    std::string suffix_;
};

int main(int argc, char* argv[]) {
    blet::Args args;
    // Add suffix on arguments if argument is "foo"
    args.addArgument("--option").help("custom option message").valid(new ValidCustom("foo", "bar")).required(true);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    return 0;
}
