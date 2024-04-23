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
#include <string>

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
    [[nodiscard]] const char *what() const noexcept override {
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
 * @class BatchExistsException
 * @brief
 * @details
 *
 * @see
 *
 * @todo Documentation
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
    InvalidKeyException(const std::vector<std::tuple<int, std::string>> &keys) {
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
    [[nodiscard]] const char *what() const noexcept override {
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
    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }
};

class FailedToOpenFileException : public CustomException {
private:
    std::string message;

    /** @todo Documentation*/
public:
    explicit FailedToOpenFileException(const std::string &file) {
        message = "Failed to open file: " + file;
        LOG_INFO << "FailedToOpenFileException: " << message;
    }
    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }
};

} // namespace exceptions

#endif
