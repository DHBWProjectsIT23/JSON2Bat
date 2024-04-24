/**
 * @file FileData.cpp
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 * @copyright See LICENSE file
 */

#include "FileData.hpp"
#include "Exceptions.hpp"
#include "LoggingWrapper.hpp"

namespace parsing {
void FileData::setOutputFile(std::string &newOutputfile)
{
    LOG_INFO << "Setting outputfile to...";

    // If no value for key "outputfile"
    if (newOutputfile.empty()) {
        LOG_INFO << "Escalating error to ErrorHandler::invalidValue!";
        throw exceptions::InvalidValueException("outputfile", "Outputfile can't be empty!");
    }

    // If outputfile is already set
    if (!this->outputfile.empty()) {
        LOG_INFO << "Escalating error to ErrorHandler::invalidValue!";
        throw exceptions::InvalidValueException("outputfile", "Outputfile is already set!");
    }

    // If outputfile does not end with ".bat"
    if (!newOutputfile.ends_with(".bat")) {
        newOutputfile += ".bat";
        LOG_WARNING << "Outputfile does not end with \".bat\", adding it now: "
                    << newOutputfile;
    }

    this->outputfile = newOutputfile;
    LOG_INFO << "Outputfile set to: " << this->outputfile << "\n";
}

void FileData::setApplication(const std::string &newApplication)
{
    if (newApplication.empty()) {
        LOG_INFO << "newApplication empty, returning";
        return;
    }

    LOG_INFO << "Setting application to: " << newApplication << "\n";
    this->application.emplace(newApplication);
}

void FileData::addCommand(const std::string &command)
{
    if (command.empty()) {
        LOG_INFO << "Escalating error to ErrorHandler::invalidValue!";
        throw exceptions::InvalidValueException("command", "Command value is empty!");
    }

    LOG_INFO << "Adding command: " << command << "\n";
    this->commands.push_back(command);
}

void FileData::addEnvironmentVariable(const std::string &name,
                                      const std::string &value)
{
    if (name.empty()) {
        LOG_INFO << "Escalating error to ErrorHandler::invalidValue!";
        throw exceptions::InvalidValueException("name", "Name value is empty!");
    }

    if (value.empty()) {
        LOG_INFO << "Escalating error to ErrorHandler::invalidValue!";
        throw exceptions::InvalidValueException("key", "Key value is empty");
    }

    LOG_INFO << "Adding environment variable: " << name << "=" << value << "\n";
    this->environmentVariables.emplace_back(name, value);
}

void FileData::addPathValue(const std::string &pathValue)
{
    if (pathValue.empty()) {
        LOG_INFO << "Escalating error to ErrorHandler::invalidValue!";
        throw exceptions::InvalidValueException("path", "Path value is empty");
    }

    LOG_INFO << "Adding path value: " << pathValue << "\n";
    this->pathValues.push_back(pathValue);
}
} // namespace parsing
