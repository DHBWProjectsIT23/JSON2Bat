# Generating files
set(LOG_CONFIG ${PROJECT_BINARY_DIR}/config/easylogging.conf)

configure_file(${PROJECT_SOURCE_DIR}/conf/config.in.hpp
        ${PROJECT_SOURCE_DIR}/src/include/config.hpp)
configure_file(${PROJECT_SOURCE_DIR}/conf/README.in.md
        ${PROJECT_SOURCE_DIR}/README.md)
configure_file(${PROJECT_SOURCE_DIR}/conf/easylogging.in.conf
        ${LOG_CONFIG})

