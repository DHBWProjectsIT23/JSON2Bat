/**
 * @file Exceptions.hpp
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
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "LoggingWrapper.hpp"
#include <format>
#include <string>
#include <utility>

/**
 * @namespace exceptions
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
namespace exceptions {
/**
 * @class CustomException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class CustomException : public std::exception {
  public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Base Exception";
    }
};

/**
 * @class ParsingException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class ParsingException : public CustomException {
  private:
    const std::string file;
    std::string message;

  public:
    explicit ParsingException(const std::string &file) : file(file) {
        this->message = std::format(
                                    "Error while trying to parse \"{}\"!\n"
                                    "There most likely is a syntax error within the \".json\" file.",
                                    file);
        LOG_INFO << "ParsingException: " << message;
    }

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class BatchExistsException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class BatchExistsException : public CustomException {
  private:
    const std::string file;
    std::string message;

  public:
    explicit BatchExistsException(const std::string &file) : file(file) {
        this->message = std::format("The outputfile \"{}\" already exists!", file);
        LOG_INFO << "BatchExistsException: " << message;
    }

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class InvalidValueException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class InvalidValueException : public CustomException {
  private:
    const std::string key;
    std::string message;

  public:
    InvalidValueException(const std::string &key, const std::string &issue)
        : key(key) {
        this->message = std::format("Error at key \"{}\"! {}", key, issue);
        LOG_INFO << "InvalidValueException: " << message;
    }
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class InvalidKeyException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class InvalidKeyException : public CustomException {
  private:
    std::string message = "Invalid key found!";

  public:
    InvalidKeyException() {
        LOG_INFO << "InvalidKeyException: " << message;
    }
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class InvalidTypeException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class InvalidTypeException : public CustomException {
  private:
    const std::string type;
    std::string message;

  public:
    InvalidTypeException(const std::string &type, int line) : type(type) {
        this->message =
                    std::format("Invalid type found at line {}: \"{}\"", line, type);
        LOG_INFO << "InvalidTypeException: " << message;
    }
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class MissingKeyException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class MissingKeyException : public CustomException {
  private:
    std::string message;
    std::string type;
    std::string key;

  public:
    MissingKeyException(const std::string &key, const std::string &type)
        : type(type), key(key) {
        this->message =
                    std::format(R"(Missing key "{}" for type "{}"!)", key, type);
        LOG_INFO << "MissingKeyException: " << message;
    }
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class MissingTypeException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class MissingTypeException : public CustomException {
  private:
    std::string message = "Missing \"type\" key for at least one entry!";

  public:
    MissingTypeException() {
        LOG_INFO << "MissingTypeException: " << message;
    }
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class UnreachableCodeException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
 */
class UnreachableCodeException : public CustomException {
  private:
    std::string message;

  public:
    explicit UnreachableCodeException(const std::string &message)
        : message(message) {
        LOG_INFO << "UnreachableCodeException: " << message;
    }
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

} // namespace exceptions

#endif
