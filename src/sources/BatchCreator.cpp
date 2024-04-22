/**
 * @file BatchCreator.hpp
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 * @copyright See LICENSE file
 */

#include "BatchCreator.hpp"
#include "LoggingWrapper.hpp" // Logs noch einfügen!!!

BatchCreator::BatchCreator(std::shared_ptr<parsing::FileData> fileData) {

}

void BatchCreator::writeBatch() {
    this->writeStart();
    this->writeHideShell();
    this->writeCommands();
    this->writeEnvVariables();
    this->writePathVariables();
    this->writeApp();
    this->writeEnd();

}

void BatchCreator::writeStart() {
    this->batchFileString = this->batchFileString + "@ECHO OFF\nC:\\Windows\\System32\\cmd.exe ";
}
 
 void BatchCreator::writeHideShell() {
    if (this->fileData->getHideShell()){
        this->batchFileString = this->batchFileString + "/c \n";
    } else {
        this-> batchFileString = this->batchFileString + "/k \n";
    }
}

void BatchCreator::writeCommands() {
    this->batchFileString = this->batchFileString + "\"";
    for (const std::string command : this->fileData->getCommands()) {
        this->batchFileString = this->batchFileString + command + "&& \n";
    }
}

void BatchCreator::writeEnvVariables() {
    for (const std::tuple env : this->fileData->getEnvironmentVariables()) {
        this->batchFileString += "set " + std::get<0>(env) + "=" + std::get<1>(env) + " && \n";
    }
}

void BatchCreator::writePathVariables() {
    this->batchFileString += "set path=";
    for (const std::string path : this->fileData->getPathValues()) {
        this->batchFileString += path + ";\n";
    }
    this->batchFileString += "%path%";
}

void BatchCreator::writeApp() {
    if (this->fileData->getApplication().has_value()) {
        this->batchFileString += " && \nstart ?WAS HIER? \n" + this->fileData->getApplication().value() + "\"\n"; //start WAS?
    } else {
        this->batchFileString +"\"";
    }
}

void BatchCreator::writeEnd() {
    this->batchFileString += "@ECHO ON";
}