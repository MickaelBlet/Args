/**
 * args.cpp
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

#include "blet/args/args.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "blet/args/argument.h"
#include "blet/args/utils.h"
#include "blet/args/vector.h"

#define _ARGS_PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define _ARGS_PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace blet {

namespace args {

Args::Args(bool addHelp) :
    Usage(*this),
    _binaryName(),
    _arguments(),
    _argumentFromName(),
    _helpOption(NULL),
    _versionOption(NULL),
    _isAlternative(false),
    _isStrict(false),
    _isHelpException(false),
    _isVersionException(false),
    _additionalArguments() {
    if (addHelp) {
        // define _helpOption
        addArgument("-h").flag("--help").action(Action::HELP).help("show this help message and exit");
    }
}

Args::~Args() {
    // delete all new element
    for (std::list<Argument*>::iterator it = _arguments.begin(); it != _arguments.end(); ++it) {
        delete (*it);
    }
}

void Args::parseArguments(int argc, char* argv[]) {
    // clear the arguments
    for (std::list<Argument*>::iterator it = _arguments.begin(); it != _arguments.end(); ++it) {
        (*it)->_clear();
    }
    // get argv[0] if filename is empty
    if (_binaryName.empty()) {
        _binaryName = argv[0];
    }
    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    // foreach argument
    for (int i = 1; i < argc; ++i) {
        if (isShortOption(argv[i])) {
            _parseShortArgument(endIndex, argv, &i);
        }
        else if (isLongOption(argv[i])) {
            _parseLongArgument(endIndex, argv, &i);
        }
        else if (isEndOption(argv[i])) {
            ++i;
            while (i < argc) {
                _parsePositionnalArgument(argc, argv, &i, true);
                ++i;
            }
            break;
        }
        else {
            _parsePositionnalArgument(endIndex, argv, &i);
        }
    }
    // check help option
    if (_helpOption != NULL && _helpOption->_isExist) {
        if (_isHelpException) {
            throw HelpException(getUsage().c_str());
        }
        else {
            std::cout << getUsage() << std::endl;
            clear();
            exit(0);
        }
    }
    // check version option
    if (_versionOption != NULL && _versionOption->_isExist) {
        if (_isVersionException) {
            throw VersionException(getVersion().c_str());
        }
        else {
            std::cout << getVersion() << std::endl;
            clear();
            exit(0);
        }
    }
    // check require option
    std::list<Argument*>::iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_isRequired && (*it)->_isExist == false) {
            if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
                throw ParseArgumentRequiredException((*it)->_nameOrFlags.front().c_str(), "argument is required");
            }
            else {
                throw ParseArgumentRequiredException((*it)->_nameOrFlags.front().c_str(), "option is required");
            }
        }
    }
    // check valid configuration function
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_isExist && (*it)->_valid != NULL) {
            try {
                std::vector<std::string> arguments;
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::NUMBER_POSITIONAL_ARGUMENT:
                    case Argument::INFINITE_POSITIONAL_ARGUMENT:
                    case Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                    case Argument::NUMBER_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                        const Argument& cArg = *(*it);
                        arguments = cArg.operator std::vector<std::string>();
                        break;
                    }
                    default:
                        break;
                }
                if ((*it)->_valid->isValid(arguments) == false) {
                    throw ParseArgumentValidException("invalid check function");
                }
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                        if (!arguments.empty()) {
                            (*it)->_argument = arguments.front();
                        }
                        break;
                    case Argument::NUMBER_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::NUMBER_POSITIONAL_ARGUMENT:
                    case Argument::INFINITE_POSITIONAL_ARGUMENT:
                        for (std::size_t i = 0; i < (*it)->size() && i < arguments.size(); ++i) {
                            (*it)->at(i)._argument = arguments[i];
                        }
                        break;
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION:
                    case Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT: {
                        std::size_t i = 0;
                        for (std::size_t j = 0; j < (*it)->size() && i < arguments.size(); ++j) {
                            for (std::size_t k = 0; k < (*it)->at(j).size() && i < arguments.size(); ++k) {
                                (*it)->at(j).at(k)._argument = arguments[i];
                                ++i;
                            }
                        }
                        break;
                    }
                    default:
                        throw ParseArgumentValidException("invalid type option for use valid");
                        break;
                }
            }
            catch (const ParseArgumentValidException& e) {
                // add name or first flag in exception
                throw ParseArgumentValidException((*it)->_nameOrFlags.front().c_str(), e.what());
            }
        }
        // tranform argument to number
        (*it)->_toNumber();
        // dest
        (*it)->_toDest();
    }
}

Argument& Args::addArgument(const Vector& nameOrFlags) {
    if (nameOrFlags.empty()) {
        throw ArgumentException("", "invalid empty flag");
    }
    Argument* argument = NULL;
    // is name
    if (nameOrFlags.size() == 1 && nameOrFlags.front()[0] != '-') {
        if (nameOrFlags.front().empty()) {
            throw ArgumentException("", "bad name argument");
        }
        if (_argumentFromName.find(nameOrFlags.front()) != _argumentFromName.end()) {
            throw ArgumentException(nameOrFlags.front().c_str(), "bad name argument already exist");
        }
        // create argument
        argument = new Argument(*this);
        argument->_nameOrFlags.push_back(nameOrFlags.front());
        argument->_nargs = 1;
        argument->_type = Argument::POSITIONAL_ARGUMENT;
    }
    else {
        std::vector<std::string> newFlags;

        for (std::size_t i = 0; i < nameOrFlags.size(); ++i) {
            Argument::_validFormatFlag(nameOrFlags[i].c_str());
            if (_argumentFromName.find(nameOrFlags.front()) != _argumentFromName.end()) {
                throw ArgumentException(nameOrFlags.front().c_str(), "invalid flag already exist");
            }
            if (std::find(newFlags.begin(), newFlags.end(), nameOrFlags[i]) == newFlags.end()) {
                newFlags.push_back(nameOrFlags[i]);
            }
        }

        argument = new Argument(*this);
        argument->_nameOrFlags = nameOrFlags;
        argument->_sortNameOrFlags();
    }

    _arguments.push_back(argument);
    Argument** addrNewArgument = &(_arguments.back());
    argument->_this = addrNewArgument;
    for (std::size_t i = 0; i < argument->_nameOrFlags.size(); ++i) {
        _argumentFromName.insert(std::pair<std::string, Argument**>(argument->_nameOrFlags[i], addrNewArgument));
    }
    _arguments.sort(&Argument::_compareOption);
    return **addrNewArgument;
}

void Args::removeArguments(const Vector& nameOrFlags) {
    if (nameOrFlags.empty()) {
        throw ArgumentException("", "invalid empty flag");
    }
    std::vector<std::map<std::string, Argument**>::iterator> vIt;
    // check if all element is exists and store iterator
    for (std::size_t i = 0; i < nameOrFlags.size(); ++i) {
        std::map<std::string, Argument**>::iterator it = _argumentFromName.find(nameOrFlags[i]);
        if (it == _argumentFromName.end()) {
            throw ArgumentException(nameOrFlags[i].c_str(), "argument not found");
        }
        vIt.push_back(it);
    }
    for (std::size_t i = 0; i < vIt.size(); ++i) {
        Argument** ppArgument = vIt[i]->second;
        // remove name or flag in argument object
        std::vector<std::string>::iterator namesIt =
            std::find((*ppArgument)->_nameOrFlags.begin(), (*ppArgument)->_nameOrFlags.end(), vIt[i]->first);
        (*ppArgument)->_nameOrFlags.erase(namesIt);
        // remove argument
        _argumentFromName.erase(vIt[i]);
        // check if ppArgument not exists
        std::map<std::string, Argument**>::iterator it = _argumentFromName.begin();
        for (it = _argumentFromName.begin(); it != _argumentFromName.end(); ++it) {
            if (it->second == ppArgument) {
                break;
            }
        }
        // remove from argument list
        if (it == _argumentFromName.end()) {
            std::list<Argument*>::iterator aIt = std::find(_arguments.begin(), _arguments.end(), *ppArgument);
            if (*aIt == _helpOption) {
                _helpOption = NULL;
            }
            else if (*aIt == _versionOption) {
                _versionOption = NULL;
            }
            delete (*aIt);
            _arguments.erase(aIt);
        }
        else {
            (**it->second)._sortNameOrFlags();
        }
    }
    _arguments.sort(&Argument::_compareOption);
}

void Args::clear() {
    // delete all new element
    for (std::list<Argument*>::iterator it = _arguments.begin(); it != _arguments.end(); ++it) {
        delete (*it);
    }
    _arguments.clear();
    _argumentFromName.clear();
    _binaryName = "";
    _helpOption = NULL;
    _versionOption = NULL;
    _version = "";
    _isAlternative = false;
    _isStrict = false;
    _isHelpException = false;
    _isVersionException = false;
    _additionalArguments.clear();
    // usage
    _description = "";
    _epilog = "";
    _usage = "";
    _usagePadWidth = 2;
    _usageArgsWidth = 20;
    _usageSepWidth = 2;
    _usageHelpWidth = 56;
}

/*
** private
*/
void Args::_parseShortArgument(int maxIndex, char* argv[], int* index) {
    std::string options;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    if (_isAlternative) {
        // try to find long option
        it = _argumentFromName.find("-" + options);
        if (it != _argumentFromName.end()) {
            _parseArgument(maxIndex, argv, index, hasArg, options.c_str() + _ARGS_PREFIX_SIZEOF_SHORT_OPTION,
                           arg.c_str(), *(it->second));
            return;
        }
    }
    // get firsts option
    for (std::size_t i = 1; i < options.size() - 1; ++i) {
        std::string charOption(options, i, 1);
        it = _argumentFromName.find("-" + charOption);
        if (it == _argumentFromName.end()) {
            throw ParseArgumentException(charOption.c_str(), "invalid option");
        }
        else if (!hasArg && ((*(it->second))->_type == Argument::SIMPLE_OPTION ||
                             (*(it->second))->_type == Argument::NUMBER_OPTION ||
                             (*(it->second))->_type == Argument::INFINITE_OPTION ||
                             (*(it->second))->_type == Argument::MULTI_OPTION ||
                             (*(it->second))->_type == Argument::MULTI_INFINITE_OPTION ||
                             (*(it->second))->_type == Argument::MULTI_NUMBER_OPTION)) {
            hasArg = true;
            arg = options.substr(i + 1, options.size() - i);
            (*(it->second))->_isExist = true;
            ++(*(it->second))->_count;
            _parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(), arg.c_str(), *(it->second));
            return;
        }
        else if ((*(it->second))->_type != Argument::BOOLEAN_OPTION &&
                 (*(it->second))->_type != Argument::REVERSE_BOOLEAN_OPTION) {
            throw ParseArgumentException(charOption.c_str(), "only last option can be use a parameter");
        }
        (*(it->second))->_isExist = true;
        ++(*(it->second))->_count;
    }
    // get last option
    std::string charOption(options, options.size() - 1, 1);
    it = _argumentFromName.find("-" + charOption);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(charOption.c_str(), "invalid option");
    }
    _parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(), arg.c_str(), *(it->second));
}

void Args::_parseLongArgument(int maxIndex, char* argv[], int* index) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    it = _argumentFromName.find(option);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(option.c_str() + _ARGS_PREFIX_SIZEOF_LONG_OPTION, "invalid option");
    }
    _parseArgument(maxIndex, argv, index, hasArg, option.c_str() + _ARGS_PREFIX_SIZEOF_LONG_OPTION, arg.c_str(),
                   *(it->second));
}

void Args::_parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                               Argument* argument) {
    if (hasArg) {
        switch (argument->_type) {
            case Argument::SIMPLE_OPTION:
                argument->_argument = arg;
                break;
            case Argument::NUMBER_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                throw ParseArgumentException(option, "option cannot use with only 1 argument");
                break;
            case Argument::INFINITE_OPTION: {
                argument->clear();
                argument->push_back(arg);
                break;
            }
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                argument->push_back(arg);
                break;
            }
            default:
                throw ParseArgumentException(option, "option cannot use with argument");
                break;
        }
    }
    else {
        switch (argument->_type) {
            case Argument::SIMPLE_OPTION:
                if (*index + 1 >= maxIndex) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ++(*index);
                argument->_argument = argv[*index];
                break;
            case Argument::NUMBER_OPTION:
                argument->clear();
                if (*index + argument->_nargs >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                for (unsigned int i = *index + 1; i <= (*index + argument->_nargs); ++i) {
                    argument->push_back(argv[i]);
                }
                *index += argument->_nargs;
                break;
            case Argument::INFINITE_OPTION: {
                argument->clear();
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; ++i) {
                    if (_endOfInfiniteArgument(argv[i])) {
                        break;
                    }
                    argument->push_back(argv[i]);
                    ++countArg;
                }
                *index += countArg;
                break;
            }
            case Argument::MULTI_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                if (*index + 1 >= maxIndex) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ++(*index);
                argument->push_back(argv[*index]);
                break;
            }
            case Argument::MULTI_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; ++i) {
                    if (_endOfInfiniteArgument(argv[i])) {
                        break;
                    }
                    argument->push_back(argv[i]);
                    ++countArg;
                }
                *index += countArg;
                break;
            }
            case Argument::MULTI_NUMBER_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                if (*index + argument->_nargs >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ArgumentElement newNumberArgument;
                for (unsigned int i = *index + 1; i <= *index + argument->_nargs; ++i) {
                    newNumberArgument.push_back(argv[i]);
                }
                argument->push_back(newNumberArgument);
                *index += argument->_nargs;
                break;
            }
            case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; i += argument->_nargs) {
                    if (_endOfInfiniteArgument(argv[i])) {
                        break;
                    }
                    if (i + argument->_nargs > static_cast<unsigned int>(maxIndex)) {
                        throw ParseArgumentException(option, "bad number of argument");
                    }
                    ArgumentElement newNumberArgument;
                    for (unsigned int j = i; j < i + argument->_nargs; ++j) {
                        newNumberArgument.push_back(argv[j]);
                        ++countArg;
                    }
                    argument->push_back(newNumberArgument);
                }
                *index += countArg;
                break;
            }
            default:
                break;
        }
    }
    argument->_isExist = true;
    ++argument->_count;
}

bool Args::_endOfInfiniteArgument(const char* argument) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    if (isShortOption(argument)) {
        bool hasArg = takeArg(argument, &option, &arg);
        if (_isAlternative) {
            it = _argumentFromName.find("-" + option);
            if (it != _argumentFromName.end()) {
                return true;
            }
        }
        // get firsts option
        for (std::size_t i = 1; i < option.size() - 1; ++i) {
            std::string charOption(option, i, 1);
            it = _argumentFromName.find("-" + charOption);
            if (it == _argumentFromName.end()) {
                return false;
            }
            else if (!hasArg && ((*(it->second))->_type == Argument::SIMPLE_OPTION ||
                                 (*(it->second))->_type == Argument::NUMBER_OPTION ||
                                 (*(it->second))->_type == Argument::INFINITE_OPTION ||
                                 (*(it->second))->_type == Argument::MULTI_OPTION ||
                                 (*(it->second))->_type == Argument::MULTI_INFINITE_OPTION ||
                                 (*(it->second))->_type == Argument::MULTI_NUMBER_OPTION)) {
                return true;
            }
            else if ((*(it->second))->_type == Argument::BOOLEAN_OPTION ||
                     (*(it->second))->_type == Argument::REVERSE_BOOLEAN_OPTION) {
                return true;
            }
        }
        // get last option
        std::string charOption(option, option.size() - 1, 1);
        it = _argumentFromName.find("-" + charOption);
    }
    else if (isLongOption(argument)) {
        takeArg(argument, &option, &arg);
        it = _argumentFromName.find(option);
    }
    else {
        return false;
    }
    if (it == _argumentFromName.end()) {
        return false;
    }
    return true;
}

void Args::_parsePositionnalArgument(int argc, char* argv[], int* index, bool hasEndOption) {
    // find not exists positionnal argument
    std::list<Argument*>::iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_isExist == false && (*it)->_isPositionnalArgument()) {
            break;
        }
    }
    if (it != _arguments.end()) {
        Argument& argument = *(*it);
        if (argument._type == Argument::POSITIONAL_ARGUMENT) {
            argument._argument = argv[*index];
        }
        else if (argument._type == Argument::NUMBER_POSITIONAL_ARGUMENT) {
            if (*index + argument._nargs > static_cast<unsigned int>(argc)) {
                throw ParseArgumentException(argument._nameOrFlags.front().c_str(), "bad number of argument");
            }
            for (unsigned int i = *index; i < (*index + argument._nargs); ++i) {
                argument.push_back(argv[i]);
            }
            *index += argument._nargs - 1;
        }
        else if (argument._type == Argument::INFINITE_POSITIONAL_ARGUMENT) {
            std::size_t countArg = 0;
            for (int i = *index; i < argc; ++i) {
                if (!hasEndOption && _endOfInfiniteArgument(argv[i])) {
                    break;
                }
                (*it)->push_back(argv[i]);
                ++countArg;
            }
            *index += countArg - 1;
        }
        else if (argument._type == Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT) {
            std::size_t countArg = 0;
            for (int i = *index; i < argc; i += argument._nargs) {
                if (!hasEndOption && _endOfInfiniteArgument(argv[i])) {
                    break;
                }
                if (i + argument._nargs > static_cast<unsigned int>(argc)) {
                    throw ParseArgumentException(argument._nameOrFlags.front().c_str(), "bad number of argument");
                }
                ArgumentElement newNumberArgument;
                for (unsigned int j = i; j < i + argument._nargs; ++j) {
                    newNumberArgument.push_back(argv[j]);
                    ++countArg;
                }
                argument.push_back(newNumberArgument);
            }
            *index += countArg - 1;
        }
        argument._isExist = true;
    }
    else {
        if (_isStrict) {
            throw ParseArgumentException(argv[*index], "invalid additional argument");
        }
        else {
            _additionalArguments.push_back(argv[*index]);
        }
    }
}

} // namespace args

} // namespace blet

#undef _ARGS_PREFIX_SIZEOF_SHORT_OPTION
#undef _ARGS_PREFIX_SIZEOF_LONG_OPTION