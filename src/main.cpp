/**
 * @file main.cpp
 * @author Elena Schwarzbach, Max Rodler, Simon Blum, Sonia Sinaci
 * @date 2024-04-26
 * @version 0.2.2
 * @brief Contains the main function.
 * @details
 * The main function is responsible for connection all parts of the programm.
 * It calls all relevant classes and finishes when everything is done.
 * - {ReqOptFunc3} - Documentation is done using doxygen syntax
 * - {ReqOptFunc3} - All Classes, methods, funciton, namespaces and file are
 * documented
 * - {ReqNonFunc5} - Source files are found under src/sources, header under
 * src/include
 * - {ReqNonFunc6} - All header files can be included withou paths
 * - {ReqNonFunc7} - Non source files are included
 * - {ReqNonFunc8} - All header files include a "ifndef/define/endif" block
 * - {ReqOptFunc5} - Every file has a top comment including the authors
 * - {ReqOptFunc6} - Logging is done using easylogging++ library
 *                 - A self written wrapper is used, to allow for parallel
 * output to the stdout and the logfile. Though we don't consider this wrapper
 * part of the project itself and as such is placed within the directorys for
 * external libraries
 * - Formatting is done via astyle
 * - !{ReqOptFunc7} - No unit tests are included
 *
 * @copyright See LICENSE file
 */
#include <LoggingWrapper.hpp>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <tuple>
#include <vector>

#include "BatchCreator.hpp"
#include "CommandLineHandler.hpp"
#include "Exceptions.hpp"
#include "JsonHandler.hpp"
#include "Utils.hpp"
#include "config.hpp"

/**
 * @brief Validates and parses arguments
 *
 * @param argc Number of arguments provided
 * @param argv The arguments provided
 * @return A tuple containing the files to be parsed and the output directory
 */
std::tuple<std::vector<std::string>, std::string>
parseAndValidateArgs(int argc, char *argv[]);

/**
 * @brief Checks if the files are valid
 * @details
 * Makes sures, that provided files exists and checks their file ending
 * @param files The files to be checked
 * - {ReqFunc5}
 *
 * @return A vector containing the valid files
 */
std::vector<std::string> validateFiles(const std::vector<std::string> &files);

/**
 * @brief Parses the given file and writes the output to the output directory
 * @details
 * Creates the Batch file from the given file
 * @param file The file to be parsed
 */
void parseFile(const std::string &file, const std::string &outputDirectory);

/**
 * @brief Main function of the program
 * @details
 * The main function is responsible for connection all parts of the
 * programm. It calls all relevant classes and finishes when everything is
 * done.
 *
 * @param argc The number of arguments given
 * @param argv The command line arguments given
 *
 * @return Returns 0 on success, 1 on failure
 *
 */
int main(int argc, char *argv[]) {
    // Setup logging
    utilities::Utils::checkConfigFile(config::LOG_CONFIG);
    utilities::Utils::setupEasyLogging(config::LOG_CONFIG);
    // Parse and validate arguments
    auto [files, outDir] = parseAndValidateArgs(argc, argv);
    OUTPUT << cli::BOLD << "Parsing the following files:\n" << cli::RESET;

    for (const auto &file : files) {
        OUTPUT << "\t - " << file << "\n";
    }

    files = validateFiles(files);

    // Loop for {ReqFunc7}
    for (auto file = files.begin(); file != files.end(); ++file) {
        OUTPUT << cli::ITALIC << "\nParsing file: " << *file << "...\n"
               << cli::RESET;

        try {
            parseFile(*file, outDir);
            // Only catch custom exceptions, other exceptions are fatal
        } catch (const exceptions::CustomException &e) {
            LOG_INFO << "Caught custom exception: " << typeid(e).name();
            if (utilities::Utils::handleParseException(e, file, files)) {
                continue;
            }

            exit(1);
        } catch (const Json::Exception &e) {
            LOG_INFO << "Caught Json exception: " << typeid(e).name();
            if (utilities::Utils::handleParseException(e, file, files)) {
                continue;
            }

            exit(1);
        }

    }
    OUTPUT << "Done parsing files!\n";

    LOG_INFO << "Exiting...";
    return 0;
}

std::tuple<std::vector<std::string>, std::string>
parseAndValidateArgs(int argc, char *argv[]) {
    if (argc < 2) {
        LOG_ERROR << "No options given!";
        cli::CommandLineHandler::printHelp();
    }

    auto [outOption, files] = cli::CommandLineHandler::parseArguments(argc, argv);
    // Set the output directory if given
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
        LOG_ERROR << "No files were given as arguments!";
        exit(1);
    }

    return {files, outDir};
}

std::vector<std::string> validateFiles(const std::vector<std::string> &files) {
    std::vector<std::string> validFiles;
    // Reserve space, to avaid reallocating with each valid file
    validFiles.reserve(files.size());

    for (const std::filesystem::path file : files) {
        // Check that the file exists
        // {ReqFunc5}
        if (!std::filesystem::is_regular_file(file)) {
            LOG_ERROR << "The file \"" << file << "\" does not exist!";

            if (files.size() > 1 && !utilities::Utils::askToContinue()) {
                OUTPUT << "Aborting...\n";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }

            continue;
        }

        // Check if the file ends in .json
        if (file.extension() != ".json") {
            LOG_WARNING << "The file \"" << file << R"(" does not end in ".json")";
            OUTPUT << "If the file is not in JSON Format, continuing may "
                   "result in\nunexpected behaviour!\n";

            if (!utilities::Utils::askToContinue()) {
                OUTPUT << "Aborting...\n";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }
        }

        validFiles.push_back(file.string());
    }

    // Shrinks the vector if invalid files were found
    validFiles.shrink_to_fit();
    return validFiles;
}

void parseFile(const std::string &file, const std::string &outputDirectory) {
    parsing::JsonHandler jsonHandler(file);
    const auto fileData = jsonHandler.getFileData();
    BatchCreator batchCreator(fileData);
    const std::shared_ptr<std::stringstream> dataStream =
        batchCreator.getDataStream();
    // Full filename is output directory + output file
    // {ReqFunc18}
    const std::string outputFileName =
        outputDirectory + fileData->getOutputFile();

    if (std::filesystem::is_regular_file(outputFileName)) {
        if (!utilities::Utils::askToContinue(
                    "The file already exists, do you want to overwrite it? (y/n) ")) {
            OUTPUT << "Skipping file...\n";
            return;
        }
        OUTPUT << "Overwriting file...\n";
    }

    std::ofstream outFile(outputFileName);

    if (!outFile.good()) {
        throw exceptions::FailedToOpenFileException(outputFileName);
    }

    outFile << dataStream->str();
}

// Initialize easylogging++
// Moved to bottom because it messed with doxygen
INITIALIZE_EASYLOGGINGPP
