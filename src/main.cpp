#include <LoggingWrapper.hpp>
#include <jsoncpp/json.h>
#include <vector>

#include "CommandLineHandler.hpp"

INITIALIZE_EASYLOGGINGPP

namespace WIP {
void setupEasyLogging();
}

int main(int argc, char* argv[])
{
    // Setup easylogging++
    WIP::setupEasyLogging();

    if (argc < 2) {
        LOG_ERROR << "No options given!\n";
        cli::CommandLineHandler::printHelp();
        return 1;
    }

    std::vector<std::string> files =
                cli::CommandLineHandler::parseArguments(argc, argv);
    int counter = 0;
    OUTPUT << cli::CYAN << cli::ITALIC << "Debug - Inputted files:\n" << cli::RESET;

    for (const auto &file : files) {
        ++counter;
        OUTPUT << "\tFile " << counter << ": " << file << "\n";
    }

    LOG_INFO << "Exiting...";
    return 0;
}

/**
 * \todo Auslagern
 **/
namespace WIP {
/**
 * \brief Setup the easylogging++ logger
 * \todo
 * - Should be moved to a separate file
 * - Proper configuration of easylogging++
 */
void setupEasyLogging()
{
    el::Configurations conf("conf/easylogging.conf");
    el::Loggers::reconfigureAllLoggers(conf);
}

/** \note
 * Example of using the logging wrapper!
 * For some cases, I thought would be most common, there are
 * definitions/macros (OUTPUT, LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_DEBUG)
 * that can be used. For other cases, the utils::log function can be used
 * directly. Possibilitys:
 * - utils::log(bool verbose = false) - Logs INFO, verbose can be set to true
 *
 * - utils::log(LogLevel level) - Logs the given level, verbose is false,
 * however only INFO can be verbose anyway, as all other always print to the
 * console
 *
 * - utils::log(comst std::string &prefix, bool verbose = false) - Logs INFO,
 *     with a custom prefix, verbose can be set to true
 *
 * - utils::log(const std::string &prefix, LogLevel level, bool verbose =
 * false) - Logs the given level, with a custom prefix, verbose can be set to
 * true
 *
 * All of the above return a std::ostream, so you can use it like e.g. a
 * normal std::cout!
 */
void printLoggingExample()
{
    OUTPUT << "\n----------\n"
           << "LoggingWrapper examples"
           << "\n----------\n";
    OUTPUT << "Hello I am a normal output! I will also be logged!\n";
    LOG_INFO
            << "I am a log info, I won't get printed to the console automatically!\n";
    // The true defines that it is verbose - the default level is INFO
    utils::log(true) << "I am a log info, I will get printed to the console!\n";
    LOG_WARNING << "I am a log warning, I will get printed to the console!\n";
    LOG_ERROR << "I am a log error, I will get printed to the console!\n";
    LOG_DEBUG << "I am a log debug, I will get printed to the console!\n";
    // False is the default value and can be omitted
    utils::log("Custom: ", false)
            << "I am a log with a prefix, I won't get printed to the console!\n";
    utils::log("Custom: ", true)
            << "I am a log with a prefix, I will get printed to the console!\n";
}
} // namespace WIP
