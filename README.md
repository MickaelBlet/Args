# Args

Parse and store options from `argc` and `argv`.
Inspired by the Python library [argparse](https://python.readthedocs.io/en/latest/library/argparse.html).
Header-only library available at [single_include/blet/args.h](single_include/blet/args.h).
Documentation available at [documentation](#documentation).

## Quick Start

```cpp
#include <iostream>

#include "blet/args.h"

enum eLogLevel {
    EMERG_LEVEL = 0,
    ALERT_LEVEL,
    CRITICAL_LEVEL,
    ERROR_LEVEL,
    WARNING_LEVEL,
    NOTICE_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExists*/, const std::string& argument) {
    if (argument == "EMERG" || argument == "0") {
        logLevel = EMERG_LEVEL;
    }
    else if (argument == "ALERT" || argument == "1") {
        logLevel = ALERT_LEVEL;
    }
    else if (argument == "CRITICAL" || argument == "2") {
        logLevel = CRITICAL_LEVEL;
    }
    else if (argument == "ERROR" || argument == "3") {
        logLevel = ERROR_LEVEL;
    }
    else if (argument == "WARNING" || argument == "4") {
        logLevel = WARNING_LEVEL;
    }
    else if (argument == "NOTICE" || argument == "5") {
        logLevel = NOTICE_LEVEL;
    }
    else if (argument == "INFO" || argument == "6") {
        logLevel = INFO_LEVEL;
    }
    else if (argument == "DEBUG" || argument == "7") {
        logLevel = DEBUG_LEVEL;
    }
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO_LEVEL;

    blet::Args args;
    // set message printed at version action option
    args.setVersion("Version: 0.0.0");
    // add required positional ARGUMENT
    args.addArgument("ARGUMENT").help("help of positional argument").required();
    // add version option (-v, --version)
    args.addArgument("-v").flag("--version").help("print version").action(args.VERSION);
    // add multiargument option (-o, --option)
    args.addArgument(args.vector("-o", "--option")).help("help of option").nargs(2).metavar("OPT1 OPT2");
    // add choise option (-l, --log-level) with "dest" function
    args.addArgument("--log-level")
        .flag("-l")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new blet::Args::ValidChoise(args.vector("0", "1", "2", "3", "4", "5", "6", "7", "EMERG", "ALERT",
                                                       "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG")))
        .defaults("INFO")
        .dest(logLevel, &argToLogLevel); // fill logLevel using argToLogLevel

    try {
        args.setStrict()           // throw exception with additional arguments
            .setAlternative()      // accept simple '-' with a long flag
            .setAbbreviate()       // accept abbreviated long options (e.g., --ver for --version)
            .setHelpException()    // throw exception when help flag is called
            .setVersionException() // throw exception when version flag is called
            .parseArguments(argc, argv); // add help option automatically
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
        case EMERG_LEVEL:
            std::cout << "EMERG";
            break;
        case ALERT_LEVEL:
            std::cout << "ALERT";
            break;
        case CRITICAL_LEVEL:
            std::cout << "CRITICAL";
            break;
        case ERROR_LEVEL:
            std::cout << "ERROR";
            break;
        case WARNING_LEVEL:
            std::cout << "WARNING";
            break;
        case NOTICE_LEVEL:
            std::cout << "NOTICE";
            break;
        case INFO_LEVEL:
            std::cout << "INFO";
            break;
        case DEBUG_LEVEL:
            std::cout << "DEBUG";
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
  ARGUMENT              help of positional argument (required)

optional arguments:
  -h, --help            show this help message and exit
  -l, --log-level LEVEL
                        help of log-level (default: INFO)
  -o, --option OPT1 OPT2
                        help of option
  -v, --version         print version
$ ./a.out
./a.out: argument is required -- 'ARGUMENT'
$ ./a.out 42 -log-level Foo
./a.out: "Foo" is not a valid choise ("0", "1", "2", "3", "4", "5", "6", "7", "EMERG", "ALERT", "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG") -- '-l'
$ ./a.out 42
ARGUMENT: 42
--log-level: INFO
$ ./a.out 42 --log-level=DEBUG --option Foo
./a.out: bad number of argument -- 'option'
$ ./a.out 42 -l7 -o Foo Bar
ARGUMENT: 42
--option: Foo, Bar
--log-level: DEBUG
```

## Build

```bash
# Static Release with install
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=0 .. && make -j && make install; popd
# Dynamic Release with install
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=1 .. && make -j && make install; popd

# Static Release C++98 with install
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=98 -DBUILD_SHARED_LIBS=0 .. && make -j && make install; popd
# Dynamic Release C++98 with install
mkdir build; pushd build; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=98 -DBUILD_SHARED_LIBS=1 .. && make -j && make install; popd

# Install with custom directory
mkdir build; pushd build; cmake -DCMAKE_INSTALL_PREFIX="YOUR_INSTALL_PATH" .. && make -j && make install; popd

# Example
mkdir build; pushd build; cmake -DBUILD_EXAMPLE=1 .. && make -j; popd

# Single Include + Test
mkdir build; pushd build; cmake -DBUILD_SINGLE_INCLUDE=1 -DBUILD_TESTING=1 .. && make -j; popd

# Tests + Coverage
mkdir build; pushd build; cmake -DBUILD_SHARED_LIBS=0 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=1 -DBUILD_COVERAGE=1 -DCMAKE_CXX_STANDARD=11 .. && make -j && make test -j; popd
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
"--ver"             # (abbreviated) [version] == true (if setAbbreviate is enabled)
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
    .required(true)                   // Whether or not the command-line option may be omitted (optionals only)
    .metavar("ARGUMENT")              // A name for the argument in usage messages
    .nargs(1)                         // The number of command-line arguments that should be consumed
    .defaults({"0"})                  // A list of default string argument values
    .valid(new blet::Args::ValidMinMax(0, 100)) // Validate class from IValid interface
    .dest(doublesFromArg);            // Fill argument in destination
```

#### Definitions

|Method|Description|
|---|---|
|[action](docs/argument.md#action)|The basic type of action to be taken when this argument is encountered at the command line.|
|[defaults](docs/argument.md#defaults)|A list of default string argument values.|
|[dest](docs/argument.md#dest)|Fill argument in destination.|
|[flag](docs/argument.md#flag)|Add option strings e.g. -f, --foo|
|[help](docs/argument.md#help-1)|A brief description of what the argument does.|
|[metavar](docs/argument.md#metavar)|A name for the argument in usage messages.|
|[nargs](docs/argument.md#nargs)|The number of command-line arguments that should be consumed.|
|[required](docs/argument.md#required)|Whether or not the command-line option may be omitted (optionals only).|
|[valid](docs/argument.md#valid)|Validate argument from IValid interface.|

### parseArguments

Convert argument strings to objects and assign them as attributes of the args map.  
Previous calls to [addArgument](docs/args.md#addargument) determine exactly what objects are created and how they are assigned.

```cpp
void parseArguments(int argc, char* argv[]);
```

#### Parse Options

```cpp
blet::Args& setStrict(); // Throw exception if not all arguments are used; otherwise, you can take additional arguments with getAdditionalArguments method
blet::Args& setAlternative(); // Enable parsing to accept long options with only one '-' character
blet::Args& setAbbreviate(); // Enable parsing to accept abbreviated long options (e.g., --ver matches --version); throws on ambiguity
blet::Args& setHelpException(); // Throw a HelpException when help action is present in arguments; otherwise, exit(0) after outputting usage to stdout
blet::Args& setVersionException(); // Throw a VersionException when version action is present in arguments; otherwise, exit(0) after outputting usage to stdout
```

## Abbreviated Options

When `setAbbreviate()` is enabled, long options can be specified by any unambiguous prefix:

```cpp
blet::Args args;
args.addArgument("--version").action(args.STORE_TRUE);
args.addArgument("--verbose").action(args.STORE_TRUE);
args.setAbbreviate();
```

```bash
./program --vers   # matches --version (unambiguous)
./program --verb   # matches --verbose (unambiguous)
./program --ver    # ERROR: ambiguous (matches both --version and --verbose)
./program --versio # matches --version (unambiguous)
```

**Important notes:**
- Only works with long options (starting with `--`)
- Exact matches always take precedence over abbreviations
- Throws `ParseArgumentException` if abbreviation is ambiguous
- Can be combined with `setAlternative()` and other parsing options

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

## Documentation

### Args Basic Methods

|Method|Description|
|---|---|
|[addArgument](docs/args.md#addargument)|Define how a single command-line argument should be parsed.|
|[parseArguments](docs/args.md#parsearguments)|Convert argument strings to objects and assign them as attributes of the args map.<br/>Previous calls to [addArgument](docs/args.md#addargument) determine exactly what objects are created and how they are assigned.<br/>If called without help action, defines '-h' and '--help' if not used.|

### Custom Usage

|Method|Description|
|---|---|
|[getDescription](docs/usage.md#getdescription)|Get the description message.|
|[getEpilog](docs/usage.md#getepilog)|Get the epilog message.|
|[getUsage](docs/usage.md#getusage)|Get the usage message.|
|[setDescription](docs/usage.md#setdescription)|Set the description in usage message.|
|[setEpilog](docs/usage.md#setepilog)|Set the epilog in usage message.|
|[setUsage](docs/usage.md#setusage)|Set the usage message.|
|[setUsageWidth](docs/usage.md#setusagewidth)|Set the Usage Widths.|


### Args Methods

|Method|Description|
|---|---|
|[argumentExists](docs/args.md#argumentexists)|Check if argument exists.|
|[clear](docs/args.md#clear)|Clear and reset with default values.|
|[getAdditionalArguments](docs/args.md#getadditionalarguments)|Get the vector of additional arguments.|
|[getArgument](docs/args.md#getargument)|Get the argument object.|
|[getBinaryName](docs/args.md#getbinaryname)|Get the binary name.|
|[getVersion](docs/args.md#getversion)|Get the version message.|
|[isAbbreviate](docs/args.md#isabbreviate)|Get the status of abbreviated options.|
|[isAlternative](docs/args.md#isalternative)|Get the status of alternative.|
|[isHelpException](docs/args.md#ishelpexception)|Get the status of helpException.|
|[isStrict](docs/args.md#isstrict)|Get the status of strict.|
|[isVersionException](docs/args.md#isversionexception)|Get the status of versionException.|
|[removeArguments](docs/args.md#removearguments)|Remove previously added arguments.|
|[setAbbreviate](docs/args.md#setabbreviate)|Enable parsing to accept abbreviated long options (e.g., --ver matches --version).|
|[setAlternative](docs/args.md#setalternative)|Enable parsing to accept long options with only one '-' character.|
|[setBinaryName](docs/args.md#setbinaryname)|Set the binary name.|
|[setHelpException](docs/args.md#sethelpexception)|Throw a HelpException when help action is present in arguments; otherwise, exit(0) after outputting usage to stdout.|
|[setStrict](docs/args.md#setstrict)|Throw exception if not all arguments are used; otherwise, you can take additional arguments with getAdditionalArguments method.|
|[setVersion](docs/args.md#setversion)|Set the version message.|
|[setVersionException](docs/args.md#setversionexception)|Throw a VersionException when version action is present in arguments; otherwise, exit(0) after outputting version to stdout.|
|[updateArgument](docs/args.md#updateargument)|Get the ref. of argument from name or flag.|

### Args::Argument Construct Methods

|Method|Description|
|---|---|
|[action](docs/argument.md#action)|Add an action when this argument is encountered at the command line.|
|[defaults](docs/argument.md#defaults)|Define the default string values.|
|[dest](docs/argument.md#dest)|Define a reference to an object to insert the value after [parseArguments](docs/args.md#parsearguments) method.|
|[flag](docs/argument.md#flag)|Add flag to argument object.|
|[help](docs/argument.md#help-1)|Set the help description message for this argument.|
|[metavar](docs/argument.md#metavar)|A name for the argument in usage messages.|
|[nargs](docs/argument.md#nargs)|The number of command-line arguments that should be consumed by this object.|
|[required](docs/argument.md#required)|Whether or not the command-line argument may be omitted.|
|[valid](docs/argument.md#valid)|You can check format of argument with IValid interface.|

### Args::Argument::Action Types

|Enum|Description|
|---|---|
|[APPEND](docs/argument.md#append)|This stores a list, and appends each argument value to the list.<br/>It is useful to allow an option to be specified multiple times.|
|[EXTEND](docs/argument.md#extend)|This stores a list, and extends each argument value to the list.|
|[HELP](docs/argument.md#help)|This is used to create the help flag.|
|[INFINITE](docs/argument.md#infinite)|This stores a list.|
|[NONE](docs/argument.md#none)|This just stores the argument's value. **This is the default action**.|
|[STORE_FALSE](docs/argument.md#store_false)|This is used to store the value `false`.|
|[STORE_TRUE](docs/argument.md#store_true)|This is used to store the value `true`.|
|[VERSION](docs/argument.md#version)|This is used to define the version flag.|

### Args::Argument Access Methods

|Method|Description|
|---|---|
|[count](docs/argument.md#count)|After [parseArguments](docs/args.md#parsearguments) method check if number of this argument in argv.|
|[getAction](docs/argument.md#getaction)|Get [action](#argsargumentaction-types) option.|
|[getDefault](docs/argument.md#getdefault)|Get the default value of argument.|
|[getDefaults](docs/argument.md#getdefaults)|Get the default(s) value(s) of this argument.|
|[getHelp](docs/argument.md#gethelp)|Get [help](docs/argument.md#help-1) option.|
|[getMetavar](docs/argument.md#getmetavar)|Get [metavar](docs/argument.md#metavar) option.|
|[getNameOrFlags](docs/argument.md#getnameorflags)|Get the name or flag(s) of this argument.|
|[getNargs](docs/argument.md#getnargs)|Get [nargs](docs/argument.md#nargs) option.|
|[getNumber](docs/argument.md#getnumber)|Get Number if [isNumber](docs/argument.md#isnumber).|
|[getString](docs/argument.md#getstring)|Get the string format of this argument.|
|[isExists](docs/argument.md#isexists)|After [parseArguments](docs/args.md#parsearguments) method check if this argument is present in *argv*.|
|[isNumber](docs/argument.md#isnumber)|Check if this argument is a number ("1234aaa" is true with 1234 like number).|
|[isRequired](docs/argument.md#isrequired)|Get [required](docs/argument.md#required) option.|
|[operator bool()](docs/argument.md#operator-bool)|Check if argument object [isExists](docs/argument.md#isexists).|
|[operator std::string()](docs/argument.md#operator-stdstring)|Call [getString](docs/argument.md#getstring) method.|
|[operator std::vector\<std::string>()](docs/argument.md#operator-stdvectorstdstring)|If the argument object contains a lot of one argument, you can get a std::vector of std::string.|
|[operator std::vector\<std::vector\<std::string> >()](docs/argument.md#operator-stdvectorstdvectorstdstring-)|If the argument object contains a lot of one argument with number of argument ([nargs](docs/argument.md#nargs)) bigger than one, you can get a std::vector of std::vector of std::string.|
|[operator T()](docs/argument.md#operator-t)|Call the [getNumber](docs/argument.md#getnumber) method with your custom type.|

### Examples

For more examples, see [docs/examples.md](docs/examples.md).