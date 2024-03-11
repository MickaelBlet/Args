/**
 * args/args.h
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

#ifndef BLET_ARGS_ARGS_H_
#define BLET_ARGS_ARGS_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "blet/args/action.h"
#include "blet/args/argument.h"
#include "blet/args/exception.h"
#include "blet/args/usage.h"
#include "blet/args/vector.h"

namespace blet {

namespace args {

class Argument;
class Usage;

/**
 * @brief Object for parse the main arguments
 */
class Args : public Usage {
    friend class Argument;
    friend class Usage;

  public:
    /**
     * @brief Construct a new Args object
     */
    Args(bool addHelp);

    /**
     * @brief Destroy the Args object
     */
    virtual ~Args();

    /**
     * @brief Set the version message
     *
     * @param version
     */
    void setVersion(const std::string& version) {
        version_ = version;
    }

    /**
     * @brief Get the version message
     *
     * @return const std::string&
     */
    const std::string& getVersion() const {
        return version_;
    }

    /**
     * @brief Active parsing for accept long option with only one '-' character
     *
     * @param alternivative
     */
    Args& setAlternative(bool alternivative = true) {
        isAlternative_ = alternivative;
        return *this;
    }

    /**
     * @brief Get the status of alternative
     *
     * @return [true] at alternative
     */
    bool isAlternative() const {
        return isAlternative_;
    }

    /**
     * @brief Active exception if not all argument is used else you can take additionnal argument with
     *        getAdditionalArguments method
     *
     * @param strict
     */
    Args& setStrict(bool strict = true) {
        isStrict_ = strict;
        return *this;
    }

    /**
     * @brief Get the status of strict
     *
     * @return [true] at strict
     */
    bool isStrict() const {
        return isStrict_;
    }

    /**
     * @brief Throw a HelpException when help action is present in arguments else exit(0) the your
     *        program after output usage at stdout
     *
     * @param helpException
     */
    Args& setHelpException(bool helpException = true) {
        isHelpException_ = helpException;
        return *this;
    }

    /**
     * @brief Get the status of helpException
     *
     * @return [true] at usage exception
     */
    bool isHelpException() const {
        return isHelpException_;
    }

    /**
     * @brief Throw a VersionException when version action is present in arguments else exit(0) the your
     *        program after output usage at stdout
     *
     * @param versionException
     */
    Args& setVersionException(bool versionException = true) {
        isVersionException_ = versionException;
        return *this;
    }

    /**
     * @brief Get the status of versionException
     *
     * @return [true] at version exception
     */
    bool isVersionException() const {
        return isVersionException_;
    }

    /**
     * @brief Set the binary name
     *
     * @param binaryName
     */
    void setBinaryName(const char* binaryName) {
        binaryName_ = binaryName;
    }

    /**
     * @brief Get the binary name
     *
     * @return const std::string&
     */
    const std::string& getBinaryName() const {
        return binaryName_;
    }

    /**
     * @brief Check if argument exist
     *
     * @param nameOrFlag
     * @return [true] argument is in map, [false] argument is not in map
     */
    bool argumentExists(const std::string& nameOrFlag) const {
        return (argumentFromName_.find(nameOrFlag) != argumentFromName_.end());
    }

    /**
     * @brief Get the argument object
     *
     * @param nameOrFlag
     * @return const Argument&
     */
    const Argument& getArgument(const std::string& nameOrFlag) const {
        std::map<std::string, Argument**>::const_iterator cit = argumentFromName_.find(nameOrFlag);
        if (cit == argumentFromName_.end()) {
            throw AccessDeniedException(nameOrFlag.c_str(), "argument not found");
        }
        return **(cit->second);
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
        return additionalArguments_;
    }

    /**
     * @brief Convert argument strings to objects and assign them as attributes of the args map.
     *        Previous calls to addArgument() determine exactly what objects are created and how they are assigned.
     *        Comportenment depend of setAlternative, setStrict, setHelpException and setVersionException modes.
     * @param argc
     * @param argv
     *
     * @throw HelpException if setHelpException is active
     * @throw VersionException if setVersionException is active
     * @throw ParseArgumentRequiredException
     * @throw ParseArgumentValidException
     * @throw ParseArgumentException
     */
    void parseArguments(int argc, char* argv[]);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     *
     * @return Argument& ref of new argument object
     *
     * @throw ArgumentException
     */
    Argument& addArgument(const Vector& nameOrFlags);

    /**
     * @brief Get the ref. of argument from name or flag
     *
     * @param nameOrFlag
     * @return Argument& ref argument object
     *
     * @throw ArgumentException
     */
    Argument& updateArgument(const std::string& nameOrFlag) {
        std::map<std::string, Argument**>::iterator it = argumentFromName_.find(nameOrFlag);
        if (it == argumentFromName_.end()) {
            throw AccessDeniedException(nameOrFlag.c_str(), "argument not found");
        }
        return **(it->second);
    }

    /**
     * @brief Remove previously arguments
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     *
     * @throw ArgumentException
     */
    void removeArguments(const Vector& nameOrFlags);

    /**
     * @brief Clear and reset with defaults values
     */
    void clear();

  private:
    Args(const Args&);            // disable copy constructor
    Args& operator=(const Args&); // disable copy operator

    /**
     * @brief Get the short argument decompose multi short argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void parseShortArgument_(int maxIndex, char* argv[], int* index);

    /**
     * @brief Get the long argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     */
    void parseLongArgument_(int maxIndex, char* argv[], int* index);

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
    void parseArgument_(int maxIndex, char* argv[], int* index, bool hasArg, const char* option, const char* arg,
                        Argument* argument);

    /**
     * @brief Get the positionnal argument
     *
     * @param argv
     * @param index
     * @param strict
     */
    void parsePositionnalArgument_(int argc, char* argv[], int* index, bool hasEndOption = false);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @param alternative
     * @return true
     * @return false
     */
    bool endOfInfiniteArgument_(const char* argument);

    std::string binaryName_;

    std::list<Argument*> arguments_;
    std::map<std::string, Argument**> argumentFromName_;

    Argument* helpOption_;
    Argument* versionOption_;

    std::string version_;

    bool isAlternative_;
    bool isStrict_;
    bool isHelpException_;
    bool isVersionException_;
    std::vector<std::string> additionalArguments_;
};

} // namespace args

} // namespace blet

#endif // #ifndef BLET_ARGS_ARGS_H_
