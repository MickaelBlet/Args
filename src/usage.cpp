/**
 * usage.cpp
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

#include "blet/args/usage.h"

#include <sstream>

#include "blet/args/args.h"
#include "blet/args/argument.h"

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#define ARGS_SEPARATOR_PATH_ '\\'
#else
#define ARGS_SEPARATOR_PATH_ '/'
#endif

namespace blet {

namespace args {

Usage::Usage(Args& args) :
    args_(args),
    description_(std::string()),
    epilog_(std::string()),
    usage_(std::string()),
    usagePadWidth_(2),
    usageArgsWidth_(20),
    usageSepWidth_(2),
    usageHelpWidth_(56) {}

Usage::~Usage() {}

static inline std::list<std::string> s_multilineWrap(const std::string& str, std::size_t widthMax) {
    std::list<std::string> lines;
    std::string line;
    std::istringstream iss(str);
    while (std::getline(iss, line)) {
        while (line.size() >= widthMax) {
            std::size_t spacePos = line.rfind(' ', widthMax);
            if (spacePos != std::string::npos) {
                lines.push_back(line.substr(0, spacePos));
                while (spacePos < line.size() && line.at(spacePos) == ' ') {
                    ++spacePos;
                }
                line = line.substr(spacePos);
            }
            else {
                break;
            }
        }
        lines.push_back(line);
    }
    return lines;
}

std::string Usage::getUsage() const {
    if (!usage_.empty()) {
        return usage_;
    }
    std::ostringstream oss("");
    bool hasOption = false;
    bool hasPositionnal = false;
    bool hasMultiLine = false;
    // get basename of binaryName
    std::string binaryName;
    std::size_t lastDirCharacterPos = args_.binaryName_.rfind(ARGS_SEPARATOR_PATH_);
    if (lastDirCharacterPos != std::string::npos) {
        binaryName = args_.binaryName_.substr(lastDirCharacterPos + 1);
    }
    else {
        binaryName = args_.binaryName_;
    }
    // usage line
    std::string usageLine = std::string("usage: ") + binaryName;
    oss << usageLine;
    std::size_t binaryPad = usageLine.size();
    std::size_t index = binaryPad;
    std::size_t indexMax = usagePadWidth_ + usageArgsWidth_ + usageSepWidth_ + usageHelpWidth_;
    std::list<Argument*>::const_iterator it;
    for (it = args_.arguments_.begin(); it != args_.arguments_.end(); ++it) {
        if ((*it)->isPositionnalArgument_()) {
            hasPositionnal = true;
            continue;
        }
        hasOption = true;
        std::ostringstream ossArgument("");
        if (!(*it)->isRequired_) {
            ossArgument << '[';
        }
        ossArgument << (*it)->nameOrFlags_.front();
        switch ((*it)->type_) {
            case Argument::SIMPLE_OPTION:
            case Argument::NUMBER_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                if ((*it)->metavar_.empty()) {
                    ossArgument << ' ' << (*it)->metavarDefault_();
                }
                else {
                    ossArgument << ' ' << (*it)->metavar_;
                }
                break;
            default:
                break;
        }
        if (!(*it)->isRequired_) {
            ossArgument << ']';
        }
        std::string argument = ossArgument.str();
        if (index + argument.size() >= indexMax) {
            hasMultiLine = true;
            oss << '\n' << std::string(binaryPad + 1, ' ') << argument;
            index = binaryPad + argument.size() + 1;
        }
        else {
            oss << ' ' << argument;
            index += argument.size() + 1;
        }
    }
    if (hasOption && hasPositionnal) {
        if (hasMultiLine || index + 3 >= indexMax) {
            oss << '\n' << std::string(binaryPad + 1, ' ') << "--\n" << std::string(binaryPad, ' ');
            index = binaryPad;
        }
        else {
            oss << " --";
            index += 3;
        }
    }
    for (it = args_.arguments_.begin(); it != args_.arguments_.end(); ++it) {
        if (!(*it)->isPositionnalArgument_()) {
            continue;
        }
        std::ostringstream ossArgument("");
        if (!(*it)->isRequired_) {
            ossArgument << '[';
        }
        if ((*it)->type_ == Argument::POSITIONAL_ARGUMENT) {
            ossArgument << (*it)->nameOrFlags_.front();
        }
        else if ((*it)->type_ == Argument::NUMBER_POSITIONAL_ARGUMENT) {
            for (std::size_t i = 0; i < (*it)->nargs_; ++i) {
                if (i != 0) {
                    ossArgument << ' ';
                }
                ossArgument << (*it)->nameOrFlags_.front();
            }
        }
        else if ((*it)->type_ == Argument::INFINITE_POSITIONAL_ARGUMENT) {
            ossArgument << (*it)->nameOrFlags_.front() << " {" << (*it)->nameOrFlags_.front() << "}...";
        }
        else if ((*it)->type_ == Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT) {
            ossArgument << "{";
            for (std::size_t i = 0; i < (*it)->nargs_; ++i) {
                if (i != 0) {
                    ossArgument << ' ';
                }
                ossArgument << (*it)->nameOrFlags_.front();
            }
            ossArgument << "}...";
        }
        if (!(*it)->isRequired_) {
            ossArgument << ']';
        }
        std::string argument = ossArgument.str();
        if (index + argument.size() >= indexMax) {
            hasMultiLine = true;
            oss << '\n' << std::string(binaryPad + 1, ' ') << argument;
            index = binaryPad + argument.size() + 1;
        }
        else {
            oss << ' ' << argument;
            index += argument.size() + 1;
        }
    }
    // description
    if (!description_.empty()) {
        oss << '\n';
        std::list<std::string> lines = s_multilineWrap(description_, indexMax);
        for (std::list<std::string>::const_iterator cit = lines.begin(); cit != lines.end(); ++cit) {
            oss << '\n';
            oss << *cit;
        }
    }
    // optionnal
    if (!args_.arguments_.empty()) {
        if (hasPositionnal) {
            index = 0;
            oss << "\n\npositional arguments:\n";
            for (it = args_.arguments_.begin(); it != args_.arguments_.end(); ++it) {
                if (!(*it)->isPositionnalArgument_()) {
                    continue;
                }
                if (index != 0) {
                    oss << '\n';
                }
                ++index;
                oss << std::string(usagePadWidth_, ' ');
                if ((*it)->nameOrFlags_.front().size() + usageSepWidth_ <= usageArgsWidth_ + usageSepWidth_) {
                    oss.width(usageArgsWidth_ + usageSepWidth_);
                    oss.flags(std::ios::left);
                    oss << (*it)->nameOrFlags_.front();
                    oss.width(0);
                }
                else {
                    oss << (*it)->nameOrFlags_.front();
                    oss << '\n';
                    oss << std::string(usagePadWidth_ + usageArgsWidth_ + usageSepWidth_, ' ');
                }
                std::ostringstream ossHelp("");
                ossHelp << (*it)->help_;
                if ((*it)->isRequired_) {
                    ossHelp << " (required)";
                }
                else {
                    if (!(*it)->default_.empty()) {
                        ossHelp << " (default: " + (*it)->default_ + ")";
                    }
                }
                std::list<std::string> lines = s_multilineWrap(ossHelp.str(), usageHelpWidth_);
                for (std::list<std::string>::const_iterator cit = lines.begin(); cit != lines.end(); ++cit) {
                    if (cit != lines.begin()) {
                        oss << '\n';
                        oss << std::string(usagePadWidth_ + usageArgsWidth_ + usageSepWidth_, ' ');
                    }
                    oss << *cit;
                }
            }
        }
        if (hasOption) {
            index = 0;
            oss << "\n\noptional arguments:\n";
            for (it = args_.arguments_.begin(); it != args_.arguments_.end(); ++it) {
                if ((*it)->isPositionnalArgument_()) {
                    continue;
                }
                if (index != 0) {
                    oss << '\n';
                }
                ++index;
                std::ostringstream ossArgument("");
                for (std::size_t i = 0; i < (*it)->nameOrFlags_.size(); ++i) {
                    if (i != 0) {
                        ossArgument << ", ";
                    }
                    ossArgument << (*it)->nameOrFlags_[i];
                }
                switch ((*it)->type_) {
                    case Argument::SIMPLE_OPTION:
                    case Argument::NUMBER_OPTION:
                    case Argument::INFINITE_OPTION:
                    case Argument::MULTI_OPTION:
                    case Argument::MULTI_INFINITE_OPTION:
                    case Argument::MULTI_NUMBER_OPTION:
                    case Argument::MULTI_NUMBER_INFINITE_OPTION:
                        if ((*it)->metavar_.empty()) {
                            ossArgument << ' ';
                            ossArgument << (*it)->metavarDefault_();
                        }
                        else {
                            ossArgument << ' ';
                            ossArgument << (*it)->metavar_;
                        }
                        break;
                    default:
                        break;
                }
                const std::string option = ossArgument.str();
                oss << std::string(usagePadWidth_, ' ');
                if (option.size() + usageSepWidth_ <= usageArgsWidth_ + usageSepWidth_) {
                    oss.width(usageArgsWidth_ + usageSepWidth_);
                    oss.flags(std::ios::left);
                    oss << option;
                    oss.width(0);
                }
                else {
                    oss << option;
                    oss << '\n';
                    oss << std::string(usagePadWidth_ + usageArgsWidth_ + usageSepWidth_, ' ');
                }
                std::ostringstream ossHelp("");
                ossHelp << (*it)->help_;
                if ((*it)->isRequired_) {
                    ossHelp << " (required)";
                }
                else {
                    if (!(*it)->default_.empty()) {
                        ossHelp << " (default: " + (*it)->default_ + ")";
                    }
                }
                std::list<std::string> lines = s_multilineWrap(ossHelp.str(), usageHelpWidth_);
                for (std::list<std::string>::const_iterator cit = lines.begin(); cit != lines.end(); ++cit) {
                    if (cit != lines.begin()) {
                        oss << '\n';
                        oss << std::string(usagePadWidth_ + usageArgsWidth_ + usageSepWidth_, ' ');
                    }
                    oss << *cit;
                }
            }
        }
    }
    // epilog
    if (!epilog_.empty()) {
        oss << '\n';
        std::list<std::string> lines = s_multilineWrap(epilog_, indexMax);
        for (std::list<std::string>::const_iterator cit = lines.begin(); cit != lines.end(); ++cit) {
            oss << '\n';
            oss << *cit;
        }
    }
    return oss.str();
}

} // namespace args

} // namespace blet

#undef ARGS_SEPARATOR_PATH_
