# Argument

## addArgument

```cpp
Argument& addArgument(const Vector& nameOrFlags);
```

Create a Argument object for use the definition methods.

Example:
```cpp
Argparsor args;
args.addArgument({"-a", "-b"});
// args.addArgument(args.vector("-a", "-b")); // C++98
```

### Definition

| Methods     | Links |
|-------------|-------|
| flag | [#flag](#flag) |
| action | [#action](#action) |
| help | [#help](#help-1) |
| required | [#required](#required) |
| metavar | [#metavar](#metavar) |
| nargs | [#nargs](#nargs) |
| defaults | [#defaults](#defaults) |
| *valid* | [#valid](#valid) |
| *dest* | [#dest](#dest) |

## getArgument

```cpp
const Argument& getArgument(const char* nameOrFlag) const;
const Argument& getArgument(const std::string& nameOrFlag) const;
const Argument& operator[](const char* nameOrFlag) const;
const Argument& operator[](const std::string& nameOrFlag) const;
```

Get a const ref. argument object if exists.

### Access

| Methods     | Links |
|-------------|-------|
| *count* | [#count](#count) |
| isExists | [#isexists](#isexists) |
| isRequired | [#isrequired](#isrequired) |
| getNargs | [#getnargs](#getnargs) |
| getHelp | [#gethelp](#gethelp) |
| getMetavar | [#getmetavar](#getmetavar) |
| getNameOrFlags | [#getnameorflags](#getnameorflags) |
| getDefaults | [#getdefaults](#getdefaults) |
| getAction | [#getaction](#getaction) |
| getString | [#getstring](#getstring) |
| getNumber | [#getnumber](#getnumber) |
| operator bool() | [#operator-bool](#operator-bool) |
| operator std::string() | [#operator-string](#operator-string) |
| operator\<\< | [#operator-stream-insertion](#operator-stream-insertion) |

## Argument object methods

### flag

```cpp
Argument& flag(const char* flag_);
```

Add flag in argument object.

Example:
```cpp
Argparsor args;
args.addArgument("-f").flag("--foo");
```

### action

```cpp
Argument& action(enum Action::eAction action_);
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

#### NONE

This just stores the argument’s value. This is the default action.  
Example at [examples.md/none](examples.md#none).

#### APPEND

This stores a list, and appends each argument value to the list. It is useful to allow an option to be specified multiple times. If the default value is non-empty, the default elements will be present in the parsed value for the option, with any values from the command line appended after those default values.  
Example at [examples.md/append](examples.md#append).

#### EXTEND

This stores a list, and extends each argument value to the list.  
Example at [examples.md/extend](examples.md#extend).

#### HELP

This case used for create the help flag.  
⚠ Can only use this action after constructor with false parameter or remove the last help flags.  

```cpp
mblet::Argparsor args(false);
// or
// mblet::Argparsor args;
// args.removeArgument(args.vector("-h", "--help"));
```

Example at [examples.md/help](examples.md#help).

#### INFINITE

This stores a list.  
Example at [examples.md/infinite](examples.md#infinite).

#### STORE_FALSE

This case used for storing the values `false` respectively.  
Example at [examples.md/storefalse](examples.md#storefalse).

#### STORE_TRUE

This case used for storing the values `true` respectively.  
Example at [examples.md/storetrue](examples.md#storetrue).

#### VERSION

This case used for define the version flag.  
Example at [examples.md/version](examples.md#version).

### help

```cpp
Argument& help(const char* help_);
```

Set the help description massge for this argument.

### required

```cpp
Argument& required(bool required_);
```

Whether or not the command-line argument may be omitted.

### metavar

```cpp
Argument& metavar(const char* metavar_);
```

A name for the argument in usage messages.

### nargs

```cpp
Argument& nargs(std::size_t nargs_);
```

The number of command-line arguments that should be consumed by this object.

### defaults

```cpp
Argument& defaults(const Vector& defaults_);
```

### valid

```cpp
Argument& valid(IValid* pValid, bool isDeletable = true);
```

You can check format of argument with IValid interface object.  
Example of Custom Valid at [examples.md/custom-valid-transform](examples.md#custom-valid-transform).

#### ValidNumber

Check if arguments are number.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidNumber());
```

#### ValidMinMax

Check if arguments are number and if in range of min-max.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidMinMax(0, 100));
```

#### ValidChoise

Check if arguments are in choise.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidChoise(args.vector("foo", "bar")));
```

#### ValidPath

Check if arguments are valid path/dir/file.

```cpp
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath());
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath(mblet::Argparsor::ValidPath::IS_DIR));
args.addArgument("--arg").valid(new mblet::Argparsor::ValidPath(mblet::Argparsor::ValidPath::IS_FILE));
```

### dest

```cpp
template<typename T>
Argument& dest(std::vector<std::vector<T> >& dest, void (*toDest)(std::vector<std::vector<T> >& dest, bool isExist, const std::vector<std::vector<std::string> >& arguments) = NULL);
template<typename T>
Argument& dest(std::vector<T>& dest, void (*toDest)(std::vector<T>& dest, bool isExist, const std::vector<std::string>& arguments) = NULL);
template<typename T>
Argument& dest(T& dest, void (*toDest)(T& dest, bool isExist, const std::string& argument) = NULL);
```

Define a reference of object for insert the value after [parseArguments](parse.md#parsearguments) method.  
Action can be changed by `toDest` parameter with your function.

```cpp
unsigned long value;
args.addArgument("--arg").dest(value);
```

Examples at [dest.md](dest.md).

### getString

```cpp
std::string getString() const;
```

Get the string format of this argument.

### isNumber

```cpp
bool isNumber() const;
```

Check if this argument is a number ("1234aaa" return *true* with 1234 like number).

### getNumber

```cpp
double getNumber() const;
```

Get Number if [isNumber](#isnumber).

### isExists

```cpp
bool isExists() const;
```

After [parseArguments](parse.md#parsearguments) method check if this argument is present in *argv*.

### isRequired

```cpp
bool isRequired() const;
```

Get [required](#required) option.

### count

```cpp
std::size_t count() const;
```

After [parseArguments](parse.md#parsearguments) method check if number of this argument in *argv*.

### getNargs

```cpp
std::size_t getNargs() const;
```

Get [nargs](#nargs) option.

### getHelp

```cpp
const std::string& getHelp() const;
```

Get [help](#help-1) option.

### getMetavar

```cpp
const std::string& getMetavar() const;
```

Get [metavar](#metavar) option.

### getNameOrFlags

```cpp
const std::vector<std::string>& getNameOrFlags() const;
```

Get the name or flag(s) of this argument.

### getDefaults

```cpp
const std::vector<std::string>& getDefaults() const
```

Get the default(s) value(s) of this argument.

### getAction

```cpp
Action::eAction getAction() const;
```

Get [action](#action) option.

### operator bool()

```cpp
operator bool() const;
```

### operator std::string()

```cpp
operator std::string() const;
```

### operator std::vector\<std::string\>()

```cpp
operator std::vector<std::string>() const;
```

### operator std::vector\<std::vector\<std::string\> \>()

```cpp
operator std::vector<std::vector<std::string> >() const;
```

### operator T()

```cpp
template<typename T>
operator T() const;
```