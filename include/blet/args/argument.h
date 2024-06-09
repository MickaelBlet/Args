/**
 * args/argument.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022-2023 BLET Mickael.
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

#ifndef BLET_ARGS_ARGUMENT_H_
#define BLET_ARGS_ARGUMENT_H_

#include <cstdlib> // stdtod
#include <cstring> // memcpy
#include <string>
#include <vector>

#include "blet/args/action.h"
#include "blet/args/exception.h"
#include "blet/args/valid.h"
#include "blet/args/vector.h"

namespace blet {

class Usage;

namespace args {

template<typename T>
inline void boolTo(const bool&, T&) {
    throw ParseArgumentException("destination method not found for this type");
}

inline void boolTo(const bool& b, bool& ret) {
    ret = b;
}

inline void boolTo(const bool& b, char& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned char& ret) {
    ret = b;
}

inline void boolTo(const bool& b, short& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned short& ret) {
    ret = b;
}

inline void boolTo(const bool& b, int& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned int& ret) {
    ret = b;
}

inline void boolTo(const bool& b, long& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned long& ret) {
    ret = b;
}

#if __cplusplus >= 201103L
#ifdef _GLIBCXX_USE_LONG_LONG

inline void boolTo(const bool& b, long long& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned long long& ret) {
    ret = b;
}

#endif
#endif

inline void boolTo(const bool& b, float& ret) {
    ret = b;
}

inline void boolTo(const bool& b, double& ret) {
    ret = b;
}

inline void boolTo(const bool& b, long double& ret) {
    ret = b;
}

inline void boolTo(const bool& b, std::string& ret) {
    if (b) {
        ret = "true";
    }
    else {
        ret = "false";
    }
}

inline void boolTo(const bool& b, const char*& ret) {
    if (b) {
        ret = "true";
    }
    else {
        ret = "false";
    }
}

template<std::size_t Size>
inline void boolTo(const bool& b, char (&ret)[Size]) {
    if (b) {
        if (Size >= sizeof("true")) {
            ::memcpy(ret, "true", sizeof("true"));
        }
        else {
            ::memcpy(ret, "true", Size - 1);
            ret[Size - 1] = '\0';
        }
    }
    else {
        if (Size >= sizeof("false")) {
            ::memcpy(ret, "false", sizeof("false"));
        }
        else {
            ::memcpy(ret, "false", Size - 1);
            ret[Size - 1] = '\0';
        }
    }
}

template<typename T>
inline void strTo(const std::string&, T&) {
    throw ParseArgumentException("destination method not found for this type");
}

inline void strTo(const std::string& str, bool& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, char& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned char& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, short& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned short& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, int& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned int& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

#if __cplusplus >= 201103L
#ifdef _GLIBCXX_USE_LONG_LONG

inline void strTo(const std::string& str, long long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned long long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

#endif
#endif

inline void strTo(const std::string& str, float& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, double& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, long double& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, std::string& ret) {
    ret = str;
}

inline void strTo(const std::string& str, const char*& ret) {
    ret = str.c_str();
}

template<std::size_t Size>
inline void strTo(const std::string& str, char (&ret)[Size]) {
    if (Size > str.size()) {
        ::memcpy(ret, str.c_str(), str.size());
        ret[str.size()] = '\0';
    }
    else {
        ::memcpy(ret, str.c_str(), Size - 1);
        ret[Size - 1] = '\0';
    }
}

class Args;

class ArgumentElement : public std::vector<ArgumentElement> {
    friend class Args;
    friend class Argument;
    friend class Usage;

  public:
    ArgumentElement();
    ArgumentElement(const ArgumentElement& rhs);
    ArgumentElement(const char* arg__, const char* default__);
    ArgumentElement(const char* arg);
    ~ArgumentElement();

    /**
     * @brief Get the string argument
     *
     * @return std::string
     */
    std::string getString() const {
        return argument_;
    }

    /**
     * @brief Get the default value of argument
     *
     * @return const std::string&
     */
    const std::string& getDefault() const {
        return default_;
    }

    /**
     * @brief Check if argument is number
     *
     * @return [true] if is number
     */
    bool isNumber() const {
        return isNumber_;
    }

    /**
     * @brief Get the number from argument if is number
     *
     * @return double
     *
     * @throw Exception is not a number
     */
    double getNumber() const {
        if (isNumber_) {
            return number_;
        }
        throw Exception("is not a number");
    }

    /**
     * @brief tranform to vector of string
     *
     * @return std::vector<std::string>
     *
     * @throw Exception convertion to vector of string not authorized
     */
    operator std::vector<std::string>() const;

    /**
     * @brief Friend function for convert Argument object to ostream
     *
     * @param os
     * @param argument
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const ArgumentElement& argument) {
        os << argument.getString();
        return os;
    }

  protected:
    std::string argument_;
    std::string default_;
    bool isNumber_;
    double number_;
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
    friend class Args;
    friend class Usage;

  public:
    /**
     * @brief Construct a new Argument object
     */
    Argument(Args& args);

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

    bool isExists() const {
        return isExist_;
    }

    bool isRequired() const {
        return isRequired_;
    }

    std::size_t count() const {
        return count_;
    }

    std::size_t getNargs() const {
        return nargs_;
    }

    const std::string& getHelp() const {
        return help_;
    }

    const std::string& getMetavar() const {
        return metavar_;
    }

    const std::vector<std::string>& getNameOrFlags() const {
        return nameOrFlags_;
    }

    const std::vector<std::string>& getDefaults() const {
        return defaults_;
    }

    Action::eAction getAction() const {
        return action_;
    }

    std::string getString() const;

    /**
     * @brief Override bool operator
     *
     * @return true if exist or false if not exist
     */
    operator bool() const {
        if (type_ == REVERSE_BOOLEAN_OPTION) {
            return !isExist_;
        }
        else {
            return isExist_;
        }
    }

    /**
     * @brief tranform to string
     *
     * @return std::string
     */
    operator std::string() const {
        return getString();
    }

    /**
     * @brief tranform to vector of string
     *
     * @return std::vector<std::string>
     *
     * @throw Exception convertion to vector of string not authorized
     */
    operator std::vector<std::string>() const;

    /**
     * @brief tranform to vector of vector of string
     *
     * @return std::vector<std::vector<std::string> >
     *
     * @throw Exception convertion to vector of vector of string not authorized
     */
    operator std::vector<std::vector<std::string> >() const;

    /**
     * @brief tranform to number
     *
     * @tparam T
     * @return T
     */
    template<typename T>
    operator T() const {
        return getNumber();
    }

    /**
     * @brief overide brakcet operator
     *
     * @param index
     * @return const Argument&
     */
    const ArgumentElement& operator[](unsigned long index) const {
        return at(index);
    }

    /**
     * @brief Option strings, e.g. -f, --foo
     *
     * @param flag__
     * @return this reference
     *
     * @throw ArgumentException
     */
    Argument& flag(const char* flag__);

    /**
     * @brief The basic type of action to be taken when this argument is encountered at the command line
     *
     * @param action__
     * @return this reference
     *
     * @throw ArgumentException
     */
    Argument& action(enum Action::eAction action__);

    /**
     * @brief A brief description of what the argument does
     *
     * @param help__
     * @return this reference
     */
    Argument& help(const char* help__) {
        help_ = help__;
        return *this;
    }

    /**
     * @brief Whether or not the command-line option may be omitted (optionals only)
     *
     * @param required__
     * @return this reference
     */
    Argument& required(bool required__ = true);

    /**
     * @brief A name for the argument in usage messages
     *
     * @param metavar__
     * @return this reference
     */
    Argument& metavar(const char* metavar__) {
        metavar_ = metavar__;
        return *this;
    }

    /**
     * @brief The number of command-line arguments that should be consumed
     *
     * @param nargs__
     * @return this reference
     *
     * @throw ArgumentException
     */
    Argument& nargs(std::size_t nargs__) {
        nargs_ = nargs__;
        typeConstructor_();
        defaultsConstructor_();
        return *this;
    }

    /**
     * @brief The value produced if the argument is absent from the command line
     *
     * @param defaults__
     * @return this reference
     *
     * @throw ArgumentException
     */
    Argument& defaults(const Vector& defaults__) {
        defaults_ = defaults__;
        defaultsConstructor_();
        return *this;
    }

    /**
     * @brief New object from IValid interface
     *
     * @param pValid
     * @param isDeletable
     * @return this reference
     */
    Argument& valid(IValid* pValid, bool isDeletable = true) {
        if (valid_ != NULL && validDeletable_) {
            delete valid_;
        }
        valid_ = pValid;
        validDeletable_ = isDeletable;
        return *this;
    }

    /**
     * @brief Define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @param toDest
     * @return reference of new argument
     */
    template<typename T>
    Argument& dest(std::vector<std::vector<T> >& dest,
                   void (*toDest)(std::vector<std::vector<T> >& dest, bool isExists,
                                  const std::vector<std::vector<std::string> >& arguments) = NULL) {
        bool validDeletable = validDeletable_;
        validDeletable_ = false;
        Argument* argumentType = new ArgumentVectorVectorType<T>(this, dest, toDest);
        argumentType->validDeletable_ = validDeletable;
        return *argumentType;
    }

    /**
     * @brief Define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @param toDest
     * @return reference of new argument
     */
    template<typename T>
    Argument& dest(std::vector<T>& dest, void (*toDest)(std::vector<T>& dest, bool isExists,
                                                        const std::vector<std::string>& arguments) = NULL) {
        bool validDeletable = validDeletable_;
        validDeletable_ = false;
        Argument* argumentType = new ArgumentVectorType<T>(this, dest, toDest);
        argumentType->validDeletable_ = validDeletable;
        return *argumentType;
    }

    /**
     * @brief Define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @param toDest
     * @return reference of new argument
     */
    template<typename T>
    Argument& dest(T& dest, void (*toDest)(T& dest, bool isExists, const std::string& argument) = NULL) {
        bool validDeletable = validDeletable_;
        validDeletable_ = false;
        Argument* argumentType = new ArgumentType<T>(this, dest, toDest);
        argumentType->validDeletable_ = validDeletable;
        return *argumentType;
    }

    /**
     * @brief Friend function for convert Argument object to ostream
     *
     * @param os
     * @param argument
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Argument& argument) {
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
        POSITIONAL_ARGUMENT,
        NUMBER_POSITIONAL_ARGUMENT,
        INFINITE_POSITIONAL_ARGUMENT,
        INFINITE_NUMBER_POSITIONAL_ARGUMENT
    };

    bool isPositionnalArgument_() const {
        switch (type_) {
            case POSITIONAL_ARGUMENT:
            case NUMBER_POSITIONAL_ARGUMENT:
            case INFINITE_POSITIONAL_ARGUMENT:
            case INFINITE_NUMBER_POSITIONAL_ARGUMENT:
                return true;
            default:
                return false;
        }
    }

    virtual void toDest_() {
        /* do nothing */
    }

    void toNumber_();

    std::string metavarDefault_();

    void typeConstructor_();

    void defaultsConstructor_();

    void sortNameOrFlags_();

    void clear_();

    static void validFormatFlag_(const char* flag);

    static bool compareOption_(const Argument* first, const Argument* second);

    Args& args_;

    std::vector<std::string> nameOrFlags_;
    enum Type type_;
    bool isExist_;
    bool isRequired_;
    std::size_t count_;
    std::size_t nargs_;
    std::string help_;
    std::string metavar_;

    IValid* valid_;
    bool validDeletable_;

    Argument** this_;
    enum Action::eAction action_;
    std::vector<std::string> defaults_;
};

template<typename T>
class ArgumentType : public Argument {
  public:
    ArgumentType(Argument* argument, T& dest, void (*toDest)(T&, bool, const std::string&)) :
        Argument(*argument),
        dest_(dest),
        toDestCustom_(toDest) {
        delete argument;
        *this_ = this;
    }
    virtual ~ArgumentType() {}

  private:
    void toDest_() {
        if (toDestCustom_ != NULL) {
            toDestCustom_(dest_, isExist_, argument_);
        }
        else {
            if (type_ == BOOLEAN_OPTION) {
                boolTo(isExist_, dest_);
            }
            else if (type_ == REVERSE_BOOLEAN_OPTION) {
                boolTo(!isExist_, dest_);
            }
            else {
                strTo(argument_, dest_);
            }
        }
    }

    T& dest_;
    void (*toDestCustom_)(T&, bool, const std::string&);
};

template<typename T>
class ArgumentVectorType : public Argument {
  public:
    ArgumentVectorType(Argument* argument, std::vector<T>& dest,
                       void (*toDest)(std::vector<T>&, bool, const std::vector<std::string>&)) :
        Argument(*argument),
        dest_(dest),
        toDestCustom_(toDest) {
        delete argument;
        *this_ = this;
    }
    virtual ~ArgumentVectorType() {}

  private:
    void toDest_() {
        if (toDestCustom_ != NULL) {
            std::vector<std::string> arguments;
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            arguments.push_back(at(i).at(j).getString());
                        }
                    }
                    else {
                        arguments.push_back(at(i).getString());
                    }
                }
            }
            else {
                arguments.push_back(argument_);
            }
            toDestCustom_(dest_, isExist_, arguments);
        }
        else {
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            T dest;
                            strTo(at(i).at(j).getString(), dest);
                            dest_.push_back(dest);
                        }
                    }
                    else {
                        T dest;
                        strTo(at(i).getString(), dest);
                        dest_.push_back(dest);
                    }
                }
            }
            else {
                T dest;
                if (type_ == BOOLEAN_OPTION) {
                    boolTo(isExist_, dest);
                }
                else if (type_ == REVERSE_BOOLEAN_OPTION) {
                    boolTo(!isExist_, dest);
                }
                else {
                    strTo(argument_, dest);
                }
                dest_.push_back(dest);
            }
        }
    }

    std::vector<T>& dest_;
    void (*toDestCustom_)(std::vector<T>&, bool, const std::vector<std::string>&);
};

template<typename T>
class ArgumentVectorVectorType : public Argument {
  public:
    ArgumentVectorVectorType(Argument* argument, std::vector<std::vector<T> >& dest,
                             void (*toDest)(std::vector<std::vector<T> >&, bool,
                                            const std::vector<std::vector<std::string> >&)) :
        Argument(*argument),
        dest_(dest),
        toDestCustom_(toDest) {
        delete argument;
        *this_ = this;
    }
    virtual ~ArgumentVectorVectorType() {}

  private:
    void toDest_() {
        if (toDestCustom_ != NULL) {
            std::vector<std::vector<std::string> > arguments;
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    std::vector<std::string> tmpVector;
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            tmpVector.push_back(at(i).at(j).getString());
                        }
                    }
                    else {
                        tmpVector.push_back(at(i).getString());
                    }
                    arguments.push_back(tmpVector);
                }
            }
            else {
                std::vector<std::string> tmpVector;
                tmpVector.push_back(argument_);
                arguments.push_back(tmpVector);
            }
            toDestCustom_(dest_, isExist_, arguments);
        }
        else {
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    std::vector<T> vectorDest;
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            T dest;
                            strTo(at(i).at(j).getString(), dest);
                            vectorDest.push_back(dest);
                        }
                    }
                    else {
                        T dest;
                        strTo(at(i).getString(), dest);
                        vectorDest.push_back(dest);
                    }
                    dest_.push_back(vectorDest);
                }
            }
            else {
                T dest;
                if (type_ == BOOLEAN_OPTION) {
                    boolTo(isExist_, dest);
                }
                else if (type_ == REVERSE_BOOLEAN_OPTION) {
                    boolTo(!isExist_, dest);
                }
                else {
                    strTo(argument_, dest);
                }
                std::vector<T> vectorDest;
                vectorDest.push_back(dest);
                dest_.push_back(vectorDest);
            }
        }
    }

    std::vector<std::vector<T> >& dest_;
    void (*toDestCustom_)(std::vector<std::vector<T> >&, bool, const std::vector<std::vector<std::string> >&);
};

} // namespace args

} // namespace blet

#endif // #ifndef BLET_ARGS_ARGUMENT_H_
