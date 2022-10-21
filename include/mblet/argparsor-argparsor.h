#ifndef _MBLET_ARGPARSOR_ARGPARSOR_H_
#define _MBLET_ARGPARSOR_ARGPARSOR_H_

#include <map>
#include <list>
#include <string>
#include <vector>

#include "mblet/argparsor-exception.h"
#include "mblet/argparsor-valid.h"
#include "mblet/argparsor-vector.h"

namespace mblet {

namespace argparsor {

class Argument;

/**
 * @brief Object for parse the main arguments
 */
class Argparsor {

    friend class Argument;

  public:

    enum Action {
        NONE,
        HELP,
        VERSION,
        STORE_TRUE,
        STORE_FALSE,
        APPEND,
        EXTEND,
        INFINITE
    };

    /**
     * @brief Construct a new Argparsor object
     */
    Argparsor(bool help);

    /**
     * @brief Destroy the Argparsor object
     */
    virtual ~Argparsor();

    /**
     * @brief Get the bynary name
     *
     * @return const std::string&
     */
    inline const std::string& getBynaryName() const {
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
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& getArgument(const char* str) const {
        return getArgument(std::string(str));
    }

    /**
     * @brief Get the argument object
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& getArgument(const std::string& str) const {
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
    inline const Argument& operator[](const char* str) const {
        return getArgument(str);
    }

    /**
     * @brief Override bracket operator with getArgument
     *
     * @param str
     * @return const Argument&
     */
    inline const Argument& operator[](const std::string& str) const {
        return getArgument(str);
    }

    /**
     * @brief Get the vector of additional argument
     *
     * @return const std::vector<std::string>&
     */
    inline const std::vector<std::string>& getAdditionalArguments() const {
        return _additionalArguments;
    }

    /**
     * @brief Set the usage message
     *
     * @param usage
     */
    inline void setUsage(const char* usage) {
        _usage = usage;
    }

    /**
     * @brief Set the description in usage message
     *
     * @param description
     */
    inline void setDescription(const char* description) {
        _description = description;
    }

    /**
     * @brief Set the epilog in usage message
     *
     * @param epilog
     */
    inline void setEpilog(const char* epilog) {
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
     * @param actionOrDefault The basic type of action to be taken when this argument is encountered at the command line
     * @param help A brief description of what the argument does
     * @param isRequired Whether or not the command-line option may be omitted (optionals only)
     * @param metavar A name for the argument in usage messages
     * @param nArgs The number of command-line arguments that should be consumed
     * @param defaultArgs The value produced if the argument is absent from the command line
     * @param valid New object from IValid interface
     *
     * @return ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags, Action action,
                          const char* help = NULL, bool isRequired = false, const char* metavar = NULL,
                          std::size_t nArgs = 0, const Vector& defaultArgs = Vector(),
                          IValid* valid = NULL);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     *
     * @return ref of new argument object
     */
    Argument& addArgument(const Vector& nameOrFlags);

    /**
     * @brief Define how a single command-line argument should be parsed
     *
     * @param nameOrFlags Either a name or a list of option strings, e.g. foo or -f, --foo
     * @param actionOrDefault The basic type of action to be taken when this argument is encountered at the command line
     * @param help A brief description of what the argument does
     * @param isRequired Whether or not the command-line option may be omitted (optionals only)
     * @param metavar A name for the argument in usage messages
     * @param nArgs The number of command-line arguments that should be consumed
     * @param defaultArgs The value produced if the argument is absent from the command line
     * @param valid New object from IValid interface
     * @param dest Reference of destination object
     */
    // template<typename T>
    // Argument& addArgument(const Vector& nameOrFlags, Action action,
    //                       const char* help, bool isRequired, const char* metavar,
    //                       std::size_t nArgs, const Vector& defaultArgs,
    //                       IValid* valid, T& dest) {
    //     return addArgument(nameOrFlags, action, help, isRequired,
    //                        metavar, nArgs, defaultArgs, valid).dest(dest);
    // }

    inline static Vector vector(const char* v1 = NULL, const char* v2 = NULL, const char* v3 = NULL, const char* v4 = NULL,
                                const char* v5 = NULL, const char* v6 = NULL, const char* v7 = NULL, const char* v8 = NULL,
                                const char* v9 = NULL, const char* v10 = NULL) {
        const char* args[] = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
        return args;
    }

  private:

    void validFlag(const char* flag) const;

    /**
     * @brief Get the short argument decompose multi short argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @param alternative
     */
    void parseShortArgument(int maxIndex, char* argv[], int* index, bool alternative);

    /**
     * @brief Get the long argument
     *
     * @param maxIndex
     * @param argv
     * @param index
     * @param alternative
     */
    void parseLongArgument(int maxIndex, char* argv[], int* index, bool alternative);

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
                       Argument* argument, bool alternative);

    /**
     * @brief Get the positionnal argument
     *
     * @param argv
     * @param index
     * @param strict
     */
    void parsePositionnalArgument(char* argv[], int* index, bool strict);

    /**
     * @brief Check end of infinite parsing
     *
     * @param argument
     * @param alternative
     * @return true
     * @return false
     */
    bool endOfInfiniteArgument(const char* argument, bool alternative);

    std::string _binaryName;

    std::list<Argument*> _arguments;
    std::map<std::string, Argument**> _argumentFromName;

    Argument* _helpOption;
    Argument* _versionOption;

    std::string _usage;
    std::string _description;
    std::string _epilog;

    std::vector<std::string> _additionalArguments;
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_ARGPARSOR_H_