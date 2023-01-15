/**
 * argparsor/argparsor.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022-2023 BLET Mickaël.
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

#ifndef _MBLET_ARGPARSOR_ARGPARSOR_H_
#define _MBLET_ARGPARSOR_ARGPARSOR_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "mblet/argparsor/action.h"
#include "mblet/argparsor/argument.h"
#include "mblet/argparsor/exception.h"
#include "mblet/argparsor/vector.h"

namespace mblet {

namespace argparsor {

class Argument;

/**
 * @brief Object for parse the main arguments
 */
class Argparsor {
    friend class Argument;

  public:
    /**
     * @brief Construct a new Argparsor object
     */
    Argparsor(bool help);

    /**
     * @brief Destroy the Argparsor object
     */
    virtual ~Argparsor();

    /**
     * @brief Get the status of alternative
     *
     * @return [true] at alternative
     */
    bool isAlternative() const {
        return _isAlternative;
    }

    /**
     * @brief Get the status of strict
     *
     * @return [true] at strict
     */
    bool isStrict() const {
        return _isStrict;
    }

    /**
     * @brief Get the bynary name
     *
     * @return const std::string&
     */
    const std::string& getBynaryName() const {
        return _binaryName;
    }

    /**
     * @brief Get the Usage
     *
     * @return std::string
     */
    std::string getUsage() const;

    /**
     * @brief Get the Version
     *
     * @return std::string
     */
    std::string getVersion() const;

    /**
     * @brief Check if argument exist
     *
     * @param str
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExists(const char* str) const {
        return argumentExists(std::string(str));
    }

    /**
     * @brief Check if argument exist
     *
     * @param str
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExists(const std::string& str) const {
        return (_argumentFromName.find(str) != _argumentFromName.end());
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    const Argument& getArgument(const char* str) const {
        return getArgument(std::string(str));
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    const Argument& getArgument(const std::string& str) const {
        std::map<std::string, Argument**>::const_iterator cit = _argumentFromName.find(str);
        if (cit == _argumentFromName.end()) {
            throw AccessDeniedException(str.c_str(), "argument not found");
        }
        return **(cit->second);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param str
     * @return const Argument&
     */
    const Argument& operator[](const char* str) const {
        return getArgument(str);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param str
     * @return const Argument&
     */
    const Argument& operator[](const std::string& str) const {
        return getArgument(str);
    }

    /**
     * @brief Get the vector of additional argument
     *
     * @return const std::vector<std::string>&
     */
    const std::vector<std::string>& getAdditionalArguments() const {
        return _additionalArguments;
    }

    /**
     * @brief Set the usage message
     *
     * @param usage
     */
    void setUsage(const char* usage) {
        _usage = usage;
    }

    /**
     * @brief Set the Usage Widths.
     * default values:
     * padWidth: 2,
     * argsWidth: 20,
     * sepWidth: 2,
     * helpWidth: 56
     *
     * @param padWidth width of padding to first column of usage message
     * @param argsWidth width of first column of usage message
     * @param sepWidth width of column separator of usage message
     * @param helpWidth width of second column of usage message
     */
    void setUsageWidth(std::size_t padWidth, std::size_t argsWidth, std::size_t sepWidth, std::size_t helpWidth) {
        _usagePadWidth = padWidth;
        _usageArgsWidth = argsWidth;
        _usageSepWidth = sepWidth;
        _usageHelpWidth = helpWidth;
    }

    /**
     * @brief Set the description in usage message
     *
     * @param description
     */
    void setDescription(const char* description) {
        _description = description;
    }

    /**
     * @brief Set the epilog in usage message
     *
     * @param epilog
     */
    void setEpilog(const char* epilog) {
        _epilog = epilog;
    }

    /**
     * @brief Convert argument strings to objects and assign them as attributes of the argparsor map.
     * Previous calls to add_argument() determine exactly what objects are created and how they are assigned
     * @param argc
     * @param argv
     * @param alternative Active parsing for accept long option with only one '-' character
     * @param strict Active exception if not all argument is used else you can take additionnal argument with
     *        getAdditionalArguments method
     */
    void parseArguments(int argc, char* argv[], bool alternative = false, bool strict = false);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     *
     * @return ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags);

    static Vector vector(const char* v1 = NULL, const char* v2 = NULL, const char* v3 = NULL, const char* v4 = NULL,
                         const char* v5 = NULL, const char* v6 = NULL, const char* v7 = NULL, const char* v8 = NULL,
                         const char* v9 = NULL, const char* v10 = NULL) {
        const char* args[] = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
        return args;
    }

  private:
    Argparsor(const Argparsor&);            // disable copy constructor
    Argparsor& operator=(const Argparsor&); // disable copy operator

    /**
     * @brief Get the short argument decompose multi short argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void parseShortArgument(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the long argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void parseLongArgument(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @param hasArg
     * @param option
     * @param arg
     * @param argument
     * @param alternative
     */
    void parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                       Argument* argument);

    /**
     * @brief Get the positionnal argument
     *
     * @param argv
     * @param index
     * @param strict
     */
    void parsePositionnalArgument(char* argv[], int* index);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @param alternative
     * @return true
     * @return false
     */
    bool endOfInfiniteArgument(const char* argument);

    std::string _binaryName;

    std::list<Argument*> _arguments;
    std::map<std::string, Argument**> _argumentFromName;

    Argument* _helpOption;
    Argument* _versionOption;

    std::string _usage;
    std::size_t _usagePadWidth;
    std::size_t _usageArgsWidth;
    std::size_t _usageSepWidth;
    std::size_t _usageHelpWidth;
    std::string _description;
    std::string _epilog;

    bool _isAlternative;
    bool _isStrict;
    std::vector<std::string> _additionalArguments;
};

} // namespace argparsor

} // namespace mblet

#endif // #ifndef _MBLET_ARGPARSOR_ARGPARSOR_H_