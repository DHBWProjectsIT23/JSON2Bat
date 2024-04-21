/**
 * @file
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 *
 * @license GNU GPLv3
 * @copyright See LICENSE file
 */

#ifndef FILEDATA_HPP
#define FILEDATA_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace parsing {
/**
 * @brief The FileData class
 * @details
 * The class is used to store the data from the json file.
 * It also does some error handling.
 **/
class FileData {
public:
    /**
     * @brief Set's the output file
     * @note
     * If the output file does not end with .bat, the function will append .bat
     *to the output file.
     *
     * @param outputfile The output file
     *
     * @throws std::invalid_argument if the outputfile is empty
     * @throws std::invalid_argument if the outputfile is already set
     **/
    void setOutputFile(std::string& newOutputfile);

    /**
     * @brief Set's the hide shell flag
     * @param hideShell The hide shell flag
     **/
    void setHideShell(bool newHideShell) {
        this->hideShell = newHideShell;
    }

    /**
     * @brief Set's the application
     * @param application The application
     **/
    void setApplication(const std::string& newApplication);

    /**
     * @brief Add a command to the commands vector
     * @param command The command
     *
     * @throws std::invalid_argument if the command is empty
     **/
    void addCommand(const std::string& command);

    /**
     * @brief Add an environment variable to the environmentVariables vector
     *
     * @details
     * The environment variable is added as a tuple with the name and value
     * as it's elements.
     *
     * @param name The name of the environment variable
     * @param value The value of the environment variable
     *
     * @throws std::invalid_argument if the name or the value is empty
     **/
    void addEnvironmentVariable(const std::string& name,
                                const std::string& value);

    /**
     * @brief Add a path value to the pathValues vector
     * @param pathValue The path value
     *
     * @throws std::invalid_argument if the pathValue is empty
     **/
    void addPathValue(const std::string& pathValue);

    /**
     * @brief Get the output file
     * @return The output file
     **/
    [[nodiscard]] const std::string& getOutputFile() const {
        return outputfile;
    }

    /**
     * @brief Get the hide shell flag
     * @return The hide shell flag
     **/
    [[nodiscard]] bool getHideShell() const {
        return hideShell;
    }

    /**
     * @brief Get the application
     * @return The application
     **/
    [[nodiscard]] const std::optional<std::string>& getApplication() const {
        return application;
    }

    /**
     * @brief Get the commands
     * @return The commands
     **/
    [[nodiscard]] const std::vector<std::string>& getCommands() const {
        return commands;
    }

    /**
     * @brief Get the environment variables
     * @return The environment variables
     **/
    [[nodiscard]] const std::vector<std::tuple<std::string, std::string>>&
    getEnvironmentVariables() const {
        return environmentVariables;
    }

    /**
     * @brief Get the path values
     * @return The path values
     **/
    [[nodiscard]] const std::vector<std::string>& getPathValues() const {
        return pathValues;
    }

private:
    std::string outputfile;
    bool hideShell;
    std::optional<std::string> application;
    std::vector<std::string> commands;
    std::vector<std::tuple<std::string, std::string>> environmentVariables;
    std::vector<std::string> pathValues;
    const static int8_t suffixLength = 4;
};
} // namespace parsing

#endif // FILEDATA_HPP
