#include <algorithm>

#include "mblet/argparsor-argument.h"
#include "mblet/argparsor-utils.h"

#define PREFIX_SIZEOF_SHORT_OPTION (sizeof("-") - 1)
#define PREFIX_SIZEOF_LONG_OPTION (sizeof("--") - 1)

namespace mblet {

namespace argparsor {

static inline bool compareFlag(const std::string& first, const std::string& second) {
    if (isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return first < second;
    }
    else if (isShortOption(first.c_str()) && !isShortOption(second.c_str())) {
        return true;
    }
    else if (!isShortOption(first.c_str()) && isShortOption(second.c_str())) {
        return false;
    }
    else {
        return first < second;
    }
}

void Argument::_sortNameOrFlags(void) {
    std::sort(_nameOrFlags.begin(), _nameOrFlags.end(), &compareFlag);
}

bool Argument::compareOption(const Argument* first, const Argument* second) {
    if (first->_type == Argument::POSITIONAL_ARGUMENT && first->_isRequired
        && second->_type == Argument::POSITIONAL_ARGUMENT && second->_isRequired) {
        return false;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT && first->_isRequired
             && second->_type == Argument::POSITIONAL_ARGUMENT) {
        return true;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT
             && second->_type == Argument::POSITIONAL_ARGUMENT && second->_isRequired) {
        return false;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT
             && second->_type == Argument::POSITIONAL_ARGUMENT) {
        return false;
    }
    else if (first->_type == Argument::POSITIONAL_ARGUMENT) {
        return false;
    }
    else if (second->_type == Argument::POSITIONAL_ARGUMENT) {
        return true;
    }
    if (isShortOption(first->_nameOrFlags.front().c_str()) && isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return first->_nameOrFlags.front() <= second->_nameOrFlags.front();
        }
    }
    else if (isShortOption(first->_nameOrFlags.front().c_str()) && !isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (!isShortOption(first->_nameOrFlags.front().c_str()) && isShortOption(second->_nameOrFlags.front().c_str())) {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        else {
            return false;
        }
    }
    else {
        if (first->_isRequired && !second->_isRequired) {
            return true;
        }
        else if (!first->_isRequired && second->_isRequired) {
            return false;
        }
        return first->_nameOrFlags.front() < second->_nameOrFlags.front();
    }
}

std::string Argument::_metavarDefault() {
    const char* flag = NULL;
    // get short or long name
    for (std::size_t i = 0 ; i < _nameOrFlags.size() ; ++i) {
        if (_nameOrFlags[i][0] == '-' && _nameOrFlags[i][1] == '-') {
            flag = _nameOrFlags[i].c_str() + PREFIX_SIZEOF_LONG_OPTION;
            break;
        }
        else if (flag == NULL && _nameOrFlags[i][0] == '-' && _nameOrFlags[i][1] != '-') {
            flag = _nameOrFlags[i].c_str() + PREFIX_SIZEOF_SHORT_OPTION;
        }
    }
    // create a defaultUsageName from longName or shortName
    std::string defaultUsageName = flag;
    for (std::size_t i = 0 ; i < defaultUsageName.size() ; ++i) {
        defaultUsageName[i] = ::toupper(defaultUsageName[i]);
    }

    if (_action == Argparsor::INFINITE || _nargs == '+') {
        return defaultUsageName + "...";
    }
    else if (_nargs > 1) {
        std::string numberDefaultUsageName;
        for (std::size_t i = 0 ; i < _nargs ; ++i) {
            if (i > 0) {
                numberDefaultUsageName += " ";
            }
            numberDefaultUsageName += defaultUsageName;
        }
        return numberDefaultUsageName;
    }
    else {
        return defaultUsageName;
    }
}

void Argument::_typeConstructor() {
    if (_type == Argument::POSITIONAL_ARGUMENT) {
        throw ArgumentException(_nameOrFlags.front().c_str(), "positional argument cannot use action or nargs");
    }
    if (_action == Argparsor::STORE_TRUE) {
        _type = Argument::BOOLEAN_OPTION;
    }
    else if (_action == Argparsor::STORE_FALSE) {
        _type = Argument::REVERSE_BOOLEAN_OPTION;
    }
    else if (_action == Argparsor::HELP) {
        if (_argparsor._helpOption == NULL) {
            _argparsor._helpOption = this;
        }
        if (_argparsor._helpOption != NULL && _argparsor._helpOption != this) {
            throw ArgumentException(_nameOrFlags.front().c_str(), "help action already defined");
        }
        _type = Argument::HELP_OPTION;
    }
    else if (_action == Argparsor::VERSION) {
        if (_argparsor._versionOption == NULL) {
            _argparsor._versionOption = this;
        }
        if (_argparsor._versionOption != NULL && _argparsor._versionOption != this) {
            throw ArgumentException(_nameOrFlags.front().c_str(), "version action already defined");
        }
        _type = Argument::VERSION_OPTION;
    }
    // is simple
    else if (_nargs == 1 && _action == Argparsor::NONE) {
        _type = Argument::SIMPLE_OPTION;
    }
    // is infinite
    else if ((_nargs == '+' && _action == Argparsor::NONE) || _action == Argparsor::INFINITE) {
        _type = Argument::INFINITE_OPTION;
    }
    // is number
    else if (_nargs > 1 && _action == Argparsor::NONE) {
        _type = Argument::NUMBER_OPTION;
    }
    // is multi
    else if (_nargs == 1 && _action == Argparsor::APPEND) {
        _type = Argument::MULTI_OPTION;
    }
    // is multi number
    else if (_nargs > 1 && _action == Argparsor::APPEND) {
        _type = Argument::MULTI_NUMBER_OPTION;
    }
    // is multi infinite
    else if (_nargs == 1 && _action == Argparsor::EXTEND) {
        _type = Argument::MULTI_INFINITE_OPTION;
    }
    // is multi number infinite
    else if (_nargs > 1 && _action == Argparsor::EXTEND) {
        _type = Argument::MULTI_NUMBER_INFINITE_OPTION;
    }
}

void Argument::_defaultsConstructor() {
    // default arguments
    if (_nargs > 0 && _defaults.size() > 0) {
        clear();
        switch (_type) {
            case Argument::SIMPLE_OPTION:
            case Argument::POSITIONAL_ARGUMENT:
                if (_defaults.size() != _nargs) {
                    throw ArgumentException(_nameOrFlags.front().c_str(), "invalid number of argument with number of default argument");
                }
                _argument = _defaults.front();
                _default = _defaults.front();
                break;
            case Argument::NUMBER_OPTION:
                if (_defaults.size() != _nargs) {
                    throw ArgumentException(_nameOrFlags.front().c_str(), "invalid number of argument with number of default argument");
                }
                _default = "";
                for (std::size_t i = 0 ; i < _defaults.size() ; ++i) {
                    if (i > 0) {
                        _default += ", ";
                    }
                    _default += _defaults[i];
                    push_back(ArgumentElement(_defaults[i].c_str(), _defaults[i].c_str()));
                }
                break;
            case Argument::MULTI_OPTION:
            case Argument::INFINITE_OPTION:
            case Argument::MULTI_INFINITE_OPTION:
                _default = "";
                for (std::size_t i = 0 ; i < _defaults.size() ; ++i) {
                    if (i > 0) {
                        _default += ", ";
                    }
                    _default += _defaults[i];
                    push_back(ArgumentElement(_defaults[i].c_str(), _defaults[i].c_str()));
                }
                break;
            case Argument::MULTI_NUMBER_OPTION:
            case Argument::MULTI_NUMBER_INFINITE_OPTION:
                if (_defaults.size() % _nargs != 0) {
                    throw ArgumentException(_nameOrFlags.front().c_str(), "invalid number of argument with number of default argument");
                }
                for (std::size_t i = 0 ; i < _defaults.size() / _nargs; ++i) {
                    if (i > 0) {
                        _default += ", ";
                    }
                    _default += "(";
                    ArgumentElement newNumberArgument;
                    for (std::size_t j = 0 ; j < _nargs ; ++j) {
                        if (j > 0) {
                            _default += ", ";
                            newNumberArgument._default += ", ";
                        }
                        _default += _defaults[i * _nargs + j];
                        newNumberArgument._default += _defaults[i * _nargs + j];
                        newNumberArgument.push_back(ArgumentElement(_defaults[i * _nargs + j].c_str(), _defaults[i * _nargs + j].c_str()));
                    }
                    _default += ")";
                    push_back(newNumberArgument);
                }
                break;
            default:
                throw ArgumentException(_nameOrFlags.front().c_str(), "invalid number of argument with number of default argument");
                break;
        }
    }
    else if (_type == Argument::VERSION_OPTION) {
        clear();
        for (std::size_t i = 0 ; i < _defaults.size() ; ++i) {
            if (i > 0) {
                _default += "\n";
            }
            _default += _defaults[i];
        }
    }
}

} // namespace argparsor

} // namespace mblet