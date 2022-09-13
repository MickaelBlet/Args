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


#ifndef _MBLET_ARGPARSOR_H_
#define _MBLET_ARGPARSOR_H_

#include <map>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

#include "mblet/argparsor-exception.h"
#include "mblet/argparsor-vector.h"
#include "mblet/argparsor-valid.h"

namespace mblet {

namespace argparsor {

/**
 * @brief Object for parse the main arguments
 */
class Argparsor {

  public:

    enum Action {
        NONE,
        HELP,
        VERSION,
        STORE_TRUE,
        STORE_FALSE,
        APPEND,
        EXTEND,
        INFINITE
    };

    class ArgumentElement : public std::vector<ArgumentElement> {

        friend class Argparsor;

      public:

        ArgumentElement() :
            std::vector<ArgumentElement>(),
            _isNumber(false),
            _number(0.0)
        {}
        ArgumentElement(const ArgumentElement& rhs) :
            std::vector<ArgumentElement>(rhs),
            _argument(rhs._argument),
            _default(rhs._default),
            _isNumber(rhs._isNumber),
            _number(rhs._number)
        {}
        ArgumentElement(const char* arg_, const char* default_) : _argument(arg_), _default(default_) {}
        ArgumentElement(const char* arg) : _argument(arg) {}
        ~ArgumentElement() {};

        const std::string& getString() const {
            return _argument;
        }

        const std::string& getDefault() const {
            return _default;
        }

        bool isNumber() const {
            return _isNumber;
        }

        double getNumber() const {
            if (!_isNumber) {
                throw Exception("is not a number");
            }
            else {
                return _number;
            }
        }

        /**
         * @brief tranform to vector of string
         *
         * @return std::vector<std::string>
         */
        inline operator std::vector<std::string>() const {
            if (!empty() && front().empty()) {
                std::vector<std::string> ret;
                for (std::size_t i = 0 ; i < size() ; ++i) {
                    ret.push_back(at(i)._argument);
                }
                return ret;
            }
            else {
                throw Exception("convertion to vector of string not authorized");
            }
        }

        /**
         * @brief Friend function for convert Argument object to ostream
         *
         * @param os
         * @param argument
         * @return std::ostream&
         */
        inline friend std::ostream& operator<<(std::ostream& os, const ArgumentElement& argument) {
            os << argument.getString();
            return os;
        }

      protected:

        std::string _argument;
        std::string _default;
        bool _isNumber;
        double _number;

    };

    /**
     * @brief Argument object
     */
    class Argument : public ArgumentElement {

        friend class Argparsor;

      public:

        /**
         * @brief Construct a new Argument object
         */
        Argument(Argparsor& argparsor) :
            ArgumentElement(),
            _argparsor(argparsor),
            _nameOrFlags(),
            _type(NONE),
            _isExist(false),
            _isRequired(false),
            _count(0),
            _nargs(0),
            _help(),
            _metavar(),
            _valid(NULL),
            _this(NULL),
            _action(Argparsor::NONE),
            _defaults()
        {}

        /**
         * @brief Copy a Argument object
         *
         * @param rhs
         */
        Argument(const Argument& rhs) :
            ArgumentElement(rhs),
            _argparsor(rhs._argparsor),
            _nameOrFlags(rhs._nameOrFlags),
            _type(rhs._type),
            _isExist(rhs._isExist),
            _isRequired(rhs._isRequired),
            _count(rhs._count),
            _nargs(rhs._nargs),
            _help(rhs._help),
            _metavar(rhs._metavar),
            _valid(rhs._valid),
            _this(rhs._this),
            _action(rhs._action),
            _defaults()
        {}

        /**
         * @brief Destroy the Argument object
         */
        virtual ~Argument() {}

        inline bool isExist() const {
            return _isExist;
        }

        inline bool isRequired() const {
            return _isRequired;
        }

        inline std::size_t count() const {
            return _count;
        }

        inline std::size_t getNargs() const {
            return _nargs;
        }

        inline const std::string& getHelp() const {
            return _help;
        }

        inline const std::string& getMetavar() const {
            return _metavar;
        }

        inline std::string getString() const {
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
            return getString();
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
                    ret.push_back(at(i)._argument);
                }
                return ret;
            }
            else if (_type == MULTI_NUMBER_OPTION || _type == MULTI_NUMBER_INFINITE_OPTION) {
                std::vector<std::string> ret;
                for (std::size_t i = 0 ; i < size() ; ++i) {
                    for (std::size_t j = 0 ; j < at(i).size() ; ++j) {
                        ret.push_back(at(i).at(j)._argument);
                    }
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
                        ret[i].push_back(at(i).at(j)._argument);
                    }
                }
                return ret;
            }
            else {
                throw Exception("convertion to vector of vector of string not authorized");
            }
        }

        template<typename T>
        inline operator T() const {
            return getNumber();
        }

        /**
         * @brief overide brakcet operator
         *
         * @param index
         * @return const Argument&
         */
        inline const ArgumentElement& operator[](unsigned long index) const {
            return at(index);
        }

        /**
         * @brief Option strings, e.g. -f, --foo
         * @param flag_
         * @return this reference
         */
        inline Argument& flag(const char* flag_) {
            _argparsor.validFlag(flag_);
            _nameOrFlags.push_back(flag_);
            _sortNameOrFlags();
            _argparsor._argumentFromName.insert(std::pair<std::string, Argument**>(flag_, _this));
            _argparsor._arguments.sort(&Argument::compareOption);
            return *this;
        }

        /**
         * @brief The basic type of action to be taken when this argument is encountered at the command line
         * @param action_
         * @return this reference
         */
        inline Argument& action(enum Action action_) {
            _action = action_;
            _typeConstructor();
            _defaultsConstructor();
            return *this;
        }

        /**
         * @brief A brief description of what the argument does
         * @param help_
         * @return this reference
         */
        inline Argument& help(const char* help_) {
            _help = help_;
            return *this;
        }

        /**
         * @brief Whether or not the command-line option may be omitted (optionals only)
         * @param required_
         * @return this reference
         */
        inline Argument& required(bool required_) {
            _isRequired = required_;
            return *this;
        }

        /**
         * @brief A name for the argument in usage messages
         * @param metavar_
         * @return this reference
         */
        inline Argument& metavar(const char* metavar_) {
            _metavar = metavar_;
            return *this;
        }

        /**
         * @brief The number of command-line arguments that should be consumed
         * @param nargs_
         * @return this reference
         */
        inline Argument& nargs(std::size_t nargs_) {
            _nargs = nargs_;
            _typeConstructor();
            _defaultsConstructor();
            return *this;
        }

        /**
         * @brief The value produced if the argument is absent from the command line
         * @param defaults_
         * @return this reference
         */
        inline Argument& defaults(const Vector& defaults_) {
            _defaults = defaults_;
            _defaultsConstructor();
            return *this;
        }

        /**
         * @brief New object from IValid interface
         * @param pValid
         * @return this reference
         */
        inline Argument& valid(IValid* pValid) {
            if (_valid != NULL) {
                delete _valid;
            }
            _valid = pValid;
            return *this;
        }

        /**
         * @brief define a reference of object for insert the value after parseArguments method
         *
         * @tparam T
         * @param dest
         * @return reference of new argument
         */
        template<typename T>
        inline Argument& dest(std::vector<T>& dest) {
            Argument* argumentType = new ArgumentVectorType<T>(this, dest);
            return *argumentType;
        }

        template<typename T>
        inline Argument& dest(std::vector<std::vector<T> >& dest) {
            Argument* argumentType = new ArgumentVectorVectorType<T>(this, dest);
            return *argumentType;
        }

        /**
         * @brief define a reference of object for insert the value after parseArguments method
         *
         * @tparam T
         * @param dest
         * @return reference of new argument
         */
        template<typename T>
        inline Argument& dest(T& dest) {
            Argument* argumentType = new ArgumentType<T>(this, dest);
            return *argumentType;
        }

        /**
         * @brief Friend function for convert Argument object to ostream
         *
         * @param os
         * @param argument
         * @return std::ostream&
         */
        inline friend std::ostream& operator<<(std::ostream& os, const Argument& argument) {
            os << argument.getString();
            return os;
        }

      private:

        enum Type {
            NONE = 0,
            HELP_OPTION,
            VERSION_OPTION,
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

        virtual inline void _toDest() {
            /* do nothing */
        }

        inline void _toNumber() {
            if (_type == BOOLEAN_OPTION || _type == REVERSE_BOOLEAN_OPTION) {
                return ;
            }
            else {
                if (!empty()) {
                    for (std::size_t i = 0 ; i < size() ; ++i) {
                        if (!at(i).empty()) {
                            for (std::size_t j = 0 ; j < at(i).size() ; ++j) {
                                std::stringstream ss(at(i).at(j)._argument);
                                at(i).at(j)._isNumber = static_cast<bool>(ss >> at(i).at(j)._number);
                            }
                        }
                        else {
                            std::stringstream ss(at(i)._argument);
                            at(i)._isNumber = static_cast<bool>(ss >> at(i)._number);
                        }
                    }
                }
                else {
                    std::stringstream ss(_argument);
                    _isNumber = static_cast<bool>(ss >> _number);
                }
            }
        }

        std::string _metavarDefault();

        void _typeConstructor();

        void _defaultsConstructor();

        void _sortNameOrFlags(void);

        static bool compareOption(const Argument* first, const Argument* second);

        Argparsor& _argparsor;

        std::vector<std::string> _nameOrFlags;
        enum Type _type;
        bool _isExist;
        bool _isRequired;
        std::size_t _count;
        std::size_t _nargs;
        std::string _help;
        std::string _metavar;
        IValid* _valid;

        Argument** _this;
        enum Action _action;
        std::vector<std::string> _defaults;

    };

    template<typename T>
    class ArgumentType : public Argument {

      public:

        ArgumentType(Argument* argument, T& dest) : Argument(*argument), _dest(dest) {
            delete argument;
            *_this = this;
        }
        virtual ~ArgumentType() {}

      private:

        void _toDest() {
            std::stringstream ss("");
            if (_type == BOOLEAN_OPTION) {
                ss << _isExist;
            }
            else if (_type == REVERSE_BOOLEAN_OPTION) {
                ss << !_isExist;
            }
            else if (_isNumber) {
                ss << _number;
            }
            else {
                ss << _argument;
            }
            ss >> _dest;
        }

        T& _dest;
    };

    template<typename T>
    class ArgumentVectorType : public Argument {

      public:

        ArgumentVectorType(Argument* argument, std::vector<T>& dest) : Argument(*argument), _dest(dest) {
            delete argument;
            *_this = this;
        }
        virtual ~ArgumentVectorType() {}

      private:

        void _toDest() {
            if (!empty()) {
                for (std::size_t i = 0 ; i < size() ; ++i) {
                    if (!at(i).empty()) {
                        for (std::size_t j = 0 ; j < at(i).size() ; ++j) {
                            T dest;
                            std::stringstream ss("");
                            if (at(i).at(j)._isNumber) {
                                ss << at(i).at(j)._number;
                            }
                            else {
                                ss << at(i).at(j)._argument;
                            }
                            ss >> dest;
                            _dest.push_back(dest);
                        }
                    }
                    else {
                        T dest;
                        std::stringstream ss("");
                        if (at(i)._isNumber) {
                            ss << at(i)._number;
                        }
                        else {
                            ss << at(i)._argument;
                        }
                        ss >> dest;
                        _dest.push_back(dest);
                    }
                }
            }
            else {
                T dest;
                std::stringstream ss("");
                if (_type == BOOLEAN_OPTION) {
                    ss << _isExist;
                }
                else if (_type == REVERSE_BOOLEAN_OPTION) {
                    ss << !_isExist;
                }
                else if (_isNumber) {
                    ss << _number;
                }
                else {
                    ss << _argument;
                }
                ss >> dest;
                _dest.push_back(dest);
            }

        }

        std::vector<T>& _dest;
    };

    template<typename T>
    class ArgumentVectorVectorType : public Argument {

      public:

        ArgumentVectorVectorType(Argument* argument, std::vector<std::vector<T> >& dest) : Argument(*argument), _dest(dest) {
            delete argument;
            *_this = this;
        }
        virtual ~ArgumentVectorVectorType() {}

      private:

        void _toDest() {
            if (!empty()) {
                for (std::size_t i = 0 ; i < size() ; ++i) {
                    std::vector<T> vectorDest;
                    if (!at(i).empty()) {
                        for (std::size_t j = 0 ; j < at(i).size() ; ++j) {
                            T dest;
                            std::stringstream ss("");
                            if (at(i).at(j)._isNumber) {
                                ss << at(i).at(j)._number;
                            }
                            else {
                                ss << at(i).at(j)._argument;
                            }
                            ss >> dest;
                            vectorDest.push_back(dest);
                        }

                    }
                    else {
                        T dest;
                        std::stringstream ss("");
                        if (at(i)._isNumber) {
                            ss << at(i)._number;
                        }
                        else {
                            ss << at(i)._argument;
                        }
                        ss >> dest;
                        vectorDest.push_back(dest);
                    }
                    _dest.push_back(vectorDest);
                }
            }
            else {
                T dest;
                std::stringstream ss("");
                if (_type == BOOLEAN_OPTION) {
                    ss << _isExist;
                }
                else if (_type == REVERSE_BOOLEAN_OPTION) {
                    ss << !_isExist;
                }
                else if (_isNumber) {
                    ss << _number;
                }
                else {
                    ss << _argument;
                }
                ss >> dest;
                std::vector<T> vectorDest;
                vectorDest.push_back(dest);
                _dest.push_back(vectorDest);
            }

        }

        std::vector<std::vector<T> >& _dest;
    };

    /**
     * @brief Construct a new Argparsor object
     */
    Argparsor(bool help);

    /**
     * @brief Destroy the Argparsor object
     */
    virtual ~Argparsor();

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
        std::map<std::string, Argument**>::const_iterator cit = _argumentFromName.find(str);
        if (cit == _argumentFromName.end()) {
            throw AccessDeniedException(str.c_str(), "argument not found");
        }
        return **(cit->second);
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
     * @param alternative Active parsing for accept long option with only one '-' character
     * @param strict Active exception if not all argument is used else you can take additionnal argument with
     *        getAdditionalArguments method
     */
    void parseArguments(int argc, char* argv[], bool alternative = false, bool strict = false);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     * @param actionOrDefault The basic type of action to be taken when this argument is encountered at the command line
     * @param help A brief description of what the argument does
     * @param isRequired Whether or not the command-line option may be omitted (optionals only)
     * @param metavar A name for the argument in usage messages
     * @param nArgs The number of command-line arguments that should be consumed
     * @param defaultArgs The value produced if the argument is absent from the command line
     * @param valid New object from IValid interface
     *
     * @return ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags, Action action,
                          const char* help = NULL, bool isRequired = false, const char* metavar = NULL,
                          std::size_t nArgs = 0, const Vector& defaultArgs = Vector(),
                          IValid* valid = NULL);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     *
     * @return ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     * @param actionOrDefault The basic type of action to be taken when this argument is encountered at the command line
     * @param help A brief description of what the argument does
     * @param isRequired Whether or not the command-line option may be omitted (optionals only)
     * @param metavar A name for the argument in usage messages
     * @param nArgs The number of command-line arguments that should be consumed
     * @param defaultArgs The value produced if the argument is absent from the command line
     * @param valid New object from IValid interface
     * @param dest Reference of destination object
     */
    template<typename T>
    Argument& addArgument(const Vector& nameOrFlags, Action action,
                          const char* help, bool isRequired, const char* metavar,
                          std::size_t nArgs, const Vector& defaultArgs,
                          IValid* valid, T& dest) {
        return addArgument(nameOrFlags, action, help, isRequired,
                           metavar, nArgs, defaultArgs, valid).dest(dest);
    }

    inline static Vector vector(const char* v1 = NULL, const char* v2 = NULL, const char* v3 = NULL, const char* v4 = NULL,
                                const char* v5 = NULL, const char* v6 = NULL, const char* v7 = NULL, const char* v8 = NULL,
                                const char* v9 = NULL, const char* v10 = NULL) {
        const char* args[] = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
        return args;
    }

  private:

    void validFlag(const char* flag) const;

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

    std::list<Argument*> _arguments;
    std::map<std::string, Argument**> _argumentFromName;

    Argument* _helpOption;
    Argument* _versionOption;

    std::string _usage;
    std::string _description;
    std::string _epilog;

    std::vector<std::string> _additionalArguments;
};

} // namespace argparsor

// simply use argparsor
class Argparsor : public argparsor::Argparsor {
  public:
    Argparsor(bool help = true) : argparsor::Argparsor(help) {}
    ~Argparsor() {}

    typedef argparsor::Exception Exception;
    typedef argparsor::ArgumentException ArgumentException;
    typedef argparsor::ParseArgumentException ParseArgumentException;
    typedef argparsor::ParseArgumentRequiredException ParseArgumentRequiredException;
    typedef argparsor::ParseArgumentValidException ParseArgumentValidException;
    typedef argparsor::AccessDeniedException AccessDeniedException;

    typedef argparsor::IValid IValid;
    typedef argparsor::ValidChoise ValidChoise;
    typedef argparsor::ValidMinMax ValidMinMax;
    typedef argparsor::ValidPath ValidPath;

  private:
    typedef argparsor::Vector Vector;

};

} // namespace mblet

#endif // _MBLET_ARGPARSOR_H_