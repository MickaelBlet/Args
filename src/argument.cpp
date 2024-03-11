/**
 * args-argument.cpp
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

#include "blet/args/argument.h"

#include <algorithm>
#include <sstream>

#include "blet/args/action.h"
#include "blet/args/args.h"
#include "blet/args/utils.h"

#define ARGS_PREFIX_SIZEOF_SHORT_OPTION_ (sizeof("-") - 1)
#define ARGS_PREFIX_SIZEOF_LONG_OPTION_ (sizeof("--") - 1)

namespace blet {

namespace args {

static inline bool compareFlag(const std::string& first, const std::string& second) {
    if (isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return first < second;
    }
    else if (isShortOption(first.c_str()) && !isShortOption(second.c_str())) {
        return true;
    }
    else if (!isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return false;
    }
    else {
        return first < second;
    }
}

/*
################################################################################
 ArgumentElement
################################################################################
*/

ArgumentElement::ArgumentElement() :
    std::vector<ArgumentElement>(),
    argument_(),
    default_(),
    isNumber_(false),
    number_(0.0) {}
ArgumentElement::ArgumentElement(const ArgumentElement& rhs) :
    std::vector<ArgumentElement>(rhs),
    argument_(rhs.argument_),
    default_(rhs.default_),
    isNumber_(rhs.isNumber_),
    number_(rhs.number_) {}
ArgumentElement::ArgumentElement(const char* arg__, const char* default__) :
    std::vector<ArgumentElement>(),
    argument_(arg__),
    default_(default__),
    isNumber_(false),
    number_(0.0) {}
ArgumentElement::ArgumentElement(const char* arg) :
    std::vector<ArgumentElement>(),
    argument_(arg),
    default_(),
    isNumber_(false),
    number_(0.0) {}
ArgumentElement::~ArgumentElement() {}

ArgumentElement::operator std::vector<std::string>() const {
    if (!empty() && front().empty()) {
        std::vector<std::string> ret;
        for (std::size_t i = 0; i < size(); ++i) {
            ret.push_back(at(i).argument_);
        }
        return ret;
    }
    throw Exception("convertion to vector of string not authorized");
}

/*
################################################################################
 Argument
################################################################################
*/

Argument::Argument(Args& args) :
    ArgumentElement(),
    args_(args),
    nameOrFlags_(),
    type_(SIMPLE_OPTION),
    isExist_(false),
    isRequired_(false),
    count_(0),
    nargs_(1),
    help_(),
    metavar_(),
    valid_(NULL),
    validDeletable_(true),
    this_(NULL),
    action_(Action::NONE),
    defaults_() {}

Argument::Argument(const Argument& rhs) :
    ArgumentElement(rhs),
    args_(rhs.args_),
    nameOrFlags_(rhs.nameOrFlags_),
    type_(rhs.type_),
    isExist_(rhs.isExist_),
    isRequired_(rhs.isRequired_),
    count_(rhs.count_),
    nargs_(rhs.nargs_),
    help_(rhs.help_),
    metavar_(rhs.metavar_),
    valid_(rhs.valid_),
    validDeletable_(rhs.validDeletable_),
    this_(rhs.this_),
    action_(rhs.action_),
    defaults_() {}

Argument::~Argument() {
    if (valid_ != NULL && validDeletable_) {
        delete valid_;
    }
}

std::string Argument::getString() const {
    std::string ret("");
    if (type_ == BOOLEAN_OPTION) {
        ret = (isExist_) ? "true" : "false";
    }
    else if (type_ == REVERSE_BOOLEAN_OPTION) {
        ret = (isExist_) ? "false" : "true";
    }
    else {
        std::ostringstream oss("");
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                if (i > 0) {
                    oss << ", ";
                }
                if (!at(i).empty()) {
                    oss << "(";
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
                        if (j > 0) {
                            oss << ", ";
                        }
                        oss << at(i).at(j).argument_;
                    }
                    oss << ")";
                }
                else {
                    oss << at(i).argument_;
                }
            }
        }
        else {
            oss << argument_;
        }
        ret = oss.str();
    }
    return ret;
}

Argument::operator std::vector<std::string>() const {
    std::vector<std::string> ret;
    switch (type_) {
        case POSITIONAL_ARGUMENT:
        case SIMPLE_OPTION:
            ret.push_back(argument_);
            break;
        case NUMBER_POSITIONAL_ARGUMENT:
        case INFINITE_POSITIONAL_ARGUMENT:
        case NUMBER_OPTION:
        case MULTI_OPTION:
        case INFINITE_OPTION:
        case MULTI_INFINITE_OPTION:
            for (std::size_t i = 0; i < size(); ++i) {
                ret.push_back(at(i).argument_);
            }
            break;
        case MULTI_NUMBER_OPTION:
        case MULTI_NUMBER_INFINITE_OPTION:
        case INFINITE_NUMBER_POSITIONAL_ARGUMENT:
            for (std::size_t i = 0; i < size(); ++i) {
                for (std::size_t j = 0; j < at(i).size(); ++j) {
                    ret.push_back(at(i).at(j).argument_);
                }
            }
            break;
        default:
            throw Exception("convertion to vector of string not authorized");
            break;
    }
    return ret;
}

Argument::operator std::vector<std::vector<std::string> >() const {
    std::vector<std::vector<std::string> > ret;
    switch (type_) {
        case MULTI_NUMBER_OPTION:
        case MULTI_NUMBER_INFINITE_OPTION:
        case INFINITE_NUMBER_POSITIONAL_ARGUMENT:
            for (std::size_t i = 0; i < size(); ++i) {
                ret.push_back(std::vector<std::string>());
                for (std::size_t j = 0; j < at(i).size(); ++j) {
                    ret[i].push_back(at(i).at(j).argument_);
                }
            }
            break;
        default:
            throw Exception("convertion to vector of vector of string not authorized");
            break;
    }
    return ret;
}

Argument& Argument::flag(const char* flag__) {
    if (isPositionnalArgument_()) {
        throw ArgumentException(flag__, "can't add flag in positionnal argument");
    }
    validFormatFlag_(flag__);
    if (args_.argumentExists(flag__)) {
        throw ArgumentException(flag__, "invalid flag already exist");
    }
    nameOrFlags_.push_back(flag__);
    sortNameOrFlags_();
    args_.argumentFromName_.insert(std::pair<std::string, Argument**>(flag__, this_));
    args_.arguments_.sort(&Argument::compareOption_);
    return *this;
}

Argument& Argument::action(enum Action::eAction action__) {
    // reset help option
    if (action_ == Action::HELP) {
        args_.helpOption_ = NULL;
    }
    // reset version option
    if (action_ == Action::VERSION) {
        args_.versionOption_ = NULL;
    }
    action_ = action__;
    typeConstructor_();
    defaultsConstructor_();
    return *this;
}

Argument& Argument::required(bool required__) {
    isRequired_ = required__;
    args_.arguments_.sort(&Argument::compareOption_);
    return *this;
}

void Argument::sortNameOrFlags_() {
    std::sort(nameOrFlags_.begin(), nameOrFlags_.end(), &compareFlag);
}

void Argument::validFormatFlag_(const char* flag) {
    if (flag[0] != '-') {
        throw ArgumentException(flag, "invalid flag not start by '-' character");
    }
    if (flag[0] == '-' && flag[1] == '\0') {
        throw ArgumentException(flag, "invalid flag not be only '-' character");
    }
    if (flag[0] == '-' && flag[1] == '-' && flag[2] == '\0') {
        throw ArgumentException(flag, "invalid flag not be only '--' characters");
    }
    if (flag[0] == '-' && flag[1] != '-' && flag[2] != '\0') {
        throw ArgumentException(flag, "invalid short flag has not only one character");
    }
}

bool Argument::compareOption_(const Argument* first, const Argument* second) {
    if (first->isPositionnalArgument_() && first->isRequired_ && second->isPositionnalArgument_() &&
        second->isRequired_) {
        return false;
    }
    else if (first->isPositionnalArgument_() && first->isRequired_ && second->isPositionnalArgument_()) {
        return true;
    }
    else if (first->isPositionnalArgument_() && second->isPositionnalArgument_() && second->isRequired_) {
        return false;
    }
    else if (first->isPositionnalArgument_() && second->isPositionnalArgument_()) {
        return false;
    }
    else if (first->isPositionnalArgument_()) {
        return false;
    }
    else if (second->isPositionnalArgument_()) {
        return true;
    }
    if (isShortOption(first->nameOrFlags_.front().c_str()) && isShortOption(second->nameOrFlags_.front().c_str())) {
        if (first->isRequired_ && !second->isRequired_) {
            return true;
        }
        else if (!first->isRequired_ && second->isRequired_) {
            return false;
        }
        else {
            return first->nameOrFlags_.front() < second->nameOrFlags_.front();
        }
    }
    else if (isShortOption(first->nameOrFlags_.front().c_str()) &&
             !isShortOption(second->nameOrFlags_.front().c_str())) {
        /*
        if (first->isRequired_ && !second->isRequired_) {
            return true;
        }
        else
        */
        if (!first->isRequired_ && second->isRequired_) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (!isShortOption(first->nameOrFlags_.front().c_str()) &&
             isShortOption(second->nameOrFlags_.front().c_str())) {
        if (first->isRequired_ && !second->isRequired_) {
            return true;
        }
        else if (!first->isRequired_ && second->isRequired_) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        if (first->isRequired_ && !second->isRequired_) {
            return true;
        }
        else if (!first->isRequired_ && second->isRequired_) {
            return false;
        }
        return first->nameOrFlags_.front() < second->nameOrFlags_.front();
    }
}

void Argument::toNumber_() {
    if (type_ == BOOLEAN_OPTION || type_ == REVERSE_BOOLEAN_OPTION) {
        return;
    }
    else {
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                if (!at(i).empty()) {
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
                        std::stringstream ss(at(i).at(j).argument_);
                        at(i).at(j).isNumber_ = static_cast<bool>(ss >> at(i).at(j).number_);
                    }
                }
                else {
                    std::stringstream ss(at(i).argument_);
                    at(i).isNumber_ = static_cast<bool>(ss >> at(i).number_);
                }
            }
        }
        else {
            std::stringstream ss(argument_);
            isNumber_ = static_cast<bool>(ss >> number_);
        }
    }
}

std::string Argument::metavarDefault_() {
    const char* flag = NULL;
    // get short or long name
    for (std::size_t i = 0; i < nameOrFlags_.size(); ++i) {
        if (nameOrFlags_[i][0] == '-' && nameOrFlags_[i][1] == '-') {
            flag = nameOrFlags_[i].c_str() + ARGS_PREFIX_SIZEOF_LONG_OPTION_;
            break;
        }
        else if (flag == NULL && nameOrFlags_[i][0] == '-' && nameOrFlags_[i][1] != '-') {
            flag = nameOrFlags_[i].c_str() + ARGS_PREFIX_SIZEOF_SHORT_OPTION_;
        }
    }
    // create a defaultUsageName from longName or shortName
    std::string defaultUsageName = flag;
    for (std::size_t i = 0; i < defaultUsageName.size(); ++i) {
        defaultUsageName[i] = ::toupper(defaultUsageName[i]);
    }

    if (action_ == Action::INFINITE || nargs_ == '+') {
        return defaultUsageName + "...";
    }
    else if (nargs_ > 1) {
        std::string numberDefaultUsageName;
        for (std::size_t i = 0; i < nargs_; ++i) {
            if (i > 0) {
                numberDefaultUsageName += " ";
            }
            numberDefaultUsageName += defaultUsageName;
        }
        return numberDefaultUsageName;
    }
    else {
        return defaultUsageName;
    }
}

void Argument::typeConstructor_() {
    if (isPositionnalArgument_()) {
        if (nargs_ == 1 && action_ == Action::NONE) {
            type_ = Argument::POSITIONAL_ARGUMENT;
        }
        else if ((nargs_ == '+' && action_ == Action::NONE) || (nargs_ == 1 && action_ == Action::INFINITE)) {
            nargs_ = 1;
            action_ = Action::INFINITE;
            type_ = Argument::INFINITE_POSITIONAL_ARGUMENT;
        }
        else if (nargs_ > 1 && action_ == Action::NONE) {
            type_ = Argument::NUMBER_POSITIONAL_ARGUMENT;
        }
        else if (nargs_ > 1 && action_ == Action::INFINITE) {
            type_ = Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT;
        }
        else {
            throw ArgumentException(nameOrFlags_.front().c_str(),
                                    "positional argument cannot use with this action or this nargs");
        }
    }
    else if (nargs_ == 0 || action_ == Action::STORE_TRUE) {
        nargs_ = 0;
        type_ = Argument::BOOLEAN_OPTION;
    }
    else if (action_ == Action::STORE_FALSE) {
        nargs_ = 0;
        type_ = Argument::REVERSE_BOOLEAN_OPTION;
    }
    else if (action_ == Action::HELP) {
        if (args_.helpOption_ == NULL) {
            args_.helpOption_ = this;
        }
        if (args_.helpOption_ != NULL && args_.helpOption_ != this) {
            throw ArgumentException(nameOrFlags_.front().c_str(), "help action already defined");
        }
        nargs_ = 0;
        type_ = Argument::HELP_OPTION;
    }
    else if (action_ == Action::VERSION) {
        if (args_.versionOption_ == NULL) {
            args_.versionOption_ = this;
        }
        if (args_.versionOption_ != NULL && args_.versionOption_ != this) {
            throw ArgumentException(nameOrFlags_.front().c_str(), "version action already defined");
        }
        nargs_ = 0;
        type_ = Argument::VERSION_OPTION;
    }
    // is simple
    else if (nargs_ == 1 && action_ == Action::NONE) {
        type_ = Argument::SIMPLE_OPTION;
    }
    // is infinite
    else if ((nargs_ == '+' && action_ == Action::NONE) || action_ == Action::INFINITE) {
        nargs_ = 1;
        action_ = Action::INFINITE;
        type_ = Argument::INFINITE_OPTION;
    }
    // is number
    else if (nargs_ > 1 && action_ == Action::NONE) {
        type_ = Argument::NUMBER_OPTION;
    }
    // is multi
    else if (nargs_ == 1 && action_ == Action::APPEND) {
        type_ = Argument::MULTI_OPTION;
    }
    // is multi number
    else if (nargs_ > 1 && action_ == Action::APPEND) {
        type_ = Argument::MULTI_NUMBER_OPTION;
    }
    // is multi infinite
    else if (nargs_ == 1 && action_ == Action::EXTEND) {
        type_ = Argument::MULTI_INFINITE_OPTION;
    }
    // is multi number infinite
    else if (nargs_ > 1 && action_ == Action::EXTEND) {
        type_ = Argument::MULTI_NUMBER_INFINITE_OPTION;
    }
}

void Argument::defaultsConstructor_() {
    // default arguments
    if (nargs_ > 0 && defaults_.size() > 0) {
        clear();
        if (type_ == Argument::POSITIONAL_ARGUMENT || type_ == Argument::SIMPLE_OPTION) {
            if (defaults_.size() != nargs_) {
                throw ArgumentException(nameOrFlags_.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            argument_ = defaults_.front();
            default_ = defaults_.front();
        }
        if (type_ == Argument::NUMBER_POSITIONAL_ARGUMENT || type_ == Argument::NUMBER_OPTION) {
            if (defaults_.size() != nargs_) {
                throw ArgumentException(nameOrFlags_.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            default_ = "";
            for (std::size_t i = 0; i < defaults_.size(); ++i) {
                if (i > 0) {
                    default_ += ", ";
                }
                default_ += defaults_[i];
                push_back(ArgumentElement(defaults_[i].c_str(), defaults_[i].c_str()));
            }
        }
        if (type_ == Argument::INFINITE_POSITIONAL_ARGUMENT || type_ == Argument::MULTI_OPTION ||
            type_ == Argument::INFINITE_OPTION || type_ == Argument::MULTI_INFINITE_OPTION) {
            default_ = "";
            for (std::size_t i = 0; i < defaults_.size(); ++i) {
                if (i > 0) {
                    default_ += ", ";
                }
                default_ += defaults_[i];
                push_back(ArgumentElement(defaults_[i].c_str(), defaults_[i].c_str()));
            }
        }
        if (type_ == Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT || type_ == Argument::MULTI_NUMBER_OPTION ||
            type_ == Argument::MULTI_NUMBER_INFINITE_OPTION) {
            if (defaults_.size() % nargs_ != 0) {
                throw ArgumentException(nameOrFlags_.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            for (std::size_t i = 0; i < defaults_.size() / nargs_; ++i) {
                if (i > 0) {
                    default_ += ", ";
                }
                default_ += "(";
                ArgumentElement newNumberArgument;
                for (std::size_t j = 0; j < nargs_; ++j) {
                    if (j > 0) {
                        default_ += ", ";
                        newNumberArgument.default_ += ", ";
                    }
                    default_ += defaults_[i * nargs_ + j];
                    newNumberArgument.default_ += defaults_[i * nargs_ + j];
                    newNumberArgument.push_back(
                        ArgumentElement(defaults_[i * nargs_ + j].c_str(), defaults_[i * nargs_ + j].c_str()));
                }
                default_ += ")";
                push_back(newNumberArgument);
            }
        }
    }
}

void Argument::clear_() {
    argument_ = default_;
    isNumber_ = false;
    number_ = 0.0;
    count_ = 0;
    isExist_ = false;
    for (std::size_t i = 0; i < size(); ++i) {
        at(i).argument_ = at(i).default_;
        at(i).isNumber_ = false;
        at(i).number_ = 0.0;
        for (std::size_t j = 0; j < at(i).size(); ++j) {
            at(i).at(j).argument_ = at(i).at(j).default_;
            at(i).at(j).isNumber_ = false;
            at(i).at(j).number_ = 0.0;
        }
    }
}

} // namespace args

} // namespace blet

#undef ARGS_PREFIX_SIZEOF_SHORT_OPTION_
#undef ARGS_PREFIX_SIZEOF_LONG_OPTION_
