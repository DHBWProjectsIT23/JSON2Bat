/**
 * @file CommandLineHandler.cpp
 * @author Simon Blum
 * @date 2024-04-18
 * @version 0.1.5
 * @brief Implementation for the Command Line Interface.
 *
 * @see src/include/utility/CommandLineHandler.hpp
 *
 * @copyright See LICENSE file
 */

#include "CommandLineHandler.hpp"
#include "LoggingWrapper.hpp"
#include "config.hpp"
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <vector>

namespace cli {
void CommandLineHandler::printHelp() {
    LOG_INFO << "Printing help message...";
    OUTPUT << BOLD << "Usage:\n"
           << RESET << "----------\n"
           << EXECUTABLE_NAME << " [options] [filenames]\n"
           << "\n"
           << BOLD << "Options:\n"
           << RESET << "----------\n"
           << "-o, --outdir\t [path]\t\tOutput the batch file to the given "
           "dir\n"
           << "-h, --help\t\t\tPrint this help message\n"
           << "-V, --version\t\t\tPrint the version number\n"
           << "-c, --credits\t\t\tPrint the credits\n\n"
           << "    --verbose\t\t\tStart the application in verbose mode\n"
           << ITALIC
           << "          \t\t\tNote: Verbose flag should be passed first!\n\n"
           << RESET << BOLD << "Filenames:\n"
           << RESET << "----------\n"
           << "The json files to be processed into batch files.\n"
           << "Multiple files should be seperated by spaces!\n\n";
    exit(0);
}
void CommandLineHandler::printVersion() {
    LOG_INFO << "Printing version number...";
    OUTPUT << PROJECT_NAME << " v" << MAJOR_VERSION << "." << MINOR_VERSION << "."
           << PATCH_VERSION << "\n";
    exit(0);
}
void CommandLineHandler::printCredits() {
    LOG_INFO << "Printing credits...";
    OUTPUT << BOLD << "Project information:\n"
           << RESET << "----------\n"
           << CYAN << BOLD << PROJECT_NAME << RESET << " v" << MAJOR_VERSION
           << "." << MINOR_VERSION << "." << PATCH_VERSION << "\n"
           << "\n"
           << DESCRIPTION << "\n"
           << "\n"
           << GREEN << "Authors: " << RESET << ITALIC << AUTHORS << RESET << "\n"
           << GREEN << "Documentation: " << RESET << ITALIC << HOMEPAGE_URL
           << RESET << GREEN << "\nContact: " << RESET << ITALIC
           << "simon21.blum@gmail.com" << "\n";
    exit(0);
}

std::tuple<std::optional<std::string>, std::vector<std::string>> CommandLineHandler::parseArguments(int argc,
        char *argv[]) {
    LOG_INFO << "Parsing arguments...";

    std::vector<std::string> files;
    std::optional<std::string> outDir;

    while (true) {
        int optIndex = -1;
        struct option longOption = {};
        auto result = getopt_long(argc, argv, "hvco:", options, &optIndex);

        if (result == -1) {
            LOG_INFO << "End of options reached";
            break;
        }

        switch (result) {
        case '?':
            LOG_ERROR << "Invalid Option (argument)\n";
            CommandLineHandler::printHelp();

        case 'h':
            LOG_INFO << "Help option detected";
            CommandLineHandler::printHelp();

        case 'v':
            LOG_INFO << "Version option detected";
            CommandLineHandler::printVersion();

        case 'c':
            LOG_INFO << "Credit option detected";
            CommandLineHandler::printCredits();

        case 'o':
            LOG_INFO << "Output option detected";
            outDir = optarg;
            break;

        case 0:
            LOG_INFO << "Long option without short version detected";
            longOption = options[optIndex];
            LOG_INFO << "Option: " << longOption.name << " given";

            if (longOption.has_arg) {
                LOG_INFO << "  Argument: " << optarg;
            }

            if (strcmp(longOption.name, "verbose") == 0) {
                logging::setVerboseMode(true);
                LOG_INFO << "Verbose mode activated";
            }

            break;

        default:
            LOG_ERROR << "Default case for options reached!";
            break;
        }
    }

    LOG_INFO << "Options have been parsed";
    LOG_INFO << "Checking for arguments...";

    while (optind < argc) {
        LOG_INFO << "Adding file: " << argv[optind];
        files.emplace_back(argv[optind++]);
    }

    LOG_INFO << "Arguments and options have been parsed";
    return std::make_tuple(outDir, files);
}
} // namespace cli
