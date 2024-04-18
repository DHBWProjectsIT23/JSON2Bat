#include "CommandLineHandler.hpp"
#include "LoggingWrapper.hpp"
#include "config.hpp"
#include <bits/getopt_ext.h>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <vector>

/* TODO: Add documentation ?*/

namespace cli {
void CommandLineHandler::printHelp() {
    LOG_INFO << "Printing help message...";
    OUTPUT << BOLD << "Usage:\n"
           << RESET << "----------\n"
           << "command [options] [filenames]\n"
           << "\n"
           << BOLD << "Options:\n"
           << RESET << "----------\n"
           << "-h, --help\t\t\tPrint this help message\n"
           << "-V, --version\t\t\tPrint the version number\n"
           << "-c, --credits\t\t\tPrint the credits\n\n"
           << "\n"
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
    OUTPUT << PROJECT_NAME << " v" << MAJOR_VERSION << "." << MINOR_VERSION
           << "." << PATCH_VERSION << "\n";
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
           << GREEN << "Authors: " << RESET << ITALIC << AUTHORS << RESET
           << "\n"
           << GREEN << "Documentation: " << RESET << ITALIC << HOMEPAGE_URL
           << RESET << "\n";
    exit(0);
}

std::vector<std::string> CommandLineHandler::parseArguments(int argc,
        char* argv[]) {
    LOG_INFO << "Parsing arguments...";

    while (true) {
        int optIndex = -1;
        struct option longOption;
        auto result = getopt_long(argc, argv, "hvc", options, &optIndex);

        if (result == -1) {
            LOG_INFO << "End of options reached";
            break;
        }

        switch (result) {
        case '?':
            LOG_WARNING << "Invalid Option\n";
            CommandLineHandler::printHelp();
            exit(0);

        case 'h':
            LOG_INFO << "Help option detected";
            CommandLineHandler::printHelp();
            break;

        case 'v':
            LOG_INFO << "Version option detected";
            CommandLineHandler::printVersion();
            break;

        case 'c':
            LOG_INFO << "Credit option detected";
            CommandLineHandler::printCredits();
            break;

        case 0:
            LOG_INFO << "Long option without short version detected";
            longOption = options[optIndex];
            LOG_INFO << "Option: " << longOption.name << " given";

            if (longOption.has_arg == required_argument || longOption.has_arg) {
                LOG_INFO << "  Argument: " << optarg;
            }

            if (strcmp(longOption.name, "verbose") == 0) {
                logging::setVerboseMode(true);
                LOG_INFO << "Verbose mode activated";
            }

            break;

        default:
            LOG_ERROR << "Default case for options reached!";
            throw std::logic_error("Default case for options reached!");
            break;
        }
    }

    LOG_INFO << "Options have been parsed";
    LOG_INFO << "Checking for arguments...";
    std::vector<std::string> files;

    while (optind < argc) {
        LOG_INFO << "Adding file: " << argv[optind];
        files.emplace_back(argv[optind++]);
    }

    LOG_INFO << "Arguments and options have been parsed";
    return files;
}
} // namespace cli
