# Argument

## flag

```cpp
Argument& flag(const char* flag__);
```

Add flag in argument object.

Example:
```cpp
Args args;
args.addArgument("-f").flag("--foo");
```

## action

```cpp
Argument& action(enum Action::eAction action__);
```

Add a action when this argument is encountered at the command line.

Action list:
- [NONE](#none)
- [APPEND](#append)
- [EXTEND](#extend)
- [HELP](#help)
- [INFINITE](#infinite)
- [STORE_FALSE](#store_false)
- [STORE_TRUE](#store_true)
- [VERSION](#version)

### NONE

This just stores the argument’s value. **This is the default action**.  
Example at [examples.md/none](examples.md#none).

### APPEND

This stores a list, and appends each argument value to the list. It is useful to allow an option to be specified multiple times. If the default value is non-empty, the default elements will be present in the parsed value for the option, with any values from the command line appended after those default values.  
Example at [examples.md/append](examples.md#append).

### EXTEND

This stores a list, and extends each argument value to the list.  
Example at [examples.md/extend](examples.md#extend).

### HELP

This case used for create the help flag.  
⚠ Can only use this action after constructor with false parameter or remove the last help flags.  

```cpp
blet::Args args(false);
// or
// blet::Args args;
// args.removeArgument(args.vector("-h", "--help"));
```

Example at [examples.md/help](examples.md#help).

### INFINITE

This stores a list.  
Example at [examples.md/infinite](examples.md#infinite).

### STORE_FALSE

This case used for storing the values `false` respectively.  
Example at [examples.md/storefalse](examples.md#storefalse).

### STORE_TRUE

This case used for storing the values `true` respectively.  
Example at [examples.md/storetrue](examples.md#storetrue).

### VERSION

This case used for define the version flag.  
Example at [examples.md/version](examples.md#version).

## help

```cpp
Argument& help(const char* help__);
```

Set the help description massge for this argument.

## required

```cpp
Argument& required(bool required__);
```

Whether or not the command-line argument may be omitted.

## metavar

```cpp
Argument& metavar(const char* metavar__);
```

A name for the argument in usage messages.

## nargs

```cpp
Argument& nargs(std::size_t nargs__);
```

The number of command-line arguments that should be consumed by this object.

## defaults

```cpp
Argument& defaults(const Vector& defaults__);
```

Define the defaults string values.

## valid

```cpp
Argument& valid(IValid* pValid, bool isDeletable = true);
```

You can check format of argument with IValid interface.  
Example of Custom Valid at [examples.md/custom-valid-transform](examples.md#custom-valid-transform).

### ValidNumber

```cpp
args.addArgument("--arg").valid(new blet::Args::ValidNumber());
```

Check if arguments are number.

### ValidMinMax

```cpp
args.addArgument("--arg").valid(new blet::Args::ValidMinMax(0, 100));
```

Check if arguments are number and if in range of min-max.

### ValidChoise

```cpp
args.addArgument("--arg").valid(new blet::Args::ValidChoise(args.vector("foo", "bar")));
```

Check if arguments are in choise.

### ValidPath

```cpp
args.addArgument("--arg").valid(new blet::Args::ValidPath());
args.addArgument("--arg").valid(new blet::Args::ValidPath(blet::Args::ValidPath::IS_DIR));
args.addArgument("--arg").valid(new blet::Args::ValidPath(blet::Args::ValidPath::IS_FILE));
```

Check if arguments are valid path/dir/file.

## dest

```cpp
template<typename T>
Argument& dest(std::vector<std::vector<T> >& dest, void (*toDest)(std::vector<std::vector<T> >& dest, bool isExist, const std::vector<std::vector<std::string> >& arguments) = NULL);
template<typename T>
Argument& dest(std::vector<T>& dest, void (*toDest)(std::vector<T>& dest, bool isExist, const std::vector<std::string>& arguments) = NULL);
template<typename T>
Argument& dest(T& dest, void (*toDest)(T& dest, bool isExist, const std::string& argument) = NULL);
```

Define a reference of object for insert the value after [parseArguments](args.md#parsearguments) method.  
Action can be changed by `toDest` parameter with your function.

```cpp
unsigned long value;
args.addArgument("--arg").dest(value);
```

Examples at [dest.md](dest.md).

## getString

```cpp
std::string getString() const;
```

Get the string format of this argument.

## getDefault

```cpp
const std::string& getDefault() const;
```

Get the default value of argument.

## isNumber

```cpp
bool isNumber() const;
```

Check if this argument is a number ("1234aaa" is true with 1234 like number).

## getNumber

```cpp
double getNumber() const;
```

Get Number if [isNumber](#isnumber).

## isExists

```cpp
bool isExists() const;
```

After [parseArguments](args.md#parsearguments) method check if this argument is present in *argv*.

## isRequired

```cpp
bool isRequired() const;
```

Get [required](#required) option.

## count

```cpp
std::size_t count() const;
```

After [parseArguments](args.md#parsearguments) method check if number of this argument in *argv*.

## getNargs

```cpp
std::size_t getNargs() const;
```

Get [nargs](#nargs) option.

## getHelp

```cpp
const std::string& getHelp() const;
```

Get [help](#help-1) option.

## getMetavar

```cpp
const std::string& getMetavar() const;
```

Get [metavar](#metavar) option.

## getNameOrFlags

```cpp
const std::vector<std::string>& getNameOrFlags() const;
```

Get the name or flag(s) of this argument.

## getDefaults

```cpp
const std::vector<std::string>& getDefaults() const
```

Get the default(s) value(s) of this argument.

## getAction

```cpp
Action::eAction getAction() const;
```

Get [action](#action) option.

## operator bool()

```cpp
operator bool() const;
```

Operator constructor bool, check if argument object [isExists](#isexists).  
For action [STORE_FALSE](#store_false) the effect is inversed.

Example:

```cpp
if (args["--option"]) { // call operator bool()
    std::cout << args["--option"] << std::endl;
}
```

## operator std::string()

```cpp
operator std::string() const;
```

Call [getString](#getstring) method.

Example:

```cpp
std::string option = args["--option"];
```

## operator std::vector\<std::string\>()

```cpp
operator std::vector<std::string>() const;
```

If the argument object contains a lot of one argument, you can get a std::vector of std::string.

Example:

```cpp
std::vector<std::string> options = args["--options"];
```

## operator std::vector\<std::vector\<std::string\> \>()

```cpp
operator std::vector<std::vector<std::string> >() const;
```

If the argument object contains a lot of one argument with number of argument ([nargs](#nargs)) bigger than one, you can get a std::vector of std::vector of std::string.

Example:

```cpp
std::vector<std::vector<std::string> > options = args["--options"];
```

## operator T()

```cpp
template<typename T>
operator T() const;
```

Call the [getNumber](#getnumber) method with your custom type.

Example:

```cpp
double option = args["--option"];
```
