#ifndef _MBLET_ARGPARSOR_UTILS_H_
#define _MBLET_ARGPARSOR_UTILS_H_

#include <cstring> // strchr
#include <string>

namespace mblet {

namespace argparsor {

/**
 * @brief arg is "-[^-].*"
 *
 * @param arg
 * @return true
 * @return false
 */
inline bool isShortOption(const char* arg) {
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
inline bool isLongOption(const char* arg) {
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
inline bool isEndOption(const char* arg) {
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
inline int endOptionIndex(int argc, char** argv) {
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
inline bool takeArg(const char* arg, std::string* retOptionName, std::string* retArgument) {
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

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_UTILS_H_