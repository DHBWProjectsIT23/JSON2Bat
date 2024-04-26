/**
 * @file config.hpp
 * @author Simon Blum
 * @date 2024-04-18
 * @version 0.1.5
 * @brief Configures general project information
 * @details
 * This file is used by CMake to configure general information which can be
 * used throughout the project.
 *
 * @note This file is automatically configured by CMake.
 *       The original file can be found in conf/config.hpp.in
 * @license GNU GPLv3
 * @copyright See LICENSE file
 */
// This file is autogenerated. Changes will be overwritten

#ifndef CONFIG_HPP
#define CONFIG_HPP

/**
 * @namespace config
 * @brief Namespace used for general project information
 */
namespace config {
inline constexpr auto LOG_CONFIG =
            "/home/simon/1_Coding/cpp/JsonToBat/build/Debug/config/easylogging.conf";
inline constexpr auto EXECUTABLE_NAME = "json2batch";
inline constexpr auto MAJOR_VERSION = "0";
inline constexpr auto MINOR_VERSION = "2";
inline constexpr auto PATCH_VERSION = "3";
inline constexpr auto DESCRIPTION = "A simple tool to convert json to batch.";
inline constexpr auto PROJECT_NAME = "JSON2Batch";
inline constexpr auto AUTHORS = "@AUTHORS";
inline constexpr auto HOMEPAGE_URL =
            "https://dhbwprojectsit23.github.io/JSON2Bat";
} // namespace config

#endif
