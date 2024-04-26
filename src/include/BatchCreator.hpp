/**
 * @file BatchCreator.hpp
 * @author Maximilian Rodler
 * @date 2024-04-22
 * @version 0.2.1
 * @brief Contains the BatchCreator class.
 *
 * @see BatchCreator
 *
 * @see src/sources/BatchCreator.cpp
 *
 * @copyright See LICENSE file
 *
 */

#include "FileData.hpp"
#include <memory>
#include <sstream>

/**
 * @class BatchCreator
 * @brief Creates a batch file from a FileData obeject
 * @details
 * Uses a FileData object to create a string stream, which can then
 * be streamed into a batch file.
 *
 * @see FileData
 */
class BatchCreator {
  public:
    /**
     * @brief Initializes the BatchCreator
     * @details
     * Creates a stringstream and calls the createBatch() function
     *
     * @param filenData A shared pointer to the FileData object
     *
     */
    explicit BatchCreator(std::shared_ptr<parsing::FileData> fileData);

    /**
     * @brief Returns the stringstream
     *
     * @return A shared pointer to the stringstream
     */
    [[nodiscard]] std::shared_ptr<std::stringstream> getDataStream() const {
        return dataStream;
    }

  private:
    std::shared_ptr<std::stringstream>
    dataStream; /** < stringstream for the batch file */

    std::shared_ptr<parsing::FileData> fileData; /** < FileData object */

    /**
     * @brief Creates the batch stream
     * @details
     * The method calls all necessary functions to create the stream for the batch
     * file.
     *
     */
    void createBatch();

    /**
     * @brief Wirtes the start of the batch file
     * @details
     * Writes the start of the batch file, which is always the same:
     * - setzt ECHO off
     * - startet cmd.exe
     *
     */
    void writeStart() const;

    /**
     * @brief Writes the visibility of the shell
     * @details
     * This hides/shows the shell after the batch file has been executed
     * - {ReqFunc19}
     *
     */
    void writeHideShell() const;

    /**
     * @brief Writes the commands to be executed
     * @details
     * Writes the commands to be executed from the FileData object.
     * Those originiate from the "commands" entry in the json file
     * - {ReqFunc20}
     * - {ReqFunc22}
     *
     */
    void writeCommands() const;

    /**
     * @brief Set's environment variables
     * @details
     * Set's the envirment variables for the batch.
     * Those originiate from the "ENV" entry in the json file with
     * the following syntax:
     * - Entry under "key" = Entry under "value"
     * - {ReqFunc20}
     * - {ReqFunc21}
     *
     */
    void writeEnvVariables() const;

    /**
     * @brief Set's the path variables
     * @details Set's the path variables for the batch.
     * Those originiate from the "PATH" entry in the json file
     * - {ReqFunc20}
     * - {ReqFunc23}
     *
     */
    void writePathVariables() const;

    /**
     * @brief If an application is given, it is started at the end
     * @details
     * If the key "application" is given in the json file, the application
     * is started at the end of the batch file.
     * - {ReqFunc16}
     * - {ReqFunc25}
     *
     */
    void writeApplication() const;

    /**
     * @brief Writes the end of the batch file
     * @details
     * Writes the end of the batch file, which is always the same:
     * - @ECHO ON
     *
     */
    void writeEnd() const;
};
