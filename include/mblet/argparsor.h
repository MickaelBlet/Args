/**
 * argparsor.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022 BLET Mickaël.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

  private:

    /**
     * @brief overide std::vector<std::string> with simple or table argument
     */
    struct Vector : public std::vector<std::string> {

        inline Vector() : std::vector<std::string>() {}

        template<std::size_t S>
        inline Vector(const char* (&v)[S]) : std::vector<std::string>() {
            for (std::size_t i = 0; i < S; ++i) {
                std::vector<std::string>::push_back(v[i]);
            }
        }

        template<std::size_t S>
        inline Vector(const char* const(&v)[S]) : std::vector<std::string>() {
            for (std::size_t i = 0; i < S; ++i) {
                std::vector<std::string>::push_back(v[i]);
            }
        }

        template<std::size_t S>
        inline Vector(const std::string(&v)[S]) : std::vector<std::string>() {
            for (std::size_t i = 0; i < S; ++i) {
                std::vector<std::string>::push_back(v[i]);
            }
        }

        template<std::size_t S>
        inline Vector(const char (&v)[S]) : std::vector<std::string>() {
            std::vector<std::string>::push_back(v);
        }

        inline Vector(const char* (&v)) : std::vector<std::string>() {
            std::vector<std::string>::push_back(v);
        }

        inline Vector(const std::string& v) : std::vector<std::string>() {
            std::vector<std::string>::push_back(v);
        }

#if __cplusplus >= 201103L
        inline Vector(const std::initializer_list<std::string>& l) : std::vector<std::string>(l) {}
#endif

    };

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
    class Argument : public std::vector<Argument> {

      public:

        enum Type {
            NONE = 0,
            BOOLEAN_OPTION,
            REVERSE_BOOLEAN_OPTION,
            SIMPLE_OPTION,
            NUMBER_OPTION,
            INFINITE_OPTION,
            MULTI_OPTION,
            MULTI_INFINITE_OPTION,
            MULTI_NUMBER_OPTION,
            MULTI_NUMBER_INFINITE_OPTION,
            POSITIONAL_ARGUMENT
        };

        /**
         * @brief Construct a new Argument object
         */
        Argument();

        /**
         * @brief Construct a new Argument object from argument
         */
        Argument(const char* arg);

        /**
         * @brief Copy a Argument object
         *
         * @param rhs
         */
        Argument(const Argument& rhs);

        /**
         * @brief Destroy the Argument object
         */
        virtual ~Argument();

        inline bool isExist() const {
            return _isExist;
        }

        inline bool isRequired() const {
            return _isRequired;
        }

        inline std::size_t count() const {
            return _count;
        }

        inline std::size_t nbArgs() const {
            return _nbArgs;
        }

        inline Type getType() const {
            return _type;
        }

        inline const std::string& getHelp() const {
            return _help;
        }

        inline const std::string& getArgHelp() const {
            return _argHelp;
        }

        inline const std::string& getArgument() const {
            return _argument;
        }

        inline const std::string& getDefault() const {
            return _default;
        }

        inline std::string str() const {
            if (_type == BOOLEAN_OPTION) {
                return ((_isExist) ? "true" : "false");
            }
            else if (_type == REVERSE_BOOLEAN_OPTION) {
                return ((_isExist) ? "false" : "true");
            }
            else {
                std::ostringstream oss("");
                if (!empty()) {
                    for (std::size_t i = 0 ; i < size() ; ++i) {
                        if (i > 0) {
                            oss << ", ";
                        }
                        if (!at(i).empty()) {
                            oss << "(";
                            for (std::size_t j = 0 ; j < at(i).size() ; ++j) {
                                if (j > 0) {
                                    oss << ", ";
                                }
                                oss << at(i).at(j)._argument;
                            }
                            oss << ")";
                        }
                        else {
                            oss << at(i)._argument;
                        }
                    }
                }
                else {
                    oss << _argument;
                }
                return oss.str();
            }
        }

        /**
         * @brief Override bool operator
         *
         * @return true if exist or false if not exist
         */
        inline operator bool() const {
            if (_type == REVERSE_BOOLEAN_OPTION) {
                return !_isExist;
            }
            else {
                return _isExist;
            }
        }

        /**
         * @brief tranform to string
         *
         * @return std::string
         */
        inline operator std::string() const {
            return str();
        }

        /**
         * @brief tranform to vector of string
         *
         * @return std::vector<std::string>
         */
        inline operator std::vector<std::string>() const {
            if (_type == NUMBER_OPTION || _type == MULTI_OPTION ||
                _type == INFINITE_OPTION || _type == MULTI_INFINITE_OPTION) {
                std::vector<std::string> ret;
                for (std::size_t i = 0 ; i < size() ; ++i) {
                    ret.push_back(at(i).getArgument());
                }
                return ret;
            }
            else {
                throw Exception("convertion to vector of string not authorized");
            }
        }

        /**
         * @brief tranform to vector of vector of string
         *
         * @return std::vector<std::vector<std::string> >
         */
        inline operator std::vector<std::vector<std::string> >() const {
            if (_type == MULTI_NUMBER_OPTION || _type == MULTI_NUMBER_INFINITE_OPTION) {
                std::vector<std::vector<std::string> > ret;
                for (std::size_t i = 0 ; i < size() ; ++i) {
                    ret.push_back(std::vector<std::string>());
                    for (std::size_t j = 0 ; j < at(i).size() ; ++j) {
                        ret[i].push_back(at(i).at(j).getArgument());
                    }
                }
                return ret;
            }
            else {
                throw Exception("convertion to vector of vector of string not authorized");
            }
        }

        /**
         * @brief overide brakcet operator
         *
         * @param index
         * @return const Argument&
         */
        inline const Argument& operator[](unsigned long index) const {
            return at(index);
        }

        /**
         * @brief Friend function for convert Argument object to ostream
         *
         * @param os
         * @param argument
         * @return std::ostream&
         */
        inline friend std::ostream& operator<<(std::ostream& os, const Argument& argument) {
            os << argument.str();
            return os;
        }

      private:

        friend class Argparsor;

        static bool compareOption(const Argument& first, const Argument& second);

        std::vector<std::string> _names;
        bool _isExist;
        bool _isRequired;
        std::size_t _count;
        std::size_t _nbArgs;
        enum Type _type;
        std::string _help;
        std::string _argHelp;
        std::string _argument;
        std::string _default;

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
     * @brief Get the Usage
     *
     * @return std::string
     */
    std::string getUsage() const;

    /**
     * @brief Get the Version
     *
     * @return std::string
     */
    std::string getVersion() const;

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& getArgument(const char* str) const {
        return getArgument(std::string(str));
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& getArgument(const std::string& str) const {
        std::map<std::string, Argument*>::const_iterator cit = _argumentFromName.find(str);
        if (cit == _argumentFromName.end()) {
            throw AccessDeniedException(str.c_str(), "argument not found");
        }
        return *(cit->second);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& operator[](const char* str) const {
        return getArgument(str);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& operator[](const std::string& str) const {
        return getArgument(str);
    }

    /**
     * @brief Get the vector of additional argument
     *
     * @return const std::vector<std::string>&
     */
    inline const std::vector<std::string>& getAdditionalArguments() const {
        return _additionalArguments;
    }

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
     * @brief Set the epilog in usage message
     *
     * @param epilog
     */
    inline void setEpilog(const char* epilog) {
        _epilog = epilog;
    }

    /**
     * @brief Convert argument strings to objects and assign them as attributes of the argparsor map.
     * Previous calls to add_argument() determine exactly what objects are created and how they are assigned
     * @param argc
     * @param argv
     * @param alternative active parsing for accept long option with only one '-' character
     * @param strict active exception if not all argument is used else you can take additionnal argument with
     *        getAdditionalArguments method
     */
    void parseArguments(int argc, char* argv[], bool alternative = false, bool strict = false);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     * @param actionOrDefault The basic type of action to be taken when this argument is encountered at the command line
     * action list: store_true, store_false, append, extend, version, help
     * @param help A brief description of what the argument does
     * @param isRequired Whether or not the command-line option may be omitted (optionals only)
     * @param argsHelp A name for the argument in usage messages
     * @param nbArgs The number of command-line arguments that should be consumed
     * @param defaultArgs The value produced if the argument is absent from the command line
     */
    void addArgument(const Vector& nameOrFlags, const char* actionOrDefault = NULL,
                     const char* help = NULL, bool isRequired = false, const char* argsHelp = NULL,
                     std::size_t nbArgs = 0, const Vector& defaultArgs = Vector());

    /**
     * @brief Constructor of Vector for cpp98
     *
     * @param v1
     * @param v2
     * @param v3
     * @param v4
     * @param v5
     * @param v6
     * @param v7
     * @param v8
     * @param v9
     * @param v10
     * @return Vector
     */
    inline static Vector vector(const char* v1 = NULL, const char* v2 = NULL, const char* v3 = NULL, const char* v4 = NULL,
                                const char* v5 = NULL, const char* v6 = NULL, const char* v7 = NULL, const char* v8 = NULL,
                                const char* v9 = NULL, const char* v10 = NULL) {
        const char* args[] = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
        Vector v;
        for (std::size_t i = 0; i < sizeof(args) / sizeof(*args); ++i) {
            if (args[i]) {
                v.push_back(args[i]);
            }
        }
        return v;
    }

  private:

    /**
     * @brief Get the short argument decompose multi short argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @param alternative
     */
    void parseShortArgument(int maxIndex, char* argv[], int* index, bool alternative);

    /**
     * @brief Get the long argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @param alternative
     */
    void parseLongArgument(int maxIndex, char* argv[], int* index, bool alternative);

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
     * @param alternative
     */
    void parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                       Argument* argument, bool alternative);

    /**
     * @brief Get the positionnal argument
     *
     * @param argv
     * @param index
     * @param strict
     */
    void parsePositionnalArgument(char* argv[], int* index, bool strict);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @param alternative
     * @return true
     * @return false
     */
    bool endOfInfiniteArgument(const char* argument, bool alternative);

    std::string _binaryName;

    std::list<Argument> _arguments;
    std::map<std::string, Argument*> _argumentFromName;

    Argument* _helpOption;
    Argument* _versionOption;

    std::string _usage;
    std::string _description;
    std::string _epilog;

    std::vector<std::string> _additionalArguments;
};

} // namespace mblet

#endif // _MBLET_ARGPARSOR_HPP_