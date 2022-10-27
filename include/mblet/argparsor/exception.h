/**
 * argparsor-exception.h
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