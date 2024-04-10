# Trying to find some packages
# This is currently just for testing. My plan is to add
# more automation in order to be compatible with different
# systems/compilers.
find_package(Catch2)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

add_library(LoggingWrapper LoggingWrapper.cpp easylogging++.cc)
target_include_directories(LoggingWrapper PUBLIC ${PROJECT_SOURCE_DIR}/include)
if(WIN32)
  target_compile_definitions(LoggingWrapper PRIVATE IS_WINDOWS)
elseif(UNIX)
  target_compile_definitions(LoggingWrapper PRIVATE IS_UNIX)
endif()
# Linking necessary libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/lib/libjsoncpp.a
  LoggingWrapper
)
