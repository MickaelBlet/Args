# Optparsor
Check and Get options from argc and argv

## Build
```bash
# static build
mkdir build ; pushd build && cmake .. && make -j ; popd
# shared build
mkdir build ; pushd build && cmake -DBUILD_SHARED_LIBS=1 .. && make -j ; popd
# build and launch test (gcov and gtest required)
mkdir build ; pushd build && cmake -DBUILD_TESTING=1 -DBUILD_COVERAGE=1 .. && make -j && make test ; popd
```

## Options

|Type|Method|Parameters
|-|-|-
|positional|addPositionalArgument|name<br/>help (default: NULL)<br/>required (default: false)<br/>defaultValue (default: NULL)
|boolean|addBooleanOption|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)
|simple|addSimpleOption|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>defaultValue (default: NULL)
|number|addNumberOption|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbArgs (default: 0)<br/>...
|infinite|addInfiniteOption|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbDefaultArgs (default: 0)<br/>...
|multi|addMultiOption|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbDefaultArgs (default: 0)<br/>...

## Examples

### Default

```cpp
#include "optparsor.h"

int main(int argc, char* argv[]) {
    mblet::Optparsor optparsor;
    try {
        optparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Optparsor::ParseArgumentException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        optparsor.getUsage(std::cerr);
        return 1; //END
    }
    return 0;
}
```
```
$ ./a.out -a
./a.out: invalid option -- 'a'
usage: ./a.out [-h]

optional arguments:
  -h, --help  show this help message and exit
$ ./a.out --foo
./a.out: invalid option -- 'foo'
usage: ./a.out [-h]

optional arguments:
  -h, --help  show this help message and exit
$ ./a.out --help
usage: ./a.out [-h]

optional arguments:
  -h, --help  show this help message and exit
```

### Positional arguments

```cpp
#include "optparsor.h"

int main(int argc, char* argv[]) {
    mblet::Optparsor optparsor;
    optparsor.addPositionalArgument("REQUIRED", "help of required", true);
    optparsor.addPositionalArgument("ARGUMENT", "help of argument", false, "defaultValue");
    try {
        optparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Optparsor::ParseArgumentException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "REQUIRED: " << optparsor["REQUIRED"].c_str() << std::endl;
    if (optparsor["ARGUMENT"]) {
        std::cout << "ARGUMENT: " << optparsor["ARGUMENT"].c_str() << std::endl;
    }
    return 0;
}
```
```
$ ./a.out
./a.out: argument is required -- 'REQUIRED'
$ ./a.out foo
REQUIRED: foo
$ ./a.out foo bar
REQUIRED: foo
ARGUMENT: bar
$ ./a.out --help
usage: ./a.out [-h] REQUIRED ARGUMENT

positional arguments:
  REQUIRED    help of required (required)
  ARGUMENT    help of argument (default: defaultValue)

optional arguments:
  -h, --help  show this help message and exit
```

### Boolean Option
```cpp
#include "optparsor.h"

int main(int argc, char* argv[]) {
    mblet::Optparsor optparsor;
    optparsor.addBooleanOption("-r", "--required", "help of required", true);
    optparsor.addBooleanOption("-b", "--boolean", "help of boolean", false);
    try {
        optparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Optparsor::ParseArgumentException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "-r: " << optparsor["-r"].c_str() << std::endl;
    std::cout << "-b: " << optparsor["-b"].c_str() << std::endl;
    return 0;
}
```
```
$ ./a.out
./a.out: option is required -- '--required'
$ ./a.out --required
-r: true
-b: false
$ ./a.out --required --boolean
-r: true
-b: true
$ ./a.out --help
usage: ./a.out [-h] [-r] [-s]

optional arguments:
  -b, --boolean   help of boolean
  -h, --help      show this help message and exit
  -r, --required  help of required (required)
```

### Simple Option
```cpp
#include "optparsor.h"

int main(int argc, char* argv[]) {
    mblet::Optparsor optparsor;
    optparsor.addSimpleOption("-r", "--required", "help of required", true, "argRequired");
    optparsor.addSimpleOption("-s", "--simple", "help of simple", false, "argSimple", "defaultValue");
    try {
        optparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Optparsor::ParseArgumentException& e) {
        std::cerr << optparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "-r: " << optparsor["-r"].c_str() << std::endl;
    std::cout << "-s: " << optparsor["-s"].c_str() << std::endl;
    return 0;
}
```
```
$ ./a.out
./a.out: option is required -- '--required'
$ ./a.out --required foo
-r: foo
-s: defaultValue
$ ./a.out --required=foo --simple=bar
-r: foo
-s: bar
$ ./a.out --help
usage: ./a.out [-h] [-r argRequired] [-s argSimple]

optional arguments:
  -h, --help                  show this help message and exit
  -r, --required argRequired  help of required (required)
  -s, --simple argSimple      help of simple (default: defaultValue)
```

### Other

Other example at [example/example.md](example/example.md)