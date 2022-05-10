#ifndef _MBLET_OPTPARSOR_HPP_
#define _MBLET_OPTPARSOR_HPP_

#include <map>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <cstdarg>
#include <cstdlib>

namespace mblet {

/**
 * @brief Object for parse the main arguments
 */
class Optparsor {

  public:

    class Exception : public std::exception {
      public:
        Exception(const char* str) : _str(str) {}
        virtual ~Exception() throw() {}
        const char* what() const throw() {
            return _str.c_str();
        }
      protected:
        std::string _str;
    };

    class ArgumentException : public Exception {
      public:
        ArgumentException(const char* argument, const char* message) : Exception(message), _argument(argument) {}
        virtual ~ArgumentException() throw() {}
        const char* argument() const throw() {
            return _argument.c_str();
        }
      private:
        std::string _argument;
    };

    class ParseArgumentException : public ArgumentException {
      public:
        ParseArgumentException(const char* argument, const char* message) : ArgumentException(argument, message) {}
        virtual ~ParseArgumentException() throw() {}
    };

    class ParseArgumentRequiredException : public ParseArgumentException {
      public:
        ParseArgumentRequiredException(const char* argument, const char* message) : ParseArgumentException(argument, message) {}
        virtual ~ParseArgumentRequiredException() throw() {}
    };

    struct Option {
        enum Type {
            OPTION,
            ARGUMENT
        };

        struct Argument : public std::string {
            Argument() : std::string() {}
            Argument(const Argument& rhs) : std::string(rhs) {}
            Argument(const std::string& rhs) : std::string(rhs) {}
            Argument(const char* const& rhs) : std::string(rhs) {}
            virtual ~Argument() {}
            template<typename T>
            T get() const {
                T retValue;
                std::stringstream stringStream("");
                valueToStream(stringStream);
                stringStream >> retValue;
                return retValue;
            }

            void valueToStream(std::ostream& stringStream) const {
                std::size_t index = 0;

                if (c_str()[index] == '-' || c_str()[index] == '+') {
                    ++index;
                }
                // is hex
                if (c_str()[index] == '0' && c_str()[index + 1] == 'x') {
                    stringStream << strtoll(c_str(), NULL, 16);
                }
                // is binary
                else if (c_str()[index] == '0' && c_str()[index + 1] == 'b') {
                    stringStream << strtoull(c_str() + index + 2, NULL, 2);
                }
                // is octal
                else if (c_str()[index] == '0' && find('.') == std::string::npos) {
                    stringStream << strtoll(c_str(), NULL, 8);
                }
                // is bool
                else if (*this == "TRUE" || *this == "True" || *this == "true" ||
                        *this == "ON"   || *this == "On"   || *this == "on"   ||
                        *this == "YES"  || *this == "Yes"  || *this == "yes") {
                    stringStream << true;
                }
                else if (*this == "FALSE" || *this == "False" || *this == "false" ||
                        *this == "OFF"   || *this == "Off"   || *this == "off"   ||
                        *this == "NO"    || *this == "No"    || *this == "no") {
                    stringStream << false;
                }
                else {
                    stringStream << *this;
                }
            }
        };

        bool isExist;
        bool isRequired;
        enum Type type;
        std::string shortName;
        std::string longName;
        std::string help;
        std::size_t nbArgs;
        std::string usageName;
        std::vector<std::string> defaultValues;
        std::vector<Argument> arguments;

        inline operator bool() const {
            return isExist;
        }

        inline const Argument& operator[](std::size_t index) const {
            return arguments[index];
        }

        inline std::size_t size() const {
            return arguments.size();
        }

        inline const std::string& toString() const {
            return *(arguments.begin());
        }

        inline const char* c_str() const {
            return toString().c_str();
        }

        inline friend std::ostream& operator<<(std::ostream& os, const Option& option) {
            os << option.toString();
            return os;
        }
    };

    Optparsor();
    ~Optparsor();

    /**
     * @brief Get the Bynary Name
     *
     * @return const std::string&
     */
    inline const std::string& getBynaryName() const {
        return _binaryName;
    }

    std::ostream& getUsage(std::ostream& oss = std::cout) const;

    inline const std::vector<std::string>& getExtraArgument() const {
        return _extraArguments;
    }

    inline const Option& getOption(const char* str) {
        return *(_optionFromName.at(str));
    }
    inline const Option& getOption(const std::string& str) {
        return *(_optionFromName.at(str));
    }

    inline const Option& operator[](const char* str) {
        return *(_optionFromName.at(str));
    }
    inline const Option& operator[](const std::string& str) {
        return *(_optionFromName.at(str));
    }

    /**
     * @brief parse option and argument
     *
     * @param argc
     * @param argv
     */
    void parseArguments(int argc, char* argv[]);

    /**
     * @brief add option from short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param usageName
     * @param nbArgs
     * @param ...
     */
    void addOption(const char* shortName, const char* longName, const char* help, bool isRequired = false,
                   const char* usageName = NULL,
                   std::size_t nbArgs = 0,
                   ...);

    /**
     * @brief
     *
     * @param name
     * @param help
     * @param isRequired
     * @param argName
     * @param defaultValue
     */
    void addArgument(const char* name, const char* help, bool isRequired = false, const char* usageName = NULL,
                     const char* defaultValue = NULL);

    void extraUsage(const char* extraUsageMessage);

  private:

    bool getShortOption(int argc, char* argv[], int* index);
    bool getLongOption(int argc, char* argv[], int* index);
    bool getArgument(int argc, char* argv[], int* index);

    std::string _binaryName;

    std::list<Option> _options;
    std::map<std::string, Option*> _optionFromName;

    std::vector<std::string> _extraArguments;

    std::string _extraUsage;

};

} // namespace mblet

#endif // _MBLET_Optparsor_HPP_