/**
 * argparsor-argument.h
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

#ifndef _MBLET_ARGPARSOR_ARGUMENT_H_
#define _MBLET_ARGPARSOR_ARGUMENT_H_

#include <sstream>
#include <string>
#include <vector>

#include "mblet/argparsor-action.h"
#include "mblet/argparsor-exception.h"
#include "mblet/argparsor-valid.h"
#include "mblet/argparsor-vector.h"

namespace mblet {

class Argparsor;

namespace argparsor {

class Argparsor;

class ArgumentElement : public std::vector<ArgumentElement> {
    friend class ::mblet::Argparsor;
    friend class Argparsor;
    friend class Argument;

  public:
    ArgumentElement();
    ArgumentElement(const ArgumentElement& rhs);
    ArgumentElement(const char* arg_, const char* default_);
    ArgumentElement(const char* arg);
    ~ArgumentElement();

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
        if (_isNumber) {
            return _number;
        }
        throw Exception("is not a number");
    }

    /**
     * @brief tranform to vector of string
     *
     * @return std::vector<std::string>
     */
    inline operator std::vector<std::string>() const;

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

template<typename T>
class ArgumentType;

template<typename T>
class ArgumentVectorType;

template<typename T>
class ArgumentVectorVectorType;

/**
 * @brief Argument object
 */
class Argument : public ArgumentElement {
    friend class ::mblet::Argparsor;
    friend class Argparsor;

  public:
    /**
     * @brief Construct a new Argument object
     */
    Argument(Argparsor& argparsor);

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

    inline std::size_t getNargs() const {
        return _nargs;
    }

    inline const std::string& getHelp() const {
        return _help;
    }

    inline const std::string& getMetavar() const {
        return _metavar;
    }

    inline const std::vector<std::string>& getNameOrFlags() const {
        return _nameOrFlags;
    }

    inline const std::vector<std::string>& getDefaults() const {
        return _defaults;
    }

    std::string getString() const;

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
    operator std::vector<std::string>() const;

    /**
     * @brief tranform to vector of vector of string
     *
     * @return std::vector<std::vector<std::string> >
     */
    operator std::vector<std::vector<std::string> >() const;

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
    Argument& flag(const char* flag_);

    /**
     * @brief The basic type of action to be taken when this argument is encountered at the command line
     * @param action_
     * @return this reference
     */
    inline Argument& action(enum Action::eAction action_) {
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
    Argument& required(bool required_);

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

    /**
     * @brief define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @return reference of new argument
     */
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

  protected:
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

    void _toNumber();

    std::string _metavarDefault();

    void _typeConstructor();

    void _defaultsConstructor();

    void _sortNameOrFlags();

    static void validFormatFlag(const char* flag);

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
    enum Action::eAction _action;
    std::vector<std::string> _defaults;
};

template<typename T>
class ArgumentType : public Argument {
  public:
    ArgumentType(Argument* argument, T& dest) :
        Argument(*argument),
        _dest(dest) {
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
    ArgumentVectorType(Argument* argument, std::vector<T>& dest) :
        Argument(*argument),
        _dest(dest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentVectorType() {}

  private:
    void _toDest() {
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                if (!at(i).empty()) {
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
                        T dest;
                        std::stringstream ss("");
                        if (at(i).at(j).isNumber()) {
                            ss << at(i).at(j).getNumber();
                        }
                        else {
                            ss << at(i).at(j).getString();
                        }
                        ss >> dest;
                        _dest.push_back(dest);
                    }
                }
                else {
                    T dest;
                    std::stringstream ss("");
                    if (at(i).isNumber()) {
                        ss << at(i).getNumber();
                    }
                    else {
                        ss << at(i).getString();
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
    ArgumentVectorVectorType(Argument* argument, std::vector<std::vector<T> >& dest) :
        Argument(*argument),
        _dest(dest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentVectorVectorType() {}

  private:
    void _toDest() {
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                std::vector<T> vectorDest;
                if (!at(i).empty()) {
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
                        T dest;
                        std::stringstream ss("");
                        if (at(i).at(j).isNumber()) {
                            ss << at(i).at(j).getNumber();
                        }
                        else {
                            ss << at(i).at(j).getString();
                        }
                        ss >> dest;
                        vectorDest.push_back(dest);
                    }
                }
                else {
                    T dest;
                    std::stringstream ss("");
                    if (at(i).isNumber()) {
                        ss << at(i).getNumber();
                    }
                    else {
                        ss << at(i).getString();
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

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_ARGUMENT_H_