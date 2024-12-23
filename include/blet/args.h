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

    static args::Vector vector() {
        return args::Vector();
    }

    static args::Vector vector(const char* s1) {
        args::Vector ret(1);
        ret[0] = s1;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2) {
        args::Vector ret(2);
        ret[0] = s1;
        ret[1] = s2;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3) {
        args::Vector ret(3);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4) {
        args::Vector ret(4);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5) {
        args::Vector ret(5);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6) {
        args::Vector ret(6);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7) {
        args::Vector ret(7);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8) {
        args::Vector ret(8);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9) {
        args::Vector ret(9);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10) {
        args::Vector ret(10);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11) {
        args::Vector ret(11);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12) {
        args::Vector ret(12);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13) {
        args::Vector ret(13);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14) {
        args::Vector ret(14);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14, const char* s15) {
        args::Vector ret(15);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        ret[14] = s15;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14, const char* s15,
                               const char* s16) {
        args::Vector ret(16);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        ret[14] = s15;
        ret[15] = s16;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14, const char* s15,
                               const char* s16, const char* s17) {
        args::Vector ret(17);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        ret[14] = s15;
        ret[15] = s16;
        ret[16] = s17;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14, const char* s15,
                               const char* s16, const char* s17, const char* s18) {
        args::Vector ret(18);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        ret[14] = s15;
        ret[15] = s16;
        ret[16] = s17;
        ret[17] = s18;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14, const char* s15,
                               const char* s16, const char* s17, const char* s18, const char* s19) {
        args::Vector ret(19);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        ret[14] = s15;
        ret[15] = s16;
        ret[16] = s17;
        ret[17] = s18;
        ret[18] = s19;
        return ret;
    }

    static args::Vector vector(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5,
                               const char* s6, const char* s7, const char* s8, const char* s9, const char* s10,
                               const char* s11, const char* s12, const char* s13, const char* s14, const char* s15,
                               const char* s16, const char* s17, const char* s18, const char* s19, const char* s20) {
        args::Vector ret(20);
        ret[0] = s1;
        ret[1] = s2;
        ret[2] = s3;
        ret[3] = s4;
        ret[4] = s5;
        ret[5] = s6;
        ret[6] = s7;
        ret[7] = s8;
        ret[8] = s9;
        ret[9] = s10;
        ret[10] = s11;
        ret[11] = s12;
        ret[12] = s13;
        ret[13] = s14;
        ret[14] = s15;
        ret[15] = s16;
        ret[16] = s17;
        ret[17] = s18;
        ret[18] = s19;
        ret[19] = s20;
        return ret;
    }

  private:
    typedef args::Vector Vector;
};

} // namespace blet

#endif // #ifndef BLET_ARGS_H_
