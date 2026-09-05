# tbaricault/cli

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)

## Description

This is a C++23 library providing tools to created powerful CLIs. This library supports multiple types of arguments and provides auto-generated help and error messages.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
    - [Download and install](#download-and-install)
    - [Uninstall](#uninstall)
    - [CMake](#cmake)
    - [Include](#include)
    - [Environment](#environment)
- [Documentation](#documentation)
- [Examples](#examples)
    - [Simple CLI](#simple-cli)
    - [Positional argument](#positional-argument)
- [License](#license)

## Features

- Fluent API
- Easy to setup CLI
- Multiple argument types: positional, flag, optional, multiple
- Auto help message

## Requirements

- C++23 or later
- CMake 3.20 or later
- [tbaricault/str](https://github.com/Thomas-Baricault/tbaricault_str)
- [tbaricault/uniconvert](https://github.com/Thomas-Baricault/tbaricault_uniconvert)

## Usage

### Download and install

```bash
git clone https://github.com/Thomas-Baricault/tbaricault_cli.git
cd tbaricault_cli
make install
```

### Uninstall

```bash
make uninstall
```

### CMake

Add the library to your project:

```cmake
find_package(tbaricault_cli REQUIRED)

target_link_libraries(
    my_target
    PRIVATE
        tbaricault::cli
)
```

### Include

```cpp
#include <tbaricault/cli.hpp>
```

### Environment

If you have a custom C++ installation, you can edit the `ENV` variable in the `Makefile` to specify your environment path.

Example on Windows with MSYS2/MinGW64:

```makefile
ENV = C:/msys64/mingw64
```

## Documentation

Read the complete documentation at [https://docs.thomas-baricault.fr/cli](https://docs.thomas-baricault.fr/cli).

## Examples

### Simple CLI

```cpp
#include <iostream>
#include <tbaricault/cli.hpp>


int callback(const tbaricault::cli::Context& context, const tbaricault::cli::Command& command)
{
    auto& out = context.getOut();
    out << "Hello world!" << std::endl;
    if (command.getArg<tbaricault::cli::Flag>("flag"))
        out << "Flag is raised!" << std::endl;
    return (0);
}


int main(int argc, char** argv)
{
    tbaricault::cli::run(
        tbaricault::cli::Command()
            .setName(argv[0])
            .setDescription("This is a test CLI")
            .setCallback(callback)
            .add(tbaricault::cli::Flag()
                .setName("flag")
                .setShort('f')
                .setDescription("Simple test flag")),
        std::span(argv + 1, argc - 1)
    );

    return (0);
}
```

#### No arguments

```console
$ ./my_program
Hello world!
```

#### With flag

```console
$ ./my_program --flag
Hello world!
Flag is raised!

$ ./my_program -f
Hello world!
Flag is raised!
```

#### Help

```console
$ ./my_program --help
USAGE:
    ./my_program [OPTIONS]


DESCRIPTION:
    This is a test CLI


OPTIONS:

    --flag, -f
        Simple test flag

    --help, -h
        Show help message
```

### Positional argument

```cpp
#include <iostream>
#include <tbaricault/cli.hpp>


int callback(const tbaricault::cli::Context& context, const tbaricault::cli::Command& command)
{
    auto& out = context.getOut();
    out << "Hello world!" << std::endl;
    out << "Arg: " << command.getArg<tbaricault::cli::Positional<int>>("arg") << std::endl;
    return (0);
}


int main(int argc, char** argv)
{
    tbaricault::cli::run(
        tbaricault::cli::Command()
            .setName(argv[0])
            .setDescription("This is a test CLI")
            .setCallback(callback)
            .add(tbaricault::cli::Positional<int>()
                .setName("arg")
                .setDescription("Simple positional argument")),
        std::span(argv + 1, argc - 1)
    );

    return (0);
}
```

#### With no arguments

```console
$ ./my_program
Error: too few arguments provided
Try './my_program --help' for more informations
```

#### With invalid argument

```console
$ ./my_program abc
Error: invalid value for 'arg', given 'abc'
Try './my_program --help' for more informations
```

#### Valid argument

```console
$ ./my_program 73
Hello world!
Arg: 73
```

#### Help

```console
$ ./my_program --help
USAGE:
    ./my_program <arg> [OPTIONS]


DESCRIPTION:
    This is a test CLI


ARGUMENTS:

    arg
        Simple positional argument


OPTIONS:

    --help, -h
        Show help message
```

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.
