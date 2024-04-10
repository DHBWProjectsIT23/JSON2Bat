#include <string>

namespace utilities {
class Utils {
  public:
    static void setupEasyLogging(const std::string &configFile);
    static bool checkIfFileExists(const std::string &fileName);
    static bool checkFileEnding(const std::string &fileName);
    static bool
    askToContinue(const std::string &prompt = "Do you want to continue? (Y/N)\n");
};
} // namespace utilities
