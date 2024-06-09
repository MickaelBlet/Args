# Args

Parse and store options from `argc` and `argv`.  
Inspired by the Python library [argparse](https://python.readthedocs.io/en/latest/library/argparse.html).  
Header-only library available at [single_include/blet/args.h](single_include/blet/args.h).  
Documentations available at [documentations](#documentations).

## Quick Start

```cpp
#include <iostream>

#include "blet/args.h"

enum eLogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExists*/, const std::string& argument) {
    if (argument == "DEBUG") {
        logLevel = DEBUG;
    }
    else if (argument == "INFO") {
        logLevel = INFO;
    }
    else if (argument == "WARNING") {
        logLevel = WARNING;
    }
    else if (argument == "ERROR") {
        logLevel = ERROR;
    }
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO;

    blet::Args args;
    args.setVersion("Version: 0.0.0");
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v").flag("--version").help("help of version option").action(args.VERSION);
    args.addArgument(args.vector("-o", "--option")).help("help of option").nargs(2).metavar("OPT1 OPT2");
    args.addArgument("--log-level")
        .flag("-l")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new blet::Args::ValidChoise(args.vector("DEBUG", "INFO", "WARNING", "ERROR")))
        .defaults("INFO")
        .dest(logLevel, &argToLogLevel); // fill logLevel using argToLogLevel

    try {
        args.setStrict()           // except with additional argument
            .setAlternative()      // accept simple '-' with a long flag
            .setHelpException()    // except when help flag is called
            .setVersionException() // except when version flag is called
            .parseArguments(argc, argv);
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    std::cout << "ARGUMENT: " << args["ARGUMENT"] << '\n';
    // check if option exists
    if (args["--option"]) {
        std::cout << "--option: " << args["--option"][0] << ", " << args["--option"][1] << '\n';
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

    return 0;
}
```

```
$ ./a.out --version
Version: 0.0.0
$ ./a.out -h
usage: a.out [-h] [-l LEVEL] [-o OPT1 OPT2] [-v] -- ARGUMENT

positional arguments:
  ARGUMENT              help of argument (required)

optional arguments:
  -h, --help            show this help message and exit
  -l, --log-level LEVEL
                        help of log-level (default: INFO)
  -o, --option OPT1 OPT2
                        help of option
  -v, --version         help of version option
$ ./a.out
./a.out: argument is required -- 'ARGUMENT'
$ ./a.out 42 -log-level Foo
./a.out: "Foo" is not a valid choise ("DEBUG", "INFO", "WARNING", "ERROR") -- '-l'
$ ./a.out 42
ARGUMENT: 42
--log-level: INFO
$ ./a.out 42 --log-level=DEBUG --option Foo
./a.out: bad number of argument -- 'option'
$ ./a.out 42 -lDEBUG -o Foo Bar
ARGUMENT: 42
--option: Foo, Bar
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
blet::Args args;
args.addArgument({"-E", "--example"}) // Either a name or a list of option strings, e.g. foo or -f, --foo
    .flag("--new-example")            // Add option strings e.g. -f, --foo
    .action(args.INFINITE)            // The basic type of action to be taken when this argument is encountered at the command line
    .help("help message")             // A brief description of what the argument does
    .required(true)                   // Whether or not the command-line option may be omitted(optionals only)
    .metavar("ARGUMENT")              // A name for the argument in usage messages
    .nargs(1)                         // The number of command-line arguments that should be consumed
    .defaults({"0"})                  // A list of default string argument values
    .valid(new blet::Args::ValidMinMax(0, 100)) // Validate class from IValid interface
    .dest(doublesFromArg);            // Fill argument in destination
```

#### Definitions

|Methods|||
|---|---|---|
| [flag](docs/argument.md#flag) | [action](docs/argument.md#action) | [help](docs/argument.md#help-1) |
| [required](docs/argument.md#required) | [metavar](docs/argument.md#metavar) | [nargs](docs/argument.md#nargs) |
| [defaults](docs/argument.md#defaults) | [valid](docs/argument.md#valid) | [dest](docs/argument.md#dest) |

### parseArguments

Convert argument strings to objects and assign them as attributes of the args map.  
Previous calls to [addArgument](docs/args.md#addargument) determine exactly what objects are created and how they are assigned.

```cpp
void parseArguments(int argc, char* argv[]);
```

#### Parse Options

```cpp
blet::Args& setStrict(); // Activate exception if not all arguments are used; otherwise, you can take additional arguments with getAdditionalArguments method
blet::Args& setAlternative(); // Activate parsing to accept long option with only one '-' character
blet::Args& setHelpException(); // Throw a HelpException when help action is present in arguments; otherwise, exit(0) after outputting usage to stdout
blet::Args& setVersionException(); // Throw a VersionException when version action is present in arguments; otherwise, exit(0) after outputting version to stdout
```

## Vector

Vector is an object that can be initialized with an initializer list, single string, or for C++98 with the `vector` static method.

```cpp
blet::Args args;
args.addArgument("--simple");
args.addArgument({"-s", "--simple"});
args.addArgument("-s").flag("--simple");
args.addArgument(args.vector("-s", "--simple"));     // C++98
args.addArgument((const char*[]){"-s", "--simple"}); // C++98
```

## Documentations

### Args Basic Methods

|||
|---|---|
|[addArgument](docs/args.md#addargument)|[parseArguments](docs/args.md#parsearguments)|

### Custom Usage

|||
|---|---|
|[getDescription](docs/usage.md#getdescription)|[setDescription](docs/usage.md#setdescription)|
|[getEpilog](docs/usage.md#getepilog)|[setEpilog](docs/usage.md#setepilog)|
|[getUsage](docs/usage.md#getusage)|[setUsage](docs/usage.md#setusage)|
||[setUsageWidth](docs/usage.md#setusagewidth)|

### Args Methods

|||
|---|---|
|[argumentExists](docs/args.md#argumentexists)|
|[clear](docs/args.md#clear)|
|[getAdditionalArguments](docs/args.md#getadditionalarguments)|
|[getArgument](docs/args.md#getargument)|
|[getBinaryName](docs/args.md#getbinaryname)|[setBinaryName](docs/args.md#setbinaryname)|
|[getVersion](docs/args.md#getversion)|[setVersion](docs/args.md#setversion)|
|[isAlternative](docs/args.md#isalternative)|[setAlternative](docs/args.md#setalternative)|
|[isHelpException](docs/args.md#ishelpexception)|[setHelpException](docs/args.md#sethelpexception)|
|[isStrict](docs/args.md#isstrict)|[setStrict](docs/args.md#setstrict)|
|[isVersionException](docs/args.md#isversionexception)|[setVersionException](docs/args.md#setversionexception)|
|[removeArguments](docs/args.md#removearguments)|
|[updateArgument](docs/args.md#updateargument)|

### Args::Argument Construct Methods

||||
|---|---|---|
|[action](docs/argument.md#action)|[dest](docs/argument.md#dest)|[flag](docs/argument.md#flag)|
|[help](docs/argument.md#help-1)|[metavar](docs/argument.md#metavar)|[nargs](docs/argument.md#nargs)|
|[required](docs/argument.md#required)|[valid](docs/argument.md#valid)|[defaults](docs/argument.md#defaults)|

### Args::Argument::Action Types

||||
|---|---|---|
|[APPEND](docs/argument.md#append)|[NONE](docs/argument.md#none)|[EXTEND](docs/argument.md#extend)|
|[HELP](docs/argument.md#help)|[INFINITE](docs/argument.md#infinite)|[STORE_FALSE](docs/argument.md#store_false)|
|[STORE_TRUE](docs/argument.md#store_true)|[VERSION](docs/argument.md#version)|

### Args::Argument Access Methods

|||
|---|---|
|[count](docs/argument.md#count)|[getAction](docs/argument.md#getaction)|
|[getDefault](docs/argument.md#getdefault)|[getDefaults](docs/argument.md#getdefaults)|
|[getHelp](docs/argument.md#gethelp)|[getMetavar](docs/argument.md#getmetavar)|
|[getNameOrFlags](docs/argument.md#getnameorflags)|[getNargs](docs/argument.md#getnargs)|
|[getNumber](docs/argument.md#getnumber)|[getString](docs/argument.md#getstring)|
|[isExists](docs/argument.md#isexists)|[isNumber](docs/argument.md#isnumber)|
|[isRequired](docs/argument.md#isrequired)|[operator bool()](docs/argument.md#operator-bool)|
|[operator std::string()](docs/argument.md#operator-stdstring)|[operator std::vector\<std::string\>()](docs/argument.md#operator-stdvectorstdstring)|
|[operator T()](docs/argument.md#operator-t)|[operator std::vector\<std::vector\<std::string\> \>()](docs/argument.md#operator-stdvectorstdvectorstdstring)|

### Examples

For more examples, see [docs/examples.md](docs/examples.md).