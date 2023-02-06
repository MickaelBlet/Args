# Argparsor

Parse and stock options from argc and argv.  
Inspired from python library [python.readthedocs.io/library/argparse](https://python.readthedocs.io/en/latest/library/argparse.html).  
Documentations at [documentation](#documentations).

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

void argToLogLevel(eLogLevel& logLevel, bool /*isExists*/, const std::string& argument) {
    static const std::pair<std::string, eLogLevel> pairLogLevels[] = {
        std::pair<std::string, eLogLevel>("DEBUG", DEBUG), std::pair<std::string, eLogLevel>("INFO", INFO),
        std::pair<std::string, eLogLevel>("WARNING", WARNING), std::pair<std::string, eLogLevel>("ERROR", ERROR)};
    static const std::map<std::string, eLogLevel> logLevels(
        pairLogLevels, pairLogLevels + sizeof(pairLogLevels) / sizeof(*pairLogLevels));

    logLevel = logLevels.at(argument);
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO;

    mblet::Argparsor args;
    args.setVersion("Version: 0.0.0");
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v").flag("--version").help("help of version option").action(args.VERSION);
    args.addArgument({"-o", "--option"}).help("help of option").nargs(2).metavar("OPT1 OPT2");
    args.addArgument("--log-level")
        .flag("-l")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new mblet::Argparsor::ValidChoise({"DEBUG", "INFO", "WARNING", "ERROR"}))
        .defaults("INFO")
        .dest(logLevel, &argToLogLevel); // fill logLevel by argToLogLevel
    try {
        args.parseArguments(argc, argv, true, true, true, true);
        std::cout << "ARGUMENT: " << args["ARGUMENT"] << '\n';
        // check if option is exists
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
    }
    catch (const mblet::Argparsor::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::UsageException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what();
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
$ ./a.out 42 --log-level Foo
./a.out: "Foo" is not a choise value ("DEBUG", "INFO", "WARNING", "ERROR") -- '-l'
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

#### Definitions

|Methods|||
|---|---|---|
| [flag](docs/argument.md#flag) | [action](docs/argument.md#action) | [help](docs/argument.md#help-1) |
| [required](docs/argument.md#required) | [metavar](docs/argument.md#metavar) | [nargs](docs/argument.md#nargs) |
| [defaults](docs/argument.md#defaults) | [valid](docs/argument.md#valid) | [dest](docs/argument.md#dest) |

### parseArguments

Convert argument strings to objects and assign them as attributes of the argparsor map.  
Previous calls to [addArgument](docs/argparsor.md#addargument) determine exactly what objects are created and how they are assigned.

```cpp
void parseArguments(
    int argc,
    char* argv[],
    bool alternative = false,     // Active parsing for accept long option with only one '-' character
    bool strict = false,          // Active exception if not all argument is used else you can take additionnal argument with getAdditionalArguments method
    bool usageException = false,  // Throw a UsageException when help action is present in arguments else exit(0) the your program after output usage at stdout
    bool versionException = false // Throw a VersionException when version action is present in arguments else exit(0) the your program after output version at stdout
);
```

## Vector

Vector is a object can be initialize with initialize string list or single string or for C++98 with `vector` static method.

```cpp
mblet::Argparsor args;
args.addArgument("--simple");
args.addArgument({"-s", "--simple"});
args.addArgument("-s").flag("--simple");
args.addArgument(args.vector("-s", "--simple"));     // C++98
args.addArgument((const char*[]){"-s", "--simple"}); // C++98
```

## Documentations

### Argparsor

#### Basic

| Methods | Links |
|---------|-------|
| addArgument | [docs/argument.md#addargument](docs/argument.md#addargument) |
| parseArguments | [docs/parse.md#parseargument](docs/parse.md#parseargument) |

#### Access

| Methods | Links |
|---------|-------|
| argumentExists | [docs/argument.md#argumentexists](docs/argument.md#argumentexists) |
| getAdditionnalArguments | [docs/parse.md#getadditionnalarguments](docs/parse.md#getadditionnalarguments) |
| getArgument/operator[] | [docs/argument.md#getargument](docs/argument.md#getargument) |
| getBinaryName | [docs/parse.md#getbinaryname](docs/parse.md#getbinaryname) |
| getUsage | [docs/usage.md#getusage](docs/usage.md#getusage) |
| getVersion | [docs/usage.md#getversion](docs/usage.md#getversion) |
| isAlternative | [docs/parse.md#isalternative](docs/parse.md#isalternative) |
| isStrict | [docs/parse.md#isstrict](docs/parse.md#isstrict) |
| setDescription | [docs/usage.md#setdescription](docs/usage.md#setdescription) |
| setEpilog | [docs/usage.md#setepilog](docs/usage.md#setepilog) |
| setUsage | [docs/usage.md#setusage](docs/usage.md#setusage) |
| setUsageWidth | [docs/usage.md#setusagewidth](docs/usage.md#setusagewidth) |
| vector | [docs/usage.md#vector](docs/usage.md#vector) |

### Argument

#### Definition

| Methods | Links |
|---------|-------|
| flag | [docs/argument.md#flag](docs/argument.md#flag) |
| action | [docs/argument.md#action](docs/argument.md#action) |
| help | [docs/argument.md#help](docs/argument.md#help) |
| required | [docs/argument.md#required](docs/argument.md#required) |
| metavar | [docs/argument.md#metavar](docs/argument.md#metavar) |
| nargs | [docs/argument.md#nargs](docs/argument.md#nargs) |
| defaults | [docs/argument.md#defaults](docs/argument.md#defaults) |
| *valid* | [docs/argument.md#valid](docs/argument.md#valid) |
| *dest* | [docs/argument.md#dest](docs/argument.md#dest) |

#### Access

| Methods | Links |
|---------|-------|
| *count* | [docs/argument.md#count](docs/argument.md#count) |
| isExists | [docs/argument.md#isexists](docs/argument.md#isexists) |
| isNumber | [docs/argument.md#isnumber](docs/argument.md#isnumber) |
| isRequired | [docs/argument.md#isrequired](docs/argument.md#isrequired) |
| getNargs | [docs/argument.md#getnargs](docs/argument.md#getnargs) |
| getHelp | [docs/argument.md#gethelp](docs/argument.md#gethelp) |
| getMetavar | [docs/argument.md#getmetavar](docs/argument.md#getmetavar) |
| getNameOrFlags | [docs/argument.md#getnameorflags](docs/argument.md#getnameorflags) |
| getDefaults | [docs/argument.md#getdefaults](docs/argument.md#getdefaults) |
| getAction | [docs/argument.md#getaction](docs/argument.md#getaction) |
| getString | [docs/argument.md#getstring](docs/argument.md#getstring) |
| getNumber | [docs/argument.md#getnumber](docs/argument.md#getnumber) |
| operator bool() | [docs/argument.md#operator-bool](docs/argument.md#operator-bool) |
| operator std::string() | [docs/argument.md#operator-string](docs/argument.md#operator-string) |
| operator\<\< | [docs/argument.md#operator-t](docs/argument.md#operator-stream-insertion) |

### Examples

[docs/examples.md](docs/examples.md).