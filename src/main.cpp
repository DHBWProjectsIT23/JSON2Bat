#include "config.hpp"
#include <LoggingWrapper.hpp>
#include <jsoncpp/json.h>

INITIALIZE_EASYLOGGINGPP

namespace WIP {
void setupEasyLogging();
}

int main(int argc, char* argv[])
{
    // Setup easylogging++
    WIP::setupEasyLogging();
    // Print some information about the Project
    // This is just for show and should be removed later
    // This kind of information should later be accesible with the cli
    OUTPUT << "----------\n"
           << "Project information:\n"
           << "----------\n"
           << PROJECT_NAME << " v" << MAJOR_VERSION << "." << MINOR_VERSION << "."
           << PATCH_VERSION << "\n"
           << DESCRIPTION << "\n"
           << "Authors: " << AUTHORS << "\n";
    OUTPUT << "\n----------\n"
           << "LoggingWrapper examples"
           << "\n----------\n";
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
    LOG_INFO << "Exiting...";
    return 0;
}

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
} // namespace WIP
