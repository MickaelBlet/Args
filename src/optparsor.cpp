#include <iostream>
#include <cstring>
#include <cstdlib>

#include "optparsor.hpp"

#ifdef DEBUG_LOG
    #include <cstdio>
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #define LOG_DEBUG(format, ...) printf("%s:%d: " format "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG_DEBUG(format, ...) /* nothing */
#endif // DEBUG_LOG

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

Optparsor::Optparsor() {
    addOption("-h", "--help", "show this help message and exit");
}

Optparsor::~Optparsor() {}

std::ostream& Optparsor::getUsage(std::ostream& oss) const {
    // usage line
    oss << "usage: " << _binaryName;
    std::list<Option>::const_iterator it;
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        if (it->type != Option::OPTION) {
            continue;
        }
        oss << " [";
        std::string optionName;
        if (!it->shortName.empty()) {
            if (it->nbArgs > 0) {
                oss << it->shortName << ' ' << it->usageName;
            }
            else {
                oss << it->shortName;
            }
        }
        else {
            if (it->nbArgs > 0) {
                oss << it->longName << ' ' << it->usageName;
            }
            else {
                oss << it->longName;
            }
        }
        oss << ']';
    }
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        if (it->type != Option::ARGUMENT) {
            continue;
        }
        oss << " [" << it->longName << "]";
    }
    oss << "\n";
    // optionnal
    if (_options.size() > 0) {
        oss << "\noptional arguments:\n";
        std::list<std::pair<std::string, std::string> > optionnals;
        for (it = _options.begin() ; it != _options.end() ; ++it) {
            optionnals.push_back(std::pair<std::string, std::string>("", ""));
            std::string& optionStr = optionnals.back().first;
            std::string& helpStr = optionnals.back().second;
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
            if (!it->usageName.empty()) {
                optionStr += " " + it->usageName;
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
        for (optIt = optionnals.begin() ; optIt != optionnals.end() ; ++optIt) {
            if (max < optIt->first.size()) {
                max = optIt->first.size();
            }
        }
        for (optIt = optionnals.begin() ; optIt != optionnals.end() ; ++optIt) {
            oss.width(max);
            oss.flags(std::ios::left);
            oss << optIt->first;
            oss.width(0);
            oss << optIt->second;
        }
    }
    return oss;
}

void Optparsor::extraUsage(const char* extraUsageMessage) {
    _extraUsage = extraUsageMessage;
}

void Optparsor::parseArguments(int argc, char* argv[]) {
#ifdef DEBUG_LOG
    LOG_DEBUG("argc: %d", argc);
    for (int i = 0 ; i < argc ; ++i) {
        LOG_DEBUG("argv[%d]: \"%s\"", i, argv[i]);
    }
#endif

    // save index of "--" if exist
    int endIndex = endOptionIndex(argc, argv);
    LOG_DEBUG("endIndex: %d", endIndex);

    _binaryName = argv[0];
    LOG_DEBUG("_binaryName: \"%s\"", _binaryName.c_str());

    // foreach argument
    for (int i = 1 ; i < argc ; ++i) {
        if (isShortOption(argv[i])) {
            LOG_DEBUG("argv[%d]: \"%s\" is short option", i, argv[i]);
            getShortOption(endIndex, argv, &i);
        }
        else if (isLongOption(argv[i])) {
            LOG_DEBUG("argv[%d]: \"%s\" is long option", i, argv[i]);
            getLongOption(endIndex, argv, &i);
        }
        else if (isEndOption(argv[i])) {
            ++i;
            while (i < argc) {
                getArgument(argc, argv, &i);
                ++i;
            }
            break;
        }
        else {
            getArgument(argc, argv, &i);
        }
    }
    // check help option
    if (_optionFromName["--help"]->isExist) {
        getUsage();
        exit(1);
    }
    // check require option
    std::list<Option>::iterator it;
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        if (it->isRequired && it->isExist == false) {
            if (!it->longName.empty()) {
                throw ParseArgumentRequiredException(it->longName.c_str(), "Option is required.");
            }
            else {
                throw ParseArgumentRequiredException(it->shortName.c_str(), "Option is required.");
            }
        }
    }
}

void Optparsor::addOption(const char* shortName, const char* longName, const char* help, bool isRequired,
                          const char* usageName,
                          std::size_t nbArgs,
                          ...) {
    if ((shortName == NULL || shortName[0] == '\0') && (longName == NULL || longName[0] == '\0')) {
        throw ArgumentException("", "Bad short and long arguments.");
    }
    if (shortName != NULL && shortName[0] != '\0') {
        if (shortName[0] != '-') {
            throw ArgumentException(shortName, "Bad short argument not start by '-' character.");
        }
        else if (shortName[0] == '-' && shortName[1] == '\0') {
            throw ArgumentException(shortName, "Bad short argument not character after '-'.");
        }
        else if (shortName[2] != '\0') {
            throw ArgumentException(shortName, "Bad short argument not only one character.");
        }
        else if (_optionFromName.find(shortName) != _optionFromName.end()) {
            throw ArgumentException(shortName, "Bad short argument already exist.");
        }
    }
    if (longName != NULL && longName[0] != '\0') {
        if (longName[0] != '-' || longName[1] != '-') {
            throw ArgumentException(longName, "Bad long argument not start by '--' characters.");
        }
        else if (longName[0] == '-' && longName[1] == '-' && longName[2] == '\0') {
            throw ArgumentException(longName, "Bad short argument not character after '-'.");
        }
        if (_optionFromName.find(longName) != _optionFromName.end()) {
            throw ArgumentException(longName, "Bad long argument already exist.");
        }
    }

    // check usageNames
    std::string defaultUsageName;
    if (usageName == NULL || usageName[0] == '\0') {
        // create a defaultUsageName from longName or shortName
        if (longName != NULL && longName[0] != '\0') {
            defaultUsageName = longName + 2;
        }
        else {
            defaultUsageName = shortName + 1;
        }
        for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
            defaultUsageName[i] = ::toupper(defaultUsageName[i]);
        }
        usageName = defaultUsageName.c_str();
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
    option.type = Option::OPTION;
    option.nbArgs = nbArgs;
    option.usageName = usageName;
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

void Optparsor::addArgument(const char* name, const char* help, bool isRequired, const char* usageName,
                            const char* defaultValue) {
    if (name == NULL || name[0] == '\0') {
        throw ArgumentException("", "Bad name argument.");
    }
    if (name != NULL && name[0] != '\0') {
        if (name[0] == '-') {
            throw ArgumentException(name, "Bad name argument start by '-' character.");
        }
        else if (_optionFromName.find(name) != _optionFromName.end()) {
            throw ArgumentException(name, "Bad name argument already exist.");
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
    option.type = Option::ARGUMENT;
    if (help != NULL) {
        option.help = help;
    }
    if (usageName != NULL) {
        option.usageName = usageName;
    }
    if (defaultValue != NULL) {
        option.arguments.push_back(defaultValue);
        option.defaultValues.push_back(defaultValue);
    }
}

bool Optparsor::getShortOption(int argc, char* argv[], int* index) {
    std::string options;
    std::string arg;
    std::map<std::string, Option*>::iterator it;
    bool hasArg = takeArg(argv[*index], &options, &arg);
    // get firsts option
    for (std::size_t i = 1 ; i < options.size() - 1 ; ++i) {
        std::string charOption(options, i, 1);
        LOG_DEBUG("try to find \"-%s\" in option map", charOption.c_str());
        it = _optionFromName.find("-" + charOption);
        if (it == _optionFromName.end()) {
            throw ParseArgumentException(charOption.c_str(), "Option not added.");
        }
        else if (it->second->nbArgs != 0) {
            throw ParseArgumentException(charOption.c_str(), "Only last short option can be have argument.");
        }
        it->second->isExist = true;
    }
    // get last option
    std::string charOption(options, options.size() - 1, 1);
    LOG_DEBUG("try to find \"-%s\" in option map", charOption.c_str());
    it = _optionFromName.find("-" + charOption);
    if (it == _optionFromName.end()) {
        throw ParseArgumentException(charOption.c_str(), "Option not added.");
    }

    if (hasArg) {
        if (it->second->nbArgs != 1) {
            throw ParseArgumentException(charOption.c_str(), "Option has not configured for use only 1 argument.");
        }
        it->second->arguments.clear();
        it->second->arguments.push_back(arg);
    }
    else {
        if (*index + it->second->nbArgs >= static_cast<unsigned int>(argc)) {
            throw ParseArgumentException(charOption.c_str(), "Option bad number of arguments.");
        }
        it->second->arguments.clear();
        for (unsigned int j = *index + 1 ; j <= (*index + it->second->nbArgs) ; ++j) {
            it->second->arguments.push_back(argv[j]);
        }
        *index += it->second->nbArgs;
    }
    it->second->isExist = true;
    return true;
}

bool Optparsor::getLongOption(int argc, char* argv[], int* index) {
    std::string option;
    std::string arg;
    std::map<std::string, Option*>::iterator it;
    bool hasArg = takeArg(argv[*index], &option, &arg);
    LOG_DEBUG("try to find \"-%s\" in option map", option.c_str());
    it = _optionFromName.find(option);
    if (it == _optionFromName.end()) {
        throw ParseArgumentException(option.c_str(), "Option not added.");
    }

    if (hasArg) {
        if (it->second->nbArgs != 1) {
            throw ParseArgumentException(option.c_str(), "Option has not configured for use only 1 argument.");
        }
        it->second->arguments.clear();
        it->second->arguments.push_back(arg);
    }
    else {
        if (*index + it->second->nbArgs >= static_cast<unsigned int>(argc)) {
            throw ParseArgumentException(option.c_str(), "Option bad number of arguments.");
        }
        it->second->arguments.clear();
        for (unsigned int j = *index + 1 ; j <= (*index + it->second->nbArgs) ; ++j) {
            it->second->arguments.push_back(argv[j]);
        }
        *index += it->second->nbArgs;
    }
    it->second->isExist = true;
    return true;
}

bool Optparsor::getArgument(int /*argc*/, char* argv[], int* index) {
    std::list<Option>::iterator it;
    for (it = _options.begin() ; it != _options.end() ; ++it) {
        // assign argument to first not used argument
        if (it->type == Option::ARGUMENT && it->isExist == false) {
            LOG_DEBUG("argv[%d]: \"%s\" is \"%s\"", *index, it->longName.c_str(), argv[*index]);
            it->isExist = true;
            it->arguments.clear();
            it->arguments.push_back(argv[*index]);
            break;
        }
    }
    if (it == _options.end()) {
        LOG_DEBUG("argv[%d]: \"%s\" is Extra", *index, argv[*index]);
        _extraArguments.push_back(argv[*index]);
    }
    return true;
}

} // namespace mblet