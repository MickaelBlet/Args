#ifndef _MBLET_ARGPARSOR_EXCEPTION_H_
#define _MBLET_ARGPARSOR_EXCEPTION_H_

#include <exception>
#include <string>

namespace mblet {

namespace argparsor {

/**
 * @brief Basic exception from std::exception
 */
class Exception : public std::exception {
  public:
    Exception(const char* str) : _str(str) {}
    virtual ~Exception() throw() {}
    const char* what() const throw() {
        return _str.c_str();
    }
  protected:
    std::string _str;
};

/**
 * @brief Argument exception from Exception
 */
class ArgumentException : public Exception {
  public:
    ArgumentException(const char* message) : Exception(message), _argument() {}
    ArgumentException(const char* argument, const char* message) : Exception(message), _argument(argument) {}
    virtual ~ArgumentException() throw() {}
    const char* argument() const throw() {
        return _argument.c_str();
    }
  protected:
    std::string _argument;
};

typedef ArgumentException ParseArgumentException;
typedef ParseArgumentException ParseArgumentRequiredException;
typedef ParseArgumentException ParseArgumentValidException;
typedef ArgumentException AccessDeniedException;

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_EXCEPTION_H_