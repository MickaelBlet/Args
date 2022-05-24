#ifndef _MBLET_OPTPARSOR_HPP_
#define _MBLET_OPTPARSOR_HPP_

#include <map>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>

namespace mblet {

/**
 * @brief Object for parse the main arguments
 */
class Optparsor {

  public:

    /**
     * @brief Basic exception from std::exception
     */
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

    /**
     * @brief Argument exception from Exception
     */
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

    /**
     * @brief Parse argument exception from ArgumentException
     */
    class ParseArgumentException : public ArgumentException {
      public:
        ParseArgumentException(const char* argument, const char* message) : ArgumentException(argument, message) {}
        virtual ~ParseArgumentException() throw() {}
    };

    /**
     * @brief Parse argument required exception from ParseArgumentException
     */
    class ParseArgumentRequiredException : public ParseArgumentException {
      public:
        ParseArgumentRequiredException(const char* argument, const char* message) : ParseArgumentException(argument, message) {}
        virtual ~ParseArgumentRequiredException() throw() {}
    };

    /**
     * @brief Get access denied exception from ArgumentException
     */
    class AccessDeniedException : public ArgumentException {
      public:
        AccessDeniedException(const char* argument, const char* message) : ArgumentException(argument, message) {}
        virtual ~AccessDeniedException() throw() {}
    };

    /**
     * @brief Option object
     */
    class Option {

      public:

        /**
         * @brief Argument object from std::string
         */
        class Argument : public std::string {
          public:

            /**
             * @brief Construct a new Argument object
             */
            Argument();

            /**
             * @brief Construct a new Argument object
             *
             * @param rhs
             */
            Argument(const Argument& rhs);

            /**
             * @brief Construct a new Argument object
             *
             * @param rhs
             */
            Argument(const std::string& rhs);

            /**
             * @brief Construct a new Argument object
             *
             * @param rhs
             */
            Argument(const char* const& rhs);

            /**
             * @brief Destroy the Argument object
             */
            virtual ~Argument();

            /**
             * @brief Get value from type
             *
             * @tparam T
             * @return T
             */
            template<typename T>
            inline T get() const {
                T retValue;
                std::stringstream stringStream("");
                valueToStream(stringStream);
                stringStream >> retValue;
                return retValue;
            }

          private:

            /**
             * @brief Insert value in stringstream
             *
             * @param stringStream
             */
            void valueToStream(std::ostream& stringStream) const;

        };

        enum Type {
            BOOLEAN_OPTION,
            SIMPLE_OPTION,
            NUMBER_OPTION,
            INFINITE_OPTION,
            MULTI_OPTION,
            POSITIONAL_ARGUMENT
        };

        /**
         * @brief Construct a new Option object
         */
        Option();

        /**
         * @brief Destroy the Option object
         */
        ~Option();

        /**
         * @brief Get arguments element at index
         *
         * @param index
         * @return const Argument&
         */
        inline const Argument& at(std::size_t index) const {
            if (arguments.size() < index) {
                if (!longName.empty()) {
                    throw AccessDeniedException(longName.c_str(), "out of range");
                }
                else {
                    throw AccessDeniedException(shortName.c_str(), "out of range");
                }
            }
            return arguments.at(index);
        }

        /**
         * @brief Get type of value
         *
         * @tparam T type of return
         * @return T
         */
        template<typename T>
        inline T get() const {
            T ret;
            switch (type) {
                case BOOLEAN_OPTION:
                    ret = isExist;
                    break;
                case SIMPLE_OPTION:
                case POSITIONAL_ARGUMENT:
                    if (!arguments.empty()) {
                        ret = arguments.begin()->get<T>();
                    }
                    break;
                default:
                    if (!longName.empty()) {
                        throw AccessDeniedException(longName.c_str(), "argument type can't read directly");
                    }
                    else {
                        throw AccessDeniedException(shortName.c_str(), "argument type can't read directly");
                    }
                    break;
            }
            return ret;
        }

        /**
         * @brief Get size of arguments
         *
         * @return std::size_t
         */
        inline std::size_t size() const {
            return arguments.size();
        }

        /**
         * @brief Tranform option to const string
         *
         * @return const char*
         */
        inline const char* c_str() const {
            static std::string retValue;
            switch (type) {
                case BOOLEAN_OPTION:
                    return (isExist) ? "true" : "false";
                    break;
                case SIMPLE_OPTION:
                case POSITIONAL_ARGUMENT:
                    if (arguments.size() > 0) {
                        return arguments.begin()->c_str();
                    }
                    else {
                        return "";
                    }
                    break;
                case NUMBER_OPTION:
                case MULTI_OPTION:
                case INFINITE_OPTION: {
                    std::ostringstream oss("");
                    for (std::size_t i = 0 ; i < arguments.size() ; ++i) {
                        if (i > 0) {
                            oss << ", ";
                        }
                        oss << arguments[i];
                    }
                    retValue = oss.str();
                    return retValue.c_str();
                    break;
                }
                default:
                    return "unknown";
                    break;
            }
        }

        /**
         * @brief Tranform option to const string
         *
         * @return const char*
         */
        inline const char* data() const {
            return c_str();
        }

        /**
         * @brief Override bool operator
         *
         * @return true if exist or false if not exist
         */
        inline operator bool() const {
            return isExist;
        }

        /**
         * @brief Override bracket operator
         *
         * @param index
         * @return const Argument&
         */
        inline const Argument& operator[](std::size_t index) const {
            return at(index);
        }

        /**
         * @brief Friend function for convert Option object to ostream
         *
         * @param os
         * @param option
         * @return std::ostream&
         */
        inline friend std::ostream& operator<<(std::ostream& os, const Option& option) {
            os << option.c_str();
            return os;
        }

        enum Type type;
        bool isExist;
        std::size_t count;
        bool isRequired;
        std::string shortName;
        std::string longName;
        std::string help;
        std::size_t nbArgs;
        std::string argHelp;
        std::vector<std::string> defaultValues;
        std::vector<Argument> arguments;
    };

    /**
     * @brief Construct a new Optparsor object
     */
    Optparsor();

    /**
     * @brief Destroy the Optparsor object
     */
    ~Optparsor();

    /**
     * @brief Get the bynary name
     *
     * @return const std::string&
     */
    inline const std::string& getBynaryName() const {
        return _binaryName;
    }

    /**
     * @brief Get the usage object
     *
     * @param oss
     * @return std::ostream&
     */
    std::ostream& getUsage(std::ostream& oss = std::cout);

    /**
     * @brief Get the option object
     *
     * @param str
     * @return const Option&
     */
    inline const Option& getOption(const char* str) const {
        std::map<std::string, Option*>::const_iterator cit = _optionFromName.find(str);
        if (cit == _optionFromName.end()) {
            throw AccessDeniedException(str, "option not found");
        }
        return *(cit->second);
    }

    /**
     * @brief Get the option object
     *
     * @param str
     * @return const Option&
     */
    inline const Option& getOption(const std::string& str) const {
        std::map<std::string, Option*>::const_iterator cit = _optionFromName.find(str);
        if (cit == _optionFromName.end()) {
            throw AccessDeniedException(str.c_str(), "option not found");
        }
        return *(cit->second);
    }

    /**
     * @brief Override bracket operator with getOption
     *
     * @param str
     * @return const Option&
     */
    inline const Option& operator[](const char* str) const {
        return getOption(str);
    }

    /**
     * @brief Override bracket operator with getOption
     *
     * @param str
     * @return const Option&
     */
    inline const Option& operator[](const std::string& str) const {
        return getOption(str);
    }

    /**
     * @brief Get the extra argument vector
     *
     * @return const std::vector<std::string>&
     */
    inline const std::vector<std::string>& getExtraArgument() const {
        return _extraArguments;
    }

    /**
     * @brief Set the help option
     *
     * @param shortName
     * @param longName
     * @param help
     */
    void setHelpOption(const char* shortName, const char* longName, const char* help);

    /**
     * @brief Set the usage message
     *
     * @param usage
     */
    inline void setUsage(const char* usage) {
        _usage = usage;
    }

    /**
     * @brief Set the description in usage message
     *
     * @param description
     */
    inline void setDescription(const char* description) {
        _description = description;
    }

    /**
     * @brief Activate exception when extra argument exist
     */
    inline void throwAtExtra(bool exceptionAtExtra) {
        _throwAtExtra = exceptionAtExtra;
    }

    /**
     * @brief Parse option and argument
     *
     * @param argc
     * @param argv
     */
    void parseArguments(int argc, char* argv[]);

    /**
     * @brief Add boolean option with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     */
    void addBooleanOption(const char* shortName, const char* longName = NULL, const char* help = NULL, bool isRequired = false);

    /**
     * @brief Add simple argument option with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param defaultValue
     */
    void addSimpleOption(const char* shortName, const char* longName = NULL, const char* help = NULL, bool isRequired = false,
                         const char* argHelp = NULL, const char* defaultValue = NULL);


    /**
     * @brief Add number argument option with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param nbArgs
     * @param ... default argument value (const char*)
     */
    void addNumberOption(const char* shortName, const char* longName = NULL, const char* help = NULL, bool isRequired = false,
                         const char* argHelp = NULL, std::size_t nbArgs = 0, ...);

    /**
     * @brief Add infinite argument option with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param nbDefaultArgs
     * @param ...
     */
    void addInfiniteOption(const char* shortName, const char* longName = NULL, const char* help = NULL, bool isRequired = false,
                           const char* argHelp = NULL, std::size_t nbDefaultArgs = 0, ...);

    /**
     * @brief Add multi option from short and long name with list argument
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param nbDefaultArgs
     * @param ...
     */
    void addMultiOption(const char* shortName, const char* longName = NULL, const char* help = NULL, bool isRequired = false,
                        const char* argHelp = NULL, std::size_t nbDefaultArgs = 0, ...);

    /**
     * @brief Add positionnal argument
     *
     * @param name
     * @param help
     * @param isRequired
     * @param argName
     * @param defaultValue
     */
    void addPositionalArgument(const char* name, const char* help = NULL, bool isRequired = false,
                                const char* defaultValue = NULL);

  private:

    /**
     * @brief Create a option with check format of shortName and longName
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @return Option&
     */
    Option& createOption(const char* shortName, const char* longName, const char* help, bool isRequired);

    /**
     * @brief Get the short option decompose multi short option
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @return true
     * @return false
     */
    void getShortOption(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the long option
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void getLongOption(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the positionnal argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void getPositionnalArgument(int maxIndex, char* argv[], int* index);

    std::string _binaryName;

    std::list<Option> _options;
    std::map<std::string, Option*> _optionFromName;

    Option* _helpOption;

    std::string _usage;
    std::string _description;

    bool _throwAtExtra;
    std::vector<std::string> _extraArguments;
};

} // namespace mblet

#endif // _MBLET_Optparsor_HPP_