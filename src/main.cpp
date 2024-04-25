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
#include <filesystem>
#include <fstream>
#include <jsoncpp/json.h>
#include <tuple>
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
 * @return
 */
void checkConfigFile();

/**
 * @brief
 * @details
 *
 * @param argc
 * @param argv
 * @return
 */
std::tuple<std::vector<std::string>, std::string>
parseAndValidateArgs(int argc, char *argv[]);

/**
 * @brief
 * @details
 *
 * @param files
 * @return
 */
std::vector<std::string> validateFiles(const std::vector<std::string> &files);

/**
 * @brief
 * @details
 *
 * @param file
 */
void parseFile(const std::string &file, const std::string &outDir);

/**
 * @brief Main function of the program
 * @details
 * The main function is responsible for connection all parts of the
 * programm. It calls all relevant classes and finishes when everything is
 * done.
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

    checkConfigFile();
    utilities::Utils::setupEasyLogging(LOG_CONFIG);
    auto [files, outDir] = parseAndValidateArgs(argc, argv);
    OUTPUT << cli::BOLD << "Parsing the following files:\n" << cli::RESET;
    for (const auto &file : files) {
        OUTPUT << "\t - " << file << "\n";
    }

    files = validateFiles(files);
    for (auto file = files.begin(); file != files.end(); ++file) {
        OUTPUT << cli::ITALIC << "\nParsing file: " << *file << "...\n"
               << cli::RESET;
        try {
            parseFile(*file, outDir);
        } catch (const exceptions::CustomException &e) {
            if (utilities::Utils::handleParseException(e, file, files)) {
                continue;
            }
            exit(1);
        }
    }
    LOG_INFO << "Exiting...";
    return 0;
}

void checkConfigFile() {
    if (!std::filesystem::is_regular_file(LOG_CONFIG)) {
        std::cerr << cli::RED << cli::BOLD
                  << "Fatal: Easylogging configuration file not found at:\n"
                  << cli::RESET << cli::ITALIC << "\n\t\"" << LOG_CONFIG << "\"\n\n"
                  << cli::RESET;
        std::cout << "Aborting...\n";
        exit(1);
    }
}

std::tuple<std::vector<std::string>, std::string>
parseAndValidateArgs(int argc, char *argv[]) {
    if (argc < 2) {
        LOG_ERROR << "No options given!\n";
        cli::CommandLineHandler::printHelp();
        exit(1);
    }
    auto [outOption, files] = cli::CommandLineHandler::parseArguments(argc, argv);
    std::string outDir = outOption.value_or("");
    if (!outDir.empty()) {
        try {
            outDir = utilities::Utils::checkDirectory(outDir);
        } catch (const exceptions::CustomException &e) {
            LOG_ERROR << e.what();
            exit(1);
        }
    }
    if (files.empty()) {
        LOG_ERROR << "No files were given as arguments!\n";
        exit(1);
    }
    return {files, outDir};
}

std::vector<std::string> validateFiles(const std::vector<std::string> &files) {
    std::vector<std::string> validFiles;
    validFiles.reserve(files.size());
    for (const std::filesystem::path file : files) {
        if (!std::filesystem::is_regular_file(file)) {
            LOG_ERROR << "The file \"" << file << "\" does not exist!\n";
            if (files.size() > 1 &&
                    !utilities::Utils::askToContinue("Do you want to continue with the "
                            "remaining files? (y/n) ")) {
                OUTPUT << "Aborting...\n";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }
            continue;
        }
        if (file.extension() != ".json") {
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

void parseFile(const std::string &file, const std::string &outputDirectory) {
    parsing::JsonHandler jsonHandler(file);
    auto fileData = jsonHandler.getFileData();
    BatchCreator batchCreator(fileData);
    std::shared_ptr<std::stringstream> dataStream = batchCreator.getDataStream();
    std::string outputFileName = outputDirectory + fileData->getOutputFile();
    std::ofstream outFile(outputFileName);
    if (!outFile.good()) {
        throw exceptions::FailedToOpenFileException(outputFileName);
    }
    outFile << dataStream->str();
    OUTPUT << "Done with files!\n";
}
