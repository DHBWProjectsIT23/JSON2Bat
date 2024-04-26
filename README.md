[![Building on Windows](https://github.com/DHBWProjectsIT23/JSON2Bat/actions/workflows/cmake-windows.yml/badge.svg?branch=main)](https://github.com/DHBWProjectsIT23/JSON2Bat/actions/workflows/cmake-windows.yml) 
[![Building on Linux](https://github.com/DHBWProjectsIT23/JSON2Bat/actions/workflows/cmake-linux.yml/badge.svg?branch=main)](https://github.com/DHBWProjectsIT23/JSON2Bat/actions/workflows/cmake-linux.yml)
[![Documentation Deployed](https://github.com/DHBWProjectsIT23/JSON2Bat/actions/workflows/doxygenPages.yml/badge.svg)](https://github.com/DHBWProjectsIT23/JSON2Bat/actions/workflows/doxygenPages.yml)
# JSON2Batch

JSON2Batch was developed during a project during our first and second
semester of university.
It generates batch files from JSON files, which can spawn terminals or
applications, that run under certain parameters specified within the
JSON file.

The project was carried out by **Elena Schwarzbach, Max Rodler, Simon Blum, Sonia Sinaci**.

## Table of Contents

<!--toc:start-->
- [JSON2Batch](#projectname)
  1. [Table of Contents](#table-of-contents)
  2. [Build Instructions](#build-instructions)
    - [Linux](#linux)
    - [Windows](#windows)
    - [Generating Documentation](#generating-documentation)
  3. [Documentation](#documentation)
    - [Project Structure](#project-structure)
  4. [External Libraries](#external-libraries)
    - [easylogging++](#easylogging)
    - [LoggingWrapper](#loggingwrapper)
    - [jsoncpp](#jsoncpp)
  5. [License](#license)
<!--toc:end-->


## Build Instructions

### Linux

```sh
git clone https://github.com/DHBWProjectsIT23/JSON2Bat/!TODO
cmake -S . -B build --config Release
cmake --build build
```

#### UNIX Compiler Compatibility

The project has been tested with GCC version >= 10.5 and Clang version > 14.

### Windows

@TODO Fix Windows

#### Windows Compiler Compatibility

### Generating Documentation

If the *doxygen* executable is installed local documentation can be
generated using:

```sh
git clone https://github.com/DHBWProjectsIT23/JSON2Bat/!TODO
cmake -S . -B build --config Release
cmake --build build --target doxygen_build
```

## Documentation

The documentation for this project can be found
[here](https://dhbwprojectsit23.github.io/JSON2Bat).
A PDF version can be found [here]() and a short man page can be found [here]().

### Project Structure

The project directory is structured as follows:

- assets > *Includes files, not directly related to the code*
- man > *Includes the man page*
- conf > *Includes files which will be configured by CMake*
- include > *Includes header files for external libraries*
- lib > *Includes source/binary files for external libraries*
- src > *Includes the source code for the project*
  - sources > *Includes all ".cpp" files*
  - include > *Includes all ".hpp" files*
  - main.cpp

## External Libraries

### easylogging++

The [easylogging++](https://github.com/abumq/easyloggingpp) library is used for logging within the application.
The configuration for the library is done via a logging file which can be found in [conf/easylogging.in.conf](conf/easylogging.in.conf).
Cmake configures this file into the binary directory upon building. If the configuration file is removed,
the application will
no longer run.

### LoggingWrapper

While easylogging++ is used for the logging back--end
within the code there are little remains apart from the configuration.
The logging and output of the application is done over a self written wrapper. 
Altough it is self written, due to it beeing not part of the project
we consider it an external libraries.
The wrapper is used to simplify parallel output to stdout and the logfile and also enables increased output to stdout for the verbose mode.
A few macros are defined for use within the application:

- OUTPUT > *Outputs to stdout and the logfile*
- LOG_INFO > *By default only outputs to the logfile*
- LOG_WARNING > *Formats text and outputs to stdout and the logfile*
- LOG_ERROR > *Same as LOG_WARNING but in red and bold*

The macros can be used with streaming in the same way as std::cout would be used.
Furthermore, some rudimentary performance tests showed, that the use of the wrapper, does not affect performance in
comparison to using both std::cout and easylogging itself.

### jsoncpp

For parsing the JSON files, the [jsoncpp](https://github.com/open-source-parsers/jsoncpp) library is used.
On UNIX system this library can simply be installed using the systems package manager (tested with WSL/Ubuntu and Arch).
For Windows system a prebuild version is included - See [Windows](#windows) for more information.

## License

The project is published under the Apache License V2.0.
Check the [license file](LICENSE) for more information!
