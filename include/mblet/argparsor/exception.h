/**
 * argparsor/exception.h
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
    Exception(const char* str);
    virtual ~Exception() throw();
    const char* what() const throw();

  protected:
    std::string _str;
};

/**
 * @brief Argument exception from Exception
 */
class ArgumentException : public Exception {
  public:
    ArgumentException(const char* message);
    ArgumentException(const char* argument, const char* message);
    virtual ~ArgumentException() throw();
    const char* argument() const throw();

  protected:
    std::string _argument;
};

struct AccessDeniedException : public ArgumentException {
    AccessDeniedException(const char* argument, const char* message);
    virtual ~AccessDeniedException() throw();
};

struct ParseArgumentException : public ArgumentException {
    ParseArgumentException(const char* message);
    ParseArgumentException(const char* argument, const char* message);
    virtual ~ParseArgumentException() throw();
};

struct ParseArgumentRequiredException : public ParseArgumentException {
    ParseArgumentRequiredException(const char* argument, const char* message);
    virtual ~ParseArgumentRequiredException() throw();
};

struct ParseArgumentValidException : public ParseArgumentException {
    ParseArgumentValidException(const char* message);
    ParseArgumentValidException(const char* argument, const char* message);
    virtual ~ParseArgumentValidException() throw();
};

} // namespace argparsor

} // namespace mblet

#endif // #ifndef _MBLET_ARGPARSOR_EXCEPTION_H_