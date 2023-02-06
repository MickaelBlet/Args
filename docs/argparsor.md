# Argparsor

## Constructor

```cpp
Argparsor(bool addHelp = true);
```

If `addhelp` is true generate a action help argument with the flags -h and --help.

## Destructor

```cpp
virtual ~Argparsor();
```

Delete all new object.

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

## isAlternative

```cpp
bool isAlternative() const;
```

Check if alternative mode was activated on [parseArguments](#parsearguments) method.

## isStrict

```cpp
bool isStrict() const;
```

Check if strict mode was activated on [parseArguments](#parsearguments) method.

## getBinaryName

```cpp
const std::string& getBinaryName() const;
```

Get the binary name (argv[0]) after [parseArguments](#parsearguments) method.

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
| [count](argument.md#count) | [isExists](argument.md#action) | [isRequired](argument.md#isRequired) |[getnargs](argument.md#getnargs) |
| [getHelp](argument.md#getHelp) | [getMetavar](argument.md#getMetavar) | [getNameOrFlags](argument.md#getNameOrFlags) |[getDefaults](argument.md#getDefaults) |
| [getAction](argument.md#getAction) | [getString](argument.md#getString) | [getNumber](argument.md#getNumber) |[operator-bool](argument.md#operator-bool) |
| [operator-string](argument.md#operator-string) |

## getAdditionalArguments

```cpp
const std::vector<std::string>& getAdditionalArguments() const;
```

Get the additionnal arguments after [parseArguments](#parsearguments) method if not strict mode activated.

## parseArguments

```cpp
void parseArguments(int argc, char* argv[], bool alternative = false, bool strict = false, bool usageException = false, bool versionException = false);
```

Convert argument strings to objects and assign them as attributes of the argparsor map.
Previous calls to [addArgument](#addargument) determine exactly what objects are created and how they are assigned.

## addArgument

```cpp
Argument& addArgument(const Vector& nameOrFlags);
```

Define how a single command-line argument should be parsed.

Example:
```cpp
Argparsor args;
args.addArgument({"-a", "-b"});
// args.addArgument(args.vector("-a", "-b")); // C++98
args.addArgument("-c");
args.addArgument("ARG");
```

### Definitions



|Methods|||
|---|---|---|
| [flag](docs/argument.md#flag) | [action](docs/argument.md#action) | [help](docs/argument.md#help-1) |
| [required](docs/argument.md#required) | [metavar](docs/argument.md#metavar) | [nargs](docs/argument.md#nargs) |
| [defaults](docs/argument.md#defaults) | [valid](docs/argument.md#valid) | [dest](docs/argument.md#dest) |

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