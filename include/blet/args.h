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

#ifndef BLET_ARGS_H_
#define BLET_ARGS_H_

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
#define ARGS_VECTOR_CAT_IMPL_(x, y) x##y
#define ARGS_VECTOR_CAT_(x, y) ARGS_VECTOR_CAT_IMPL_(x, y)
#define ARGS_VECTOR_CAT2_(x, y, z) ARGS_VECTOR_CAT_(ARGS_VECTOR_CAT_(x, y), z)
#define ARGS_VECTOR_COMMA_REPEAT_0_(m, v) /* nothing */
#define ARGS_VECTOR_COMMA_REPEAT_1_(m, v) m(1, v)
#define ARGS_VECTOR_COMMA_REPEAT_2_(m, v) ARGS_VECTOR_COMMA_REPEAT_1_(m, v), m(2, v)
#define ARGS_VECTOR_COMMA_REPEAT_3_(m, v) ARGS_VECTOR_COMMA_REPEAT_2_(m, v), m(3, v)
#define ARGS_VECTOR_COMMA_REPEAT_4_(m, v) ARGS_VECTOR_COMMA_REPEAT_3_(m, v), m(4, v)
#define ARGS_VECTOR_COMMA_REPEAT_5_(m, v) ARGS_VECTOR_COMMA_REPEAT_4_(m, v), m(5, v)
#define ARGS_VECTOR_COMMA_REPEAT_6_(m, v) ARGS_VECTOR_COMMA_REPEAT_5_(m, v), m(6, v)
#define ARGS_VECTOR_COMMA_REPEAT_7_(m, v) ARGS_VECTOR_COMMA_REPEAT_6_(m, v), m(7, v)
#define ARGS_VECTOR_COMMA_REPEAT_8_(m, v) ARGS_VECTOR_COMMA_REPEAT_7_(m, v), m(8, v)
#define ARGS_VECTOR_COMMA_REPEAT_9_(m, v) ARGS_VECTOR_COMMA_REPEAT_8_(m, v), m(9, v)
#define ARGS_VECTOR_COMMA_REPEAT_10_(m, v) ARGS_VECTOR_COMMA_REPEAT_9_(m, v), m(10, v)
#define ARGS_VECTOR_COMMA_REPEAT_11_(m, v) ARGS_VECTOR_COMMA_REPEAT_10_(m, v), m(11, v)
#define ARGS_VECTOR_COMMA_REPEAT_12_(m, v) ARGS_VECTOR_COMMA_REPEAT_11_(m, v), m(12, v)
#define ARGS_VECTOR_COMMA_REPEAT_13_(m, v) ARGS_VECTOR_COMMA_REPEAT_12_(m, v), m(13, v)
#define ARGS_VECTOR_COMMA_REPEAT_14_(m, v) ARGS_VECTOR_COMMA_REPEAT_13_(m, v), m(14, v)
#define ARGS_VECTOR_COMMA_REPEAT_15_(m, v) ARGS_VECTOR_COMMA_REPEAT_14_(m, v), m(15, v)
#define ARGS_VECTOR_COMMA_REPEAT_16_(m, v) ARGS_VECTOR_COMMA_REPEAT_15_(m, v), m(16, v)
#define ARGS_VECTOR_COMMA_REPEAT_17_(m, v) ARGS_VECTOR_COMMA_REPEAT_16_(m, v), m(17, v)
#define ARGS_VECTOR_COMMA_REPEAT_18_(m, v) ARGS_VECTOR_COMMA_REPEAT_17_(m, v), m(18, v)
#define ARGS_VECTOR_COMMA_REPEAT_19_(m, v) ARGS_VECTOR_COMMA_REPEAT_18_(m, v), m(19, v)
#define ARGS_VECTOR_COMMA_REPEAT_20_(m, v) ARGS_VECTOR_COMMA_REPEAT_19_(m, v), m(20, v)
#define ARGS_VECTOR_SEMICOLON_REPEAT_0_(m, v) /* nothing */
#define ARGS_VECTOR_SEMICOLON_REPEAT_1_(m, v) m(1, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_2_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_1_(m, v) m(2, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_3_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_2_(m, v) m(3, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_4_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_3_(m, v) m(4, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_5_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_4_(m, v) m(5, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_6_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_5_(m, v) m(6, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_7_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_6_(m, v) m(7, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_8_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_7_(m, v) m(8, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_9_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_8_(m, v) m(9, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_10_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_9_(m, v) m(10, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_11_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_10_(m, v) m(11, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_12_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_11_(m, v) m(12, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_13_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_12_(m, v) m(13, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_14_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_13_(m, v) m(14, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_15_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_14_(m, v) m(15, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_16_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_15_(m, v) m(16, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_17_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_16_(m, v) m(17, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_18_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_17_(m, v) m(18, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_19_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_18_(m, v) m(19, v);
#define ARGS_VECTOR_SEMICOLON_REPEAT_20_(m, v) ARGS_VECTOR_SEMICOLON_REPEAT_19_(m, v) m(20, v);
#define ARGS_VECTOR_ARG_(i, v) const char* ARGS_VECTOR_CAT_(s, i)
#define ARGS_VECTOR_PUSH_ARG_(i, v) v.push_back(ARGS_VECTOR_CAT_(s, i))

#define ARGS_VECTOR(nb)                                                                                       \
    static args::Vector vector(ARGS_VECTOR_CAT2_(ARGS_VECTOR_COMMA_REPEAT_, nb, _)(ARGS_VECTOR_ARG_, NULL)) { \
        args::Vector ret;                                                                                     \
        ret.reserve(nb);                                                                                      \
        ARGS_VECTOR_CAT2_(ARGS_VECTOR_SEMICOLON_REPEAT_, nb, _)                                               \
        (ARGS_VECTOR_PUSH_ARG_, ret) return ret;                                                              \
    }

    ARGS_VECTOR(0)
    ARGS_VECTOR(1)
    ARGS_VECTOR(2)
    ARGS_VECTOR(3)
    ARGS_VECTOR(4)
    ARGS_VECTOR(5)
    ARGS_VECTOR(6)
    ARGS_VECTOR(7)
    ARGS_VECTOR(8)
    ARGS_VECTOR(9)
    ARGS_VECTOR(10)
    ARGS_VECTOR(11)
    ARGS_VECTOR(12)
    ARGS_VECTOR(13)
    ARGS_VECTOR(14)
    ARGS_VECTOR(15)
    ARGS_VECTOR(16)
    ARGS_VECTOR(17)
    ARGS_VECTOR(18)
    ARGS_VECTOR(19)
    ARGS_VECTOR(20)

#undef ARGS_VECTOR
#undef ARGS_VECTOR_PUSH_ARG_
#undef ARGS_VECTOR_ARG_
#undef ARGS_VECTOR_COMMA_REPEAT_20_
#undef ARGS_VECTOR_COMMA_REPEAT_19_
#undef ARGS_VECTOR_COMMA_REPEAT_18_
#undef ARGS_VECTOR_COMMA_REPEAT_17_
#undef ARGS_VECTOR_COMMA_REPEAT_16_
#undef ARGS_VECTOR_COMMA_REPEAT_15_
#undef ARGS_VECTOR_COMMA_REPEAT_14_
#undef ARGS_VECTOR_COMMA_REPEAT_13_
#undef ARGS_VECTOR_COMMA_REPEAT_12_
#undef ARGS_VECTOR_COMMA_REPEAT_11_
#undef ARGS_VECTOR_COMMA_REPEAT_10_
#undef ARGS_VECTOR_COMMA_REPEAT_9_
#undef ARGS_VECTOR_COMMA_REPEAT_8_
#undef ARGS_VECTOR_COMMA_REPEAT_7_
#undef ARGS_VECTOR_COMMA_REPEAT_6_
#undef ARGS_VECTOR_COMMA_REPEAT_5_
#undef ARGS_VECTOR_COMMA_REPEAT_4_
#undef ARGS_VECTOR_COMMA_REPEAT_3_
#undef ARGS_VECTOR_COMMA_REPEAT_2_
#undef ARGS_VECTOR_COMMA_REPEAT_1_
#undef ARGS_VECTOR_COMMA_REPEAT_0_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_20_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_19_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_18_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_17_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_16_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_15_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_14_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_13_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_12_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_11_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_10_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_9_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_8_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_7_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_6_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_5_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_4_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_3_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_2_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_1_
#undef ARGS_VECTOR_SEMICOLON_REPEAT_0_
#undef ARGS_VECTOR_CAT2_
#undef ARGS_VECTOR_CAT_
#undef ARGS_VECTOR_CAT_IMPL_

  private:
    typedef args::Vector Vector;
};

} // namespace blet

#endif // #ifndef BLET_ARGS_H_
