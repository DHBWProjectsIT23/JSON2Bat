/**
 * @file main.cpp
 * @author Elena Schwarzbach, Max Rodler, Simon Blum, Sonia Sinaci
 * @date 2024-04-26
 * @version 0.2.2
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
parseAndValidateArgs(int argc, char* argv[]);

/**
 * @brief Checks if the files are valid
 * @details
 * Makes sures, that provided files exists and checks their file ending
 * @param files The files to be checked
 * @return A vector containing the valid files
 */
const std::vector<std::string>
validateFiles(const std::vector<std::string> &files);

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
int main(int argc, char* argv[])
{
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

    // Main parsing loop
    for (auto file = files.begin(); file != files.end(); ++file) {
        OUTPUT << cli::ITALIC << "\nParsing file: " << *file << "...\n"
               << cli::RESET;

        try {
            parseFile(*file, outDir);
            // Only catch custom exceptions, other exceptions are fatal
        }
        catch (const exceptions::CustomException &e) {
            if (utilities::Utils::handleParseException(e, file, files)) {
                continue;
            }

            exit(1);
        }
    }

    LOG_INFO << "Exiting...";
    return 0;
}

std::tuple<std::vector<std::string>, std::string> parseAndValidateArgs(int argc,
        char* argv[])
{
    if (argc < 2) {
        LOG_ERROR << "No options given!\n";
        cli::CommandLineHandler::printHelp();
    }

    auto [outOption, files] = cli::CommandLineHandler::parseArguments(argc, argv);
    // Set the output directory if given
    std::string outDir = outOption.value_or("");

    if (!outDir.empty()) {
        try {
            outDir = utilities::Utils::checkDirectory(outDir);
        }
        catch (const exceptions::CustomException &e) {
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

const std::vector<std::string> validateFiles(const std::vector<std::string>
        &files)
{
    std::vector<std::string> validFiles;
    // Reserve space, to avaid reallocating with each valid file
    validFiles.reserve(files.size());

    for (const std::filesystem::path file : files) {
        // Check that the file exists
        if (!std::filesystem::is_regular_file(file)) {
            LOG_ERROR << "The file \"" << file << "\" does not exist!\n";

            if (files.size() > 1 && !utilities::Utils::askToContinue()) {
                OUTPUT << "Aborting...\n";
                LOG_INFO << "Application ended by user Input";
                exit(1);
            }

            continue;
        }

        // Check if the file ends in .json
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

    // Shrinks the vector if invalid files were found
    validFiles.shrink_to_fit();
    return validFiles;
}

void parseFile(const std::string &file, const std::string &outputDirectory)
{
    parsing::JsonHandler jsonHandler(file);
    const auto fileData = jsonHandler.getFileData();
    BatchCreator batchCreator(fileData);
    const std::shared_ptr<std::stringstream> dataStream =
        batchCreator.getDataStream();
    // Full filename is output directory + output file
    const std::string outputFileName =
        outputDirectory + fileData->getOutputFile();
    std::ofstream outFile(outputFileName);

    if (!outFile.good()) {
        throw exceptions::FailedToOpenFileException(outputFileName);
    }

    outFile << dataStream->str();
    OUTPUT << "Done with files!\n";
}

// Initialize easylogging++
// Moved to bottom because it messed with doxygen
INITIALIZE_EASYLOGGINGPP
