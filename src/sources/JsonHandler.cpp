/**
 * @file JsonHandler.cpp
 * @author Elena Schwarzbach, Sonia Sinacci
 * @date 2024-04-16
 * @version 0.1.6
 * @brief Implementation of the JsonHandler class.
 *
 * @see src/include/JsonHandler.hpp
 *
 * @copyright See LICENSE file
 */

#include "JsonHandler.hpp"
#include "Exceptions.hpp"
#include "FileData.hpp"
#include "KeyValidator.hpp"
#include "LoggingWrapper.hpp"
#include "Utils.hpp"

#include <algorithm>

namespace parsing {
JsonHandler::JsonHandler(const std::string &filename) {
    LOG_INFO << "Initializing JSONHandler with filename: " << filename << "\n";
    this->root = parseFile(filename);
}

std::shared_ptr<Json::Value> JsonHandler::parseFile(const std::string &filename)

{
    LOG_INFO << "Parsing file: " << filename << "\n";
    // Can open files anywhere with relative/absolute path
    // - {ReqFunc5}
    std::ifstream file(filename);
    Json::Value newRoot;

    // Json::Reader.parse() returns false if parsing fails
    if (Json::Reader reader; !reader.parse(file, newRoot)) {
        throw exceptions::ParsingException(filename);
    }

    // Validate keys
    // Check for errors
    if (auto errors = KeyValidator::getInstance().validateKeys(newRoot, filename);
            !errors.empty()) {
        throw exceptions::InvalidKeyException(errors);
    }

    LOG_INFO << "File \"" << filename << "\" has been parsed\n";
    return std::make_shared<Json::Value>(newRoot);
}

std::shared_ptr<FileData> JsonHandler::getFileData() {
    LOG_INFO << "Creating FileData object for return...\n";
    return this->createFileData();
}

std::shared_ptr<FileData> JsonHandler::createFileData() {
    LOG_INFO << "Creating FileData object...\n";
    this->data = std::make_shared<FileData>();
    this->assignOutputFile();
    this->assignHideShell();
    this->assignApplication();
    this->assignEntries();
    return this->data;
}

void JsonHandler::assignOutputFile() const {
    LOG_INFO << "Assigning outputfile...\n";
    std::string outputFile = this->root->get("outputfile", "").asString();
    if (containsBadCharacter(outputFile)) {
        outputFile = utilities::Utils::escapeString(outputFile);
        throw exceptions::ContainsBadCharacterException(outputFile);
    }
    this->data->setOutputFile(outputFile);
}

void JsonHandler::assignHideShell() const {
    LOG_INFO << "Assigning hide shell...\n";
    // If the 'hideshell' key is not given, it defaults to false
    this->data->setHideShell(this->root->get("hideshell", false).asBool());
}

void JsonHandler::assignApplication() const {
    LOG_INFO << "Assigning application...\n";
    std::string application = this->root->get("application", "").asString();
    if (containsBadCharacter(application)) {
        application = utilities::Utils::escapeString(application);
        throw exceptions::ContainsBadCharacterException(application);
    }
    this->data->setApplication(application);
}

void JsonHandler::assignEntries() const {
    LOG_INFO << "Assigning entries...\n";

    for (const auto &entry : this->root->get("entries", "")) {
        std::string entryType = entry.get("type", "").asString();

        if (entryType == "EXE") {
            LOG_INFO << "Calling function to assign command...\n";
            this->assignCommand(entry);
        } else if (entryType == "ENV") {
            LOG_INFO << "Calling function to assign environment variable...\n";
            this->assignEnvironmentVariable(entry);
        } else if (entryType == "PATH") {
            LOG_INFO << "Calling function to assign path value...\n";
            this->assignPathValue(entry);
        } else {
            // Due to validation beforehand - this should never be reached!
            throw exceptions::UnreachableCodeException(
                "Unknown entries should be caught by KeyValidator!\nPlease report "
                "this bug!");
        }
    }
}

void JsonHandler::assignCommand(const Json::Value &entry) const {
    LOG_INFO << "Assigning command...\n";
    std::string command = entry.get("command", "").asString();
    if (containsBadCharacter(command)) {
        command = utilities::Utils::escapeString(command);
        throw exceptions::ContainsBadCharacterException(command);
    }
    this->data->addCommand(command);
}

void JsonHandler::assignEnvironmentVariable(const Json::Value &entry) const {
    LOG_INFO << "Assigning environment variable...\n";
    std::string key = entry.get("key", "").asString();
    std::string value = entry.get("value", "").asString();

    if (containsBadCharacter(key)) {
        key = utilities::Utils::escapeString(key);
        throw exceptions::ContainsBadCharacterException(key);
    }
    if (containsBadCharacter(value)) {
        value = utilities::Utils::escapeString(value);
        throw exceptions::ContainsBadCharacterException(value);
    }
    this->data->addEnvironmentVariable(key, value);
}

void JsonHandler::assignPathValue(const Json::Value &entry) const {
    LOG_INFO << "Assigning path value...\n";
    std::string path = entry.get("path", "").asString();
    if (containsBadCharacter(path)) {
        path = utilities::Utils::escapeString(path);
        throw exceptions::ContainsBadCharacterException(path);
    }
    this->data->addPathValue(path);
}

bool JsonHandler::containsBadCharacter(const std::string_view &str) {

    // Set of characters which may not be in the string
    static const std::unordered_set<char> badChars = {
        '\n', '\t', '\r', '\0', '\x1A', '|', ';', '<', '>', '!', '%', '"', '\''
    };

    // Lambda function which returns true, if the char is bad
    auto isBadCharacter = [](char c) {
        return badChars.contains(c);
    };

    return std::any_of(str.begin(), str.end(), isBadCharacter);
}
} // namespace parsing
