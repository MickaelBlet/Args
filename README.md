# Argparsor

Parse and stock options from argc and argv

Examples at [examples.md](doc/examples.md)

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

Define how a single command-line argument should be parsed

```cpp
mblet::Argparsor args;
args.addArgument(
    {"-E", "--example"}, // nameOrFlags: Either a name or a list of option strings, e.g. foo or -f, --foo
    mblet::Argparsor::NONE, // action: The basic type of action to be taken when this argument is encountered at the command line
    "help message", // help: A brief description of what the argument does

mblet::Argparsor::Argument &mblet::Argparsor::addArgument(
    const mblet::Argparsor::Vector &nameOrFlags,
    mblet::Argparsor::Action action,
    const char *help,
    bool isRequired,
    const char *metavar,
    std::size_t nArgs,
    const mblet::Argparsor::Vector &defaultArgs,
    mblet::Argparsor::IValid *valid,
    T &dest)
Argparsor::Argument& addArgument(
    const Vector& nameOrFlags,
    Argparsor::Action action,
                          const char* help, bool isRequired, const char* metavar,
                          std::size_t nArgs, const Vector& defaultArgs,
                          IValid* valid, T& dest)
void addArgument(
    const Vector& nameOrFlags, // Either a name or a list of option strings, e.g. foo or -f, --foo
    const char* actionOrDefault = NULL, // The basic type of action to be taken when this argument is encountered at the command line
    // action list: store_true, store_false, infinite, append, extend, version, help
    const char* help = NULL, // A brief description of what the argument does
    bool isRequired = false, // Whether or not the command-line option may be omitted (optionals only)
    const char* argsHelp = NULL, // A name for the argument in usage messages
    std::size_t nbArgs = 0, // The number of command-line arguments that should be consumed
    const Vector& defaultArgs = Vector() // The value produced if the argument is absent from the command line
);
```

### parseArguments

Convert argument strings to objects and assign them as attributes of the argparsor map.

Previous calls to add_argument() determine exactly what objects are created and how they are assigned

```cpp
void parseArguments(
    int argc,
    char* argv[],
    bool alternative = false, //active parsing for accept long option with only one '-' character
    bool strict = false // active exception if not all argument is used else you can take additionnal argument with getAdditionalArguments method
);

```

## Vector

Vector is a object can be initialize with initialize string list or single string or for c++98 with `vector` method.

```cpp
mblet::Argparsor args;
args.addArgument("--boolean");
args.addArgument({"-b", "--boolean"});
args.addArgument(args.vector("-b", "--boolean")); // C++98
```

## Build

```bash
# static build
mkdir build ; pushd build && cmake .. && make -j ; popd
# shared build
mkdir build ; pushd build && cmake -DBUILD_SHARED_LIBS=1 .. && make -j ; popd
# build examples
mkdir build ; pushd build && cmake -DBUILD_EXAMPLE=1 .. && make -j ; popd
# build and launch test (gcov and gtest required)
mkdir build ; pushd build && cmake -DBUILD_TESTING=1 -DBUILD_COVERAGE=1 .. && make -j && make test ; popd
# static build for c++98
mkdir build ; pushd build && cmake -DCMAKE_CXX_STANDARD=98 .. && make -j ; popd
```