/**
 * @file CommandLineHandler.hpp
 * @author Simon Blum
 * @date 2024-04-26
 * @version 0.2.2
 * @brief Responsible for the Command Line Interface.
 * @details
 * This file is responsible for the Command Line Interface.
 * As such it includes things such as the
 * CommandLineHandler class, possible options and style helpers.
 *
 * @see cli
 * @see CommandLineHandler
 * @see options
 * @see StyleHelpers
 *
 * @see src/sources/CommandLineHandler.cpp
 *
 * @copyright See LICENSE file
 */
#ifndef COMMANDLINEHANDLER_HPP
#define COMMANDLINEHANDLER_HPP

#include <getopt.h>
#include <optional>
#include <string>
#include <vector>

/**
 * @namespace cli
 * @brief Includes everything regarding the CLI
 * @details
 * This namespace includes all the code regarding the Command Line Interface.
 * This includes the CommandLineHandler Class, the struct for the options and
 * helpers for Styling.
 *
 * @see CommandLineHandler
 * @see options
 * @see StyleHelpers
 */
namespace cli {

/**
 * @class CommandLineHandler
 * @brief Responsible for the Command Line Interface.
 * @details
 * This class is responsible for parsing the command line arguments,
 * printing Help/Version/Credits messages and returning inputted files.
 *
 * @author Simon Blum
 * @date 2024-04-18
 * @version 0.1.5
 * @see options
 */
class CommandLineHandler {
public:
    /**
     * @brief Prints the help message.
     *
     * @note This function ends the application.
     */
    [[noreturn]] static void printHelp();
    /**
     * @brief Prints the version message.
     *
     * @note This function ends the application.
     */
    [[noreturn]] static void printVersion();
    /**
     * @brief Prints the credits message.
     *
     * @note This function ends the application.
     */
    [[noreturn]] static void printCredits();
    /**
     * @brief Parses the Command Line Arguments.
     * @details
     * This function uses the "getopt.h" library to parse all options given
     * and then returns all files which are given as arguments.
     *
     * @param argc The number of arguments given
     * @param argv The arguments given
     *
     * @return Returns a tuple containing the output directory and the files
     */
    static std::tuple<std::optional<std::string>, std::vector<std::string>>
    parseArguments(int argc, char* argv[]);
    /**
     * @brief The Constructor of the CommandLineHandler Class
     * @note As all functions are static it should not be used and as such
     * is deleted.
     */
    CommandLineHandler() = delete;
    /**
     * @brief The Destructor of the CommandLineHandler Class
     * @note As all functions are static it should not be used and as such
     * is deleted.
     */
    ~CommandLineHandler() = delete;
};

/**
 * @struct options
 * @brief The struct containing all possible options.
 * @details
 * This struct contains all long and short options which can be used and will be
 * parsed using "getopt.h"
 *
 * @see CommandLineHandler
 */
static const struct option options[] = {
    {"help", no_argument, nullptr, 'h'}, /** < Help */
    {"version", no_argument, nullptr, 'v'}, /** < Version */
    {"credits", no_argument, nullptr, 'c'}, /** < Credits */
    {"verbose", no_argument, nullptr, 0}, /** < Verbose */
    {"outdir", required_argument, nullptr, 'o'}, /** < Output directory */
    nullptr
};

/**
 * @defgroup StyleHelpers
 * @brief Static variables to help with CLI styling.
 * @details
 * A group of strings, that use escape sequences to easily style the
 * command line interface on Unix systems.
 * When compiling for Windows all of these strings will be empty, as escape
 * sequences can't be used the same way.
 *
 * @{
 */
#ifdef IS_UNIX // CLI Formatting for Linux
static const std::string CLEAR_TERMINAL = "\033[2J\033[1;1H";
static const std::string RESET = "\033[0m";
static const std::string RED = "\033[0;31m";
static const std::string GREEN = "\033[0;32m";
static const std::string YELLOW = "\033[0;33m";
static const std::string BLUE = "\033[0;34m";
static const std::string MAGENTA = "\033[0;35m";
static const std::string CYAN = "\033[0;36m";
static const std::string WHITE = "\033[0;37m";
static const std::string BOLD = "\033[1m";
static const std::string UNDERLINE = "\033[4m";
static const std::string ITALIC = "\033[3m";
//@note Windows doesn't support ANSI escape codes the same way
#elif defined(IS_WINDOWS)
static const std::string CLEAR_TERMINAL = "";
static const std::string RESET = "";
static const std::string RED = "";
static const std::string GREEN = "";
static const std::string YELLOW = "";
static const std::string BLUE = "";
static const std::string MAGENTA = "";
static const std::string CYAN = "";
static const std::string WHITE = "";
static const std::string BOLD = "";
static const std::string UNDERLINE = "";
static const std::string ITALIC = "";
#endif
/** @} */ // end of group StyleHelpers

} // namespace cli

#endif // COMMANDLINEHANDLER_HPP
