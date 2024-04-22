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
#include "LoggingWrapper.hpp"

BatchCreator::BatchCreator(std::shared_ptr<parsing::FileData> fileData){

}


void BatchCreator::createBatch() {
    LOG_INFO << "Creating Batch file";

    this->batchFile.open(this->fileData->getOutputFile());
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
    this->batchFile << "@ECHO OFF\nC:\\Windows\\System32\\cmd.exe ";
}
 
 void BatchCreator::writeHideShell() {
    if (this->fileData->getHideShell()){
        LOG_INFO << "writing hide Shell";
        this->batchFile << "/c \n";

    } else {
        LOG_INFO << "writing show Shell";
        this->batchFile << "/k \n";
    }
}

void BatchCreator::writeCommands() {
    LOG_INFO << "writing Commands";
    this->batchFile << "\"";
    for (const std::string command : this->fileData->getCommands()) {
        this->batchFile << command << "&& \n";
    }
}

void BatchCreator::writeEnvVariables() {
    LOG_INFO << "writing Environment Variables";
    for (const std::tuple env : this->fileData->getEnvironmentVariables()) {
        this->batchFile << "set " << std::get<0>(env) << "=" 
                        << std::get<1>(env) << " && \n";
    }
}

void BatchCreator::writePathVariables() {
    LOG_INFO << "writing Path Variables";
    this->batchFile << "set path=";
    for (const std::string path : this->fileData->getPathValues()) {
        this->batchFile << path << ";\n";
    }
    this->batchFile << "%path%";
}

void BatchCreator::writeApp() {
    std::string appName = this->fileData->getOutputFile();
    if (this->fileData->getApplication().has_value()) {
        LOG_INFO << "writing start Application";
        this->batchFile << " && \nstart \"" << appName << "\" \n" 
                        << this->fileData->getApplication().value() 
                        << "\"\n";
    } else {
        LOG_INFO << "writing not start Application";
        this->batchFile << "\"";
    }
}

void BatchCreator::writeEnd() {
    this->batchFile << "@ECHO ON";
}