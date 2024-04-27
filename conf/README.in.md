
# @PROJECT_NAME@

@PROJECT_VERSION_MAJOR@.@PROJECT_VERSION_MINOR@.@PROJECT_VERSION_PATCH@

@PROJECT_NAME@ was developed for a project during our first and second
semester of university.
It generates batch files from JSON files, which can spawn terminals or
applications, that run under certain parameters specified within the
JSON file.

The project was carried out by **@AUTHORS@**.

## Table of Contents


1. [Build Instructions](#build-instructions)
   - [Linux](#linux)
   - [Windows](#windows)
   - [Generating Documentation](#generating-documentation)
2. [Documentation](#documentation)
   - [Project Structure](#project-structure)
3. [External Libraries](#external-libraries)
   - [easylogging++](#easylogging)
   - [LoggingWrapper](#loggingwrapper)
   - [jsoncpp](#jsoncpp)
4. [License](#license)

## Build Instructions

### Linux

```sh
git clone -b release https://github.com/DHBWProjectsIT23/JSON2Bat/
cd JSON2Bat
cmake -S . -B build
cmake --build build
```

#### UNIX Compiler Compatibility

The project has been tested with GCC version 10.5+ and Clang version 14+.

### Windows

The project has been tested on windows using MinGW and Ninja.

### Build with MinGW

MinGW can be installed by following Steps 1 through 7 in this [tutorial](https://code.visualstudio.com/docs/cpp/config-mingw)

```powershell
git clone -b release https://github.com/DHBWProjectsIT23/JSON2Bat/
cd JSON2Bat
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```
*The project was tested using MinGW with the above mentioned installation and
using [this](https://github.com/marketplace/actions/install-mingw) GitHub Action.*

### Build with Ninja

The Ninja binary can be found [here](https://github.com/ninja-build/ninja/releases). Alternatively Ninja can be build from [source](https://github.com/ninja-build/ninja).

```powershell
git clone -b release https://github.com/DHBWProjectsIT23/JSON2Bat/
cd JSON2Bat
cmake -S . -B build -G "Ninja"
cmake --build build
```

*The project was tested using Ninja v1.12.0 on a local machine and using v1.10 using [this](https://github.com/marketplace/actions/setup-ninja) GitHub Action.*

### Generating Documentation

If the *doxygen* executable is installed local documentation can be
generated using:

```sh
git clone -b release https://github.com/DHBWProjectsIT23/JSON2Bat/
cd JSON2Bat
cmake -S . -B build
cmake --build build --target doxygen_build
```

## Documentation

The documentation for this project can be found
[here](@PROJECT_HOMEPAGE_URL@).
A PDF version can be found [here](assets/@PROJECT_NAME@.pdf) and a short man page can be found [here](assets/man/@EXECUTABLE_NAME@.troff).

### Project Structure

The project directory is structured as follows:

- assets > *Includes files, not directly related to the code*
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
For Windows system a prebuild version is included.

## License

The project is published under the Apache License V2.0.
Check the [license file](LICENSE) for more information!
