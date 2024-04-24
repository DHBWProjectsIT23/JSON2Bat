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
 * @copyright See LICENSE file
 */
#include <LoggingWrapper.hpp>
#include <cstdlib>
#include <fstream>
#include <jsoncpp/json.h>
#include <vector>

#include "BatchCreator.hpp"
#include "CommandLineHandler.hpp"
#include "Exceptions.hpp"
#include "FileData.hpp"
#include "JsonHandler.hpp"
#include "Utils.hpp"
#include "config.hpp"

INITIALIZE_EASYLOGGINGPP

/**
 * @brief
 * @details
 *
 * @param files
 * @return
 */
std::vector<std::string> validateFiles(std::vector<std::string> files);

/**
 * @brief
 * @details
 *
 * @param files
 */
void parseFiles(std::vector<std::string> files);

/**
 * @brief Main function of the program
 * @details
 * The main function is responsible for connection all parts of the programm.
 * It calls all relevant classes and finishes when everything is done.
 *
 * @param argc The number of arguments given
 * @param argv Th command line arguments given
 *
 * @return Returns 0 on success, 1 on failure
 *
 * @todo Documentation
 * @todo Refactoring
 */
int main(int argc, char *argv[]) {
    std::ifstream configFile(LOG_CONFIG);
    if (!configFile.good()) {
        std::cerr << cli::RED << cli::BOLD
                  << "Fatal: Easylogging configuration file not found at:\n"
                  << cli::RESET << cli::ITALIC << "\n\t\"" << LOG_CONFIG << "\"\n\n"
                  << cli::RESET;

        std::cout << "Aborting...\n";
        return 1;
    }

    utilities::Utils::setupEasyLogging(LOG_CONFIG);

    // Check if any options/arguments were given
    if (argc < 2) {
        LOG_ERROR << "No options given!\n";
        cli::CommandLineHandler::printHelp();
    }

    // Vector of all inputted file names
    std::vector<std::string> files =
        cli::CommandLineHandler::parseArguments(argc, argv);

    if (files.empty()) {
        LOG_ERROR << "No files were given as arguments!\n";
        return 1;
    }
    OUTPUT << cli::BOLD << "Parsing the following files:\n" << cli::RESET;
    for (const auto &file : files) {
        OUTPUT << "\t - " << file << "\n";
    }

    // Replace the original files vector with the validFiles vector
    files = std::move(validateFiles(files));
    parseFiles(files);

    LOG_INFO << "Exiting...";
    return 0;
}

std::vector<std::string> validateFiles(std::vector<std::string> files) {
    std::vector<std::string> validFiles;

    for (const auto &file : files) {
        if (!utilities::Utils::checkIfFileExists(file)) {
            LOG_ERROR << "The file \"" << file << "\" does not exist!\n";

            if (files.size() != 1 &&
                    !utilities::Utils::askToContinue("Do you want to continue with the "
                            "remaining files? (y/n) ")) {
                // Exit if it's the only file or the user does not want to
                // continue
                OUTPUT << "Aborting...\n";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }

            continue;
        }

        if (!utilities::Utils::checkFileEnding(file)) {
            LOG_WARNING << "The file \"" << file << "\" does not end in \".json\"\n";
            OUTPUT << "If the file is not in JSON Format, continuing may "
                   "result in\nunexpected behaviour!\n";

            if (!utilities::Utils::askToContinue()) {
                OUTPUT << "Aborting...\n";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }
        }

        validFiles.push_back(file);
    }

    return validFiles;
}

void parseFiles(std::vector<std::string> files) {

    for (auto file = files.begin(); file != files.end(); ++file) {
        OUTPUT << cli::ITALIC << "\nParsing file: " << *file << "...\n"
               << cli::RESET;

        std::shared_ptr<parsing::FileData> fileData;
        try {
            parsing::JsonHandler jsonHandler(*file);
            fileData = jsonHandler.getFileData();
            BatchCreator batchCreator(fileData);
        } catch (const exceptions::CustomException &e) {
            OUTPUT << "\nThere has been a error while trying to parse \"" << *file
                   << ":\n";
            LOG_ERROR << e.what();

            if (std::next(file) != files.end() &&
                    !utilities::Utils::askToContinue(
                        "Do you want to continue with the other files? (y/n) "
                        "")) {
                OUTPUT << "Aborting...";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }

            std::cout << "\n";
            continue;
        }
    }
    OUTPUT << cli::ITALIC << "Done with files!\n" << cli::RESET;
}
