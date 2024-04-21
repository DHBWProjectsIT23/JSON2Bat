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
