/**
 * argparsor-argparsor.cpp
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

#include "mblet/argparsor-argparsor.h"

#include <algorithm>
#include <iostream>

#include "mblet/argparsor-argument.h"
#include "mblet/argparsor-utils.h"
#include "mblet/argparsor-vector.h"

#define PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace mblet {

namespace argparsor {

Argparsor::Argparsor(bool help) :
    _binaryName(),
    _arguments(),
    _argumentFromName(),
    _helpOption(NULL),
    _versionOption(NULL),
    _usage(),
    _description(),
    _epilog(),
    _additionalArguments() {
    if (help) {
        // define _helpOption
        addArgument("-h").flag("--help").action(Action::HELP).help("show this help message and exit");
    }
}

Argparsor::~Argparsor() {
    // delete all new element
    for (std::list<Argument*>::iterator it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_valid != NULL) {
            delete (*it)->_valid;
        }
        delete (*it);
    }
}

std::string Argparsor::getUsage() const {
    std::ostringstream oss("");
    if (!_usage.empty()) {
        return _usage;
    }
    bool hasOption = false;
    bool hasPositionnal = false;
    // usage line
    oss << "usage: " << _binaryName;
    std::list<Argument*>::const_iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
            hasPositionnal = true;
            continue;
        }
        hasOption = true;
        oss << ' ';
        if (!(*it)->_isRequired) {
            oss << '[';
        }
        oss << (*it)->_nameOrFlags.front();
        switch ((*it)->_type) {
            case Argument::SIMPLE_OPTION:
            case Argument::NUMBER_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                if ((*it)->_metavar.empty()) {
                    oss << ' ' << (*it)->_metavarDefault();
                }
                else {
                    oss << ' ' << (*it)->_metavar;
                }
                break;
            default:
                break;
        }
        if (!(*it)->_isRequired) {
            oss << ']';
        }
    }
    if (hasOption && hasPositionnal) {
        oss << " --";
    }
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        if ((*it)->_type != Argument::POSITIONAL_ARGUMENT) {
            continue;
        }
        oss << ' ';
        if (!(*it)->_isRequired) {
            oss << '[';
        }
        oss << (*it)->_nameOrFlags.front();
        if (!(*it)->_isRequired) {
            oss << ']';
        }
    }
    oss << '\n';
    // description
    if (!_description.empty()) {
        oss << '\n' << _description << '\n';
    }
    // optionnal
    if (!_arguments.empty()) {
        std::list<std::pair<std::string, std::string> > positionals;
        std::list<std::pair<std::string, std::string> > optionnals;
        for (it = _arguments.begin(); it != _arguments.end(); ++it) {
            std::list<std::pair<std::string, std::string> >* listOption = NULL;
            if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
                positionals.push_back(std::pair<std::string, std::string>("", ""));
                listOption = &positionals;
            }
            else {
                optionnals.push_back(std::pair<std::string, std::string>("", ""));
                listOption = &optionnals;
            }
            std::string& optionStr = listOption->back().first;
            std::string& helpStr = listOption->back().second;
            optionStr += "  ";
            for (std::size_t i = 0; i < (*it)->_nameOrFlags.size(); ++i) {
                if (i > 0) {
                    optionStr += ", ";
                }
                optionStr += (*it)->_nameOrFlags[i];
            }
            switch ((*it)->_type) {
                case Argument::SIMPLE_OPTION:
                case Argument::NUMBER_OPTION:
                case Argument::INFINITE_OPTION:
                case Argument::MULTI_OPTION:
                case Argument::MULTI_INFINITE_OPTION:
                case Argument::MULTI_NUMBER_OPTION:
                case Argument::MULTI_NUMBER_INFINITE_OPTION:
                    if ((*it)->_metavar.empty()) {
                        optionStr += " " + (*it)->_metavarDefault();
                    }
                    else {
                        optionStr += " " + (*it)->_metavar;
                    }
                    break;
                default:
                    break;
            }
            helpStr += "  " + (*it)->_help;
            if ((*it)->_isRequired) {
                helpStr += " (required)";
            }
            else {
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                    case Argument::NUMBER_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION:
                        if (!(*it)->_default.empty()) {
                            helpStr += " (default: " + (*it)->_default + ")";
                        }
                        break;
                    default:
                        break;
                }
            }
            helpStr += "\n";
        }
        // calculate width max
        std::size_t max = 0;
        std::list<std::pair<std::string, std::string> >::iterator optIt;
        for (optIt = positionals.begin(); optIt != positionals.end(); ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        for (optIt = optionnals.begin(); optIt != optionnals.end(); ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        if (!positionals.empty()) {
            oss << "\npositional arguments:\n";
            for (optIt = positionals.begin(); optIt != positionals.end(); ++optIt) {
                oss.width(max);
                oss.flags(std::ios::left);
                oss << optIt->first;
                oss.width(0);
                oss << optIt->second;
            }
        }
        if (!optionnals.empty()) {
            oss << "\noptional arguments:\n";
            for (optIt = optionnals.begin(); optIt != optionnals.end(); ++optIt) {
                oss.width(max);
                oss.flags(std::ios::left);
                oss << optIt->first;
                oss.width(0);
                oss << optIt->second;
            }
        }
    }
    // epilog
    if (!_epilog.empty()) {
        oss << '\n' << _epilog << '\n';
    }
    return oss.str();
}

std::string Argparsor::getVersion() const {
    std::ostringstream oss("");
    if (_versionOption != NULL) {
        oss << _versionOption->_default << std::endl;
    }
    return oss.str();
}

void Argparsor::parseArguments(int argc, char* argv[], bool alternative, bool strict) {
    _binaryName = argv[0];
    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    // create parse info
    int i = 1;
    // foreach argument
    for (i = 1; i < argc; ++i) {
        if (isShortOption(argv[i])) {
            parseShortArgument(endIndex, argv, &i, alternative);
        }
        else if (isLongOption(argv[i])) {
            parseLongArgument(endIndex, argv, &i, alternative);
        }
        else if (isEndOption(argv[i])) {
            ++i;
            while (i < argc) {
                parsePositionnalArgument(argv, &i, strict);
                ++i;
            }
            break;
        }
        else {
            parsePositionnalArgument(argv, &i, strict);
        }
    }
    // check help option
    if (_helpOption != NULL && _helpOption->_isExist) {
        std::cout << getUsage() << std::flush;
        this->~Argparsor();
        exit(0);
    }
    // check version option
    if (_versionOption != NULL && _versionOption->_isExist) {
        std::cout << getVersion() << std::flush;
        this->~Argparsor();
        exit(0);
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
                        throw ParseArgumentValidException("invalid type option for use valid");
                        break;
                }
                if ((*it)->_valid->isValid(arguments) == false) {
                    throw ParseArgumentValidException("invalid check function");
                }
                switch ((*it)->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                        if (!arguments.empty()) {
                            (*it)->_argument = arguments[0];
                        }
                        break;
                    case Argument::NUMBER_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                        for (std::size_t i = 0; i < (*it)->size() && i < arguments.size(); ++i) {
                            (*it)->at(i)._argument = arguments[i];
                        }
                        break;
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION: {
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

Argument& Argparsor::addArgument(const Vector& nameOrFlags) {
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
            Argument::validFormatFlag(nameOrFlags[i].c_str());
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
        argument->_type = Argument::NONE;
    }

    _arguments.push_back(argument);
    Argument** addrNewArgument = &(_arguments.back());
    argument->_this = addrNewArgument;
    for (std::size_t i = 0; i < argument->_nameOrFlags.size(); ++i) {
        _argumentFromName.insert(std::pair<std::string, Argument**>(argument->_nameOrFlags[i], addrNewArgument));
    }
    _arguments.sort(&Argument::compareOption);
    return **addrNewArgument;
}

/*
** private
*/
void Argparsor::parseShortArgument(int maxIndex, char* argv[], int* index, bool alternative) {
    std::string options;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    if (alternative) {
        // try to find long option
        it = _argumentFromName.find("-" + options);
        if (it != _argumentFromName.end()) {
            parseArgument(maxIndex, argv, index, hasArg, options.c_str() + PREFIX_SIZEOF_SHORT_OPTION, arg.c_str(),
                          *(it->second), alternative);
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
            parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(), arg.c_str(), *(it->second), alternative);
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
    parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(), arg.c_str(), *(it->second), alternative);
}

void Argparsor::parseLongArgument(int maxIndex, char* argv[], int* index, bool alternative) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    it = _argumentFromName.find(option);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(option.c_str() + PREFIX_SIZEOF_LONG_OPTION, "invalid option");
    }
    parseArgument(maxIndex, argv, index, hasArg, option.c_str() + PREFIX_SIZEOF_LONG_OPTION, arg.c_str(), *(it->second),
                  alternative);
}

void Argparsor::parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                              Argument* argument, bool alternative) {
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
                    if (endOfInfiniteArgument(argv[i], alternative)) {
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
                    if (endOfInfiniteArgument(argv[i], alternative)) {
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
                    if (endOfInfiniteArgument(argv[i], alternative)) {
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

bool Argparsor::endOfInfiniteArgument(const char* argument, bool alternative) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    if (isShortOption(argument)) {
        bool hasArg = takeArg(argument, &option, &arg);
        if (alternative) {
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

void Argparsor::parsePositionnalArgument(char* argv[], int* index, bool strict) {
    std::list<Argument*>::iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        // assign to first not used positional argument
        if ((*it)->_type == Argument::POSITIONAL_ARGUMENT && (*it)->_isExist == false) {
            (*it)->_argument = argv[*index];
            (*it)->_isExist = true;
            break;
        }
    }
    if (it == _arguments.end()) {
        if (strict) {
            throw ParseArgumentException(argv[*index], "invalid additional argument");
        }
        else {
            _additionalArguments.push_back(argv[*index]);
        }
    }
}

}  // namespace argparsor

}  // namespace mblet