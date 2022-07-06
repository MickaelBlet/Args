# Argparsor

Parse and stock options from argc and argv

## Build

```bash
# static build
mkdir build ; pushd build && cmake .. && make -j ; popd
# shared build
mkdir build ; pushd build && cmake -DBUILD_SHARED_LIBS=1 .. && make -j ; popd
# build and launch test (gcov and gtest required)
mkdir build ; pushd build && cmake -DBUILD_TESTING=1 -DBUILD_COVERAGE=1 .. && make -j && make test ; popd
```

<details open><summary><h2>Argument methods</h2></summary>

|Method|Parameters
|-|-
|addPositionalArgument|name<br/>help (default: NULL)<br/>required (default: false)<br/>defaultValue (default: NULL)
|addBooleanArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)
|addSimpleArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>defaultValue (default: NULL)
|addNumberArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbArgs (default: 0)<br/>...
|addInfiniteArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbDefaultArgs (default: 0)<br/>...
|addMultiArgument|shortName<br/>longName (default: NULL)<br/>help (default: NULL)<br/>required (default: false)<br/>usageName (default: NULL)<br/>nbDefaultArgs (default: 0)<br/>...

</details>

## Examples

```cpp
#include "argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor argparsor;
    argparsor.setDescription("custom description message");
    argparsor.setEpilog("custom epilog message");
    argparsor.setHelpArgument("-h", "--help", "custom help option message");
    argparsor.addPositionalArgument("REQUIRED", "help of required positional argument", true);
    argparsor.addBooleanArgument("-b", NULL, "help of boolean option", false);
    argparsor.addBooleanArgument("-c", NULL, "help of count option", false);
    argparsor.addSimpleArgument("-s", "--simple", "help of simple option", false, "argSimple", NULL);
    argparsor.addNumberArgument("-n", "--number", "help of number", false, "ARG1 ARG2", 2, "foo", "bar");
    argparsor.addInfiniteArgument(NULL, "--infinite", "help of infinite");
    argparsor.addMultiArgument("-m", "--multi", "help of multi", false, "MULTI", 3, "0", "1", "2");
    try {
        argparsor.parseArguments(argc, argv);
        std::cout << "-b: " << argparsor["-b"] << std::endl;
        std::cout << "-c: " << argparsor["-c"].count << std::endl;
        std::cout << "REQUIRED: " << argparsor["REQUIRED"].get<int>() << " (" << argparsor["REQUIRED"].str() << ")" << std::endl;
        if (argparsor["-s"]) {
            std::cout << "-s: " << argparsor["-s"] << std::endl;
        }
        std::cout << "-n: [0]: " << argparsor["-n"][0] << ", [1]: " << argparsor["-n"][1].get<double>() << " (" << argparsor["-n"] << ")" << std::endl;
        if (argparsor["--infinite"]) {
            std::cout << "--infinite: " << argparsor["--infinite"] << std::endl;
        }
        std::cout << "-m: " << argparsor["-m"] << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << argparsor.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; //END
    }
    return 0;
}
```

```
$ ./a.out -h
usage: ./a.out [-b] [-c] [-h] [-m MULTI] [-n ARG1 ARG2] [-s argSimple] [--infinite INFINITE...] REQUIRED

custom description message

positional arguments:
  REQUIRED                help of required positional argument (required)

optional arguments:
  -b                      help of boolean option
  -c                      help of count option
  -h, --help              custom help option message
  -m, --multi MULTI       help of multi (default: 0 1 2)
  -n, --number ARG1 ARG2  help of number (default: foo bar)
  -s, --simple argSimple  help of simple option
  --infinite INFINITE...  help of infinite

custom epilog message
```
```
$ ./a.out -a
./a.out: invalid option -- 'a'
```
```
$ ./a.out --foo
./a.out: invalid option -- 'foo'
```
```
$ ./a.out 042
-b: false
-c: 0
REQUIRED: 34 (042)
-n: [0]: foo, [1]: 0 (foo, bar)
-m: 0, 1, 2
```
```
$ ./a.out 0x42 -n 24 42.42
-b: false
-c: 0
REQUIRED: 66 (0x42)
-n: [0]: 24, [1]: 42.42 (24, 42.42)
-m: 0, 1, 2
```
```
$ ./a.out true -n 24 42.42 -s woot --infinite -1 0 1 2 -m=foo -ccc -m bar
-b: false
-c: 3
REQUIRED: 1 (true)
-s: woot
-n: [0]: 24, [1]: 42.42 (24, 42.42)
--infinite: -1, 0, 1, 2
-m: foo, bar
```
