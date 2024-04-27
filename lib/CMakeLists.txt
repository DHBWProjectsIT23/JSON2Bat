######## LOGGING WRAPPER ########
add_library(LoggingWrapper LoggingWrapper.cpp easylogging++.cc)
target_include_directories(LoggingWrapper PRIVATE ${PROJECT_SOURCE_DIR}/include)


######## LIBRARIES ########
if(UNIX)
  # CLI Styling is only used on Unix
  target_compile_definitions(LoggingWrapper PRIVATE IS_UNIX)
  # Link systemlibrary jsoncpp on Unix
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE
          jsoncpp
          LoggingWrapper)
else()
  # CLI Styling is only used on Unix
  target_compile_definitions(LoggingWrapper PRIVATE IS_WINDOWS)
  # Link precompiled jsoncpp for windows
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE
          ${PROJECT_SOURCE_DIR}/lib/compiled/libjsoncpp.a
          LoggingWrapper)
endif()


