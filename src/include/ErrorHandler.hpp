/**
 * @file ErrorHandler.hpp
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 * @copyright See LICENSE file
 *
 * @todo Documentation
 */

#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <string>
#include <vector>

/**
 * @namespace errors
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
namespace errors {
/**
 * @class ErrorHandler
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class ErrorHandler {
  public:
    /**
     * @brief
     * @details
     *
     * @param outputFile
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void batchFileExists(const std::string &outputFile);

    /**
     * @brief
     * @details
     *
     * @param fileName
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void parsingError(const std::string &fileName);

    /**
     * @brief
     * @details
     *
     * @param key
     * @param issue
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void invalidValue(const std::string &key,
                                          const std::string &issue);

    /**
     * @brief
     * @details
     *
     * @param keys
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void
    invalidKeys(const std::vector<std::tuple<int, std::string>> &keys);

    /**
     * @brief
     * @details
     *
     * @param type
     * @param line
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void invalidType(const std::string &type, int line);

    /**
     * @brief
     * @details
     *
     * @param key
     * @param type
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void missingKey(const std::string &key,
                                        const std::string &type);
    /**
     * @brief
     * @details
     *
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void missingType();

    /**
     * @brief
     * @details
     *
     * @param message
     * @throws
     *
     * @todo Documentation
     */
    [[noreturn]] static void unreachableCode(const std::string &message);
};

} // namespace errors

#endif
