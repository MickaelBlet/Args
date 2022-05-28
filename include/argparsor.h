#ifndef _MBLET_ARGPARSOR_HPP_
#define _MBLET_ARGPARSOR_HPP_

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
class Argparsor {

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
      protected:
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
     * @brief Argument object
     */
    class Argument {

      public:

        /**
         * @brief String object from std::string
         */
        class String : public std::string {
          public:

            /**
             * @brief Construct a new String object
             *
             * @param rhs
             */
            String(const String& rhs);

            /**
             * @brief Construct a new String object
             *
             * @param rhs
             */
            String(const char* const& rhs);

            /**
             * @brief Destroy the String object
             */
            virtual ~String();

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
         * @brief Construct a new Argument object
         */
        Argument();

        /**
         * @brief Destroy the Argument object
         */
        ~Argument();

        /**
         * @brief Get arguments element at index
         *
         * @param index
         * @return const String&
         */
        inline const String& at(std::size_t index) const {
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
         * @brief Tranform argument to const string
         *
         * @return std::string
         */
        inline std::string str() const {
            switch (type) {
                case BOOLEAN_OPTION:
                    return (isExist) ? "true" : "false";
                    break;
                case SIMPLE_OPTION:
                case POSITIONAL_ARGUMENT:
                    if (arguments.size() > 0) {
                        return *(arguments.begin());
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
                    return oss.str();
                    break;
                }
                default:
                    return "unknown";
                    break;
            }
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
         * @return const String&
         */
        inline const String& operator[](std::size_t index) const {
            return at(index);
        }

        /**
         * @brief Friend function for convert String object to ostream
         *
         * @param os
         * @param arg
         * @return std::ostream&
         */
        inline friend std::ostream& operator<<(std::ostream& os, const Argument& arg) {
            os << arg.str();
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
        std::vector<String> arguments;
    };

    /**
     * @brief Construct a new Argparsor object
     */
    Argparsor();

    /**
     * @brief Destroy the Argparsor object
     */
    ~Argparsor();

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
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& getOption(const char* str) const {
        std::map<std::string, Argument*>::const_iterator cit = _argumentFromName.find(str);
        if (cit == _argumentFromName.end()) {
            throw AccessDeniedException(str, "option not found");
        }
        return *(cit->second);
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& getOption(const std::string& str) const {
        return getOption(str.c_str());
    }

    /**
     * @brief Override bracket operator with getOption
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& operator[](const char* str) const {
        return getOption(str);
    }

    /**
     * @brief Override bracket operator with getOption
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& operator[](const std::string& str) const {
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
     * @brief Set the help argument
     *
     * @param shortName
     * @param longName
     * @param help
     */
    void setHelpArgument(const char* shortName = NULL, const char* longName = NULL, const char* help = NULL);

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
     * @brief Parse arguments
     *
     * @param argc
     * @param argv
     */
    void parseArguments(int argc, char* argv[]);

    /**
     * @brief Add boolean argument with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     */
    void addBooleanArgument(const char* shortName, const char* longName = NULL, const char* help = NULL,
                            bool isRequired = false);

    /**
     * @brief Add simple argument with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param defaultValue
     */
    void addSimpleArgument(const char* shortName, const char* longName = NULL, const char* help = NULL,
                           bool isRequired = false,
                           const char* argHelp = NULL, const char* defaultValue = NULL);


    /**
     * @brief Add number argument with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param nbArgs
     * @param ... default argument value (const char*)
     */
    void addNumberArgument(const char* shortName, const char* longName = NULL, const char* help = NULL,
                           bool isRequired = false,
                           const char* argHelp = NULL, std::size_t nbArgs = 0, ...);

    /**
     * @brief Add infinite argument with short and long name
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param nbDefaultArgs
     * @param ...
     */
    void addInfiniteArgument(const char* shortName, const char* longName = NULL, const char* help = NULL,
                             bool isRequired = false,
                             const char* argHelp = NULL, std::size_t nbDefaultArgs = 0, ...);

    /**
     * @brief Add multi argument from short and long name with list argument
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @param argHelp
     * @param nbDefaultArgs
     * @param ...
     */
    void addMultiArgument(const char* shortName, const char* longName = NULL, const char* help = NULL,
                          bool isRequired = false,
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
     * @brief Create a argument with check format of shortName and longName
     *
     * @param shortName
     * @param longName
     * @param help
     * @param isRequired
     * @return Argument&
     */
    Argument& createArgument(const char* shortName, const char* longName, const char* help, bool isRequired);

    /**
     * @brief Get the short argument decompose multi short argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @return true
     * @return false
     */
    void parseShortArgument(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the long argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void parseLongArgument(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @param hasArg
     * @param option
     * @param arg
     * @param argument
     */
    void parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                       Argument* argument);

    /**
     * @brief Get the positionnal argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void parsePositionnalArgument(int maxIndex, char* argv[], int* index);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @return true
     * @return false
     */
    bool endOfInfiniteArgument(const char* argument);

    std::string _binaryName;

    std::list<Argument> _arguments;
    std::map<std::string, Argument*> _argumentFromName;

    Argument* _helpOption;

    std::string _usage;
    std::string _description;

    bool _throwAtExtra;
    std::vector<std::string> _extraArguments;
};

} // namespace mblet

#endif // _MBLET_ARGPARSOR_HPP_