#ifndef _MBLET_ARGPARSOR_VECTOR_H_
#define _MBLET_ARGPARSOR_VECTOR_H_

#include <string>
#include <vector>

namespace mblet {

namespace argparsor {

/**
 * @brief Object for parse the main arguments
 */
class Vector : public std::vector<std::string> {

  public:

    Vector() : std::vector<std::string>() {}

    template<std::size_t S>
    Vector(const char* (&v)[S]) : std::vector<std::string>() {
        for (std::size_t i = 0; i < S; ++i) {
            if (v[i] != NULL) {
                std::vector<std::string>::push_back(v[i]);
            }
        }
    }

    template<std::size_t S>
    Vector(const char* const(&v)[S]) : std::vector<std::string>() {
        for (std::size_t i = 0; i < S; ++i) {
            if (v[i] != NULL) {
                std::vector<std::string>::push_back(v[i]);
            }
        }
    }

    template<std::size_t S>
    Vector(const std::string(&v)[S]) : std::vector<std::string>() {
        for (std::size_t i = 0; i < S; ++i) {
            std::vector<std::string>::push_back(v[i]);
        }
    }

    template<std::size_t S>
    Vector(const char (&v)[S]) : std::vector<std::string>() {
        std::vector<std::string>::push_back(v);
    }

    Vector(const char* (&v)) : std::vector<std::string>() {
        std::vector<std::string>::push_back(v);
    }

    Vector(const std::string& v) : std::vector<std::string>() {
        std::vector<std::string>::push_back(v);
    }

#if __cplusplus >= 201103L
    Vector(const std::initializer_list<std::string>& l) : std::vector<std::string>(l) {}
#endif

};

} // namespace argparsor

} // namespace mblet

#endif // _MBLET_ARGPARSOR_VECTOR_H_