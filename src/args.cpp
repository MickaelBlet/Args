/**
 * args.cpp
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

#include "blet/args/args.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "blet/args/argument.h"
#include "blet/args/utils.h"
#include "blet/args/vector.h"

#define ARGS_PREFIX_SIZEOF_SHORT_OPTION_ (sizeof("-") - 1)
#define ARGS_PREFIX_SIZEOF_LONG_OPTION_ (sizeof("--") - 1)

namespace blet {

namespace args {

Args::Args() :
    Usage(*this),
    binaryName_(),
    arguments_(),
    argumentFromName_(),
    helpOption_(NULL),
    versionOption_(NULL),
    isAlternative_(false),
    isStrict_(false),
    isAbbreviate_(false),
    isHelpException_(false),
    isVersionException_(false),
    additionalArguments_() {}

Args::~Args() {
    // delete all new element
    for (std::list<Argument*>::iterator it = arguments_.begin(); it != arguments_.end(); ++it) {
        delete (*it);
    }
}

void Args::parseArguments(int argc, char* argv[]) {
    // clear the arguments
    for (std::list<Argument*>::iterator it = arguments_.begin(); it != arguments_.end(); ++it) {
        (*it)->clear_();
    }
    // check help option exists
    if (helpOption_ == NULL) {
        const std::map<std::string, blet::args::Argument**>::const_iterator cith = argumentFromName_.find("-h");
        const std::map<std::string, blet::args::Argument**>::const_iterator cithelp = argumentFromName_.find("--help");
        if (cith != argumentFromName_.end() && cithelp != argumentFromName_.end()) {
            // the flags are already used
            return;
        }
        Vector flags;
        if (cith == argumentFromName_.end()) {
            flags.push_back("-h");
        }
        if (cithelp == argumentFromName_.end()) {
            flags.push_back("--help");
        }
        addArgument(flags).action(Action::HELP).help("show this help message and exit");
    }
    // get argv[0] if filename is empty
    if (binaryName_.empty()) {
        binaryName_ = argv[0];
    }
    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    // foreach argument
    for (int i = 1; i < argc; ++i) {
        if (isShortOption(argv[i])) {
            parseShortArgument_(endIndex, argv, &i);
        }
        else if (isLongOption(argv[i])) {
            parseLongArgument_(endIndex, argv, &i);
        }
        else if (isEndOption(argv[i])) {
            ++i;
            while (i < argc) {
                parsePositionnalArgument_(argc, argv, &i, true);
                ++i;
            }
            break;
        }
        else {
            parsePositionnalArgument_(endIndex, argv, &i);
        }
    }
    // check help option
    if (helpOption_ != NULL && helpOption_->isExist_) {
        if (isHelpException_) {
            throw HelpException(getUsage().c_str());
        }
        else {
            std::cout << getUsage() << std::endl;
            clear();
            exit(0);
        }
    }
    // check version option
    if (versionOption_ != NULL && versionOption_->isExist_) {
        if (isVersionException_) {
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
    for (it = arguments_.begin(); it != arguments_.end(); ++it) {
        if ((*it)->isRequired_ && (*it)->isExist_ == false) {
            if ((*it)->type_ == Argument::POSITIONAL_ARGUMENT) {
                throw ParseArgumentRequiredException((*it)->nameOrFlags_.front().c_str(), "argument is required");
            }
            else {
                throw ParseArgumentRequiredException((*it)->nameOrFlags_.front().c_str(), "option is required");
            }
        }
    }
    // check valid configuration function
    for (it = arguments_.begin(); it != arguments_.end(); ++it) {
        if ((*it)->isExist_ && (*it)->valid_ != NULL) {
            try {
                std::vector<std::string> arguments;
                switch ((*it)->type_) {
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
                if ((*it)->valid_->isValid(arguments) == false) {
                    throw ParseArgumentValidException("invalid check function");
                }
                switch ((*it)->type_) {
                    case Argument::POSITIONAL_ARGUMENT:
                    case Argument::SIMPLE_OPTION:
                        if (!arguments.empty()) {
                            (*it)->argument_ = arguments.front();
                        }
                        break;
                    case Argument::NUMBER_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::NUMBER_POSITIONAL_ARGUMENT:
                    case Argument::INFINITE_POSITIONAL_ARGUMENT:
                        for (std::size_t i = 0; i < (*it)->size() && i < arguments.size(); ++i) {
                            (*it)->at(i).argument_ = arguments[i];
                        }
                        break;
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION:
                    case Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT: {
                        std::size_t i = 0;
                        for (std::size_t j = 0; j < (*it)->size() && i < arguments.size(); ++j) {
                            for (std::size_t k = 0; k < (*it)->at(j).size() && i < arguments.size(); ++k) {
                                (*it)->at(j).at(k).argument_ = arguments[i];
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
                throw ParseArgumentValidException((*it)->nameOrFlags_.front().c_str(), e.what());
            }
        }
        // tranform argument to number
        (*it)->toNumber_();
        // dest
        (*it)->toDest_();
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
        if (argumentFromName_.find(nameOrFlags.front()) != argumentFromName_.end()) {
            throw ArgumentException(nameOrFlags.front().c_str(), "bad name argument already exist");
        }
        // create argument
        argument = new Argument(*this);
        argument->nameOrFlags_.push_back(nameOrFlags.front());
        argument->nargs_ = 1;
        argument->type_ = Argument::POSITIONAL_ARGUMENT;
    }
    else {
        std::vector<std::string> newFlags;
        newFlags.reserve(nameOrFlags.size());

        for (std::size_t i = 0; i < nameOrFlags.size(); ++i) {
            Argument::validFormatFlag_(nameOrFlags[i].c_str());
            if (argumentFromName_.find(nameOrFlags[i]) != argumentFromName_.end()) {
                throw ArgumentException(nameOrFlags[i].c_str(), "invalid flag already exist");
            }
            if (std::find(newFlags.begin(), newFlags.end(), nameOrFlags[i]) == newFlags.end()) {
                newFlags.push_back(nameOrFlags[i]);
            }
        }

        argument = new Argument(*this);
        argument->nameOrFlags_.swap(newFlags);
        argument->sortNameOrFlags_();
    }

    arguments_.push_back(argument);
    Argument** addrNewArgument = &(arguments_.back());
    argument->this_ = addrNewArgument;
    for (std::size_t i = 0; i < argument->nameOrFlags_.size(); ++i) {
        argumentFromName_.insert(std::pair<std::string, Argument**>(argument->nameOrFlags_[i], addrNewArgument));
    }
    arguments_.sort(&Argument::compareOption_);
    return **addrNewArgument;
}

void Args::removeArguments(const Vector& nameOrFlags) {
    if (nameOrFlags.empty()) {
        throw ArgumentException("", "invalid empty flag");
    }
    std::vector<std::map<std::string, Argument**>::iterator> vIt;
    // check if all element is exists and store iterator
    for (std::size_t i = 0; i < nameOrFlags.size(); ++i) {
        std::map<std::string, Argument**>::iterator it = argumentFromName_.find(nameOrFlags[i]);
        if (it == argumentFromName_.end()) {
            throw ArgumentException(nameOrFlags[i].c_str(), "argument not found");
        }
        vIt.push_back(it);
    }
    for (std::size_t i = 0; i < vIt.size(); ++i) {
        Argument** ppArgument = vIt[i]->second;
        // remove name or flag in argument object
        std::vector<std::string>::iterator namesIt =
            std::find((*ppArgument)->nameOrFlags_.begin(), (*ppArgument)->nameOrFlags_.end(), vIt[i]->first);
        (*ppArgument)->nameOrFlags_.erase(namesIt);
        // remove argument
        argumentFromName_.erase(vIt[i]);
        // check if ppArgument not exists
        std::map<std::string, Argument**>::iterator it = argumentFromName_.begin();
        for (it = argumentFromName_.begin(); it != argumentFromName_.end(); ++it) {
            if (it->second == ppArgument) {
                break;
            }
        }
        // remove from argument list
        if (it == argumentFromName_.end()) {
            std::list<Argument*>::iterator aIt = std::find(arguments_.begin(), arguments_.end(), *ppArgument);
            if (*aIt == helpOption_) {
                helpOption_ = NULL;
            }
            else if (*aIt == versionOption_) {
                versionOption_ = NULL;
            }
            delete (*aIt);
            arguments_.erase(aIt);
        }
        else {
            (**it->second).sortNameOrFlags_();
        }
    }
    arguments_.sort(&Argument::compareOption_);
}

void Args::clear() {
    // delete all new element
    for (std::list<Argument*>::iterator it = arguments_.begin(); it != arguments_.end(); ++it) {
        delete (*it);
    }
    arguments_.clear();
    argumentFromName_.clear();
    binaryName_.clear();
    helpOption_ = NULL;
    versionOption_ = NULL;
    version_.clear();
    isAlternative_ = false;
    isStrict_ = false;
    isHelpException_ = false;
    isVersionException_ = false;
    isAbbreviate_ = false;
    additionalArguments_.clear();
    // usage
    description_.clear();
    epilog_.clear();
    usage_.clear();
    usagePadWidth_ = 2;
    usageArgsWidth_ = 20;
    usageSepWidth_ = 2;
    usageHelpWidth_ = 56;
}

/*
** private
*/
void Args::parseShortArgument_(int maxIndex, char* argv[], int* index) {
    std::string options;
    std::string arg;
    std::map<std::string, Argument**>::const_iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    if (isAlternative_) {
        // try to find long option
        std::string altOption("-");
        altOption += options;
        it = argumentFromName_.find(altOption);
        if (it != argumentFromName_.end()) {
            parseArgument_(maxIndex, argv, index, hasArg, it->first.c_str() + ARGS_PREFIX_SIZEOF_LONG_OPTION_,
                           arg.c_str(), *(it->second));
            return;
        }
    }
    // Pre-allocate short option key buffer: "-X"
    std::string shortKey("-");
    shortKey.reserve(2);
    // get firsts option
    for (std::size_t i = 1; i < options.size() - 1; ++i) {
        shortKey.resize(1);
        shortKey += options[i];
        it = argumentFromName_.find(shortKey);
        if (it == argumentFromName_.end()) {
            const char optChar[2] = {options[i], '\0'};
            throw ParseArgumentException(optChar, "invalid option");
        }
        else if (!hasArg && ((*(it->second))->type_ == Argument::SIMPLE_OPTION ||
                             (*(it->second))->type_ == Argument::NUMBER_OPTION ||
                             (*(it->second))->type_ == Argument::INFINITE_OPTION ||
                             (*(it->second))->type_ == Argument::MULTI_OPTION ||
                             (*(it->second))->type_ == Argument::MULTI_INFINITE_OPTION ||
                             (*(it->second))->type_ == Argument::MULTI_NUMBER_OPTION)) {
            hasArg = true;
            arg.assign(options, i + 1, std::string::npos);
            (*(it->second))->isExist_ = true;
            ++(*(it->second))->count_;
            const char optChar[2] = {options[i], '\0'};
            parseArgument_(maxIndex, argv, index, hasArg, optChar, arg.c_str(), *(it->second));
            return;
        }
        else if ((*(it->second))->type_ != Argument::BOOLEAN_OPTION &&
                 (*(it->second))->type_ != Argument::REVERSE_BOOLEAN_OPTION) {
            const char optChar[2] = {options[i], '\0'};
            throw ParseArgumentException(optChar, "only last option can be use a parameter");
        }
        (*(it->second))->isExist_ = true;
        ++(*(it->second))->count_;
    }
    // get last option
    shortKey.resize(1);
    shortKey += options[options.size() - 1];
    it = argumentFromName_.find(shortKey);
    if (it == argumentFromName_.end()) {
        const char optChar[2] = {options[options.size() - 1], '\0'};
        throw ParseArgumentException(optChar, "invalid option");
    }
    const char lastOptChar[2] = {options[options.size() - 1], '\0'};
    parseArgument_(maxIndex, argv, index, hasArg, lastOptChar, arg.c_str(), *(it->second));
}

void Args::parseLongArgument_(int maxIndex, char* argv[], int* index) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::const_iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    it = argumentFromName_.find(option);
    if (it == argumentFromName_.end()) {
        if (isAbbreviate_) {
            it = findAbbreviatedOption_(option);
        }
        if (it == argumentFromName_.end()) {
            throw ParseArgumentException(option.c_str() + ARGS_PREFIX_SIZEOF_LONG_OPTION_, "invalid option");
        }
    }
    parseArgument_(maxIndex, argv, index, hasArg, it->first.c_str() + ARGS_PREFIX_SIZEOF_LONG_OPTION_, arg.c_str(),
                   *(it->second));
}

void Args::parseArgument_(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                          Argument* argument) {
    if (hasArg) {
        switch (argument->type_) {
            case Argument::SIMPLE_OPTION: {
                argument->argument_ = arg;
                break;
            }
            case Argument::NUMBER_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                throw ParseArgumentException(option, "option cannot use with only 1 argument");
                break;
            }
            case Argument::INFINITE_OPTION: {
                argument->clear();
                argument->push_back(arg);
                break;
            }
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION: {
                if (argument->isExist_ == false) {
                    argument->clear();
                }
                argument->push_back(arg);
                break;
            }
            default: {
                throw ParseArgumentException(option, "option cannot use with argument");
                break;
            }
        }
    }
    else {
        switch (argument->type_) {
            case Argument::SIMPLE_OPTION:
                if (*index + 1 >= maxIndex) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ++(*index);
                argument->argument_ = argv[*index];
                break;
            case Argument::NUMBER_OPTION:
                argument->clear();
                if (*index + argument->nargs_ >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                for (unsigned int i = *index + 1; i <= (*index + argument->nargs_); ++i) {
                    argument->push_back(argv[i]);
                }
                *index += argument->nargs_;
                break;
            case Argument::INFINITE_OPTION: {
                argument->clear();
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; ++i) {
                    if (endOfInfiniteArgument_(argv[i])) {
                        break;
                    }
                    argument->push_back(argv[i]);
                    ++countArg;
                }
                *index += countArg;
                break;
            }
            case Argument::MULTI_OPTION: {
                if (argument->isExist_ == false) {
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
                if (argument->isExist_ == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; ++i) {
                    if (endOfInfiniteArgument_(argv[i])) {
                        break;
                    }
                    argument->push_back(argv[i]);
                    ++countArg;
                }
                *index += countArg;
                break;
            }
            case Argument::MULTI_NUMBER_OPTION: {
                if (argument->isExist_ == false) {
                    argument->clear();
                }
                if (*index + argument->nargs_ >= static_cast<unsigned int>(maxIndex)) {
                    throw ParseArgumentException(option, "bad number of argument");
                }
                ArgumentElement newNumberArgument;
                for (unsigned int i = *index + 1; i <= *index + argument->nargs_; ++i) {
                    newNumberArgument.push_back(argv[i]);
                }
                argument->push_back(newNumberArgument);
                *index += argument->nargs_;
                break;
            }
            case Argument::MULTI_NUMBER_INFINITE_OPTION: {
                if (argument->isExist_ == false) {
                    argument->clear();
                }
                std::size_t countArg = 0;
                for (int i = *index + 1; i < maxIndex; i += argument->nargs_) {
                    if (endOfInfiniteArgument_(argv[i])) {
                        break;
                    }
                    if (i + argument->nargs_ > static_cast<unsigned int>(maxIndex)) {
                        throw ParseArgumentException(option, "bad number of argument");
                    }
                    ArgumentElement newNumberArgument;
                    for (unsigned int j = i; j < i + argument->nargs_; ++j) {
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
    argument->isExist_ = true;
    ++argument->count_;
}

bool Args::endOfInfiniteArgument_(const char* argument) {
    std::string option;
    std::string arg;
    std::map<std::string, Argument**>::iterator it;
    if (isShortOption(argument)) {
        bool hasArg = takeArg(argument, &option, &arg);
        if (isAlternative_) {
            std::string altOption("-");
            altOption += option;
            it = argumentFromName_.find(altOption);
            if (it != argumentFromName_.end()) {
                return true;
            }
        }
        // Pre-allocate short option key buffer: "-X"
        std::string shortKey("-");
        shortKey.reserve(2);
        // get firsts option
        for (std::size_t i = 1; i < option.size() - 1; ++i) {
            shortKey.resize(1);
            shortKey += option[i];
            it = argumentFromName_.find(shortKey);
            if (it == argumentFromName_.end()) {
                return false;
            }
            else if (!hasArg && ((*(it->second))->type_ == Argument::SIMPLE_OPTION ||
                                 (*(it->second))->type_ == Argument::NUMBER_OPTION ||
                                 (*(it->second))->type_ == Argument::INFINITE_OPTION ||
                                 (*(it->second))->type_ == Argument::MULTI_OPTION ||
                                 (*(it->second))->type_ == Argument::MULTI_INFINITE_OPTION ||
                                 (*(it->second))->type_ == Argument::MULTI_NUMBER_OPTION)) {
                return true;
            }
            else if ((*(it->second))->type_ == Argument::BOOLEAN_OPTION ||
                     (*(it->second))->type_ == Argument::REVERSE_BOOLEAN_OPTION) {
                return true;
            }
        }
        // get last option
        shortKey.resize(1);
        shortKey += option[option.size() - 1];
        it = argumentFromName_.find(shortKey);
    }
    else if (isLongOption(argument)) {
        takeArg(argument, &option, &arg);
        it = argumentFromName_.find(option);
        if (it == argumentFromName_.end() && isAbbreviate_) {
            // Try abbreviated match (without throwing on ambiguity for end detection)
            std::size_t matchCount = 0;
            for (std::map<std::string, Argument**>::iterator searchIt = argumentFromName_.begin();
                 searchIt != argumentFromName_.end(); ++searchIt) {
                const std::string& key = searchIt->first;
                if (key.size() > 2 && key[0] == '-' && key[1] == '-') {
                    if (key.size() >= option.size() && key.compare(0, option.size(), option) == 0) {
                        it = searchIt;
                        ++matchCount;
                    }
                }
            }
            if (matchCount != 1) {
                it = argumentFromName_.end();
            }
        }
    }
    else {
        return false;
    }
    return it != argumentFromName_.end();
}

void Args::parsePositionnalArgument_(int argc, char* argv[], int* index, bool hasEndOption) {
    // find not exists positionnal argument
    std::list<Argument*>::iterator it;
    for (it = arguments_.begin(); it != arguments_.end(); ++it) {
        if ((*it)->isExist_ == false && (*it)->isPositionnalArgument_()) {
            break;
        }
    }
    if (it != arguments_.end()) {
        Argument& argument = *(*it);
        if (argument.type_ == Argument::POSITIONAL_ARGUMENT) {
            argument.argument_ = argv[*index];
        }
        else if (argument.type_ == Argument::NUMBER_POSITIONAL_ARGUMENT) {
            if (*index + argument.nargs_ > static_cast<unsigned int>(argc)) {
                throw ParseArgumentException(argument.nameOrFlags_.front().c_str(), "bad number of argument");
            }
            for (unsigned int i = *index; i < (*index + argument.nargs_); ++i) {
                argument.push_back(argv[i]);
            }
            *index += argument.nargs_ - 1;
        }
        else if (argument.type_ == Argument::INFINITE_POSITIONAL_ARGUMENT) {
            std::size_t countArg = 0;
            for (int i = *index; i < argc; ++i) {
                if (!hasEndOption && endOfInfiniteArgument_(argv[i])) {
                    break;
                }
                (*it)->push_back(argv[i]);
                ++countArg;
            }
            *index += countArg - 1;
        }
        else if (argument.type_ == Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT) {
            std::size_t countArg = 0;
            for (int i = *index; i < argc; i += argument.nargs_) {
                if (!hasEndOption && endOfInfiniteArgument_(argv[i])) {
                    break;
                }
                if (i + argument.nargs_ > static_cast<unsigned int>(argc)) {
                    throw ParseArgumentException(argument.nameOrFlags_.front().c_str(), "bad number of argument");
                }
                ArgumentElement newNumberArgument;
                for (unsigned int j = i; j < i + argument.nargs_; ++j) {
                    newNumberArgument.push_back(argv[j]);
                    ++countArg;
                }
                argument.push_back(newNumberArgument);
            }
            *index += countArg - 1;
        }
        argument.isExist_ = true;
    }
    else {
        if (isStrict_) {
            throw ParseArgumentException(argv[*index], "invalid additional argument");
        }
        else {
            additionalArguments_.push_back(argv[*index]);
        }
    }
}

std::map<std::string, Argument**>::const_iterator Args::findAbbreviatedOption_(const std::string& option) const {
    std::map<std::string, Argument**>::const_iterator found = argumentFromName_.end();
    std::size_t matchCount = 0;

    // First pass: count matches and find the last one
    for (std::map<std::string, Argument**>::const_iterator it = argumentFromName_.begin();
         it != argumentFromName_.end(); ++it) {
        const std::string& key = it->first;
        // Only match long options (starting with --)
        if (key.size() > 2 && key[0] == '-' && key[1] == '-') {
            // Check if option is a prefix of this key
            if (key.size() >= option.size() && key.compare(0, option.size(), option) == 0) {
                found = it;
                ++matchCount;
            }
        }
    }

    // Only build error message if ambiguous
    if (matchCount > 1) {
        std::string ambiguousOptions;
        for (std::map<std::string, Argument**>::const_iterator it = argumentFromName_.begin();
             it != argumentFromName_.end(); ++it) {
            const std::string& key = it->first;
            if (key.size() > 2 && key[0] == '-' && key[1] == '-') {
                if (key.size() >= option.size() && key.compare(0, option.size(), option) == 0) {
                    if (!ambiguousOptions.empty()) {
                        ambiguousOptions += ", ";
                    }
                    ambiguousOptions += key;
                }
            }
        }
        throw ParseArgumentException((option.c_str() + ARGS_PREFIX_SIZEOF_LONG_OPTION_),
                                     ("ambiguous option, could be: " + ambiguousOptions).c_str());
    }

    return found;
}

} // namespace args

} // namespace blet

#undef ARGS_PREFIX_SIZEOF_SHORT_OPTION_
#undef ARGS_PREFIX_SIZEOF_LONG_OPTION_
