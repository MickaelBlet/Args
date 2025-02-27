/**
 * args/vector.h
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

#ifndef BLET_ARGS_VECTOR_H_
#define BLET_ARGS_VECTOR_H_

#include <string>
#include <vector>

namespace blet {

namespace args {

class Vector : public std::vector<std::string> {
  public:
    Vector() :
        std::vector<std::string>() {}

    Vector(int size) :
        std::vector<std::string>(size) {}

    template<std::size_t S>
    Vector(const char* (&v)[S]) :
        std::vector<std::string>() {
        std::vector<std::string>::reserve(S);
        for (std::size_t i = 0; i < S; ++i) {
            std::vector<std::string>::push_back(v[i]);
        }
    }

    template<std::size_t S>
    Vector(const char* const (&v)[S]) :
        std::vector<std::string>() {
        std::vector<std::string>::reserve(S);
        for (std::size_t i = 0; i < S; ++i) {
            std::vector<std::string>::push_back(v[i]);
        }
    }

    template<std::size_t S>
    Vector(const std::string (&v)[S]) :
        std::vector<std::string>() {
        std::vector<std::string>::reserve(S);
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

    template<std::size_t S>
    Vector& operator+(const char (&v)[S]) {
        std::vector<std::string>::push_back(v);
        return *this;
    }

    Vector& operator+(const char*(&v)) {
        std::vector<std::string>::push_back(v);
        return *this;
    }

    Vector& operator+(const std::string& v) {
        std::vector<std::string>::push_back(v);
        return *this;
    }
};

} // namespace args

} // namespace blet

#endif // #ifndef BLET_ARGS_VECTOR_H_
