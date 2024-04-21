find_package(Catch2)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

# Add LoggingWrapper Library
 add_library(LoggingWrapper LoggingWrapper.cpp easylogging++.cc)

# Check OS to define necessary macros (for Styling)
target_include_directories(LoggingWrapper PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(WIN32)
  target_compile_definitions(LoggingWrapper PRIVATE IS_WINDOWS)
elseif(UNIX)
  target_compile_definitions(LoggingWrapper PRIVATE IS_UNIX)
endif()

# Linking necessary libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  jsoncpp
  LoggingWrapper)
