/**
 * argparsor/argparsor.h
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

#ifndef _MBLET_ARGPARSOR_ARGPARSOR_H_
#define _MBLET_ARGPARSOR_ARGPARSOR_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "mblet/argparsor/action.h"
#include "mblet/argparsor/argument.h"
#include "mblet/argparsor/exception.h"
#include "mblet/argparsor/usage.h"
#include "mblet/argparsor/vector.h"

namespace mblet {

namespace argparsor {

class Argument;
class Usage;

/**
 * @brief Object for parse the main arguments
 */
class Argparsor : public Usage {
    friend class Argument;
    friend class Usage;

  public:
    /**
     * @brief Construct a new Argparsor object
     */
    Argparsor(bool addHelp);

    /**
     * @brief Destroy the Argparsor object
     */
    virtual ~Argparsor();

    /**
     * @brief Set the version message
     *
     * @param version
     */
    void setVersion(const char* version) {
        _version = version;
    }

    /**
     * @brief Get the Version
     *
     * @return std::string
     */
    const std::string& getVersion() const {
        return _version;
    }

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
     * @brief Get the binary name
     *
     * @return const std::string&
     */
    const std::string& getBinaryName() const {
        return _binaryName;
    }

    /**
     * @brief Check if argument exist
     *
     * @param nameOrFlag
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExists(const std::string& nameOrFlag) const {
        return (_argumentFromName.find(nameOrFlag) != _argumentFromName.end());
    }

    /**
     * @brief Check if argument exist
     *
     * @param nameOrFlag
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExists(const char* nameOrFlag) const {
        return argumentExists(std::string(nameOrFlag));
    }

    /**
     * @brief Get the argument object
     *
     * @param nameOrFlag
     * @return const Argument&
     */
    const Argument& getArgument(const std::string& nameOrFlag) const {
        std::map<std::string, Argument**>::const_iterator cit = _argumentFromName.find(nameOrFlag);
        if (cit == _argumentFromName.end()) {
            throw AccessDeniedException(nameOrFlag.c_str(), "argument not found");
        }
        return **(cit->second);
    }

    /**
     * @brief Get the argument object
     *
     * @param nameOrFlag
     * @return const Argument&
     */
    const Argument& getArgument(const char* nameOrFlag) const {
        return getArgument(std::string(nameOrFlag));
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param nameOrFlag
     * @return const Argument&
     */
    const Argument& operator[](const char* nameOrFlag) const {
        return getArgument(nameOrFlag);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param nameOrFlag
     * @return const Argument&
     */
    const Argument& operator[](const std::string& nameOrFlag) const {
        return getArgument(nameOrFlag);
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
     * @return Argument& ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags);

    /**
     * @brief Get the ref. of argument from name or flag
     *
     * @param nameOrFlag
     * @return Argument& ref argument object
     */
    Argument& updateArgument(const std::string& nameOrFlag) {
        std::map<std::string, Argument**>::iterator it = _argumentFromName.find(nameOrFlag);
        if (it == _argumentFromName.end()) {
            throw AccessDeniedException(nameOrFlag.c_str(), "argument not found");
        }
        return **(it->second);
    }

    /**
     * @brief Remove previously addArgument
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     */
    void removeArguments(const Vector& nameOrFlags);

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
    void _parseShortArgument(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the long argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void _parseLongArgument(int maxIndex, char* argv[], int* index);

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
    void _parseArgument(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                        Argument* argument);

    /**
     * @brief Get the positionnal argument
     *
     * @param argv
     * @param index
     * @param strict
     */
    void _parsePositionnalArgument(int argc, char* argv[], int* index, bool hasEndOption = false);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @param alternative
     * @return true
     * @return false
     */
    bool _endOfInfiniteArgument(const char* argument);

    std::string _binaryName;

    std::list<Argument*> _arguments;
    std::map<std::string, Argument**> _argumentFromName;

    Argument* _helpOption;
    Argument* _versionOption;

    std::string _version;

    bool _isAlternative;
    bool _isStrict;
    std::vector<std::string> _additionalArguments;
};

} // namespace argparsor

} // namespace mblet

#endif // #ifndef _MBLET_ARGPARSOR_ARGPARSOR_H_