/**
 * argparsor.h
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

#ifndef _MBLET_ARGPARSOR_H_
#define _MBLET_ARGPARSOR_H_

#include "mblet/argparsor/action.h"
#include "mblet/argparsor/argparsor.h"
#include "mblet/argparsor/exception.h"
#include "mblet/argparsor/valid.h"
#include "mblet/argparsor/vector.h"

namespace mblet {

// simply use argparsor
class Argparsor : public argparsor::Argparsor, public argparsor::Action {
  public:
    Argparsor(bool addHelp = true) :
        argparsor::Argparsor(addHelp) {}
    ~Argparsor() {}

    typedef argparsor::Exception Exception;
    typedef argparsor::HelpException HelpException;
    typedef argparsor::VersionException VersionException;
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

/**
 * @brief Generate static vector methods
 */
#define _ARGPARSOR_VECTOR_CAT_IMPL_(x, y) x##y
#define _ARGPARSOR_VECTOR_CAT_(x, y) _ARGPARSOR_VECTOR_CAT_IMPL_(x, y)
#define _ARGPARSOR_VECTOR_CAT2_(x, y, z) _ARGPARSOR_VECTOR_CAT_(_ARGPARSOR_VECTOR_CAT_(x, y), z)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_0_(m, v) /* nothing */
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_1_(m, v) m(1, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_2_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_1_(m, v), m(2, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_3_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_2_(m, v), m(3, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_4_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_3_(m, v), m(4, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_5_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_4_(m, v), m(5, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_6_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_5_(m, v), m(6, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_7_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_6_(m, v), m(7, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_8_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_7_(m, v), m(8, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_9_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_8_(m, v), m(9, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_10_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_9_(m, v), m(10, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_11_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_10_(m, v), m(11, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_12_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_11_(m, v), m(12, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_13_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_12_(m, v), m(13, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_14_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_13_(m, v), m(14, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_15_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_14_(m, v), m(15, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_16_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_15_(m, v), m(16, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_17_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_16_(m, v), m(17, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_18_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_17_(m, v), m(18, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_19_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_18_(m, v), m(19, v)
#define _ARGPARSOR_VECTOR_COMMA_REPEAT_20_(m, v) _ARGPARSOR_VECTOR_COMMA_REPEAT_19_(m, v), m(20, v)
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_0_(m, v) /* nothing */
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_1_(m, v) m(1, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_2_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_1_(m, v) m(2, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_3_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_2_(m, v) m(3, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_4_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_3_(m, v) m(4, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_5_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_4_(m, v) m(5, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_6_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_5_(m, v) m(6, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_7_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_6_(m, v) m(7, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_8_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_7_(m, v) m(8, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_9_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_8_(m, v) m(9, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_10_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_9_(m, v) m(10, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_11_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_10_(m, v) m(11, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_12_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_11_(m, v) m(12, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_13_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_12_(m, v) m(13, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_14_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_13_(m, v) m(14, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_15_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_14_(m, v) m(15, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_16_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_15_(m, v) m(16, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_17_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_16_(m, v) m(17, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_18_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_17_(m, v) m(18, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_19_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_18_(m, v) m(19, v);
#define _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_20_(m, v) _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_19_(m, v) m(20, v);
#define _ARGPARSOR_VECTOR_ARG_(i, v) const char* _ARGPARSOR_VECTOR_CAT_(var_, i)
#define _ARGPARSOR_VECTOR_PUSH_ARG_(i, v) v.push_back(_ARGPARSOR_VECTOR_CAT_(var_, i))

#define _ARGPARSOR_VECTOR(nb)                                                                            \
    static argparsor::Vector vector(                                                                     \
        _ARGPARSOR_VECTOR_CAT2_(_ARGPARSOR_VECTOR_COMMA_REPEAT_, nb, _)(_ARGPARSOR_VECTOR_ARG_, NULL)) { \
        argparsor::Vector ret;                                                                           \
        ret.reserve(nb);                                                                                 \
        _ARGPARSOR_VECTOR_CAT2_(_ARGPARSOR_VECTOR_SEMICOLON_REPEAT_, nb, _)                              \
        (_ARGPARSOR_VECTOR_PUSH_ARG_, ret) return ret;                                                   \
    }

    _ARGPARSOR_VECTOR(0)
    _ARGPARSOR_VECTOR(1)
    _ARGPARSOR_VECTOR(2)
    _ARGPARSOR_VECTOR(3)
    _ARGPARSOR_VECTOR(4)
    _ARGPARSOR_VECTOR(5)
    _ARGPARSOR_VECTOR(6)
    _ARGPARSOR_VECTOR(7)
    _ARGPARSOR_VECTOR(8)
    _ARGPARSOR_VECTOR(9)
    _ARGPARSOR_VECTOR(10)
    _ARGPARSOR_VECTOR(11)
    _ARGPARSOR_VECTOR(12)
    _ARGPARSOR_VECTOR(13)
    _ARGPARSOR_VECTOR(14)
    _ARGPARSOR_VECTOR(15)
    _ARGPARSOR_VECTOR(16)
    _ARGPARSOR_VECTOR(17)
    _ARGPARSOR_VECTOR(18)
    _ARGPARSOR_VECTOR(19)
    _ARGPARSOR_VECTOR(20)

#undef _ARGPARSOR_VECTOR
#undef _ARGPARSOR_VECTOR_PUSH_ARG_
#undef _ARGPARSOR_VECTOR_ARG_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_20_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_19_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_18_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_17_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_16_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_15_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_14_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_13_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_12_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_11_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_10_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_9_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_8_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_7_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_6_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_5_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_4_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_3_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_2_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_1_
#undef _ARGPARSOR_VECTOR_COMMA_REPEAT_0_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_20_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_19_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_18_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_17_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_16_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_15_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_14_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_13_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_12_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_11_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_10_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_9_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_8_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_7_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_6_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_5_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_4_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_3_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_2_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_1_
#undef _ARGPARSOR_VECTOR_SEMICOLON_REPEAT_0_
#undef _ARGPARSOR_VECTOR_CAT2_
#undef _ARGPARSOR_VECTOR_CAT_
#undef _ARGPARSOR_VECTOR_CAT_IMPL_

  private:
    typedef argparsor::Vector Vector;
};

} // namespace mblet

#endif // #ifndef _MBLET_ARGPARSOR_H_