# Generating files
configure_file(${PROJECT_SOURCE_DIR}/conf/config.hpp.in
               ${PROJECT_SOURCE_DIR}/src/include/utility/config.hpp)
configure_file(${PROJECT_SOURCE_DIR}/conf/README.in.md
               ${PROJECT_SOURCE_DIR}/README.md)

