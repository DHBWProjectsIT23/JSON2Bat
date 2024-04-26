# Add LoggingWrapper Library
add_library(LoggingWrapper LoggingWrapper.cpp easylogging++.cc)

# Check OS to define necessary macros (for Styling)
target_include_directories(LoggingWrapper PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(WIN32)
  target_compile_definitions(LoggingWrapper PRIVATE IS_WINDOWS)
elseif(UNIX)
  target_compile_definitions(LoggingWrapper PRIVATE IS_UNIX)
endif()

# Linking necessary libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  jsoncpp
  LoggingWrapper)

if(WIN32)
  add_library(xgetopt ${PROJECT_SOURCE_DIR}/lib/xgetopt.c)
  target_include_directories(xgetopt PRIVATE ${PROJECT_SOURCE_DIR}/include)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/compiled/libjsoncpp.a
    LoggingWrapper
    xgetopt)
endif()
