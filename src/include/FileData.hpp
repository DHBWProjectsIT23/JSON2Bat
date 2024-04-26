/**
 * @file FileData.hpp
 * @author Sonia Sinacci, Elena Schwartzbach
 * @date 16.04.2024
 * @version 0.1.5
 * @brief This file contains the FileData class
 *
 * @see parsing::FileData
 *
 * @see src/sources/FileData.cpp
 *
 * @copyright See LICENSE file
 */

#ifndef FILEDATA_HPP
#define FILEDATA_HPP

#include <optional>
#include <string>
#include <vector>

namespace parsing {
/**
 * @class FileData
 * @brief This class contains all data from the json file.
 * @details
 * The data from the json file is parsed by the JsonHandler and then assigned
 * to the attributes of an instance of this class.
 * This class also handles a part of the error handling.
 */
class FileData {
public:
    /**
     * @brief Setter for this->outputfile
     * @details
     * Checks that neither the given string is empty, nor that the outputfile
     * is already set and then assigns the newOutputfile to the instance.
     *
     * @param newOutputfile The outputfile to be set
     *
     * @throws exceptions::InvalidValueException
     */
    void setOutputFile(std::string &newOutputfile);

    /**
     * @brief Setter for this->hideshell
     * @param newHideShell The hideshell value to be set
     */
    void setHideShell(bool newHideShell) {
        this->hideShell = newHideShell;
    }

    /**
     * @brief Setter for this->application
     * @details
     * Set's the application attribute. Return's if the given string is
     * empty.
     *
     * @param newApplication THe application to be set
     */
    void setApplication(const std::string &newApplication);

    /**
     * @brief Adds a given command to this->commands
     * @details
     * Makes sure, that the given command value is not empty and then add's
     * it to the commands attribute.
     *
     * @param command The command to be added
     *
     * @throws exceptions::InvalidValueException
     */
    void addCommand(const std::string &command);

    /**
     * @brief Adds a given tuple to this->environmentVariables
     * @details
     * Makes sure that neither the key nor the value is empty and then adds
     * a tuple with both values to the environmentVariables attribute
     *
     * @param name The name of the env variable
     * @param value The value of the env variable
     *
     * @throws exceptions::InvalidValueException
     */
    void addEnvironmentVariable(const std::string &name,
                                const std::string &value);

    /**
     * @brief Add's a given value to this->pathValues
     * @details
     * Makes sure that the given value is not empty and then assigns it to
     * the given pathValues attribute
     *
     * @param pathValue The value to be added
     *
     * @throws exceptions::InvalidValueException
     */
    void addPathValue(const std::string &pathValue);

    /**
     * @brief Getter for this->outputfile
     * @return The assigned outputfile
     */
    [[nodiscard]] const std::string &getOutputFile() const {
        return outputfile;
    }

    /**
     * @brief Getter for this->hideShell
     * @return The assigned value for hideshell
     */
    [[nodiscard]] bool getHideShell() const {
        return hideShell;
    }

    /**
     * @brief Getter for this->application
     * @return The assigned application
     */
    [[nodiscard]] const std::optional<std::string> &getApplication() const {
        return application;
    }

    /**
     * @brief Getter for this->commands
     * @return The vector of assigned commands
     */
    [[nodiscard]] const std::vector<std::string> &getCommands() const {
        return commands;
    }

    /**
     * @brief Getter for this->environmentVariables
     * @return The vector of assigned env variables
     */
    [[nodiscard]] const std::vector<std::tuple<std::string, std::string>> &
    getEnvironmentVariables() const {
        return environmentVariables;
    }

    /**
     * @brief Getter for this->pathValues
     * @return The vector of assigned pathValues
     */
    [[nodiscard]] const std::vector<std::string> &getPathValues() const {
        return pathValues;
    }

private:
    std::string outputfile;
    bool hideShell;
    std::optional<std::string> application;
    std::vector<std::string> commands;
    // Tuple<Name, Value>
    std::vector<std::tuple<std::string, std::string>> environmentVariables;
    std::vector<std::string> pathValues;
};
} // namespace parsing

#endif // FILEDATA_HPP
