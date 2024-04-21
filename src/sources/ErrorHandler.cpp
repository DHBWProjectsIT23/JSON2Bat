/**
 * @file ErrorHandler.cpp
 * @author
 * @date
 * @version
 * @brief
 * @details
 *
 * @copyright See LICENSE file
 */

#include "ErrorHandler.hpp"
#include "Exceptions.hpp"
#include <LoggingWrapper.hpp>
#include <cstdlib>

namespace errors {

void ErrorHandler::batchFileExists(const std::string &outputFile)
{
    throw exceptions::BatchExistsException(outputFile);
}

void ErrorHandler::parsingError(const std::string &fileName)
{
    throw exceptions::ParsingException(fileName);
}

void ErrorHandler::invalidValue(const std::string &key,
                                const std::string &issue)
{
    throw exceptions::InvalidValueException(key, issue);
}

void ErrorHandler::invalidKeys(
    const std::vector<std::tuple<int, std::string>> &keys)
{
    for (const auto &[line, key] : keys) {
        LOG_WARNING << "Invalid key found at line " << line << ": \"" << key
                    << "\"!";
    }

    throw exceptions::InvalidKeyException();
}

void ErrorHandler::invalidType(const std::string &type, int line)
{
    throw exceptions::InvalidTypeException(type, line);
}

void ErrorHandler::missingKey(const std::string &key, const std::string &type)
{
    throw exceptions::MissingKeyException(key, type);
}

void ErrorHandler::missingType()
{
    throw exceptions::MissingTypeException();
}

void ErrorHandler::unreachableCode(const std::string &message)
{
    throw exceptions::UnreachableCodeException(message);
}

} // namespace errors
