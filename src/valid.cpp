/**
 * args-valid.cpp
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

#include "blet/args/valid.h"

#include <sys/stat.h>

#include <cstdlib>
#include <sstream>

#include "blet/args/exception.h"

namespace blet {

namespace args {

/*
################################################################################
 ValidNumber
################################################################################
*/

ValidNumber::ValidNumber() {}
ValidNumber::~ValidNumber() {}

bool ValidNumber::isValid(std::vector<std::string>& args) {
    for (std::size_t i = 0; i < args.size(); ++i) {
        char* endPtr = NULL;
        ::strtod(args[i].c_str(), &endPtr);
        if (endPtr != NULL && endPtr[0] != '\0') {
            std::ostringstream oss("");
            oss << "\"" << args[i] << "\" is not a number";
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidMinMax
################################################################################
*/

ValidMinMax::ValidMinMax(double min, double max) :
    _min(min),
    _max(max) {
    // bad initialized reverse value
    if (min > max) {
        _min = max;
        _max = min;
    }
}

ValidMinMax::~ValidMinMax() {}

bool ValidMinMax::isValid(std::vector<std::string>& args) {
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::stringstream ssArg("");
        ssArg << args[i];
        double number;
        if (!(ssArg >> number)) {
            std::ostringstream oss("");
            oss << "\"" << args[i] << "\" is not a number";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (number < _min || number > _max) {
            std::ostringstream oss("");
            oss << args[i] << " is not between " << _min << " and " << _max;
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidChoise
################################################################################
*/

ValidChoise::ValidChoise(const std::vector<std::string>& choises) :
    _choises(choises) {}

ValidChoise::~ValidChoise() {}

bool ValidChoise::isValid(std::vector<std::string>& args) {
    std::ostringstream ossChoise("");
    for (std::size_t i = 0; i < _choises.size(); ++i) {
        if (i > 0) {
            ossChoise << ", ";
        }
        ossChoise << '\"' << _choises[i] << '\"';
    }
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::size_t j;
        for (j = 0; j < _choises.size(); ++j) {
            if (args[i] == _choises[j]) {
                break;
            }
        }
        if (j == _choises.size()) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a choise value (" << ossChoise.str() << ')';
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidPath
################################################################################
*/

ValidPath::ValidPath(enum eMode mode) :
    _mode(mode) {}

ValidPath::~ValidPath() {}

bool ValidPath::isValid(std::vector<std::string>& args) {
    struct stat statBuff;
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (::stat(args[i].c_str(), &statBuff) == -1) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid path";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (_mode == ValidPath::IS_DIR && !S_ISDIR(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid directory";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        else if (_mode == ValidPath::IS_FILE && !S_ISREG(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid file";
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

} // namespace args

} // namespace blet