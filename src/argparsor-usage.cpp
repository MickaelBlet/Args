#include <sstream>

#include "mblet/argparsor/argparsor.h"
#include "mblet/argparsor/argument.h"
#include "mblet/argparsor/usage.h"

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#define _ARGPARSOR_SEPARATOR_PATH '\\'
#else
#define _ARGPARSOR_SEPARATOR_PATH '/'
#endif

namespace mblet {

namespace argparsor {

Usage::Usage(Argparsor& argparsor) :
    _argparsor(argparsor),
    _description(std::string()),
    _epilog(std::string()),
    _usage(std::string()),
    _usagePadWidth(2),
    _usageArgsWidth(20),
    _usageSepWidth(2),
    _usageHelpWidth(56) {}

Usage::~Usage() {}

std::vector<std::string> static inline s_multilineWrap(const std::string& str, std::size_t widthMax) {
    std::vector<std::string> lines;
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
    if (!_usage.empty()) {
        return _usage;
    }
    std::ostringstream oss("");
    bool hasOption = false;
    bool hasPositionnal = false;
    bool hasMultiLine = false;
    // get basename of binaryName
    std::string binaryName;
    std::size_t lastDirCharacterPos = _argparsor._binaryName.rfind(_ARGPARSOR_SEPARATOR_PATH);
    if (lastDirCharacterPos != std::string::npos) {
        binaryName = _argparsor._binaryName.substr(lastDirCharacterPos + 1);
    }
    else {
        binaryName = _argparsor._binaryName;
    }
    // usage line
    std::string usageLine = std::string("usage: ") + binaryName;
    oss << usageLine;
    std::size_t binaryPad = usageLine.size();
    std::size_t index = binaryPad;
    std::size_t indexMax = _usagePadWidth + _usageArgsWidth + _usageSepWidth + _usageHelpWidth;
    std::list<Argument*>::const_iterator it;
    for (it = _argparsor._arguments.begin(); it != _argparsor._arguments.end(); ++it) {
        if ((*it)->_isPositionnalArgument()) {
            hasPositionnal = true;
            continue;
        }
        hasOption = true;
        std::ostringstream ossArgument("");
        if (!(*it)->_isRequired) {
            ossArgument << '[';
        }
        ossArgument << (*it)->_nameOrFlags.front();
        switch ((*it)->_type) {
            case Argument::SIMPLE_OPTION:
            case Argument::NUMBER_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                if ((*it)->_metavar.empty()) {
                    ossArgument << ' ' << (*it)->_metavarDefault();
                }
                else {
                    ossArgument << ' ' << (*it)->_metavar;
                }
                break;
            default:
                break;
        }
        if (!(*it)->_isRequired) {
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
    for (it = _argparsor._arguments.begin(); it != _argparsor._arguments.end(); ++it) {
        if (!(*it)->_isPositionnalArgument()) {
            continue;
        }
        std::ostringstream ossArgument("");
        if (!(*it)->_isRequired) {
            ossArgument << '[';
        }
        if ((*it)->_type == Argument::POSITIONAL_ARGUMENT) {
            ossArgument << (*it)->_nameOrFlags.front();
        }
        else if ((*it)->_type == Argument::NUMBER_POSITIONAL_ARGUMENT) {
            for (std::size_t i = 0; i < (*it)->_nargs; ++i) {
                if (i != 0) {
                    ossArgument << ' ';
                }
                ossArgument << (*it)->_nameOrFlags.front();
            }
        }
        else if ((*it)->_type == Argument::INFINITE_POSITIONAL_ARGUMENT) {
            ossArgument << (*it)->_nameOrFlags.front() << " {" << (*it)->_nameOrFlags.front() << "}...";
        }
        else if ((*it)->_type == Argument::INFINITE_NUMBER_POSITIONAL_ARGUMENT) {
            ossArgument << "{";
            for (std::size_t i = 0; i < (*it)->_nargs; ++i) {
                if (i != 0) {
                    ossArgument << ' ';
                }
                ossArgument << (*it)->_nameOrFlags.front();
            }
            ossArgument << "}...";
        }
        if (!(*it)->_isRequired) {
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
    if (!_description.empty()) {
        oss << '\n';
        std::vector<std::string> lines = s_multilineWrap(_description, indexMax);
        for (std::size_t i = 0; i < lines.size(); ++i) {
            oss << '\n';
            oss << lines[i];
        }
    }
    // optionnal
    if (!_argparsor._arguments.empty()) {
        if (hasPositionnal) {
            index = 0;
            oss << "\n\npositional arguments:\n";
            for (it = _argparsor._arguments.begin(); it != _argparsor._arguments.end(); ++it) {
                if (!(*it)->_isPositionnalArgument()) {
                    continue;
                }
                if (index != 0) {
                    oss << '\n';
                }
                ++index;
                oss << std::string(_usagePadWidth, ' ');
                if ((*it)->_nameOrFlags.front().size() + _usageSepWidth <= _usageArgsWidth + _usageSepWidth) {
                    oss.width(_usageArgsWidth + _usageSepWidth);
                    oss.flags(std::ios::left);
                    oss << (*it)->_nameOrFlags.front();
                    oss.width(0);
                }
                else {
                    oss << (*it)->_nameOrFlags.front();
                    oss << '\n';
                    oss << std::string(_usagePadWidth + _usageArgsWidth + _usageSepWidth, ' ');
                }
                std::ostringstream ossHelp("");
                ossHelp << (*it)->_help;
                if ((*it)->_isRequired) {
                    ossHelp << " (required)";
                }
                else {
                    if (!(*it)->_default.empty()) {
                        ossHelp << " (default: " + (*it)->_default + ")";
                    }
                }
                std::vector<std::string> lines = s_multilineWrap(ossHelp.str(), _usageHelpWidth);
                for (std::size_t i = 0; i < lines.size(); ++i) {
                    if (i != 0) {
                        oss << '\n';
                        oss << std::string(_usagePadWidth + _usageArgsWidth + _usageSepWidth, ' ');
                    }
                    oss << lines[i];
                }
            }
        }
        if (hasOption) {
            index = 0;
            oss << "\n\noptional arguments:\n";
            for (it = _argparsor._arguments.begin(); it != _argparsor._arguments.end(); ++it) {
                if ((*it)->_isPositionnalArgument()) {
                    continue;
                }
                if (index != 0) {
                    oss << '\n';
                }
                ++index;
                std::ostringstream ossArgument("");
                for (std::size_t i = 0; i < (*it)->_nameOrFlags.size(); ++i) {
                    if (i != 0) {
                        ossArgument << ", ";
                    }
                    ossArgument << (*it)->_nameOrFlags[i];
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
                            ossArgument << ' ';
                            ossArgument << (*it)->_metavarDefault();
                        }
                        else {
                            ossArgument << ' ';
                            ossArgument << (*it)->_metavar;
                        }
                        break;
                    default:
                        break;
                }
                const std::string option = ossArgument.str();
                oss << std::string(_usagePadWidth, ' ');
                if (option.size() + _usageSepWidth <= _usageArgsWidth + _usageSepWidth) {
                    oss.width(_usageArgsWidth + _usageSepWidth);
                    oss.flags(std::ios::left);
                    oss << option;
                    oss.width(0);
                }
                else {
                    oss << option;
                    oss << '\n';
                    oss << std::string(_usagePadWidth + _usageArgsWidth + _usageSepWidth, ' ');
                }
                std::ostringstream ossHelp("");
                ossHelp << (*it)->_help;
                if ((*it)->_isRequired) {
                    ossHelp << " (required)";
                }
                else {
                    if (!(*it)->_default.empty()) {
                        ossHelp << " (default: " + (*it)->_default + ")";
                    }
                }
                std::vector<std::string> lines = s_multilineWrap(ossHelp.str(), _usageHelpWidth);
                for (std::size_t i = 0; i < lines.size(); ++i) {
                    if (i != 0) {
                        oss << '\n';
                        oss << std::string(_usagePadWidth + _usageArgsWidth + _usageSepWidth, ' ');
                    }
                    oss << lines[i];
                }
            }
        }
    }
    // epilog
    if (!_epilog.empty()) {
        oss << '\n';
        std::vector<std::string> lines = s_multilineWrap(_epilog, indexMax);
        for (std::size_t i = 0; i < lines.size(); ++i) {
            oss << '\n';
            oss << lines[i];
        }
    }
    return oss.str();
}

} // namespace argparsor

} // namespace mblet

#undef _ARGPARSOR_SEPARATOR_PATH