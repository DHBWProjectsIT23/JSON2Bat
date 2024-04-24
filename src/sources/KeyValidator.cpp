/**
 * @file KeyValidator.cpp
 * @author
 * @date
 * @version
 * @brief
 * @details
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
KeyValidator &KeyValidator::getInstance() {
    static KeyValidator keyValidator;
    LOG_INFO << "Returning KeyValidator instance!";
    return keyValidator;
}
std::vector<std::tuple<int, std::string>>
KeyValidator::validateKeys(const Json::Value &root,
                           const std::string &filename) {

    // Initiate vector , with wrong keys at top leve
    std::vector<std::tuple<int, std::string>> wrongKeys =
        getWrongKeys(root, filename);

    // Go through the entry keys
    for (Json::Value entries = root.get("entries", "");
            const auto &entry : entries) {

        // Retrieve all EntryKeys
        std::vector<std::string> entryKeys = entry.getMemberNames();

        // Add all invalid entries to an array
        auto wrongEntries = validateEntries(filename, entryKeys);

        // Append the invalid entries to the invalid keys
        wrongKeys.insert(wrongKeys.end(), wrongEntries.begin(), wrongEntries.end());

        // Validate that each entry has it's necessary keys
        validateTypes(filename, entry, entryKeys);
    }

    return wrongKeys;
}

std::vector<std::tuple<int, std::string>>
KeyValidator::getWrongKeys(const Json::Value &root,
                           const std::string &filename) {
    std::vector<std::tuple<int, std::string>> wrongKeys = {};

    // Go through each key at top level
    for (std::vector<std::string> keys = root.getMemberNames();
            const auto &key : keys) {
        // Iterator tries to find the key within the valid keys
        auto keyIterator = std::ranges::find(validKeys, key);

        // If the valid key isn't found, the iterator will be at the end
        if (keyIterator == validKeys.end()) {
            auto error = getUnknownKeyLine(filename, key);

            if (!error.has_value()) {
                LOG_ERROR << "Unable to find line of wrong key!";
                continue;
            }

            // Add the wrong key to the array
            wrongKeys.emplace_back(error.value_or(-1), key);
        }
    }
    return wrongKeys;
}

std::vector<std::tuple<int, std::string>>
KeyValidator::validateEntries(const std::string &filename,
                              const std::vector<std::string> &entryKeys) {
    std::vector<std::tuple<int, std::string>> wrongKeys = {};

    // Go through each key within the entries
    for (const auto &key : entryKeys) {
        // try to find the key within the valid entry keys
        auto keyIterator = std::ranges::find(validEntryKeys, key);

        // if the key isn't found, the iterator will be at the end
        if (keyIterator == validEntryKeys.end()) {
            auto error = getUnknownKeyLine(filename, key);

            if (!error.has_value()) {
                LOG_ERROR << "Unable to find line of wrong key!";
                continue;
            }

            // Add the wrong key to the array
            wrongKeys.emplace_back(error.value(), key);
        }
    }

    return wrongKeys;
}

void KeyValidator::validateTypes(const std::string &filename,
                                 const Json::Value &entry,
                                 std::vector<std::string> &entryKeys) {
    // Retrieve the type of the entry - ERROR if it can't be found
    std::string type = entry.get("type", "ERROR").asString();

    if (type == "EXE") {
        // Try to find the "command" key
        if (auto commandIterator = std::ranges::find(entryKeys, "command");
                commandIterator == entryKeys.end()) {
            throw exceptions::MissingKeyException("command", "EXE");
        }
    } else if (type == "PATH") {
        // Try to find the "path" key
        if (auto pathIterator = std::ranges::find(entryKeys, "path");
                pathIterator == entryKeys.end()) {
            throw exceptions::MissingKeyException("path", "PATH");
        }
    } else if (type == "ENV") {
        // Try to find the "key" key
        if (auto keyIterator = std::ranges::find(entryKeys, "key");
                keyIterator == entryKeys.end()) {
            throw exceptions::MissingKeyException("key", "ENV");
        }
        // Try to find the "value" key
        if (auto valueIterator = std::ranges::find(entryKeys, "value");
                valueIterator == entryKeys.end()) {
            throw exceptions::MissingKeyException("value", "ENV");
        }
    } else if (type == "ERROR") {
        // If the "type" key wasn't found, throw an error
        throw exceptions::MissingTypeException();
    } else {
        // If the type wasn't any of the above, it's invalid
        std::optional<int> line = getUnknownKeyLine(filename, type);

        if (!line.has_value()) {
            LOG_INFO << "Unable to find line of wrong type!";
        }

        throw exceptions::InvalidTypeException(type, line.value());
    }
}

std::optional<int>
KeyValidator::getUnknownKeyLine(const std::string &filename,
                                const std::string &wrongKey) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        LOG_ERROR << "File not open!";
    }

    int lineNumber = 1;
    std::string errorLine;
    std::regex wrongKeyPattern("\\b" + wrongKey + "\\b");

    // Go through each line of the file and search for the wrong key
    for (std::string line; std::getline(file, line);) {
        if (std::regex_search(line, wrongKeyPattern)) {
            errorLine = line;
            break;
        }

        ++lineNumber;
    }

    if (errorLine.empty()) {
        return std::nullopt;
    }

    return lineNumber;
}

} // namespace parsing
