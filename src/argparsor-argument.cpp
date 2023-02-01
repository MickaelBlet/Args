/**
 * argparsor-argument.cpp
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

#include <algorithm>
#include <sstream>

#include "mblet/argparsor/action.h"
#include "mblet/argparsor/argparsor.h"
#include "mblet/argparsor/argument.h"
#include "mblet/argparsor/utils.h"

#define _ARGPARSOR_PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define _ARGPARSOR_PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace mblet {

namespace argparsor {

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
    _argument(),
    _default(),
    _isNumber(false),
    _number(0.0) {}
ArgumentElement::ArgumentElement(const ArgumentElement& rhs) :
    std::vector<ArgumentElement>(rhs),
    _argument(rhs._argument),
    _default(rhs._default),
    _isNumber(rhs._isNumber),
    _number(rhs._number) {}
ArgumentElement::ArgumentElement(const char* arg_, const char* default_) :
    std::vector<ArgumentElement>(),
    _argument(arg_),
    _default(default_),
    _isNumber(false),
    _number(0.0) {}
ArgumentElement::ArgumentElement(const char* arg) :
    std::vector<ArgumentElement>(),
    _argument(arg),
    _default(),
    _isNumber(false),
    _number(0.0) {}
ArgumentElement::~ArgumentElement() {}

ArgumentElement::operator std::vector<std::string>() const {
    if (!empty() && front().empty()) {
        std::vector<std::string> ret;
        for (std::size_t i = 0; i < size(); ++i) {
            ret.push_back(at(i)._argument);
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

Argument::Argument(Argparsor& argparsor) :
    ArgumentElement(),
    _argparsor(argparsor),
    _nameOrFlags(),
    _type(SIMPLE_OPTION),
    _isExist(false),
    _isRequired(false),
    _count(0),
    _nargs(1),
    _help(),
    _metavar(),
    _valid(NULL),
    _validDeletable(true),
    _this(NULL),
    _action(Action::NONE),
    _defaults() {}

Argument::Argument(const Argument& rhs) :
    ArgumentElement(rhs),
    _argparsor(rhs._argparsor),
    _nameOrFlags(rhs._nameOrFlags),
    _type(rhs._type),
    _isExist(rhs._isExist),
    _isRequired(rhs._isRequired),
    _count(rhs._count),
    _nargs(rhs._nargs),
    _help(rhs._help),
    _metavar(rhs._metavar),
    _valid(rhs._valid),
    _validDeletable(rhs._validDeletable),
    _this(rhs._this),
    _action(rhs._action),
    _defaults() {}

Argument::~Argument() {
    if (_valid != NULL && _validDeletable) {
        delete _valid;
    }
}

std::string Argument::getString() const {
    if (_type == BOOLEAN_OPTION) {
        return ((_isExist) ? "true" : "false");
    }
    else if (_type == REVERSE_BOOLEAN_OPTION) {
        return ((_isExist) ? "false" : "true");
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
                        oss << at(i).at(j)._argument;
                    }
                    oss << ")";
                }
                else {
                    oss << at(i)._argument;
                }
            }
        }
        else {
            oss << _argument;
        }
        return oss.str();
    }
}

Argument::operator std::vector<std::string>() const {
    std::vector<std::string> ret;
    switch (_type) {
        case POSITIONAL_ARGUMENT:
        case SIMPLE_OPTION:
            ret.push_back(_argument);
            break;
        case NUMBER_POSITIONAL_ARGUMENT:
        case INFINITE_POSITIONAL_ARGUMENT:
        case NUMBER_OPTION:
        case MULTI_OPTION:
        case INFINITE_OPTION:
        case MULTI_INFINITE_OPTION:
            for (std::size_t i = 0; i < size(); ++i) {
                ret.push_back(at(i)._argument);
            }
            break;
        case MULTI_NUMBER_OPTION:
        case MULTI_NUMBER_INFINITE_OPTION:
        case INFINITE_NUMBER_POSITIONAL_ARGUMENT:
            for (std::size_t i = 0; i < size(); ++i) {
                for (std::size_t j = 0; j < at(i).size(); ++j) {
                    ret.push_back(at(i).at(j)._argument);
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
    switch (_type) {
        case MULTI_NUMBER_OPTION:
        case MULTI_NUMBER_INFINITE_OPTION:
        case INFINITE_NUMBER_POSITIONAL_ARGUMENT:
            for (std::size_t i = 0; i < size(); ++i) {
                ret.push_back(std::vector<std::string>());
                for (std::size_t j = 0; j < at(i).size(); ++j) {
                    ret[i].push_back(at(i).at(j)._argument);
                }
            }
            break;
        default:
            throw Exception("convertion to vector of vector of string not authorized");
            break;
    }
    return ret;
}

Argument& Argument::flag(const char* flag_) {
    if (_isPositionnalArgument()) {
        throw ArgumentException(flag_, "can't add flag in positionnal argument");
    }
    _validFormatFlag(flag_);
    if (_argparsor.argumentExists(flag_)) {
        throw ArgumentException(flag_, "invalid flag already exist");
    }
    _nameOrFlags.push_back(flag_);
    _sortNameOrFlags();
    _argparsor._argumentFromName.insert(std::pair<std::string, Argument**>(flag_, _this));
    _argparsor._arguments.sort(&Argument::_compareOption);
    return *this;
}

Argument& Argument::action(enum Action::eAction action_) {
    // reset help option
    if (_action == Action::HELP) {
        _argparsor._helpOption = NULL;
    }
    // reset version option
    if (_action == Action::VERSION) {
        _argparsor._versionOption = NULL;
    }
    _action = action_;
    _typeConstructor();
    _defaultsConstructor();
    return *this;
}

Argument& Argument::required(bool required_) {
    _isRequired = required_;
    _argparsor._arguments.sort(&Argument::_compareOption);
    return *this;
}

void Argument::_sortNameOrFlags() {
    std::sort(_nameOrFlags.begin(), _nameOrFlags.end(), &compareFlag);
}

void Argument::_validFormatFlag(const char* flag) {
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

bool Argument::_compareOption(const Argument* first, const Argument* second) {
    if (first->_isPositionnalArgument() && first->_isRequired && second->_isPositionnalArgument() &&
        second->_isRequired) {
        return false;
    }
    else if (first->_isPositionnalArgument() && first->_isRequired && second->_isPositionnalArgument()) {
        return true;
    }
    else if (first->_isPositionnalArgument() && second->_isPositionnalArgument() && second->_isRequired) {
        return false;
    }
    else if (first->_isPositionnalArgument() && second->_isPositionnalArgument()) {
        return false;
    }
    else if (first->_isPositionnalArgument()) {
        return false;
    }
    else if (second->_isPositionnalArgument()) {
        return true;
    }
    if (isShortOption(first->_nameOrFlags.front().c_str()) && isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return first->_nameOrFlags.front() < second->_nameOrFlags.front();
        }
    }
    else if (isShortOption(first->_nameOrFlags.front().c_str()) &&
             !isShortOption(second->_nameOrFlags.front().c_str())) {
        /*
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else
        */
        if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (!isShortOption(first->_nameOrFlags.front().c_str()) &&
             isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        return first->_nameOrFlags.front() < second->_nameOrFlags.front();
    }
}

void Argument::_toNumber() {
    if (_type == BOOLEAN_OPTION || _type == REVERSE_BOOLEAN_OPTION) {
        return;
    }
    else {
        if (!empty()) {
            for (std::size_t i = 0; i < size(); ++i) {
                if (!at(i).empty()) {
                    for (std::size_t j = 0; j < at(i).size(); ++j) {
                        std::stringstream ss(at(i).at(j)._argument);
                        at(i).at(j)._isNumber = static_cast<bool>(ss >> at(i).at(j)._number);
                    }
                }
                else {
                    std::stringstream ss(at(i)._argument);
                    at(i)._isNumber = static_cast<bool>(ss >> at(i)._number);
                }
            }
        }
        else {
            std::stringstream ss(_argument);
            _isNumber = static_cast<bool>(ss >> _number);
        }
    }
}

std::string Argument::_metavarDefault() {
    const char* flag = NULL;
    // get short or long name
    for (std::size_t i = 0; i < _nameOrFlags.size(); ++i) {
        if (_nameOrFlags[i][0] == '-' && _nameOrFlags[i][1] == '-') {
            flag = _nameOrFlags[i].c_str() + _ARGPARSOR_PREFIX_SIZEOF_LONG_OPTION;
            break;
        }
        else if (flag == NULL && _nameOrFlags[i][0] == '-' && _nameOrFlags[i][1] != '-') {
            flag = _nameOrFlags[i].c_str() + _ARGPARSOR_PREFIX_SIZEOF_SHORT_OPTION;
        }
    }
    // create a defaultUsageName from longName or shortName
    std::string defaultUsageName = flag;
    for (std::size_t i = 0; i < defaultUsageName.size(); ++i) {
        defaultUsageName[i] = ::toupper(defaultUsageName[i]);
    }

    if (_action == Action::INFINITE || _nargs == '+') {
        return defaultUsageName + "...";
    }
    else if (_nargs > 1) {
        std::string numberDefaultUsageName;
        for (std::size_t i = 0; i < _nargs; ++i) {
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

void Argument::_typeConstructor() {
    if (_isPositionnalArgument()) {
        if (_nargs == 1 && _action == Action::NONE) {
            _type = Argument::POSITIONAL_ARGUMENT;
        }
        else if ((_nargs == '+' && _action == Action::NONE) || (_nargs == 1 && _action == Action::INFINITE)) {
            _nargs = 1;
            _action = Action::INFINITE;
            _type = Argument::INFINITE_POSITIONAL_ARGUMENT;
        }
        else if (_nargs > 1 && _action == Action::NONE) {
            _type = Argument::NUMBER_POSITIONAL_ARGUMENT;
        }
        else if (_nargs > 1 && _action == Action::INFINITE) {
            _type = Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT;
        }
        else {
            throw ArgumentException(_nameOrFlags.front().c_str(),
                                    "positional argument cannot use with this action or this nargs");
        }
    }
    else if (_nargs == 0 || _action == Action::STORE_TRUE) {
        _nargs = 0;
        _type = Argument::BOOLEAN_OPTION;
    }
    else if (_action == Action::STORE_FALSE) {
        _nargs = 0;
        _type = Argument::REVERSE_BOOLEAN_OPTION;
    }
    else if (_action == Action::HELP) {
        if (_argparsor._helpOption == NULL) {
            _argparsor._helpOption = this;
        }
        if (_argparsor._helpOption != NULL && _argparsor._helpOption != this) {
            throw ArgumentException(_nameOrFlags.front().c_str(), "help action already defined");
        }
        _nargs = 0;
        _type = Argument::HELP_OPTION;
    }
    else if (_action == Action::VERSION) {
        if (_argparsor._versionOption == NULL) {
            _argparsor._versionOption = this;
        }
        if (_argparsor._versionOption != NULL && _argparsor._versionOption != this) {
            throw ArgumentException(_nameOrFlags.front().c_str(), "version action already defined");
        }
        _nargs = 0;
        _type = Argument::VERSION_OPTION;
    }
    // is simple
    else if (_nargs == 1 && _action == Action::NONE) {
        _type = Argument::SIMPLE_OPTION;
    }
    // is infinite
    else if ((_nargs == '+' && _action == Action::NONE) || _action == Action::INFINITE) {
        _nargs = 1;
        _action = Action::INFINITE;
        _type = Argument::INFINITE_OPTION;
    }
    // is number
    else if (_nargs > 1 && _action == Action::NONE) {
        _type = Argument::NUMBER_OPTION;
    }
    // is multi
    else if (_nargs == 1 && _action == Action::APPEND) {
        _type = Argument::MULTI_OPTION;
    }
    // is multi number
    else if (_nargs > 1 && _action == Action::APPEND) {
        _type = Argument::MULTI_NUMBER_OPTION;
    }
    // is multi infinite
    else if (_nargs == 1 && _action == Action::EXTEND) {
        _type = Argument::MULTI_INFINITE_OPTION;
    }
    // is multi number infinite
    else if (_nargs > 1 && _action == Action::EXTEND) {
        _type = Argument::MULTI_NUMBER_INFINITE_OPTION;
    }
}

void Argument::_defaultsConstructor() {
    // default arguments
    if (_nargs > 0 && _defaults.size() > 0) {
        clear();
        if (_type == Argument::POSITIONAL_ARGUMENT || _type == Argument::SIMPLE_OPTION) {
            if (_defaults.size() != _nargs) {
                throw ArgumentException(_nameOrFlags.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            _argument = _defaults.front();
            _default = _defaults.front();
        }
        if (_type == Argument::NUMBER_POSITIONAL_ARGUMENT || _type == Argument::NUMBER_OPTION) {
            if (_defaults.size() != _nargs) {
                throw ArgumentException(_nameOrFlags.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            _default = "";
            for (std::size_t i = 0; i < _defaults.size(); ++i) {
                if (i > 0) {
                    _default += ", ";
                }
                _default += _defaults[i];
                push_back(ArgumentElement(_defaults[i].c_str(), _defaults[i].c_str()));
            }
        }
        if (_type == Argument::INFINITE_POSITIONAL_ARGUMENT || _type == Argument::MULTI_OPTION ||
            _type == Argument::INFINITE_OPTION || _type == Argument::MULTI_INFINITE_OPTION) {
            _default = "";
            for (std::size_t i = 0; i < _defaults.size(); ++i) {
                if (i > 0) {
                    _default += ", ";
                }
                _default += _defaults[i];
                push_back(ArgumentElement(_defaults[i].c_str(), _defaults[i].c_str()));
            }
        }
        if (_type == Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT || _type == Argument::MULTI_NUMBER_OPTION ||
            _type == Argument::MULTI_NUMBER_INFINITE_OPTION) {
            if (_defaults.size() % _nargs != 0) {
                throw ArgumentException(_nameOrFlags.front().c_str(),
                                        "invalid number of argument with number of default argument");
            }
            for (std::size_t i = 0; i < _defaults.size() / _nargs; ++i) {
                if (i > 0) {
                    _default += ", ";
                }
                _default += "(";
                ArgumentElement newNumberArgument;
                for (std::size_t j = 0; j < _nargs; ++j) {
                    if (j > 0) {
                        _default += ", ";
                        newNumberArgument._default += ", ";
                    }
                    _default += _defaults[i * _nargs + j];
                    newNumberArgument._default += _defaults[i * _nargs + j];
                    newNumberArgument.push_back(
                        ArgumentElement(_defaults[i * _nargs + j].c_str(), _defaults[i * _nargs + j].c_str()));
                }
                _default += ")";
                push_back(newNumberArgument);
            }
        }
    }
}

} // namespace argparsor

} // namespace mblet

#undef _ARGPARSOR_PREFIX_SIZEOF_SHORT_OPTION
#undef _ARGPARSOR_PREFIX_SIZEOF_LONG_OPTION