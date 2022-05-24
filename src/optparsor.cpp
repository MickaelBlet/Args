#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

#include "optparsor.h"

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

Optparsor::Optparsor() : _throwAtExtra(true) {
    setHelpOption("-h", "--help", "show this help message and exit");
}

Optparsor::~Optparsor() {}

Optparsor::Option::Option() :
    type(Option::BOOLEAN_OPTION),
    isExist(false),
    count(0),
    isRequired(false),
    shortName(std::string()),
    longName(std::string()),
    help(std::string()),
    nbArgs(0),
    argHelp(std::string()),
    defaultValues(std::vector<std::string>()),
    arguments(std::vector<Argument>()) {}

Optparsor::Option::~Option() {}

Optparsor::Option::Argument::Argument() : std::string() {}
Optparsor::Option::Argument::~Argument() {}

Optparsor::Option::Argument::Argument(const Argument& rhs) : std::string(rhs) {}
Optparsor::Option::Argument::Argument(const std::string& rhs) : std::string(rhs) {}
Optparsor::Option::Argument::Argument(const char* const& rhs) : std::string(rhs) {}

void Optparsor::Option::Argument::valueToStream(std::ostream& stringStream) const {
    std::size_t index = 0;

    if (c_str()[index] == '-' || c_str()[index] == '+') {
        ++index;
    }
    // is hex
    if (c_str()[index] == '0' && c_str()[index + 1] == 'x') {
        stringStream << strtoll(c_str(), NULL, 16);
    }
    // is binary
    else if (c_str()[index] == '0' && c_str()[index + 1] == 'b') {
        stringStream << strtoull(c_str() + index + 2, NULL, 2);
    }
    // is octal
    else if (c_str()[index] == '0' && find('.') == std::string::npos) {
        stringStream << strtoll(c_str(), NULL, 8);
    }
    // is bool
    else if (*this == "TRUE" || *this == "True" || *this == "true" ||
             *this == "ON"   || *this == "On"   || *this == "on"   ||
             *this == "YES"  || *this == "Yes"  || *this == "yes") {
        stringStream << true;
    }
    else if (*this == "FALSE" || *this == "False" || *this == "false" ||
             *this == "OFF"   || *this == "Off"   || *this == "off"   ||
             *this == "NO"    || *this == "No"    || *this == "no") {
        stringStream << false;
    }
    else {
        stringStream << *this;
    }
}

static bool compareOption(const Optparsor::Option& first, const Optparsor::Option& second) {
    if (first.type == Optparsor::Option::POSITIONAL_ARGUMENT) {
        return false;
    }
    if (!first.shortName.empty() && !second.shortName.empty()) {
        return first.shortName <= second.shortName;
    }
    else if (!first.shortName.empty() && second.shortName.empty()) {
        return true;
    }
    else if (first.shortName.empty() && !second.shortName.empty()) {
        return false;
    }
    else if (!first.longName.empty() && !second.longName.empty()) {
        if (first.longName[0] == '-' && second.longName[0] == '-') {
            return first.longName <= second.longName;
        }
        else if (first.longName[0] == '-' && second.longName[0] != '-') {
            return true;
        }
        else if (first.longName[0] != '-' && second.longName[0] == '-') {
            return false;
        }
        else {
            return first.longName <= second.longName;
        }
    }
    else if (!first.longName.empty() && second.longName.empty()) {
        return false;
    }
    else {
        return true;
    }
}

std::ostream& Optparsor::getUsage(std::ostream& oss) {
    _options.sort(&compareOption);
    if (!_usage.empty()) {
        oss << _usage;
        return oss;
    }
    // usage line
    oss << "usage: " << _binaryName;
    std::list<Option>::const_iterator it;
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        if (it->type == Option::POSITIONAL_ARGUMENT) {
            continue;
        }
        oss << " [";
        if (!it->shortName.empty()) {
            if (!it->argHelp.empty()) {
                oss << it->shortName << ' ' << it->argHelp;
            }
            else {
                oss << it->shortName;
            }
        }
        else {
            if (!it->argHelp.empty()) {
                oss << it->longName << ' ' << it->argHelp;
            }
            else {
                oss << it->longName;
            }
        }
        oss << ']';
    }
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        if (it->type != Option::POSITIONAL_ARGUMENT) {
            continue;
        }
        oss << " " << it->longName;
    }
    oss << "\n";
    // description
    if (!_description.empty()) {
        oss << "\n" << _description << "\n";
    }
    // optionnal
    if (!_options.empty()) {
        std::list<std::pair<std::string, std::string> > positionals;
        std::list<std::pair<std::string, std::string> > optionnals;
        for (it = _options.begin() ; it != _options.end() ; ++it) {
            std::list<std::pair<std::string, std::string> > *listOption = NULL;
            if (it->type == Option::POSITIONAL_ARGUMENT) {
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
            if (!it->shortName.empty() && !it->longName.empty()) {
                optionStr += it->shortName + ", " + it->longName;
            }
            else if (!it->shortName.empty()) {
                optionStr += it->shortName;
            }
            else if (!it->longName.empty()) {
                optionStr += it->longName;
            }
            if (!it->argHelp.empty()) {
                optionStr += " " + it->argHelp;
            }
            helpStr += "  " + it->help;
            if (it->isRequired) {
                helpStr += " (required)";
            }
            else if (it->defaultValues.size() > 0) {
                helpStr += " (default:";
                for (std::size_t i = 0 ; i < it->defaultValues.size() ; ++i) {
                    helpStr += " " + it->defaultValues[i];
                }
                helpStr += ")";
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
    return oss;
}

void Optparsor::setHelpOption(const char* shortName, const char* longName, const char* help) {
    if (_helpOption != NULL) {
        for (std::list<Option>::iterator itList = _options.begin() ; itList != _options.end() ; ++itList) {
            if (_helpOption == itList.operator->()) {
                _options.erase(itList);
                break;
            }
        }
        std::map<std::string, Option*>::iterator itMap = _optionFromName.begin();
        while (itMap != _optionFromName.end()) {
            if (_helpOption == itMap->second) {
                _optionFromName.erase(itMap);
                itMap = _optionFromName.begin();
            }
            else {
                ++itMap;
            }
        }
    }
    // disable help
    if ((shortName == NULL || shortName[0] == '\0') &&
        (longName  == NULL || longName[0]  == '\0')) {
        _helpOption = NULL;
        return;
    }
    _helpOption = &createOption(shortName, longName, help, false);
}

void Optparsor::parseArguments(int argc, char* argv[]) {
    _binaryName = argv[0];
    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    // foreach argument
    for (int i = 1 ; i < argc ; ++i) {
        if (isShortOption(argv[i])) {
            getShortOption(endIndex, argv, &i);
        }
        else if (isLongOption(argv[i])) {
            getLongOption(endIndex, argv, &i);
        }
        else if (isEndOption(argv[i])) {
            ++i;
            while (i < argc) {
                getPositionnalArgument(argc, argv, &i);
                ++i;
            }
            break;
        }
        else {
            getPositionnalArgument(argc, argv, &i);
        }
    }
    // check help option
    if (_helpOption != NULL && _helpOption->isExist) {
        getUsage();
        exit(1);
    }
    // check require option
    std::list<Option>::iterator it;
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        if (it->isRequired && it->isExist == false) {
            if (!it->longName.empty()) {
                if (it->type == Option::POSITIONAL_ARGUMENT) {
                    throw ParseArgumentRequiredException(it->longName.c_str(), "argument is required");
                }
                else {
                    throw ParseArgumentRequiredException(it->longName.c_str(), "option is required");
                }
            }
            else {
                throw ParseArgumentRequiredException(it->shortName.c_str(), "option is required");
            }
        }
    }
}

void Optparsor::addBooleanOption(const char* shortName, const char* longName, const char* help, bool isRequired) {
    Option& option = createOption(shortName, longName, help, isRequired);
    option.nbArgs = 0;
    option.type = Option::BOOLEAN_OPTION;
}

void Optparsor::addSimpleOption(const char* shortName, const char* longName, const char* help, bool isRequired,
                                const char* argHelp, const char* defaultValue) {
    Option& option = createOption(shortName, longName, help, isRequired);
    // check argHelps
    std::string defaultUsageName;
    if (argHelp == NULL || argHelp[0] == '\0') {
        // create a defaultUsageName from longName or shortName
        if (longName != NULL && longName[0] != '\0') {
            defaultUsageName = longName + PREFIX_SIZEOF_LONG_OPTION;
        }
        else {
            defaultUsageName = shortName + PREFIX_SIZEOF_SHORT_OPTION;
        }
        for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
            defaultUsageName[i] = ::toupper(defaultUsageName[i]);
        }
        argHelp = defaultUsageName.c_str();
    }
    option.type = Option::SIMPLE_OPTION;
    option.nbArgs = 1;
    option.argHelp = argHelp;
    if (isRequired == false && defaultValue != NULL) {
        option.arguments.push_back(defaultValue);
        option.defaultValues.push_back(defaultValue);
    }
}

void Optparsor::addNumberOption(const char* shortName, const char* longName, const char* help, bool isRequired,
                                const char* argHelp, std::size_t nbArgs, ...) {
    Option& option = createOption(shortName, longName, help, isRequired);
    // check argHelps
    std::string defaultUsageName;
    if (argHelp == NULL || argHelp[0] == '\0') {
        // create a defaultUsageName from longName or shortName
        if (longName != NULL && longName[0] != '\0') {
            defaultUsageName = longName + PREFIX_SIZEOF_LONG_OPTION;
        }
        else {
            defaultUsageName = shortName + PREFIX_SIZEOF_SHORT_OPTION;
        }
        for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
            defaultUsageName[i] = ::toupper(defaultUsageName[i]);
        }
        std::string numberDefaultUsageName;
        for (std::size_t i = 0 ; i < nbArgs ; ++i) {
            if (i > 0) {
                numberDefaultUsageName += " ";
            }
            numberDefaultUsageName += defaultUsageName;
        }
        defaultUsageName = numberDefaultUsageName;
        argHelp = defaultUsageName.c_str();
    }
    option.type = Option::NUMBER_OPTION;
    option.nbArgs = nbArgs;
    if (nbArgs > 0) {
        option.argHelp = argHelp;
    }
    if (isRequired == false && nbArgs > 0) {
        va_list pa;
        va_start(pa, nbArgs);
        for (std::size_t i = 0 ; i < nbArgs ; ++i) {
            const char* defaultValue = (const char*)va_arg(pa, const char*);
            option.defaultValues.push_back(defaultValue);
            option.arguments.push_back(defaultValue);
        }
        va_end(pa);
    }
}

void Optparsor::addInfiniteOption(const char* shortName, const char* longName, const char* help, bool isRequired,
                                  const char* argHelp, std::size_t nbDefaultArgs, ...) {
    Option& option = createOption(shortName, longName, help, isRequired);
    option.nbArgs = 0;
    option.type = Option::INFINITE_OPTION;
    // check argHelps
    std::string defaultUsageName;
    if (argHelp == NULL || argHelp[0] == '\0') {
        // create a defaultUsageName from longName or shortName
        if (longName != NULL && longName[0] != '\0') {
            defaultUsageName = longName + PREFIX_SIZEOF_LONG_OPTION;
        }
        else {
            defaultUsageName = shortName + PREFIX_SIZEOF_SHORT_OPTION;
        }
        for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
            defaultUsageName[i] = ::toupper(defaultUsageName[i]);
        }
        defaultUsageName += "...";
        argHelp = defaultUsageName.c_str();
    }
    option.argHelp = argHelp;
    if (isRequired == false && nbDefaultArgs > 0) {
        va_list pa;
        va_start(pa, nbDefaultArgs);
        for (std::size_t i = 0 ; i < nbDefaultArgs ; ++i) {
            const char* defaultValue = (const char*)va_arg(pa, const char*);
            option.defaultValues.push_back(defaultValue);
            option.arguments.push_back(defaultValue);
        }
        va_end(pa);
    }
}

void Optparsor::addMultiOption(const char* shortName, const char* longName, const char* help, bool isRequired,
                               const char* argHelp, std::size_t nbDefaultArgs, ...) {
    Option& option = createOption(shortName, longName, help, isRequired);
    option.type = Option::MULTI_OPTION;
    option.nbArgs = 1;
    // check argHelps
    std::string defaultUsageName;
    if (argHelp == NULL || argHelp[0] == '\0') {
        // create a defaultUsageName from longName or shortName
        if (longName != NULL && longName[0] != '\0') {
            defaultUsageName = longName + PREFIX_SIZEOF_LONG_OPTION;
        }
        else {
            defaultUsageName = shortName + PREFIX_SIZEOF_SHORT_OPTION;
        }
        for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
            defaultUsageName[i] = ::toupper(defaultUsageName[i]);
        }
        argHelp = defaultUsageName.c_str();
    }
    option.argHelp = argHelp;
    if (isRequired == false && nbDefaultArgs > 0) {
        va_list pa;
        va_start(pa, nbDefaultArgs);
        for (std::size_t i = 0 ; i < nbDefaultArgs ; ++i) {
            const char* defaultValue = (const char*)va_arg(pa, const char*);
            option.defaultValues.push_back(defaultValue);
            option.arguments.push_back(defaultValue);
        }
        va_end(pa);
    }
}

void Optparsor::addPositionalArgument(const char* name, const char* help, bool isRequired, const char* defaultValue) {
    if (name == NULL || name[0] == '\0') {
        throw ArgumentException("", "bad name argument");
    }
    if (name != NULL && name[0] != '\0') {
        if (name[0] == '-') {
            throw ArgumentException(name, "bad name argument start by '-' character");
        }
        else if (_optionFromName.find(name) != _optionFromName.end()) {
            throw ArgumentException(name, "bad name argument already exist");
        }
    }
    // create option
    _options.push_back(Option());
    Option& option = _options.back();
    _optionFromName.insert(std::pair<std::string, Option*>(name, &option));

    option.isExist = false;
    option.isRequired = isRequired;
    option.longName = name;
    option.nbArgs = 1;
    option.type = Option::POSITIONAL_ARGUMENT;
    if (help != NULL) {
        option.help = help;
    }
    if (defaultValue != NULL) {
        option.arguments.push_back(defaultValue);
        option.defaultValues.push_back(defaultValue);
    }
}

/*
** private
*/

Optparsor::Option& Optparsor::createOption(const char* shortName, const char* longName, const char* help,
                                           bool isRequired) {
    if ((shortName == NULL || shortName[0] == '\0') && (longName == NULL || longName[0] == '\0')) {
        throw ArgumentException("", "invalid shortName and longName arguments");
    }
    if (shortName != NULL && shortName[0] != '\0') {
        if (shortName[0] != '-') {
            throw ArgumentException(shortName, "invalid shortName argument not start by '-' character");
        }
        else if (shortName[0] == '-' && shortName[1] == '\0') {
            throw ArgumentException(shortName, "invalid shortName argument is '-'");
        }
        else if (shortName[2] != '\0') {
            throw ArgumentException(shortName, "invalid shortName argument not only one character");
        }
        else if (_optionFromName.find(shortName) != _optionFromName.end()) {
            throw ArgumentException(shortName, "invalid shortName argument already exist");
        }
    }
    if (longName != NULL && longName[0] != '\0') {
        if (longName[0] != '-' || longName[1] != '-') {
            throw ArgumentException(longName, "invalid longName argument not start by '--' characters");
        }
        else if (longName[0] == '-' && longName[1] == '-' && longName[2] == '\0') {
            throw ArgumentException(longName, "invalid longName argument is '--'");
        }
        if (_optionFromName.find(longName) != _optionFromName.end()) {
            throw ArgumentException(longName, "invalid longName argument already exist");
        }
    }

    // create option
    _options.push_back(Option());
    Option& option = _options.back();
    if (shortName != NULL && shortName[0] != '\0') {
        _optionFromName.insert(std::pair<std::string, Option*>(shortName, &option));
        option.shortName = shortName;
    }
    else {
        option.shortName = "";
    }
    if (longName != NULL && longName[0] != '\0') {
        _optionFromName.insert(std::pair<std::string, Option*>(longName, &option));
        option.longName = longName;
    }
    else {
        option.longName = "";
    }
    if (help != NULL) {
        option.help = help;
    }
    option.isRequired = isRequired;
    option.isExist = false;
    return option;
}

void Optparsor::getShortOption(int maxIndex, char* argv[], int* index) {
    std::string options;
    std::string arg;
    std::map<std::string, Option*>::iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    // get firsts option
    for (std::size_t i = 1 ; i < options.size() - 1 ; ++i) {
        std::string charOption(options, i, 1);
        it = _optionFromName.find("-" + charOption);
        if (it == _optionFromName.end()) {
            throw ParseArgumentException(charOption.c_str(), "invalid option");
        }
        else if (it->second->nbArgs != 0) {
            throw ParseArgumentException(charOption.c_str(), "only last option can be use a parameter");
        }
        it->second->isExist = true;
        ++it->second->count;
    }
    // get last option
    std::string charOption(options, options.size() - 1, 1);
    it = _optionFromName.find("-" + charOption);
    if (it == _optionFromName.end()) {
        throw ParseArgumentException(charOption.c_str(), "invalid option");
    }

    if (hasArg) {
        if (it->second->type == Option::NUMBER_OPTION && it->second->nbArgs != 1) {
            throw ParseArgumentException(charOption.c_str(), "option cannot use with only 1 argument");
        }
        if (it->second->type != Option::MULTI_OPTION || it->second->isExist == false) {
            it->second->arguments.clear();
        }
        it->second->arguments.push_back(arg);
    }
    else {
        if (*index + it->second->nbArgs >= static_cast<unsigned int>(maxIndex)) {
            throw ParseArgumentException(charOption.c_str(), "bad number of argument");
        }
        if (it->second->type != Option::MULTI_OPTION || it->second->isExist == false) {
            it->second->arguments.clear();
        }
        if (it->second->type == Option::INFINITE_OPTION) {
            std::size_t countArg = 0;
            for (int j = *index + 1 ; j < maxIndex ; ++j) {
                if (isShortOption(argv[j]) || isLongOption(argv[j])) {
                    break;
                }
                it->second->arguments.push_back(argv[j]);
                ++countArg;
            }
            *index += countArg;
        }
        else {
            for (unsigned int j = *index + 1 ; j <= (*index + it->second->nbArgs) ; ++j) {
                it->second->arguments.push_back(argv[j]);
            }
            *index += it->second->nbArgs;
        }
    }
    it->second->isExist = true;
    ++it->second->count;
}

void Optparsor::getLongOption(int maxIndex, char* argv[], int* index) {
    std::string option;
    std::string arg;
    std::map<std::string, Option*>::iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    it = _optionFromName.find(option);
    if (it == _optionFromName.end()) {
        throw ParseArgumentException(option.c_str() + PREFIX_SIZEOF_LONG_OPTION, "invalid option");
    }

    if (hasArg) {
        if (it->second->type == Option::NUMBER_OPTION && it->second->nbArgs != 1) {
            throw ParseArgumentException(option.c_str() + PREFIX_SIZEOF_LONG_OPTION, "option cannot use with only 1 argument");
        }
        if (it->second->type != Option::MULTI_OPTION || it->second->isExist == false) {
            it->second->arguments.clear();
        }
        it->second->arguments.push_back(arg);
    }
    else {
        if (*index + it->second->nbArgs >= static_cast<unsigned int>(maxIndex)) {
            throw ParseArgumentException(option.c_str() + PREFIX_SIZEOF_LONG_OPTION, "bad number of argument");
        }
        if (it->second->type != Option::MULTI_OPTION || it->second->isExist == false) {
            it->second->arguments.clear();
        }
        if (it->second->type == Option::INFINITE_OPTION) {
            std::size_t countArg = 0;
            for (int j = *index + 1 ; j < maxIndex ; ++j) {
                if (isShortOption(argv[j]) || isLongOption(argv[j])) {
                    break;
                }
                it->second->arguments.push_back(argv[j]);
                ++countArg;
            }
            *index += countArg;
        }
        else {
            for (unsigned int j = *index + 1 ; j <= (*index + it->second->nbArgs) ; ++j) {
                it->second->arguments.push_back(argv[j]);
            }
            *index += it->second->nbArgs;
        }
    }
    it->second->isExist = true;
    ++it->second->count;
}

void Optparsor::getPositionnalArgument(int /*maxIndex*/, char* argv[], int* index) {
    std::list<Option>::iterator it;
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        // assign argument to first not used argument
        if (it->type == Option::POSITIONAL_ARGUMENT && it->isExist == false) {
            it->isExist = true;
            it->arguments.clear();
            it->arguments.push_back(argv[*index]);
            break;
        }
    }
    if (it == _options.end()) {
        if (_throwAtExtra) {
            throw ParseArgumentException(argv[*index], "invalid extra argument");
        }
        else {
            _extraArguments.push_back(argv[*index]);
        }
    }
}

} // namespace mblet