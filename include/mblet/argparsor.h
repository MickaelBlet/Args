/**
 * argparsor.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022 BLET Mickaël.
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
    Argparsor(bool help = true) :
        argparsor::Argparsor(help) {}
    ~Argparsor() {}

    typedef argparsor::Exception Exception;
    typedef argparsor::ArgumentException ArgumentException;
    typedef argparsor::ParseArgumentException ParseArgumentException;
    typedef argparsor::ParseArgumentRequiredException ParseArgumentRequiredException;
    typedef argparsor::ParseArgumentValidException ParseArgumentValidException;
    typedef argparsor::AccessDeniedException AccessDeniedException;

    typedef argparsor::IValid IValid;
    typedef argparsor::ValidChoise ValidChoise;
    typedef argparsor::ValidMinMax ValidMinMax;
    typedef argparsor::ValidPath ValidPath;

  private:
    typedef argparsor::Vector Vector;
};

} // namespace mblet

#endif // _MBLET_ARGPARSOR_H_