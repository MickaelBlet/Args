#ifndef _MBLET_OPTPARSOR_HPP_
#define _MBLET_OPTPARSOR_HPP_

#include <map>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <cstdarg>

#if __cplusplus < 201103L

// max 19 args
#define MBLET_NARGS_SEQ(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _0, N, ...) N
#define MBLET_NARGS(...) MBLET_NARGS_SEQ(__VA_ARGS__, 0, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define MBLET_PRE_NARGS(...) MBLET_NARGS(__VA_ARGS__)
#define MBLET_NOARGS() 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19
#define MBLET_NARG(...) MBLET_PRE_NARGS(MBLET_NOARGS __VA_ARGS__ ())

// create a temporary vector in c++98
#define MBLET_OPT_VECTOR(...) ::mblet::Optparsor::make_vector(MBLET_NARG(__VA_ARGS__), "" __VA_ARGS__ "")

#endif

namespace mblet {

/**
 * @brief Object for parse the main arguments
 */
class Optparsor {

  public:

#if __cplusplus < 201103L
    /**
     * @brief Custom class from create a vector from va_list
     */
    class make_vector : public std::vector<const char *> {
      public:
        /**
         * @brief Construct a new vector object from va_list
         *
         * @param nbArg
         * @param ...
         */
        make_vector(std::size_t nbArg, ...) : std::vector<const char *>() {
            va_list pa;
            va_start(pa, nbArg);
            for (std::size_t i = 0 ; i < nbArg ; ++i) {
                this->push_back(va_arg(pa, const char *));
            }
            va_end(pa);
        }

        /**
         * @brief Destroy the make vector object
         */
        virtual ~make_vector() {}
    };
#endif

    class Exception : public std::exception {
      public:
        Exception(const char* str) : _str(str) {}
        virtual ~Exception() throw() {}
        const char* what() const throw() { return _str.c_str(); }
      protected:
        std::string _str;
    };

    class ArgumentException : public Exception {
      public:
        ArgumentException(const char* argument, const char* message) : Exception(message), _argument(argument) {}
        virtual ~ArgumentException() throw() {}
        const char* argument() const throw() { return _argument.c_str(); }
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

        bool isExist;
        bool isRequired;
        enum Type type;
        std::string shortName;
        std::string longName;
        std::string help;
        std::size_t nbArgs;
        std::vector<std::string> usageNames;
        std::vector<std::string> defaultValues;
        std::vector<std::string> arguments;

        inline operator bool() const {
            return isExist;
        }

        inline const std::string& operator[](std::size_t index) const {
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
     * @param nbArgs
     * @param usageNames
     * @param defaultValues
     */
    void addOption(const char* shortName, const char* longName, const char* help, bool isRequired = false,
        std::size_t nbArgs = 0,
        const std::vector<const char *>& usageNames = std::vector<const char *>(),
        const std::vector<const char *>& defaultValues = std::vector<const char *>());

    /**
     * @brief
     *
     * @param name
     * @param help
     * @param isRequired
     * @param argName
     * @param defaultValue
     */
    void addArgument(const char* name, const char* help, bool isRequired = false, const char* usageName = NULL, const char* defaultValue = NULL);

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