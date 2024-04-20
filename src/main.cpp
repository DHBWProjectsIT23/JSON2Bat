/**
 * @file main.cpp
 * @author Elena Schwarzbach, Max Rodler, Simon Blum, Sonia Sinaci
 * @date 2024-04-18
 * @version 0.1.5
 * @brief Contains the main function.
 * @details
 * The main function is responsible for connection all parts of the programm.
 * It calls all relevant classes and finishes when everything is done.
 *
 * @license GNU GPLv3
 * @copyright See LICENSE file
 */
#include <LoggingWrapper.hpp>
#include "FileData.hpp"
#include "JsonParser.hpp"
#include <cstdlib>
#include <jsoncpp/json.h>
#include <vector>

#include "CommandLineHandler.hpp"
#include "Utils.hpp"

INITIALIZE_EASYLOGGINGPP

/* INFO:
 * Um logging zu verwenden:
 * "OUTPUT << ..." statt "std::cout < ..."
 * "DEBUG << ..." für temporäres - macht nichts anderes als Formatierung zu
 * "LOG_INFO << ..." um bspw. den Ablauf von Prozessen zu loggen
 * "LOG_WARNING << ..." um Warnungen zu loggen
 * "LOG_ERROR << ..." um Fehler zu loggen, bevor sie geworfen werden
 * ändern, hilft aber damit es auffällt, falls vergessen
 * OUTPUT, DEBUG, WARNING und ERROR werden automatisch auch in der Konsole
 * ausgegeben
 * -- Der Header <LoggingWrapper> muss includiert sein --
 */

/**
 * @brief Main function of the program
 * @details
 * The main function is responsible for connection all parts of the programm.
 * It calls all relevant classes and finishes when everything is done.
 * @param argc The number of arguments given
 * @param argv Th command line arguments given
 * @return Returns 0 on success, 1 on failure
 */
int main(int argc, char* argv[])
{
    // Setup easylogging++
    utilities::Utils::setupEasyLogging("conf/easylogging.conf");


    // Check if any options/arguments were given
    if (argc < 2) {
        LOG_ERROR << "No options given!\n";
        cli::CommandLineHandler::printHelp();
        return 1;
    }

    // Vector of all inputted file names
    std::vector<std::string> files =
        cli::CommandLineHandler::parseArguments(argc, argv);

    if (files.empty()) {
        LOG_ERROR << "No files were given as arguments!\n";
        return 1;
    }

    // Checking files
    for (const std::string &file : files) {
        // Checking if file exists
        if (!utilities::Utils::checkIfFileExists(file)) {
            LOG_ERROR << "The file \"" << file << "\" does not exist!";
            OUTPUT << "Exiting..." << std::endl;
            std::exit(1);
        }

        // Checking if file ends with ".json"
        if (!utilities::Utils::checkFileEnding(file)) {
            LOG_WARNING << "The file \"" << file
                        << "\" does not end in \".json\"\n";
            OUTPUT << "If the file is not in JSON Format, continuing may "
                   "result in\nunexpected behaviour!\n";

            // Asking user if they want to continue
            if (!utilities::Utils::askToContinue()) {
                OUTPUT << "Exiting...\n";
                LOG_INFO << "Application ended by user Input";
                std::exit(1);
            }
        }
    }

    // INFO: From here on out we can assume, that all strings in the
    // filename vector, lead to valid files!

    /* @TODO:
     * - Parse Files:
     *      - take file name or vector
     *        return data object
     *      - Verification?
     */
    /* @TODO:
     * - Create Batch File:
     *      - take data object and create file
     *        return ?
     */
    LOG_INFO << "Exiting...";
    return 0;
}
