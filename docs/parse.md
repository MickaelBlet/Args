# Parse

## parseArguments

```cpp
void parseArguments(int argc, char* argv[], bool alternative = false, bool strict = false);
```

Convert argument strings to objects and assign them as attributes of the argparsor map.  
Previous calls to [add_argument](argument.md#addargument) determine exactly what objects are created and how they are assigned.

Example:
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("FOO");
    args.parseArguments(argc, argv);
    // check if FOO exists
    if (args["FOO"]) {
        std::cout << args["FOO"] << std::endl;
    }
    return 0;
}
```
```
$ ./a.out
$ ./a.out 42
42
$ ./a.out -h
usage: a.out [-h] -- [FOO]

positional arguments:
  FOO

optional arguments:
  -h, --help            show this help message and exit
```

Other examples at [examples.md](examples.md).

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

Use this after [parseArguments](#parseArguments) method for get the binary name.

## getAdditionnalArguments

```cpp
const std::vector<std::string>& getAdditionalArguments() const;
```

Use this after [parseArguments](#parseArguments) method for get the additionnal arguments.
