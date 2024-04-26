/**
 * @file KeyValidator.hpp
 * @author Simon Blum
 * @date 21.04.2024
 * @version 0.1.6
 * @brief This file contains the KeyValidator class
 *
 * @see parsing::KeyValidator
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
 * with the application, the validKeys and validEntryKeys field only
 * have to be allocated once.
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
   * Makes sure that each type has it's according keys, needed to parse it.
   *
   * @param filename The filename from which 'entry' is from
   * @param entry
   * @param entryKeys
   */
  void validateTypes(const std::string &filename, const Json::Value &entry,
                     const std::unordered_set<std::string> &entryKeys);

  /**
   * @brief Validates that an entries 'type' key is valid
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
                  const std::unordered_set<std::string> &entryKeys) const;

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

  std::unordered_set<std::string> validKeys = {"outputfile", "hideshell",
                                               "entries", "application"};
  std::unordered_set<std::string> validEntryKeys = {"type", "key", "value",
                                                    "path", "command"};

  std::unordered_map<std::string_view, std::vector<std::string>> typeToKeys = {
      {"EXE", {"command"}}, {"PATH", {"path"}}, {"ENV", {"key", "value"}}};
};
} // namespace parsing

#endif
