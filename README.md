# Argparsor

Parse and stock options from argc and argv  
Examples at [examples.md](docs/examples.md)

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
    .dest(doublesFromArg);            // Fill argument in destination from << operator
```

### parseArguments

Convert argument strings to objects and assign them as attributes of the argparsor map.  
Previous calls to add_argument() determine exactly what objects are created and how they are assigned

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
Example at [examples.md/none](docs/examples.md#none).

### APPEND

This stores a list, and appends each argument value to the list. It is useful to allow an option to be specified multiple times. If the default value is non-empty, the default elements will be present in the parsed value for the option, with any values from the command line appended after those default values.  
Example at [examples.md/append](docs/examples.md#append).

### EXTEND

This stores a list, and extends each argument value to the list.  
Example at [examples.md/extend](docs/examples.md#extend).

### HELP

This case used for create the help text.  
⚠ Can only use this action after constructor with false parameter.
```cpp
mblet::Argparsor args(false);
```
Example at [examples.md/help](docs/examples.md#help).

### INFINITE

This stores a list.  
Example at [examples.md/infinite](docs/examples.md#infinite).

### STORE_FALSE

This case used for storing the values `false` respectively.  
Example at [examples.md/storefalse](docs/examples.md#storefalse).

### STORE_TRUE

This case used for storing the values `true` respectively.  
Example at [examples.md/storetrue](docs/examples.md#storetrue).

### VERSION

This case used for storing the version text with `defaults` method.  
Example at [examples.md/version](docs/examples.md#version).

## Valid

You can check format of argument with IValid interface object.  
Example of Custom Valid at [examples.md/custom-valid-transform](docs/examples.md#custom-valid-transform).

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
Check if arguments are in choise
```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidChoise(args.vector("foo", "bar")));
```

### ValidPath
Check if arguments are valid path/dir/file
```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath());
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath(mblet::Argparsor::ValidPath::IS_DIR));
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath(mblet::Argparsor::ValidPath::IS_FILE));
```

## Build

```bash
# Static
mkdir build; pushd build; cmake .. && make -j && make install; popd
# Dynamic
mkdir build; pushd build; cmake -DBUILD_SHARED_LIBS=1 .. && make -j && make install; popd
# Static C++98
mkdir build; pushd build; cmake -DCMAKE_CXX_STANDARD=98 .. && make -j && make install; popd
# Example + Tests + Coverage
mkdir build; pushd build; cmake -DBUILD_EXAMPLE=1 -DBUILD_TESTING=1 -DBUILD_COVERAGE=1 -DCMAKE_CXX_STANDARD=98 .. && make -j && make test -j; popd
# Install with custom directory
mkdir build; pushd build; cmake -DCMAKE_INSTALL_PREFIX="YOUR_INSTALL_PATH" .. && make -j && make install; popd
```