/**
 * @file JsonHandler.hpp
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

#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include "FileData.hpp"
#include "LoggingWrapper.hpp"
#include <jsoncpp/json.h>

#include <memory>

/**
 * @namespace parsing
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
namespace parsing {

/**
 * @class JsonHandler
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class JsonHandler {
  public:
    /**
     * @brief
     * @details
     *
     * @todo Documentation
     */
    JsonHandler() {
        LOG_INFO << "Initialising empty JsonHandler";
    }
    /**
     * @brief
     * @details
     *
     * @param filename
     *
     * @todo Documentation
     */
    explicit JsonHandler(const std::string &filename);
    /**
     * @brief
     * @details
     *
     * @return
     *
     * @todo Documentation
     */
    std::shared_ptr<FileData> getFileData();

  private:
    /**
     * @brief
     * @details
     *
     * @param filename
     * @return
     *
     * @todo Documentation
     */
    [[nodiscard]] static std::shared_ptr<Json::Value>
    parseFile(const std::string &filename);
    /**
     * @brief
     * @details
     *
     *
     * @todo Documentation
     */
    void assignOutputFile() const;
    /**
     * @brief
     * @details
     *
     *
     * @todo Documentation
     */
    void assignHideShell() const;
    /**
     * @brief
     * @details
     *
     *
     * @todo Documentation
     */
    void assignApplication() const;
    /**
     * @brief
     * @details
     *
     *
     * @todo Documentation
     */
    void assignEntries() const;
    /**
     * @brief
     * @details
     *
     * @param entry
     *
     * @todo Documentation
     */
    void assignCommand(const Json::Value &entry) const;
    /**
     * @brief
     * @details
     *
     * @param entry
     *
     * @todo Documentation
     */
    void assignEnvironmentVariable(const Json::Value &entry) const;
    /**
     * @brief
     * @details
     *
     * @param entry
     *
     * @todo Documentation
     */
    void assignPathValue(const Json::Value &entry) const;
    /**
     * @brief
     * @details
     *
     * @return
     *
     * @todo Documentation
     */
    std::shared_ptr<FileData> createFileData();
    std::shared_ptr<Json::Value> root;
    std::shared_ptr<FileData> data;
};
} // namespace parsing

#endif // JSONHANDLER_HPP
