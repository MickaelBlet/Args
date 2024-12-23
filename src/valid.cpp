/**
 * valid.cpp
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022-2024 BLET Mickael.
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
    min_(min),
    max_(max) {
    // bad initialized reverse value
    if (min > max) {
        min_ = max;
        max_ = min;
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
        if (number < min_ || number > max_) {
            std::ostringstream oss("");
            oss << args[i] << " is not between " << min_ << " and " << max_;
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
    choises_(choises) {}

ValidChoise::~ValidChoise() {}

bool ValidChoise::isValid(std::vector<std::string>& args) {
    std::ostringstream ossChoise("");
    for (std::size_t i = 0; i < choises_.size(); ++i) {
        if (i > 0) {
            ossChoise << ", ";
        }
        ossChoise << '\"' << choises_[i] << '\"';
    }
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::size_t j;
        for (j = 0; j < choises_.size(); ++j) {
            if (args[i] == choises_[j]) {
                break;
            }
        }
        if (j == choises_.size()) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid choise (" << ossChoise.str() << ')';
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
    mode_(mode) {}

ValidPath::~ValidPath() {}

bool ValidPath::isValid(std::vector<std::string>& args) {
    struct stat statBuff;
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (::stat(args[i].c_str(), &statBuff) == -1) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid path";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (mode_ == ValidPath::IS_DIR && !S_ISDIR(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid directory";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        else if (mode_ == ValidPath::IS_FILE && !S_ISREG(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid file";
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

} // namespace args

} // namespace blet
