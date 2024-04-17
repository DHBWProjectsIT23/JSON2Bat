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
 * Perfomance based on my not very scientific tests: 
 * Average over 10 runs with 1.000.000 iterations each:
 * - only Easylogging++: 1046.1 ms
 * - easylogging++ and std::cout: 3814.24 ms
 * - wrapper: 3643.04 ms
 *
 * \todo
 * - More easily allow for verbosity options.
 * - Check performance -> Especially compare to std::cout.
 *
 * \copyright MIT License 2024
 **/

#ifndef LOGANDOUT_HPP
#define LOGANDOUT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <easylogging++.h>

namespace logging {
void setVerboseMode(bool mode);
}

namespace libLogging {

#define LOG_INFO libLogging::log(libLogging::LogLevel::INFO)
#define LOG_ERROR libLogging::log(libLogging::LogLevel::ERROR)
#define LOG_WARNING libLogging::log(libLogging::LogLevel::WARNING)
#define LOG_DEBUG libLogging::log(libLogging::LogLevel::DEBUG)
#define OUTPUT libLogging::log(libLogging::LogLevel::OUT, "Output: ")


enum class LogLevel {
  INFO,
  WARNING,
  ERROR,
  FATAL,
  DEBUG,
  OUT,
};

/**
 * \note
 * # Bugs and Quirks
 * - Automatically makes new line for cout -- Nevermind?!
 **/
class LoggingWrapper {
public:
  LoggingWrapper(LogLevel newLevel, bool newVerbose = false)
      : level(newLevel), verbose(newVerbose) {}
  LoggingWrapper(const std::string &newPrefix, LogLevel newLevel,
                 bool newVerbose = false)

      : prefix(newPrefix), level(newLevel), verbose(newVerbose) {}

  template <typename T> LoggingWrapper &operator<<(const T &val) {
    buffer << val;
    return *this;
  }

  typedef std::ostream &(*Manipulator)(std::ostream &);
  LoggingWrapper &operator<<(Manipulator manipulator);

  ~LoggingWrapper();

private:
  std::string prefix;
  LogLevel level;
  std::ostringstream buffer;
  const bool verbose;
};
inline LoggingWrapper log(bool verbose = false) {
  return LoggingWrapper(LogLevel::INFO, verbose);
}
inline LoggingWrapper log(LogLevel level) {
  return LoggingWrapper(level, false);
}
inline LoggingWrapper log(const std::string &prefix, bool verbose = false) {
  return LoggingWrapper(prefix, LogLevel::INFO, verbose);
}
inline LoggingWrapper log(LogLevel level, const std::string &prefix,
                          bool verbose = false) {
  return LoggingWrapper(prefix, level, verbose);
}
} // namespace libLogging

namespace libLogging {

#ifdef IS_UNIX
const static std::string CLEAR_TERMINAL = "\x1b[2J";
const static std::string RESET = "\x1b[0m";
const static std::string BOLD = "\x1b[1m";
const static std::string DIM = "\x1b[2m";
const static std::string ITALIC = "\x1b[3m";
const static std::string UNDERLINE = "\x1b[4m";
const static std::string BLINKING = "\x1b[5m";
const static std::string BLACK_FG = "\x1b[30m";
const static std::string RED_FG = "\x1b[31m";
const static std::string GREEN_FG = "\x1b[32m";
const static std::string YELLOW_FG = "\x1b[33m";
const static std::string BLUE_FG = "\x1b[34m";
const static std::string MAGENTA_FG = "\x1b[35m";
const static std::string CYAN_FG = "\x1b[36m";
const static std::string WHITE_FG = "\x1b[37m";
const static std::string RED_BG = "\x1b[41m";
const static std::string GREEN_BG = "\x1b[42m";
const static std::string YELLOW_BG = "\x1b[43m";
const static std::string BLUE_BG = "\x1b[44m";
const static std::string MAGENTA_BG = "\x1b[45m";
const static std::string CYAN_BG = "\x1b[46m";
const static std::string WHITE_BG = "\x1b[47m";
const static std::string ERROR = "\x1b[31m\x1b[1m";
#elif IS_WINDOWS
const static std::string CLEAR_TERMINAL = "";
const static std::string RESET = "";
const static std::string BOLD = "";
const static std::string DIM = "";
const static std::string ITALIC = "";
const static std::string UNDERLINE = "";
const static std::string BLINKING = "";
const static std::string BLACK_FG = "";
const static std::string RED_FG = "";
const static std::string GREEN_FG = "";
const static std::string YELLOW_FG = "";
const static std::string BLUE_FG = "";
const static std::string MAGENTA_FG = "";
const static std::string CYAN_FG = "";
const static std::string WHITE_FG = "";
const static std::string RED_BG = "";
const static std::string GREEN_BG = "";
const static std::string YELLOW_BG = "";
const static std::string BLUE_BG = "";
const static std::string MAGENTA_BG = "";
const static std::string CYAN_BG = "";
const static std::string WHITE_BG = "";
const static std::string ERROR = "";
#endif
} // namespace libLogging

#endif // LOGANDOUT_HPP
