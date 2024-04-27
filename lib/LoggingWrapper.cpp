/**
 * \author Simon Blum
 * \biref A simple wrapper for easylogging++.
 * \details
 * This wrapper handles simultaneous outputs to the console and to a log file.
 * It also allows to easily log at different levels. The compiled library
 * also includes the easylogging++ library.
 * Both headers need to be added to the project, however only this header needs
 * to be included to allow for logging.
 * Easylogging++ will not be configured or initialised in this library.
 *
 * \copyright MIT License 2024
 **/

#include "LoggingWrapper.hpp"
namespace logging {
static bool verboseMode = false;
void setVerboseMode(bool mode) { verboseMode = mode; }
} // namespace logging

namespace libLogging {
LoggingWrapper::~LoggingWrapper() {
  switch (this->level) {
  case LogLevel::OUTP:
    std::cout << this->buffer.str();
    LOG(INFO) << this->prefix << this->buffer.str();
    break;
  case LogLevel::INFO:
    if (logging::verboseMode) {
      std::cout << libLogging::GRAY_FG << this->prefix << this->buffer.str()
                << libLogging::RESET << std::endl;
    }
    LOG(INFO) << this->prefix << this->buffer.str();
    break;
  case LogLevel::WARNING:
    std::cout << libLogging::YELLOW_FG << this->buffer.str()
              << libLogging::RESET << "\n"
              << std::endl;
    LOG(WARNING) << this->prefix << this->buffer.str();
    break;
  case LogLevel::ERROR:
    std::cerr << libLogging::ERROR << this->prefix << this->buffer.str()
              << libLogging::RESET << "\n"
              << std::endl;
    LOG(ERROR) << this->prefix << this->buffer.str();
    break;
  case LogLevel::FATAL:
    std::cerr << libLogging::BLACK_FG << libLogging::RED_BG << this->prefix
              << this->buffer.str() << libLogging::RESET << std::endl;
    LOG(FATAL) << this->prefix << this->buffer.str();
    break;
  case LogLevel::DEBUG:
    std::cout << libLogging::ITALIC << libLogging::CYAN_FG << this->prefix
              << this->buffer.str() << libLogging::RESET << std::endl;
    LOG(DEBUG) << this->prefix << this->buffer.str();
    break;
  }
}
LoggingWrapper &LoggingWrapper::operator<<(Manipulator manipulator) {
  manipulator(std::cout);
  this->buffer << manipulator;
  return *this;
}

} // namespace libLogging
