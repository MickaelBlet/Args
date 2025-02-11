# Args

## setVersion

```cpp
void setVersion(const char* version);
```

Set the version message.

## getVersion

```cpp
const std::string& getVersion() const;
```

Get the version message.

## setAlternative

```cpp
Args& setAlternative(bool alternivative = true);
```

Active parsing for accept long option with only one '-' character.

## isAlternative

```cpp
bool isAlternative() const;
```

Get the status of alternative.

## setStrict

```cpp
Args& setStrict(bool strict = true);
```

Active exception if not all argument is used else you can take additionals arguments with [getAdditionalArguments](#getadditionalarguments) method.

## isStrict

```cpp
bool isStrict() const;
```

Get the status of strict.

## setHelpException

```cpp
Args& setHelpException(bool helpException = true);
```

Throw a HelpException when help action is present in arguments else exit(0) the your program after output usage at stdout.

## isHelpException

```cpp
bool isHelpException() const;
```

Get the status of helpException.

## setVersionException

```cpp
Args& setVersionException(bool versionException = true);
```

Throw a VersionException when version action is present in arguments else exit(0) the your program after output usage at stdout.

## isVersionException

```cpp
bool isVersionException() const;
```

Get the status of versionException.

## setBinaryName

```cpp
void setBinaryName(const char* binaryName);
```

Set the binary name.

## getBinaryName

```cpp
const std::string& getBinaryName() const;
```

Get the binary name.

## argumentExists

```cpp
bool argumentExists(const std::string& nameOrFlag) const;
```

Check if name or flag is added with [addArgument](#addargument) method.

## getArgument

```cpp
const Argument& getArgument(const std::string& nameOrFlag) const;
const Argument& operator[](const std::string& nameOrFlag) const
```

Get the const argument from name or flag.

### Access

|Methods||||
|---|---|---|---|
| [count](argument.md#count) | [isExists](argument.md#action) | [isRequired](argument.md#isRequired) |[getNargs](argument.md#getnargs) |
| [getHelp](argument.md#getHelp) | [getMetavar](argument.md#getMetavar) | [getNameOrFlags](argument.md#getNameOrFlags) |[getDefaults](argument.md#getDefaults) |
| [getAction](argument.md#getAction) | [getString](argument.md#getString) | [getNumber](argument.md#getNumber) |[operator-bool](argument.md#operator-bool) |
| [operator-string](argument.md#operator-string) |

## getAdditionalArguments

```cpp
const std::vector<std::string>& getAdditionalArguments() const;
```

Get the additional arguments after [parseArguments](#parsearguments) method if not strict mode activated.

## parseArguments

```cpp
void parseArguments(int argc, char* argv[]);
```

Convert argument strings to objects and assign them as attributes of the args map.
Previous calls to [addArgument](#addargument) determine exactly what objects are created and how they are assigned.

### Parse Options

|Methods||
|---|---|
| [setStrict](#setstrict) | [setAlternative](#setalternative) |
| [setHelpException](#sethelpexception) | [setVersionException](#setversionexception) |

## addArgument

```cpp
Argument& addArgument(const Vector& nameOrFlags);
```

Define how a single command-line argument should be parsed.

Example:
```cpp
Args args;
args.addArgument({"-a", "-b"});
// args.addArgument(args.vector("-a", "-b")); // C++98
args.addArgument("-c");
args.addArgument("ARG");
```

### Definitions

|Methods|||
|---|---|---|
| [flag](argument.md#flag) | [action](argument.md#action) | [help](argument.md#help-1) |
| [required](argument.md#required) | [metavar](argument.md#metavar) | [nargs](argument.md#nargs) |
| [defaults](argument.md#defaults) | [valid](argument.md#valid) | [dest](argument.md#dest) |

## updateArgument

```cpp
Argument& updateArgument(const std::string& nameOrFlag);
```

Get the ref. of argument from name or flag.

## removeArguments

```cpp
void removeArguments(const Vector& nameOrFlags);
```

Remove previously arguments.

## clear

```cpp
void clear();
```

Clear and reset with defaults values.