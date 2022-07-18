/**
 * argparsor.cpp
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

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "argparsor.h"

#define PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace mblet {

/**
 * @brief arg is "-[^-].*"
 *
 * @param arg
 * @return true
 * @return false
 */
static inline bool isShortOption(const char* arg) {
    if (arg != NULL &&
        arg[0] == '-' && arg[1] != '-' &&
        arg[1] != '\0') {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief arg is "--.*"
 *
 * @param arg
 * @return true
 * @return false
 */
static inline bool isLongOption(const char* arg) {
    if (arg != NULL &&
        arg[0] == '-' && arg[1] == '-' &&
        arg[2] != '\0') {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief arg is "--"
 *
 * @param arg
 * @return true
 * @return false
 */
static inline bool isEndOption(const char* arg) {
    if (arg != NULL &&
        arg[0] == '-' && arg[1] == '-' &&
        arg[2] == '\0') {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief get index of en option index or argc
 *
 * @param argc
 * @param argv
 * @return int
 */
static inline int endOptionIndex(int argc, char** argv) {
    for (int i = 0 ; i < argc ; ++i) {
        if (isEndOption(argv[i])) {
            return i;
        }
    }
    return argc;
}

/**
 * @brief split arg if contain '=' character
 *
 * @param arg
 * @param retOptionName
 * @param retArgument
 * @return true
 * @return false
 */
static inline bool takeArg(const char* arg, std::string* retOptionName, std::string* retArgument) {
    char* equal = ::strchr(const_cast<char*>(arg), '=');
    if (equal) {
        std::string firstPart(arg, 0, equal - arg);
        *retOptionName = firstPart;
        std::string secondPart(arg, equal - arg + 1, std::string::npos);
        *retArgument = secondPart;
        return true;
    }
    else {
        *retOptionName = arg;
        return false;
    }
}

static bool compareFlag(const std::string& first, const std::string& second) {
    if (isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return first <= second;
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

Argparsor::Argparsor() :
    _binaryName(std::string()),
    _arguments(std::list<Argument>()),
    _argumentFromName(std::map<std::string, Argument*>()),
    _helpOption(NULL),
    _versionOption(NULL),
    _usage(std::string()),
    _description(std::string()),
    _epilog(std::string()),
    _additionalArguments(std::vector<std::string>()) {
    // define _helpOption
    Vector v;
    v.push_back("-h");
    v.push_back("--help");
    addArgument(v, "help", "show this help message and exit");
}

Argparsor::~Argparsor() {}

Argparsor::Argument::Argument() :
    std::vector<Argument>(),
    _names(std::vector<std::string>()),
    _isExist(false),
    _isRequired(false),
    _count(0),
    _nbArgs(0),
    _type(NONE),
    _help(std::string()),
    _argHelp(std::string()),
    _argument(std::string()),
    _default(std::string())
{}

Argparsor::Argument::Argument(const char* arg) :
    std::vector<Argument>(),
    _names(std::vector<std::string>()),
    _isExist(false),
    _isRequired(false),
    _count(0),
    _nbArgs(0),
    _type(NONE),
    _help(std::string()),
    _argHelp(std::string()),
    _argument(arg),
    _default(std::string())
{}

Argparsor::Argument::Argument(const Argument& rhs) :
    std::vector<Argument>(rhs),
    _names(rhs._names),
    _isExist(rhs._isExist),
    _isRequired(rhs._isRequired),
    _count(rhs._count),
    _nbArgs(rhs._nbArgs),
    _type(rhs._type),
    _help(rhs._help),
    _argHelp(rhs._argHelp),
    _argument(rhs._argument),
    _default(rhs._default)
{}

Argparsor::Argument::~Argument() {}

bool Argparsor::Argument::compareOption(const Argparsor::Argument& first, const Argparsor::Argument& second) {
    if (first._type == Argparsor::Argument::POSITIONAL_ARGUMENT && first._isRequired
        && second._type == Argparsor::Argument::POSITIONAL_ARGUMENT && second._isRequired) {
        return false;
    }
    else if (first._type == Argparsor::Argument::POSITIONAL_ARGUMENT && first._isRequired
        && second._type == Argparsor::Argument::POSITIONAL_ARGUMENT) {
        return true;
    }
    else if (first._type == Argparsor::Argument::POSITIONAL_ARGUMENT
        && second._type == Argparsor::Argument::POSITIONAL_ARGUMENT && second._isRequired) {
        return false;
    }
    else if (first._type == Argparsor::Argument::POSITIONAL_ARGUMENT
        && second._type == Argparsor::Argument::POSITIONAL_ARGUMENT) {
        return false;
    }
    else if (first._type == Argparsor::Argument::POSITIONAL_ARGUMENT) {
        return false;
    }
    else if (second._type == Argparsor::Argument::POSITIONAL_ARGUMENT) {
        return true;
    }
    if (isShortOption(first._names[0].c_str()) && isShortOption(second._names[0].c_str())) {
        if (first._isRequired && !second._isRequired) {
            return true;
        }
        else if (!first._isRequired && second._isRequired) {
            return false;
        }
        else {
            return first._names[0] <= second._names[0];
        }
    }
    else if (isShortOption(first._names[0].c_str()) && !isShortOption(second._names[0].c_str())) {
        if (first._isRequired && !second._isRequired) {
            return true;
        }
        else if (!first._isRequired && second._isRequired) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (!isShortOption(first._names[0].c_str()) && isShortOption(second._names[0].c_str())) {
        if (first._isRequired && !second._isRequired) {
            return true;
        }
        else if (!first._isRequired && second._isRequired) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        if (first._isRequired && !second._isRequired) {
            return true;
        }
        else if (!first._isRequired && second._isRequired) {
            return false;
        }
        return first._names[0] < second._names[0];
    }
}

std::ostream& Argparsor::getUsage(std::ostream& oss) {
    if (!_usage.empty()) {
        oss << _usage;
        return oss;
    }
    _arguments.sort(&Argparsor::Argument::compareOption);
    bool hasOption = false;
    bool hasPositionnal = false;
    // usage line
    oss << "usage: " << _binaryName;
    std::list<Argument>::const_iterator it;
    for (it = _arguments.begin() ; it != _arguments.end() ; ++it) {
        if (it->_type == Argument::POSITIONAL_ARGUMENT) {
            hasPositionnal = true;
            continue;
        }
        hasOption = true;
        oss << ' ';
        if (!it->_isRequired) {
            oss << '[';
        }
        oss << it->_names[0];
        switch (it->_type) {
            case Argument::SIMPLE_OPTION:
            case Argument::NUMBER_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                oss << ' ' << it->_argHelp;
                break;
            default:
                break;
        }
        if (!it->_isRequired) {
            oss << ']';
        }
    }
    if (hasOption && hasPositionnal) {
        oss << " --";
    }
    for (it = _arguments.begin() ; it != _arguments.end() ; ++it) {
        if (it->_type != Argument::POSITIONAL_ARGUMENT) {
            continue;
        }
        oss << ' ';
        if (!it->_isRequired) {
            oss << '[';
        }
        oss << it->_names[0];
        if (!it->_isRequired) {
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
        for (it = _arguments.begin() ; it != _arguments.end() ; ++it) {
            std::list<std::pair<std::string, std::string> >* listOption = NULL;
            if (it->_type == Argument::POSITIONAL_ARGUMENT) {
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
            for (std::size_t i = 0; i < it->_names.size(); ++i) {
                if (i > 0) {
                    optionStr += ", ";
                }
                optionStr += it->_names[i];
            }
            switch (it->_type) {
                case Argument::POSITIONAL_ARGUMENT:
                case Argument::SIMPLE_OPTION:
                case Argument::NUMBER_OPTION:
                case Argument::INFINITE_OPTION:
                case Argument::MULTI_OPTION:
                case Argument::MULTI_INFINITE_OPTION:
                case Argument::MULTI_NUMBER_OPTION:
                case Argument::MULTI_NUMBER_INFINITE_OPTION:
                    optionStr += " " + it->_argHelp;
                    break;
                default:
                    break;
            }
            helpStr += "  " + it->_help;
            if (it->_isRequired) {
                helpStr += " (required)";
            }
            else {
                switch (it->_type) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                    case Argument::NUMBER_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION:
                        if (!it->_default.empty()) {
                            helpStr += " (default: " + it->_default + ")";
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
        for (optIt = positionals.begin() ; optIt != positionals.end() ; ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        for (optIt = optionnals.begin() ; optIt != optionnals.end() ; ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        if (!positionals.empty()) {
            oss << "\npositional arguments:\n";
            for (optIt = positionals.begin() ; optIt != positionals.end() ; ++optIt) {
                oss.width(max);
                oss.flags(std::ios::left);
                oss << optIt->first;
                oss.width(0);
                oss << optIt->second;
            }
        }
        if (!optionnals.empty()) {
            oss << "\noptional arguments:\n";
            for (optIt = optionnals.begin() ; optIt != optionnals.end() ; ++optIt) {
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
    return oss;
}

std::ostream& Argparsor::getVersion(std::ostream& oss) {
    if (_versionOption != NULL) {
        oss << _versionOption->getDefault() << '\n';
    }
    return oss;
}

void Argparsor::parseArguments(int argc, char* argv[], bool alternative, bool strict) {
    // sort all arguments
    _arguments.sort(&Argparsor::Argument::compareOption);
    _binaryName = argv[0];
    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    // create parse info
    int i = 1;
    // foreach argument
    for (i = 1 ; i < argc ; ++i) {
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
        getUsage();
        exit(0);
    }
    // check version option
    if (_versionOption != NULL && _versionOption->_isExist) {
        getVersion();
        exit(0);
    }
    // check require option
    std::list<Argument>::iterator it;
    for (it = _arguments.begin() ; it != _arguments.end() ; ++it) {
        if (it->_isRequired && it->_isExist == false) {
            if (it->_type == Argument::POSITIONAL_ARGUMENT) {
                throw ParseArgumentRequiredException(it->_names[0].c_str(), "argument is required");
            }
            else {
                throw ParseArgumentRequiredException(it->_names[0].c_str(), "option is required");
            }
        }
    }
}

void Argparsor::addArgument(const Vector& nameOrFlags, const char* actionOrDefault, const char* help, bool isRequired,
                            const char* argsHelp, std::size_t nbArgs,
                            const Vector& defaultArgs) {
    // is name
    if (nameOrFlags.size() == 1 && nameOrFlags[0][0] != '-') {
        if (nameOrFlags[0].empty()) {
            throw ArgumentException("", "bad name argument");
        }
        else if (_argumentFromName.find(nameOrFlags[0]) != _argumentFromName.end()) {
            throw ArgumentException(nameOrFlags[0].c_str(), "bad name argument already exist");
        }
        // create argument
        Argument argument;

        argument._isRequired = isRequired;
        argument._names.push_back(nameOrFlags[0]);
        argument._type = Argument::POSITIONAL_ARGUMENT;
        if (help != NULL) {
            argument._help = help;
        }
        if (actionOrDefault != NULL && actionOrDefault[0] != '\0') {
            argument._argument = actionOrDefault;
            argument._default = actionOrDefault;
        }
        else if (defaultArgs.size() == 1) {
            argument._argument = defaultArgs[0];
            argument._default = defaultArgs[0];
        }

        _arguments.push_back(argument);
        _argumentFromName.insert(std::pair<std::string, Argument*>(nameOrFlags[0], &(_arguments.back())));
        return;
    }

    std::vector<std::string> flags = nameOrFlags;
    std::sort(flags.begin(), flags.end(), &compareFlag);

    enum eAction {
        NONE = 0,
        STORE_TRUE,
        STORE_FALSE,
        INFINITE,
        APPEND,
        EXTEND,
        VERSION,
        HELP
    } action = NONE;
    if (actionOrDefault != NULL) {
        if (strncmp("store_true", actionOrDefault, sizeof("store_true")) == 0) {
            action = STORE_TRUE;
        }
        else if (strncmp("store_false", actionOrDefault, sizeof("store_false")) == 0) {
            action = STORE_FALSE;
        }
        else if (strncmp("infinite", actionOrDefault, sizeof("infinite")) == 0) {
            action = INFINITE;
        }
        else if (strncmp("append", actionOrDefault, sizeof("append")) == 0) {
            action = APPEND;
        }
        else if (strncmp("extend", actionOrDefault, sizeof("extend")) == 0) {
            action = EXTEND;
        }
        else if (strncmp("version", actionOrDefault, sizeof("version")) == 0) {
            action = VERSION;
        }
        else if (strncmp("help", actionOrDefault, sizeof("help")) == 0) {
            action = HELP;
        }
    }

    // remove last help option
    if (action == HELP && _helpOption != NULL) {
        for (std::list<Argument>::iterator itList = _arguments.begin() ; itList != _arguments.end() ; ++itList) {
            if (_helpOption == &(*itList)) {
                _arguments.erase(itList);
                break;
            }
        }
        std::map<std::string, Argument*>::iterator itMap = _argumentFromName.begin();
        while (itMap != _argumentFromName.end()) {
            if (_helpOption == itMap->second) {
                _argumentFromName.erase(itMap);
                itMap = _argumentFromName.begin();
            }
            else {
                ++itMap;
            }
        }
        _helpOption = NULL;
    }
    // remove last version option
    if (action == VERSION && _versionOption != NULL) {
        for (std::list<Argument>::iterator itList = _arguments.begin() ; itList != _arguments.end() ; ++itList) {
            if (_versionOption == &(*itList)) {
                _arguments.erase(itList);
                break;
            }
        }
        std::map<std::string, Argument*>::iterator itMap = _argumentFromName.begin();
        while (itMap != _argumentFromName.end()) {
            if (_versionOption == itMap->second) {
                _argumentFromName.erase(itMap);
                itMap = _argumentFromName.begin();
            }
            else {
                ++itMap;
            }
        }
        _versionOption = NULL;
    }
    if (flags.empty()) {
        if (action == HELP || action == VERSION) {
            return;
        }
        else {
            throw ArgumentException("", "invalid empty flag");
        }
    }

    std::vector<std::string> newFlags;

    const char* shortFlag = NULL;
    const char* longFlag = NULL;

    for (std::size_t i = 0 ; i < flags.size() ; ++i) {
        if (flags[i][0] != '-') {
            throw ArgumentException(flags[i].c_str(), "invalid flag not start by '-' character");
        }

        if (flags[i] == "-") {
            throw ArgumentException(flags[i].c_str(), "invalid flag not be only '-' character");
        }
        if (flags[i] == "--") {
            throw ArgumentException(flags[i].c_str(), "invalid flag not be only '--' characters");
        }

        if (flags[i][0] == '-' && flags[i][1] != '-' && flags[i][2] != '\0') {
            throw ArgumentException(flags[i].c_str(), "invalid short flag has not only one character");
        }

        if (_argumentFromName.find(flags[i]) != _argumentFromName.end()) {
            throw ArgumentException(flags[i].c_str(), "invalid flag already exist");
        }

        if (longFlag == NULL && flags[i][0] == '-' && flags[i][1] == '-') {
            longFlag = flags[i].c_str();
        }
        else if (shortFlag == NULL && flags[i][0] == '-' && flags[i][1] != '-') {
            shortFlag = flags[i].c_str();
        }

        if (std::find(newFlags.begin(), newFlags.end(), flags[i]) == newFlags.end()) {
            newFlags.push_back(flags[i]);
        }
    }

    // create argument
    Argument argument;
    argument._names = newFlags;

    if (nbArgs > 0 && (argsHelp == NULL || argsHelp[0] == '\0')) {
        std::string defaultUsageName;
        // create a defaultUsageName from longName or shortName
        if (longFlag != NULL) {
            defaultUsageName = longFlag + PREFIX_SIZEOF_LONG_OPTION;
        }
        else {
            defaultUsageName = shortFlag + PREFIX_SIZEOF_SHORT_OPTION;
        }
        for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
            defaultUsageName[i] = ::toupper(defaultUsageName[i]);
        }
        if (action == INFINITE || nbArgs == '+') {
            argument._argHelp = defaultUsageName + "...";
        }
        else {
            std::string numberDefaultUsageName;
            for (std::size_t i = 0 ; i < nbArgs ; ++i) {
                if (i > 0) {
                    numberDefaultUsageName += " ";
                }
                numberDefaultUsageName += defaultUsageName;
            }
            argument._argHelp = numberDefaultUsageName;
        }
    }
    argument._isRequired = isRequired;
    if (help != NULL && help[0] != '\0') {
        argument._help = help;
    }
    if (argsHelp != NULL && argsHelp[0] != '\0') {
        argument._argHelp = argsHelp;
    }
    argument._nbArgs = nbArgs;
    // is bool
    if (action == STORE_TRUE) {
        argument._type = Argument::BOOLEAN_OPTION;
    }
    else if (action == STORE_FALSE) {
        argument._type = Argument::REVERSE_BOOLEAN_OPTION;
    }
    // is simple
    else if (nbArgs == 1 && action == NONE) {
        argument._type = Argument::SIMPLE_OPTION;
    }
    // is infinite
    else if ((nbArgs == '+' && action == NONE) || action == INFINITE) {
        argument._type = Argument::INFINITE_OPTION;
    }
    // is number
    else if (nbArgs > 1 && action == NONE) {
        argument._type = Argument::NUMBER_OPTION;
    }
    // is multi
    else if (nbArgs == 1 && action == APPEND) {
        argument._type = Argument::MULTI_OPTION;
    }
    // is multi number
    else if (nbArgs > 1 && action == APPEND) {
        argument._type = Argument::MULTI_NUMBER_OPTION;
    }
    // is multi infinite
    else if (nbArgs == 1 && action == EXTEND) {
        argument._type = Argument::MULTI_INFINITE_OPTION;
    }
    // is multi number infinite
    else if (nbArgs > 1 && action == EXTEND) {
        argument._type = Argument::MULTI_NUMBER_INFINITE_OPTION;
    }
    else {
        argument._type = Argument::BOOLEAN_OPTION;
    }
    // default arguments
    if (isRequired == false && defaultArgs.size() > 0) {
        switch (argument._type) {
            case Argument::SIMPLE_OPTION:
                if (defaultArgs.size() != nbArgs) {
                    if (longFlag != NULL) {
                        throw ArgumentException(longFlag, "invalid number of argument with number of default argument");
                    }
                    else {
                        throw ArgumentException(shortFlag, "invalid number of argument with number of default argument");
                    }
                }
                argument._argument = defaultArgs[0];
                argument._default = defaultArgs[0];
                break;
            case Argument::NUMBER_OPTION:
                if (defaultArgs.size() != nbArgs) {
                    if (longFlag != NULL) {
                        throw ArgumentException(longFlag, "invalid number of argument with number of default argument");
                    }
                    else {
                        throw ArgumentException(shortFlag, "invalid number of argument with number of default argument");
                    }
                }
                for (std::size_t i = 0 ; i < defaultArgs.size() ; ++i) {
                    if (i > 0) {
                        argument._default += ", ";
                    }
                    argument._default += defaultArgs[i];
                    Argument newArgument;
                    newArgument._argument = defaultArgs[i];
                    newArgument._default = defaultArgs[i];
                    argument.push_back(newArgument);
                }
                break;
            case Argument::MULTI_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
                for (std::size_t i = 0 ; i < defaultArgs.size() ; ++i) {
                    if (i > 0) {
                        argument._default += ", ";
                    }
                    argument._default += defaultArgs[i];
                    Argument newArgument;
                    newArgument._argument = defaultArgs[i];
                    newArgument._default = defaultArgs[i];
                    argument.push_back(newArgument);
                }
                break;
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                if (defaultArgs.size() % nbArgs != 0) {
                    if (longFlag != NULL) {
                        throw ArgumentException(longFlag, "invalid number of argument with number of default argument");
                    }
                    else {
                        throw ArgumentException(shortFlag, "invalid number of argument with number of default argument");
                    }
                }
                for (std::size_t i = 0 ; i < defaultArgs.size() / nbArgs; ++i) {
                    if (i > 0) {
                        argument._default += ", ";
                    }
                    argument._default += "(";
                    Argument newNumberArgument;
                    newNumberArgument._type = Argument::NUMBER_OPTION;
                    for (std::size_t j = 0 ; j < nbArgs ; ++j) {
                        if (j > 0) {
                            argument._default += ", ";
                            newNumberArgument._default += ", ";
                        }
                        argument._default += defaultArgs[i * nbArgs + j];
                        newNumberArgument._default += defaultArgs[i * nbArgs + j];
                        Argument newArgument;
                        newArgument._argument = defaultArgs[i * nbArgs + j];
                        newArgument._default = defaultArgs[i * nbArgs + j];
                        newNumberArgument.push_back(newArgument);
                    }
                    argument._default += ")";
                    argument.push_back(newNumberArgument);
                }
                break;
            default:
                if (action == VERSION) {
                    for (std::size_t i = 0 ; i < defaultArgs.size() ; ++i) {
                        if (i > 0) {
                            argument._default += "\n";
                        }
                        argument._default += defaultArgs[i];
                    }
                }
                else if (longFlag != NULL) {
                    throw ArgumentException(longFlag, "invalid number of argument with number of default argument");
                }
                else {
                    throw ArgumentException(shortFlag, "invalid number of argument with number of default argument");
                }
                break;
        }
    }

    // add in Argument list
    _arguments.push_back(argument);
    Argument& newArgument = _arguments.back(); // get new argument object
    for (std::size_t i = 0; i < newArgument._names.size(); ++i) {
        _argumentFromName.insert(std::pair<std::string, Argument*>(newArgument._names[i], &newArgument));
    }

    if (action == HELP) {
        _helpOption = &newArgument;
    }
    else if (action == VERSION) {
        _versionOption = &newArgument;
    }
}

/*
** private
*/

void Argparsor::parseShortArgument(int maxIndex, char* argv[], int* index, bool alternative) {
    std::string options;
    std::string arg;
    std::map<std::string, Argument*>::iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    if (alternative) {
        // try to find long option
        it = _argumentFromName.find("-" + options);
        if (it != _argumentFromName.end()) {
            parseArgument(maxIndex, argv, index, hasArg, options.c_str() + PREFIX_SIZEOF_SHORT_OPTION,
                          arg.c_str(), it->second, alternative);
            return ;
        }
    }
    // get firsts option
    for (std::size_t i = 1 ; i < options.size() - 1 ; ++i) {
        std::string charOption(options, i, 1);
        it = _argumentFromName.find("-" + charOption);
        if (it == _argumentFromName.end()) {
            throw ParseArgumentException(charOption.c_str(), "invalid option");
        }
        else if (!hasArg && (
                    it->second->_type == Argument::SIMPLE_OPTION ||
                    it->second->_type == Argument::NUMBER_OPTION ||
                    it->second->_type == Argument::INFINITE_OPTION ||
                    it->second->_type == Argument::MULTI_OPTION ||
                    it->second->_type == Argument::MULTI_INFINITE_OPTION ||
                    it->second->_type == Argument::MULTI_NUMBER_OPTION
                    )
                ) {
            hasArg = true;
            arg = options.substr(i + 1, options.size() - i);
            it->second->_isExist = true;
            ++it->second->_count;
            parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(),
                  arg.c_str(), it->second, alternative);
            return;
        }
        else if (it->second->_type != Argument::BOOLEAN_OPTION &&
                 it->second->_type != Argument::REVERSE_BOOLEAN_OPTION) {
            throw ParseArgumentException(charOption.c_str(), "only last option can be use a parameter");
        }
        it->second->_isExist = true;
        ++it->second->_count;
    }
    // get last option
    std::string charOption(options, options.size() - 1, 1);
    it = _argumentFromName.find("-" + charOption);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(charOption.c_str(), "invalid option");
    }
    parseArgument(maxIndex, argv, index, hasArg, charOption.c_str(),
                  arg.c_str(), it->second, alternative);
}

void Argparsor::parseLongArgument(int maxIndex, char* argv[], int* index, bool alternative) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument*>::iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    it = _argumentFromName.find(option);
    if (it == _argumentFromName.end()) {
        throw ParseArgumentException(option.c_str() + PREFIX_SIZEOF_LONG_OPTION, "invalid option");
    }
    parseArgument(maxIndex, argv, index, hasArg, option.c_str() + PREFIX_SIZEOF_LONG_OPTION,
                  arg.c_str(), it->second, alternative);
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
                if (*index + argument->_nbArgs >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                for (unsigned int i = *index + 1 ; i <= (*index + argument->_nbArgs) ; ++i) {
                    argument->push_back(argv[i]);
                }
                *index += argument->_nbArgs;
                break;
            case Argument::INFINITE_OPTION: {
                argument->clear();
                std::size_t countArg = 0;
                for (int i = *index + 1 ; i < maxIndex ; ++i) {
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
                for (int i = *index + 1 ; i < maxIndex ; ++i) {
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
                if (*index + argument->_nbArgs >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                Argument newNumberArgument;
                newNumberArgument._type = Argument::NUMBER_OPTION;
                for (unsigned int i = *index + 1 ; i <= *index + argument->_nbArgs ; ++i) {
                    newNumberArgument.push_back(argv[i]);
                }
                argument->push_back(newNumberArgument);
                *index += argument->_nbArgs;
                break;
            }
            case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                if (argument->_isExist == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1 ; i < maxIndex ; i += argument->_nbArgs) {
                    if (endOfInfiniteArgument(argv[i], alternative)) {
                        break;
                    }
                    if (i + argument->_nbArgs > static_cast<unsigned int>(maxIndex)) {
                        throw ParseArgumentException(option, "bad number of argument");
                    }
                    Argument newNumberArgument;
                    newNumberArgument._type = Argument::NUMBER_OPTION;
                    for (unsigned int j = i; j < i + argument->_nbArgs; ++j) {
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
    std::map<std::string, Argument*>::iterator it;
    if (isShortOption(argument)) {
        bool hasArg = takeArg(argument, &option, &arg);
        if (alternative) {
            it = _argumentFromName.find("-" + option);
            if (it != _argumentFromName.end()) {
                return true;
            }
        }
        // get firsts option
        for (std::size_t i = 1 ; i < option.size() - 1 ; ++i) {
            std::string charOption(option, i, 1);
            it = _argumentFromName.find("-" + charOption);
            if (it == _argumentFromName.end()) {
                return false;
            }
            else if (!hasArg && (
                        it->second->_type == Argument::SIMPLE_OPTION ||
                        it->second->_type == Argument::NUMBER_OPTION ||
                        it->second->_type == Argument::INFINITE_OPTION ||
                        it->second->_type == Argument::MULTI_OPTION ||
                        it->second->_type == Argument::MULTI_INFINITE_OPTION ||
                        it->second->_type == Argument::MULTI_NUMBER_OPTION
                        )
                    ) {
                return true;
            }
            else if (it->second->_type == Argument::BOOLEAN_OPTION ||
                     it->second->_type == Argument::REVERSE_BOOLEAN_OPTION) {
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
    std::list<Argument>::iterator it;
    for (it = _arguments.begin() ; it != _arguments.end() ; ++it) {
        // assign to first not used positional argument
        if (it->_type == Argument::POSITIONAL_ARGUMENT && it->_isExist == false) {
            it->_argument = argv[*index];
            it->_isExist = true;
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

} // namespace mblet