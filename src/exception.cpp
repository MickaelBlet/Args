/**
 * args-exception.cpp
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

#include "blet/args/exception.h"

namespace blet {

namespace args {

Exception::Exception(const char* str) :
    std::exception(),
    str_(str) {}

Exception::~Exception() throw() {}

const char* Exception::what() const throw() {
    return str_.c_str();
}

HelpException::HelpException(const char* message) :
    Exception(message) {}

HelpException::~HelpException() throw() {}

VersionException::VersionException(const char* message) :
    Exception(message) {}

VersionException::~VersionException() throw() {}

ArgumentException::ArgumentException(const char* message) :
    Exception(message),
    argument_() {}

ArgumentException::ArgumentException(const char* argument, const char* message) :
    Exception(message),
    argument_(argument) {}

ArgumentException::~ArgumentException() throw() {}

const char* ArgumentException::argument() const throw() {
    return argument_.c_str();
}

AccessDeniedException::AccessDeniedException(const char* argument, const char* message) :
    ArgumentException(argument, message) {}

AccessDeniedException::~AccessDeniedException() throw() {}

ParseArgumentException::ParseArgumentException(const char* message) :
    ArgumentException(message) {}

ParseArgumentException::ParseArgumentException(const char* argument, const char* message) :
    ArgumentException(argument, message) {}

ParseArgumentException::~ParseArgumentException() throw() {}

ParseArgumentRequiredException::ParseArgumentRequiredException(const char* argument, const char* message) :
    ParseArgumentException(argument, message) {}

ParseArgumentRequiredException::~ParseArgumentRequiredException() throw() {}

ParseArgumentValidException::ParseArgumentValidException(const char* message) :
    ParseArgumentException(message) {}

ParseArgumentValidException::ParseArgumentValidException(const char* argument, const char* message) :
    ParseArgumentException(argument, message) {}

ParseArgumentValidException::~ParseArgumentValidException() throw() {}

} // namespace args

} // namespace blet
