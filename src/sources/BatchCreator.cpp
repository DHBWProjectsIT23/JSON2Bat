/**
 * @file BatchCreator.hpp
 * @author Maximilian Rodler
 * @date 22.04.2024
 * @version
 * @brief Creates batch file
 * @details Creates batch file from Arguments in JSON
 *
 * @copyright See LICENSE file
 */

#include "BatchCreator.hpp"
#include "Exceptions.hpp"
#include "LoggingWrapper.hpp"

BatchCreator::BatchCreator(std::shared_ptr<parsing::FileData> fileData) {
    LOG_INFO << "Initializing BatchCreator";
    this->fileData = fileData;
    this->dataStream = std::make_shared<std::stringstream>();
    this->createBatch();
}

void BatchCreator::createBatch() {
    LOG_INFO << "Creating Batch file";

    this->writeStart();
    this->writeHideShell();
    this->writeCommands();
    this->writeEnvVariables();
    this->writePathVariables();
    this->writeApp();
    this->writeEnd();
}

void BatchCreator::writeStart() {
    LOG_INFO << "writing Start of Batch";
    *this->dataStream << "@ECHO OFF\r\nC:\\Windows\\System32\\cmd.exe ";
}

void BatchCreator::writeHideShell() {
    if (this->fileData->getHideShell()) {
        LOG_INFO << "writing hide Shell";
        *this->dataStream << "/c ";

    } else {
        LOG_INFO << "writing show Shell";
        *this->dataStream << "/k ";
    }
}

void BatchCreator::writeCommands() {
    LOG_INFO << "writing Commands";
    *this->dataStream << "\"";
    for (const std::string &command : this->fileData->getCommands()) {
        *this->dataStream << command << " && ";
    }
}

void BatchCreator::writeEnvVariables() {
    LOG_INFO << "writing Environment Variables";
    for (const std::tuple env : this->fileData->getEnvironmentVariables()) {
        *this->dataStream << "set " << std::get<0>(env) << "=" << std::get<1>(env)
                          << " && ";
    }
}

void BatchCreator::writePathVariables() {
    LOG_INFO << "writing Path Variables";
    *this->dataStream << "set path=";
    for (const std::string &path : this->fileData->getPathValues()) {
        *this->dataStream << path << ";";
    }
    *this->dataStream << "%path%";
}

void BatchCreator::writeApp() {
    std::string appName = this->fileData->getOutputFile();
    appName = appName.substr(0, appName.find("."));
    if (this->fileData->getApplication().has_value()) {
        LOG_INFO << "writing start Application";
        *this->dataStream << " && start \"" << appName << "\" "
                          << this->fileData->getApplication().value() << "\"\r\n";
    } else {
        LOG_INFO << "writing not start Application";
        *this->dataStream << "\"\r\n";
    }
}

void BatchCreator::writeEnd() {
    *this->dataStream << "@ECHO ON";
}
