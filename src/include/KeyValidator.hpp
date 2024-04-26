/**
 * @file KeyValidator.hpp
 * @author Simon Blum
 * @date 2024-04-26
 * @version 0.2.2
 * @brief This file contains the KeyValidator class
 *
 * @see parsing::KeyValidator
 *
 * @see src/sources/KeyValidator.cpp
 *
 * @copyright See LICENSE file
 */
#ifndef KEYVALIDATOR_HPP
#define KEYVALIDATOR_HPP

#include "jsoncpp/value.h"
#include <optional>
#include <unordered_map>
#include <unordered_set>
namespace parsing {
/**
 * @class KeyValidator
 * @brief Validates keys of a Json::Value object.
 * @details
 * This class is singleton. That way when multiple files are parsed
 * with the application, the maps for valid keys and the set for the type
 * entries field only have to be allocated once when parsing multiple files.
 * - {ReqFunc17}
 */
class KeyValidator {
  public:
    /**
     * @brief Get the instance of this class
     *
     * @return Reference to the instance of this class
     */
    static KeyValidator &getInstance();

    /**
     * @brief Validate keys off a Json::Value object
     * @details
     * This method goes through the MemberNames of a Json::Value object and
     * validates, that they are part of the validKey attribute.
     * It calls the nessecary methods to validate the keys within the
     * entries array.
     *
     * @param root The Json::Value object to be validated.
     * @param filename The filename from which 'root' is from.
     *
     * @return A vector with tuples, containing the line and name of invalid
     * types.
     */
    std::vector<std::tuple<int, std::string>>
    validateKeys(const Json::Value &root, const std::string &filename);

  private:
    /**
     * @brief Retrieve the wrong keys from a Json::Value object
     * @details
     * This method goes through each key of the Json::Value object and makes
     * sure it's valid.
     *
     * @param root The Json::Value object to be validated.
     * @param filename The filename from which 'root' is from.
     *
     * @return A vector with tuples, containing the line and name of invalid
     * types.
     */
    std::vector<std::tuple<int, std::string>>
    getWrongKeys(const Json::Value &root, const std::string &filename) const;

    /**
     * @brief Validates types from the entries array.
     * @details
     * This method goes makes sure, that the type of the given entry is valid
     * and that it contains it's necessary keys.
     * It will throw an exception if the type is missing, if the type is invalid
     * or if the type is missing a key.
     *
     * @note Unnecessary keys within a type entry, don't cause an exception and
     * are ignored.
     *
     * @param filename The filename from which 'entry' is from
     * @param entry The entry to be validated
     * @param entryKeys The keys of the entry
     *
     * @throw exceptions::MissingTypeException
     * @throw exceptions::InvalidTypeException
     * @throw exceptions::MissingKeyException
     */
    void validateTypes(const std::string &filename, const Json::Value &entry,
                       const std::unordered_set<std::string> &entryKeys);

    /**
     * @brief Validates that keys within the entries array are valid.
     * @details
     * This mehthod goes through each of the entries, and validates, that
     * the keys are part of the validEntryKeys attribute.
     *
     *
     * @param filename The filename from which the entries are from
     * @param entryKeys The keys of the entries
     *
     * @return A vector with tuples, containing the line and name of invalid
     * entrie keys
     */
    std::vector<std::tuple<int, std::string>>
    validateEntries(const std::string &filename,
                    const std::unordered_set<std::string> &entryKeys) const;

    /**
     * @brief Get the line of an unknown key
     * @details
     * This method goes through each line of the given file and checks if the
     * line contains the given key. Returns std::nullopt if the file can't be
     * opened or the key was not found.
     *
     * @param filename The filename which should contain the key
     * @param wrongKey The key to be searched for
     *
     * @return The line of the key, if it was found
     */
    static std::optional<int> getUnknownKeyLine(const std::string &filename,
                                                const std::string &wrongKey);

    /**
     * @note Changed from vector to unordered_set in 0.2.1 - as this shoud improve
     * lookup performance from O(n) to O(1)
     */
    std::unordered_set<std::string> validKeys = {"outputfile", "hideshell",
        "entries", "application"
    };
    /**
     * @note Changed from vector to unordered_set in 0.2.1 - as this shoud improve
     * lookup performance from O(n) to O(1)
     */
    std::unordered_set<std::string> validEntryKeys = {"type", "key", "value",
        "path", "command"
    };

    /**
     * @note Changed from if/else clause within function to map in 0.2.1
     */
    std::unordered_map<std::string_view, std::vector<std::string>> typeToKeys = {
        {"EXE", {"command"}}, {"PATH", {"path"}}, {"ENV", {"key", "value"}}
    };
};
} // namespace parsing

#endif
