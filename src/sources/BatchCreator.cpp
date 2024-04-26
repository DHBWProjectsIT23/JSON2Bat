/**
 * @file BatchCreator.cpp
 * @author Maximilian Rodler
 * @date 22.04.2024
 * @version 0.2.2
 * @brief Contains the implementation of the BatchCreator class.
 *
 * @see src/include/BatchCreator.hpp
 *
 * @copyright See LICENSE file
 */

#include "BatchCreator.hpp"

#include "LoggingWrapper.hpp"
#include <utility>

BatchCreator::BatchCreator(std::shared_ptr<parsing::FileData> fileData)
    : fileData(std::move(fileData)) {
    LOG_INFO << "Initializing BatchCreator";
    this->dataStream = std::make_shared<std::stringstream>();
    this->createBatch();
}

void BatchCreator::createBatch() const {
    LOG_INFO << "Creating Batch file";
    this->writeStart();
    this->writeHideShell();
    this->writeCommands();
    this->writeEnvVariables();
    this->writePathVariables();
    this->writeApplication();
    this->writeEnd();
}

void BatchCreator::writeStart() const {
    LOG_INFO << "writing Start of Batch";
    // {ReqFunc24} - \r\n
    *this->dataStream << "@ECHO OFF\r\nC:\\Windows\\System32\\cmd.exe ";
}

void BatchCreator::writeHideShell() const {
    if (this->fileData->getHideShell()) {
        LOG_INFO << "writing hide Shell";
        *this->dataStream << "/c ";
    }
    else {
        LOG_INFO << "writing show Shell";
        *this->dataStream << "/k ";
    }
}

void BatchCreator::writeCommands() const {
    LOG_INFO << "writing Commands";
    *this->dataStream << "\"";

    for (const std::string &command : this->fileData->getCommands()) {
        *this->dataStream << command << " && ";
    }
}

void BatchCreator::writeEnvVariables() const {
    LOG_INFO << "writing Environment Variables";

    for (const auto &[key, value] : this->fileData->getEnvironmentVariables()) {
        *this->dataStream << "set " << key << "=" << value << " && ";
    }
}

void BatchCreator::writePathVariables() const {
    LOG_INFO << "writing Path Variables";
    *this->dataStream << "set path=";

    for (const std::string &path : this->fileData->getPathValues()) {
        *this->dataStream << path << ";";
    }

    *this->dataStream << "%path%";
}

void BatchCreator::writeApplication() const {
    std::string appName = this->fileData->getOutputFile();
    appName = appName.substr(0, appName.find('.'));

    if (this->fileData->getApplication().has_value()) {
        LOG_INFO << "writing start Application";
        *this->dataStream << " && start \"" << appName
                          << "\" "
                          // {ReqFunc24} - \r\n
                          << this->fileData->getApplication().value() << "\"\r\n";
    }
    else {
        LOG_INFO << "writing not start Application";
        // {ReqFunc24} - \r\n
        *this->dataStream << "\"\r\n";
    }
}

void BatchCreator::writeEnd() const {
    *this->dataStream << "@ECHO ON";
}
