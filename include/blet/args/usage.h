/**
 * args/usage.h
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

#ifndef BLET_ARGS_USAGE_H_
#define BLET_ARGS_USAGE_H_

#include <string>

namespace blet {

namespace args {

class Args;

class Usage {
  public:
    /**
     * @brief Construct a new Usage object
     *
     * @param args
     */
    Usage(Args& args);

    /**
     * @brief Destroy the Usage object
     */
    ~Usage();

    /**
     * @brief Set the usage message
     *
     * @param usage
     */
    void setUsage(const char* usage) {
        usage_ = usage;
    }

    /**
     * @brief Get the usage message
     *
     * @return std::string
     */
    std::string getUsage() const;

    /**
     * @brief Set the description in usage message
     *
     * @param description
     */
    void setDescription(const char* description) {
        description_ = description;
    }

    /**
     * @brief Get the description message
     *
     * @return const std::string&
     */
    const std::string& getDescription() const {
        return description_;
    }

    /**
     * @brief Set the epilog in usage message
     *
     * @param epilog
     */
    void setEpilog(const char* epilog) {
        epilog_ = epilog;
    }

    /**
     * @brief Get the epilog message
     *
     * @return const std::string&
     */
    const std::string& getEpilog() const {
        return epilog_;
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
        usagePadWidth_ = padWidth;
        usageArgsWidth_ = argsWidth;
        usageSepWidth_ = sepWidth;
        usageHelpWidth_ = helpWidth;
    }

  protected:
    Args& args_;

    std::string description_;
    std::string epilog_;
    std::string usage_;
    std::size_t usagePadWidth_;
    std::size_t usageArgsWidth_;
    std::size_t usageSepWidth_;
    std::size_t usageHelpWidth_;
};

} // namespace args

} // namespace blet

#endif // #ifndef BLET_ARGS_USAGE_H_
