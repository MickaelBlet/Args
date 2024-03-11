/**
 * MockC
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2021-2024 BLET Mickaël.
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

#ifndef BLET_MOCKC_H_
#define BLET_MOCKC_H_

#include <dlfcn.h>
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

#define MOCKC_INSTANCE(n)                                                                            \
    ((MOCKC_CAT_(MockC_, n)::instance())                                                             \
         ? *(MOCKC_CAT_(MockC_, n)::instance())                                                      \
         : (throw MockC_InstanceNotFound(__FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n)), \
            *(MOCKC_CAT_(MockC_, n)::instance())))

#define MOCKC_NEW_INSTANCE(n) MOCKC_CAT_(MockC_, n) MOCKC_CAT_(local_instance_, n)

#define MOCKC_METHOD0(r, n, f) MOCKC_(0, r, n, f)
#define MOCKC_METHOD1(r, n, f) MOCKC_(1, r, n, f)
#define MOCKC_METHOD2(r, n, f) MOCKC_(2, r, n, f)
#define MOCKC_METHOD3(r, n, f) MOCKC_(3, r, n, f)
#define MOCKC_METHOD4(r, n, f) MOCKC_(4, r, n, f)
#define MOCKC_METHOD5(r, n, f) MOCKC_(5, r, n, f)
#define MOCKC_METHOD6(r, n, f) MOCKC_(6, r, n, f)
#define MOCKC_METHOD7(r, n, f) MOCKC_(7, r, n, f)
#define MOCKC_METHOD8(r, n, f) MOCKC_(8, r, n, f)
#define MOCKC_METHOD9(r, n, f) MOCKC_(9, r, n, f)
#define MOCKC_METHOD10(r, n, f) MOCKC_(10, r, n, f)
#define MOCKC_ATTRIBUTE_METHOD0(r, n, f, a) MOCKC_ATTRIBUTE_(0, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD1(r, n, f, a) MOCKC_ATTRIBUTE_(1, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD2(r, n, f, a) MOCKC_ATTRIBUTE_(2, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD3(r, n, f, a) MOCKC_ATTRIBUTE_(3, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD4(r, n, f, a) MOCKC_ATTRIBUTE_(4, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD5(r, n, f, a) MOCKC_ATTRIBUTE_(5, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD6(r, n, f, a) MOCKC_ATTRIBUTE_(6, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD7(r, n, f, a) MOCKC_ATTRIBUTE_(7, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD8(r, n, f, a) MOCKC_ATTRIBUTE_(8, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD9(r, n, f, a) MOCKC_ATTRIBUTE_(9, r, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD10(r, n, f, a) MOCKC_ATTRIBUTE_(10, r, n, f, a)

#define MOCKC_EXPECT_CALL(n, p) EXPECT_CALL(MOCKC_INSTANCE(n), n p)

struct MockC_InstanceNotFound : public std::exception {
    MockC_InstanceNotFound(const char* file, const char* line, const char* name) throw() {
        message_ = file;
        message_ += ":";
        message_ += line;
        message_ += " MockC '";
        message_ += name;
        message_ += "' instance not found.";
    }
    virtual ~MockC_InstanceNotFound() throw() {}
    const char* what() const throw() {
        return message_.c_str();
    }
    std::string message_;
};
struct MockC_RealFunctionNotFound : public std::exception {
    MockC_RealFunctionNotFound(const char* file, const char* line, const char* name) throw() {
        message_ = file;
        message_ += ":";
        message_ += line;
        message_ += " MockC '";
        message_ += name;
        message_ += "' real function not found.";
    }
    virtual ~MockC_RealFunctionNotFound() throw() {}
    const char* what() const throw() {
        return message_.c_str();
    }
    std::string message_;
};

template<typename T>
struct MockC_Guard {
    MockC_Guard(T& instance) :
        instance_(instance) {
        instance_.isActive = true;
    }
    ~MockC_Guard() {
        instance_.isActive = false;
    }
    T& instance_;
};
template<typename T>
struct MockC_GuardReverse {
    MockC_GuardReverse(T& instance) :
        instance_(instance) {
        instance_.isActive = false;
    }
    ~MockC_GuardReverse() {
        instance_.isActive = true;
    }
    T& instance_;
};

template<typename T>
struct MockC_Singleton {
    static T*& instance() {
        static T* singleton = NULL;
        return singleton;
    }
};

#define MOCKC_GUARD(n) MockC_Guard<MOCKC_CAT_(MockC_, n)> MOCKC_CAT_(mockCGuard_, n)(MOCKC_INSTANCE(n))
#define MOCKC_GUARD_REVERSE(n) \
    MockC_GuardReverse<MOCKC_CAT_(MockC_, n)> MOCKC_CAT_(mockCGuardReverse_, n)(MOCKC_INSTANCE(n))
#define MOCKC_ENABLE(n) MOCKC_INSTANCE(n).isActive = true;
#define MOCKC_DISABLE(n) MOCKC_INSTANCE(n).isActive = false;

#define MOCKC_(i, r, n, f)       \
    MOCKC_CLASS_(i, r, n, f);    \
    MOCKC_REAL_FUNC_(i, r, n, f) \
    MOCKC_FAKE_FUNC_(i, r, n, f)

#define MOCKC_ATTRIBUTE_(i, r, n, f, a) \
    MOCKC_CLASS_(i, r, n, f);           \
    MOCKC_REAL_FUNC_(i, r, n, f)        \
    MOCKC_FAKE_FUNC_ATTRIBUTE_(i, r, n, f, a)

#define MOCKC_REAL_FUNC_(i, r, n, f)                                                        \
    typedef r(*MOCKC_CAT2_(mockc_func_, n, _t)) f;                                          \
    static MOCKC_CAT2_(mockc_func_, n, _t) MOCKC_CAT2_(mockc_real_func_, n, _singleton)() { \
        static MOCKC_CAT2_(mockc_func_, n, _t) MOCKC_CAT_(mockc_real_func_, n) =            \
            (MOCKC_CAT2_(mockc_func_, n, _t))dlsym(RTLD_NEXT, #n);                          \
        return MOCKC_CAT_(mockc_real_func_, n);                                             \
    }

// version gtest <= 1.8.0
#ifndef MOCK_METHOD
#define MOCKC_CLASS_(i, r, n, f)                        \
    struct MOCKC_CAT_(MockC_, n) :                      \
        public MockC_Singleton<MOCKC_CAT_(MockC_, n)> { \
        MOCKC_CAT_(MockC_, n)                           \
        () :                                            \
            isActive(false) {                           \
            instance() = this;                          \
        }                                               \
        ~MOCKC_CAT_(MockC_, n)() {                      \
            instance() = NULL;                          \
        }                                               \
        MOCKC_CAT_(MOCK_METHOD, i)(n, r f);             \
        bool isActive;                                  \
    }

#define MOCKC_FAKE_FUNC_(i, r, n, f)                                                                            \
    r n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, r f)) {                                        \
        if (MOCKC_CAT_(MockC_, n)::instance() && MOCKC_INSTANCE(n).isActive) {                                  \
            MOCKC_GUARD_REVERSE(n);                                                                             \
            return MOCKC_INSTANCE(n).n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));                        \
        }                                                                                                       \
        if (MOCKC_CAT2_(mockc_real_func_, n, _singleton)() == NULL) {                                           \
            throw MockC_RealFunctionNotFound(__FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n));        \
        }                                                                                                       \
        return MOCKC_CAT2_(mockc_real_func_, n, _singleton)()(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f)); \
    }                                                                                                           \
    struct MOCKC_CAT_(MockC_, n)

#define MOCKC_FAKE_FUNC_ATTRIBUTE_(i, r, n, f, a)                                                               \
    r n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, r f)) a {                                      \
        if (MOCKC_CAT_(MockC_, n)::instance() && MOCKC_INSTANCE(n).isActive) {                                  \
            MOCKC_GUARD_REVERSE(n);                                                                             \
            return MOCKC_INSTANCE(n).n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));                        \
        }                                                                                                       \
        if (MOCKC_CAT2_(mockc_real_func_, n, _singleton)() == NULL) {                                           \
            throw MockC_RealFunctionNotFound(__FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n));        \
        }                                                                                                       \
        return MOCKC_CAT2_(mockc_real_func_, n, _singleton)()(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f)); \
    }                                                                                                           \
    struct MOCKC_CAT_(MockC_, n)
#else
#define MOCKC_CLASS_(i, r, n, f)                        \
    struct MOCKC_CAT_(MockC_, n) :                      \
        public MockC_Singleton<MOCKC_CAT_(MockC_, n)> { \
        MOCKC_CAT_(MockC_, n)                           \
        () :                                            \
            isActive(false) {                           \
            instance() = this;                          \
        }                                               \
        ~MOCKC_CAT_(MockC_, n)() {                      \
            instance() = NULL;                          \
        }                                               \
        MOCK_METHOD(r, n, f, ());                       \
        bool isActive;                                  \
    }

#define MOCKC_FAKE_FUNC_(i, r, n, f)                                                                     \
    r n(GMOCK_PP_REPEAT(GMOCK_INTERNAL_PARAMETER, (GMOCK_INTERNAL_SIGNATURE(r, f)), i)) {                \
        if (MOCKC_CAT_(MockC_, n)::instance() && MOCKC_INSTANCE(n).isActive) {                           \
            MOCKC_GUARD_REVERSE(n);                                                                      \
            return MOCKC_INSTANCE(n).n(                                                                  \
                GMOCK_PP_REPEAT(GMOCK_INTERNAL_FORWARD_ARG, (GMOCK_INTERNAL_SIGNATURE(r, f)), i));       \
        }                                                                                                \
        if (MOCKC_CAT2_(mockc_real_func_, n, _singleton)() == NULL) {                                    \
            throw MockC_RealFunctionNotFound(__FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n)); \
        }                                                                                                \
        return MOCKC_CAT2_(mockc_real_func_, n, _singleton)()(                                           \
            GMOCK_PP_REPEAT(GMOCK_INTERNAL_FORWARD_ARG, (GMOCK_INTERNAL_SIGNATURE(r, f)), i));           \
    }                                                                                                    \
    struct MOCKC_CAT_(MockC_, n)

#define MOCKC_FAKE_FUNC_ATTRIBUTE_(i, r, n, f, a)                                                        \
    r n(GMOCK_PP_REPEAT(GMOCK_INTERNAL_PARAMETER, (GMOCK_INTERNAL_SIGNATURE(r, f)), i)) a {              \
        if (MOCKC_CAT_(MockC_, n)::instance() && MOCKC_INSTANCE(n).isActive) {                           \
            MOCKC_GUARD_REVERSE(n);                                                                      \
            return MOCKC_INSTANCE(n).n(                                                                  \
                GMOCK_PP_REPEAT(GMOCK_INTERNAL_FORWARD_ARG, (GMOCK_INTERNAL_SIGNATURE(r, f)), i));       \
        }                                                                                                \
        if (MOCKC_CAT2_(mockc_real_func_, n, _singleton)() == NULL) {                                    \
            throw MockC_RealFunctionNotFound(__FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n)); \
        }                                                                                                \
        return MOCKC_CAT2_(mockc_real_func_, n, _singleton)()(                                           \
            GMOCK_PP_REPEAT(GMOCK_INTERNAL_FORWARD_ARG, (GMOCK_INTERNAL_SIGNATURE(r, f)), i));           \
    }                                                                                                    \
    struct MOCKC_CAT_(MockC_, n)
#endif

#endif // #ifndef BLET_MOCKC_H_
