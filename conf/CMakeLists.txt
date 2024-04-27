######## GENERATE FILES ########

# Directory where config for easylogging will be found
set(LOG_CONFIG ${PROJECT_BINARY_DIR}/config/easylogging.conf)

# config.hpp used in the project
configure_file(${PROJECT_SOURCE_DIR}/conf/config.in.hpp
        ${PROJECT_SOURCE_DIR}/src/include/config.hpp)

# README.md with version information etc.
configure_file(${PROJECT_SOURCE_DIR}/conf/README.in.md
        ${PROJECT_SOURCE_DIR}/README.md)

# easylogging config to ensure consistend log output and file location are consistent
configure_file(${PROJECT_SOURCE_DIR}/conf/easylogging.in.conf
        ${LOG_CONFIG})

# Man page with latest info
configure_file(${PROJECT_SOURCE_DIR}/conf/man1.in.troff
        ../assets/man/${EXECUTABLE_NAME}.troff)

