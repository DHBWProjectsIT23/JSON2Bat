# Generating files
configure_file(${PROJECT_SOURCE_DIR}/conf/config.in.hpp
        ${PROJECT_SOURCE_DIR}/src/include/config.hpp)
configure_file(${PROJECT_SOURCE_DIR}/conf/README.in.md
        ${PROJECT_SOURCE_DIR}/README.md)
configure_file(${PROJECT_SOURCE_DIR}/conf/NewREADME.in.md
        ${PROJECT_SOURCE_DIR}/NewREADME.md)

