/**
 * @file Utilities.hpp
 * @author Simon Blum
 * @date 2024-04-18
 * @version 0.1.5
 * @brief Responsible for miscellaneous utility
 * @details
 * This file includes the Utils class, which includes miscellaneous utility
 * functions which can be used throughout the project.
 *
 * @see utilities
 * @see Utils
 *
 * @see src/sources/Utils.cpp
 *
 * @copyright See LICENSE file
 */
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Exceptions.hpp"
#include <string>

/**
 * @namespace utilities
 * @brief Includes all utilities
 * @details
 * This namespace includes the Utils class with utility functions which can be
 * used throughout the project.
 *
 * @see Utils
 */
namespace utilities {

/**
 * @class Utils
 * @brief Responsible for utility function.
 * @details
 * This class is responsible for handling miscellaneous utility functions
 * which be used throughout the whole project.
 */
class Utils {
public:
    /**
     * @brief Set up easylogging
     * @details
     * This function sets up the easylogging library based on the given
     * config file.
     * @param configFile The config file which is used
     */
    static void setupEasyLogging(const std::string &configFile);

    /**
     * @brief Handle an exception within the main parsing loop
     * @details
     * This function handles an exception within the main parsing loop. It
     * displays the error message and asks the user if they want to continue.
     * - Moved to Utils in 0.2.2 to improve readibility in main.cpp
     *
     * @param e The exception to be handled
     * @param file The file which caused the exception
     * @param files The list of files
     *
     * @return Returns true if the user wants to continue and false otherwise
     */
    static bool
    handleParseException(const exceptions::CustomException &e,
                         const std::vector<std::string>::iterator &file,
                         const std::vector<std::string> &files);

    /**
     * @brief Asks if the user wants to continue
     * @details
     * Asks the user if they want to continue and prompts them for a response.
     * @param prompt (Optional) A custom prompt to be used.
     * @return Returns true if the user wants to continue and false otherwise.
     */
    static bool
    askToContinue(const std::string &prompt = "Do you want to continue? (Y/N)\n");

    /**
     * @brief Checks if the easylogging-config file exists
     * @param configFile The config file to be checked
     */
    static void checkConfigFile(const std::string &configFile);

    /**
     * @brief Checks if the given directory exists and is valid
     *
     * @details
     * This function checks if the given directory exists and is valid. If the
     * directory does not end with a '/' or a '\', it will be added.
     *
     * @param directory The directory to be checked
     *
     * @return The checked directory
     */
    static const std::string &checkDirectory(std::string &directory);

    /**
    * @brief Escape any unwanted escape sequences in a string.
    * @details
    * This function takes a string and escapes already existing escape
    * sequences. E.g. "\n" would become "\\n".
    *
    * @param str The string to be escaped
    *
    * @return The processed string
    */
    static std::string escapeString(const std::string &str);
};
} // namespace utilities

#endif // UTILITIES_HPP
