/**
 * @file KeyValidator.hpp
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
#ifndef KEYVALIDATOR_HPP
#define KEYVALIDATOR_HPP

#include "jsoncpp/value.h"
#include <optional>
namespace parsing {
/**
 * @class KeyValidator
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class KeyValidator {
public:
    /**
     * @brief
     * @details
     *
     * @return
     *
     * @todo Documentation
     */
    static KeyValidator &getInstance();

    /**
     * @brief
     * @details
     *
     * @param root
     * @param filename
     * @return
     *
     * @todo Documentation
     */
    std::vector<std::tuple<int, std::string>>
                                           validateKeys(const Json::Value &root, const std::string &filename);

private:
    /**
     * @brief
     * @details
     *
     * @param root
     * @param filename
     *
     * @return
     */
    std::vector<std::tuple<int, std::string>>
                                           getWrongKeys(Json::Value root, const std::string &filename);

    /**
     * @brief
     * @details
     *
     * @param filename
     * @param entry
     * @param entryKeys
     * @return
     *
     * @todo Documentation
     */
    static void validateTypes(const std::string &filename,
                              const Json::Value &entry,
                              std::vector<std::string> &entryKeys);

    /**
     * @brief
     * @details
     *
     * @param filename
     * @param entryKeys
     * @return
     *
     * @todo Documentation
     */
    std::vector<std::tuple<int, std::string>>
                                           validateEntries(const std::string &filename,
                                                   const std::vector<std::string> &entryKeys);

    /**
     * @brief
     * @details
     *
     * @param filename
     * @param wrongKey
     * @return
     *
     * @todo Documentation
     */
    static std::optional<int> getUnknownKeyLine(const std::string &filename,
            const std::string &wrongKey);

    std::vector<std::string> validKeys = {"outputfile", "hideshell", "entries",
                                          "application"
                                         };
    std::vector<std::string> validEntryKeys = {"type", "key", "value", "path",
                                               "command"
                                              };
};
} // namespace parsing

#endif
