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
 * @copyright See LICENSE file
 */
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

/**
 * @namespace utilities
 * @brief Includes all utilities
 * @details
 * This namespace includes the utility class with utility functions which can be
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
     * @brief Check if a file exists
     * @details
     * This function checks if a file exists by trying to open it using fstream.
     * @param fileName The file which should be checked.
     * @return Returns true if the file exists and false otherwise
     */
    static bool checkIfFileExists(const std::string &fileName);

    /**
     * @brief Checks if the file ending is ".json"
     * @details
     * This function checks if the given file ends with ".json".
     * @param fileName The file which should be checked.
     * @return Returns true if the file ends with ".json" and false otherwise.
     */
    static bool checkFileEnding(const std::string_view &fileName);

    /**
     * @brief Asks if the user wants to continue
     * @details
     * Asks the user if they want to continue and prompts them for a response.
     * @param prompt (Optional) A custom prompt to be used.
     * @return Returns true if the user wants to continue and false otherwise.
     */
    static bool
    askToContinue(const std::string &prompt = "Do you want to continue? (Y/N)\n");

    /** @todo documentation */
    static std::string &checkDirectory(std::string &directory);
};
} // namespace utilities

#endif // UTILITIES_HPP
