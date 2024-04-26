/**
 * @file Exceptions.hpp
 * @author Simon Blum
 * @date 2024-04-26
 * @version 0.2.2
 * @brief Contains all the custom exceptions used in the project.
 * @details
 * The error handling within this project is exception based.
 * This allows us to throw custom exceptions throughout any part
 * of the process and allow us to deal with them when necessary.
 *
 * @copyright See LICENSE file
 */
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "LoggingWrapper.hpp"
#include "config.hpp"
#include <string>

/**
 * @namespace exceptions
 * @brief Namespace used for customized exceptions
 */
namespace exceptions {
/**
 * @class CustomException
 * @brief Base class for all custom exceptions
 * @details
 * This class is the base class which is inherited by all custom exceptions.
 * It can be used to catch all exceptions that are thrown by us.
 *
 * @see std::exception
 */
class CustomException : public std::exception {
public:
  [[nodiscard]] const char *what() const noexcept override {
    return "Base Exception";
  }
};

/**
 * @class ParsingException
 * @brief Exception for syntax errors within the json file.
 */
class ParsingException : public CustomException {
private:
  const std::string file;
  std::string message;

public:
  explicit ParsingException(const std::string &file) : file(file) {
    /**
     * @note I planned to use std::format, however it seems that the
     * required Compiler Version is not yet available in the stable Ubuntu
     * Repo!
     */
    std::stringstream ss;
    ss << "Error while trying to parse \"" << file << "\"!\n"
       << "There most likely is a syntax error within the \".json\" file.";
    this->message = ss.str();
    LOG_INFO << "ParsingException: " << message;
  }

  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class FileExistsException
 * @brief Exception for an already exisiting outputfile
 */
class FileExistsException : public CustomException {
private:
  const std::string file;
  std::string message;

public:
  explicit FileExistsException(const std::string &file) : file(file) {
    /**
     * @note I planned to use std::format, however it seems that the
     * required Compiler Version is not yet available in the stable Ubuntu
     * Repo!
     */
    std::stringstream ss;
    ss << "The outputfile \"" << file << "\" already exists!";
    this->message = ss.str();
    LOG_INFO << "BatchExistsException: " << message;
  }

  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class InvalidValueException
 * @brief Exception for an ivalid (usually empty) value field
 */
class InvalidValueException : public CustomException {
private:
  const std::string key;
  std::string message;

public:
  InvalidValueException(const std::string &key, const std::string &issue)
      : key(key) {
    /**
     * @note I planned to use std::format, however it seems that the
     * required Compiler Version is not yet available in the stable Ubuntu
     * Repo!
     */
    std::stringstream ss;
    ss << "Error at key \"" << key << "\"! " << issue;
    this->message = ss.str();
    LOG_INFO << "InvalidValueException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class InvalidKeyException
 * @brief Exception for invalid keys
 * @details
 * This exception is thrown when a key is found within the json file,
 * that is not part of the valid keys. It will also display the name
 * and the line of the invalid key.
 *
 * @see parsing::KeyValidator::validKeys
 * @see parsing::KeyValidator::validEntryKeys
 */
class InvalidKeyException : public CustomException {
private:
  std::string message = "Invalid key found!";

public:
  explicit InvalidKeyException(
      const std::vector<std::tuple<int, std::string>> &keys) {
    LOG_INFO << "InvalidKeyException: " << message;

    for (const auto &[line, key] : keys) {
      LOG_WARNING << "Invalid key found at line " << line << ": \"" << key
                  << "\"!";
    }
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class InvalidTypeException
 * @brief Exception for invalid types.
 * @details
 * This exception is thrown when the value of the "type" field within the
 * entries is invalid (not "EXE", "PATH", "ENV"). It also prints the type and
 * the line of the invalid type.
 */
class InvalidTypeException : public CustomException {
private:
  const std::string type;
  std::string message;

public:
  InvalidTypeException(const std::string &type, int line) : type(type) {
    /**
     * @note I planned to use std::format, however it seems that the
     * required Compiler Version is not yet available in the stable Ubuntu
     * Repo!
     */
    std::stringstream ss;
    ss << "Invalid type found at line " << line << ": \"" << type << "\"";
    this->message = ss.str();
    LOG_INFO << "InvalidTypeException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class MissingKeyException
 * @brief Exception for missing keys within entries.
 * @details
 * This exception is thrown when a key (such as "path" or "command") is missing
 * from an entry. It also prints the type and which key it is missing.
 */
class MissingKeyException : public CustomException {
private:
  std::string message;
  std::string type;
  std::string key;

public:
  MissingKeyException(const std::string &key, const std::string &type)
      : type(type), key(key) {
    /**
     * @note I planned to use std::format, however it seems that the
     * required Compiler Version is not yet available in the stable Ubuntu
     * Repo!
     */
    std::stringstream ss;
    ss << "Missing key \"" << key << "\" for type \"" << type << "\"!";
    this->message = ss.str();
    LOG_INFO << "MissingKeyException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class MissingTypeException
 * @brief Exception for missing types of entries
 * @details
 * This exception is thrown, when an entry is missing it's "type" key.
 */
class MissingTypeException : public CustomException {
private:
  std::string message = "Missing \"type\" key for at least one entry!";

public:
  MissingTypeException() { LOG_INFO << "MissingTypeException: " << message; }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class UnreachableCodeException
 * @brief Exception for when the application reaches code it shouldn't reach
 */
class UnreachableCodeException : public CustomException {
private:
  std::string message;

public:
  explicit UnreachableCodeException(const std::string &message)
      : message(message) {
    OUTPUT << "This exception happened due to a bug in the application!\n"
           << "Please report this bug! See " << config::EXECUTABLE_NAME
           << " -c for contact information.\n";
    LOG_INFO << "UnreachableCodeException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class FailedToOpenFileException
 * @brief Exception for when a file can't be opened
 */
class FailedToOpenFileException : public CustomException {
private:
  std::string message;

public:
  explicit FailedToOpenFileException(const std::string &file) {
    message = "Failed to open file: " + file;
    LOG_INFO << "FailedToOpenFileException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class NoSuchDirException
 * @brief Exception for when a directory does not exist
 */
class NoSuchDirException : public CustomException {
private:
  std::string message;

public:
  explicit NoSuchDirException(const std::string &dir) {
    message = "No such directory: " + dir;
    LOG_INFO << "NoSuchDirException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

/**
 * @class ContainsBadCharacterException
 * @brief Exception for when a string contains bad characters
 */
class ContainsBadCharacterException : public CustomException {
private:
  std::string message;

public:
  explicit ContainsBadCharacterException(const std::string &value) {
    message = "The value \"" + value + "\" contains bad characters!";
    LOG_INFO << "ContainsBadCharacterException: " << message;
  }
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

} // namespace exceptions

#endif
