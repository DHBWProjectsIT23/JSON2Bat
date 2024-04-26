/**
 * @file KeyValidator.cpp
 * @author Simon Blum
 * @date 2024-04-26
 * @version 0.2.2
 * @brief Implementation for the KeyValidator class.
 *
 * @see src/include/KeyValidator.hpp
 *
 * @copyright See LICENSE file
 */
#include "KeyValidator.hpp"
#include "Exceptions.hpp"
#include "LoggingWrapper.hpp"
#include <optional>
#include <regex>
#include <vector>

namespace parsing {
KeyValidator &KeyValidator::getInstance()
{
    static KeyValidator keyValidator;
    LOG_INFO << "Returning KeyValidator instance!";
    return keyValidator;
}

std::vector<std::tuple<int, std::string>> KeyValidator::validateKeys(
    const Json::Value &root,
    const std::string &filename)
{
    std::vector<std::tuple<int, std::string>> wrongKeys =
        getWrongKeys(root, filename);

    // Inline declaration to prevent leaking in outer scope
    for (Json::Value entries = root.get("entries", "");
            const auto &entry : entries) {
        const auto entryKeys = entry.getMemberNames();
        // Create a set of the entry keys for faster lookup (O(1) instead of O(n))
        std::unordered_set<std::string> entryKeysSet(entryKeys.begin(),
                entryKeys.end());
        const auto wrongEntries = validateEntries(filename, entryKeysSet);
        // Combine wrong keys
        wrongKeys.insert(wrongKeys.end(), wrongEntries.begin(), wrongEntries.end());
        // Validate that each entry has it's necessary keys
        validateTypes(filename, entry, entryKeysSet);
    }

    return wrongKeys;
}

std::vector<std::tuple<int, std::string>> KeyValidator::getWrongKeys(
    const Json::Value &root,
    const std::string &filename) const
{
    std::vector<std::tuple<int, std::string>> wrongKeys = {};

    for (const auto &key : root.getMemberNames()) {
        if (!validKeys.contains(key)) {
            const auto error = getUnknownKeyLine(filename, key);

            if (!error.has_value()) {
                LOG_ERROR << "Unable to find line of wrong key!";
                continue;
            }

            // If the line can't be found, add -1 as line number
            wrongKeys.emplace_back(error.value_or(-1), key);
        }
    }

    return wrongKeys;
}

std::vector<std::tuple<int, std::string>> KeyValidator::validateEntries(
    const std::string &filename,
    const std::unordered_set<std::string> &entryKeys) const
{
    std::vector<std::tuple<int, std::string>> wrongKeys = {};

    for (const auto &key : entryKeys) {
        if (!validEntryKeys.contains(key)) {
            const auto error = getUnknownKeyLine(filename, key);

            if (!error.has_value()) {
                LOG_ERROR << "Unable to find line of wrong key!";
                continue;
            }

            wrongKeys.emplace_back(error.value_or(-1), key);
        }
    }

    return wrongKeys;
}

void KeyValidator::validateTypes(
    const std::string &filename, const Json::Value &entry,
    const std::unordered_set<std::string> &entryKeys)
{
    // Gett the type of the entry - error if not found
    const std::string type = entry.get("type", "ERROR").asString();

    // If the type is not found, throw an exception
    if (type == "ERROR") {
        throw exceptions::MissingTypeException();
        // If the type is not known, throw an exception
        // @note This should already have been checked
    }
    else if (typeToKeys.contains(type)) {
        const std::optional<int> line =
            getUnknownKeyLine(filename, std::string(type));

        if (!line.has_value()) {
            LOG_INFO << "Unable to find line of wrong type!";
        }

        throw exceptions::InvalidTypeException(std::string(type), line.value());
        // If the type is known, check if all necessary keys are present
    }
    else {
        for (const auto &key : typeToKeys[type]) {
            if (entryKeys.contains(key)) {
                throw exceptions::MissingKeyException(key, std::string(type));
            }
        }
    }
}

std::optional<int> KeyValidator::getUnknownKeyLine(const std::string &filename,
        const std::string &wrongKey)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        LOG_ERROR << "File not open!";
        return std::nullopt;
    }

    std::string line;
    // Create a regex pattern that matches the wrong key whole word
    const std::regex wrongKeyPattern("\\b" + wrongKey + "\\b");

    for (int lineNumber = 1; std::getline(file, line); ++lineNumber) {
        if (std::regex_search(line, wrongKeyPattern)) {
            return lineNumber;
        }
    }

    return std::nullopt;
}

} // namespace parsing
