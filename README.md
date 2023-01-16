# Argparsor

Parse and stock options from argc and argv.  
Inspired from python library [python.readthedocs.io/library/argparse](https://python.readthedocs.io/en/latest/library/argparse.html).  
Examples at [docs/examples.md](docs/examples.md).

## Quick Start

```cpp
#include <iostream>

#include "mblet/argparsor.h"

enum eLogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExist*/, const std::string& argument) {
    static const std::pair<std::string, eLogLevel> pairLogLevels[] = {
        std::pair<std::string, eLogLevel>("DEBUG", DEBUG),
        std::pair<std::string, eLogLevel>("INFO", INFO),
        std::pair<std::string, eLogLevel>("WARNING", WARNING),
        std::pair<std::string, eLogLevel>("ERROR", ERROR)
    };
    static const std::map<std::string, eLogLevel> logLevels(pairLogLevels, pairLogLevels + sizeof(pairLogLevels) / sizeof(*pairLogLevels));

    logLevel = logLevels.at(argument);
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO;

    mblet::Argparsor args;
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v").flag("--version").help("help of version option")
        .action(args.VERSION).defaults("Version: 0.0.0");
    args.addArgument("--option").help("help of option");
    args.addArgument("--log-level").help("help of log-level").metavar("LEVEL")
        .valid(new mblet::Argparsor::ValidChoise(args.vector("DEBUG", "INFO", "WARNING", "ERROR")))
        .defaults("INFO")
        .dest(logLevel, argToLogLevel);
    try {
        args.parseArguments(argc, argv, true);
        std::cout << "ARGUMENT: " << args["ARGUMENT"] << '\n';
        if (args["--option"]) {
            std::cout << "--option: " << args["--option"] << '\n';
        }
        std::cout << "--log-level: ";
        switch (logLevel) {
            case DEBUG:
                std::cout << "DEBUG";
                break;
            case INFO:
                std::cout << "INFO";
                break;
            case WARNING:
                std::cout << "WARNING";
                break;
            case ERROR:
                std::cout << "ERROR";
                break;
        }
        std::cout << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}
```

```
$ ./a.out --version
Version: 0.0.0
$ ./a.out -h
usage: a.out [-h] [-v] [--log-level LEVEL] [--option OPTION] -- ARGUMENT

positional arguments:
  ARGUMENT              help of argument (required)

optional arguments:
  -h, --help            show this help message and exit
  -v, --version         help of version option
  --log-level LEVEL     help of log-level (default: INFO)
  --option OPTION       help of option
$ ./a.out
./a.out: argument is required -- 'ARGUMENT'
$ ./a.out 42 --log-level Foo
./a.out: "Foo" is not a choise value ("DEBUG", "INFO", "WARNING", "ERROR") -- '--log-level'
$ ./a.out 42
ARGUMENT: 42
--log-level: INFO
$ ./a.out 42 --log-level DEBUG --option Bar
ARGUMENT: 42
--option: Bar
--log-level: DEBUG
```

## Build

```bash
# Static Release
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=0 .. && make -j && make install; popd
# Dynamic Release
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=1 .. && make -j && make install; popd

# Static Release C++98
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=98 -DBUILD_SHARED_LIBS=0 .. && make -j && make install; popd
# Dynamic Release C++98
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=98 -DBUILD_SHARED_LIBS=1 .. && make -j && make install; popd

# Install with custom directory
mkdir build; pushd build; cmake -DCMAKE_INSTALL_PREFIX="YOUR_INSTALL_PATH" .. && make -j && make install; popd

# Example
mkdir build; pushd build; cmake -DBUILD_EXAMPLE=1 .. && make -j; popd

# Single Include + Test
mkdir build; pushd build; cmake -DBUILD_SINGLE_INCLUDE=1 -DBUILD_TESTING=1 .. && make -j; popd

# Tests + Coverage
mkdir build; pushd build; cmake -DBUILD_SHARED_LIBS=0 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=1 -DBUILD_COVERAGE=1 -DCMAKE_CXX_STANDARD=98 .. && make -j && make test -j; popd
```

## Option format

Short format
```bash
"-b"          # [b] == true
"-s" "Simple" # [s] == Simple
"-sSimple"    # [s] == Simple
"-s=Simple"   # [s] == Simple
"-bsSimple"   # [b] == true and [s] == Simple
"-bs=Simple"  # [b] == true and [s] == Simple
```

Long format
```bash
"--boolean"         # [boolean] == true
"--simple" "Simple" # [simple] == Simple
"--simple=Simple"   # [simple] == Simple
"-simple" "Simple"  # (alternative) [simple] == Simple
"-simple=Simple"    # (alternative) [simple] == Simple
```

## Methods

### addArgument

Define how a single command-line argument should be parsed.

```cpp
std::vector<double> doublesFromArg;
mblet::Argparsor args;
args.addArgument({"-E", "--example"}) // Either a name or a list of option strings, e.g. foo or -f, --foo
    .flag("--new-example")            // Add option strings e.g. -f, --foo
    .action(args.INFINITE)            // The basic type of action to be taken when this argument is encountered at the command line
    .help("help message")             // A brief description of what the argument does
    .required(true)                   // Whether or not the command-line option may be omitted(optionals only)
    .metavar("ARGUMENT")              // A name for the argument in usage messages
    .nargs(1)                         // The number of command-line arguments that should be consumed
    .defaults({"0"})                  // A list of default strings argument value
    .valid(new mblet::Argparsor::ValidMinMax(0, 100)) // Validate class from IValid interface
    .dest(doublesFromArg);            // Fill argument in destination
```

### parseArguments

Convert argument strings to objects and assign them as attributes of the argparsor map.  
Previous calls to add_argument() determine exactly what objects are created and how they are assigned.

```cpp
void parseArguments(
    int argc,
    char* argv[],
    bool alternative = false, // active parsing for accept long option with only one '-' character
    bool strict = false       // active exception if not all argument is used else you can take additionnal argument with getAdditionalArguments method
);
```

## Vector

Vector is a object can be initialize with initialize string list or single string or for C++98 with `vector` method.

```cpp
mblet::Argparsor args;
args.addArgument("--simple");
args.addArgument({"-s", "--simple"});
args.addArgument("-s").flag("--simple");
args.addArgument(args.vector("-s", "--simple"));     // C++98
args.addArgument((const char*[]){"-s", "--simple"}); // C++98
```

## Action

List of action

### DEFAULT

This just stores the argument’s value. This is the default action.  
Example at [docs/examples.md/none](docs/examples.md#none).

### APPEND

This stores a list, and appends each argument value to the list. It is useful to allow an option to be specified multiple times. If the default value is non-empty, the default elements will be present in the parsed value for the option, with any values from the command line appended after those default values.  
Example at [docs/examples.md/append](docs/examples.md#append).

### EXTEND

This stores a list, and extends each argument value to the list.  
Example at [docs/examples.md/extend](docs/examples.md#extend).

### HELP

This case used for create the help text.  
⚠ Can only use this action after constructor with false parameter.
```cpp
mblet::Argparsor args(false);
```
Example at [docs/examples.md/help](docs/examples.md#help).

### INFINITE

This stores a list.  
Example at [docs/examples.md/infinite](docs/examples.md#infinite).

### STORE_FALSE

This case used for storing the values `false` respectively.  
Example at [docs/examples.md/storefalse](docs/examples.md#storefalse).

### STORE_TRUE

This case used for storing the values `true` respectively.  
Example at [docs/examples.md/storetrue](docs/examples.md#storetrue).

### VERSION

This case used for storing the version text with `defaults` method.  
Example at [docs/examples.md/version](docs/examples.md#version).

## Valid

You can check format of argument with IValid interface object.  
Example of Custom Valid at [docs/examples.md/custom-valid-transform](docs/examples.md#custom-valid-transform).

### ValidNumber

Check if arguments are number.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidNumber());
```

### ValidMinMax

Check if arguments are number and if in range of min-max.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidMinMax(0, 100));
```

### ValidChoise

Check if arguments are in choise.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidChoise(args.vector("foo", "bar")));
```

### ValidPath

Check if arguments are valid path/dir/file.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath());
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath(mblet::Argparsor::ValidPath::IS_DIR));
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath(mblet::Argparsor::ValidPath::IS_FILE));
```

## Dest

Argument filler  
Example at [docs/dest.md](docs/dest.md).

```cpp
unsigned long value;
args.addArgument("--arg").dest(value);
```

## Setter

### Usage

Replace usage message

```cpp
void setUsage(const char* usage);
```

### Usage width column

Change the width of usage column.  
Example at [docs/usageWidth.md](docs/usageWidth.md).

```cpp
void setUsageWidth(std::size_t padWidth, std::size_t argsWidth, std::size_t sepWidth, std::size_t helpWidth);
```

### Description

Define a description message in usage.

```cpp
void setDescription(const char* description);
```

### Epilog

Define a epilog message in usage.

```cpp
void setEpilog(const char* epilog);
```

## Getter

### isAlternative

Check if alternative mode is activated after `parseArguments` method.

```cpp
bool isAlternative() const;
```

### isStrict

Check if strict mode is activated after `parseArguments` method.

```cpp
bool isStrict() const;
```

### getBinaryName

Return argv[0] after `parseArguments` method.

```cpp
const std::string& getBinaryName() const;
```

### getUsage

Get the usage message.

```cpp
std::string getUsage() const;
```

### getVersion

Get the version message.

```cpp
std::string getVersion() const;
```

### argumentExists

Check if argument was added

```cpp
bool argumentExists(const std::string& nameOrFlag) const;
```

### getArgument

Get argument object from key

```cpp
const Argument& getArgument(const std::string& nameOrFlag) const;
```

### getAdditionalArguments

Get the arguments if not used at not strict mode with `parseArguments`.

```cpp
const std::vector<std::string>& getAdditionalArguments() const;
```