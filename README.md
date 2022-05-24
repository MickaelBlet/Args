# Argparsor
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

## Arguments

|Type|Method|Parameters
|-|-|-
|positional|addPositionalArgument|name<br/>help (default: NULL)<br/>required (default: false)<br/>defaultValue (default: NULL)
|boolean|addBooleanArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)
|simple|addSimpleArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>defaultValue (default: NULL)
|number|addNumberArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbArgs (default: 0)<br/>...
|infinite|addInfiniteArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbDefaultArgs (default: 0)<br/>...
|multi|addMultiArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbDefaultArgs (default: 0)<br/>...

## Examples

### Default

```cpp
#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    try {
        argparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; //END
    }
    return 0;
}
```
```
$ ./a.out -a
./a.out: invalid option -- 'a'
$ ./a.out --foo
./a.out: invalid option -- 'foo'
$ ./a.out --help
usage: ./a.out [-h]

optional arguments:
  -h, --help  show this help message and exit
```

### Positional arguments

```cpp
#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    argparsor.addPositionalArgument("REQUIRED", "help of required", true);
    argparsor.addPositionalArgument("ARGUMENT", "help of argument", false, "defaultValue");
    try {
        argparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "REQUIRED: " << argparsor["REQUIRED"].c_str() << std::endl;
    if (argparsor["ARGUMENT"]) {
        std::cout << "ARGUMENT: " << argparsor["ARGUMENT"].c_str() << std::endl;
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

### Boolean Argument
```cpp
#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    argparsor.addBooleanArgument("-r", "--required", "help of required", true);
    argparsor.addBooleanArgument("-b", "--boolean", "help of boolean", false);
    try {
        argparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "-r: " << argparsor["-r"].c_str() << std::endl;
    std::cout << "-b: " << argparsor["-b"].c_str() << std::endl;
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

### Simple Argument
```cpp
#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    argparsor.addSimpleArgument("-r", "--required", "help of required", true, "argRequired");
    argparsor.addSimpleArgument("-s", "--simple", "help of simple", false, "argSimple", "defaultValue");
    try {
        argparsor.parseArguments(argc, argv);
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what() \
                  << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    std::cout << "-r: " << argparsor["-r"].c_str() << std::endl;
    std::cout << "-s: " << argparsor["-s"].c_str() << std::endl;
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