/**
 * args.h
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

#ifndef _BLET_ARGS_H_
#define _BLET_ARGS_H_

#include "blet/args/action.h"
#include "blet/args/args.h"
#include "blet/args/exception.h"
#include "blet/args/valid.h"
#include "blet/args/vector.h"

namespace blet {

// simply use args
class Args : public args::Args, public args::Action {
  public:
    Args(bool addHelp = true) :
        args::Args(addHelp) {}
    ~Args() {}

    typedef args::Exception Exception;
    typedef args::HelpException HelpException;
    typedef args::VersionException VersionException;
    typedef args::ArgumentException ArgumentException;
    typedef args::ParseArgumentException ParseArgumentException;
    typedef args::ParseArgumentRequiredException ParseArgumentRequiredException;
    typedef args::ParseArgumentValidException ParseArgumentValidException;
    typedef args::AccessDeniedException AccessDeniedException;

    typedef args::IValid IValid;
    typedef args::ValidNumber ValidNumber;
    typedef args::ValidChoise ValidChoise;
    typedef args::ValidMinMax ValidMinMax;
    typedef args::ValidPath ValidPath;

/**
 * @brief Generate static vector methods
 */
#define _ARGS_VECTOR_CAT_IMPL_(x, y) x##y
#define _ARGS_VECTOR_CAT_(x, y) _ARGS_VECTOR_CAT_IMPL_(x, y)
#define _ARGS_VECTOR_CAT2_(x, y, z) _ARGS_VECTOR_CAT_(_ARGS_VECTOR_CAT_(x, y), z)
#define _ARGS_VECTOR_COMMA_REPEAT_0_(m, v) /* nothing */
#define _ARGS_VECTOR_COMMA_REPEAT_1_(m, v) m(1, v)
#define _ARGS_VECTOR_COMMA_REPEAT_2_(m, v) _ARGS_VECTOR_COMMA_REPEAT_1_(m, v), m(2, v)
#define _ARGS_VECTOR_COMMA_REPEAT_3_(m, v) _ARGS_VECTOR_COMMA_REPEAT_2_(m, v), m(3, v)
#define _ARGS_VECTOR_COMMA_REPEAT_4_(m, v) _ARGS_VECTOR_COMMA_REPEAT_3_(m, v), m(4, v)
#define _ARGS_VECTOR_COMMA_REPEAT_5_(m, v) _ARGS_VECTOR_COMMA_REPEAT_4_(m, v), m(5, v)
#define _ARGS_VECTOR_COMMA_REPEAT_6_(m, v) _ARGS_VECTOR_COMMA_REPEAT_5_(m, v), m(6, v)
#define _ARGS_VECTOR_COMMA_REPEAT_7_(m, v) _ARGS_VECTOR_COMMA_REPEAT_6_(m, v), m(7, v)
#define _ARGS_VECTOR_COMMA_REPEAT_8_(m, v) _ARGS_VECTOR_COMMA_REPEAT_7_(m, v), m(8, v)
#define _ARGS_VECTOR_COMMA_REPEAT_9_(m, v) _ARGS_VECTOR_COMMA_REPEAT_8_(m, v), m(9, v)
#define _ARGS_VECTOR_COMMA_REPEAT_10_(m, v) _ARGS_VECTOR_COMMA_REPEAT_9_(m, v), m(10, v)
#define _ARGS_VECTOR_COMMA_REPEAT_11_(m, v) _ARGS_VECTOR_COMMA_REPEAT_10_(m, v), m(11, v)
#define _ARGS_VECTOR_COMMA_REPEAT_12_(m, v) _ARGS_VECTOR_COMMA_REPEAT_11_(m, v), m(12, v)
#define _ARGS_VECTOR_COMMA_REPEAT_13_(m, v) _ARGS_VECTOR_COMMA_REPEAT_12_(m, v), m(13, v)
#define _ARGS_VECTOR_COMMA_REPEAT_14_(m, v) _ARGS_VECTOR_COMMA_REPEAT_13_(m, v), m(14, v)
#define _ARGS_VECTOR_COMMA_REPEAT_15_(m, v) _ARGS_VECTOR_COMMA_REPEAT_14_(m, v), m(15, v)
#define _ARGS_VECTOR_COMMA_REPEAT_16_(m, v) _ARGS_VECTOR_COMMA_REPEAT_15_(m, v), m(16, v)
#define _ARGS_VECTOR_COMMA_REPEAT_17_(m, v) _ARGS_VECTOR_COMMA_REPEAT_16_(m, v), m(17, v)
#define _ARGS_VECTOR_COMMA_REPEAT_18_(m, v) _ARGS_VECTOR_COMMA_REPEAT_17_(m, v), m(18, v)
#define _ARGS_VECTOR_COMMA_REPEAT_19_(m, v) _ARGS_VECTOR_COMMA_REPEAT_18_(m, v), m(19, v)
#define _ARGS_VECTOR_COMMA_REPEAT_20_(m, v) _ARGS_VECTOR_COMMA_REPEAT_19_(m, v), m(20, v)
#define _ARGS_VECTOR_SEMICOLON_REPEAT_0_(m, v) /* nothing */
#define _ARGS_VECTOR_SEMICOLON_REPEAT_1_(m, v) m(1, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_2_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_1_(m, v) m(2, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_3_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_2_(m, v) m(3, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_4_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_3_(m, v) m(4, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_5_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_4_(m, v) m(5, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_6_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_5_(m, v) m(6, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_7_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_6_(m, v) m(7, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_8_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_7_(m, v) m(8, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_9_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_8_(m, v) m(9, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_10_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_9_(m, v) m(10, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_11_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_10_(m, v) m(11, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_12_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_11_(m, v) m(12, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_13_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_12_(m, v) m(13, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_14_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_13_(m, v) m(14, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_15_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_14_(m, v) m(15, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_16_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_15_(m, v) m(16, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_17_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_16_(m, v) m(17, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_18_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_17_(m, v) m(18, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_19_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_18_(m, v) m(19, v);
#define _ARGS_VECTOR_SEMICOLON_REPEAT_20_(m, v) _ARGS_VECTOR_SEMICOLON_REPEAT_19_(m, v) m(20, v);
#define _ARGS_VECTOR_ARG_(i, v) const char* _ARGS_VECTOR_CAT_(var_, i)
#define _ARGS_VECTOR_PUSH_ARG_(i, v) v.push_back(_ARGS_VECTOR_CAT_(var_, i))

#define _ARGS_VECTOR(nb)                                                                                         \
    static args::Vector vector(_ARGS_VECTOR_CAT2_(_ARGS_VECTOR_COMMA_REPEAT_, nb, _)(_ARGS_VECTOR_ARG_, NULL)) { \
        args::Vector ret;                                                                                        \
        ret.reserve(nb);                                                                                         \
        _ARGS_VECTOR_CAT2_(_ARGS_VECTOR_SEMICOLON_REPEAT_, nb, _)                                                \
        (_ARGS_VECTOR_PUSH_ARG_, ret) return ret;                                                                \
    }

    _ARGS_VECTOR(0)
    _ARGS_VECTOR(1)
    _ARGS_VECTOR(2)
    _ARGS_VECTOR(3)
    _ARGS_VECTOR(4)
    _ARGS_VECTOR(5)
    _ARGS_VECTOR(6)
    _ARGS_VECTOR(7)
    _ARGS_VECTOR(8)
    _ARGS_VECTOR(9)
    _ARGS_VECTOR(10)
    _ARGS_VECTOR(11)
    _ARGS_VECTOR(12)
    _ARGS_VECTOR(13)
    _ARGS_VECTOR(14)
    _ARGS_VECTOR(15)
    _ARGS_VECTOR(16)
    _ARGS_VECTOR(17)
    _ARGS_VECTOR(18)
    _ARGS_VECTOR(19)
    _ARGS_VECTOR(20)

#undef _ARGS_VECTOR
#undef _ARGS_VECTOR_PUSH_ARG_
#undef _ARGS_VECTOR_ARG_
#undef _ARGS_VECTOR_COMMA_REPEAT_20_
#undef _ARGS_VECTOR_COMMA_REPEAT_19_
#undef _ARGS_VECTOR_COMMA_REPEAT_18_
#undef _ARGS_VECTOR_COMMA_REPEAT_17_
#undef _ARGS_VECTOR_COMMA_REPEAT_16_
#undef _ARGS_VECTOR_COMMA_REPEAT_15_
#undef _ARGS_VECTOR_COMMA_REPEAT_14_
#undef _ARGS_VECTOR_COMMA_REPEAT_13_
#undef _ARGS_VECTOR_COMMA_REPEAT_12_
#undef _ARGS_VECTOR_COMMA_REPEAT_11_
#undef _ARGS_VECTOR_COMMA_REPEAT_10_
#undef _ARGS_VECTOR_COMMA_REPEAT_9_
#undef _ARGS_VECTOR_COMMA_REPEAT_8_
#undef _ARGS_VECTOR_COMMA_REPEAT_7_
#undef _ARGS_VECTOR_COMMA_REPEAT_6_
#undef _ARGS_VECTOR_COMMA_REPEAT_5_
#undef _ARGS_VECTOR_COMMA_REPEAT_4_
#undef _ARGS_VECTOR_COMMA_REPEAT_3_
#undef _ARGS_VECTOR_COMMA_REPEAT_2_
#undef _ARGS_VECTOR_COMMA_REPEAT_1_
#undef _ARGS_VECTOR_COMMA_REPEAT_0_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_20_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_19_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_18_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_17_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_16_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_15_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_14_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_13_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_12_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_11_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_10_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_9_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_8_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_7_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_6_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_5_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_4_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_3_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_2_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_1_
#undef _ARGS_VECTOR_SEMICOLON_REPEAT_0_
#undef _ARGS_VECTOR_CAT2_
#undef _ARGS_VECTOR_CAT_
#undef _ARGS_VECTOR_CAT_IMPL_

  private:
    typedef args::Vector Vector;
};

} // namespace blet

#endif // #ifndef _BLET_ARGS_H_