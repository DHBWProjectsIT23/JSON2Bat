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
// @AUTOGENERATED_WARNING@

#ifndef CONFIG_HPP
#define CONFIG_HPP

/**
 * @namespace config
 * @brief Namespace used for general project information
 */
namespace config {
inline constexpr auto LOG_CONFIG = "@LOG_CONFIG@";
inline constexpr auto EXECUTABLE_NAME = "@EXECUTABLE_NAME@";
inline constexpr auto MAJOR_VERSION = "@PROJECT_VERSION_MAJOR@";
inline constexpr auto MINOR_VERSION = "@PROJECT_VERSION_MINOR@";
inline constexpr auto PATCH_VERSION = "@PROJECT_VERSION_PATCH@";
inline constexpr auto DESCRIPTION = "@PROJECT_DESCRIPTION@";
inline constexpr auto PROJECT_NAME = "@PROJECT_NAME@";
inline constexpr auto AUTHORS = "@AUTHORS";
inline constexpr auto HOMEPAGE_URL = "@PROJECT_HOMEPAGE_URL@";
} // namespace config

#endif