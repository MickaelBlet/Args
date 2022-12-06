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

// #include "mblet/argparsor/action.h"
/**
 * argparsor/action.h
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

#ifndef _MBLET_ARGPARSOR_ACTION_H_
#define _MBLET_ARGPARSOR_ACTION_H_

namespace mblet {

namespace argparsor {

struct Action {
    enum eAction {
        NONE = 0,
        HELP,
        VERSION,
        STORE_TRUE,
        STORE_FALSE,
        APPEND,
        EXTEND,
        INFINITE
    };
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_ACTION_H_

// #include "mblet/argparsor/argparsor.h"
/**
 * argparsor/argparsor.h
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

#ifndef _MBLET_ARGPARSOR_ARGPARSOR_H_
#define _MBLET_ARGPARSOR_ARGPARSOR_H_

#include <list>
#include <map>
#include <string>
#include <vector>

// #include "mblet/argparsor/action.h"

// #include "mblet/argparsor/argument.h"
/**
 * argparsor/argument.h
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

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// #include "mblet/argparsor/action.h"

// #include "mblet/argparsor/exception.h"
/**
 * argparsor/exception.h
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

#ifndef _MBLET_ARGPARSOR_EXCEPTION_H_
#define _MBLET_ARGPARSOR_EXCEPTION_H_

#include <exception>
#include <string>

namespace mblet {

namespace argparsor {

/**
 * @brief Basic exception from std::exception
 */
class Exception : public std::exception {
  public:
    Exception(const char* str) :
        std::exception(),
        _str(str) {}
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
    ArgumentException(const char* message) :
        Exception(message),
        _argument() {}
    ArgumentException(const char* argument, const char* message) :
        Exception(message),
        _argument(argument) {}
    virtual ~ArgumentException() throw() {}
    const char* argument() const throw() {
        return _argument.c_str();
    }

  protected:
    std::string _argument;
};

typedef ArgumentException ParseArgumentException;
typedef ParseArgumentException ParseArgumentRequiredException;
typedef ParseArgumentException ParseArgumentValidException;
typedef ArgumentException AccessDeniedException;

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_EXCEPTION_H_

// #include "mblet/argparsor/valid.h"
/**
 * argparsor/valid.h
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

#ifndef _MBLET_ARGPARSOR_VALID_H_
#define _MBLET_ARGPARSOR_VALID_H_

#include <string>
#include <vector>

namespace mblet {

namespace argparsor {

/**
 * @brief Interface for validate argument
 */
class IValid {
  public:
    /**
     * @brief Destroy the IValid object
     */
    virtual ~IValid() {}

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    virtual bool isValid(std::vector<std::string>& arguments) = 0;
};

class ValidNumber : public IValid {
  public:
    /**
     * @brief Construct a new Valid Number object
     */
    ValidNumber();

    /**
     * @brief Destroy the Valid Number object
     */
    ~ValidNumber();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);
};

class ValidMinMax : public IValid {
  public:
    /**
     * @brief Construct a new Valid Min Max object
     * at call self @c isValid it check if arguments are between of @p min and @p max
     *
     * @param min
     * @param max
     */
    ValidMinMax(double min, double max);

    /**
     * @brief Destroy the Valid Min Max object
     */
    ~ValidMinMax();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);

  private:
    double _min;
    double _max;
};

class ValidChoise : public IValid {
  public:
    /**
     * @brief
     *
     * @param choises
     */
    ValidChoise(const std::vector<std::string>& choises);

    /**
     * @brief Destroy the Valid Choise object
     */
    ~ValidChoise();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);

  private:
    std::vector<std::string> _choises;
};

class ValidPath : public IValid {
  public:
    enum eMode {
        ALL = 0,
        IS_FILE,
        IS_DIR
    };

    /**
     * @brief Construct a new Valid Path Exist object
     * at call self @c isValid it check if argument is a exist path
     */
    ValidPath(enum eMode mode = ValidPath::ALL);

    /**
     * @brief Destroy the Valid Path Exist object
     */
    ~ValidPath();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);

  private:
    enum eMode _mode;
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_VALID_H_

// #include "mblet/argparsor/vector.h"
/**
 * argparsor/vector.h
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

#ifndef _MBLET_ARGPARSOR_VECTOR_H_
#define _MBLET_ARGPARSOR_VECTOR_H_

#include <string>
#include <vector>

namespace mblet {

namespace argparsor {

class Vector : public std::vector<std::string> {
  public:
    Vector() :
        std::vector<std::string>() {}

    template<std::size_t S>
    Vector(const char* (&v)[S]) :
        std::vector<std::string>() {
        for (std::size_t i = 0; i < S; ++i) {
            if (v[i] != NULL) {
                std::vector<std::string>::push_back(v[i]);
            }
        }
    }

    template<std::size_t S>
    Vector(const char* const (&v)[S]) :
        std::vector<std::string>() {
        for (std::size_t i = 0; i < S; ++i) {
            if (v[i] != NULL) {
                std::vector<std::string>::push_back(v[i]);
            }
        }
    }

    template<std::size_t S>
    Vector(const std::string (&v)[S]) :
        std::vector<std::string>() {
        for (std::size_t i = 0; i < S; ++i) {
            std::vector<std::string>::push_back(v[i]);
        }
    }

    template<std::size_t S>
    Vector(const char (&v)[S]) :
        std::vector<std::string>() {
        std::vector<std::string>::push_back(v);
    }

    Vector(const char*(&v)) :
        std::vector<std::string>() {
        std::vector<std::string>::push_back(v);
    }

    Vector(const std::string& v) :
        std::vector<std::string>() {
        std::vector<std::string>::push_back(v);
    }

#if __cplusplus >= 201103L
    Vector(const std::initializer_list<std::string>& l) :
        std::vector<std::string>(l) {}
#endif
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_VECTOR_H_


namespace mblet {

class Argparsor;

namespace argparsor {

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

    bool isExist() const {
        return _isExist;
    }

    bool isRequired() const {
        return _isRequired;
    }

    std::size_t count() const {
        return _count;
    }

    std::size_t getNargs() const {
        return _nargs;
    }

    const std::string& getHelp() const {
        return _help;
    }

    const std::string& getMetavar() const {
        return _metavar;
    }

    const std::vector<std::string>& getNameOrFlags() const {
        return _nameOrFlags;
    }

    const std::vector<std::string>& getDefaults() const {
        return _defaults;
    }

    Action::eAction getAction() const {
        return _action;
    }

    std::string getString() const;

    /**
     * @brief Override bool operator
     *
     * @return true if exist or false if not exist
     */
    operator bool() const {
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
    operator std::string() const {
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
     * @param flag_
     * @return this reference
     */
    Argument& flag(const char* flag_);

    /**
     * @brief The basic type of action to be taken when this argument is encountered at the command line
     * @param action_
     * @return this reference
     */
    Argument& action(enum Action::eAction action_) {
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
    Argument& help(const char* help_) {
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
    Argument& metavar(const char* metavar_) {
        _metavar = metavar_;
        return *this;
    }

    /**
     * @brief The number of command-line arguments that should be consumed
     * @param nargs_
     * @return this reference
     */
    Argument& nargs(std::size_t nargs_) {
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
    Argument& defaults(const Vector& defaults_) {
        _defaults = defaults_;
        _defaultsConstructor();
        return *this;
    }

    /**
     * @brief New object from IValid interface
     * @param pValid
     * @return this reference
     */
    Argument& valid(IValid* pValid, bool isDeletable = true) {
        if (_valid != NULL && _validDeletable) {
            delete _valid;
        }
        _valid = pValid;
        _validDeletable = isDeletable;
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
    Argument& dest(std::vector<std::vector<T> >& dest,
                   void (*toDest)(std::vector<std::vector<T> >& dest, bool isExist,
                                  const std::vector<std::vector<std::string> >& arguments) = NULL) {
        bool validDeletable = _validDeletable;
        _validDeletable = false;
        Argument* argumentType = new ArgumentVectorVectorType<T>(this, dest, toDest);
        argumentType->_validDeletable = validDeletable;
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
    Argument& dest(std::vector<T>& dest, void (*toDest)(std::vector<T>& dest, bool isExist,
                                                        const std::vector<std::string>& arguments) = NULL) {
        bool validDeletable = _validDeletable;
        _validDeletable = false;
        Argument* argumentType = new ArgumentVectorType<T>(this, dest, toDest);
        argumentType->_validDeletable = validDeletable;
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
    Argument& dest(T& dest, void (*toDest)(T& dest, bool isExist, const std::string& argument) = NULL) {
        bool validDeletable = _validDeletable;
        _validDeletable = false;
        Argument* argumentType = new ArgumentType<T>(this, dest, toDest);
        argumentType->_validDeletable = validDeletable;
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
        POSITIONAL_ARGUMENT
    };

    virtual void _toDest() {
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
    bool _validDeletable;

    Argument** _this;
    enum Action::eAction _action;
    std::vector<std::string> _defaults;
};

template<typename T>
class ArgumentType : public Argument {
  public:
    ArgumentType(Argument* argument, T& dest, void (*toDest)(T&, bool, const std::string&)) :
        Argument(*argument),
        _dest(dest),
        _toDestCustom(toDest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentType() {}

  private:
    void _toDest() {
        if (_toDestCustom != NULL) {
            _toDestCustom(_dest, _isExist, _argument);
        }
        else {
            if (_type == BOOLEAN_OPTION) {
                boolTo(_isExist, _dest);
            }
            else if (_type == REVERSE_BOOLEAN_OPTION) {
                boolTo(!_isExist, _dest);
            }
            else {
                strTo(_argument, _dest);
            }
        }
    }

    T& _dest;
    void (*_toDestCustom)(T&, bool, const std::string&);
};

template<typename T>
class ArgumentVectorType : public Argument {
  public:
    ArgumentVectorType(Argument* argument, std::vector<T>& dest,
                       void (*toDest)(std::vector<T>&, bool, const std::vector<std::string>&)) :
        Argument(*argument),
        _dest(dest),
        _toDestCustom(toDest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentVectorType() {}

  private:
    void _toDest() {
        if (_toDestCustom != NULL) {
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
                arguments.push_back(_argument);
            }
            _toDestCustom(_dest, _isExist, arguments);
        }
        else {
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            T dest;
                            strTo(at(i).at(j).getString(), dest);
                            _dest.push_back(dest);
                        }
                    }
                    else {
                        T dest;
                        strTo(at(i).getString(), dest);
                        _dest.push_back(dest);
                    }
                }
            }
            else {
                T dest;
                if (_type == BOOLEAN_OPTION) {
                    boolTo(_isExist, dest);
                }
                else if (_type == REVERSE_BOOLEAN_OPTION) {
                    boolTo(!_isExist, dest);
                }
                else {
                    strTo(_argument, dest);
                }
                _dest.push_back(dest);
            }
        }
    }

    std::vector<T>& _dest;
    void (*_toDestCustom)(std::vector<T>&, bool, const std::vector<std::string>&);
};

template<typename T>
class ArgumentVectorVectorType : public Argument {
  public:
    ArgumentVectorVectorType(Argument* argument, std::vector<std::vector<T> >& dest,
                             void (*toDest)(std::vector<std::vector<T> >&, bool,
                                            const std::vector<std::vector<std::string> >&)) :
        Argument(*argument),
        _dest(dest),
        _toDestCustom(toDest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentVectorVectorType() {}

  private:
    void _toDest() {
        if (_toDestCustom != NULL) {
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
                tmpVector.push_back(_argument);
                arguments.push_back(tmpVector);
            }
            _toDestCustom(_dest, _isExist, arguments);
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
                    _dest.push_back(vectorDest);
                }
            }
            else {
                T dest;
                if (_type == BOOLEAN_OPTION) {
                    boolTo(_isExist, dest);
                }
                else if (_type == REVERSE_BOOLEAN_OPTION) {
                    boolTo(!_isExist, dest);
                }
                else {
                    strTo(_argument, dest);
                }
                std::vector<T> vectorDest;
                vectorDest.push_back(dest);
                _dest.push_back(vectorDest);
            }
        }
    }

    std::vector<std::vector<T> >& _dest;
    void (*_toDestCustom)(std::vector<std::vector<T> >&, bool, const std::vector<std::vector<std::string> >&);
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_ARGUMENT_H_

// #include "mblet/argparsor/exception.h"

// #include "mblet/argparsor/vector.h"


namespace mblet {

namespace argparsor {

class Argument;

/**
 * @brief Object for parse the main arguments
 */
class Argparsor {
    friend class Argument;

  public:
    /**
     * @brief Construct a new Argparsor object
     */
    Argparsor(bool help);

    /**
     * @brief Destroy the Argparsor object
     */
    virtual ~Argparsor();

    /**
     * @brief Get the status of alternative
     *
     * @return [true] at alternative
     */
    bool isAlternative() const {
        return _isAlternative;
    }

    /**
     * @brief Get the status of strict
     *
     * @return [true] at strict
     */
    bool isStrict() const {
        return _isStrict;
    }

    /**
     * @brief Get the bynary name
     *
     * @return const std::string&
     */
    const std::string& getBynaryName() const {
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
     * @brief Check if argument exist
     *
     * @param str
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExist(const char* str) const {
        return argumentExist(std::string(str));
    }

    /**
     * @brief Check if argument exist
     *
     * @param str
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExist(const std::string& str) const {
        return (_argumentFromName.find(str) != _argumentFromName.end());
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    const Argument& getArgument(const char* str) const {
        return getArgument(std::string(str));
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    const Argument& getArgument(const std::string& str) const {
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
    const Argument& operator[](const char* str) const {
        return getArgument(str);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param str
     * @return const Argument&
     */
    const Argument& operator[](const std::string& str) const {
        return getArgument(str);
    }

    /**
     * @brief Get the vector of additional argument
     *
     * @return const std::vector<std::string>&
     */
    const std::vector<std::string>& getAdditionalArguments() const {
        return _additionalArguments;
    }

    /**
     * @brief Set the usage message
     *
     * @param usage
     */
    void setUsage(const char* usage) {
        _usage = usage;
    }

    /**
     * @brief Set the description in usage message
     *
     * @param description
     */
    void setDescription(const char* description) {
        _description = description;
    }

    /**
     * @brief Set the epilog in usage message
     *
     * @param epilog
     */
    void setEpilog(const char* epilog) {
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
     *
     * @return ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags);

    static Vector vector(const char* v1 = NULL, const char* v2 = NULL, const char* v3 = NULL, const char* v4 = NULL,
                         const char* v5 = NULL, const char* v6 = NULL, const char* v7 = NULL, const char* v8 = NULL,
                         const char* v9 = NULL, const char* v10 = NULL) {
        const char* args[] = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
        return args;
    }

  private:
    Argparsor(const Argparsor&);            // disable copy constructor
    Argparsor& operator=(Argparsor const&); // disable copy operator

    /**
     * @brief Get the short argument decompose multi short argument
     *
     * @param maxIndex
     * @param argv
     * @param index
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
     * @param alternative
     */
    void parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                       Argument* argument);

    /**
     * @brief Get the positionnal argument
     *
     * @param argv
     * @param index
     * @param strict
     */
    void parsePositionnalArgument(char* argv[], int* index);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @param alternative
     * @return true
     * @return false
     */
    bool endOfInfiniteArgument(const char* argument);

    std::string _binaryName;

    std::list<Argument*> _arguments;
    std::map<std::string, Argument**> _argumentFromName;

    Argument* _helpOption;
    Argument* _versionOption;

    std::string _usage;
    std::string _description;
    std::string _epilog;

    bool _isAlternative;
    bool _isStrict;
    std::vector<std::string> _additionalArguments;
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_ARGPARSOR_H_

// #include "mblet/argparsor/exception.h"

// #include "mblet/argparsor/valid.h"

// #include "mblet/argparsor/vector.h"


namespace mblet {

// simply use argparsor
class Argparsor : public argparsor::Argparsor, public argparsor::Action {
  public:
    Argparsor(bool help = true) :
        argparsor::Argparsor(help) {}
    ~Argparsor() {}

    typedef argparsor::Exception Exception;
    typedef argparsor::ArgumentException ArgumentException;
    typedef argparsor::ParseArgumentException ParseArgumentException;
    typedef argparsor::ParseArgumentRequiredException ParseArgumentRequiredException;
    typedef argparsor::ParseArgumentValidException ParseArgumentValidException;
    typedef argparsor::AccessDeniedException AccessDeniedException;

    typedef argparsor::IValid IValid;
    typedef argparsor::ValidNumber ValidNumber;
    typedef argparsor::ValidChoise ValidChoise;
    typedef argparsor::ValidMinMax ValidMinMax;
    typedef argparsor::ValidPath ValidPath;

  private:
    typedef argparsor::Vector Vector;
};

} // namespace mblet

#endif // _MBLET_ARGPARSOR_H_
/**
 * argparsor-argparsor.cpp
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

// #include "mblet/argparsor/argparsor.h"


#include <algorithm>
#include <iostream>
#include <sstream>

// #include "mblet/argparsor/argument.h"

// #include "mblet/argparsor/utils.h"
/**
 * argparsor/utils.h
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

#ifndef _MBLET_ARGPARSOR_UTILS_H_
#define _MBLET_ARGPARSOR_UTILS_H_

#include <cstring> // strchr
#include <string>

namespace mblet {

namespace argparsor {

/**
 * @brief arg is "-[^-].*"
 *
 * @param arg
 * @return true
 * @return false
 */
inline bool isShortOption(const char* arg) {
    if (arg != NULL && arg[0] == '-' && arg[1] != '-' && arg[1] != '\0') {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief arg is "--.*"
 *
 * @param arg
 * @return true
 * @return false
 */
inline bool isLongOption(const char* arg) {
    if (arg != NULL && arg[0] == '-' && arg[1] == '-' && arg[2] != '\0') {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief arg is "--"
 *
 * @param arg
 * @return true
 * @return false
 */
inline bool isEndOption(const char* arg) {
    if (arg != NULL && arg[0] == '-' && arg[1] == '-' && arg[2] == '\0') {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief get index of en option index or argc
 *
 * @param argc
 * @param argv
 * @return int
 */
inline int endOptionIndex(int argc, char** argv) {
    for (int i = 0; i < argc; ++i) {
        if (isEndOption(argv[i])) {
            return i;
        }
    }
    return argc;
}

/**
 * @brief split arg if contain '=' character
 *
 * @param arg
 * @param retOptionName
 * @param retArgument
 * @return true
 * @return false
 */
inline bool takeArg(const char* arg, std::string* retOptionName, std::string* retArgument) {
    char* equal = ::strchr(const_cast<char*>(arg), '=');
    if (equal) {
        std::string firstPart(arg, 0, equal - arg);
        *retOptionName = firstPart;
        std::string secondPart(arg, equal - arg + 1, std::string::npos);
        *retArgument = secondPart;
        return true;
    }
    else {
        *retOptionName = arg;
        return false;
    }
}

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_UTILS_H_

// #include "mblet/argparsor/vector.h"


#define PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace mblet {

namespace argparsor {

inline Argparsor::Argparsor(bool help) :
    _binaryName(),
    _arguments(),
    _argumentFromName(),
    _helpOption(NULL),
    _versionOption(NULL),
    _usage(),
    _description(),
    _epilog(),
    _isAlternative(false),
    _isStrict(false),
    _additionalArguments() {
    if (help) {
        // define _helpOption
        addArgument("-h").flag("--help").action(Action::HELP).help("show this help message and exit");
    }
}

inline Argparsor::~Argparsor() {
    // delete all new element
    for (std::list<Argument*>::iterator it = _arguments.begin(); it != _arguments.end(); ++it) {
        delete (*it);
    }
}

inline std::string Argparsor::getUsage() const {
    std::ostringstream oss("");
    if (!_usage.empty()) {
        return _usage;
    }
    bool hasOption = false;
    bool hasPositionnal = false;
    // usage line
    oss << "usage: " << _binaryName;
    std::list<Argument*>::const_iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
            hasPositionnal = true;
            continue;
        }
        hasOption = true;
        oss << ' ';
        if (!(*it)->_isRequired) {
            oss << '[';
        }
        oss << (*it)->_nameOrFlags.front();
        switch ((*it)->_type) {
            case Argument::SIMPLE_OPTION:
            case Argument::NUMBER_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                if ((*it)->_metavar.empty()) {
                    oss << ' ' << (*it)->_metavarDefault();
                }
                else {
                    oss << ' ' << (*it)->_metavar;
                }
                break;
            default:
                break;
        }
        if (!(*it)->_isRequired) {
            oss << ']';
        }
    }
    if (hasOption && hasPositionnal) {
        oss << " --";
    }
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_type != Argument::POSITIONAL_ARGUMENT) {
            continue;
        }
        oss << ' ';
        if (!(*it)->_isRequired) {
            oss << '[';
        }
        oss << (*it)->_nameOrFlags.front();
        if (!(*it)->_isRequired) {
            oss << ']';
        }
    }
    oss << '\n';
    // description
    if (!_description.empty()) {
        oss << '\n' << _description << '\n';
    }
    // optionnal
    if (!_arguments.empty()) {
        std::list<std::pair<std::string, std::string> > positionals;
        std::list<std::pair<std::string, std::string> > optionnals;
        for (it = _arguments.begin(); it != _arguments.end(); ++it) {
            std::list<std::pair<std::string, std::string> >* listOption = NULL;
            if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
                positionals.push_back(std::pair<std::string, std::string>("", ""));
                listOption = &positionals;
            }
            else {
                optionnals.push_back(std::pair<std::string, std::string>("", ""));
                listOption = &optionnals;
            }
            std::string& optionStr = listOption->back().first;
            std::string& helpStr = listOption->back().second;
            optionStr += "  ";
            for (std::size_t i = 0; i < (*it)->_nameOrFlags.size(); ++i) {
                if (i > 0) {
                    optionStr += ", ";
                }
                optionStr += (*it)->_nameOrFlags[i];
            }
            switch ((*it)->_type) {
                case Argument::SIMPLE_OPTION:
                case Argument::NUMBER_OPTION:
                case Argument::INFINITE_OPTION:
                case Argument::MULTI_OPTION:
                case Argument::MULTI_INFINITE_OPTION:
                case Argument::MULTI_NUMBER_OPTION:
                case Argument::MULTI_NUMBER_INFINITE_OPTION:
                    if ((*it)->_metavar.empty()) {
                        optionStr += " " + (*it)->_metavarDefault();
                    }
                    else {
                        optionStr += " " + (*it)->_metavar;
                    }
                    break;
                default:
                    break;
            }
            helpStr += "  " + (*it)->_help;
            if ((*it)->_isRequired) {
                helpStr += " (required)";
            }
            else {
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                    case Argument::NUMBER_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION:
                        if (!(*it)->_default.empty()) {
                            helpStr += " (default: " + (*it)->_default + ")";
                        }
                        break;
                    default:
                        break;
                }
            }
            helpStr += "\n";
        }
        // calculate width max
        std::size_t max = 0;
        std::list<std::pair<std::string, std::string> >::iterator optIt;
        for (optIt = positionals.begin(); optIt != positionals.end(); ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        for (optIt = optionnals.begin(); optIt != optionnals.end(); ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        if (!positionals.empty()) {
            oss << "\npositional arguments:\n";
            for (optIt = positionals.begin(); optIt != positionals.end(); ++optIt) {
                oss.width(max);
                oss.flags(std::ios::left);
                oss << optIt->first;
                oss.width(0);
                oss << optIt->second;
            }
        }
        if (!optionnals.empty()) {
            oss << "\noptional arguments:\n";
            for (optIt = optionnals.begin(); optIt != optionnals.end(); ++optIt) {
                oss.width(max);
                oss.flags(std::ios::left);
                oss << optIt->first;
                oss.width(0);
                oss << optIt->second;
            }
        }
    }
    // epilog
    if (!_epilog.empty()) {
        oss << '\n' << _epilog << '\n';
    }
    return oss.str();
}

inline std::string Argparsor::getVersion() const {
    std::ostringstream oss("");
    if (_versionOption != NULL) {
        oss << _versionOption->_default << std::endl;
    }
    return oss.str();
}

inline void Argparsor::parseArguments(int argc, char* argv[], bool alternative, bool strict) {
    _binaryName = argv[0];
    _isAlternative = alternative;
    _isStrict = strict;
    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    // foreach argument
    for (int i = 1; i < argc; ++i) {
        if (isShortOption(argv[i])) {
            parseShortArgument(endIndex, argv, &i);
        }
        else if (isLongOption(argv[i])) {
            parseLongArgument(endIndex, argv, &i);
        }
        else if (isEndOption(argv[i])) {
            ++i;
            while (i < argc) {
                parsePositionnalArgument(argv, &i);
                ++i;
            }
            break;
        }
        else {
            parsePositionnalArgument(argv, &i);
        }
    }
    // check help option
    if (_helpOption != NULL && _helpOption->_isExist) {
        std::cout << getUsage() << std::flush;
        this->~Argparsor();
        exit(0);
    }
    // check version option
    if (_versionOption != NULL && _versionOption->_isExist) {
        std::cout << getVersion() << std::flush;
        this->~Argparsor();
        exit(0);
    }
    // check require option
    std::list<Argument*>::iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_isRequired && (*it)->_isExist == false) {
            if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
                throw ParseArgumentRequiredException((*it)->_nameOrFlags.front().c_str(), "argument is required");
            }
            else {
                throw ParseArgumentRequiredException((*it)->_nameOrFlags.front().c_str(), "option is required");
            }
        }
    }
    // check valid configuration function
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_isExist && (*it)->_valid != NULL) {
            try {
                std::vector<std::string> arguments;
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                    case Argument::NUMBER_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                        const Argument& cArg = *(*it);
                        arguments = cArg.operator std::vector<std::string>();
                        break;
                    }
                    default:
                        break;
                }
                if ((*it)->_valid->isValid(arguments) == false) {
                    throw ParseArgumentValidException("invalid check function");
                }
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                        if (!arguments.empty()) {
                            (*it)->_argument = arguments.front();
                        }
                        break;
                    case Argument::NUMBER_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                        for (std::size_t i = 0; i < (*it)->size() && i < arguments.size(); ++i) {
                            (*it)->at(i)._argument = arguments[i];
                        }
                        break;
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                        std::size_t i = 0;
                        for (std::size_t j = 0; j < (*it)->size() && i < arguments.size(); ++j) {
                            for (std::size_t k = 0; k < (*it)->at(j).size() && i < arguments.size(); ++k) {
                                (*it)->at(j).at(k)._argument = arguments[i];
                                ++i;
                            }
                        }
                        break;
                    }
                    default:
                        throw ParseArgumentValidException("invalid type option for use valid");
                        break;
                }
            }
            catch (const ParseArgumentValidException& e) {
                // add name or first flag in exception
                throw ParseArgumentValidException((*it)->_nameOrFlags.front().c_str(), e.what());
            }
        }
        // tranform argument to number
        (*it)->_toNumber();
        // dest
        (*it)->_toDest();
    }
}

inline Argument& Argparsor::addArgument(const Vector& nameOrFlags) {
    if (nameOrFlags.empty()) {
        throw ArgumentException("", "invalid empty flag");
    }
    Argument* argument = NULL;
    // is name
    if (nameOrFlags.size() == 1 && nameOrFlags.front()[0] != '-') {
        if (nameOrFlags.front().empty()) {
            throw ArgumentException("", "bad name argument");
        }
        if (_argumentFromName.find(nameOrFlags.front()) != _argumentFromName.end()) {
            throw ArgumentException(nameOrFlags.front().c_str(), "bad name argument already exist");
        }
        // create argument
        argument = new Argument(*this);
        argument->_nameOrFlags.push_back(nameOrFlags.front());
        argument->_nargs = 1;
        argument->_type = Argument::POSITIONAL_ARGUMENT;
    }
    else {
        std::vector<std::string> newFlags;

        for (std::size_t i = 0; i < nameOrFlags.size(); ++i) {
            Argument::validFormatFlag(nameOrFlags[i].c_str());
            if (_argumentFromName.find(nameOrFlags.front()) != _argumentFromName.end()) {
                throw ArgumentException(nameOrFlags.front().c_str(), "invalid flag already exist");
            }
            if (std::find(newFlags.begin(), newFlags.end(), nameOrFlags[i]) == newFlags.end()) {
                newFlags.push_back(nameOrFlags[i]);
            }
        }

        argument = new Argument(*this);
        argument->_nameOrFlags = nameOrFlags;
        argument->_sortNameOrFlags();
    }

    _arguments.push_back(argument);
    Argument** addrNewArgument = &(_arguments.back());
    argument->_this = addrNewArgument;
    for (std::size_t i = 0; i < argument->_nameOrFlags.size(); ++i) {
        _argumentFromName.insert(std::pair<std::string, Argument**>(argument->_nameOrFlags[i], addrNewArgument));
    }
    _arguments.sort(&Argument::compareOption);
    return **addrNewArgument;
}

/*
** private
*/
inline void Argparsor::parseShortArgument(int maxIndex, char* argv[], int* index) {
    std::string options;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    if (_isAlternative) {
        // try to find long option
        it = _argumentFromName.find("-" + options);
        if (it != _argumentFromName.end()) {
            parseArgument(maxIndex, argv, index, hasArg, options.c_str() + PREFIX_SIZEOF_SHORT_OPTION, arg.c_str(),
                          *(it->second));
            return;
        }
    }
    // get firsts option
    for (std::size_t i = 1; i < options.size() - 1; ++i) {
        std::string charOption(options, i, 1);
        it = _argumentFromName.find("-" + charOption);
        if (it == _argumentFromName.end()) {
            throw ParseArgumentException(charOption.c_str(), "invalid option");
        }
        else if (!hasArg && ((*(it->second))->_type == Argument::SIMPLE_OPTION ||
                             (*(it->second))->_type == Argument::NUMBER_OPTION ||
                             (*(it->second))->_type == Argument::INFINITE_OPTION ||
                             (*(it->second))->_type == Argument::MULTI_OPTION ||
                             (*(it->second))->_type == Argument::MULTI_INFINITE_OPTION ||
                             (*(it->second))->_type == Argument::MULTI_NUMBER_OPTION)) {
            hasArg = true;
            arg = options.substr(i + 1, options.size() - i);
            (*(it->second))->_isExist = true;
            ++(*(it->second))->_count;
            parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(), arg.c_str(), *(it->second));
            return;
        }
        else if ((*(it->second))->_type != Argument::BOOLEAN_OPTION &&
                 (*(it->second))->_type != Argument::REVERSE_BOOLEAN_OPTION) {
            throw ParseArgumentException(charOption.c_str(), "only last option can be use a parameter");
        }
        (*(it->second))->_isExist = true;
        ++(*(it->second))->_count;
    }
    // get last option
    std::string charOption(options, options.size() - 1, 1);
    it = _argumentFromName.find("-" + charOption);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(charOption.c_str(), "invalid option");
    }
    parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(), arg.c_str(), *(it->second));
}

inline void Argparsor::parseLongArgument(int maxIndex, char* argv[], int* index) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    it = _argumentFromName.find(option);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(option.c_str() + PREFIX_SIZEOF_LONG_OPTION, "invalid option");
    }
    parseArgument(maxIndex, argv, index, hasArg, option.c_str() + PREFIX_SIZEOF_LONG_OPTION, arg.c_str(),
                  *(it->second));
}

inline void Argparsor::parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                              Argument* argument) {
    if (hasArg) {
        switch (argument->_type) {
            case Argument::SIMPLE_OPTION:
                argument->_argument = arg;
                break;
            case Argument::NUMBER_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                throw ParseArgumentException(option, "option cannot use with only 1 argument");
                break;
            case Argument::INFINITE_OPTION: {
                argument->clear();
                argument->push_back(arg);
                break;
            }
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                argument->push_back(arg);
                break;
            }
            default:
                throw ParseArgumentException(option, "option cannot use with argument");
                break;
        }
    }
    else {
        switch (argument->_type) {
            case Argument::SIMPLE_OPTION:
                if (*index + 1 >= maxIndex) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ++(*index);
                argument->_argument = argv[*index];
                break;
            case Argument::NUMBER_OPTION:
                argument->clear();
                if (*index + argument->_nargs >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                for (unsigned int i = *index + 1; i <= (*index + argument->_nargs); ++i) {
                    argument->push_back(argv[i]);
                }
                *index += argument->_nargs;
                break;
            case Argument::INFINITE_OPTION: {
                argument->clear();
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; ++i) {
                    if (endOfInfiniteArgument(argv[i])) {
                        break;
                    }
                    argument->push_back(argv[i]);
                    ++countArg;
                }
                *index += countArg;
                break;
            }
            case Argument::MULTI_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                if (*index + 1 >= maxIndex) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ++(*index);
                argument->push_back(argv[*index]);
                break;
            }
            case Argument::MULTI_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; ++i) {
                    if (endOfInfiniteArgument(argv[i])) {
                        break;
                    }
                    argument->push_back(argv[i]);
                    ++countArg;
                }
                *index += countArg;
                break;
            }
            case Argument::MULTI_NUMBER_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                if (*index + argument->_nargs >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ArgumentElement newNumberArgument;
                for (unsigned int i = *index + 1; i <= *index + argument->_nargs; ++i) {
                    newNumberArgument.push_back(argv[i]);
                }
                argument->push_back(newNumberArgument);
                *index += argument->_nargs;
                break;
            }
            case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; i += argument->_nargs) {
                    if (endOfInfiniteArgument(argv[i])) {
                        break;
                    }
                    if (i + argument->_nargs > static_cast<unsigned int>(maxIndex)) {
                        throw ParseArgumentException(option, "bad number of argument");
                    }
                    ArgumentElement newNumberArgument;
                    for (unsigned int j = i; j < i + argument->_nargs; ++j) {
                        newNumberArgument.push_back(argv[j]);
                        ++countArg;
                    }
                    argument->push_back(newNumberArgument);
                }
                *index += countArg;
                break;
            }
            default:
                break;
        }
    }
    argument->_isExist = true;
    ++argument->_count;
}

inline bool Argparsor::endOfInfiniteArgument(const char* argument) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    if (isShortOption(argument)) {
        bool hasArg = takeArg(argument, &option, &arg);
        if (_isAlternative) {
            it = _argumentFromName.find("-" + option);
            if (it != _argumentFromName.end()) {
                return true;
            }
        }
        // get firsts option
        for (std::size_t i = 1; i < option.size() - 1; ++i) {
            std::string charOption(option, i, 1);
            it = _argumentFromName.find("-" + charOption);
            if (it == _argumentFromName.end()) {
                return false;
            }
            else if (!hasArg && ((*(it->second))->_type == Argument::SIMPLE_OPTION ||
                                 (*(it->second))->_type == Argument::NUMBER_OPTION ||
                                 (*(it->second))->_type == Argument::INFINITE_OPTION ||
                                 (*(it->second))->_type == Argument::MULTI_OPTION ||
                                 (*(it->second))->_type == Argument::MULTI_INFINITE_OPTION ||
                                 (*(it->second))->_type == Argument::MULTI_NUMBER_OPTION)) {
                return true;
            }
            else if ((*(it->second))->_type == Argument::BOOLEAN_OPTION ||
                     (*(it->second))->_type == Argument::REVERSE_BOOLEAN_OPTION) {
                return true;
            }
        }
        // get last option
        std::string charOption(option, option.size() - 1, 1);
        it = _argumentFromName.find("-" + charOption);
    }
    else if (isLongOption(argument)) {
        takeArg(argument, &option, &arg);
        it = _argumentFromName.find(option);
    }
    else {
        return false;
    }
    if (it == _argumentFromName.end()) {
        return false;
    }
    return true;
}

inline void Argparsor::parsePositionnalArgument(char* argv[], int* index) {
    std::list<Argument*>::iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        // assign to first not used positional argument
        if ((*it)->_type == Argument::POSITIONAL_ARGUMENT && (*it)->_isExist == false) {
            (*it)->_argument = argv[*index];
            (*it)->_isExist = true;
            break;
        }
    }
    if (it == _arguments.end()) {
        if (_isStrict) {
            throw ParseArgumentException(argv[*index], "invalid additional argument");
        }
        else {
            _additionalArguments.push_back(argv[*index]);
        }
    }
}

} // namespace argparsor

} // namespace mblet
/**
 * argparsor-argument.cpp
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

#include <algorithm>
#include <sstream>

// #include "mblet/argparsor/action.h"

// #include "mblet/argparsor/argparsor.h"

// #include "mblet/argparsor/argument.h"

// #include "mblet/argparsor/utils.h"


#define PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace mblet {

namespace argparsor {

static inline bool compareFlag(const std::string& first, const std::string& second) {
    if (isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return first < second;
    }
    else if (isShortOption(first.c_str()) && !isShortOption(second.c_str())) {
        return true;
    }
    else if (!isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return false;
    }
    else {
        return first < second;
    }
}

/*
################################################################################
 ArgumentElement
################################################################################
*/

inline ArgumentElement::ArgumentElement() :
    std::vector<ArgumentElement>(),
    _argument(),
    _default(),
    _isNumber(false),
    _number(0.0) {}
inline ArgumentElement::ArgumentElement(const ArgumentElement& rhs) :
    std::vector<ArgumentElement>(rhs),
    _argument(rhs._argument),
    _default(rhs._default),
    _isNumber(rhs._isNumber),
    _number(rhs._number) {}
inline ArgumentElement::ArgumentElement(const char* arg_, const char* default_) :
    std::vector<ArgumentElement>(),
    _argument(arg_),
    _default(default_),
    _isNumber(false),
    _number(0.0) {}
inline ArgumentElement::ArgumentElement(const char* arg) :
    std::vector<ArgumentElement>(),
    _argument(arg),
    _default(),
    _isNumber(false),
    _number(0.0) {}
inline ArgumentElement::~ArgumentElement() {}

inline ArgumentElement::operator std::vector<std::string>() const {
    if (!empty() && front().empty()) {
        std::vector<std::string> ret;
        for (std::size_t i = 0; i < size(); ++i) {
            ret.push_back(at(i)._argument);
        }
        return ret;
    }
    throw Exception("convertion to vector of string not authorized");
}

/*
################################################################################
 Argument
################################################################################
*/

inline Argument::Argument(Argparsor& argparsor) :
    ArgumentElement(),
    _argparsor(argparsor),
    _nameOrFlags(),
    _type(SIMPLE_OPTION),
    _isExist(false),
    _isRequired(false),
    _count(0),
    _nargs(1),
    _help(),
    _metavar(),
    _valid(NULL),
    _validDeletable(true),
    _this(NULL),
    _action(Action::NONE),
    _defaults() {}

inline Argument::Argument(const Argument& rhs) :
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
    _validDeletable(rhs._validDeletable),
    _this(rhs._this),
    _action(rhs._action),
    _defaults() {}

inline Argument::~Argument() {
    if (_valid != NULL && _validDeletable) {
        delete _valid;
    }
}

inline std::string Argument::getString() const {
    if (_type == BOOLEAN_OPTION) {
        return ((_isExist) ? "true" : "false");
    }
    else if (_type == REVERSE_BOOLEAN_OPTION) {
        return ((_isExist) ? "false" : "true");
    }
    else {
        std::ostringstream oss("");
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                if (i > 0) {
                    oss << ", ";
                }
                if (!at(i).empty()) {
                    oss << "(";
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
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

inline Argument::operator std::vector<std::string>() const {
    std::vector<std::string> ret;
    switch (_type) {
        case POSITIONAL_ARGUMENT:
        case SIMPLE_OPTION:
            ret.push_back(_argument);
            break;
        case NUMBER_OPTION:
        case MULTI_OPTION:
        case INFINITE_OPTION:
        case MULTI_INFINITE_OPTION:
            for (std::size_t i = 0; i < size(); ++i) {
                ret.push_back(at(i)._argument);
            }
            break;
        case MULTI_NUMBER_OPTION:
        case MULTI_NUMBER_INFINITE_OPTION:
            for (std::size_t i = 0; i < size(); ++i) {
                for (std::size_t j = 0; j < at(i).size(); ++j) {
                    ret.push_back(at(i).at(j)._argument);
                }
            }
            break;
        default:
            throw Exception("convertion to vector of string not authorized");
            break;
    }
    return ret;
}

inline Argument::operator std::vector<std::vector<std::string> >() const {
    std::vector<std::vector<std::string> > ret;
    switch (_type) {
        case MULTI_NUMBER_OPTION:
        case MULTI_NUMBER_INFINITE_OPTION:
            for (std::size_t i = 0; i < size(); ++i) {
                ret.push_back(std::vector<std::string>());
                for (std::size_t j = 0; j < at(i).size(); ++j) {
                    ret[i].push_back(at(i).at(j)._argument);
                }
            }
            break;
        default:
            throw Exception("convertion to vector of vector of string not authorized");
            break;
    }
    return ret;
}

inline Argument& Argument::flag(const char* flag_) {
    if (_type == POSITIONAL_ARGUMENT) {
        throw ArgumentException(flag_, "can't add flag in positionnal argument");
    }
    validFormatFlag(flag_);
    if (_argparsor.argumentExist(flag_)) {
        throw ArgumentException(flag_, "invalid flag already exist");
    }
    _nameOrFlags.push_back(flag_);
    _sortNameOrFlags();
    _argparsor._argumentFromName.insert(std::pair<std::string, Argument**>(flag_, _this));
    _argparsor._arguments.sort(&Argument::compareOption);
    return *this;
}

inline Argument& Argument::required(bool required_) {
    _isRequired = required_;
    _argparsor._arguments.sort(&Argument::compareOption);
    return *this;
}

inline void Argument::_sortNameOrFlags() {
    std::sort(_nameOrFlags.begin(), _nameOrFlags.end(), &compareFlag);
}

inline void Argument::validFormatFlag(const char* flag) {
    if (flag[0] != '-') {
        throw ArgumentException(flag, "invalid flag not start by '-' character");
    }
    if (flag[0] == '-' && flag[1] == '\0') {
        throw ArgumentException(flag, "invalid flag not be only '-' character");
    }
    if (flag[0] == '-' && flag[1] == '-' && flag[2] == '\0') {
        throw ArgumentException(flag, "invalid flag not be only '--' characters");
    }
    if (flag[0] == '-' && flag[1] != '-' && flag[2] != '\0') {
        throw ArgumentException(flag, "invalid short flag has not only one character");
    }
}

inline bool Argument::compareOption(const Argument* first, const Argument* second) {
    if (first->_type == Argument::POSITIONAL_ARGUMENT && first->_isRequired &&
        second->_type == Argument::POSITIONAL_ARGUMENT && second->_isRequired) {
        return false;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT && first->_isRequired &&
             second->_type == Argument::POSITIONAL_ARGUMENT) {
        return true;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT && second->_type == Argument::POSITIONAL_ARGUMENT &&
             second->_isRequired) {
        return false;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT && second->_type == Argument::POSITIONAL_ARGUMENT) {
        return false;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT) {
        return false;
    }
    else if (second->_type == Argument::POSITIONAL_ARGUMENT) {
        return true;
    }
    if (isShortOption(first->_nameOrFlags.front().c_str()) && isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return first->_nameOrFlags.front() < second->_nameOrFlags.front();
        }
    }
    else if (isShortOption(first->_nameOrFlags.front().c_str()) &&
             !isShortOption(second->_nameOrFlags.front().c_str())) {
        /*
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else
        */
        if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (!isShortOption(first->_nameOrFlags.front().c_str()) &&
             isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        return first->_nameOrFlags.front() < second->_nameOrFlags.front();
    }
}

inline void Argument::_toNumber() {
    if (_type == BOOLEAN_OPTION || _type == REVERSE_BOOLEAN_OPTION) {
        return;
    }
    else {
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                if (!at(i).empty()) {
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
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

inline std::string Argument::_metavarDefault() {
    const char* flag = NULL;
    // get short or long name
    for (std::size_t i = 0; i < _nameOrFlags.size(); ++i) {
        if (_nameOrFlags[i][0] == '-' && _nameOrFlags[i][1] == '-') {
            flag = _nameOrFlags[i].c_str() + PREFIX_SIZEOF_LONG_OPTION;
            break;
        }
        else if (flag == NULL && _nameOrFlags[i][0] == '-' && _nameOrFlags[i][1] != '-') {
            flag = _nameOrFlags[i].c_str() + PREFIX_SIZEOF_SHORT_OPTION;
        }
    }
    // create a defaultUsageName from longName or shortName
    std::string defaultUsageName = flag;
    for (std::size_t i = 0; i < defaultUsageName.size(); ++i) {
        defaultUsageName[i] = ::toupper(defaultUsageName[i]);
    }

    if (_action == Action::INFINITE || _nargs == '+') {
        return defaultUsageName + "...";
    }
    else if (_nargs > 1) {
        std::string numberDefaultUsageName;
        for (std::size_t i = 0; i < _nargs; ++i) {
            if (i > 0) {
                numberDefaultUsageName += " ";
            }
            numberDefaultUsageName += defaultUsageName;
        }
        return numberDefaultUsageName;
    }
    else {
        return defaultUsageName;
    }
}

inline void Argument::_typeConstructor() {
    if (_type == Argument::POSITIONAL_ARGUMENT) {
        throw ArgumentException(_nameOrFlags.front().c_str(), "positional argument cannot use action or nargs");
    }
    if (_nargs == 0 || _action == Action::STORE_TRUE) {
        _nargs = 0;
        _type = Argument::BOOLEAN_OPTION;
    }
    else if (_action == Action::STORE_FALSE) {
        _nargs = 0;
        _type = Argument::REVERSE_BOOLEAN_OPTION;
    }
    else if (_action == Action::HELP) {
        if (_argparsor._helpOption == NULL) {
            _argparsor._helpOption = this;
        }
        if (_argparsor._helpOption != NULL && _argparsor._helpOption != this) {
            throw ArgumentException(_nameOrFlags.front().c_str(), "help action already defined");
        }
        _nargs = 0;
        _type = Argument::HELP_OPTION;
    }
    else if (_action == Action::VERSION) {
        if (_argparsor._versionOption == NULL) {
            _argparsor._versionOption = this;
        }
        if (_argparsor._versionOption != NULL && _argparsor._versionOption != this) {
            throw ArgumentException(_nameOrFlags.front().c_str(), "version action already defined");
        }
        _nargs = 0;
        _type = Argument::VERSION_OPTION;
    }
    // is simple
    else if (_nargs == 1 && _action == Action::NONE) {
        _type = Argument::SIMPLE_OPTION;
    }
    // is infinite
    else if ((_nargs == '+' && _action == Action::NONE) || _action == Action::INFINITE) {
        _nargs = 1;
        _action = Action::INFINITE;
        _type = Argument::INFINITE_OPTION;
    }
    // is number
    else if (_nargs > 1 && _action == Action::NONE) {
        _type = Argument::NUMBER_OPTION;
    }
    // is multi
    else if (_nargs == 1 && _action == Action::APPEND) {
        _type = Argument::MULTI_OPTION;
    }
    // is multi number
    else if (_nargs > 1 && _action == Action::APPEND) {
        _type = Argument::MULTI_NUMBER_OPTION;
    }
    // is multi infinite
    else if (_nargs == 1 && _action == Action::EXTEND) {
        _type = Argument::MULTI_INFINITE_OPTION;
    }
    // is multi number infinite
    else if (_nargs > 1 && _action == Action::EXTEND) {
        _type = Argument::MULTI_NUMBER_INFINITE_OPTION;
    }
}

inline void Argument::_defaultsConstructor() {
    // default arguments
    if (_nargs > 0 && _defaults.size() > 0) {
        clear();
        if (_type == Argument::POSITIONAL_ARGUMENT || _type == Argument::SIMPLE_OPTION) {
            if (_defaults.size() != _nargs) {
                throw ArgumentException(_nameOrFlags.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            _argument = _defaults.front();
            _default = _defaults.front();
        }
        if (_type == Argument::NUMBER_OPTION) {
            if (_defaults.size() != _nargs) {
                throw ArgumentException(_nameOrFlags.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            _default = "";
            for (std::size_t i = 0; i < _defaults.size(); ++i) {
                if (i > 0) {
                    _default += ", ";
                }
                _default += _defaults[i];
                push_back(ArgumentElement(_defaults[i].c_str(), _defaults[i].c_str()));
            }
        }
        if (_type == Argument::MULTI_OPTION || _type == Argument::INFINITE_OPTION ||
            _type == Argument::MULTI_INFINITE_OPTION) {
            _default = "";
            for (std::size_t i = 0; i < _defaults.size(); ++i) {
                if (i > 0) {
                    _default += ", ";
                }
                _default += _defaults[i];
                push_back(ArgumentElement(_defaults[i].c_str(), _defaults[i].c_str()));
            }
        }
        if (_type == Argument::MULTI_NUMBER_OPTION || _type == Argument::MULTI_NUMBER_INFINITE_OPTION) {
            if (_defaults.size() % _nargs != 0) {
                throw ArgumentException(_nameOrFlags.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            for (std::size_t i = 0; i < _defaults.size() / _nargs; ++i) {
                if (i > 0) {
                    _default += ", ";
                }
                _default += "(";
                ArgumentElement newNumberArgument;
                for (std::size_t j = 0; j < _nargs; ++j) {
                    if (j > 0) {
                        _default += ", ";
                        newNumberArgument._default += ", ";
                    }
                    _default += _defaults[i * _nargs + j];
                    newNumberArgument._default += _defaults[i * _nargs + j];
                    newNumberArgument.push_back(
                        ArgumentElement(_defaults[i * _nargs + j].c_str(), _defaults[i * _nargs + j].c_str()));
                }
                _default += ")";
                push_back(newNumberArgument);
            }
        }
    }
    else if (_type == Argument::VERSION_OPTION) {
        clear();
        for (std::size_t i = 0; i < _defaults.size(); ++i) {
            if (i > 0) {
                _default += "\n";
            }
            _default += _defaults[i];
        }
    }
}

} // namespace argparsor

} // namespace mblet
/**
 * argparsor-valid.cpp
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

#include <sys/stat.h>

#include <cstdlib>
#include <sstream>

// #include "mblet/argparsor/exception.h"

// #include "mblet/argparsor/valid.h"


namespace mblet {

namespace argparsor {

/*
################################################################################
 ValidNumber
################################################################################
*/
inline ValidNumber::ValidNumber() {}
inline ValidNumber::~ValidNumber() {}

inline bool ValidNumber::isValid(std::vector<std::string>& args) {
    for (std::size_t i = 0; i < args.size(); ++i) {
        char* endPtr = NULL;
        ::strtod(args[i].c_str(), &endPtr);
        if (endPtr != NULL && endPtr[0] != '\0') {
            std::ostringstream oss("");
            oss << "\"" << args[i] << "\" is not a number";
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidMinMax
################################################################################
*/

inline ValidMinMax::ValidMinMax(double min, double max) :
    _min(min),
    _max(max) {
    // bad initialized reverse value
    if (min > max) {
        _min = max;
        _max = min;
    }
}

inline ValidMinMax::~ValidMinMax() {}

inline bool ValidMinMax::isValid(std::vector<std::string>& args) {
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::stringstream ssArg("");
        ssArg << args[i];
        double number;
        if (!(ssArg >> number)) {
            std::ostringstream oss("");
            oss << "\"" << args[i] << "\" is not a number";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (number < _min || number > _max) {
            std::ostringstream oss("");
            oss << args[i] << " is not between " << _min << " and " << _max;
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidChoise
################################################################################
*/

inline ValidChoise::ValidChoise(const std::vector<std::string>& choises) :
    _choises(choises) {}

inline ValidChoise::~ValidChoise() {}

inline bool ValidChoise::isValid(std::vector<std::string>& args) {
    std::ostringstream ossChoise("");
    for (std::size_t i = 0; i < _choises.size(); ++i) {
        if (i > 0) {
            ossChoise << ", ";
        }
        ossChoise << '\"' << _choises[i] << '\"';
    }
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::size_t j;
        for (j = 0; j < _choises.size(); ++j) {
            if (args[i] == _choises[j]) {
                break;
            }
        }
        if (j == _choises.size()) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a choise value (" << ossChoise.str() << ')';
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidPath
################################################################################
*/

inline ValidPath::ValidPath(enum eMode mode) :
    _mode(mode) {}

inline ValidPath::~ValidPath() {}

inline bool ValidPath::isValid(std::vector<std::string>& args) {
    struct stat statBuff;
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (::stat(args[i].c_str(), &statBuff) == -1) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid path";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (_mode == ValidPath::IS_DIR && !S_ISDIR(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid directory";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        else if (_mode == ValidPath::IS_FILE && !S_ISREG(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid file";
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

} // namespace argparsor

} // namespace mblet
