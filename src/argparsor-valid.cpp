#include "mblet/argparsor-valid.h"

#include <sys/stat.h>

#include <iostream>
#include <sstream>

#include "mblet/argparsor-exception.h"

namespace mblet {

namespace argparsor {

/*
################################################################################
 ValidMinMax
################################################################################
*/

ValidMinMax::ValidMinMax(double min, double max) : _min(min), _max(max) {
    // bad initialized reverse value
    if (min > max) {
        _min = max;
        _max = min;
    }
}

ValidMinMax::~ValidMinMax() {}

bool ValidMinMax::isValid(std::vector<std::string>& args) {
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::stringstream ssArg("");
        ssArg << args[i];
        double number;
        if (!(ssArg >> number)) {
            std::ostringstream oss("");
            oss << "\"" << args[i] << "\" is not a number";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (number < _min || number > _max) {
            std::ostringstream oss("");
            oss << args[i] << " is not between " << _min << " and " << _max;
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidChoise
################################################################################
*/

ValidChoise::ValidChoise(const std::vector<std::string>& choises) : _choises(choises) {}

ValidChoise::~ValidChoise() {}

bool ValidChoise::isValid(std::vector<std::string>& args) {
    std::ostringstream ossChoise("");
    for (std::size_t i = 0; i < _choises.size(); ++i) {
        if (i > 0) {
            ossChoise << ", ";
        }
        ossChoise << '\"' << _choises[i] << '\"';
    }
    for (std::size_t i = 0; i < args.size(); ++i) {
        std::size_t j;
        for (j = 0; j < _choises.size(); ++j) {
            if (args[i] == _choises[j]) {
                break;
            }
        }
        if (j == _choises.size()) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a choise value (" << ossChoise.str() << ')';
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

/*
################################################################################
 ValidPath
################################################################################
*/

ValidPath::ValidPath(enum eMode mode) : _mode(mode) {}

ValidPath::~ValidPath() {}

bool ValidPath::isValid(std::vector<std::string>& args) {
    struct stat statBuff;
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (::stat(args[i].c_str(), &statBuff) == -1) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid path";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        if (_mode == ValidPath::IS_DIR && !S_ISDIR(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid directory";
            throw ParseArgumentValidException(oss.str().c_str());
        }
        else if (_mode == ValidPath::IS_FILE && !S_ISREG(statBuff.st_mode)) {
            std::ostringstream oss("");
            oss << '\"' << args[i] << "\" is not a valid file";
            throw ParseArgumentValidException(oss.str().c_str());
        }
    }
    return true;
}

}  // namespace argparsor

}  // namespace mblet