/**
 * MockC
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2021 BLET Mickaël.
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

#ifndef _MOCKC_H_
#define _MOCKC_H_

#ifdef MOCKC_DLFCN
#include <dlfcn.h>
#endif

#include <gmock/gmock.h>

#define MOCKC_CAT_IMPL_(x, y) x##y
#define MOCKC_CAT_(x, y) MOCKC_CAT_IMPL_(x, y)
#define MOCKC_CAT2_(x, y, z) MOCKC_CAT_(MOCKC_CAT_(x, y), z)
#define MOCKC_STRINGIFY_(x) #x
#define MOCKC_TO_STRING_(x) MOCKC_STRINGIFY_(x)

#define MOCKC_REPEAT_0_(m, f) /* nothing */
#define MOCKC_REPEAT_1_(m, f) m(1, f)
#define MOCKC_REPEAT_2_(m, f) MOCKC_REPEAT_1_(m, f), m(2, f)
#define MOCKC_REPEAT_3_(m, f) MOCKC_REPEAT_2_(m, f), m(3, f)
#define MOCKC_REPEAT_4_(m, f) MOCKC_REPEAT_3_(m, f), m(4, f)
#define MOCKC_REPEAT_5_(m, f) MOCKC_REPEAT_4_(m, f), m(5, f)
#define MOCKC_REPEAT_6_(m, f) MOCKC_REPEAT_5_(m, f), m(6, f)
#define MOCKC_REPEAT_7_(m, f) MOCKC_REPEAT_6_(m, f), m(7, f)
#define MOCKC_REPEAT_8_(m, f) MOCKC_REPEAT_7_(m, f), m(8, f)
#define MOCKC_REPEAT_9_(m, f) MOCKC_REPEAT_8_(m, f), m(9, f)
#define MOCKC_REPEAT_10_(m, f) MOCKC_REPEAT_9_(m, f), m(10, f)

#define MOCKC_ARG_(i, f) MOCKC_CAT_(var_, i)
#define MOCKC_ARG_DECLARATION_(i, f) GMOCK_ARG_(, i, f) MOCKC_ARG_(i, f)

#ifdef MOCKC_DLFCN
/* template guard */
template<typename T>
struct MockCGuard {
    MockCGuard(T& mockC) :
        refMockC(mockC) {
        refMockC.isActive = true;
    }
    ~MockCGuard() {
        refMockC.isActive = false;
    }
    T& refMockC;
};
template<typename T>
struct MockCGuardReverse {
    MockCGuardReverse(T& mockC) :
        refMockC(mockC) {
        refMockC.isActive = false;
    }
    ~MockCGuardReverse() {
        refMockC.isActive = true;
    }
    T& refMockC;
};
#define MOCKC_GUARD(n) MockCGuard<MOCKC_CAT_(MockC_, n)> MOCKC_CAT_(mockCGuard_, n)(MOCKC_CAT_(MockC_, n)::instance());
#define MOCKC_GUARD_REVERSE(n) \
    MockCGuardReverse<MOCKC_CAT_(MockC_, n)> MOCKC_CAT_(mockCGuardReverse_, n)(MOCKC_CAT_(MockC_, n)::instance());

#define MOCKC_(i, n, f)                                                                                          \
                                                                                                                 \
    struct MOCKC_CAT_(MockC_, n) {                                                                               \
        typedef GMOCK_RESULT_(, f) (*func_t)(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, f));       \
        MOCKC_CAT_(MockC_, n)                                                                                    \
        () :                                                                                                     \
            isActive(false),                                                                                     \
            real((func_t)dlsym(RTLD_NEXT, #n)) {                                                                 \
            return;                                                                                              \
        }                                                                                                        \
        MOCKC_CAT_(MOCK_METHOD, i)(n, f);                                                                        \
        static MOCKC_CAT_(MockC_, n) & instance() {                                                              \
            static MOCKC_CAT_(MockC_, n) singleton;                                                              \
            return singleton;                                                                                    \
        }                                                                                                        \
        bool isActive;                                                                                           \
        func_t real;                                                                                             \
    };                                                                                                           \
                                                                                                                 \
    struct MOCKC_CAT_(Exception_, n) :                                                                           \
        public std::exception {                                                                                  \
        MOCKC_CAT_(Exception_, n)                                                                                \
        (const char* str) throw() :                                                                              \
            str(str) {                                                                                           \
            return;                                                                                              \
        }                                                                                                        \
        virtual ~MOCKC_CAT_(Exception_, n)() throw() { return; }                                                 \
        virtual const char* what() const throw() { return str.c_str(); }                                         \
        const std::string str;                                                                                   \
    };                                                                                                           \
                                                                                                                 \
    GMOCK_RESULT_(, f) n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, f)) {                          \
        if (MOCKC_CAT_(MockC_, n)::instance().isActive) {                                                        \
            MOCKC_GUARD_REVERSE(n);                                                                              \
            return MOCKC_CAT_(MockC_, n)::instance().n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));         \
        }                                                                                                        \
        if (MOCKC_CAT_(MockC_, n)::instance().real == NULL) {                                                    \
            throw MOCKC_CAT_(Exception_,                                                                         \
                             n)(__FILE__ ":" MOCKC_TO_STRING_(__LINE__) ": real function \"" #n "\" not found"); \
        }                                                                                                        \
        return MOCKC_CAT_(MockC_, n)::instance().real(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));          \
    }
#define MOCKC_ENABLE(n) MOCKC_CAT_(MockC_, n)::instance().isActive = true;
#define MOCKC_DISABLE(n) MOCKC_CAT_(MockC_, n)::instance().isActive = false;

#else // ! MOCKC_DLFCN

#define MOCKC_(i, n, f)                                                                              \
    struct MOCKC_CAT_(MockC_, n) {                                                                   \
        MOCKC_CAT_(MOCK_METHOD, i)(n, f);                                                            \
        static MOCKC_CAT_(MockC_, n) & instance() {                                                  \
            static MOCKC_CAT_(MockC_, n) singleton;                                                  \
            return singleton;                                                                        \
        }                                                                                            \
    };                                                                                               \
    GMOCK_RESULT_(, f) n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, f)) {              \
        return MOCKC_CAT_(MockC_, n)::instance().n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f)); \
    }

#endif // MOCKC_DLFCN

#define MOCKC_INSTANCE(n) MOCKC_CAT_(MockC_, n)::instance()

#define MOCKC_METHOD0(n, f) MOCKC_(0, n, f)
#define MOCKC_METHOD1(n, f) MOCKC_(1, n, f)
#define MOCKC_METHOD2(n, f) MOCKC_(2, n, f)
#define MOCKC_METHOD3(n, f) MOCKC_(3, n, f)
#define MOCKC_METHOD4(n, f) MOCKC_(4, n, f)
#define MOCKC_METHOD5(n, f) MOCKC_(5, n, f)
#define MOCKC_METHOD6(n, f) MOCKC_(6, n, f)
#define MOCKC_METHOD7(n, f) MOCKC_(7, n, f)
#define MOCKC_METHOD8(n, f) MOCKC_(8, n, f)
#define MOCKC_METHOD9(n, f) MOCKC_(9, n, f)
#define MOCKC_METHOD10(n, f) MOCKC_(10, n, f)

#define MOCKC_EXPECT_CALL(n, p) EXPECT_CALL(MOCKC_INSTANCE(n), n p)

#if __cplusplus >= 201103L
#define MOCKC_DECLTYPE_METHOD0(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD0(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD1(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD1(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD2(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD2(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD3(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD3(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD4(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD4(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD5(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD5(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD6(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD6(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD7(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD7(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD8(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD8(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD9(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD9(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD10(n)                \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD10(n, MOCKC_CAT_(decltype_, n))
#else
#define MOCKC_DECLTYPE_METHOD0()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD1()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD2()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD3()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD4()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD5()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD6()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD7()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD8()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD9()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD10() /* not supported with version < cpp11 */
#endif                            // __cplusplus >= 201103L

#endif // _MOCKC_H_