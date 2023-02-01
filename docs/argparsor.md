# Argparsor

## Constructor

```cpp
Argparsor(bool addHelp);
```

If `addhelp` is true generate a action help argument with the flags -h and --help.

## Destructor

```cpp
virtual ~Argparsor();
```

Delete all new object.

## isAlternative

```cpp
bool isAlternative() const;
```

Use this after [parseArguments](#parseArguments) method for check if alternative mode was activated.

## isStrict

```cpp
bool isStrict() const;
```

Use this after [parseArguments](#parseArguments) method for check if strict mode was activated.

## getBinaryName

```cpp
const std::string& getBinaryName() const;
```

Use this after [parseArguments](#parseArguments) method for get the binary name (argv[0]).

## getUsage

```cpp
std::string getUsage() const;
```

## getVersion

```cpp
std::string getVersion() const;
```

## argumentExists

```cpp
bool argumentExists(const std::string& nameOrFlag) const;
bool argumentExists(const char* nameOrFlag) const;
```

## isAlternative

```cpp
bool isAlternative() const;
```

## isAlternative

```cpp
bool isAlternative() const;
```