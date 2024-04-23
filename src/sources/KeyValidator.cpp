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
/** @todo Documentation */
std::vector<std::tuple<int, std::string>>
                                       KeyValidator::validateKeys(const Json::Value &root,
const std::string &filename) {
    std::vector<std::tuple<int, std::string>> wrongKeys =
            getWrongKeys(root, filename);

    for (Json::Value entries = root.get("entries", "");
            const auto &entry : entries) {
        std::vector<std::string> entryKeys = entry.getMemberNames();
        auto wrongEntries = validateEntries(filename, entryKeys);
        wrongKeys.insert(wrongKeys.end(), wrongEntries.begin(), wrongEntries.end());
        validateTypes(filename, entry, entryKeys);
    }

    return wrongKeys;
}

std::vector<std::tuple<int, std::string>>
KeyValidator::getWrongKeys(Json::Value root, const std::string &filename) {
    std::vector<std::tuple<int, std::string>> wrongKeys = {};

    for (std::vector<std::string> keys = root.getMemberNames();
            const auto &key : keys) {
        auto keyIterator = std::ranges::find(validKeys, key);

        if (keyIterator == validKeys.end()) {
            auto error = getUnknownKeyLine(filename, key);

            if (!error.has_value()) {
                LOG_ERROR << "Unable to find line of wrong key!";
                continue;
            }

            wrongKeys.emplace_back(error.value(), key);
        }
    }
    return wrongKeys;
}

/** @todo Documentation */
std::vector<std::tuple<int, std::string>>
                                       KeyValidator::validateEntries(const std::string &filename,
const std::vector<std::string> &entryKeys) {
    std::vector<std::tuple<int, std::string>> wrongKeys = {};

    for (const auto &key : entryKeys) {
        auto keyIterator = std::ranges::find(validEntryKeys, key);

        if (keyIterator == validEntryKeys.end()) {
            auto error = getUnknownKeyLine(filename, key);

            if (!error.has_value()) {
                LOG_ERROR << "Unable to find line of wrong key!";
                continue;
            }

            wrongKeys.emplace_back(error.value(), key);
        }
    }

    return wrongKeys;
}

/**
 * @todo Documentation
 * @todo Refactoring
 */
void KeyValidator::validateTypes(const std::string &filename,
                                 const Json::Value &entry,
                                 std::vector<std::string> &entryKeys) {
    std::string type = entry.get("type", "ERROR").asString();

    if (type == "EXE") {
        if (auto commandIterator = std::ranges::find(entryKeys, "command");
                commandIterator == entryKeys.end()) {
            exceptions::MissingKeyException("command", "EXE");
        }
    } else if (type == "PATH") {
        if (auto pathIterator = std::ranges::find(entryKeys, "path");
                pathIterator == entryKeys.end()) {
            exceptions::MissingKeyException("path", "PATH");
        }
    } else if (type == "ENV") {
        if (auto keyIterator = std::ranges::find(entryKeys, "key");
                keyIterator == entryKeys.end()) {
            exceptions::MissingKeyException("key", "ENV");
        }

        if (auto valueIterator = std::ranges::find(entryKeys, "value");
                valueIterator == entryKeys.end()) {
            exceptions::MissingKeyException("value", "ENV");
        }
    } else if (type == "ERROR") {
        exceptions::MissingTypeException();
    } else {
        std::optional<int> line = getUnknownKeyLine(filename, type);

        if (!line.has_value()) {
            LOG_INFO << "Unable to find line of wrong type!";
        }

        exceptions::InvalidTypeException(type, line.value());
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
