/**
 * @file Utils.cpp
 * @author Simon Blum
 * @date 2024-04-26
 * @version 0.2.2
 * @brief Implementation for the Utils class
 * @details
 * This file includes the implementation for the Utils class.
 *
 * @see src/include/utility/Utilities.hpp
 *
 * @copyright See LICENSE file
 */

#include "Utils.hpp"
#include "CommandLineHandler.hpp"
#include "Exceptions.hpp"
#include "config.hpp"

#include <LoggingWrapper.hpp>
#include <filesystem>
#include <string>

namespace utilities {
void Utils::setupEasyLogging(const std::string &configFile) {
    el::Configurations conf(configFile);
    el::Loggers::reconfigureAllLoggers(conf);
    LOG_INFO << "Running " << config::PROJECT_NAME << " v"
             << config::MAJOR_VERSION << "." << config::MINOR_VERSION << "."
             << config::PATCH_VERSION;
    LOG_INFO << "For more Information checkout " << config::HOMEPAGE_URL;
    LOG_INFO << "EasyLogging has been setup!";
}
bool Utils::askToContinue(const std::string &prompt) {
    std::string userInput;
    LOG_INFO << "Asking for user Confirmation to continue...";
    OUTPUT << cli::BOLD << prompt << cli::RESET;

    do {
        std::cin >> userInput;
        std::ranges::transform(userInput, userInput.begin(), ::tolower);

        if (userInput != "y" && userInput != "yes" && userInput != "n" &&
                userInput != "no") {
            LOG_INFO << "Wrong user input!";
            OUTPUT << cli::ITALIC << "Please enter Y/Yes or N/No!\n" << cli::RESET;
            continue;
        }

        break;
    } while (true);

    return userInput == "y" || userInput == "yes";
}
void Utils::checkConfigFile(const std::string &configFile) {
    if (!std::filesystem::is_regular_file(configFile)) {
        std::cerr << cli::RED << cli::BOLD
                  << "Fatal: Easylogging configuration file not found at:\n"
                  << cli::RESET << cli::ITALIC << "\n\t\"" << configFile << "\"\n\n"
                  << cli::RESET;
        std::cout << "Aborting...\n";
        exit(1);
    }
}
const std::string &Utils::checkDirectory(std::string &directory) {
    if (!directory.empty() && directory.back() != '/' &&
            directory.back() != '\\') {
        directory += '/';
    }

    if (!std::filesystem::exists(directory)) {
        throw exceptions::NoSuchDirException(directory);
    }

    return directory;
}
bool Utils::handleParseException(const exceptions::CustomException &e,
                                 const std::vector<std::string>::iterator &file,
                                 const std::vector<std::string> &files) {
    OUTPUT << "\nThere has been a error while trying to parse \"" << *file
           << ":\n";
    LOG_ERROR << e.what();

    if (std::next(file) != files.end() &&
            !utilities::Utils::askToContinue(
                "Do you want to continue with the other files? (y/n) "
                "")) {
        OUTPUT << "Aborting...";
        LOG_INFO << "Application ended by user Input";
        return false;
    }

    std::cout << std::endl;
    return true;
}

std::string Utils::escapeString(const std::string &str) {
    // Map of characters to their escape sequences
    static const std::unordered_map<char, std::string> escapeSequences = {
        {'\\', "\\\\"},    // Replace backslash with double backslash
        {'\n', "\\n"},     // Replace newline with backslash-n
        {'\t', "\\t"},     // Replace tab with backslash-t
        {'\x1A', "\\x1A"}, // Replace end of file with backslash-x1A
        {'\r', "\\r"}      // Replace carriage return with backslash-r
    };

    std::ostringstream escapedStream;
    for (char c : str) {
        // Replace a character with it's counterpart, if it is in the map
        if (escapeSequences.contains(c)) {
            escapedStream << escapeSequences.at(c);
        } else {
            escapedStream << c;
        }
    }
    return escapedStream.str();
}

} // namespace utilities
