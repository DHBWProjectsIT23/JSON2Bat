/**
 * @file FileData.hpp
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 * @copyright See LICENSE file
 *
 * @todo Documentation
 */

#ifndef FILEDATA_HPP
#define FILEDATA_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace parsing {
/**
 * @class FileData
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class FileData {
public:
    /**
     * @brief
     * @details
     *
     * @param newOutputfile
     *
     * @todo Documentation
     */
    void setOutputFile(std::string &newOutputfile);

    /**
     * @brief
     * @param newHideShell
     *
     * @todo Documentation
     */
    void setHideShell(bool newHideShell) {
        this->hideShell = newHideShell;
    }

    /**
     * @brief
     * @details
     *
     * @param newApplication
     *
     * @todo Documentation
     */
    void setApplication(const std::string &newApplication);

    /**
     * @brief
     * @details
     *
     * @param command
     *
     * @todo Documentation
     */
    void addCommand(const std::string &command);

    /**
     * @brief
     * @details
     *
     * @param name
     * @param value
     *
     * @todo Documentation
     */
    void addEnvironmentVariable(const std::string &name,
                                const std::string &value);

    /**
     * @brief
     * @details
     *
     * @param pathValue
     *
     * @todo Documentation
     */
    void addPathValue(const std::string &pathValue);

    /**
     * @brief
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] const std::string &getOutputFile() const {
        return outputfile;
    }

    /**
     * @brief
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] bool getHideShell() const {
        return hideShell;
    }

    /**
     * @brief
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] const std::optional<std::string> &getApplication() const {
        return application;
    }

    /**
     * @brief
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] const std::vector<std::string> &getCommands() const {
        return commands;
    }

    /**
     * @brief
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] const std::vector<std::tuple<std::string, std::string>> &
    getEnvironmentVariables() const {
        return environmentVariables;
    }

    /**
     * @brief
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] const std::vector<std::string> &getPathValues() const {
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
