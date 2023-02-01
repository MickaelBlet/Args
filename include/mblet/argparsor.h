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

#define _ARGPARSOR_VECTOR_CAT_IMPL_(x, y) x##y
#define _ARGPARSOR_VECTOR_CAT_(x, y) _ARGPARSOR_VECTOR_CAT_IMPL_(x, y)
#define _ARGPARSOR_VECTOR_CAT2_(x, y, z) _ARGPARSOR_VECTOR_CAT_(_ARGPARSOR_VECTOR_CAT_(x, y), z)
#define _ARGPARSOR_VECTOR_REPEAT_0_(m, f) /* nothing */
#define _ARGPARSOR_VECTOR_REPEAT_1_(m, f) m(1, f)
#define _ARGPARSOR_VECTOR_REPEAT_2_(m, f) _ARGPARSOR_VECTOR_REPEAT_1_(m, f), m(2, f)
#define _ARGPARSOR_VECTOR_REPEAT_3_(m, f) _ARGPARSOR_VECTOR_REPEAT_2_(m, f), m(3, f)
#define _ARGPARSOR_VECTOR_REPEAT_4_(m, f) _ARGPARSOR_VECTOR_REPEAT_3_(m, f), m(4, f)
#define _ARGPARSOR_VECTOR_REPEAT_5_(m, f) _ARGPARSOR_VECTOR_REPEAT_4_(m, f), m(5, f)
#define _ARGPARSOR_VECTOR_REPEAT_6_(m, f) _ARGPARSOR_VECTOR_REPEAT_5_(m, f), m(6, f)
#define _ARGPARSOR_VECTOR_REPEAT_7_(m, f) _ARGPARSOR_VECTOR_REPEAT_6_(m, f), m(7, f)
#define _ARGPARSOR_VECTOR_REPEAT_8_(m, f) _ARGPARSOR_VECTOR_REPEAT_7_(m, f), m(8, f)
#define _ARGPARSOR_VECTOR_REPEAT_9_(m, f) _ARGPARSOR_VECTOR_REPEAT_8_(m, f), m(9, f)
#define _ARGPARSOR_VECTOR_REPEAT_10_(m, f) _ARGPARSOR_VECTOR_REPEAT_9_(m, f), m(10, f)
#define _ARGPARSOR_VECTOR_REPEAT_11_(m, f) _ARGPARSOR_VECTOR_REPEAT_10_(m, f), m(11, f)
#define _ARGPARSOR_VECTOR_REPEAT_12_(m, f) _ARGPARSOR_VECTOR_REPEAT_11_(m, f), m(12, f)
#define _ARGPARSOR_VECTOR_REPEAT_13_(m, f) _ARGPARSOR_VECTOR_REPEAT_12_(m, f), m(13, f)
#define _ARGPARSOR_VECTOR_REPEAT_14_(m, f) _ARGPARSOR_VECTOR_REPEAT_13_(m, f), m(14, f)
#define _ARGPARSOR_VECTOR_REPEAT_15_(m, f) _ARGPARSOR_VECTOR_REPEAT_14_(m, f), m(15, f)
#define _ARGPARSOR_VECTOR_REPEAT_16_(m, f) _ARGPARSOR_VECTOR_REPEAT_15_(m, f), m(16, f)
#define _ARGPARSOR_VECTOR_REPEAT_17_(m, f) _ARGPARSOR_VECTOR_REPEAT_16_(m, f), m(17, f)
#define _ARGPARSOR_VECTOR_REPEAT_18_(m, f) _ARGPARSOR_VECTOR_REPEAT_17_(m, f), m(18, f)
#define _ARGPARSOR_VECTOR_REPEAT_19_(m, f) _ARGPARSOR_VECTOR_REPEAT_18_(m, f), m(19, f)
#define _ARGPARSOR_VECTOR_REPEAT_20_(m, f) _ARGPARSOR_VECTOR_REPEAT_19_(m, f), m(20, f)
#define _ARGPARSOR_VECTOR_ARG_(i, f) const char* _ARGPARSOR_VECTOR_CAT_(var_, i)
#define _ARGPARSOR_VECTOR_PUSH_ARG_(i, f) v.push_back(_ARGPARSOR_VECTOR_CAT_(var_, i))

#define _ARGPARSOR_VECTOR(nb)                                                                       \
    static argparsor::Vector vector(                                                                \
        _ARGPARSOR_VECTOR_CAT2_(_ARGPARSOR_VECTOR_REPEAT_, nb, _)(_ARGPARSOR_VECTOR_ARG_, nb)) {    \
        argparsor::Vector v;                                                                        \
        v.reserve(nb);                                                                              \
        _ARGPARSOR_VECTOR_CAT2_(_ARGPARSOR_VECTOR_REPEAT_, nb, _)(_ARGPARSOR_VECTOR_PUSH_ARG_, nb); \
        return v;                                                                                   \
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
#undef _ARGPARSOR_VECTOR_REPEAT_20_
#undef _ARGPARSOR_VECTOR_REPEAT_19_
#undef _ARGPARSOR_VECTOR_REPEAT_18_
#undef _ARGPARSOR_VECTOR_REPEAT_17_
#undef _ARGPARSOR_VECTOR_REPEAT_16_
#undef _ARGPARSOR_VECTOR_REPEAT_15_
#undef _ARGPARSOR_VECTOR_REPEAT_14_
#undef _ARGPARSOR_VECTOR_REPEAT_13_
#undef _ARGPARSOR_VECTOR_REPEAT_12_
#undef _ARGPARSOR_VECTOR_REPEAT_11_
#undef _ARGPARSOR_VECTOR_REPEAT_10_
#undef _ARGPARSOR_VECTOR_REPEAT_9_
#undef _ARGPARSOR_VECTOR_REPEAT_8_
#undef _ARGPARSOR_VECTOR_REPEAT_7_
#undef _ARGPARSOR_VECTOR_REPEAT_6_
#undef _ARGPARSOR_VECTOR_REPEAT_5_
#undef _ARGPARSOR_VECTOR_REPEAT_4_
#undef _ARGPARSOR_VECTOR_REPEAT_3_
#undef _ARGPARSOR_VECTOR_REPEAT_2_
#undef _ARGPARSOR_VECTOR_REPEAT_1_
#undef _ARGPARSOR_VECTOR_REPEAT_0_
#undef _ARGPARSOR_VECTOR_CAT2_
#undef _ARGPARSOR_VECTOR_CAT_
#undef _ARGPARSOR_VECTOR_CAT_IMPL_

  private:
    typedef argparsor::Vector Vector;
};

} // namespace mblet

#endif // #ifndef _MBLET_ARGPARSOR_H_