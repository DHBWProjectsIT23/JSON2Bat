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
#include "FileData.hpp"
#include "JsonHandler.hpp"

class BatchCreator {
public:

    BatchCreator(std::shared_ptr<parsing::FileData> fileData);

    std::string batchFileString;
    std::shared_ptr<parsing::FileData> fileData;
    void writeBatch();

private:

    void writeStart();

    void writeHideShell();

    void writeCommand();
 
};