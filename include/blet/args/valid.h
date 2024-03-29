/**
 * args/valid.h
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

#ifndef BLET_ARGS_VALID_H_
#define BLET_ARGS_VALID_H_

#include <string>
#include <vector>

namespace blet {

namespace args {

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

class ValidNumber : public IValid {
  public:
    /**
     * @brief Construct a new Valid Number object
     */
    ValidNumber();

    /**
     * @brief Destroy the Valid Number object
     */
    ~ValidNumber();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);
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
    ValidMinMax(double min, double max);

    /**
     * @brief Destroy the Valid Min Max object
     */
    ~ValidMinMax();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);

  private:
    double min_;
    double max_;
};

class ValidChoise : public IValid {
  public:
    /**
     * @brief
     *
     * @param choises
     */
    ValidChoise(const std::vector<std::string>& choises);

    /**
     * @brief Destroy the Valid Choise object
     */
    ~ValidChoise();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);

  private:
    std::vector<std::string> choises_;
};

class ValidPath : public IValid {
  public:
    enum eMode {
        ALL = 0,
        IS_FILE,
        IS_DIR
    };

    /**
     * @brief Construct a new Valid Path Exist object
     * at call self @c isValid it check if argument is a exist path
     */
    ValidPath(enum eMode mode = ValidPath::ALL);

    /**
     * @brief Destroy the Valid Path Exist object
     */
    ~ValidPath();

    /**
     * @brief check if arguments are valid
     *
     * @param arguments
     * @return [true] arguments are valid, [false] arguments are not valid
     */
    bool isValid(std::vector<std::string>& args);

  private:
    enum eMode mode_;
};

} // namespace args

} // namespace blet

#endif // #ifndef BLET_ARGS_VALID_H_
