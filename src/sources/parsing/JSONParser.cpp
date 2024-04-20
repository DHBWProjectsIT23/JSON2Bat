/**
 * @file
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 *
 * @license GNU GPLv3
 * @copyright See LICENSE file
 */

#include "JSONParser.hpp"
#include "FileData.hpp"
#include "LoggingWrapper.hpp"

#include <json/json.h>

namespace proJson {
JsonHandler::JsonHandler(const std::string &filename)
{
    LOG_INFO << "Initializing JSONHandler with filename: " << filename << "\n";
    this->root = parseFile(filename);
}

std::shared_ptr<Json::Value> JsonHandler::parseFile(const std::string &filename)
const
{
    LOG_INFO << "Parsing file: " << filename << "\n";
    std::ifstream file(filename);
    Json::Value newRoot;
    Json::Reader reader;

    if (!reader.parse(file, newRoot)) {
        LOG_ERROR << "Failed to parse file: " << filename << "\n";
        exit(1);
    }

    LOG_INFO << "File parsed\n";
    return std::make_shared<Json::Value>(newRoot);
}

std::shared_ptr<JsonData> JsonHandler::getJSONData()
{
    LOG_INFO << "Creating JSONData object for return...\n";
    return this->createJSONData();
}

std::shared_ptr<JsonData> JsonHandler::createJSONData()
{
    LOG_INFO << "Creating JSONData object...\n";
    this->data = std::make_shared<JsonData>();
    this->assignOutputFile();
    this->assignHideShell();
    this->assignApplication();
    this->assignEntries();
    return this->data;
}

void JsonHandler::assignOutputFile() const
{
    LOG_INFO << "Assigning outputfile...\n";
    std::string outputFile = this->root->get("outputfile", "").asString();
    this->data->setOutputFile(outputFile);
}

void JsonHandler::assignHideShell() const
{
    LOG_INFO << "Assigning hide shell...\n";
    bool hideShell = this->root->get("hideshell", false).asBool();
    this->data->setHideShell(hideShell);
}

void JsonHandler::assignApplication() const
{
    LOG_INFO << "Assigning application...\n";
    std::string application = this->root->get("application", "").asString();
    this->data->setApplication(application);
}

void JsonHandler::assignEntries() const
{
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
            LOG_ERROR << "Unknown entry type: " << entryType << "\n";
            throw std::invalid_argument("Unknown entry type");
        }
    }
}

void JsonHandler::assignCommand(const Json::Value &entry) const
{
    LOG_INFO << "Assigning command...\n";
    std::string command = entry.get("command", "").asString();
    this->data->addCommand(command);
}

void JsonHandler::assignEnvironmentVariable(const Json::Value &entry) const
{
    LOG_INFO << "Assigning environment variable...\n";
    std::string key = entry.get("key", "").asString();
    std::string value = entry.get("value", "").asString();
    this->data->addEnvironmentVariable(key, value);
}

void JsonHandler::assignPathValue(const Json::Value &entry) const
{
    LOG_INFO << "Assigning path value...\n";
    std::string pathValue = entry.get("path", "").asString();
    this->data->addPathValue(pathValue);
}
} // namespace json
