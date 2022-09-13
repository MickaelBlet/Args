#ifndef _MBLET_ARGPARSOR_VALID_H_
#define _MBLET_ARGPARSOR_VALID_H_

#include <vector>
#include <string>
#include <sstream>
#include <sys/stat.h>

#include "mblet/argparsor-exception.h"

namespace mblet {

namespace argparsor {

/**
 * @brief Interface for validate argument
 */
class IValid {
  public:
    /**
     * @brief Destroy the IValid object
     */
    virtual ~IValid() {}

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    virtual bool isValid(std::vector<std::string>& arguments) = 0;
};

class ValidMinMax : public IValid {
  public:
    /**
     * @brief Construct a new Valid Min Max object
     * at call self @c isValid it check if arguments are between of @p min and @p max
     *
     * @param min
     * @param max
     */
    ValidMinMax(double min, double max) : _min(min), _max(max) {
        // bad initialized reverse value
        if (min > max) {
            _min = max;
            _max = min;
        }
    }

    /**
     * @brief Destroy the Valid Min Max object
     */
    ~ValidMinMax() {}

    bool isValid(std::vector<std::string>& args) {
        for (std::size_t i = 0 ; i < args.size() ; ++i) {
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

  private:
    double _min;
    double _max;
};

class ValidChoise : public IValid {
  public:
    ValidChoise(const std::vector<std::string>& choises) : _choises(choises) {}
    ~ValidChoise() {}
    bool isValid(std::vector<std::string>& args) {
        std::ostringstream ossChoise("");
        for (std::size_t i = 0; i < _choises.size(); ++i) {
            if (i > 0) {
                ossChoise << ", ";
            }
            ossChoise << '\"' << _choises[i] << '\"';
        }
        for (std::size_t i = 0 ; i < args.size() ; ++i) {
            std::size_t j;
            for (j = 0 ; j < _choises.size() ; ++j) {
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
  private:
    std::vector<std::string> _choises;
};

class ValidPath : public IValid {
  public:
    /**
     * @brief Construct a new Valid Path Exist object
     * at call self @c isValid it check if argument is a exist path
     */
    ValidPath() {}

    /**
     * @brief Destroy the Valid Path Exist object
     */
    ~ValidPath() {}

    bool isValid(std::vector<std::string>& args) {
        struct stat statBuff;
        for (std::size_t i = 0 ; i < args.size() ; ++i) {
            if (::stat(args[i].c_str(), &statBuff) == -1) {
                std::ostringstream oss("");
                oss << '\"' << args[i] << "\" is not a valid path";
                throw ParseArgumentValidException(oss.str().c_str());
            }
        }
        return true;
    }
};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_VALID_H_