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

#include "BatchCreator.hpp"

BatchCreator::BatchCreator(std::shared_ptr<parsing::FileData> fileData){

}



void BatchCreator::writeBatch() {
    this->writeStart();
    this->writeHideShell();

}

void BatchCreator::writeStart() {
    this->batchFileString = this->batchFileString + "@ECHO OFF\nC:\\Windows\\System32\\cmd.exe ";
}
 
 void BatchCreator::writeHideShell() {
    if (this->fileData->getHideShell()){
        this->batchFileString = this->batchFileString + "/c\n";

    } else {
        this-> batchFileString = this->batchFileString + "/k\n";
    }
}

void BatchCreator::writeCommand() {
    this->batchFileString = this->batchFileString + "\"";
    for (const std::string command : this->fileData->getCommands()) {
        this->batchFileString = this->batchFileString + command + "&& \n";
    }
}