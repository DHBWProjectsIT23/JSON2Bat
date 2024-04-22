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

    std::shared_ptr<parsing::FileData> fileData;

    std::string batchFileString; // Noch in Datei schreiben (shared_ptr?)
    void writeBatch(); // Datei als Rückgabewert?

private:

    void writeStart();

    void writeHideShell();
  
    void writeCommands();

    void writeEnvVariables();

    void writePathVariables();

    void writeApp(); // start "WAS"? Das gleiche wie in "outputfile" ohne ".bat"

    void writeEnd(); // brauch ich noch irgendwo n carriage return? wenn aj wo?


};
