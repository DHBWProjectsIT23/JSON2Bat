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
    this->data->setOutputFile(outputFile);
}

void JsonHandler::assignHideShell() const {
    LOG_INFO << "Assigning hide shell...\n";
    // If the 'hideshell' key is not given, it defaults to false
    this->data->setHideShell(this->root->get("hideshell", false).asBool());
}

void JsonHandler::assignApplication() const {
    LOG_INFO << "Assigning application...\n";
    this->data->setApplication(this->root->get("application", "").asString());
}

void JsonHandler::assignEntries() const {
    LOG_INFO << "Assigning entries...\n";

    for (const auto &entry : this->root->get("entries", "")) {
        std::string entryType = entry.get("type", "").asString();

        if (entryType == "EXE") {
            LOG_INFO << "Calling function to assign command...\n";
            this->assignCommand(entry);
        }
        else if (entryType == "ENV") {
            LOG_INFO << "Calling function to assign environment variable...\n";
            this->assignEnvironmentVariable(entry);
        }
        else if (entryType == "PATH") {
            LOG_INFO << "Calling function to assign path value...\n";
            this->assignPathValue(entry);
        }
        else {
            // Due to validation beforehand - this should never be reached!
            throw exceptions::UnreachableCodeException(
                        "Unknown entries should be caught by KeyValidator!\nPlease report "
                        "this bug!");
        }
    }
}

void JsonHandler::assignCommand(const Json::Value &entry) const {
    LOG_INFO << "Assigning command...\n";
    this->data->addCommand(entry.get("command", "").asString());
}

void JsonHandler::assignEnvironmentVariable(const Json::Value &entry) const {
    LOG_INFO << "Assigning environment variable...\n";
    std::string key = entry.get("key", "").asString();
    std::string value = entry.get("value", "").asString();
    this->data->addEnvironmentVariable(key, value);
}

void JsonHandler::assignPathValue(const Json::Value &entry) const {
    LOG_INFO << "Assigning path value...\n";
    this->data->addPathValue(entry.get("path", "").asString());
}
} // namespace parsing
